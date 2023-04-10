using KiwiTactics.Data;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Transactions;

namespace KiwiTactics.strategy
{
    internal class BuildingFactory
    { 
        public static BuildingSequence Create(int seq)
        {
            return new BuildingSequence();
        }
    }
    internal class BuildingSequence
    {
        public Dictionary<int, int> fee;        // 维护费
        public Dictionary<int, int> produce;    // 产出
        public List<int> unlock;                // 解锁内容
        public void Upgrade()
        { }
        public void Downgrade() { }

        public void OnTurnStart()
        { }

        public void OnTurnEnd() { }

    }
    internal class BuildingSlot
    {
        public int seq;     // 建筑槽内的序列
        public int DestructibleSeq;   // 此槽位是否只允许建造指定序列
        public BuildingSequence? building;
        public void Destroy()
        {
            building = null;
        }
        public void Upgrade()
        {
            building.Upgrade();
        }
        public void Downgrade()
        {
            building.Downgrade();
        }
        public void NewSequence(int s)
        {
            seq = s;
            building = BuildingFactory.Create(s);
        }
    }
}
