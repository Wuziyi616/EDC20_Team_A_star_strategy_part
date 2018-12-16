using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.IO;

using OpenCvSharp;
using System.Threading;
using OpenCvSharp.Extensions;
using Point2i = OpenCvSharp.Point;
using Cuda = OpenCvSharp.Cuda;

using System.Net;

namespace EDC20HOST
{
    public partial class Tracker : Form
    {
        private long receive_count = 0;                  // 接收字节计数
        private StringBuilder sb = new StringBuilder("");  // 将接受的蓝牙信息转码用的字符串
        private List<char> receive_messages = new List<char>();  // 存储接收到的蓝牙信息，大括号匹配时开始decode
        char myID;
        private MyFlags flags = null;
        private VideoCapture capture = null;
        //private Thread threadCamera = null;
        private Point2f[] ptsShowCorners = null;
        private DateTime timeCamNow;
        private DateTime timeCamPrev;
        private TextBox[] tbsPoint = null;
        private CoordinateConverter cc;
        private Localiser localiser;
        private Point2i car1;
        private Point2i car2;
        private Point2i nextDestination;  // 本车下一个要去的点坐标
        private Point2i predCurPosition;  // 预测本车当前坐标
        private int yaw = 0;
        private int receive_num = 0;
        private double distance_to_next_destination = 0;
        private double angle_to_next_destination = 0;
        private Game game;
        private VideoWriter vw = null;

        private CaiNetwork.CaiServer server;
        private CaiNetwork.CaiUDP udp;

        public Dot CarALocation()
        {
            Dot D = new Dot();
            D.x = car1.X;
            D.y = car1.Y;
            return D;
        }
        public Dot CarBLocation()
        {
            Dot D = new Dot();
            D.x = car2.X;
            D.y = car2.Y;
            return D;
        }

        public Tracker()
        {
            InitializeComponent();

            InitialCaiServer();
            MessageBox.Show("TCP IP is "+ server.getUsedIP().ToString()+"  port is "+ server.getPort().ToString());
            udp = new CaiNetwork.CaiUDP();
            MessageBox.Show("UDP IP is " + udp.broadcastIpEndPoint.Address.ToString() + "  port is " + udp.broadcastIpEndPoint.Port.ToString());

            tbsPoint = new TextBox[] { tbPoint1, tbPoint2, tbPoint3, tbPoint4 };
            // Init
            flags = new MyFlags();
            flags.Init();
            flags.Start();
            ptsShowCorners = new Point2f[4];
            cc = new CoordinateConverter(flags);
            localiser = new Localiser();
            capture = new VideoCapture();
            // threadCamera = new Thread(CameraReading);
            /****************************************** 修改了此处，调用电脑自带摄像头 ******************************************/
            capture.Open(0);
            //capture.Open(1);
            timeCamNow = DateTime.Now;
            timeCamPrev = timeCamNow;

            car1 = new Point2i();
            car2 = new Point2i();

            buttonStart.Enabled = true;
            buttonPause.Enabled = false;
            button_reset.Enabled = false;

            Game.LoadMap();
            game = new Game();

            if (capture.IsOpened())
            {
                capture.FrameWidth = flags.cameraSize.Width;
                capture.FrameHeight = flags.cameraSize.Height;
                capture.ConvertRgb = true;
                timer100ms.Interval = 75;
                timer100ms.Start();
                //Cv2.NamedWindow("binary");
            }
            portCB.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
            myID = 'A';
        }

        private void Flush() 
        {
            CameraReading();
            lock (flags)
            {
                /*
                game.CarA.Pos.x = flags.posCarA.X;
                game.CarA.Pos.y = flags.posCarA.Y;
                game.CarB.Pos.x = flags.posCarB.X;
                game.CarB.Pos.y = flags.posCarB.Y;
                */
                flags.posCarA.X = game.CarA.Pos.x;
                flags.posCarA.Y = game.CarA.Pos.y;
                flags.posCarB.X = game.CarB.Pos.x;
                flags.posCarB.Y = game.CarB.Pos.y;
            }
            game.Update();
            lock(flags)
            {
                flags.currPassengerNum = game.CurrPassengerNumber;
                for(int i = 0;i!=Game.MaxPassenger;++i)
                {
                    flags.posPassengerStart[i].X = game.Passengers[i].StartDestPos.StartPos.x;
                    flags.posPassengerStart[i].Y = game.Passengers[i].StartDestPos.StartPos.y;
                    flags.posPassengerEnd[i].X = game.Passengers[i].StartDestPos.DestPos.x;
                    flags.posPassengerEnd[i].Y = game.Passengers[i].StartDestPos.DestPos.y;
                    flags.passengerState[i] = game.Passengers[i].Owner;
                    flags.gameState = game.state;
                }
            }
            byte[] Message = game.PackMessage();
            string a = BitConverter.ToString(Message, 0);
            // labelMsg.Text = a;
            labelRound.Text = Convert.ToString(game.Round);
            CaiZhuo_SendBytesViaNet(Message);
            ShowMessage(Message);
        }

