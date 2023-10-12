static ref array<string> ab_Scarecrow_Stealable_Items = {};

modded class PlayerBase extends ManBase
{
	private float ab_ScarecrowKillTimer;
	private float ab_ScarecrowUncoTimer;
	private bool ab_ScarecrowUnco;
	private string ab_ScarecrowKillName;
	private bool ab_ScarecrowKillRequested;
	
	override void Init()
	{
		super.Init();
		
		ab_ScarecrowUnco = false;
		ab_ScarecrowKillRequested = false;
	}
	
	override void EOnFrame(IEntity other, float timeSlice)
	{
		super.EOnFrame(other, timeSlice);
		
		if (GetGame() && GetGame().IsServer())	
		{
			if (ab_ScarecrowKillRequested)
			{
				if ((GetGame().GetTime() / 1000) >= ab_ScarecrowKillTimer)
				{
					ab_ScarecrowKillRequested = false;
					PlayerIdentity identity = GetIdentity();
					
					if (identity)
					{
						Print("Player <" + GetIdentity().GetName() + "> has been caught by scarecrow <" + ab_ScarecrowKillName + ">.");
					}
					else
					{
						Print("Player <unknown> has been caught by scarecrow <" + ab_ScarecrowKillName + ">.");
					}
					
					if (GetAllowDamage())
					{
						float currenthealth = GetHealth("GlobalHealth", "Health");
						currenthealth = currenthealth - Math.RandomFloatInclusive(5, 10);
						SetHealth("GlobalHealth", "Health", currenthealth);
						RequestUnconsciousness(true);
						ab_ScarecrowRandomItemSteal(ab_ScarecrowKillName);
						ab_ScarecrowUncoTimer = (GetGame().GetTime() / 1000) + 10;
						ab_ScarecrowUnco = true;
					}

					ab_ScarecrowKillName = "";
				}
			}
			
			if (ab_ScarecrowUnco)
			{
				if ((GetGame().GetTime() / 1000) >= ab_ScarecrowUncoTimer)
				{
					RequestUnconsciousness(false);
					ab_ScarecrowUnco = false;
				}
			}
		}
	}
	
	private bool ab_ScarecrowIsStealableItem(ItemBase item)
	{
		foreach (string type : ab_Scarecrow_Stealable_Items)
		{
			if (item && item.IsKindOf(type))
			{
				return true;
			}
		}

		return false;
	}
	
	private void ab_ScarecrowRandomItemSteal(string stealer)
	{
		if (ab_Scarecrow_Stealable_Items.Count() == 0) return;
		
		array<EntityAI> itemsArray = new array<EntityAI>;
		array<ItemBase> itemsStealable = new array<ItemBase>;;
		ItemBase item;
		
		GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
		
		for (int i = 0; i < itemsArray.Count(); i++)
		{
			Class.CastTo(item, itemsArray.Get(i));
			
			if (item && !item.IsInherited(SurvivorBase))
			{
				if (ab_ScarecrowIsStealableItem(item))
				{
					itemsStealable.Insert(item);
				}
			}
		}
		
		if (itemsStealable.Count() > 0)
		{
			item = itemsStealable.GetRandomElement();
			PlayerIdentity identity = GetIdentity();
			GetInventory().LocalDestroyEntity(item);
			
			if (identity)
			{
				Print("Scarecrow <" + stealer + "> stealed <" + item.GetType() + "> from Player <" + GetIdentity().GetName() + ">.");
			}
			else
			{
				Print("Scarecrow <" + stealer + "> stealed <" + item.GetType() + "> from Player <unknown>.");
			}
		}
	}

	void RequestScarecrowKill(string name)
	{
		ab_ScarecrowKillTimer = (GetGame().GetTime() / 1000) + 0.5;
		ab_ScarecrowKillRequested = true;
		ab_ScarecrowKillName = name;
	}
};