using Neo.SmartContract.Framework.Services.Neo;

namespace Neo.SmartContract
{
    public class Arithmetic3 : Framework.SmartContract
    {
        public static int Main()
        {
            int a = 1;
            int b = 2;
            int c = 3;
            int e = 4;
            int d = a + b - c * e;
            return d;
        }
    }
}
