from boa.interop.Neo.Storage import Put, Get, Delete, GetContext

context = GetContext()

def Main():
    Put(context, "Hello", "World")
    Delete(context, "Hello")

