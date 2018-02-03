#! /usr/bin/env python

from __future__ import print_function
import openturns as ot

ot.TESTPREAMBLE()

try:
    mesh = ot.IntervalMesher([9]).build(ot.Interval(-1.0, 1.0))
    # 1D mesh, 1D covariance, uniform weight, automatic centering, more samples
    # than vertices
    cov1D = ot.AbsoluteExponential([1.0])
    sample = ot.GaussianProcess(cov1D, mesh).getSample(16)
    algo = ot.KarhunenLoeveSVDAlgorithm(sample, 0.0)
    algo.run()
    result = algo.getResult()
    lambd = result.getEigenValues()
    KLModes = result.getModesAsProcessSample()
    print("KL modes=", KLModes)
    print("KL eigenvalues=", lambd)
    coefficients = result.project(sample)
    print("KL coefficients=", coefficients)
    KLFunctions = result.getModes()
    print("KL functions=", KLFunctions)
    print("KL lift=", result.lift(coefficients[0]))
    print("KL lift as field=", result.liftAsField(coefficients[0]))
    # 1D mesh, 1D covariance, uniform weight, automatic centering
    sample = ot.GaussianProcess(cov1D, mesh).getSample(6)
    algo = ot.KarhunenLoeveSVDAlgorithm(sample, 0.0)
    algo.run()
    result = algo.getResult()
    lambd = result.getEigenValues()
    KLModes = result.getModesAsProcessSample()
    print("KL modes=", KLModes)
    print("KL eigenvalues=", lambd)
    coefficients = result.project(sample)
    print("KL coefficients=", coefficients)
    KLFunctions = result.getModes()
    print("KL functions=", KLFunctions)
    print("KL lift=", result.lift(coefficients[0]))
    print("KL lift as field=", result.liftAsField(coefficients[0]))
    # 1D mesh, 1D covariance, uniform weight, declared centered
    algo = ot.KarhunenLoeveSVDAlgorithm(sample, 0.0, True)
    algo.run()
    result = algo.getResult()
    lambd = result.getEigenValues()
    KLModes = result.getModesAsProcessSample()
    print("KL modes=", KLModes)
    print("KL eigenvalues=", lambd)
    coefficients = result.project(sample)
    print("KL coefficients=", coefficients)
    KLFunctions = result.getModes()
    print("KL functions=", KLFunctions)
    print("KL lift=", result.lift(coefficients[0]))
    print("KL lift as field=", result.liftAsField(coefficients[0]))
    # 1D mesh, 1D covariance, nonuniform weight, automatic centering
    weights = mesh.computeWeights()
    algo = ot.KarhunenLoeveSVDAlgorithm(sample, weights, 0.0, True)
    algo.run()
    result = algo.getResult()
    lambd = result.getEigenValues()
    KLModes = result.getModesAsProcessSample()
    print("KL modes=", KLModes)
    print("KL eigenvalues=", lambd)
    coefficients = result.project(sample)
    print("KL coefficients=", coefficients)
    KLFunctions = result.getModes()
    print("KL functions=", KLFunctions)
    print("KL lift=", result.lift(coefficients[0]))
    print("KL lift as field=", result.liftAsField(coefficients[0]))
    # 1D mesh, 1D covariance, uniform weight, automatic centering
    R = ot.CorrelationMatrix(2, [1.0, 0.5, 0.5, 1.0])
    scale = [1.0]
    amplitude = [1.0, 2.0]
    cov2D = ot.ExponentialModel(scale, amplitude, R)
    sample = ot.GaussianProcess(cov2D, mesh).getSample(6)
    algo = ot.KarhunenLoeveSVDAlgorithm(sample, 0.0)
    algo.run()
    result = algo.getResult()
    lambd = result.getEigenValues()
    KLModes = result.getModesAsProcessSample()
    print("KL modes=", KLModes)
    print("KL eigenvalues=", lambd)
    coefficients = result.project(sample)
    print("KL coefficients=", coefficients)
    KLFunctions = result.getModes()
    print("KL functions=", KLFunctions)
    print("KL lift=", result.lift(coefficients[0]))
    print("KL lift as field=", result.liftAsField(coefficients[0]))
except:
    import sys
    print("t_KarhunenLoeveSVDAlgorithm_std.py",
          sys.exc_info()[0], sys.exc_info()[1])