using KiwiTactics.Base;
using KiwiTactics.Core;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.Manager
{
    public class GlobalResourceManager
    {
        private DynamicEnum<ResourceNumeric> resources = DynamicEnum<ResourceNumeric>.Instance;
        private GlobalResourceManager() { }
        private static GlobalResourceManager? instance;
        public static GlobalResourceManager Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new GlobalResourceManager();
                }
                return instance;
            }
        }
        public void OnTurnStart()
        {
            foreach (var resource in resources)
            {
                var cls = resource.Value;
                cls.Value += cls.Valuechg;
            }
        }
        public ResourceNumeric Get(string resourceName)
        {
            return resources[resourceName];
        }

        public void Destory()
        {
            resources.Destroy();
        }
    }
}