        private void CameraReading()
        {
            bool control = false;
            lock(flags)
            {
                control = flags.running;
            }
            if(control)
            {
                //using (Mat videoFrame = new Mat())
                using (Mat videoFrame = new Mat("../../map/reverse_map.png"))
                using (Mat showFrame = new Mat())
                {
                    //if (capture.Read(videoFrame))
                    if (true)
                    {
                        lock (flags)
                        {
                            cc.PassengersFilter(flags);
                            localiser.Locate(videoFrame, flags);
                        }
                        /*
                        localiser.GetLocations(out car1, out car2);
                        lock (flags)
                        {
                            if (flags.calibrated)
                            {
                                Point2f[] car12 = { car1, car2 };
                                Point2f[] carAB = cc.CameraToLogic(car12);
                                flags.posCarA = carAB[0];
                                flags.posCarB = carAB[1];
                            }
                            else
                            {
                                flags.posCarA = car1;
                                flags.posCarB = car2;
                            }
                        }
                        */
                        timeCamNow = DateTime.Now;
                        TimeSpan timeProcess = timeCamNow - timeCamPrev;
                        timeCamPrev = timeCamNow;
                        Cv2.Resize(videoFrame, showFrame, flags.showSize, 0, 0, InterpolationFlags.Nearest);
                        BeginInvoke(new Action<TimeSpan>(UpdateProcessTime), timeProcess);
                        Mat show_img = new Mat();
                        Cv2.Flip(showFrame, show_img, 0);
                        //BeginInvoke(new Action<Image>(UpdateCameraPicture), BitmapConverter.ToBitmap(showFrame));
                        BeginInvoke(new Action<Image>(UpdateCameraPicture), BitmapConverter.ToBitmap(show_img));
                        //输出视频
                        if (flags.videomode == true)
                            //vw.Write(showFrame);
                            vw.Write(show_img);
                    }
                    lock (flags)
                    {
                        control = flags.running;
                    }
                }
            }
        }

        private void UpdateProcessTime(TimeSpan time)
        {
            string timeToDisp = time.TotalMilliseconds.ToString();
            tbInfo.Text = timeToDisp + "ms";
        }

        private void UpdateCameraPicture(Image img)
        {
            pbCamera.Image = img;
        }

        private void InitialCaiServer()
        {
            server = new CaiNetwork.CaiServer(CaiNetwork.util.getIPV4());//不指定端口，CaiServer会自行寻找空闲的端口；由util自动寻找本机的IPV4地址
            /*
             * 如果需要知道使用的IP和端口
             * 可以调用server.getUsedIP(),server.getPort()
             */
        }

        private void CaiZhuo_SendBytesViaNet(byte[] Message)
        {
            server.GroupSend(Message);
            udp.sendByte(Message);
        }

        private void Tracker_FormClosed(object sender, FormClosedEventArgs e)
        {
            server.DisconnectAll();
            lock (flags)
            {
                flags.End();
            }
            timer100ms.Stop();
            //threadCamera.Join();
            capture.Release();

            string arrStr = String.Format("{0} {1} {2} {3} {4} {5} {6} {7}", flags.configs.hue1Lower, flags.configs.hue1Upper, flags.configs.hue2Lower
            , flags.configs.hue2Upper, flags.configs.saturation1Lower, flags.configs.saturation2Lower
            , flags.configs.valueLower, flags.configs.areaLower);
            File.WriteAllText("data.txt", arrStr);
        }

        private void btnReset_Click(object sender, EventArgs e)
        {
            lock(flags)
            {
                flags.clickCount = 0;
                flags.calibrated = false;
            }

            foreach(TextBox tb in tbsPoint)
            {
                tb.Text = "";
            }
        }

        private void pbCamera_MouseClick(object sender, MouseEventArgs e)
        {
            int widthView = pbCamera.Width;
            int heightView = pbCamera.Height;

            int xMouse = e.X;
            int yMouse = e.Y;

            if (e.Button == MouseButtons.Left)
            {
                int idx = -1;
                lock (flags)
                {
                    if (flags.clickCount < 4) idx = flags.clickCount++;
                }

                if (idx == -1) return;

                if (xMouse >= 0 && xMouse < widthView && yMouse >= 0 && yMouse < heightView)
                {
                    ptsShowCorners[idx].X = xMouse;
                    ptsShowCorners[idx].Y = yMouse;

                    tbsPoint[idx].Text = String.Format("({0},{1})", xMouse, yMouse);
                    if (idx == 3) cc.UpdateCorners(ptsShowCorners, flags);
                }
            }
            else
            {
                Point2f[] res_my_car = cc.ShowToLogic(new Point2f[] { new Point2i { X = xMouse, Y = 480 - yMouse } });
                if (myID == 'A')
                {
                    game.CarA.Pos.x = Convert.ToInt16(res_my_car[0].X);
                    game.CarA.Pos.y = Convert.ToInt16(res_my_car[0].Y);
                }
                else
                {
                    game.CarB.Pos.x = Convert.ToInt16(res_my_car[0].X);
                    game.CarB.Pos.y = Convert.ToInt16(res_my_car[0].Y);
                }
            }
        }

        private void nudHue1L_ValueChanged(object sender, EventArgs e)
        {
            lock (flags) flags.configs.hue1Lower = (int)nudHue1L.Value;
        }

        private void nudHue1H_ValueChanged(object sender, EventArgs e)
        {
            lock (flags) flags.configs.hue1Upper = (int)nudHue1H.Value;
        }

