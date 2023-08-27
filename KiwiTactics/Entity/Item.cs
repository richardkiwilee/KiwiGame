using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.Entity
{
    internal class Item
    {
    }

    enum ItemType
    {
        Helmet = 1,     // 头盔
        Armor = 2,      // 护甲
        Gaiters = 3,    // 护腿
        Jewelry = 4,    // 饰品
        Weapon = 5,     // 武器
        Shield = 6,     // 盾牌
        Consulmable = 7,   // 消耗品
    }
    internal abstract class Equipment
    {
        public abstract void OnEquiped(Unit unit);
        public abstract void OnUnequiped(Unit unit);
        public abstract void OnUsed(Unit unit);
    }
}
