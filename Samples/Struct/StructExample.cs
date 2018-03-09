namespace Neo.SmartContract
{
    public class StructExample : Framework.SmartContract
    {
        public static Point Add(Point a, Point b)
        {
            return new Point
            {
                X = a.X + b.X,
                Y = a.Y + b.Y
            };
        }

        public static void Main()
        {
            object[] array = new[]
            {
                (object)new Point
                {
                    X = 1,
                    Y = 2
                },
                (object)new Point
                {
                    X = 2,
                    Y = 1
                }
            };
            Add((Point)array[0], (Point)array[1]);
        }
    }
}
