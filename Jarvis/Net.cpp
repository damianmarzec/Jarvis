#include "stdafx.h"
#include "Net.h"
#include "Neuron.h"
#include <vector>
#include <iostream>
#include <cassert>

//typedef std::vector<Neuron> Layer;

//void Layer::Layer() {
//
//}

Net::Net(const std::vector<unsigned>& topology)
{
	std::cout << "Net creating... [" << topology.size() << "]" << std::endl;

	unsigned layersCount = topology.size();
	for (unsigned layerNr = 0; layerNr < layersCount; ++layerNr) {

		std::cout << "  Layer creating... [" << layerNr << "]" << std::endl;

		layers.push_back(Layer{});
		unsigned outputsCount = layerNr == topology.size() - 1 ? 0 : topology[layerNr + 1];


		for (unsigned neuronNr = 0; neuronNr <= topology[layerNr]; ++neuronNr) {
			layers.back().push_back(Neuron(outputsCount, neuronNr));
		}

		// Dla bies ustawiamy wartoœæ zwsze 1.0
		layers.back().back().setOutputValue(1.0);
	}

}

void Net::feedForward(const std::vector<double>& inputVals)
{
	//@todo Dodaæ sprawdzanie czy jest minimum 1 warstwa neurownów

	// Liczba wejœæ danych musi byæ równa iloœci neurownów w pierwszej warstwie
	assert(inputVals.size() == layers[0].size()-1);

	// wprowadzanie danych do neuronów
	for (unsigned i = 0; i < inputVals.size(); ++i) {
			layers[0][i].setOutputValue(inputVals[i]);
	}

	for (unsigned layerNr = 1; layerNr < layers.size(); ++layerNr) {

		// wskaŸnikiem bêdzie szybciej
		Layer &prevLayer = layers[layerNr - 1];
		for (unsigned neuronNr = 0; neuronNr < layers[layerNr].size() - 1; ++neuronNr) {
			layers[layerNr][neuronNr].feedForward(prevLayer);
		}
	}
}


void Net::backProp(std::vector<double>& targetVals)
{
	// B³êdy
	Layer &outputLayer = layers.back();
	error = 0.0;

	// Lecimy po neuronach (bez bies)
	for (unsigned neuronNr = 1; neuronNr < outputLayer.size() - 1; ++neuronNr) {

		double delta = targetVals[neuronNr] - outputLayer[neuronNr].getOutputValue();
		error += delta * delta;
	}


	error /= outputLayer.size() - 1; // œrednia
	error = sqrt(error); // œrednia kwadratowa


	// Ogólne info
	recentAverageError =
		(recentAverageError	* recentAverageSmoothingFactor + error) / (recentAverageSmoothingFactor + 1.0);

	// Lecimy po neuronach w warstwie output(bez bies)
	// Liczymy grandient
	for (unsigned neuronNr = 1; neuronNr < outputLayer.size() - 1; ++neuronNr) {
		outputLayer[neuronNr].calclOutputGradients(targetVals[neuronNr]);
	}

	// Ukryte warstwy
	// Liczymy grandient
	for (unsigned layerNum = layers.size() - 2; layerNum > 2; --layerNum) {
		Layer &hiddenLayer = layers[layerNum];
		Layer &nextLayer = layers[layerNum + 1];

		for (unsigned neuronNr = 0; neuronNr < hiddenLayer.size() - 1; ++neuronNr) {
			hiddenLayer[neuronNr].calcHiddenGradients(nextLayer);
		}
	}

	// Wszystkie warstwy - bez input bo tam weight = 0
	for (unsigned layerNum = layers.size() - 1; layerNum > 0; --layerNum) {

		Layer &layer = layers[layerNum];
		Layer &prevLayer = layers[layerNum - 1];

		for (unsigned neuronNr = 1; neuronNr < layer.size() - 1; ++neuronNr) {
			layer[neuronNr].updateInputWeights(prevLayer);
		}
	}

}

void Net::getResults(std::vector<double>& resultsVals) const
{
	resultsVals.clear();

	for (unsigned neuronNum = 0; neuronNum < layers.back().size() - 1; ++neuronNum) {

		std::cout << "init - " << neuronNum << std::endl;

		resultsVals.push_back(layers.back()[neuronNum].getOutputValue());
	}
}

double Net::getRecentAverageError()
{
	return recentAverageError;
}

Net::~Net()
{

}
