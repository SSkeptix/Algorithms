﻿namespace NeuralNetworks.Console
{
    public class ConsoleLogger : ILogger
    {
        public void Log(string msg) => System.Console.Write(msg);
        public void LogLine(string msg = null) => Log(msg + '\n');
    }
}
