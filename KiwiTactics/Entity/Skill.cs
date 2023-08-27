using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;
using KiwiTactics.QuadMap;
using KiwiTactics.Base;
using KiwiTactics.Manager;
using System.Data.Entity.Validation;
using System.Data.Entity.Infrastructure;

namespace KiwiTactics.Entity
{

    public class SkillFactory: SingletonBase<SkillFactory>
    {
        private static Dictionary<string, Skill> _skills = new Dictionary<string, Skill>();
        public static Skill Set(XmlNode node)
        {
            string key = XmlNodeHelper.GetAttribute(node, SkillNodeAttr.NAME);
            if (!_skills.ContainsKey(key))
            {
                _skills[key] = new Skill(node);
            }
            return _skills[key];
        }

        public static Skill Get(string name)
        { 
            return _skills[name.ToUpper()];
        }
    }

    /*
     <skill name="fireball" trigger="active" range="circle" targetType="cell" targetCount="1" targetRange="3" targetFilter="enemy" MustVisible="false">
        <damage>
            <factor name="intelligence" value="0.8"/>
            <factor name="const" value="50"/>
        </damage>
        <cost>
            <resource name="ap" value="2"/>
            <resource name="mp" value="50"/>
        </cost>
        <apply>
            <damage repeat="false"/>
            <terrain effect="fire" turns="3"/>
            <unit effect="burn" turns="3"/>
            <generate name="炽焰法球"/>
        </apply>
    </skill>
     */

    public class Skill
    {
        private XmlNode node;
        private XmlNode GetSingleNode<T>(T e) where T: struct, Enum
        {
            return this.node.SelectSingleNode(EnumHelper<T>.EnumToString(e));
        }
        public int GetBaseDamage(Unit caster)
        {
            int dmg = 0;
            XmlNode fcts = this.GetSingleNode(SkillChildNode.DAMAGE);
            foreach (XmlNode factor in fcts)
            {
                string func = factor.Name;
                if (!XmlNodeHelper.Equals<SkillDamageField>(func, SkillDamageField.FACTOR))
                    continue;
                if (XmlNodeHelper.Equals<SkillDamageField, SkillDamageFactor>(factor, SkillDamageField.NAME, SkillDamageFactor.CONST))
                {
                    dmg += int.Parse(XmlNodeHelper.GetAttribute(factor, SkillDamageField.VALUE));
                }
                else
                {
                    string key = XmlNodeHelper.GetAttribute(factor, SkillDamageField.NAME);
                    EnumHelper<UnitAttr>.TryGetEnumValue(key, out UnitAttr attr);
                    int unitAttr = caster.GetAttr(attr);
                    float adj = float.Parse(XmlNodeHelper.GetAttribute(factor, SkillDamageField.VALUE));
                    dmg += (int)(unitAttr * adj);
                }
            }
            return dmg;
        }
        public Skill(XmlNode node)
        {
            this.node = node;
        }
        public SkillCastStatus GetCastStatus(Unit unit, QuadCell cell)
        {
            return SkillCastStatus.SUCCESS;
        }
        public bool Castable(Unit unit, QuadCell cell)
        {
            return GetCastStatus(unit, cell) == SkillCastStatus.SUCCESS;
        }
        private void ApplyCost(Unit caster)
        {
            XmlNode costs = this.GetSingleNode(SkillChildNode.COST);
            foreach (XmlNode cost in costs)
            {
                string func = cost.Name;
            }
        }
        public void Cast(Unit caster, QuadCell cell)
        {
            ApplyCost(caster);
            SkillExecutor executor = SkillExecutor.Instance;
            var g = GlobalResourceManager.Instance;
            XmlNode actions = this.GetSingleNode(SkillChildNode.APPLY);
            foreach (XmlNode action in actions)
            {
                string func = action.Name;
                bool res = EnumHelper<SkillActionEnum>.TryGetEnumValue(func, out SkillActionEnum ret);
                if (res)
                {
                    executor.Execute(caster, cell, action, g);
                }

            }
        }
    }

    public class SkillExecutor : SingletonBase<SkillExecutor>
    {
        public EnumHelper<SkillActionEnum> executorHelper = new EnumHelper<SkillActionEnum>();
        public void Execute(Unit caster, QuadCell target, XmlNode childnode, GlobalResourceManager globalResource)
        {
            string func = childnode.Name;
            bool res = EnumHelper<SkillActionEnum>.TryGetEnumValue(func, out SkillActionEnum ret);
            if (res)
            {
                executorHelper.Get(ret)(caster, target, childnode, globalResource);
            }
        }   
        public SkillExecutor()
        {
            this.executorHelper.Add(SkillActionEnum.DAMAGE, DamageDelegate);
            this.executorHelper.Add(SkillActionEnum.DAMAGE, DamageDelegate);
            this.executorHelper.Add(SkillActionEnum.HEAL, HealDelegate);
            this.executorHelper.Add(SkillActionEnum.MOVE, MoveDelegate);
            this.executorHelper.Add(SkillActionEnum.SUMMON, SummonDelegate);
            this.executorHelper.Add(SkillActionEnum.BUFF, BuffDelegate);
            this.executorHelper.Add(SkillActionEnum.DEBUFF, DebuffDelegate);
        }
        private void DamageDelegate(Unit caster, QuadCell target, XmlNode node, GlobalResourceManager globalResource)
        {

        }
        private void HealDelegate(Unit caster, QuadCell target, XmlNode node, GlobalResourceManager globalResource)
        {
        }

        private void MoveDelegate(Unit caster, QuadCell target, XmlNode node, GlobalResourceManager globalResource)
        {
        }

        private void SummonDelegate(Unit caster, QuadCell target, XmlNode node, GlobalResourceManager globalResource)
        {
        }

        private void BuffDelegate(Unit caster, QuadCell target, XmlNode node, GlobalResourceManager globalResource)
        {
        }

        private void DebuffDelegate(Unit caster, QuadCell target, XmlNode node, GlobalResourceManager globalResource)
        {
        }


    }
}
