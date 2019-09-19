
#ifndef OPENTURNS_ITERATIVEALGORITHMIMPLEMENTATION_HXX
#define OPENTURNS_ITERATIVEALGORITHMIMPLEMENTATION_HXX

#include "openturns/OSS.hxx"
#include "openturns/PersistentObject.hxx"
#include "openturns/Point.hxx"
#include "openturns/Sample.hxx"
// #include <unordered_map>                   // for std::map

BEGIN_NAMESPACE_OPENTURNS


class OT_API IterativeAlgorithmImplementation
  : public PersistentObject
{
  CLASSNAME

public:

  /**
   * Default constructor
   *
   * The constructor sets a new Id to the object,
   * so it can be later referenced by a Study object.
   * It is also declared visible if member of a study.
   *
   * The object has the default name but it does not
   * use storage for it.
   */
  IterativeAlgorithmImplementation()
    : PersistentObject()
  {
    // Nothing to do
  }

  IterativeAlgorithmImplementation(const IterativeAlgorithmImplementation & other)
    : PersistentObject(other)
    {
      // Nothing to do
    }

  /**
   * Virtual constructor
   *
   * @warning This method MUST be overloaded in derived classes.
   * @return A pointer to a newly allocated object similar to this one
   */
  virtual IterativeAlgorithmImplementation * clone() const = 0;

  /**
   * Increment methods
   *
   * @warning These methods MUST be overloaded in derived classes.
   */

  virtual void increment(const Point & newData) = 0;

  virtual void increment(const Sample & newData) = 0;

  virtual void finalize()
  {
    // Nothing to do
  }

  /**
   * Comparison operator
   *
   * This method compares objects based on their content.
   */
  inline virtual
  Bool operator ==(const IterativeAlgorithmImplementation & /*other*/) const
  {
    return true;
  }

  /**
   * Comparison operator
   *
   * This method compares objects based on their content.
   */
  inline virtual
  Bool operator !=(const IterativeAlgorithmImplementation & other) const
  {
    return !operator==(other);
  }

  /* String converter */
  virtual
  String __repr__() const
  {
    return OSS(true) << "class=" << getClassName();
  }

  /* String converter */
  virtual
  String __str__(const String & offset = "") const
  {
    return __repr__();
  }

  /** Method save() stores the object through the StorageManager
   *
   * @warning This method MUST be overloaded in derived classes.
   * @internal
   */
  virtual void save(Advocate & adv) const = 0;

  /** Method load() reloads the object from the StorageManager
   *
   * @warning This method MUST be overloaded in derived classes.
   * @internal
   */
  virtual void load(Advocate & adv) = 0;

}; /* class IterativeAlgorithmImplementation */

END_NAMESPACE_OPENTURNS

#endif /* OPENTURNS_ITERATIVEALGORITHMIMPLEMENTATION_HXX */
