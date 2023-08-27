using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using KiwiTactics.Core;

namespace KiwiTactics.Base
{
    public class NumericStructure : IComparable<NumericStructure>
    {
        public int id;
        public int value;
        public string name;

        public int CompareTo(NumericStructure other)
        {
            return other.value.CompareTo(value);
        }
    }
    public class Numeric
    {
        private int value;
        private int valuechg = 0;
        private List<NumericStructure> source;
        public Numeric(int _value) { value = _value; }
        public int Value { get => value; set => this.value = value; }
        public int Valuechg { get => valuechg; set => valuechg = value; }
        public void Add(int value) { this.value += value; }
        public void AddResourcePerTurn(NumericStructure s)
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
        public void RemoveResourcePerTurn(NumericStructure s)
        {
            source.Remove(s);
            Refresh();
        }

        public void Cost(int cost)
        {
            Value -= cost;
        }
    }

}
