using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vizualization
{
    public class Tree<T>
    {
        public const float Margin = Painter<int>.HorizontalDistanceBetweenNodes / 2 + Painter<int>.NodeDiameter / 2;

        public T Value { get; set; }
        public Tree<T> Left { get; set; }
        public Tree<T> Right { get; set; }
        public bool? IsRed { get; set; }

        private float? _leftMargin, _rightMargin;

        public float LeftMargin
        {
            get
            {
                if (_leftMargin == null)
                    CalculateMargins();
                return _leftMargin.Value;
            }
        }
        public float RightMargin
        {
            get
            {
                if (_rightMargin == null)
                    CalculateMargins();
                return _rightMargin.Value;
            }
        }

        public void CalculateMargins()
        {
            _leftMargin = Math.Max(Margin,
                (Left?.LeftMargin ?? 0) + (Left?.RightMargin ?? 0));

            _rightMargin = Math.Max(Margin,
                (Right?.LeftMargin ?? 0) + (Right?.RightMargin ?? 0));
        }

        public int GetHeight()
        {
            if (Left == null && Right == null)
                return 1;
            else
                return Math.Max(Left?.GetHeight() ?? 0, Right?.GetHeight() ?? 0) + 1;
        }
    }
}
