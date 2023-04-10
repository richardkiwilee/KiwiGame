namespace KiwiTactics.Unit
{
    internal class Unit
    {
        public int Health { get; private set; }
        public int MaxHealth { get; private set; }
        public int MaxMovement { get; private set; }
        public int Movement { get; private set; }
        public int Attack { get; private set; }
        public int Defense { get; private set; }
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

        public List<Attritube> Attributes { get; private set; }
        public List<Status> Statuses { get; private set; }

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
        public void Attack(Unit target)
        {
            target.Health -= Attack;
        }
        public void OnAttacked(Unit attacker)
        {
            Health -= attacker.Attack;
        }
    }
}