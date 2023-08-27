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
        Persistent = 1, // ������buff
        Turn = 2,       // �غ���buff
        Times = 3,       // ������buff
        Range = 4      // ��Χ��buff
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
        public bool actioned;   // �Ƿ����
        public List<PropertyBuff> buffs;    // ��ǰ��ɫ������buff

        public void OnTurnStart()
        {
            // �غϿ�ʼʱˢ��ÿ�غϵ��ж���Դ
            movement.Refresh();
            actionPoint.Refresh();
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

    internal class EnemyUnit : Unit
    {

    }
}