using System;
using System.Collections;
using System.Collections.Generic;

namespace KiwiTactics.Core
{
    public class DynamicEnum<T> : IEnumerable<KeyValuePair<string, T>>
    {
        private static DynamicEnum<T> _instance;
        private Dictionary<string, T> _values = new Dictionary<string, T>();

        // Private constructor ensures that external classes cannot create a new instance.
        private DynamicEnum() { }

        // Singleton instance accessor
        public static DynamicEnum<T> Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new DynamicEnum<T>();
                }
                return _instance;
            }
        }

        public void AddValue(string name, T value)
        {
            if (!_values.ContainsKey(name))
            {
                _values[name] = value;
            }
            else
            {
                Console.WriteLine($"Value '{name}' already exists.");
            }
        }

        public T GetValue(string name)
        {
            return this[name];
        }

        public bool ContainsValue(string name)
        {
            return _values.ContainsKey(name);
        }

        // Implementing the this[] indexer for getting values
        public T this[string key]
        {
            get
            {
                if (_values.ContainsKey(key))
                    return _values[key];
                throw new KeyNotFoundException($"Value '{key}' not found.");
            }
            set
            {
                _values[key] = value;
            }
        }

        public IEnumerator<KeyValuePair<string, T>> GetEnumerator()
        {
            return _values.GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return _values.GetEnumerator();
        }

        public void PrintAll()
        {
            foreach (var pair in _values)
            {
                Console.WriteLine($"{pair.Key} = {pair.Value}");
            }
        }
        public void Destroy()
        {
            foreach (var pair in _values)
            {
                if (pair.Value is IDisposable disposable)
                {
                    disposable.Dispose();
                }
            }
            _values.Clear();
        }
    }

}