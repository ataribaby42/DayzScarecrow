class ab_ScarecrowController
{
	private string name;
	private float resetRadius;
	private float minTimeBetweenCreepySound = 20;
	private float creepySoundChance = 0.3;
	private float lastCreepySoundTimeslice;
	private vector position;
	private float radius;
	private int scarecrowCount;
	private ref array<ref ab_Scarecrow> scarecrows = new array<ref ab_Scarecrow>();
	private ref array<string> scarecrowPositions = new array<string>();
	private bool active = false;
	
	void ab_ScarecrowController(string Name, vector Position, float ResetRadius, float Radius, int ScarecrowCount, ref array<string> ScarecrowPositions)
	{
		if (!ScarecrowPositions)
		{
			Print("Random Scarecrow <" + Name + "> created at " + Position + ".");
		}
		else
		{
			Print("Predefined Scarecrows <" + Name + "> created at " + Position + ".");
		}
		
		lastCreepySoundTimeslice = 0;
		this.name = Name;
		this.position = Position;
		this.radius = Radius;
		this.scarecrowCount = ScarecrowCount;
		this.scarecrowPositions = ScarecrowPositions;
		this.resetRadius = ResetRadius;
		
		for (int i = 0; i < scarecrowCount; i++)
		{
			scarecrows.Insert(new ref ab_Scarecrow(name, position, resetRadius));
		}
		
		SetupScarecrows();
	}

	void ~ab_ScarecrowController()
	{
		
	}
	
	void SetupScarecrows()
	{
		if (scarecrows)
		{
			int i;
			vector pos;
			vector orientation;
			
			if (!scarecrowPositions)
			{
				for (i = 0; i < scarecrowCount; i++)
				{
					if (scarecrows && scarecrows[i])
					{
						Vector2 randomPos = GetRandomPointInCircle(radius);
						pos = Vector(position[0] + randomPos.x, position[1], position[2] + randomPos.y);
						orientation = Vector(Math.RandomFloatInclusive(0, 359), Math.RandomFloatInclusive(-2, 2), Math.RandomFloatInclusive(-2, 2));
						scarecrows[i].Setup(pos, orientation);
					}
				}
			}
			else
			{
				for (i = 0; i < scarecrowPositions.Count(); i++)
				{
					if (scarecrows && scarecrows[i])
					{
						pos = scarecrowPositions[i].ToVector();
						orientation = Vector(Math.RandomFloatInclusive(0, 359), Math.RandomFloatInclusive(-2, 2), Math.RandomFloatInclusive(-2, 2));
						scarecrows[i].Setup(pos, orientation);
					}
				}
			}
			
			Print("Scarecrows <" + name + "> reset.");
		}
	}
	
	void Update(float timeslice)
	{
		if (GetGame() && scarecrows)
		{
			int i;
			bool nobodyNear = true;
			
			array<Man> players = new array<Man>; 																				
			GetGame().GetPlayers(players);
			
			for (i = 0; i < players.Count(); i++)
			{
				PlayerBase player;
				Class.CastTo(player, players.Get(i));
				
				if (player.IsAlive())
				{
					vector playerPos = player.GetPosition();
					float distance = vector.Distance(playerPos, position);
					
					if (distance <= resetRadius * 1.5)
					{
						if (!active)
						{
							Print("Scarecrows <" + name + "> active at " + position + ".");
						}
					
						nobodyNear = false;
						active = true;
						break;
					}
				}
			}
			
			if (nobodyNear && active)
			{
				SetupScarecrows();
				active = false;
				Print("Scarecrows <" + name + "> inactive at " + position + ".");
			}
			
			for (i = 0; i < scarecrows.Count(); i++)
			{
				if (scarecrows && scarecrows[i])
				{
					scarecrows[i].Update(timeslice);
					
					if (active && scarecrows[i].InRange)
					{
						scarecrows[i].RequestPlayAmbient();
						scarecrows[i].RequestPlaySync();
					}
				}
			}
		}
	}
	
	void UpdateSounds(float timeslice)
	{	
		if (GetGame() && scarecrows)
		{
			int i;
			array<ab_Scarecrow> scarecrowsTransmitting = new array<ab_Scarecrow>();
			array<ab_Scarecrow> scarecrowsInRange = new array<ab_Scarecrow>();
			lastCreepySoundTimeslice += timeslice;
			
			if (lastCreepySoundTimeslice >= minTimeBetweenCreepySound)
			{
				lastCreepySoundTimeslice = 0;	
				
				for (i = 0; i < scarecrows.Count(); i++)
				{
					if (scarecrows && scarecrows[i] && scarecrows[i].InRange)
					{
						scarecrowsInRange.Insert(scarecrows[i]);
					}
				}
				
				if (scarecrowsInRange.Count() > 0 && Math.RandomFloat01() < creepySoundChance)
				{
					scarecrowsInRange.GetRandomElement().RequestPlayCreepy();
				}
			}
			
			for (i = 0; i < scarecrows.Count(); i++)
			{
				if (scarecrows && scarecrows[i] && scarecrows[i].IsTransmitting)
				{
					scarecrowsTransmitting.Insert(scarecrows[i]);
				}
			}
			
			for (i = 0; i < Math.RandomIntInclusive(1, 4); i++)
			{
				if (scarecrowsTransmitting.Count() > 0)
				{
					ab_Scarecrow scarecrowPlay = scarecrowsTransmitting.GetRandomElement();
					scarecrowPlay.RequestPlayAmbient();
					scarecrowsTransmitting.RemoveItem(scarecrowPlay);
				}
			}
		}
	}
	
	Vector2 GetRandomPointInCircle(float Radius)
	{
		float a = Math.RandomFloat01() * 2 * Math.PI;
		float r = Radius * Math.Sqrt(Math.RandomFloat01());
		float x = r * Math.Cos(a);
		float y = r * Math.Sin(a);
		return new Vector2(x, y);
	}
}