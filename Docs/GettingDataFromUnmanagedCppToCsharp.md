### Getting data from the unmanaged c++ to managed c#

There is a memory barrier between the C# side and the C++ side and that means that there are considerations that I must take into account
when passing data from one side to another.

## The data structures

In the dll we have a struct:

```
struct ReceivedData {
    uint64_t timestamp;
    char data[256];
};
```

In the unity this is equivalent to:

```
[StructLayout(LayoutKind.Sequential, Pack = 4)]
public unsafe struct ReceivedData{
    public ulong timestamp;
    public fixed byte data[256];
}
```

I must use unsafe and must set the memory layout. C++ expects structs to be sequential and tightly packed.

## The function

In the dll the function expects a pointer to ReceivedData as a parameter. The struct will be filled by the function.

```
extern "C" __declspec(dllexport) bool __stdcall GetIncomingMessage(ReceivedData * outData)
{
    if (incomingDataQueue.size() > 0) {
        ReceivedData data = incomingDataQueue.front();
        incomingDataQueue.pop();
        outData->timestamp = data.timestamp;
        std::memcpy(outData->data, data.data, sizeof(char) * 256);
        return true;
    }
    else {
        return false;
    }
}
```
What matters is that the struct, that will be created in the Unity side of the memory barrier, receives the data. Primitive types
are assigned and memory buffers are copied so that the data will live on the C# side.

In c# the function is defined like this:
```
public static extern bool GetIncomingMessage(ref ReceivedData data);
```
Because c++ side is expecting a pointer I must pass C#'s ReceivedData as reference.

To actually get the data in the c# side i do:
```
unsafe {
            ReceivedData incomingData = new ReceivedData();
            GetIncomingMessage(ref incomingData);
            byte[] arr = new byte[256];
            Marshal.Copy((IntPtr)incomingData.data, arr, 0, 256);
            String message = System.Text.Encoding.UTF8.GetString(arr);
            Debug.Log($"Incoming: timestamp={incomingData.timestamp}, message={message}");
        }
```
I must define the struct's array data as a fixed array or else it'll crash with access violation once the c++ function returns control to the c# world. 
But unsafe c# fixed arrays have to be converted to safe arrays. That's what ```Marshal.Copy``` does. Then, with the data as safe byte array, I can use it to
create a string, the data is available to use in the c# side of the memory frontier.