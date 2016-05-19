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
	for (unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}

	std::cout << std::endl;
}

void showVectorValsUnsigned(std::string label, std::vector<unsigned> &v)
{
	std::cout << " " + label << "  " << v.size() << std::endl;
	for (unsigned i = 0; i < v.size(); ++i) {
		std::cout << v[i] << " ";
	}

	std::cout << std::endl;
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
		if (trainData.getNextInputs(inputVals) != topology[0]) {
			break;
		}
		showVectorVals(": Inputs:", inputVals);
	}
	
	int x;
	std::cin >> x;
	return 0;

	while (!trainData.isEof()) {

		++trainingPass;
		std::cout << std::endl << "Pass " << trainingPass;

		if (trainData.getNextInputs(inputVals) != topology[0]) {
			break;
		}
		showVectorVals(": inputs:", inputVals);
		myNet.feedForward(inputVals);

		myNet.getResoults(resultVals);
		showVectorVals("outputs:", resultVals);

		trainData.getTargetOutputs(targetVals);
		showVectorVals("targets :", targetVals);
		assert(targetVals.size() == topology.back());
		myNet.backProp(targetVals);

		std::cout << "error: "
			<< myNet.getRecentAverageError() << std::endl;
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