        private void nudHue2L_ValueChanged(object sender, EventArgs e)
        {
            lock (flags) flags.configs.hue2Lower = (int)nudHue2L.Value;
        }

        private void nudHue2H_ValueChanged(object sender, EventArgs e)
        {
            lock (flags) flags.configs.hue2Upper = (int)nudHue2H.Value;
        }

        private void nudSat1L_ValueChanged(object sender, EventArgs e)
        {
            lock (flags) flags.configs.saturation1Lower = (int)nudSat1L.Value;
        }

        private void nudSat2L_ValueChanged(object sender, EventArgs e)
        {
            lock (flags) flags.configs.saturation2Lower = (int)nudSat2L.Value;
        }

        private void nudValueL_ValueChanged(object sender, EventArgs e)
        {
            lock (flags) flags.configs.valueLower = (int)nudValueL.Value;
        }

        private void nudAreaL_ValueChanged(object sender, EventArgs e)
        {
            lock (flags) flags.configs.areaLower = (int)nudAreaL.Value;
        }

        private void timer100ms_Tick(object sender, EventArgs e)
        {
            Flush();
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            game.Start();
            buttonPause.Enabled = true;
            buttonStart.Enabled = false;
            button_reset.Enabled = true;
        }

        private void buttonPause_Click(object sender, EventArgs e)
        {
            game.Pause();
            buttonPause.Enabled = false;
            buttonStart.Enabled = true;
            button_reset.Enabled = false;
        }

        private void ShowMessage(byte[] M) //通过Message显示信息到UI上
        {
            int x, y;
            x = ((M[2] & 0x80) << 1) + M[5];
            y = ((M[2] & 0x40) << 2) + M[6];
            labelALocation.Text = $"({x}, {y})";
            x = ((M[2] & 0x20) << 3) + M[7];
            y = ((M[2] & 0x10) << 4) + M[8];
            labelBLocation.Text = $"({x}, {y})";
            int tx, ty;
            x = ((M[2] & 0x08) << 5) + M[11];
            y = ((M[2] & 0x04) << 6) + M[12];
            tx = ((M[2] & 0x02) << 7) + M[13];
            ty = ((M[2] & 0x01) << 8) + M[14];
            label1L.Text = $"({x}, {y}) -> ({tx}, {ty})/{M[9] & 0x03}";
            x = ((M[3] & 0x80) << 1) + M[15];
            y = ((M[3] & 0x40) << 2) + M[16];
            tx = ((M[3] & 0x20) << 3) + M[17];
            ty = ((M[3] & 0x10) << 4) + M[18];
            label2L.Text = $"({x}, {y}) -> ({tx}, {ty})/{(M[10] & 0xC0) >> 6}";
            x = ((M[3] & 0x08) << 5) + M[19];
            y = ((M[3] & 0x04) << 6) + M[20];
            tx = ((M[3] & 0x02) << 7) + M[21];
            ty = ((M[3] & 0x01) << 8) + M[22];
            label3L.Text = $"({x}, {y}) -> ({tx}, {ty})/{(M[10] & 0x30) >> 4}";
            x = ((M[4] & 0x80) << 1) + M[23];
            y = ((M[4] & 0x40) << 2) + M[24];
            tx = ((M[4] & 0x20) << 3) + M[25];
            ty = ((M[4] & 0x10) << 4) + M[26];
            label4L.Text = $"({x}, {y}) -> ({tx}, {ty})/{(M[10] & 0x0C) >> 2}";
            x = ((M[4] & 0x08) << 5) + M[27];
            y = ((M[4] & 0x04) << 6) + M[28];
            tx = ((M[4] & 0x02) << 7) + M[29];
            ty = ((M[4] & 0x01) << 8) + M[30];
            label5L.Text = $"({x}, {y}) -> ({tx}, {ty})/{(M[10] & 0x03)}";
            labelValidP.Text = $"{M[9] >> 2}";
            labelRound.Text = $"{((M[0] & 0x3F) << 8) + M[1]}";
            labelState.Text = $"{((M[0] & 0xC0) >> 6)}";
            labelAScore.Text = $"{(M[33] << 8) + M[34]}/{M[31]}";
            labelBScore.Text = $"{(M[35] << 8) + M[36]}/{M[32]}";
        }

        private void Tracker_Load(object sender, EventArgs e)
        {
            if (File.Exists("data.txt"))
            {
                FileStream fsRead = new FileStream("data.txt", FileMode.Open);
                int fsLen = (int)fsRead.Length;
                byte[] heByte = new byte[fsLen];
                int r = fsRead.Read(heByte, 0, heByte.Length);
                string myStr = System.Text.Encoding.UTF8.GetString(heByte);
                string[] str = myStr.Split(' ');
                nudHue1L.Value = (flags.configs.hue1Lower = Convert.ToInt32(str[0]));
                nudHue1H.Value = (flags.configs.hue1Upper = Convert.ToInt32(str[1]));
                nudHue2L.Value = (flags.configs.hue2Lower = Convert.ToInt32(str[2]));
                nudHue2H.Value = (flags.configs.hue2Upper = Convert.ToInt32(str[3]));
                nudSat1L.Value = (flags.configs.saturation1Lower = Convert.ToInt32(str[4]));
                nudSat2L.Value = (flags.configs.saturation2Lower = Convert.ToInt32(str[5]));
                nudValueL.Value = (flags.configs.valueLower = Convert.ToInt32(str[6]));
                nudAreaL.Value = (flags.configs.areaLower = Convert.ToInt32(str[7]));
                fsRead.Close();
            }

        }

