using KiwiTactics.Entity;
using KiwiTactics.Manager;
using KiwiTactics.QuadMap;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace KiwiTactics.Base
{
    public enum SkillNodeAttr
    { 
        NAME,
        TYPE,
        TRIGGER,
        RANGE,
        TARGET,
        EFFECT
    }
    public enum SkillChildNode
    {
        DAMAGE,
        COST,
        APPLY
    }
    public enum SkillActionEnum
    {
        NULL,
        DAMAGE,
        HEAL,
        BUFF,
        DEBUFF,
        MOVE,
        SUMMON,
    }
    public enum SkillDamageFactor
    { 
        CONST,
        STR,
        INT,
        DEX,
        WILL,
        LUCK,
        MAXHP,
        MAXMP,
        CURHP,
        CURMP,
        AP
    }
    public enum SkillDamageField
    { 
        FACTOR,
        NAME,
        VALUE
    }
    public enum SkillTriggerType
    {
        Active = 1,
        Passive = 2,
        Trigger = 3
    }
    public enum SkillEffectRange
    {
        Self = 1,
        Single = 2,
        Line = 3,
        Cross = 4,
        Circle = 5,
        Square = 6,
        All = 7
    }
    public enum TargetType
    {
        Unit = 1,   // 影响单位
        Cell = 2,    // 影响地格
        BattleField = 3, // 影响战场

    }
    public enum SkillCastStatus
    {
        SUCCESS = 0,      // 有效
        OutOfRange = 1,     // 超出范围
        OutOfResource = 2,  // 资源不足
        InvalidTargetType = 3,  // 目标类型不对
        NotVisible = 4, // 不可见
        WrongCamp = 5,  // 目标阵营错误
        WrongCellType = 6   // 目标地格类型错误
    }


    // unit
    public enum UnitAttr
    {
        Health,
        Mana,
        Movement,
        Jump,
        ActionPoint,
        Strength,
        Dexterity,
        Intelligent,
        Will,
        Luck,
    }
}
