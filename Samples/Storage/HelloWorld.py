from boa.interop.Neo.Storage import Put, GetContext

context = GetContext()

def Main():
    Put(context, "Hello", "World")

