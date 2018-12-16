using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net;
using System.Net.Sockets;



namespace CaiNetwork
{
    class CaiClient
    {
        //This is not very urgent
        Socket serverSocket;
        IPAddress serverIP;
        IPEndPoint serverIEP;
        int serverPort;
        Thread listenThread;

        public CaiClient()
        {
            serverSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        }
    }
}
