using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using System.Drawing;
using Newtonsoft.Json;
using System.IO;

namespace Vizualization
{
    class Program
    {
        public const string DataPath = @"B:\study_projects\Algorithms\Data\";
        public const string JsonDataFileName = DataPath + "data.json";
        public const string ImageFileName = DataPath + "tree{0}.png";

        public const int PictureMargin = 5;
        public const int NodeRadius = 10;
        public const int VerticalDistanceBetweenNodes = 40;
        public const int HorizontalDistanceBetweenNodes = 20;
        public static readonly Color BackgoundColor = Color.White;

        static void Main(string[] args)
        {
            var reader = new StreamReader(JsonDataFileName);
            string[] data = reader.ReadToEnd().Split(';');

            int index = 1;
            foreach (var jsonTree in data)
            {
                Tree<int> tree = null;
                try { tree = JsonConvert.DeserializeObject<Tree<int>>(jsonTree); }
                catch { break; }

                if (tree == null)
                    continue;

                var painter = new Painter<int>(tree);
                painter.DrawTree(string.Format(ImageFileName, index.ToString("D2")));
                index++;
            }
        }
    }
}
