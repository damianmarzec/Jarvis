#pragma once
#include "stdafx.h"
#include "Connection.h"
#include <vector>

//typedef std::vector<Neuron> Layer;

class Neuron
{
public:
	Neuron(unsigned outputsCount, unsigned index);
	void setOutputValue(double input);
	double getOutputValue() const;
	void feedForward(const std::vector<Neuron> & prevLayer);
	void calclOutputGradients(double targetVal);
	void calcHiddenGradients(const std::vector<Neuron>  &nextLayer);
	void updateInputWeights(std::vector<Neuron> &prevLayer);

private:
	double outputVal;
	std::vector<Connection> outputWeights;

	static double randomWeight(void);
	static double transfer(double x);
	static double transferDerivative(double x);
	double sumDow(const std::vector<Neuron> &nextLayer) const;

	static double eta; // [0.0 .. 1.0] overall net training rate
	static double alpha; // [0.0 .. n] multiplyer of last weight chnage (omentum)

	unsigned index;
	double gradient;


};

