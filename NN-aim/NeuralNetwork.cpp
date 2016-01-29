#include "NeuralNetwork.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Neuron::Neuron(int inputs): m_inputs(inputs)
{
	srand(time(NULL));

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

NeuralNetwork::NeuralNetwork(): m_firstLayer(neuronsPerLayer, 4),
		m_secondLayer(neuronsPerLayer, 5)
{

}

float NeuralNetwork::sigmoid(float x) const
{
	return 1.f / (1.f + exp(x));
}

Move NeuralNetwork::calculateMove(bool inFov, bool bulletInFov, bool alreadyFired, float fov)
{
	Move move{0};

	int res = rand();

	move.advanceStraight = res % 2;
	move.shoot = (res >> 1) % 2;
	move.turnLeft = (res >> 2) % 2;
	move.turnRight = (res >> 3) % 2;
	move.fovMult = 1.f;

	return move;
}
