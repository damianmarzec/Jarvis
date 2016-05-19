#include "stdafx.h"
#include "Neuron.h"
#include <vector>
#pragma once

typedef std::vector<Neuron> Layer;

class Net
{
public:
	Net(const std::vector<unsigned>& topology);
	void feedForward(const std::vector<double>& inputVals);
	void backProp(std::vector<double>& targetVals);
	void getResoults(std::vector<double>& resoultVals) const;

	double getRecentAverageError();

	~Net();
private:
	std::vector<Layer> layers;
	double error;
	double recentAverageError;
	double recentAverageSmoothingFactor;
};