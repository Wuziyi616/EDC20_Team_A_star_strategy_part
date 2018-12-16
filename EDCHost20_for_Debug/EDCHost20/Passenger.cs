using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EDC20HOST
{
    public struct Dot //点
    {
        public int x;
        public int y;
    }
    struct StartDestDot
    {
        public Dot StartPos;
        public Dot DestPos;
        public double Distance =>
            Math.Sqrt((StartPos.x - DestPos.x) * (StartPos.x - DestPos.x) + (StartPos.y - DestPos.y) * (StartPos.y - DestPos.y));
    }

    public enum Camp
    {
        None = 0, CampA, CampB
    }
    class Passenger
    {
        private static int[] distanceLevel = new int[5] { 0, 68, 158, 270, 381 };
        private static int[] scoreLevel = new int[4] { 20, 40, 80, 100 };
        public StartDestDot StartDestPos; //起点
        public Camp Owner { get; set; }  //所有者
        public bool Special { get; set; } //特殊乘客
        public int Number { get; set; } //编号
        public double Distance =>
            Math.Sqrt((StartDestPos.StartPos.x - StartDestPos.DestPos.x) * (StartDestPos.StartPos.x - StartDestPos.DestPos.x)
                + (StartDestPos.StartPos.y - StartDestPos.DestPos.y) * (StartDestPos.StartPos.y - StartDestPos.DestPos.y)); //距离
        public int Score() //得分
        {
            int score = 0;
            for (int i = 0; i != distanceLevel.Length; ++i)
                if (Distance >= distanceLevel[i] && Distance < distanceLevel[i + 1])
                {
                    score = scoreLevel[i];
                    break;
                }
                else continue;
            if (score == 0) throw new System.IndexOutOfRangeException("Score为0");
            // if (Special) score = score * 3 / 2;
            return score;
        }
        public Passenger(StartDestDot startDestDot, bool special, int number)
        {
            StartDestPos = startDestDot;
            Special = special;
            Number = number;
            Owner = Camp.None;
        }
        public void ResetInfo(StartDestDot startDestDot, bool special, int number)
        {
            StartDestPos = startDestDot;
            Special = special;
            Number = number;
            Owner = Camp.None;
        }
    }
    class PassengerGenerator //存储预备要用的乘客信息
    {
        //A和B分别完成到了哪一个乘客
        private Stack<StartDestDot> APassenger;
        private Stack<StartDestDot> BPassenger;
        private Stack<StartDestDot> SPassenger;
        public void Generate(int amount) //生成指定数量的乘客
        {
            APassenger = new Stack<StartDestDot>();
            BPassenger = new Stack<StartDestDot>();
            SPassenger = new Stack<StartDestDot>();
            int nextX, nextY;
            StartDestDot dots;
            Random NRand = new Random();
            for (int i = 0; i != amount; ++i)
            {
                do
                {
                    nextX = NRand.Next(Game.MaxSize);
                    nextY = NRand.Next(Game.MaxSize);
                    dots.StartPos.x = nextX; dots.StartPos.y = nextY;
                }
                while ((!Game.PassengerDotValid(dots.StartPos)) || (Math.Abs(nextX - nextY) < 15)); //循环得到一个有效的点，并避免在中线上
                do
                {
                    nextX = NRand.Next(Game.MaxSize);
                    nextY = NRand.Next(Game.MaxSize);
                    dots.DestPos.x = nextX; dots.DestPos.y = nextY;
                }
                while ((!Game.PassengerDotValid(dots.DestPos)) || dots.Distance < 20); //循环得到一个有效的终点，并且舍弃过近的距离
                if(dots.StartPos.x < dots.StartPos.y) //下半->A区
                {
                    APassenger.Push(dots);
                    BPassenger.Push(Game.OppoDots(dots));
                }
                else  //上半->B区
                {
                    BPassenger.Push(dots);
                    APassenger.Push(Game.OppoDots(dots));
                }
                //下面生成特殊点位置
                do
                {
                    nextX = NRand.Next(Game.MaxSize);
                    nextY = NRand.Next(Game.MaxSize);
                    dots.StartPos.x = nextX; dots.StartPos.y = nextY;
                    nextX = NRand.Next(Game.MaxSize);
                    nextY = NRand.Next(Game.MaxSize);
                    dots.DestPos.x = nextX; dots.DestPos.y = nextY;
                }
                while ((!Game.PassengerDotValid(dots.StartPos))|| (!Game.PassengerDotValid(dots.DestPos))
                    || dots.Distance < 100); //循环得到一个有效的终点，并且舍弃过近的距离->更大
                SPassenger.Push(dots);
            }
        }
        //返回下一个乘客的坐标
        public StartDestDot NextA() { return APassenger.Pop(); }
        public StartDestDot NextB() { return BPassenger.Pop(); }
        public StartDestDot NextS() { return SPassenger.Pop(); }
    }
}