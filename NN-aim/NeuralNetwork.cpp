#include "NeuralNetwork.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Neuron::Neuron(int inputs): m_inputs(inputs)
{
	float a = 0.f, b = 30.f;

	for(int i = 0; i < m_inputs + 1; ++i) // plus 1 for the bias
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

NeuralNetwork::NeuralNetwork(): m_firstLayer(neuronsPerLayer, layer1InputsPerNeuron),
		m_secondLayer(neuronsPerLayer, layer2InputsPerNeuron)
{

}

float NeuralNetwork::sigmoid(float activation) const
{
	return 1.f / (1.f + exp((-activation / 1.f)));
}

Move NeuralNetwork::calculateMove(bool inFov, bool bulletInFov, bool alreadyFired, float fov)
{
	Move move{0};

	std::vector<float> inputs = {static_cast<float>(inFov), static_cast<float>(bulletInFov),
								 static_cast<float>(alreadyFired), fov};
	std::vector<float> activations(m_firstLayer.m_numNeurons, 0.f);

	for(int i = 0; i < m_firstLayer.m_numNeurons; ++i)
	{
		auto neuronInputs = m_firstLayer.m_neurons[i].m_inputs;
		for(int j = 0; j < neuronInputs - 1; ++j)
		{
			activations[i] += inputs[j] * m_firstLayer.m_neurons[i].m_weights[j];
		}
		activations[i] += (-1.f) * m_firstLayer.m_neurons[i].m_weights[neuronInputs - 1]; //bias
	}

	inputs = activations;
	for(int i = 0; i < m_secondLayer.m_numNeurons; ++i)
	{
		auto neuronsInput = m_secondLayer.m_neurons[i].m_inputs;
		for(int j = 0; j < neuronsInput - 1; ++j)
		{
			activations[i] += inputs[j] * m_secondLayer.m_neurons[i].m_weights[j];
		}
		activations[i] += (-1.f) * m_secondLayer.m_neurons[i].m_weights[neuronsInput - 1];
		activations[i] = sigmoid(activations[i]);
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
