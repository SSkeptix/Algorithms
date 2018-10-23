using System;
using System.Linq;
using Layer = System.Collections.Generic.List<NeuralNetworks.Neuron>;

namespace NeuralNetworks
{
    class Neuron
    {
        private static double _eta = 0.15; // Net learning rate.
        private static double _alpha = 0.5; // Momentum.


        private Connection[] _outputWeights;
        private int _myIndex;
        private double _gradient;
        private ActivationFuntions ActiveFuns;
        public double OutputVal { get; set; }

        public Neuron(int numOutputs, int myIndex, ActivationFuntions activationFunctions = null)
        {
            ActiveFuns = activationFunctions ?? ActivationFuntions.Tanh;
            _outputWeights = new Connection[numOutputs];
            _myIndex = myIndex;

            var random = new Random(0);
            for (int i = 0; i < numOutputs; i++)
                _outputWeights[i] = new Connection
                { 
                    Weight = random.NextDouble(),
                };
        }

        public void FeedForward(Layer prevLayer)
        {
            double sum = prevLayer.Sum(_ => _.OutputVal * _._outputWeights[_myIndex].Weight);
            OutputVal = ActiveFuns.ActivationFunction(sum);
        }

        public void CalcOutputGradients(double targetVals)
        {
            double delta = targetVals - OutputVal;
            _gradient = delta * ActiveFuns.ActivationFunctionDerivative(OutputVal);
        }

        public void CalcHiddenGradients(Layer nextLayer)
        {
            double sum = 0;
            for (int i = 0; i < nextLayer.Count() - 1; i++)
                sum += _outputWeights[i].Weight * nextLayer[i]._gradient;

            _gradient = sum * ActiveFuns.ActivationFunctionDerivative(OutputVal);
        }

        public void UpdateInputWeights(Layer prevLayer)
        {
            foreach (var neuron in prevLayer)
            {
                double newDeltaWeight = _eta * neuron.OutputVal * _gradient 
                    + _alpha * neuron._outputWeights[_myIndex].DeltaWeight;
                neuron._outputWeights[_myIndex].DeltaWeight = newDeltaWeight;
                neuron._outputWeights[_myIndex].Weight += newDeltaWeight;
            }
        }

        private class Connection
        {
            public double Weight { get; set; }
            public double DeltaWeight { get; set; }
        }
    }
}
