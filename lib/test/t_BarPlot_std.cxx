//                                               -*- C++ -*-
/**
 *  @brief The test file of class BarPlot for standard methods
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
#include "openturns/OT.hxx"
#include "openturns/OTtestcode.hxx"

using namespace OT;
using namespace OT::Test;

int main(int , char *[])
{
  TESTPREAMBLE;
  OStream fullprint(std::cout);
  setRandomGenerator();

  try
  {

    // Instanciate one distribution object
    UnsignedInteger dim = 1;
    Point meanPoint(dim, 1.0);
    meanPoint[0] = 0.5;
    Point sigma(dim, 1.0);
    sigma[0] = 2.0;
    CorrelationMatrix R = IdentityMatrix(dim);
    Normal distribution1(meanPoint, sigma, R);

    // Instanciate another distribution object
    meanPoint[0] = -1.5;
    sigma[0] = 4.0;
    Normal distribution2(meanPoint, sigma, R);

    // Test for sampling
    UnsignedInteger size = 2000;
    UnsignedInteger nBars = 20;
    Sample sample1(distribution1.getSample( size ));
    Sample sample2(distribution2.getSample( size ));


    // Construct histograms
    Scalar epsilon = 0.1;
    Scalar min1 = sample1.getMin()[0];
    Scalar max1 = sample1.getMax()[0] + epsilon;
    Scalar min2 = sample2.getMin()[0];
    Scalar max2 = sample2.getMax()[0] + epsilon;
    Point tmp(2);
    tmp[0] = (max1 - min1) / nBars;
    tmp[1] = 0;
    Sample data1(nBars, tmp);
    tmp[0] = (max2 - min2) / nBars;
    Sample data2(nBars, tmp);
    UnsignedInteger index;

    for(UnsignedInteger i = 0; i < size; i++)
    {
      index = static_cast<UnsignedInteger>(floor((sample1[i][0] - min1) / (max1 - min1) * nBars));
      data1[index][1]++;
      index = static_cast<UnsignedInteger>(floor((sample2[i][0] - min2) / (max2 - min2) * nBars));
      data2[index][1]++;
    }

    // Create an empty graph
    Graph myGraph("Some barplots", "y", "frequency", true, "topleft");

    // Create the first barplot
    BarPlot myBarPlot1(data1, min1, "blue", "shaded", "dashed", "histogram1");

    // Then, draw it
    myGraph.add(myBarPlot1);
    myGraph.draw("Graph_BarPlot_a_OT.png");

    // Check that the correct files have been generated by computing their checksum

    // Create the second barplot
    BarPlot myBarPlot2(data2, min2, "red", "solid", "solid", "histogram2");

    // Add it to the graph and draw everything
    myGraph.add(myBarPlot2);
    myGraph.draw("Graph_BarPlot_b_OT.png");
  }
  catch (TestFailed & ex)
  {
    std::cerr << ex << std::endl;
    return ExitCode::Error;
  }


  return ExitCode::Success;
}
