namespace NeuralNetworks.Console
{
    interface ILogger
    {
        void Log(string msg);
        void LogLine(string msg = null);
    }
}
