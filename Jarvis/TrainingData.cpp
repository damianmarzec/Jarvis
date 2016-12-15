#include "stdafx.h"
#include "TrainingData.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>


void TrainingData::getTopology(std::vector<unsigned> &topology)
{
	std::string line;
	std::string label;

	std::getline(m_trainingDataFile, line);

	std::stringstream ss(line);

	ss >> label;

	if (this->isEof() || label.compare("topology:") != 0) {
		std::cout << "I'm broke!";
		abort();
	}

	while (!ss.eof()) {
		unsigned n;
		ss >> n;
		topology.push_back(n);
	}

	return;
}

TrainingData::TrainingData(const std::string filename)
{
	m_trainingDataFile.open(filename.c_str());
}

unsigned TrainingData::getNextInputs(std::vector<double> &inputVals)
{
	inputVals.clear();

	std::string line;
	std::getline(m_trainingDataFile, line);
	std::stringstream ss(line);

	std::string label;
	ss >> label;
	if (label.compare("in:") == 0) {
		double oneValue;
		while (ss >> oneValue) {
			inputVals.push_back(oneValue);
		}
	}

	return inputVals.size();
}

unsigned TrainingData::getTargetOutputs(std::vector<double> &targetOutputVals)
{
	targetOutputVals.clear();

	std::string line;
	std::getline(m_trainingDataFile, line);
	std::stringstream ss(line);

	std::string label;
	ss >> label;
	if (label.compare("out:") == 0) {
		double oneValue;
		while (ss >> oneValue) {
			targetOutputVals.push_back(oneValue);
		}
	}

	return targetOutputVals.size();
}
//*/

//http://stackoverflow.com/questions/1903954/is-there-a-standard-sign-function-signum-sgn-in-c-c
template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

/*
template <class T> const T& min (const T& a, const T& b) {
return !(b<a)?a:b;     // or: return !comp(b,a)?a:b; for version (2)
}
*/