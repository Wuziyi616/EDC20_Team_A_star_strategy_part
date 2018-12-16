using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;

namespace CaiNetwork
{
    public class CaiUDP
    {
        UdpClient sendUdpClient;
        public IPEndPoint broadcastIpEndPoint;
        //IPAddress localIP;
        int localPort;
        public CaiUDP()
        {
            //localIP = util.getIPV4();
            localPort = util.GetFirstAvailablePort();
            broadcastIpEndPoint = new IPEndPoint(IPAddress.Broadcast, localPort);
        }
        public void sendByte(byte[] bytes)
        {
            if (bytes.Length == 0)
                return;
            sendUdpClient = new UdpClient();
            sendUdpClient.Send(bytes, bytes.Length, broadcastIpEndPoint);
            sendUdpClient.Close();
        }
        public string UDPInfo()
        {
            //Local is {0}:{1}.\n
            return string.Format("Broadcast is {0}:{1}", broadcastIpEndPoint.Address.MapToIPv4(), localPort);
        }
    }
}
