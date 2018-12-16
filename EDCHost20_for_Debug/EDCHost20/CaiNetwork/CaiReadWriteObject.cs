using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;

namespace CaiNetwork
{
    class CaiReadWriteObject
    {
        public TcpClient client;
        public NetworkStream netStream;
        public byte[] readBytes;
        public byte[] writeBytes;
        public CaiReadWriteObject(TcpClient client)
        {
            this.client = client;
            netStream = client.GetStream();
            readBytes = new byte[client.ReceiveBufferSize];
            writeBytes = new byte[client.SendBufferSize];
        }
        public void InitReadArray()
        {
            readBytes = new byte[client.ReceiveBufferSize];
        }
        public void InitWriteArray()
        {
            writeBytes = new byte[client.SendBufferSize];
        }
    }
}
