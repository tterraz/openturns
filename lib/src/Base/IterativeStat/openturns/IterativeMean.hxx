
#ifndef OPENTURNS_ITERATIVEMEAN_HXX
#define OPENTURNS_ITERATIVEMEAN_HXX

#include "openturns/TypedInterfaceObject.hxx"
#include "openturns/IterativeMeanImplementation.hxx"

BEGIN_NAMESPACE_OPENTURNS

class OT_API IterativeMean
  : public TypedInterfaceObject<IterativeMeanImplementation>
{
  CLASSNAME
  
public:
  
  explicit IterativeMean(const UnsignedInteger size = 1);

  /** Copy constructors */
  IterativeMean(const IterativeMeanImplementation & implementation);

  /** Constructor from implementation */
  IterativeMean(const Pointer<IterativeMeanImplementation> & p_implementation);

#ifndef SWIG
  /** Constructor from implementation pointer */
  IterativeMean(IterativeMeanImplementation * p_implementation);
#endif
  
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
  Bool operator ==(const IterativeMean & /*other*/) const
  {
    return true;
  }

  /**
   * Comparison operator
   *
   * This method compares objects based on their content.
   */
  inline
  Bool operator !=(const IterativeMean & other) const
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
  
  Point getValues() const;

//   static AlgoRegister reg;
  
private:
//   static IterativeAlgorithm * create(const int size);
  UnsignedInteger              iteration_;
  UnsignedInteger              size_;
//   UnsignedInteger              dim_;
  PersistentCollection<Scalar> data_;
};

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_ITERATIVEMEAN_HXX */
