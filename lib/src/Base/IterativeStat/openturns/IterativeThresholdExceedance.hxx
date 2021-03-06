
#ifndef OPENTURNS_ITERATIVETHRESHOLDEXCEEDANCE_HXX
#define OPENTURNS_ITERATIVETHRESHOLDEXCEEDANCE_HXX

#include "openturns/IterativeAlgorithmImplementation.hxx"
#include "openturns/Point.hxx"

BEGIN_NAMESPACE_OPENTURNS

class OT_API IterativeThresholdExceedance
  : public IterativeAlgorithmImplementation
{
  CLASSNAME

public:

  explicit IterativeThresholdExceedance(const UnsignedInteger dimension = 1, const Scalar thresholdValue = 0.0);

  IterativeThresholdExceedance * clone() const;

  void increment(const Point & newData);

  void increment(const Sample & newData);
  /**
   * Comparison operator
   *
   * This method compares objects based on their content.
   */
  inline
  Bool operator ==(const IterativeThresholdExceedance & /*other*/) const
  {
    return true;
  }

  /**
   * Comparison operator
   *
   * This method compares objects based on their content.
   */
  inline
  Bool operator !=(const IterativeThresholdExceedance & other) const
  {
    return !operator==(other);
  }

  /* String converter */
  String __repr__() const;

  /* String converter */
  String __str__(const String & offset = "") const;

  Scalar getThresholdValue() const;

  Point getThresholdExceedance() const;

  /** Method save() stores the object through the StorageManager */
  void save(Advocate & adv) const;

  /** Method load() reloads the object from the StorageManager */
  void load(Advocate & adv);

private:
  Scalar thresholdValue_;
  Point data_;
};

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_ITERATIVETHRESHOLDEXCEEDANCE_HXX */
