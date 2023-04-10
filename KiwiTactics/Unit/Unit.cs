namespace KiwiTactics.Unit
{
    internal class Unit
    {
        public int Health { get; private set; }
        public int MaxHealth { get; private set; }
        public int MaxMovement { get; private set; }
        public int Movement { get; private set; }
        public int PhyAttack { get; private set; }
        public int PhyDefense { get; private set; }
        public int MagicAttack { get; private set; }
        public int MagicDefense { get; private set; }
        public int Speed { get; private set; }
        public int Luck { get; private set; }
        public int Direction { get; private set; }

        public int FireResistance { get; private set; }
        public int IceResistance { get; private set; }
        public int ThunderResistance { get; private set; }
        public int LightResistance { get; private set; }
        public int DarkResistance { get; private set; }
        public int EarthResistance { get; private set; }
        public int WindResistance { get; private set; }

        public bool actioned;   // 地图指令是否已执行
        public List<Attributes.Attribute> Attributes { get; private set; }
        public List<Attributes.Status> Statuses { get; private set; }

        public void OnTurnStart()
        {
            Movement = MaxMovement;
        }
        public void OnTurnEnd()
        {
            Movement = 0;
        }
        public void Move(int distance)
        {
            Movement -= distance;
        }

        public void OnAttacked(Unit attacker)
        {
            Health -= attacker.PhyAttack;
        }
    }
}