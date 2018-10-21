using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Configuration.FileExtensions;
using Microsoft.Extensions.Configuration.Json;
using System.IO;
using System.Linq;

namespace NeuralNetworks.Console
{
    public static class Program
    {
        static int iii;
        static void Main()
        {
            ILogger logger = new ConsoleLogger();
            IConfiguration configuration = new ConfigurationBuilder()
                .SetBasePath(Directory.GetCurrentDirectory())
                .AddJsonFile("appsetting.json")
                .Build();

            // Get topology.
            int[] topology = configuration.GetSection("topology").Get<int[]>();

            // Read data.
            TrainingData[] data;
            string trainingDataFileName = Directory.GetCurrentDirectory() + "\\trainingData.json";
            if (File.Exists(trainingDataFileName))
                data = TrainingData.ReadFromFile(trainingDataFileName);
            else
            {
                data = TrainingData.GenerateData(topology.First(), topology.Last(), 2000);
                TrainingData.WriteToFile(data, trainingDataFileName);
            }

            // Train network.
            Net net = new Net(topology);
            for (int i = 0; i < data.Length; i++)
            {
                logger.LogLine($"Pass: {i + 1}");
                logger.LogLine($"Input: [{string.Join(", ", data[i].In.Select(_ => _.ToString("F3")))}]");
                logger.LogLine($"Targets: [{string.Join(", ", data[i].Out.Select(_ => _.ToString("F3")))}]");
                net.FeedForward(data[i].In);

                var resultVals = net.GetResults();
                logger.LogLine($"Outputs: [{string.Join(", ", resultVals.Select(_ => _.ToString("F3")))}]");

                net.BackProp(data[i].Out);
                logger.LogLine($"Net average error: {net.RecentAverageError.ToString("F9")}\n");

                if (i == 100)
                    iii = 0;
                if (i == 200)
                    iii = 0;
                if (i == 300)
                    iii = 0;
                if (i == 400)
                    iii = 0;
                if (i == 500)
                    iii = 0;
                if (i == 600)
                    iii = 0;
            }

            logger.LogLine("Done");
            System.Console.Read();
        }
    }
}