        private void button_restart_Click(object sender, EventArgs e)
        {
            lock (game) { game = new Game(); }
            buttonStart.Enabled = true;
            buttonPause.Enabled = false;
            button_reset.Enabled = false;
        }

        private void buttonChangeScore_Click(object sender, EventArgs e)
        {
            int AScore = (int)numericUpDownScoreA.Value;
            int BScore = (int)numericUpDownScoreB.Value;
            numericUpDownScoreA.Value = 0;
            numericUpDownScoreB.Value = 0;
            lock(game)
            {
                game.CarA.Score += AScore;
                game.CarB.Score += BScore;
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            timer100ms.Interval = (int)numericUpDownTime.Value;
        }

        private void button_minus10_Click(object sender, EventArgs e)
        {
            lock (game)
            {
                if (radioButton_CarA.Checked)
                {
                    game.CarA.Score -= 10;
                }
                if (radioButton_CarB.Checked)
                    game.CarB.Score -= 10;
            }  
        }

        private void button_minus20_Click(object sender, EventArgs e)
        {
            lock (game)
            {
                if (radioButton_CarA.Checked)
                    game.CarA.Score -= 20;
                if (radioButton_CarB.Checked)
                    game.CarB.Score -= 20;
            }
        }

        private void button_minus80_Click(object sender, EventArgs e)
        {
            lock (game)
            {
                if (radioButton_CarA.Checked)
                    game.CarA.Score -= 80;
                if (radioButton_CarB.Checked)
                    game.CarB.Score -= 80;
            }
        }

        private void button_plus50_Click(object sender, EventArgs e)
        {
            lock (game)
            {
                if (radioButton_CarA.Checked)
                    if (game.CarA.People != null)
                        game.CarA.Score += ((game.CarA.People.Score() > 50) ? game.CarA.People.Score() : 50);
                    else
                        game.CarA.Score += 50;
                if (radioButton_CarB.Checked)
                    if (game.CarB.People != null)
                        game.CarB.Score += ((game.CarB.People.Score() > 50) ? game.CarB.People.Score() : 50);
                    else
                        game.CarB.Score += 50;
            }
        }

        private void button_plus100_Click(object sender, EventArgs e)
        {
            if (radioButton_CarA.Checked)
                if (game.CarA.People != null)
                    game.CarA.Score += ((game.CarA.People.Score() > 100) ? game.CarA.People.Score() : 100);
                else
                    game.CarA.Score += 100;
            if (radioButton_CarB.Checked)
                if (game.CarB.People != null)
                    game.CarB.Score += ((game.CarB.People.Score() > 100) ? game.CarB.People.Score() : 100);
                else
                    game.CarB.Score += 100;
        }

        private void button_plus150_Click(object sender, EventArgs e)
        {
            if (radioButton_CarA.Checked)
                if (game.CarA.People != null)
                    game.CarA.Score += ((game.CarA.People.Score() > 150) ? game.CarA.People.Score() : 150);
                else
                    game.CarA.Score += 150;
            if (radioButton_CarB.Checked)
                if (game.CarB.People != null)
                    game.CarB.Score += ((game.CarB.People.Score() > 150) ? game.CarB.People.Score() : 150);
                else
                    game.CarB.Score += 150;
        }

        private void button_reset_Click(object sender, EventArgs e)
        {
            game.Pause();
            game.Round -= 50; //复位5s
            buttonPause.Enabled = false;
            buttonStart.Enabled = true;
            button_reset.Enabled = false;
        }

        private void button_video_Click(object sender, EventArgs e)
        {
            lock (flags)
            {
                if (flags.videomode == false)
                {
                    vw = new VideoWriter("../../video/" + DateTime.Now.ToString("MMdd_HH_mm_ss") + ".avi",
                        FourCC.XVID, 10.0, flags.showSize);
                    flags.videomode = true;
                    ((Button)sender).Text = "停止录像";
                }
                else
                {
                    vw.Release();
                    vw = null;
                    flags.videomode = false;
                    ((Button)sender).Text = "开始录像";
                }
            }
        }
        private void checkBox_DebugMode_CheckedChanged(object sender, EventArgs e)
        {
            game.DebugMode = checkBox_DebugMode.Checked;
        }

        private void bluetoothBtn_Click(object sender, EventArgs e)
        {
            try
            {
                // 将可能产生异常的代码放置在try块中
                // 根据当前串口属性来判断是否打开
                if (serialPort1.IsOpen)
                {
                    // 串口已经处于打开状态
                    serialPort1.Close();  // 关闭串口
                    bluetoothBtn.Text = "打开串口";
                    portCB.Enabled = true;
                    receiveTB.Text = "";  // 清空接收区
                }
                else
                {
                    // 串口已经处于关闭状态，则设置好串口属性后打开
                    serialPort1.PortName = portCB.Text;
                    serialPort1.BaudRate = 9600;
                    serialPort1.DataBits = 8;

                    serialPort1.Parity = System.IO.Ports.Parity.None;
                    serialPort1.StopBits = System.IO.Ports.StopBits.One;

                    serialPort1.Open();  // 打开串口
                    bluetoothBtn.Text = "关闭串口";
                }
            }
            catch (Exception ex)
            {
                // 捕获可能发生的异常并进行处理
                // 捕获到异常，创建一个新的对象，之前的不可以再用
                serialPort1 = new System.IO.Ports.SerialPort();
                // 刷新COM口选项
                portCB.Items.Clear();
                portCB.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());
                bluetoothBtn.Text = "打开串口";
                MessageBox.Show(ex.Message);
                portCB.Enabled = true;
                receiveTB.Text = "";  // 清空接收区
            }
        }

