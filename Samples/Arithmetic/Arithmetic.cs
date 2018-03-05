using Neo.SmartContract.Framework.Services.Neo;

namespace Neo.SmartContract
{
    public class Arithmetic : Framework.SmartContract
    {
        public static int Main(int a, int b, int c, int d)
        {
            return a + b - c * d;
        }
    }
}
