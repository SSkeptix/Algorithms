using System;
using System.Collections.Generic;
using System.Linq;
using Layer = System.Collections.Generic.List<NeuralNetworks.Neuron>;

namespace NeuralNetworks
{
    public class Net
    {
        private static double _recentAverageSmoothingFactor = 100.0; // Number of training samples to average over

        private double _error;
        public double RecentAverageError { get; private set; }
        private List<Layer> _layers;

        public Net(int[] topology)
        {
            _layers = new List<Layer>();

            for (int layerNum = 0; layerNum < topology.Length; ++layerNum)
            {
                var newLayer = new Layer();
                _layers.Add(newLayer);
                int numOutputs = (layerNum == topology.Count() - 1) 
                    ? 0 
                    : topology[layerNum + 1];

                for (int i = 0; i <= topology[layerNum]; i++)
                    newLayer.Add(new Neuron(numOutputs, i));

                newLayer.Last().OutputVal = 1;
            }
        }

        public void FeedForward(double[] inputVals)
        {
            for (int i = 0; i < inputVals.Count(); i++)
                _layers[0][i].OutputVal = inputVals[i];

            for (int layerNum = 1; layerNum < _layers.Count(); layerNum++)
            {
                var prevLayer = _layers[layerNum - 1];
                for (int i = 0; i < _layers[layerNum].Count() - 1; i++)
                    _layers[layerNum][i].FeedForward(prevLayer);
            }
        }

        public void BackProp(double[] targetVals)
        {
            var outputLayer = _layers.Last();
            _error = 0;

            for (int i = 0; i < outputLayer.Count() - 1; i++)
                _error += Math.Pow(targetVals[i] - outputLayer[i].OutputVal, 2);
            _error /= outputLayer.Count() - 1;
            _error = Math.Sqrt(_error);

            RecentAverageError = (RecentAverageError * _recentAverageSmoothingFactor + _error)
                / (_recentAverageSmoothingFactor + 1);

            for (int i = 0; i < outputLayer.Count() - 1; i++)
                outputLayer[i].CalcOutputGradients(targetVals[i]);

            for (int layerNum = _layers.Count() - 2; layerNum > 0; layerNum--)
            {
                var nextLayer = _layers[layerNum + 1];
                foreach (var neuron in _layers[layerNum])
                    neuron.CalcHiddenGradients(nextLayer);
            }

            for (int layerNum = _layers.Count() - 1; layerNum > 0; layerNum--)
            {
                var layer = _layers[layerNum];
                var prevLayer = _layers[layerNum - 1];
                for (int i = 0; i < layer.Count() - 1; i++)
                    layer[i].UpdateInputWeights(prevLayer);
            }
        }

        public IEnumerable<double> GetResults()
        {
            return _layers.Last()
                .Take(_layers.Last().Count() - 1)
                .Select(_ => _.OutputVal);
        }
    }
}