        private void SerialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            int num = serialPort1.BytesToRead;     // 获取接收缓冲区中的字节数
            byte[] received_buf = new byte[num];   // 声明一个大小为num的字节数据用于存放读出的byte型数据
            receive_count += num;                  // 接收字节计数变量增加nun
            serialPort1.Read(received_buf, 0, num);  // 读取接收缓冲区中num个字节到byte数组中
            sb.Clear();
            sb.Append(Encoding.ASCII.GetString(received_buf));  // 现在sb存储了收到的蓝牙信息

            try
            {
                Invoke((EventHandler)(delegate
                {
                    receiveTB.AppendText(sb.ToString());
                    bluetoothLb.Text = "Rx:" + sb.Length.ToString() + "Bytes" + "Tx:    Bytes";
                }
                )
                );
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            for (int i = 0; i < sb.Length; i++)
            {
                receive_messages.Add(sb[i]);
            }
            if (receive_messages[0] != '{')
            {
                receive_messages.Clear();
                return;
            }
            sb.Clear();
            int flag = 0;  // 记录匹配到的'}'的位置
            for (; flag < receive_messages.Count(); flag++)
            {
                if (receive_messages[flag] == '$')
                {
                    for (int i = 0; i < flag; i++)
                    {
                        sb.Append(receive_messages[i]);
                    }
                    decode();
                    sb.Clear();
                    receive_messages.Clear();
                    return;
                }
            }
        }

        //printf("{A%d:%d:%d:%d:%d:%d}$\n", (int) now_x, (int) now_y, (int) go_x, (int) go_y, (int) transformYaw(), (int) all_receive_num);
        private void decode()  // 将接收到的蓝牙消息解码,此时已保证sb必为标准格式输入"{A%d:%d:%d:%d:%d:%d}"
        {
            int now_x = 0, now_y = 0, go_x = 0, go_y = 0, transformYaw = 0, all_receive_num = 0;
            string info = sb.ToString();
            int i = 0, j = 2;

            i = info.IndexOf(':', 0);
            for (; j < i; j++)
            {
                now_x = 10 * now_x + info[j] - '0';
            }

            i = info.IndexOf(':', ++i);
            for (++j; j < i; j++)
            {
                now_y = 10 * now_y + info[j] - '0';
            }

            i = info.IndexOf(':', ++i);
            for (++j; j < i; j++)
            {
                go_x = 10 * go_x + info[j] - '0';
            }

            i = info.IndexOf(':', ++i);
            for (++j; j < i; j++)
            {
                go_y = 10 * go_y + info[j] - '0';
            }

            i = info.IndexOf(':', ++i);
            if (info[++j] == '-')
            {
                for (++j; j < i; j++)
                {
                    transformYaw = 10 * transformYaw + info[j] - '0';
                }
                transformYaw *= -1;
            }
            else
            {
                for (; j < i; j++)
                {
                    transformYaw = 10 * transformYaw + info[j] - '0';
                }
            }

            i = info.IndexOf('}');
            for (++j; j <= i; j++)
            {
                all_receive_num = 10 * all_receive_num + info[j] - '0';
            }

            nextDestination.X = go_x;
            nextDestination.Y = go_y;
            predCurPosition.X = now_x;
            predCurPosition.Y = now_y;
            yaw = transformYaw;
            receive_num = all_receive_num;

            distance_to_next_destination = Point2i.Distance(nextDestination, predCurPosition);
            double pred_angle_to_go = Math.Acos((go_x - now_x) / (distance_to_next_destination + 1e-6));
            pred_angle_to_go = pred_angle_to_go / 3.1416 * 180;
            if (go_y > now_y)
            {
                angle_to_next_destination = pred_angle_to_go - yaw;
            }
            else
            {
                angle_to_next_destination = -yaw - pred_angle_to_go;
            }
            distanceLb.Text = Convert.ToString(distance_to_next_destination);
            goLb.Text = "go_position: (" + Convert.ToString(go_x) + ", " + Convert.ToString(go_y) + ")";
            nowLb.Text = "now_position: (" + Convert.ToString(now_x) + ", " + Convert.ToString(now_y) + ")";
            yawLb.Text = "transformYaw: " + Convert.ToString(transformYaw);
            deltayawLb.Text = "delta angle: " + Convert.ToString(angle_to_next_destination);

            Point2f[] res_destination = cc.LogicToCamera(new Point2f[] { nextDestination, predCurPosition });
            flags.nextDestination = res_destination[0];
            flags.predCurPosition = res_destination[1];
        }

