// Jarvis.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include "Net.h"
#include "TrainingData.h"
#include <iostream>
#include <cassert>
#include <string>

void showVectorVals(std::string label, std::vector<double> &v)
{
	//std::cout << " list " << v.size() << std::endl;
	std::cout << " " + label 
	//	<< " " 
	//	<< v.size() 
		<< " {";

	for (unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i];
		if (v.size() > 1) {
			std::cout << ", ";
		}
	}

	std::cout << "} " << std::endl;
}

void showVectorValsUnsigned(std::string label, std::vector<unsigned> &v)
{
	std::cout << " " + label << " " << v.size() << " {";
	for (unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i];
		if (v.size() > 1) {
			std::cout << ", ";
		}
	}

	std::cout << "} " << std::endl;
}

int main()
{
	TrainingData trainData("trainingData.txt");
	// e.g., { 3, 2, 1 }
	std::vector<unsigned> topology;
	trainData.getTopology(topology);
	showVectorValsUnsigned("topology:", topology);
	Net myNet(topology);
	std::vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;

	while (!trainData.isEof()) {

		trainingPass++;
		std::cout << "Pass " << trainingPass << " ~-~-~-~-~~-~" << std::endl;

		if (trainData.getNextInputs(inputVals) != topology[0]) {
			break;
		}
		//showVectorVals(": inputs:", inputVals);
		myNet.feedForward(inputVals);

		myNet.getResults(resultVals);
		showVectorVals("outputs:", resultVals);

		trainData.getTargetOutputs(targetVals);
		showVectorVals("targets :", targetVals);
		assert(targetVals.size() == topology.back());
		myNet.backProp(targetVals);
		

		std::cout << "error: "
			<< myNet.getRecentAverageError() << std::endl;
		//std::cout << "|~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~" << std::endl;
	}



	std::cout << std::endl << "done" << std::endl;

	TrainingData testData("testData.txt");


	int xx;
	std::cin >> xx;
	return 0;

}

