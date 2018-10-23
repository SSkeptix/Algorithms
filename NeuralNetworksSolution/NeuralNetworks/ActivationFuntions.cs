using System;

namespace NeuralNetworks
{
    public class ActivationFuntions
    {
        public ActivationFunction ActivationFunction { get; set; }
        public ActivationFunctionDerivative ActivationFunctionDerivative { get; set; }

        public static ActivationFuntions Tanh
            => new ActivationFuntions
            {
                ActivationFunction = x => Math.Tanh(x),
                ActivationFunctionDerivative = x => 1.0 - x * x,
            };
    }

    public delegate double ActivationFunction(double arg);
    public delegate double ActivationFunctionDerivative(double arg);
}
