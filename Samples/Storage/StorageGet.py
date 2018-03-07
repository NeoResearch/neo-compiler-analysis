from boa.interop.Neo.Storage import Put, Get, GetContext

context = GetContext()

def Main():
    Put(context, "Hello", "World")
    return Get(context, "Hello")

