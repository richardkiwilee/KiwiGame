using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;
using KiwiTactics.Base;
namespace KiwiTactics.Entity
{
    enum ValueEffectType
    {
        ConstValue = 1,
        PercentValue = 2
    }
    enum BuffType
    {
        Persistent = 1, // 持续性buff
        Turn = 2,       // 回合性buff
        Times = 3,       // 次数性buff
        Range = 4      // 范围性buff
    }
    internal abstract class PropertyBuff
    {
        public int id;
        public ValueEffectType effectType;
        public BuffType type;
        public int remainTurns;
        public int effectValue;
        public void OnTurnEnd()
        {
            if (type == BuffType.Turn)
            {
                remainTurns--;
            }
        }
        public abstract void OnApply(Unit unit);
        public abstract void OnRemove(Unit unit);

    }

    internal class Property
    {
        public int baseValue;       // 基础值
        public int bonusValue;      // 加值
        public int totalValue;      // 最终结算值
        public float bonusRate;     // 调整百分比
        public bool hasMax;     // 是否有最大值
        public int maxValue;    // 最大值
        public bool overflowable;   // 值是否可以超过最大值
        public bool negative;   // 值是否可以为负数
        public int limit;      // 属性的硬上限
        public void Refresh()
        {
            totalValue = (int)(baseValue * (1 + bonusRate) + bonusValue);
        }
    }

    // 简化伤害类型 不细分物理打击类型和属性类型
    enum DamageType
    {
        Physical = 1,
        Magical = 2,
        Pure = 3,
        Heal = 4
    }
    class Health : Property
    {
        Health()
        {
            hasMax = true;
            maxValue = 100;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }
    class Mana : Property
    {
        Mana()
        {
            hasMax = true;
            maxValue = 100;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }
    class Movement : Property
    {
        Movement()
        {
            hasMax = true;
            maxValue = 5;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }

    class Jump : Property
    {
        Jump()
        {
            hasMax = true;
            maxValue = 5;
            overflowable = false;
            negative = false;
            limit = 9;
        }
    }
    class ActionPoint : Property
    {
        ActionPoint()
        {
            hasMax = true;
            maxValue = 3;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }
    class Strength : Property
    {
        Strength()
        {
            hasMax = true;
            maxValue = 3;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }
    class Dexterity : Property
    {
        Dexterity()
        {
            hasMax = true;
            maxValue = 3;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }
    class Intelligent : Property
    {
        Intelligent()
        {
            hasMax = true;
            maxValue = 3;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }

    class Will : Property
    {
        Will()
        {
            hasMax = true;
            maxValue = 3;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }
    class Luck : Property
    {
        Luck()
        {
            hasMax = true;
            maxValue = 3;
            overflowable = false;
            negative = false;
            limit = 999;
        }
    }

    enum Direction
    {
        N = 1,
        E = 2,
        W = 3,
        S = 4
    }

    public class Unit
    {
        public Health health;
        public Mana mana;
        public Movement movement;
        public Jump jump;
        public ActionPoint actionPoint;
        public Strength strength;
        public Dexterity dexterity;
        public Intelligent intelligent;
        public Will will;
        public Luck luck;
        public Direction direction;
        public int GetAttr(UnitAttr key)
        {
            return 0;
        }
        public bool actioned;   // 是否待机
        public List<PropertyBuff> buffs;    // 当前角色的所有buff

        public void OnTurnStart()
        {
            // 回合开始时刷新每回合的行动资源
            movement.Refresh();
            actionPoint.Refresh();
        }
        public void OnTurnEnd()
        {
            // 回合结束时结算效果时长 如果效果时长为0则移除效果 并从
            for (int i = buffs.Count; i > 0; i--)
            {
                buffs[i].OnTurnEnd();
                if (buffs[i].remainTurns <= 0)
                {
                    buffs[i].OnRemove(this);
                    buffs.RemoveAt(i);
                }
            }
        }
        public void Move(int distance)
        {

        }

        public void OnAttacked(Unit attacker)
        {

        }
    }

    internal class EnemyUnit : Unit
    {

    }
}