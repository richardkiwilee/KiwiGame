using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.Base
{
    public enum NumericAdjType
    {
        CONST,
        PERCENT
    }

    public class UnitPropertyStructure : IComparable<UnitPropertyStructure>
    {
        // 数值类 提供资源增减和消费
        public int id;
        public int value;
        public string name;
        public int CompareTo(UnitPropertyStructure other)
        {
            return other.value.CompareTo(value);
        }
    }
    public class UnitProperty
    {
        private int value;
        private int valuechg = 0;
        private List<UnitPropertyStructure> source;
        public UnitProperty(int _value) { value = _value; }
        public int Value { get => value; set => this.value = value; }
        public int Valuechg { get => valuechg; set => valuechg = value; }
        public void Add(int value) { this.value += value; }
        public void AddResourcePerTurn(UnitPropertyStructure s)
        {
            source.Add(s);
            Refresh();
        }
        private void Refresh()
        {
            source.Sort();
            int chg = 0;
            foreach (var s in source)
            {
                chg += s.value;
            }
            valuechg = chg;
        }
        public void RemoveResourcePerTurn(UnitPropertyStructure s)
        {
            source.Remove(s);
            Refresh();
        }
    }
}
