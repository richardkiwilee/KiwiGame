using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.Player
{
    enum WorldResource
    { 
        GOLD = 0,
        FOOD = 1,
        WOOD = 2,
        STONE = 3,
        IRON = 4,
        LUXURY = 5
    }
    internal class PlayerResource
    {
        public Dictionary<WorldResource, int> resource = new Dictionary<WorldResource, int>();
        public List<Army> armies = new List<Army>();
        public bool Actionable()
        {
            foreach (var army in armies)
            {
                if (army.Actionable())
                    return true;
            }
            return false;
        }
        public void EndTurn()
        { 
            foreach (var army in armies)
            {
                // 对每一个部曲执行回合结束操作
                army.EndTurn();
            }
        }
    }
}
