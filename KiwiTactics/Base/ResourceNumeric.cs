using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using KiwiTactics.Core;
using KiwiTactics.Entity;

namespace KiwiTactics.Base
{
    public class ResourceNumericStructure : IComparable<ResourceNumericStructure>
    {
        // 数值类 提供资源增减和消费
        public int id;
        public int value;
        public string name;
        public int CompareTo(ResourceNumericStructure other)
        {
            return other.value.CompareTo(value);
        }
    }
    public class ResourceNumeric
    {
        private int _value;
        private int _changePerTurn = 0;
        private List<ResourceNumericStructure> buffs;
        public ResourceNumeric(int _value) { this._value = _value; buffs = new List<ResourceNumericStructure>(); }
        public int Value { get => _value; set => this._value = value; }
        public int Valuechg { get => _changePerTurn; set => _changePerTurn = value; }
        public void Add(int value) { this._value += value; }
        public void AddResourcePerTurn(ResourceNumericStructure s)
        {
            buffs.Add(s);
            Refresh();
        }
        private void Refresh()
        {
            _changePerTurn = 0;
            foreach (var s in buffs)
            {
                _changePerTurn += s.value;
            }
        }
        public void RemoveResourcePerTurn(ResourceNumericStructure s)
        {
            buffs.Remove(s);
            Refresh();
        }

        public void Cost(int cost)
        {
            Value -= cost;
        }
    }

}
