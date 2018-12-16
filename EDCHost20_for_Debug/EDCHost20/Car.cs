using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EDC20HOST
{
    class Car //选手的车
    {
        public const int PunishScore = 100; //惩罚分数
        public Dot Pos;
        public Camp Who { get; set; } //A or B
        public int Score { get; set; } //当前得分
        public Passenger People { get; set; } //乘客
        public bool UnderStop; //是否正在强制停车
        public int FoulCnt; //惩罚次数
        public void FinishCarry()
        {
            if (People == null) return; //没有乘客直接返回
            Score += People.Score();
            People = null;
        }
        public void Stop() { UnderStop = true; } //车辆强制停止
        public void Start() { UnderStop = false; } //从强制停止中恢复
        public void StartCarry(Passenger passenger)
        {
            if (People != null) return; //有乘客直接返回
            People = passenger;
        }
        public void Out() //出界处理
        {
            Stop();
            Foul();
        }
        public void Foul() //犯规
        {
            FoulCnt++;
        }
        public Car(Camp c)
        {
            Who = c;
            Pos = new Dot();
            Score = 0;
            People = null;
            UnderStop = false;
            FoulCnt = 0;
        }
    }
}
