using System;
using System.Collections.Generic;
using System.Linq;
using Layer = System.Collections.Generic.List<NeuralNetworks.Neuron>;

namespace NeuralNetworks
{
    class Neuron
    {
        private static double temp = 0;
        private static double GetRandom()
        {
            double d = Math.Pow(temp + 1.13, 3);         
            return temp = d - (int)d;
        }

        private static double _eta = 0.15; // Net learning rate.
        private static double _alpha = 0.5; // Momentum.


        private Connection[] _outputWeights;
        private int _myIndex;
        private double _gradient;
        private Func<double, double> ActivationFunction, ActivationFunctionDerivative;
        public double OutputVal { get; set; }

        public Neuron(int numOutputs, int myIndex, Func<double, double> activationFunction = null)
        {
            ActivationFunction = activationFunction ?? ActivationFuntions.ActivationFunction;
            ActivationFunctionDerivative = ActivationFuntions.ActivationFunctionDerivative;
            _outputWeights = new Connection[numOutputs];
            _myIndex = myIndex;

            for (int i = 0; i < numOutputs; i++)
                _outputWeights[i] = new Connection
                { 
                    Weight = /*0,*/GetRandom(),
                };
        }

        public void FeedForward(Layer prevLayer)
        {
            double sum = prevLayer.Sum(_ => _.OutputVal * _._outputWeights[_myIndex].Weight);
            OutputVal = ActivationFunction(sum);
        }

        public void CalcOutputGradients(double targetVals)
        {
            double delta = targetVals - OutputVal;
            _gradient = delta * ActivationFunctionDerivative(OutputVal);
        }

        public void CalcHiddenGradients(Layer nextLayer)
        {
            _gradient = SumDOW(nextLayer) * ActivationFunctionDerivative(OutputVal);
        }

        public void UpdateInputWeights(Layer prevLayer)
        {
            for (int i = 0; i < prevLayer.Count(); i++)
            {
                var neuron = prevLayer[i];
                double oldDeltaWeight = neuron._outputWeights[_myIndex].DeltaWeight;
                double newDeltaWeight = _eta * neuron.OutputVal * _gradient * _alpha * oldDeltaWeight;
                neuron._outputWeights[_myIndex].DeltaWeight = newDeltaWeight;
                neuron._outputWeights[_myIndex].Weight += newDeltaWeight;
            }
        }

        private double SumDOW(Layer nextLayer)
        {
            double sum = 0;
            for (int i = 0; i < nextLayer.Count() - 1; i++)
                sum += _outputWeights[i].Weight * nextLayer[i]._gradient;
            return sum;
        }

        private class Connection
        {
            public double Weight { get; set; }
            public double DeltaWeight { get; set; }
        }
    }
}
