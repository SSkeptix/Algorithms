using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetworks.Console
{
    interface ILogger
    {
        void Log(string msg);
        void LogLine(string msg = null);
    }
}
