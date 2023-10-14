// for singleplayer / offline mode
modded class MissionGameplay
{
	private float ab_ScarecrowsTimeslice;
	private float ab_ScarecrowsSoundTimeslice;
	
	void MissionGameplay()
	{

	}
	
	void ~MissionGameplay() 
	{
		
	}
	
	override void OnInit()
	{
		super.OnInit();
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		if (GetGame() && GetGame().IsServer())	
		{
			ab_ScarecrowsTimeslice += timeslice;
			
			if (ab_ScarecrowsTimeslice >= 5.0)
			{
				Get_ab_ScarecrowManager().Update(ab_ScarecrowsTimeslice);
				ab_ScarecrowsTimeslice = 0;	
			}
			
			ab_ScarecrowsSoundTimeslice += timeslice;
			
			if (ab_ScarecrowsSoundTimeslice >= 2.0)
			{
				Get_ab_ScarecrowManager().UpdateSounds(ab_ScarecrowsSoundTimeslice);
				ab_ScarecrowsSoundTimeslice = 0;	
			}
		}
	}
}