        private void clearreceiveBtn_Click(object sender, EventArgs e)
        {
            receiveTB.Text = "";
        }

        private void round1Btn_Click(object sender, EventArgs e)
        {
            game.Round = 1;
            game.state = GameState.Normal;
        }

        private void setmycarBtn_Click(object sender, EventArgs e)
        {
            int x = Convert.ToInt32(CarXTB.Text);
            int y = Convert.ToInt32(CarYTB.Text);
            lock (flags)
            {
                game.CarA.Pos.x = x;
                game.CarA.Pos.y = y;
            }
        }

        private void setBcarposBtn_Click(object sender, EventArgs e)
        {
            int x = Convert.ToInt32(CarXTB.Text);
            int y = Convert.ToInt32(CarYTB.Text);
            lock (flags)
            {
                game.CarB.Pos.x = x;
                game.CarB.Pos.y = y;
            }
        }

        private void setmyidBtn_Click(object sender, EventArgs e)
        {
            myID = myIDTB.Text[0];
        }

        private void updatePassengerBtn_Click(object sender, EventArgs e)
        {
            int i = Convert.ToInt32(nextPassengerTB.Text);
            int start_x = Convert.ToInt32(nextPassengerStartXTB.Text);
            int start_y = Convert.ToInt32(nextPassengerStartYTB.Text);
            int end_x = Convert.ToInt32(nextPassengerEndXTB.Text);
            int end_y = Convert.ToInt32(nextPassengerEndYTB.Text);
            Dot start_pos = new Dot { x = start_x, y = start_y };
            Dot end_pos = new Dot { x = end_x, y = end_y };
            StartDestDot start_dest_dot = new StartDestDot { StartPos = start_pos, DestPos = end_pos };

            lock (game)  // 更新game里的ground_truth
            {
                game.Passengers[i - 1] = new Passenger(start_dest_dot, (i == 5), i);
            }
            lock (flags)  // 更新flags里的信息
            {
                i--;
                flags.posPassengerStart[i].X = game.Passengers[i].StartDestPos.StartPos.x;
                flags.posPassengerStart[i].Y = game.Passengers[i].StartDestPos.StartPos.y;
                flags.posPassengerEnd[i].X = game.Passengers[i].StartDestPos.DestPos.x;
                flags.posPassengerEnd[i].Y = game.Passengers[i].StartDestPos.DestPos.y;
                flags.passengerState[i] = game.Passengers[i].Owner;
            }
            nextPassengerTB.Text = "";
            nextPassengerStartXTB.Text = "";
            nextPassengerStartYTB.Text = "";
            nextPassengerEndXTB.Text = "";
            nextPassengerEndYTB.Text = "";
        }
    }

    public class MyFlags
    {
        public bool running;
        public bool calibrated;
        public bool videomode;
        public int clickCount;
        public struct LocConfigs
        {
            public int hue1Lower;
            public int hue1Upper;
            public int hue2Lower;
            public int hue2Upper;
            public int saturation1Lower;
            public int saturation2Lower;
            public int valueLower;
            public int areaLower;
        }
        public LocConfigs configs;
        public OpenCvSharp.Size showSize;
        public OpenCvSharp.Size cameraSize;
        public OpenCvSharp.Size logicSize;
        public Point2i posCarA;
        public Point2i posCarB;
        public Point2i nextDestination;  // 本车下一个要去点坐标
        public Point2i predCurPosition;  // 本车预测当前所在坐标

        public Point2i[] posPassengerStart;
        public Point2i[] posPassengerEnd;
        public Camp[] passengerState;
        public int currPassengerNum;
        public GameState gameState;

        public void Init()
        {
            running = false;
            calibrated = false;
            videomode = false;
            configs = new LocConfigs();
            posCarA = new Point2i();
            posCarB = new Point2i();
            showSize = new OpenCvSharp.Size(640, 480);
            //cameraSize = new OpenCvSharp.Size(1280, 960);
            cameraSize = new OpenCvSharp.Size(372, 372);
            logicSize = new OpenCvSharp.Size(270, 270);
            clickCount = 0;
            posPassengerStart = new Point2i[Game.MaxPassenger];
            posPassengerEnd = new Point2i[Game.MaxPassenger];
            passengerState = new Camp[Game.MaxPassenger];
        }

        public void Start()
        {
            running = true;
        }

        public void End()
        {
            running = false;
        }
    }

