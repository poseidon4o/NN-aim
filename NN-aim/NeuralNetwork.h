#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include <vector>

struct Move
{
	bool advanceStraight;
	bool turnLeft;
	bool turnRight;
	bool shoot;
	float fovMult;
};

struct Neuron
{
	Neuron(int inputs);

	int m_inputs;
	std::vector<float> m_weights;
};

struct NeuronLayer
{
	NeuronLayer(int numNeurons, int inputsPerNeuron);

	int m_numNeurons;
	std::vector<Neuron> m_neurons;
};

class NeuralNetwork
{
public:
	NeuralNetwork();
	Move calculateMove(bool inFov, bool bulletInFov, bool alreadyFired, float fov);
private:
	float sigmoid(float x) const;

	static const int neuronsPerLayer = 5;

	NeuronLayer m_firstLayer;
	NeuronLayer m_secondLayer;
};



#endif /* NEURALNETWORK_H_ */
