using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.strategy
{
    internal class Landmark
    {
        // 定义战略地图的地标或据点
        public int id;     // 唯一id 全局索引的依据
        public string name;
        public int faction;    // 归属阵营id
        public bool mainstrongholds;      // 是否为主要据点
        public bool iscapital;             // 是否为首都
        public List<BuildingSlot> buildingslots;       // 本据点的所有建筑槽位
        public void FactionChange(int faction) 
        {
            this.faction = faction;
        }

        public void OnTurnStart()
        { 
            foreach (var slot in buildingslots)
            {
                slot.building.OnTurnStart();
            }
        }
        public void OnTurnEnd()
        {
            foreach (var slot in buildingslots)
            {
                slot.building.OnTurnEnd();
            }
        }
    }
}
