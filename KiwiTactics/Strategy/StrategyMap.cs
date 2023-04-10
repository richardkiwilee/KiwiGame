using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.strategy
{
    internal class StrategyMapNode
    {
        Landmark Landmark;
        int pos_x;
        int pos_y;
    }
    internal class StrategyMap
    {
        // 定义无向图
        private Dictionary<int, List<int>> map;
        public static bool IsNeighbor(int x, int y) 
        {
            return true;
        }
        public static int GetMoveCost(int x, int y) 
        {
            return 1;
        }
    }
    
}
