//                                               -*- C++ -*-
/**
 *  @brief ProcessSampleImplementation Class
 *
 *  Copyright 2005-2018 Airbus-EDF-IMACS-Phimeca
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "openturns/ProcessSampleImplementation.hxx"
#include "openturns/PersistentObjectFactory.hxx"
#include "openturns/Exception.hxx"
#include "openturns/ResourceMap.hxx"
#include "openturns/Drawable.hxx"
#include "openturns/Description.hxx"
#include "openturns/Log.hxx"

BEGIN_NAMESPACE_OPENTURNS

TEMPLATE_CLASSNAMEINIT(PersistentCollection<ProcessSampleImplementation>)

TEMPLATE_CLASSNAMEINIT(PersistentCollection<Field>)

static const Factory<PersistentCollection<Field> > Factory_PersistentCollection_Field;

CLASSNAMEINIT(ProcessSampleImplementation)

static const Factory<ProcessSampleImplementation> Factory_ProcessSampleImplementation;

ProcessSampleImplementation::ProcessSampleImplementation()
  : PersistentObject()
  , mesh_()
  , data_(0)
{
  // Nothing to do
}

/* Default constructor */
ProcessSampleImplementation::ProcessSampleImplementation(const UnsignedInteger size,
                             const Field & field)
  : PersistentObject()
  , mesh_(field.getMesh())
  , data_(SampleCollection(size, field.getValues()))
{
  // Nothing to do
}

ProcessSampleImplementation::ProcessSampleImplementation(const Mesh & mesh,
                             const UnsignedInteger size,
                             const UnsignedInteger dimension)
  : PersistentObject()
  , mesh_(mesh)
  , data_(SampleCollection(size, Sample(mesh.getVerticesNumber(), dimension)))
{
  // Nothing to do
}

/* Virtual constructor */
ProcessSampleImplementation * ProcessSampleImplementation::clone() const
{
  return new ProcessSampleImplementation(*this);
}

/* String converter */
String ProcessSampleImplementation::__repr__() const
{
  OSS oss(true);
  oss << "class=" << ProcessSampleImplementation::GetClassName()
      << " mesh=" << mesh_
      << " values=" << data_;
  return oss;
}

String ProcessSampleImplementation::__str__(const String & offset) const
{
  OSS oss(false);
  oss << offset << "[";
  String separator("");
  for (UnsignedInteger i = 0; i < data_.getSize(); ++i, separator = "\n") oss << separator << offset << "field " << i << ":\n" << getField(i).__str__(offset);
  oss << "]";
  return oss;
}

/* Partial copy constructor */
void ProcessSampleImplementation::add(const Field & field)
{
  if (getSize() == 0)
  {
    data_.add(field.getValues());
    mesh_ = field.getMesh();
  }
  else if ((data_[0].getDimension() == field.getOutputDimension()) && (mesh_ == field.getMesh())) data_.add(field.getValues());
  else throw InvalidArgumentException(HERE) << "Error: could not add the field. Either its dimenson or its mesh are incompatible.";
}

void ProcessSampleImplementation::add(const Sample & values)
{
  if (values.getSize() != mesh_.getVerticesNumber()) throw InvalidArgumentException(HERE) << "Error: could not add the values. Their size=" << values.getSize() << " does not match the number of vertices=" << mesh_.getVerticesNumber() << " of the mesh.";
  if ((getSize() > 0) && (data_[0].getDimension() != values.getDimension())) throw InvalidArgumentException(HERE) << "Error: could not add the values. Their dimension=" << values.getDimension() << " does not match the process sample dimension=" << data_[0].getDimension();
  data_.add(values);
}


/* Operators accessors */
Field ProcessSampleImplementation::getField(const UnsignedInteger index) const
{
  if (index >= data_.getSize()) throw OutOfBoundException(HERE)  << " Error - index should be between 0 and " << data_.getSize() - 1;
  return Field(mesh_, data_[index]);
}

void ProcessSampleImplementation::setField(const Field & field,
                             const UnsignedInteger index)
{
  if (index >= data_.getSize()) throw OutOfBoundException(HERE)  << " Error - index should be between 0 and " << data_.getSize() - 1;
  if (field.getOutputDimension() != data_[0].getDimension()) throw InvalidArgumentException(HERE) << "Error: expected a field of dimension=" << data_[0].getDimension() << ", got a field of dimension=" << field.getOutputDimension();
  data_[index] = field.getValues();
}

Sample & ProcessSampleImplementation::operator[] (const UnsignedInteger index)
{
  if (index >= data_.getSize()) throw OutOfBoundException(HERE)  << " Error - index should be between 0 and " << data_.getSize() - 1;
  return data_[index];
}

const Sample & ProcessSampleImplementation::operator[] (const UnsignedInteger index) const
{
  if (index >= data_.getSize()) throw OutOfBoundException(HERE)  << " Error - index should be between 0 and " << data_.getSize() - 1;
  return data_[index];
}

