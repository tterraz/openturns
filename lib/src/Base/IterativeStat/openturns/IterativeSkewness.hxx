
#ifndef OPENTURNS_ITERATIVESKEWNESS_HXX
#define OPENTURNS_ITERATIVESKEWNESS_HXX

#include "openturns/IterativeAlgorithmImplementation.hxx"
// #include "openturns/PersistentCollection.hxx"
#include "openturns/Point.hxx"

BEGIN_NAMESPACE_OPENTURNS

class OT_API IterativeSkewness
  : public IterativeAlgorithmImplementation
{
  CLASSNAME
  
public:
  
  explicit IterativeSkewness(const UnsignedInteger size = 1);
  
  IterativeSkewness * clone() const;
  
  void increment(const Scalar newData);
  
//   void increment(PersistentCollection<Scalar> & newData);
  
  void increment(const Point & newData);
  
  void increment(const Sample & newData);
  
  void finalize();
  
  /**
   * Comparison operator
   *
   * This method compares objects based on their content.
   */
  inline
  Bool operator ==(const IterativeSkewness & /*other*/) const
  {
    return true;
  }

  /**
   * Comparison operator
   *
   * This method compares objects based on their content.
   */
  inline
  Bool operator !=(const IterativeSkewness & other) const
  {
    return !operator==(other);
  }

  /* String converter */
  String __repr__() const;

  /* String converter */
  String __str__(const String & offset = "") const;
  
//   Sample & operator[] (const UnsignedInteger index);
//   
//   const Sample & operator[] (const UnsignedInteger index) const;
  
  UnsignedInteger getSize() const;
  
  UnsignedInteger getIteration() const;
  
  Point getSkewness() const;
  
  Point getVariance() const;
  
  Point getMean() const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);
  
private:
  UnsignedInteger              iteration_;
  UnsignedInteger              size_;
  PersistentCollection<Scalar> mean1Data_;
  PersistentCollection<Scalar> mean2Data_;
  PersistentCollection<Scalar> mean3Data_;
};

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_ITERATIVESKEWNESS_HXX */
