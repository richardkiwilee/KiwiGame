using KiwiTactics.Entity;
using KiwiTactics.Manager;
using KiwiTactics.QuadMap;
using System;
using System.Collections.Generic;
using System.Data.SQLite;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace KiwiTactics.Base
{
    public abstract class SingletonBase<T> where T : SingletonBase<T>, new()
    {
        private static readonly Lazy<T> _instance = new Lazy<T>(() => new T());

        // 提供一个静态实例，这是获取单例对象的方式
        public static T Instance => _instance.Value;

        // 私有或受保护的构造函数确保不能直接实例化
        protected SingletonBase()
        {
            // 可以添加一些初始化代码
            Initialize();
        }

        // 可选：虚方法允许子类执行自定义初始化
        protected virtual void Initialize()
        {
        }
    }

    public class XmlNodeHelper
    { 
        public static string GetAttribute<T>(XmlNode node, T e) where T : struct, Enum
        {
            string attributeName = EnumHelper<T>.EnumToString(e);
            var attribute = node.Attributes[attributeName];
            if (attribute != null)
            {
                return attribute.Value.ToUpper();
            }
            else
            {
                return null;
            }
        }
        public static T2 Get<T1, T2>(XmlNode node, T1 field) where T1: struct, Enum where T2 : struct, Enum
        {
            string value = XmlNodeHelper.GetAttribute<T1>(node, field);
            return EnumHelper<T2>.TryGetEnumValue(value, out var result) ? result : default;
        }
        public static bool Equals<T1,T2>(XmlNode node, T1 field, T2 value) where T1: struct, Enum where T2 :struct ,Enum
        {
            T2 a = XmlNodeHelper.Get<T1, T2>(node, field);
            return a.Equals(value);
        }
        public static bool Equals<T>(string value, T val) where T: struct, Enum
        {
            return EnumHelper<T>.TryGetEnumValue(value, out var result) && result.Equals(val);
        }
    }
    public class EnumHelper<T> where T : struct, Enum
    {
        public static bool TryGetEnumValue(string value, out T result)
        {
            return Enum.TryParse(value, true, out result);
        }
        public static string EnumToString(T value)
        {
            return value.ToString().ToUpper();
        }
        public delegate void AtomDelegate(Unit caster, QuadCell target, XmlNode node, GlobalResourceManager globalResource);
        
        // 使用字典来存储字符串到方法的映射
        private Dictionary<T, AtomDelegate> enumDict = new Dictionary<T, AtomDelegate>();
        public AtomDelegate Get(T key)
        {
            return enumDict[key]; 
        }
        // 添加一个字符串与方法的映射
        public void Add(T key, AtomDelegate action)
        {
            if (!enumDict.ContainsKey(key))
            {
                enumDict[key] = action;
            }
            else
            {
                Console.WriteLine($"Action with key {key} already exists.");
            }
        }

    }
    public class EnumHelper<TEnum, TDelegate>
    where TEnum : struct, Enum
    where TDelegate : Delegate
    {
        public static bool TryGetEnumValue(string value, out TEnum result)
        {
            return Enum.TryParse(value, true, out result);
        }
        public static string EnumToString(TEnum value)
        {
            return value.ToString().ToUpper();
        }

        private Dictionary<TEnum, TDelegate> actions = new Dictionary<TEnum, TDelegate>();

        public void Add(TEnum key, TDelegate action)
        {
            if (!actions.ContainsKey(key))
            {
                actions[key] = action;
            }
            else
            {
                Console.WriteLine($"Action with key {key} already exists.");
            }
        }

        public void Execute(TEnum key, params object[] parameters)
        {
            if (actions.ContainsKey(key))
            {
                actions[key].DynamicInvoke(parameters);
            }
            else
            {
                Console.WriteLine($"No action found for key {key}");
            }
        }
    }
}