/* Time grid accessors */
RegularGrid ProcessSampleImplementation::getTimeGrid() const
{
  return RegularGrid(mesh_);
}

/* Mesh accessors */
Mesh ProcessSampleImplementation::getMesh() const
{
  return mesh_;
}

/* Dimension accessors */
UnsignedInteger ProcessSampleImplementation::getDimension() const
{
  if (data_.getSize() == 0) return 0;
  return data_[0].getDimension();
}

/* Dimension accessors */
UnsignedInteger ProcessSampleImplementation::getSize() const
{
  return data_.getSize();
}

Field ProcessSampleImplementation::computeMean() const
{
  const UnsignedInteger size = getSize();
  if (size == 0) return Field();
  if (size == 1) return Field(mesh_, data_[0]);
  Sample meanValues(data_[0]);
  for (UnsignedInteger i = 1; i < size; ++i) meanValues += data_[i];
  meanValues *= Point(getDimension(), 1.0 / size);
  return Field(mesh_, meanValues);
}

/* Compute the sample of spatial means of each field */
Sample ProcessSampleImplementation::computeTemporalMean() const
{
  if (!mesh_.isRegular() || (mesh_.getDimension() != 1)) throw InvalidArgumentException(HERE) << "Error: the temporal mean is defined only when the mesh is regular and of dimension 1.";
  return computeSpatialMean();
}

/* Compute the sample of spatial means of each field */
Sample ProcessSampleImplementation::computeSpatialMean() const
{
  const UnsignedInteger size = getSize();
  const UnsignedInteger dimension = getDimension();
  Sample result(size, dimension);
  for (UnsignedInteger i = 0; i < size; ++i) result[i] = data_[i].computeMean();
  return result;
}

/*
 * Method computeQuantilePerComponent() gives the quantile per component of the sample
 */
Field ProcessSampleImplementation::computeQuantilePerComponent(const Scalar prob) const
{
  const UnsignedInteger size = getSize();
  if (size == 0) return Field();
  if (size == 1) return Field(mesh_, data_[0]);
  // This initialization set the correct time grid into result
  const UnsignedInteger dimension = data_[0].getDimension();
  const UnsignedInteger length = data_[0].getSize();
  Sample result(length, dimension);
  // Loop over the location indices
  for (UnsignedInteger i = 0; i < length; ++i)
  {
    Sample dataI(size, dimension);
    for (UnsignedInteger j = 0; j < size; ++j)
      dataI[j] = data_[j][i];
    result[i] = dataI.computeQuantilePerComponent(prob);
  }
  return Field(mesh_, result);
}

/* Get the i-th marginal process sample */
ProcessSampleImplementation ProcessSampleImplementation::getMarginal(const UnsignedInteger index) const
{
  const UnsignedInteger size = data_.getSize();
  ProcessSampleImplementation result(mesh_, size, 1);
  for (UnsignedInteger i = 0; i < size; ++i) result[i] = data_[i].getMarginal(index);
  return result;
}

/* Get the marginal field corresponding to indices dimensions */
ProcessSampleImplementation ProcessSampleImplementation::getMarginal(const Indices & indices) const
{
  const UnsignedInteger size = data_.getSize();
  ProcessSampleImplementation result(mesh_, size, indices.getSize());
  for (UnsignedInteger i = 0; i < size; ++i) result[i] = data_[i].getMarginal(indices);
  return result;
}

/* Draw a marginal of the ProcessSampleImplementation, ie the collection of all the Field marginals */
Graph ProcessSampleImplementation::drawMarginal(const UnsignedInteger index) const
{
  if (mesh_.getDimension() != 1) throw NotDefinedException(HERE) << "Error: cannot draw a marginal sample if the mesh is of dimension greater than one. Here dimension=" << mesh_.getDimension();
  if (index > getDimension() - 1 ) throw InvalidArgumentException(HERE) << "Error : indice should be in {0,...," << getDimension() - 1 << "}";

  // Discretization of the x axis
  const String title(OSS() << getName() << " - " << index << " marginal" );
  Graph graph(title, "Time", "Values", true, "topright");
  const UnsignedInteger size = data_.getSize();
  const Description colors(Drawable::BuildDefaultPalette(size));
  for (UnsignedInteger i = 0; i < size; ++i)
  {
    Drawable drawable(Field(mesh_, data_[i]).drawMarginal(index).getDrawable(0));
    drawable.setColor(colors[i]);
    graph.add(drawable);
  }
  return graph;
}

/* Method save() stores the object through the StorageManager */
void ProcessSampleImplementation::save(Advocate & adv) const
{
  PersistentObject::save(adv);
  adv.saveAttribute( "mesh_", mesh_);
  adv.saveAttribute( "data_", data_ );
}

/* Method load() reloads the object from the StorageManager */
void ProcessSampleImplementation::load(Advocate & adv)
{
  PersistentObject::load(adv);
  adv.loadAttribute( "mesh_", mesh_);
  adv.loadAttribute( "data_", data_ );
}

END_NAMESPACE_OPENTURNS