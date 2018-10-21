using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetworks
{
    public static class ActivationFuntions
    {
        public static double ActivationFunction(double x) => Math.Tanh(x);
        public static double ActivationFunctionDerivative(double x) => 1.0 - x * x;
    }
}
