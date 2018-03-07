using Neo.SmartContract.Framework.Services.Neo;

namespace Neo.SmartContract
{
    public class HelloWorld : Framework.SmartContract
    {
        public static byte[] Main()
        {
            Storage.Put(Storage.CurrentContext, "Hello", "World");
            return Storage.Get(Storage.CurrentContext, "Hello");
        }
    }
}
