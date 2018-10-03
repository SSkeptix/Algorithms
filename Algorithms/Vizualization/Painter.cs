using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vizualization
{
    public class Painter<T>
    {
        public const float PictureMargin = 5;
        public const float NodeDiameter = 30;
        public const float NodeRadius = NodeDiameter / 2;
        public const float VerticalDistanceBetweenNodes = 50;
        public const float HorizontalDistanceBetweenNodes = 10;

        public static readonly Color BackgoundColor = Color.White;
        public static readonly Color NodeColor = Color.Black;
        public static readonly Color ConnectionColor = Color.Black;
        public static readonly Font Font = new Font(FontFamily.GenericSansSerif, 10);

        private readonly float _height, _width;
        private readonly Tree<T> _tree;

        public Painter(Tree<T> tree)
        {
            _tree = tree;

            // Calculate picture size.
            float heightNodeCount = tree.GetHeight();
            _height = NodeDiameter * heightNodeCount + VerticalDistanceBetweenNodes * (heightNodeCount - 1);
            float widthNodeCount = (float)Math.Pow(2, heightNodeCount - 1);
            _width = NodeDiameter * widthNodeCount + HorizontalDistanceBetweenNodes * (widthNodeCount - 1);
        }

        public void DrawTree(string fileName)
        {
            var image = new Bitmap((int)(_width + 2 * PictureMargin), (int)(_height + 2 * PictureMargin));
            using (var g = Graphics.FromImage(image))
            {
                DrawBackground(g);
                DrawNode(g, _tree, 0, 0);
            }
            image.Save(fileName);
        }

        private void DrawNode(Graphics g, Tree<T> node, int currentHeight, int currentWidth, PointF? parentPosition = null)
        {
            var position = CapculateNodePosition(currentHeight, currentWidth);
            if (parentPosition.HasValue)
                DrawConnection(g, parentPosition.Value, position);
            DrawNode(g, node.Value, position);

            if (node.Left != null)
                DrawNode(g, node.Left, currentHeight + 1, 2 * currentWidth, position);
            if (node.Right != null)
                DrawNode(g, node.Right, currentHeight + 1, 2 * currentWidth + 1, position);
        }

        // nodeHeight and nodeWidth are zero based.
        private PointF CapculateNodePosition(int nodeHeight, int nodeWidth)
        {
            int maxWidthCount = (int)Math.Pow(2, nodeHeight);
            float nodeWidthAvailable = _width / maxWidthCount;

            return new PointF
            {
                X = nodeWidthAvailable * nodeWidth + nodeWidthAvailable / 2 - NodeRadius,
                Y = nodeHeight * (NodeDiameter + VerticalDistanceBetweenNodes),
            };
        }

        private void DrawBackground(Graphics g)
        {
            g.FillRectangle(new SolidBrush(BackgoundColor), 0, 0, _width + 2 * PictureMargin, _height + 2 * PictureMargin);
        }

        private void DrawNode(Graphics g, T value, PointF position)
        {
            var realPosition = new PointF
            {
                X = PictureMargin + position.X,
                Y = PictureMargin + position.Y,
            };
            g.DrawEllipse(new Pen(NodeColor),
                realPosition.X, realPosition.Y,
                NodeDiameter, NodeDiameter);

            g.DrawString(value.ToString(), Font, new SolidBrush(NodeColor), 
                realPosition.X + 3, realPosition.Y + 7);
        }

        private void DrawConnection(Graphics g, PointF parent, PointF child)
        {
            parent.X += PictureMargin + NodeRadius;
            parent.Y += PictureMargin + NodeRadius;
            child.X += PictureMargin + NodeRadius;
            child.Y += PictureMargin + NodeRadius;

            float cof = (parent.Y - child.Y) / (parent.X - child.X);
            float x = NodeRadius / (float)Math.Sqrt(cof * cof + 1);
            float y = cof * x;

            parent.X += (cof > 0 ? x : -x);
            parent.Y += (cof > 0 ? y : -y);
            child.X += (cof < 0 ? x : -x);
            child.Y += (cof < 0 ? y : -y);

            g.DrawLine(new Pen(ConnectionColor), parent, child);
        }

    }
}
