using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace EDC20HOST
{
    public enum GameState { Unstart = 0, Normal = 1, Pause = 2, End = 3 };
    class Game
    {
        public bool DebugMode; //调试模式，最大回合数 = 1,000,000
        public const int MaxSize = 270;
        public const int MaxPassenger = 5;
        public const int MinCarryDistance = 10; //最小接送距离
        public const int BackRound = 50; //回溯回合数
        public int Round { get; set; }//当前回合
        public GameState state { get; set; }
        public Car CarA, CarB;
        public Passenger[] Passengers;
        public PassengerGenerator Generator { get; set; }
        public int CurrPassengerNumber; //当前乘客数量
        public static bool[,] GameMap = new bool[MaxSize, MaxSize]; //地图信息
        public static bool PassengerDotValid(Dot dot)//新规则直接输出点
        {
            //return true;
            //             int margin = 6;
            //             if (dot.x < margin || dot.x > MaxSize - margin || dot.y < margin || dot.y > MaxSize - margin) return false;
            //             for (int i = ((dot.x - margin > 0) ? (dot.x - margin) : 0); i <= ((dot.x + margin < MaxSize) ? (dot.x + margin) : MaxSize - 1); ++i)
            //                 for (int j = ((dot.y - margin > 0) ? (dot.y - margin) : 0); j <= ((dot.y + margin < MaxSize) ? (dot.y + margin) : MaxSize - 1); ++j)
            //                     if (!GameMap[i, j])
            //                         return false;
            //            return true;
            return GameMap[dot.x, dot.y];
        }
        public static bool CarDotValid(Dot dot)//车点是否有效->3*3方格白色大于4
        {
            //return true;
            int count = 0;
            for (int i = ((dot.x - 1 > 0) ? (dot.x - 1) : 0); i <= ((dot.x + 1 < MaxSize) ? (dot.x + 1) : MaxSize - 1); ++i)
                for (int j = ((dot.y - 1 > 0) ? (dot.y - 1) : 0); j <= ((dot.y + 1 < MaxSize) ? (dot.y + 1) : MaxSize - 1); ++j)
                    if (GameMap[i, j])
                        count++;
            if (count >= 4) return true;
            else return false;
        }
        public static void LoadMap()//读取地图文件
        {
            FileStream MapFile = File.OpenRead("../../map/map270ver2.bmp");
            byte[] buffer = new byte[MapFile.Length - 54]; //存储图片文件
            MapFile.Position = 54;
            MapFile.Read(buffer, 0, buffer.Length);
            for (int i = 0; i != MaxSize; ++i)
               for (int j = 0; j != MaxSize; ++j)
                 if (buffer[(i * MaxSize + j) * 3 + 2*i] > 128)//白色
                   GameMap[i, j] = true;
              else
                   GameMap[i, j] = false;
        }
        public static StartDestDot OppoDots(StartDestDot prevDot)
        {
            StartDestDot newDots = new StartDestDot();
            newDots.StartPos.x = prevDot.StartPos.y;
            newDots.StartPos.y = prevDot.StartPos.x;
            newDots.DestPos.x = prevDot.DestPos.y;
            newDots.DestPos.y = prevDot.DestPos.x;
            return newDots;
        }
        public double GetDistance(Dot A, Dot B)
        {
            return Math.Sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
        }
        public Game()
        {
            CarA = new Car(Camp.CampA);
            CarB = new Car(Camp.CampB);
            Passengers = new Passenger[MaxPassenger];
            Round = 0;
            state = GameState.Unstart;
            Generator = new PassengerGenerator();
            Generator.Generate(500);
            Passengers[0] = new Passenger(Generator.NextA(), false, 1);
            Passengers[1] = new Passenger(Generator.NextB(), false, 2);
            Passengers[2] = new Passenger(Generator.NextA(), false, 3);
            Passengers[3] = new Passenger(Generator.NextB(), false, 4);
            Passengers[4] = new Passenger(Generator.NextS(), true, 5);
            CheckPassengerNumber();
            DebugMode = false;
        }
        protected void CheckPassengerNumber() //根据回合数更改最大乘客数量
        {
            if (Round == 0)
            {
                CurrPassengerNumber = 2;
            }
            else if (Round == 400)
            {
                CurrPassengerNumber = 4;
            }
            else if (Round == 800)
            {
                CurrPassengerNumber = 5;
            }
        }
        public void NewPassenger(int num) //刷新这一位置的新乘客
        {
            StartDestDot temp = new StartDestDot();
            if (num == 1 || num == 3)
                temp = Generator.NextA();
            else if (num == 2 || num == 4)
                temp = Generator.NextB();
            else
                temp = Generator.NextS();
            Passengers[num - 1] = new Passenger(temp, num == 5, num);
        }
        /*public void CarFoul(Camp c) //车犯规
        {
            Pause();
            if (c == Camp.CampA)
            {
                CarB.Score += Car.PunishScore;
                CarA.FoulCnt++;
            }
            else
            {
                CarA.Score += Car.PunishScore;
                CarB.FoulCnt++;
            }
            Round -= BackRound;
            if(CarA.People != null)
            {
                int currNum = CarA.People.Number;
                CarA.People = null;
                NewPassenger(currNum);
            }
            if (CarB.People != null)
            {
                int currNum = CarB.People.Number;
                CarB.People = null;
                NewPassenger(currNum);
            }
            if (Round < 0) Round = 0;
        }*/
        public void Start() //开始比赛
        {
            state = GameState.Normal;
            CarA.Start();
            CarB.Start();
        }
        public void Pause() //暂停比赛
        {
            state = GameState.Pause;
            CarA.Stop();
            CarB.Stop();
        }
        public void End() //结束比赛
        {
            state = GameState.End;
        }
        public void Update()//每回合执行
        {
            if (state == GameState.Normal)
            {
                Round++;
                //GetInfoFromCameraAndUpdate();
                CheckPassengerNumber();
                #region PunishmentPhase
                //if (!CarDotValid(CarA.Pos)) CarA.Stop();
                //if (!CarDotValid(CarB.Pos)) CarB.Stop();
                #endregion

                //上车
                for (int i = 0; i != CurrPassengerNumber; ++i)
                {
                    Passenger p = Passengers[i];
                    if (p.Owner != Camp.None) continue; //已经上车了
                    if (CarA.UnderStop == false && CarA.People == null && GetDistance(p.StartDestPos.StartPos, CarA.Pos) < MinCarryDistance)
                    {
                        CarA.StartCarry(p);
                        p.Owner = Camp.CampA;
                    }

                    else if (CarB.UnderStop == false && CarB.People == null && GetDistance(p.StartDestPos.StartPos, CarB.Pos) < MinCarryDistance)
                    {
                        CarB.StartCarry(p);
                        p.Owner = Camp.CampB;
                    }
                }
                //下车
                if (CarA.People != null && GetDistance(CarA.People.StartDestPos.DestPos, CarA.Pos) < MinCarryDistance)
                {
                    int currNum = CarA.People.Number;
                    CarA.FinishCarry();
                    NewPassenger(currNum);
                }
                if (CarB.People != null && GetDistance(CarB.People.StartDestPos.DestPos, CarB.Pos) < MinCarryDistance)
                {
                    int currNum = CarB.People.Number;
                    CarB.FinishCarry();
                    NewPassenger(currNum);
                }
                if ((Round >= 1200 && DebugMode == false) || (Round >= 1000000 && DebugMode == true)) //结束比赛
                {
                    End();
                }
            }
            //byte[] message = PackMessage();
            //SendMessage
        } 
        public byte[] PackMessage()
        {
            byte[] message = new byte[64]; //上位机传递的信息
            message[0] = (byte)(((byte)state << 6)|(Round>>8));
            message[1] = (byte)Round;
            StartDestDot[] P = new StartDestDot[5];
            for (int i = 0; i != 5; ++i)
            {
                P[i] = Passengers[i].StartDestPos;
                if(i >= CurrPassengerNumber)
                {
                    P[i].StartPos.x = 0;
                    P[i].StartPos.y = 0;
                    P[i].DestPos.x = 0;
                    P[i].DestPos.y = 0;
                }
            }
            message[2] = (byte)((CarA.Pos.x >> 1 & 0x80)| (CarA.Pos.y >> 2 & 0x40)| (CarB.Pos.x >> 3 & 0x20)| (CarB.Pos.y >> 4 & 0x10)
                | (P[0].StartPos.x >> 5 & 0x08) | (P[0].StartPos.y >> 6 & 0x04)
                | (P[0].DestPos.x >> 7 & 0x02) | (P[0].DestPos.y >> 8 & 0x01));
            message[3] = (byte)((P[1].StartPos.x >> 1 & 0x80) | (P[1].StartPos.y >> 2 & 0x40)
                | (P[1].DestPos.x >> 3 & 0x20) | (P[1].DestPos.y >> 4 & 0x10)
                | (P[2].StartPos.x >> 5 & 0x08) | (P[2].StartPos.y >> 6 & 0x04)
                | (P[2].DestPos.x >> 7 & 0x02) | (P[2].DestPos.y >> 8 & 0x01));
            message[4] = (byte)((P[3].StartPos.x >> 1 & 0x80) | (P[3].StartPos.y >> 2 & 0x40)
                | (P[3].DestPos.x >> 3 & 0x20) | (P[3].DestPos.y >> 4 & 0x10)
                | (P[4].StartPos.x >> 5 & 0x08) | (P[4].StartPos.y >> 6 & 0x04)
                | (P[4].DestPos.x >> 7 & 0x02) | (P[4].DestPos.y >> 8 & 0x01));
            message[5] = (byte)CarA.Pos.x;
            message[6] = (byte)CarA.Pos.y;
            message[7] = (byte)CarB.Pos.x;
            message[8] = (byte)CarB.Pos.y;
            message[9] = (byte)((CurrPassengerNumber << 2) | (byte)Passengers[0].Owner);
            message[10] = (byte)((byte)Passengers[1].Owner << 6 | (byte)Passengers[2].Owner << 4
                | (byte)Passengers[3].Owner << 2 | (byte)Passengers[4].Owner);
            for(int i = 0; i != 5; ++i)
            {
                message[11 + i * 4] = (byte)P[i].StartPos.x;
                message[12 + i * 4] = (byte)P[i].StartPos.y;
                message[13 + i * 4] = (byte)P[i].DestPos.x;
                message[14 + i * 4] = (byte)P[i].DestPos.y;
            }
            message[31] = (byte)CarA.FoulCnt;
            message[32] = (byte)CarB.FoulCnt;
            message[33] = (byte)(CarA.Score >> 8);
            message[34] = (byte)(CarA.Score);
            message[35] = (byte)(CarB.Score >> 8);
            message[36] = (byte)(CarB.Score);
            message[62] = 0x0D;
            message[63] = 0x0A;
            return message;
        }
    }
}