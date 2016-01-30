#include "NeuralNetwork.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Neuron::Neuron(int inputs): m_inputs(inputs + 1)
{
	float a = 0.f, b = 1.f;

	for(int i = 0; i < m_inputs; ++i) // plus 1 for the bias
	{
		float value = (b - a) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) + a;
		m_weights.push_back(value);
	}
}

NeuronLayer::NeuronLayer(int numNeurons, int inputsPerNeuron)
{
	m_numNeurons = numNeurons;
	for(int i = 0; i < m_numNeurons; ++i)
	{
		m_neurons.push_back(Neuron(inputsPerNeuron));
	}
}

NeuralNetwork::NeuralNetwork(): m_layers{NeuronLayer(neuronsPerLayer, layer1InputsPerNeuron),
	NeuronLayer(neuronsPerLayer, layer2InputsPerNeuron)}
{

}

float NeuralNetwork::sigmoid(float activation) const
{
	return 1.f / (1.f + exp(-activation));
}

Move NeuralNetwork::calculateMove(bool inFov, bool bulletInFov, bool alreadyFired, float fov)
{
	Move move{0};

	std::vector<float> inputs = {static_cast<float>(inFov), static_cast<float>(bulletInFov),
								 static_cast<float>(alreadyFired), fov};
	std::vector<float> activations(neuronsPerLayer);

	for(int layerNum = 0; layerNum < layersCount; ++layerNum)
	{
		std::fill(activations.begin(), activations.end(), 0.f);
		for(int i = 0; i < m_layers[layerNum].m_numNeurons; ++i)
		{
			auto neuronInputs = m_layers[layerNum].m_neurons[i].m_inputs;
			for(int j = 0; j < neuronInputs - 1; ++j)
			{
				activations[i] += inputs[j] * m_layers[layerNum].m_neurons[i].m_weights[j];
			}
			activations[i] += (-1.f) * m_layers[layerNum].m_neurons[i].m_weights[neuronInputs - 1]; //bias
			activations[i] = sigmoid(activations[i]);
		}

		inputs = activations;
	}

	move.advanceStraight = static_cast<int>(activations[0] + 0.5f);
	move.turnLeft = static_cast<int>(activations[1] + 0.5f);
	move.turnRight = static_cast<int>(activations[2] + 0.5f);
	move.shoot = static_cast<int>(activations[3] + 0.5f);
	move.fovMult = activations[4];
	/*int res = rand();

	move.advanceStraight = res % 2;
	move.shoot = (res >> 1) % 2;
	move.turnLeft = (res >> 2) % 2;
	move.turnRight = (res >> 3) % 2;
	move.fovMult = 1.f;*/

	return move;
}

int NeuralNetwork::weightsCount() const
{
	int count = 0;

	for(const auto& layer: m_layers)
	{
		for(const auto& neuron: layer.m_neurons)
		{
			count += neuron.m_inputs;
		}
	}

	return count;
}

std::vector<float> NeuralNetwork::getWeights() const
{
	std::vector<float> weights;

	for(const auto& layer: m_layers)
	{
		for(const auto& neuron: layer.m_neurons)
		{
			weights.insert(weights.end(), neuron.m_weights.begin(), neuron.m_weights.end());
		}
	}

	return weights;
}

void NeuralNetwork::setWeights(const std::vector<float>& newWeights)
{
	auto start = newWeights.begin();
	for(auto& layer: m_layers)
	{
		for(auto& neuron: layer.m_neurons)
		{
			auto end = start + neuron.m_inputs;
			neuron.m_weights = std::vector<float>(start, end);
			start = end;
		}
	}
}