    public class CoordinateConverter : IDisposable
    {
        private Mat cam2logic;
        private Mat logic2cam;
        private Mat show2cam;
        private Mat cam2show;
        private Mat show2logic;
        private Mat logic2show;
        private Point2f[] logicCorners;
        private Point2f[] camCorners;
        private Point2f[] showCorners;

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                ((IDisposable)(cam2logic)).Dispose();
                ((IDisposable)(logic2cam)).Dispose();
                ((IDisposable)(show2cam)).Dispose();
                ((IDisposable)(cam2show)).Dispose();
                ((IDisposable)(show2logic)).Dispose();
                ((IDisposable)(logic2show)).Dispose();
            }

        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        public CoordinateConverter(MyFlags myFlags)
        {
            camCorners = new Point2f[4];
            logicCorners = new Point2f[4];
            showCorners = new Point2f[4];
            cam2logic = new Mat();
            show2cam = new Mat();
            logic2show = new Mat();
            show2logic = new Mat();
            cam2show = new Mat();
            logic2cam = new Mat();

            logicCorners[0].X = 0;
            logicCorners[0].Y = 0;
            logicCorners[1].X = myFlags.logicSize.Width;
            logicCorners[1].Y = 0;
            logicCorners[2].X = 0;
            logicCorners[2].Y = myFlags.logicSize.Height;
            logicCorners[3].X = myFlags.logicSize.Width;
            logicCorners[3].Y = myFlags.logicSize.Height;

            showCorners[0].X = 0;
            showCorners[0].Y = 0;
            showCorners[1].X = myFlags.showSize.Width;
            showCorners[1].Y = 0;
            showCorners[2].X = 0;
            showCorners[2].Y = myFlags.showSize.Height;
            showCorners[3].X = myFlags.showSize.Width;
            showCorners[3].Y = myFlags.showSize.Height;

            camCorners[0].X = 0;
            camCorners[0].Y = 0;
            camCorners[1].X = myFlags.cameraSize.Width;
            camCorners[1].Y = 0;
            camCorners[2].X = 0;
            camCorners[2].Y = myFlags.cameraSize.Height;
            camCorners[3].X = myFlags.cameraSize.Width;
            camCorners[3].Y = myFlags.cameraSize.Height;

            show2cam = Cv2.GetPerspectiveTransform(showCorners, camCorners);
            cam2show = Cv2.GetPerspectiveTransform(camCorners, showCorners);
        }

        public void UpdateCorners(Point2f[] corners, MyFlags myFlags)
        {
            if (corners == null) return;
            if (corners.Length != 4) return;
            else showCorners = corners;

            logic2show = Cv2.GetPerspectiveTransform(logicCorners, showCorners);
            show2logic = Cv2.GetPerspectiveTransform(showCorners, logicCorners);
            camCorners = Cv2.PerspectiveTransform(showCorners, show2cam);
            cam2logic = Cv2.GetPerspectiveTransform(camCorners, logicCorners);
            logic2cam = Cv2.GetPerspectiveTransform(logicCorners, camCorners);
            myFlags.calibrated = true;
        }

        public Point2f[] ShowToCamera(Point2f[] ptsShow)
        {
            return Cv2.PerspectiveTransform(ptsShow, show2cam);
        }

        public Point2f[] CameraToShow(Point2f[] ptsCamera)
        {
            return Cv2.PerspectiveTransform(ptsCamera, cam2show);
        }

        public Point2f[] CameraToLogic(Point2f[] ptsCamera)
        {
            return Cv2.PerspectiveTransform(ptsCamera, cam2logic);
        }

        public Point2f[] LogicToCamera(Point2f[] ptsLogic)
        {
            return Cv2.PerspectiveTransform(ptsLogic, logic2cam);
        }

        public Point2f[] LogicToShow(Point2f[] ptsLogic)
        {
            return Cv2.PerspectiveTransform(ptsLogic, logic2show);
        }

        public Point2f[] ShowToLogic(Point2f[] ptsShow)
        {
            return Cv2.PerspectiveTransform(ptsShow, show2logic);
        }

