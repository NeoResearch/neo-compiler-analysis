using Neo.SmartContract.Framework.Services.Neo;

namespace Neo.SmartContract
{
    public class Arithmetic3 : Framework.SmartContract
    {
        public static int Main(int a, int b, int c, int d)
        {
            int a2 = a * 2;
            int b2 = b + 1;
            int c2 = c / 2;
            int d2 = d - 1;
            return a2 + b2 + c2 + d2;
        }
    }
}
