using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using KiwiTactics.Base;
using KiwiTactics.Entity;
namespace KiwiTactics.Manager
{
    public class UnitManager
    {
        public UnitManager() { }
        private static UnitManager? instance;
        public static UnitManager Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new UnitManager();
                }
                return instance;
            }
        }
        public Unit RandomUnit(int level)
        {
            UnitContainerProperty health = new UnitContainerProperty(100);
            UnitContainerProperty mana = new UnitContainerProperty(100);
            UnitContainerProperty movement = new UnitContainerProperty(100);
            UnitProperty strength = new UnitProperty(10);
            UnitProperty dexterity = new UnitProperty(10);
            UnitProperty intelligent = new UnitProperty(10);
            UnitProperty will = new UnitProperty(10);
            UnitProperty luck = new UnitProperty(10);

            UnitProperty jump = new UnitProperty(2);
            UnitContainerProperty actionPoint = new UnitContainerProperty(4);
            Direction direction = new Direction();
            List< PropertyBuff > buffs = new List<PropertyBuff> ();
            Unit u = new Unit(health, mana, movement, jump, actionPoint, strength, dexterity, intelligent, will, luck, direction, false, buffs);
            return u;
        }
    }
}
