#include "stdafx.h"
#include "Neuron.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

double Neuron::eta = 0.15;
double Neuron::alpha = 0.5;

Neuron::Neuron(unsigned outputsCount, unsigned myIndex)
{
	//std::cout << "    Neuron creating... [" << myIndex << "]" << std::endl;

	for (unsigned c = 0; c < outputsCount; ++c) {
		outputWeights.push_back(Connection());
	}

	index = myIndex;
}

void Neuron::setOutputValue(double input)
{
	outputVal = input;
}

double Neuron::getOutputValue() const
{
	return outputVal;
}


void Neuron::feedForward(const std::vector<Neuron> &prevLayer)
{
	double sum = 0.0;

	// dodajemy wszystkie wejscia
	// pamietac o neuroenie bias z poprzedniej warstwy

	for (unsigned neuronNr = 0; neuronNr < prevLayer.size(); ++neuronNr) {
		sum += prevLayer[neuronNr].getOutputValue() * prevLayer[neuronNr].outputWeights[index].weight;
	}
	
	outputVal = Neuron::transfer(sum);
}

void Neuron::calclOutputGradients(double targetVal)
{
	double delta = targetVal - outputVal;
	gradient = delta * Neuron::transferDerivative(outputVal);
}

void Neuron::calcHiddenGradients(const std::vector<Neuron>  & nextLayer)
{
	double dow = sumDow(nextLayer);
	gradient = dow * Neuron::transferDerivative(outputVal);
}

void Neuron::updateInputWeights(std::vector<Neuron> & prevLayer)
{
	for (unsigned neuronNr = 0; neuronNr < prevLayer.size(); ++neuronNr) {
		//Neuron &neuron prevLayer[neuronNr];
		double oldDeltaWeights = prevLayer[neuronNr].outputWeights[index].deltaWeight;
		double newDeltaWeight =
			eta
			* prevLayer[neuronNr].getOutputValue()
			* gradient
			+ alpha
			* oldDeltaWeights;

		prevLayer[neuronNr].outputWeights[index].deltaWeight = newDeltaWeight;
		prevLayer[neuronNr].outputWeights[index].weight += newDeltaWeight;

	}
}


double Neuron::randomWeight(void)
{
	return rand() / double(RAND_MAX);
}

double Neuron::transfer(double x)
{
	// od -1 do 1
	return tanh(x);
}

double Neuron::transferDerivative(double x)
{
	// Dziwna pochodna
	// Nie dok³adna - bêdzie szybciej :p
	return 1.0 - x * x;
}

double Neuron::sumDow(const std::vector<Neuron>& nextLayer) const
{
	double sum = 0.0;

	// bez bias
	for (unsigned neuronNum = 0; neuronNum < nextLayer.size() - 1; ++neuronNum) {
		sum += outputWeights[neuronNum].weight * nextLayer[neuronNum].gradient;
	}

	return sum;
}

