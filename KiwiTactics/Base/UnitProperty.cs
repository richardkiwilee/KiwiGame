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
        private int _value;
        private int _adj = 0;
        public List<UnitPropertyStructure> buffs;
        public UnitProperty(int v) 
        {
            _value = v; 
            buffs = new List<UnitPropertyStructure>(); 
        }
        public int Value { get => _value + _adj;}
        private void Refresh()
        {
            _adj = 0;
            foreach (var s in buffs)
            {
                _adj += s.value;
            }
        }
    }
    public class UnitContainerProperty
    {
        private int _currValue;
        private int _maxValue;
        private int _adj = 0;
        public List<UnitPropertyStructure> buffs;
        public int MaxValue
        {
            get { return _maxValue+_adj; }
            set
            {
                if (value < 0) // 如果试图设置的MaxValue小于0，可以抛出异常或设置为0
                {
                    throw new ArgumentOutOfRangeException("MaxValue cannot be less than 0");
                }
                _maxValue = value;
                if (_currValue > _maxValue) // 确保currValue不会超过新设置的MaxValue
                {
                    _currValue = _maxValue;
                }
            }
        }
        public int CurrValue
        {
            get { return _currValue; }
            set
            {
                if (value > _maxValue)
                {
                    _currValue = _maxValue;
                }
                else if (value < 0)
                {
                    _currValue = 0;
                }
                else
                {
                    _currValue = value;
                }
            }
        }

        public UnitContainerProperty(int maxValue)
        {
            if (maxValue < 0)
            {
                throw new ArgumentOutOfRangeException("MaxValue cannot be less than 0");
            }
            _maxValue = maxValue;
            _currValue = _maxValue; 
            _adj = 0;
            buffs = new List<UnitPropertyStructure>();
        }
        private void Refresh()
        {
            _adj = 0;
            foreach (var s in buffs)
            {
                _adj += s.value;
            }
        }
        public void Add(int value)
        {
            this.CurrValue += value;
        }
        public void Subtract(int value)
        {
            this.CurrValue -= value;
        }
        public void Recover()
        { 
           this.CurrValue = this.MaxValue;
        }
    }

}
