// Jarvis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include "Net.h"
#include "Debuger.h"
#include "TrainingData.h"
#include <iostream>
#include <cassert>
#include <string>


int main()
{


	TrainingData trainData("trainingData.txt");
	// e.g., { 3, 2, 1 }
	std::vector<unsigned> topology;
	trainData.getTopology(topology);
	Debuger::showVectorValsUnsigned("Topology", topology);

	Net myNet(topology);
	std::vector<double> inputVals, targetVals, resultVals;
	
	int trainingPass = 0;

	while (!trainData.isEof()) {

		++trainingPass;
		std::cout << std::endl << "Pass" << trainingPass;

		if (trainData.getNextInputs(inputVals) != topology[0]) {
			continue;
		}
		//Debuger::showVectorValsDouble("Inputs", inputVals);
		myNet.feedForward(inputVals);

		myNet.getResoults(resultVals);
		//Debuger::showVectorValsDouble("Outputs", resultVals);
		for (unsigned i = 0; i < resultVals.size(); ++i) {
			std::cout << " r:" << resultVals[i] << " ";
		}

		trainData.getTargetOutputs(targetVals);
		//Debuger::showVectorValsDouble("Targets", targetVals);
		for (unsigned i = 0; i < targetVals.size(); ++i) {
			std::cout << " t:" << targetVals[i] << " ";
		}

		assert(targetVals.size() == topology.back());
		myNet.backProp(targetVals);

		std::cout << " error: " << myNet.getRecentAverageError() << std::endl;
	}

	std::cout << std::endl << "done" << std::endl;
	int xx;
	std::cin >> xx;
	return 0;




	/*

	std::vector<unsigned> topology;
	std::vector<double> inputVals;
	std::vector<double> targetVals;
	std::vector<double> resoultVals;
	
	for (size_t i = 10; i > 0; i--)
	{
		topology.push_back(i);
	}


	for (size_t i = topology[0]; i > 0; i--)
	{
		inputVals.push_back(0.1);
	}



	Net network = Net(topology);

	

	network.feedForward(inputVals);

	network.backProp(targetVals);
	network.getResoults(resoultVals);

	showVectorVals("Inputs:", inputVals);
	showVectorVals("Outputs:", resoultVals);

	std::cout << std::endl << "Net recent average error: "
		<< network.getRecentAverageError() << std::endl;

	int x;
	std::cin >> x;
	return 0;
	*/
}

