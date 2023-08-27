using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KiwiTactics.QuadMap
{
    internal class QuadMap
    {
        QuadMap(int x, int y) { }
        private QuadCell[,] cells;
        public QuadCell GetCell(int x, int y) { return cells[x, y]; }

    }

}
