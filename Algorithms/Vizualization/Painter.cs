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
        public const float VerticalDistanceBetweenNodes = 20;
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
            _width = _tree.LeftMargin + _tree.RightMargin;
        }

        public void DrawTree(string fileName)
        {
            var image = new Bitmap((int)(_width + 2 * PictureMargin), (int)(_height + 2 * PictureMargin));
            using (var g = Graphics.FromImage(image))
            {
                DrawBackground(g);

                var nodePosition = new PointF
                {
                    X = _tree.LeftMargin - NodeDiameter / 2,
                    Y = 0,
                };
                DrawNode(g, _tree, nodePosition);
            }
            image.Save(fileName);
        }

        private void DrawNode(Graphics g, Tree<T> node, PointF nodePosition, PointF? parentPosition = null)
        {
            DrawNodeValue(g, node, nodePosition);
            if (parentPosition.HasValue)
                DrawConnection(g, parentPosition.Value, nodePosition);

            if (node.Left != null)
                DrawNode(g: g,
                    node: node.Left,
                    nodePosition: new PointF
                    {
                        X = nodePosition.X - node.Left.RightMargin,
                        Y = nodePosition.Y + NodeDiameter + VerticalDistanceBetweenNodes,
                    },
                    parentPosition: nodePosition);
            if (node.Right != null)
                DrawNode(g: g, 
                    node: node.Right,
                    nodePosition: new PointF
                    {
                        X = nodePosition.X + node.Right.LeftMargin,
                        Y = nodePosition.Y + NodeDiameter + VerticalDistanceBetweenNodes,
                    },
                    parentPosition: nodePosition);
        }
        
        private void DrawBackground(Graphics g)
        {
            g.FillRectangle(new SolidBrush(BackgoundColor), 0, 0, _width + 2 * PictureMargin, _height + 2 * PictureMargin);
        }

        private PointF DrawNodeValue(Graphics g, Tree<T> node, PointF position)
        {
            var realPosition = new PointF
            {
                X = PictureMargin + position.X,
                Y = PictureMargin + position.Y,
            };
            g.DrawEllipse(new Pen(NodeColor),
                realPosition.X, realPosition.Y,
                NodeDiameter, NodeDiameter);

            var nodeColor = node.IsRed == true ? Color.Red : Color.Black;
            g.DrawString(node.Value.ToString(), Font, new SolidBrush(nodeColor), 
                realPosition.X + 3, realPosition.Y + 7);

            return realPosition;
        }

        private void DrawConnection(Graphics g, PointF parent, PointF child)
        {
            var newParent = new PointF
            {
                X = parent.X + PictureMargin + NodeRadius,
                Y = parent.Y + PictureMargin + NodeRadius,
            };
            var newChild = new PointF
            {
                X = child.X + PictureMargin + NodeRadius,
                Y = child.Y + PictureMargin + NodeRadius,
            };

            float cof = (newParent.Y - newChild.Y) / (newParent.X - newChild.X);
            float x = NodeRadius / (float)Math.Sqrt(cof * cof + 1);
            float y = cof * x;

            newParent.X += (cof > 0 ? x : -x);
            newParent.Y += (cof > 0 ? y : -y);
            newChild.X -= (cof > 0 ? x : -x);
            newChild.Y -= (cof > 0 ? y : -y);

            g.DrawLine(new Pen(ConnectionColor), newParent, newChild);
        }

    }
}
