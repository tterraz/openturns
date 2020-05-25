
# Irerative Algorithms in OpenTURNS

This document describe the work of Inria for the implementation of iterative statistics and iterative sensitivity analysis in OpenTURNS.

## Table of Contents
* Overview
* Iterative Statistics
* Iterative Sensitivity Analysis

## Overview

OpenTURNS provides a lot of algorithms to compute classical statistics and Sobol indices. However, these algorithms are not designed to compute such statistics in an iterative fashion. In OpenTURNS, quantities of interest are computed directly from a sample or an experiment design. From a complete set of data, we compute the value of interest. This aproach can no longer scale with the size of the data set.
Iterative Algorithms can increment statistics with a subset of the data, and then are no longer limited by the size of the data set itself. They require a standalone data structure that can be fed with the samples iteratively. This point of view is not classical in OpenTurns. The data structure of the value of interest must persist and be updated when given new data. In this document, we present the  work of Inria to implemente iterative algorithms in OpenTURNS.

## Iterative Statistics

The iterative statistics have to satisfy folowing criterions:
* Have a persistent data structure to keep the current value of the statistic
* Have an Increment method
* keep track of the number of iterations

From these criterions, we defined a base class: <code>IterativeAlgorithm</code>. Its implementation is in <code>lib/src/baseIterativeStat</code>.
This class inherit from <code>PersistentObject</code> and is designed with a bridge patern. All the iterative statistics must inherit from <code>IterativeAlgorithm</code>.

Currently implemented iterative statistics are:
* IterativeExtrema
* IterativeThreshold exceedance
* Mean
* Variance
* Skewness
* Kurtosis
* Quantiles (not validated)

These objects are instanciable. They all inherit the <code>getIteration()</code> and <code>getDimension()</code> methods from the <code>IterativeAlgorithm</code> class, and overload the <code>Increment(Point)</code> and <code>Increment(Sample)</code> methods. These objects are standalone, so it is the responsibility of the user to manage the experiments that will generate the samples for the iterative algorithms.

These classes do not keep track of the input samples, but some quantities of interest can still be derived from the main statistic.
For example, the mean can be extracted from the internal data structure of the iterative variance, so the <code>IterativeVariance</code> class has a <code>getMean()</code> method.

All these classical iterative statistics do not affect the other parts of OpenTURNS.


## Iterative Sensitivity Analysis

As for the classical statistics, OpenTURNS is not designed for itertative sensitivity analysis. So as for the classical statistics, we defined a persistent object that contains the data structure for the Sobol' indices and the algorithms to compute them. This object is a <code>SobolIndices</code> object, its implementation is in <code>lib/src/Uncertainty/Algorithm/Sensitivity</code>. It is similar to <code>IterativeAlgorithm</code>: it inherits from <code>PersistentObject</code> and is designed with a bridge patern. The 4 classes that inherit from this class are: <code>JansenSobolIndices</code>, MartinezSobolIndices</code>, <code>MauntzKucherenkoSobolIndices</code> and <code>SaltelliSobolIndices</code>. These classes implement the methods to compute the corresponding Sobol' indices. In order to be consistent with the <code>SobolIndicesAlgorithm</code> classes, we moved the classical algorithm from
the corresponding <code>SobolIndicesAlgorithm</code> to the <code>SobolIndices</code> classes, and added a <code>SobolIndices</code> attribute to the SobolIndicesAlgorithm classes. This way, all the logic to manage the sensitivity analysis stays in the <code>SobolIndicesAlgorithm</code> classes, but the data and the algorithms of each <code>SobolIndices</code> live in a <code>SobolIndices</code> attribute.

The <code>SobolIndices</code> classes can be instancied outside a <code>SobolIndicesAlgorithm</code>, but the data that will be used to compute them must come from a <code>SobolIndicesExperiment</code>. (see <code>python/doc/examples/iterative_statistics/iterative_sobol.ipynb</code>).

The <code>SobolIndices</code> contains a method <code>ComputeIndices(Sample)</code> to compute the classical Sobol' indices of a Sample, and a <code>IncrementIndices(Sample)<code> method to increment the Sobol' indices with samples generated by the iterative pick-freeze method.