        public void PassengersFilter(MyFlags flags)
        {
            if (!flags.calibrated) return;
            Point2f[] res_car = LogicToCamera(new Point2f[] { flags.posCarA, flags.posCarB });
            flags.posCarA = res_car[0];
            flags.posCarB = res_car[1];
            for (int i = 0; i < flags.currPassengerNum; ++i)
            {
                Point2f[] res = LogicToCamera(new Point2f[] { flags.posPassengerStart[i], flags.posPassengerEnd[i] });
                flags.posPassengerStart[i] = res[0];
                flags.posPassengerEnd[i] = res[1];
            }
        }
    }

    public class Localiser
    {
        private List<Point2i> centres1;
        private List<Point2i> centres2;

        public Localiser()
        {
            centres1 = new List<Point2i>();
            centres2 = new List<Point2i>();
            
        }

        public void GetLocations(out Point2i pt1, out Point2i pt2)
        {
            if (centres1.Count != 0)
            {
                pt1 = centres1[0];
                centres1.Clear();
            }
            else pt1 = new Point2i(-1,-1);
            if (centres2.Count != 0)
            {
                pt2 = centres2[0];
                centres2.Clear();
            }
            else pt2 = new Point2i(-1, -1);
        }

        public void Locate(Mat mat, MyFlags localiseFlags)
        {
            if (mat == null || mat.Empty()) return;
            if (localiseFlags == null) return;
            {
                /*
                using (Mat hsv = new Mat())
                using (Mat car1 = new Mat())
                using (Mat car2 = new Mat())
                //using (Mat merged = new Mat())
                using (Mat black = new Mat(mat.Size(), MatType.CV_8UC1))
                {
                    Cv2.CvtColor(mat, hsv, ColorConversionCodes.RGB2HSV);
                    MyFlags.LocConfigs configs = localiseFlags.configs;
                    Cv2.InRange(hsv,
                        new Scalar(configs.hue1Lower, configs.saturation1Lower, configs.valueLower),
                        new Scalar(configs.hue1Upper, 255, 255),
                        car1);
                    Cv2.InRange(hsv,
                        new Scalar(configs.hue2Lower, configs.saturation2Lower, configs.valueLower),
                        new Scalar(configs.hue2Upper, 255, 255),
                        car2);

                    Point2i[][] contours1, contours2;

                    contours1 = Cv2.FindContoursAsArray(car1, RetrievalModes.External, ContourApproximationModes.ApproxSimple);
                    contours2 = Cv2.FindContoursAsArray(car2, RetrievalModes.External, ContourApproximationModes.ApproxSimple);

                    foreach (Point2i[] c1 in contours1)
                    {
                        Point2i centre = new Point2i();
                        Moments moments = Cv2.Moments(c1);
                        centre.X = (int)(moments.M10 / moments.M00);
                        centre.Y = (int)(moments.M01 / moments.M00);
                        double area = moments.M00;
                        if (area < configs.areaLower) continue;
                        centres1.Add(centre);
                    }
                    foreach (Point2i[] c2 in contours2)
                    {
                        Point2i centre = new Point2f();
                        Moments moments = Cv2.Moments(c2);
                        centre.X = (int)(moments.M10 / moments.M00);
                        centre.Y = (int)(moments.M01 / moments.M00);
                        double area = moments.M00;
                        if (area < configs.areaLower) continue;
                        centres2.Add(centre);
                    }

                    foreach (Point2i c1 in centres1) Cv2.Circle(mat, c1, 10, new Scalar(0x1b, 0xff, 0xa7), -1);
                    foreach (Point2i c2 in centres2) Cv2.Circle(mat, c2, 10, new Scalar(0x00, 0x98, 0xff), -1);
                    */
                Cv2.Circle(mat, localiseFlags.posCarA, 4, new Scalar(0x1b, 0xff, 0xa7), -1);  // 画车
                Cv2.Circle(mat, localiseFlags.posCarB, 4, new Scalar(0x00, 0x98, 0xff), -1);
                int x_destination = localiseFlags.nextDestination.X - 4;
                int y_destination = localiseFlags.nextDestination.Y - 4;
                Rect rect_destination = new Rect(x_destination, y_destination, 8, 8);
                Cv2.Rectangle(mat, rect_destination, new Scalar(0x58, 0xee, 0xff), -1);  // next target point
                int x_predCurPosition = localiseFlags.predCurPosition.X - 4;
                int y_predCurPosition = localiseFlags.predCurPosition.Y - 4;
                Rect rect_pred = new Rect(x_predCurPosition, y_predCurPosition, 8, 8);
                Cv2.Rectangle(mat, rect_pred, new Scalar(0x58, 0xee, 0xff), -1);  // pred current point
                Cv2.Line(mat, localiseFlags.predCurPosition, localiseFlags.nextDestination, new Scalar(100, 105, 200), 2);
                if (localiseFlags.gameState != GameState.Unstart)
                {
                    for (int i = 0; i < localiseFlags.currPassengerNum; ++i)
                    {
                        int x1 = localiseFlags.posPassengerEnd[i].X;
                        int y1 = localiseFlags.posPassengerEnd[i].Y;
                        int x2 = localiseFlags.posPassengerStart[i].X;
                        int y2 = localiseFlags.posPassengerStart[i].Y;
                        int x10 = x1 - 4;
                        int y10 = y1 - 4;
                        int x20 = x2 - 4;
                        int y20 = y2 - 4;
                        Rect rectDest = new Rect(x10, y10, 8, 8);
                        Rect rectSrc = new Rect(x20, y20, 8, 8);
                        switch (localiseFlags.passengerState[i])
                        {
                            case Camp.CampA:
                                Cv2.Rectangle(mat, rectDest, new Scalar(0x1b, 0xff, 0xa7), -1);
                                Cv2.Line(mat, localiseFlags.posCarA, localiseFlags.posPassengerEnd[i], new Scalar(0x1b, 0xff, 0xa7), 1);
                                break;
                            case Camp.CampB:
                                Cv2.Rectangle(mat, rectDest, new Scalar(0x00, 0x98, 0xff), -1);
                                Cv2.Line(mat, localiseFlags.posCarB, localiseFlags.posPassengerEnd[i], new Scalar(0x00, 0x98, 0xff), 1);
                                break;
                            case Camp.None:
                                // Cv2.Circle(mat, localiseFlags.posPassengerStart[i], 5, new Scalar(0xd8, 0x93, 0xce), -1);
                                Cv2.Rectangle(mat, rectSrc, new Scalar(0xf3, 0x96, 0x21), -1);
                                Cv2.Rectangle(mat, rectDest, new Scalar(0x58, 0xee, 0xff), -1);
                                Cv2.Line(mat, localiseFlags.posPassengerStart[i], localiseFlags.posPassengerEnd[i], new Scalar(0xf3, 0x96, 0x21), 1);
                                break;
                            default:
                                break;
                        }
                    }
                }
                //Cv2.Merge(new Mat[] { car1, car2, black }, merged);
                //Cv2.ImShow("binary", merged);
            }
        }
    }
}
