using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.Data
{
    internal class BuildingData
    {
        // 获取建筑序列升级的id列表
        public static int[] GetUpgradeIds(int faction, int seq, int id)
        {
            return new int[] { id };
        }
        public static int GetBuildingLevelById(int seq, int id)
        {
            return 1;
        }
        public static int GetBuildingIdByLevel(int faction, int seq, int level)
        {
            return 1;
        }
        // 获取建筑序列降级的id列表
        public static int[] GetDowngradeIds(int faction, int seq, int id)
        {
            return new int[] { id };
        }
        // 获取升级或降级的所需回合数 只能一级级升或一级级降
        public static int GetBuildingCostTurnById(int faction, int seq, int id)
        {
            return 2;
        }
        public static int GetBuildingDestroyTurn()
        {
            return 1;
        }
    }
}
