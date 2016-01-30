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
	std::vector<float> getWeights() const;
	void setWeights(const std::vector<float>& newWeights);
	int weightsCount() const;

private:
	float sigmoid(float x) const;

	static const int neuronsPerLayer = 5;
	static const int layer1InputsPerNeuron = 4;
	static const int layer2InputsPerNeuron = 5;
	static const int layersCount = 2;

	NeuronLayer m_layers[layersCount];
};



#endif /* NEURALNETWORK_H_ */
