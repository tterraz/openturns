//                                               -*- C++ -*-
/**
 *  @brief Ipopt optimization solver.
 *
 *  Copyright 2005-2020 Airbus-EDF-IMACS-ONERA-Phimeca
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
#ifndef OPENTURNS_IPOPT_HXX
#define OPENTURNS_IPOPT_HXX

#include "openturns/OTprivate.hxx"
#include "openturns/OptimizationAlgorithmImplementation.hxx"

BEGIN_NAMESPACE_OPENTURNS

/**
 * @class Ipopt
 * Ipopt allows to solve a MINLP optimization problem, including:
 * + objective functions of continuous, discrete or binary variables
 * + multiple equality, inequality and bounds constraints
 */

class OT_API Ipopt
  : public OptimizationAlgorithmImplementation
{
  CLASSNAME

public:

  /** Constructors */
  Ipopt();

  explicit Ipopt( OptimizationProblem & problem);

  /** Virtual constructor */
  virtual Ipopt * clone() const;

  /** Ipopt static methods */
  static Bool IsAvailable();  // Check whether Ipopt support is available

  /** Performing the actual computation. */
  void run();

  /** Description of object */
  String __str__(const String & offset = "") const;
  String __repr__() const;

protected:
  /** Check whether this problem can be solved by this solver.  Must be overloaded by the actual optimisation algorithm */
  virtual void checkProblem(const OptimizationProblem & problem) const;

private:

};

END_NAMESPACE_OPENTURNS

#endif
