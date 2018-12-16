using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Net.NetworkInformation;
using System.Net;
namespace CaiNetwork
{
    public static class util
    {
        public static bool isConnected(Socket socket)
        {
            try
            {
                byte[] sendBytes = Encoding.UTF8.GetBytes("test");
                byte[] temp = new byte[1024];
                int nRead = socket.Receive(temp);
                if (nRead == 0)
                    return false;
                //int success = socket.Send(sendBytes, sendBytes.Length, SocketFlags.None);
            }
            catch
            {
                return false;
            }
            return true;
        }
        public static IPAddress getIPV4()
        {
            try
            {
                string HostName = Dns.GetHostName(); //得到主机名
                IPHostEntry IpEntry = Dns.GetHostEntry(HostName);
                for (int i = 0; i < IpEntry.AddressList.Length; i++)
                {
                    //从IP地址列表中筛选出IPv4类型的IP地址
                    //AddressFamily.InterNetwork表示此IP为IPv4,
                    //AddressFamily.InterNetworkV6表示此地址为IPv6类型
                    //if(IpEntry.AddressList[i].AddressFamily!=AddressFamily.InterNetworkV6)
                    //MessageBox.Show(string.Format("THE {0} ADDRESS {1} IS A {2} ", i, IpEntry.AddressList[i].MapToIPv4(),
                    //IpEntry.AddressList[i].AddressFamily));
                    if (IpEntry.AddressList[i].AddressFamily == AddressFamily.InterNetwork)
                    {
                        return IpEntry.AddressList[i];
                    }
                }
                return null;
            }
            catch (Exception ex)
            {
                //MessageBox.Show("获取本机IP出错:" + ex.Message);
                return null;
            }
        }

        public static List<int> PortIsUsed()
        {
            IPGlobalProperties iPGlobalProperties = IPGlobalProperties.GetIPGlobalProperties();

            IPEndPoint[] ipsTCP = iPGlobalProperties.GetActiveTcpListeners();
            IPEndPoint[] ipsUDP = iPGlobalProperties.GetActiveUdpListeners();

            TcpConnectionInformation[] tcpConnectionInformation = iPGlobalProperties.GetActiveTcpConnections();

            List<int> allPorts = new List<int>();
            foreach (IPEndPoint ep in ipsTCP)
                allPorts.Add(ep.Port);
            foreach (IPEndPoint ep in ipsUDP)
                allPorts.Add(ep.Port);
            foreach (TcpConnectionInformation conn in tcpConnectionInformation)
                allPorts.Add(conn.LocalEndPoint.Port);

            return allPorts;
        }
        public static bool PortIsAvailable(int port)
        {
            //bool isAvailable = true;
            List<int> portUsed = PortIsUsed();

            foreach (int p in portUsed)
            {
                if (p == port)
                {
                    return false;
                }
            }
            return true;
        }
        public static int GetFirstAvailablePort()
        {
            int MAX_PORT = 40000;
            int BEGIN_PORT = 20000;

            for (int i = BEGIN_PORT; i < MAX_PORT; i++)
            {
                if (PortIsAvailable(i))
                    return i;
            }
            return -1;
        }
    }
}
