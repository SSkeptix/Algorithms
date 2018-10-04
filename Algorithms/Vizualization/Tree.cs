using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vizualization
{
    public class Tree<T>
    {
        public T Value { get; set; }
        public Tree<T> Left { get; set; }
        public Tree<T> Right { get; set; }
        public bool? IsRed { get; set; }

        public int GetHeight()
        {
            if (Left == null && Right == null)
                return 1;
            else
                return Math.Max(Left?.GetHeight() ?? 0, Right?.GetHeight() ?? 0) + 1;
        }
    }
}
