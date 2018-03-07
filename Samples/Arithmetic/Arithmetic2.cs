using Neo.SmartContract.Framework.Services.Neo;

namespace Neo.SmartContract
{
    public class Arithmetic2 : Framework.SmartContract
    {
        public static int Main(int m)
        {
            int c = m +2;
            return c;
        }
    }
}
