using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.Player
{
    internal class Army
    {
        public List<Unit.Unit>  units = new List<Unit.Unit>();
        public Unit.Unit leader;
        public bool trusteeship { get; set; }        // 托管回合结束
        public bool Actionable()
        { 
            if (trusteeship) { return false; }
            foreach (var unit in units)
            {
                if (!unit.actioned)
                    return true;
             }
            return false;
        }
        public void EndTurn()
        { 
            // 回合结束时 执行可用的据点指令
            foreach (var unit in units)
            {
                if (!unit.actioned)
                { 
                    // 执行可用的指令
                }
            }
        }
    }
}
