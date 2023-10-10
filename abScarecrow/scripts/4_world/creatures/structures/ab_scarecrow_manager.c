static ref ab_ScarecrowManager g_ab_ScarecrowManager;
static ref ab_ScarecrowManager Get_ab_ScarecrowManager()
{
	if (!g_ab_ScarecrowManager) 
	{
		g_ab_ScarecrowManager = new ref ab_ScarecrowManager();
	}
	return g_ab_ScarecrowManager;
}

class ab_ScarecrowManager
{
	private ref array<ref ab_ScarecrowController> controllers = new array<ref ab_ScarecrowController>();
	private bool lessIntrusiveAmbientSounds = false;
	
	void ab_ScarecrowManager()
	{
		Print("Scarecrow Manager started.");
	}

	void ~ab_ScarecrowManager()
	{
		Print("Scarecrow Manager stopped.");
	}
	
	void SetLessIntrusiveAmbientSounds(bool lessIntrusive)
	{
		lessIntrusiveAmbientSounds = lessIntrusive;
		
		if(lessIntrusiveAmbientSounds)
		{
			Print("Scarecrow Manager LessIntrusiveAmbientSounds set to ON.");
		}
		else
		{
			Print("Scarecrow Manager LessIntrusiveAmbientSounds set to OFF.");
		}
	}
	
	bool GetLessIntrusiveAmbientSounds()
	{
		return lessIntrusiveAmbientSounds;
	}

	void CreateRandomScarecrowController(string name, vector position, float resetRadius, float radius, int scarecrowCount)
	{
		if (controllers)
		{
			controllers.Insert(new ref ab_ScarecrowController(name, position, resetRadius, radius, scarecrowCount, NULL));
		}
	}
	
	void CreatePredefinedScarecrowController(string name, vector position, float resetRadius, ref array<string> scarecrowPositions)
	{
		if (controllers)
		{
			controllers.Insert(new ref ab_ScarecrowController(name, position, resetRadius, 0, scarecrowPositions.Count(), scarecrowPositions));
		}
	}
	
	void Update(float timeslice)
	{
		if (controllers)
		{
			for (int i = 0; i < controllers.Count(); i++)
			{
				if (controllers && controllers[i])
				{
					controllers[i].Update(timeslice);
				}
			}
		}
	}
	
	void UpdateSounds(float timeslice)
	{
		if (controllers)
		{
			for (int i = 0; i < controllers.Count(); i++)
			{
				if (controllers && controllers[i])
				{
					controllers[i].UpdateSounds(timeslice);
				}
			}
		}
	}
}