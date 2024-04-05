using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using UnityEngine;
using System.Text;
using System;
[StructLayout(LayoutKind.Sequential, Pack = 4)]
public unsafe struct ReceivedData{
    public ulong timestamp;
    public fixed byte data[256];
}
public class DllInterface : MonoBehaviour
{
    /// <summary>
    /// Must be the first thing called or else the library globals and statics may be in
    /// a inconsistent state. Example - while playing in unity editor the library will not
    /// be unloaded so statics and globals from one session will leak to the next.
    /// </summary>
    [DllImport("libmultiplayer")]
    public static extern void Initialize();

    /// <summary>
    /// Has to be called when the game is quitting because I need to do cleanup on the resources
    /// like, in windows, WSA.
    /// </summary>
    [DllImport("libmultiplayer")]
    public static extern void Shutdown();

    [DllImport("libmultiplayer")]
    public static extern int GetCounter();
    [DllImport("libmultiplayer")]
    public static extern void Increment();
    [DllImport("libmultiplayer", CharSet=CharSet.Ansi)]
    public static extern void CreateUDPServer(string ipAddress, ushort port);
    [DllImport("libmultiplayer")]
    public static extern uint GetMessageQueueSize();
    [DllImport("libmultiplayer")]
    public static extern bool GetIncomingMessage(ref ReceivedData data);

    bool isServer = false;
    void Awake()
    {
        Initialize();
        
    }
    public void LaunchServer()
    {
        CreateUDPServer("0.0.0.0", 9999);
        isServer = true;
    }
    void OnApplicationQuit(){
        Shutdown();
    }
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if(isServer == true){
        uint queueSize = GetMessageQueueSize();
            Debug.Log($"queue size={queueSize}");   
            if(queueSize > 0)unsafe {
                ReceivedData incomingData = new ReceivedData();
                GetIncomingMessage(ref incomingData);
                byte[] arr = new byte[256];
                Marshal.Copy((IntPtr)incomingData.data, arr, 0, 256);
                String message = System.Text.Encoding.UTF8.GetString(arr);
                Debug.Log($"Incoming: timestamp={incomingData.timestamp}, message={message}");
            } 
        }
    }
}
