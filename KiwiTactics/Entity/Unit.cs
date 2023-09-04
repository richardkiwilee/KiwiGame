using System.Runtime.CompilerServices;
using System.Security.Cryptography.X509Certificates;
using KiwiTactics.Base;
namespace KiwiTactics.Entity
{
    public enum ValueEffectType
    {
        ConstValue = 1,
        PercentValue = 2
    }
    public enum BuffType
    {
        Persistent = 1, // 持续性buff
        Turn = 2,       // 回合性buff
        Times = 3,       // 次数性buff
        Range = 4      // 范围性buff
    }
    public abstract class PropertyBuff
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

    public class Unit
    {
        public UnitContainerProperty health;
        public UnitContainerProperty mana;
        public UnitContainerProperty movement;
        public UnitProperty jump;
        public UnitContainerProperty actionPoint;
        public UnitProperty strength;
        public UnitProperty dexterity;
        public UnitProperty intelligent;
        public UnitProperty will;
        public UnitProperty luck;
        public Direction direction;

        public Unit(UnitContainerProperty health, UnitContainerProperty mana, UnitContainerProperty movement, UnitProperty jump, UnitContainerProperty actionPoint, UnitProperty strength, UnitProperty dexterity, UnitProperty intelligent, UnitProperty will, UnitProperty luck, Direction direction, bool actioned, List<PropertyBuff> buffs)
        {
            this.health = health;
            this.mana = mana;
            this.movement = movement;
            this.jump = jump;
            this.actionPoint = actionPoint;
            this.strength = strength;
            this.dexterity = dexterity;
            this.intelligent = intelligent;
            this.will = will;
            this.luck = luck;
            this.direction = direction;
            this.actioned = actioned;
            this.buffs = buffs;
        }

        public int GetAttr(UnitAttr key)
        {
            return 0;
        }
        public bool actioned;   // 是否待机
        public List<PropertyBuff> buffs;    // 当前角色的所有buff

        public void OnTurnStart()
        {
            // 回合开始时刷新每回合的行动资源
            movement.Recover();
            actionPoint.Recover();
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
}