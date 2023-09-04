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
        Persistent = 1, // ������buff
        Turn = 2,       // �غ���buff
        Times = 3,       // ������buff
        Range = 4      // ��Χ��buff
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
        public int baseValue;       // ����ֵ
        public int bonusValue;      // ��ֵ
        public int totalValue;      // ���ս���ֵ
        public float bonusRate;     // �����ٷֱ�
        public bool hasMax;     // �Ƿ������ֵ
        public int maxValue;    // ���ֵ
        public bool overflowable;   // ֵ�Ƿ���Գ������ֵ
        public bool negative;   // ֵ�Ƿ����Ϊ����
        public int limit;      // ���Ե�Ӳ����
        public void Refresh()
        {
            totalValue = (int)(baseValue * (1 + bonusRate) + bonusValue);
        }
    }

    // ���˺����� ��ϸ�����������ͺ���������

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
        public bool actioned;   // �Ƿ����
        public List<PropertyBuff> buffs;    // ��ǰ��ɫ������buff

        public void OnTurnStart()
        {
            // �غϿ�ʼʱˢ��ÿ�غϵ��ж���Դ
            movement.Recover();
            actionPoint.Recover();
        }
        public void OnTurnEnd()
        {
            // �غϽ���ʱ����Ч��ʱ�� ���Ч��ʱ��Ϊ0���Ƴ�Ч�� ����
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