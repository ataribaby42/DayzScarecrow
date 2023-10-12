ab_ScarecrowManager g_ab_ScarecrowManager;
ab_ScarecrowManager Get_ab_ScarecrowManager()
{
	if (!g_ab_ScarecrowManager) 
	{
		g_ab_ScarecrowManager = ab_ScarecrowManager.Cast(GetGame().CreateObject("ab_ScarecrowManager", "0 0 0"));
	}
	return g_ab_ScarecrowManager;
}

class ab_ScarecrowManager extends ScriptedEntity
{
	private ref array<ref ab_ScarecrowController> controllers = new array<ref ab_ScarecrowController>();
	private float ab_ScarecrowsTimeslice;
	private float ab_ScarecrowsSoundTimeslice;
	
	void ab_ScarecrowManager()
	{
		Print("Scarecrow Manager started.");
		SetEventMask(EntityEvent.FRAME);
	}

	void ~ab_ScarecrowManager()
	{
		Print("Scarecrow Manager stopped.");
		ClearEventMask(EntityEvent.FRAME);
	}
	
	override void EOnFrame(IEntity other, float timeSlice)
    {
		if (GetGame() && GetGame().IsServer())
		{
			if (GetGame() && GetGame().IsServer())	
			{
				ab_ScarecrowsTimeslice += timeSlice;
				
				if (ab_ScarecrowsTimeslice >= 5.0)
				{
					Get_ab_ScarecrowManager().Update(ab_ScarecrowsTimeslice);
					ab_ScarecrowsTimeslice = 0;	
				}
				
				ab_ScarecrowsSoundTimeslice += timeSlice;
				
				if (ab_ScarecrowsSoundTimeslice >= 2.0)
				{
					Get_ab_ScarecrowManager().UpdateSounds(ab_ScarecrowsSoundTimeslice);
					ab_ScarecrowsSoundTimeslice = 0;	
				}
			}
		}
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