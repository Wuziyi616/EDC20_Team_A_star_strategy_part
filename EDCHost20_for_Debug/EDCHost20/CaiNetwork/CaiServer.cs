using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net;
using System.Net.Sockets;
using System.IO;

namespace CaiNetwork
{
    public class CaiServer
    {
        IPAddress m_localIP;
        int m_localPort;
        int maxClientNum ;
        TcpListener m_listener;
        List<CaiReadWriteObject> clientList = new List<CaiReadWriteObject>();
        bool isExit;
        private EventWaitHandle allDone = new EventWaitHandle(false, EventResetMode.ManualReset);


        public CaiServer(IPAddress localIP, int localPort = -1)
        {
            m_localIP = localIP ;
            if (localPort >= 0 && util.PortIsAvailable(localPort))
                m_localPort = localPort;
            else
                m_localPort = util.GetFirstAvailablePort();
            maxClientNum = 10;

            PrepareConnect();
        }

        //准备连接，开启监听进程
        public void PrepareConnect()
        {
   
            Thread myThread = new Thread(new ThreadStart(AcceptConnect));
            myThread.Start();
        }

        public void AcceptConnect()
        {
            m_listener = new TcpListener(m_localIP, m_localPort);
            m_listener.Start();
            while (isExit == false)
            {
                try
                {
                    allDone.Reset();
                    AsyncCallback callback = new AsyncCallback(AcceptTcpClientCallback);
                    
                    m_listener.BeginAcceptTcpClient(callback, m_listener);
                    allDone.WaitOne();
                }
                catch (Exception err)
                {
                    //Parent.AddStatus(err.Message);
                    break;
                }
            }
        }

        private void AcceptTcpClientCallback(IAsyncResult ar)
        {
            try
            {
                allDone.Set();
                TcpListener myListener = (TcpListener)ar.AsyncState;
                TcpClient client = myListener.EndAcceptTcpClient(ar);
                //Parent.AddStatus("已接受客户连接" + client.Client.RemoteEndPoint);
                //Parent.ComboAddConnected(client.Client.RemoteEndPoint.ToString());
                CaiReadWriteObject readWriteObject = new CaiReadWriteObject(client);
                clientList.Add(readWriteObject);
                SendString(readWriteObject, "Connection Accepted!");
                readWriteObject.netStream.BeginRead(readWriteObject.readBytes, 0, readWriteObject.readBytes.Length, ReadCallback, readWriteObject);
            }
            catch (Exception err)
            {
                //Parent.AddStatus(err.Message);
                return;
            }
        }

        private void ReadCallback(IAsyncResult ar)
        {
            try
            {
                CaiReadWriteObject readWriteObject = (CaiReadWriteObject)ar.AsyncState;
                int count = readWriteObject.netStream.EndRead(ar);
                //Parent.AppendString(string.Format("[from{0}]{1}", readWriteObject.client.Client.RemoteEndPoint,
                    //Encoding.UTF8.GetString(readWriteObject.readBytes, 0, count)));
                if (isExit == false)
                {
                    readWriteObject.InitReadArray();
                    readWriteObject.netStream.BeginRead(readWriteObject.readBytes, 0,
                        readWriteObject.readBytes.Length, ReadCallback, readWriteObject);
                }
            }
            catch (Exception err)
            {
               // Parent.AddStatus(err.Message);
            }
        }

        public void GroupSend(string str)
        {
            foreach (CaiReadWriteObject client in clientList)
            {
                SendString(client, str);
            }
        }

        public void GroupSend(byte[] sendBytes)
        {
            foreach (CaiReadWriteObject client in clientList)
            {
                SendBytes(client, sendBytes);
            }
        }

        public int getPort()
        {
            return m_localPort;
        }
        public IPAddress getUsedIP()
        {
            return m_localIP;
        }
        private void SendString(CaiReadWriteObject readWriteObject, string str)
        {
            try
            {
                readWriteObject.writeBytes = Encoding.UTF8.GetBytes(str + "\r\n");
                readWriteObject.netStream.BeginWrite(readWriteObject.writeBytes, 0,
                    readWriteObject.writeBytes.Length, new AsyncCallback(SendCallback), readWriteObject);
                readWriteObject.netStream.Flush();
                //Parent.AddStatus(string.Format("向{0}发送：{1}", readWriteObject.client.Client.RemoteEndPoint, str));
            }
            catch (Exception err)
            {
               // Parent.AddStatus(err.Message);
            }
        }
        private void SendBytes(CaiReadWriteObject readWriteObject, byte[] sendBytes)
        {
            try
            {
                readWriteObject.writeBytes = sendBytes;
                readWriteObject.netStream.BeginWrite(readWriteObject.writeBytes, 0,
                    readWriteObject.writeBytes.Length, new AsyncCallback(SendCallback), readWriteObject);
                readWriteObject.netStream.Flush();
                //Parent.AddStatus(string.Format("向{0}发送：{1}", readWriteObject.client.Client.RemoteEndPoint, str));
            }
            catch (Exception err)
            {
                // Parent.AddStatus(err.Message);
            }
        }
        private void SendCallback(IAsyncResult ar)
        {
            CaiReadWriteObject readWriteObject = (CaiReadWriteObject)ar.AsyncState;
            try
            {
                readWriteObject.netStream.EndWrite(ar);
            }
            catch (Exception err)
            {
                //Parent.AddStatus(err.Message);
                //Parent.ComboRemoveConnected(readWriteObject.client.Client.RemoteEndPoint.ToString());
            }
        }

        public void StopConnect()
        {
            isExit = true;
            allDone.Set();
        }

        public void SendMessage(string SelectedClient, string message)
        {

            if (SelectedClient == null)
            {
                return;
            }
            else
            {
                CaiReadWriteObject obj = null;
                foreach (CaiReadWriteObject rwo in clientList)
                {
                    if (rwo.client.Client.RemoteEndPoint.ToString() == SelectedClient)
                    {
                        obj = rwo;
                    }
                }
                if (obj == null)
                {
                    return;
                }
                else
                {
                    SendString(obj, message);
                }
            }

        }





        public void DisconnectAll()
        {
            this.StopConnect();
        }
    }
}
