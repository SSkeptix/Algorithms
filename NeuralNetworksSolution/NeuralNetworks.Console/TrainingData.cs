using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace NeuralNetworks.Console
{
    public class TrainingData
    {
        public double[] In { get; set; }
        public double[] Out { get; set; }


        #region Helpers
        public static TrainingData[] GenerateData(int inputValsCount, int outputValsCount, int dataCount)
        {
            var random = new Random(0);
            var result = new TrainingData[dataCount];

            for (int i = 0; i < dataCount; i++)
            {
                result[i] = new TrainingData
                {
                    In = new double[inputValsCount],
                    Out = new double[outputValsCount],
                };

                for (int j = 0; j < inputValsCount; j++)
                    result[i].In[j] = random.Next(2);
                for (int j = 0; j < outputValsCount; j++)
                    result[i].Out[j] = result[i].In.Any(_ => _ == 0) ? 1 : 0;
            }
            return result;
        }

        public static void WriteToFile(TrainingData[] data, string fileName)
        {
            using (var streamWriter = new StreamWriter(fileName))
            {
                streamWriter.Write(
                    Newtonsoft.Json.JsonConvert.SerializeObject(data)
                    );
                streamWriter.Close();
            }
        }

        public static TrainingData[] ReadFromFile(string fileName)
        {
            TrainingData[] data;
            using (var streamReader = new StreamReader(fileName))
            {
                string jsonData = streamReader.ReadToEnd();
                data = Newtonsoft.Json.JsonConvert.DeserializeObject<TrainingData[]>(jsonData);
            }
            return data;
        }
        #endregion
    }
}
