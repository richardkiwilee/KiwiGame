using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Transactions;

namespace KiwiTactics.Entity
{
    internal class Building
    {
        public int id;
        public int size_x;
        public int size_y;
        public void OnTurnStart() { }
        public void OnTurnEnd() { }
        public void OnBuild() { }
        public void OnDestory() { }
    }
    internal class BuildingEntity
    {
        public Building building;
        public int x;
        public int y;
    }
    internal class BuildingManager
    {
        List<BuildingEntity> entities;
        public void OnTurnStart()
        {
            foreach (var entity in entities)
            {
                entity.building.OnTurnStart();
            }
        }
        public void OnTurnEnd()
        {
            foreach (var entity in entities)
            {
                entity.building.OnTurnEnd();
            }
        }
    }

}
