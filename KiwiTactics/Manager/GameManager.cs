using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using KiwiTactics.Entity;

namespace KiwiTactics.Manager
{
    internal class GameManager
    {
        public GameManager() { }
        public List<Unit> playerUnits = new List<Unit>();

        public void LoadMap(string mapName) { }
        public void StartGame() { }
        public void OnPlayerTurnStart()
        {
            foreach (var unit in playerUnits)
            {
                unit.OnTurnStart();
            }
        }
        public void OnPlayerTurnEnd()
        {
            foreach (var unit in playerUnits)
            {
                unit.OnTurnEnd();
            }
        }
        public void OnEnemyTurnStart()
        {

        }
        public void OnEnemyTurnEnd()
        {

        }

    }
}
