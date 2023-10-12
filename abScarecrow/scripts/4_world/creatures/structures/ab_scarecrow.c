class ab_Scarecrow
{
	private string name;
	private float scarecrowModelHeightOffset = 0.5;
	private float scarecrowModelLosCheckOriginHeightOffset = 1.0;
	private float transmittingRange = 100;
	private float detectionRange = 40;
	private float teleportRange = 10;
	private float teleportKillRange = 10;
	private const ref array<string> scarecrowModels = {"ab_scarecrow_model_1"};
	private Object scarecrowObject;
	private vector areaPosition;
	private float areaResetRadius;
	private ab_scarecrow_model_base scarecrowObjectBase;
	bool InRange = false; // Any player is within detectionRange regardless of LOS and FOV checks - used for creepy random sounds
	bool IsTransmitting = false; // Any player is within transmittingRange regardless of LOS and FOV checks - used for ambient random sounds
	bool IsTeleportBlocked = false; // Scarecrow teleportation is blocked by any player that looks at it with clear LOS within detectionRange or scarecrow wandered outside scarecrows area
	private float attackTimeoutTimeslice;
	private bool attackTimeout;
	
	void ab_Scarecrow(string Name, vector AreaPosition, float AreaResetRadius)
	{
		if (GetGame())
		{
			this.name = Name;
			attackTimeoutTimeslice = 0;
			attackTimeout = false;
			this.areaPosition = AreaPosition;
			this.areaResetRadius = AreaResetRadius;
			scarecrowObject = GetGame().CreateObject(scarecrowModels.GetRandomElement(), areaPosition);
			scarecrowObjectBase = ab_scarecrow_model_base.Cast(scarecrowObject);
		}
	}
	
	void ~ab_Scarecrow()
	{
		
	}
	
	void Setup(vector position, vector orientation)
	{
		if (GetGame())
		{
			float y = GetGame().SurfaceY(position[0], position[2]);
			scarecrowObject.SetPosition(Vector(position[0], y + scarecrowModelHeightOffset, position[2]));
			scarecrowObject.SetOrientation(orientation);
			InRange = false;
			IsTransmitting = false;
			IsTeleportBlocked = false;
			attackTimeoutTimeslice = 0;
			attackTimeout = false;
		}
	}
	
	void RequestPlaySync()
	{
		if (scarecrowObjectBase)
		{
			scarecrowObjectBase.RequestPlaySync();
		}
	}
	
	void RequestPlayTeleport()
	{
		if (scarecrowObjectBase)
		{
			scarecrowObjectBase.RequestPlayTeleport();
		}
	}
	
	void RequestPlayAmbient()
	{
		if (scarecrowObjectBase)
		{
			scarecrowObjectBase.RequestPlayAmbient();
		}
	}
	
	void RequestPlayCreepy()
	{
		if (scarecrowObjectBase)
		{
			scarecrowObjectBase.RequestPlayCreepy();
		}
	}
	
	bool LosCheck(Object fromObj, PlayerBase toObj)
	{
		if (fromObj && toObj)
		{
			vector fromPos = fromObj.GetPosition();
			vector begPos = Vector(fromPos[0], fromPos[1] + scarecrowModelLosCheckOriginHeightOffset, fromPos[2]);
			vector endPos = toObj.GetPosition();
			vector contactPos;
			vector contactDir;
			int contactComponent; 
			set<Object> results = new set<Object>;
			Object with = NULL; 
			Object ignore = scarecrowObject;  
			bool sorted = false; 
			bool ground_only = false;  
			int iType = 2;
			float radius = 0;
			
			int bone_index = toObj.GetBoneIndexByName("Head");
			vector headPosition= toObj.GetBonePositionWS(bone_index);
			bone_index = toObj.GetBoneIndexByName("Pelvis");
			vector pelvisPosition= toObj.GetBonePositionWS(bone_index);
			
			/* 3D debug particle 
			vector hit_normal;
			hit_normal = contactDir.VectorToAngles();
			hit_normal[1] = hit_normal[1] + 90;
			Particle hitEnd = Particle.PlayInWorld(ParticleList.DEBUG_DOT, contactPos);
			hitEnd.SetOrientation(hit_normal);
			*/
			
			if (DayZPhysics.RaycastRV(begPos, endPos, contactPos, contactDir, contactComponent, results, with, ignore, sorted, ground_only, iType, radius))
			{
				if (results && results.Count() > 0 && results[0] == toObj)
				{
					return true;
				}
			}
			
			if (DayZPhysics.RaycastRV(begPos, pelvisPosition, contactPos, contactDir, contactComponent, results, with, ignore, sorted, ground_only, iType, radius))
			{
				if (results && results.Count() > 0 && results[0] == toObj)
				{
					return true;
				}
			}
			
			if (DayZPhysics.RaycastRV(begPos, headPosition, contactPos, contactDir, contactComponent, results, with, ignore, sorted, ground_only, iType, radius))
			{
				if (results && results.Count() > 0 && results[0] == toObj)
				{
					return true;
				}
			}
		}
		
		return false;
	}
	
	bool InPlayerFovCheck(PlayerBase playerObj, Object scarecrowObj, out vector orientation, out vector angles)
	{
		if (playerObj && scarecrowObj)
		{
			angles = vector.Direction(playerObj.GetPosition(), scarecrowObj.GetPosition()).Normalized().VectorToAngles();
			orientation = Vector(angles[0] + 25, Math.RandomFloatInclusive(-5, 5), Math.RandomFloatInclusive(-5, 5));
			int bone_index = playerObj.GetBoneIndexByName("Head");
			float bone_rot[4];
			playerObj.GetBoneRotationWS(bone_index, bone_rot);
			vector lookPosition= playerObj.GetBonePositionWS(bone_index);
			vector lookDirection = Math3D.QuatToAngles(bone_rot).AnglesToVector();
			float swap = lookDirection[0];
			lookDirection[0] = lookDirection[2];
			lookDirection[2] = swap;
			lookDirection[0] = -lookDirection[0];
			lookDirection[1] = -lookDirection[1];
			
			return IsPointInsideCone(lookPosition, lookDirection, scarecrowObj.GetPosition(), 35 * Math.DEG2RAD, detectionRange);
		}
		
		return false;
	}
	
	bool IsPointInsideCone(vector coneOrigin, vector coneDirection, vector point, float maxAngle, float maxDistance)
	{
		float distanceToConeOrigin = vector.Distance(coneOrigin, point);
		
		if (distanceToConeOrigin > maxDistance)
		{
			return false;
		}
		
		return Math3D.IntersectSphereCone(point, 0.1, coneOrigin, coneDirection, maxAngle);
	}
	
	void Update(float timeslice)
	{
		if (GetGame())
		{
			InRange = false;
			IsTransmitting = false;
			IsTeleportBlocked = false;
			int i;
			float distance = -1;
			vector orientation;
			vector angles;
			Object nearestPerson = NULL;
			vector position = scarecrowObject.GetPosition();
			array<Man> players = new array<Man>; 			
			
			if (attackTimeout)
			{
				attackTimeoutTimeslice += timeslice;
				
				if (attackTimeoutTimeslice >= 20)
				{
					attackTimeoutTimeslice = 0;
					attackTimeout = false;
				}
			}
			
			GetGame().GetPlayers(players);
			
			for (i = 0; i < players.Count(); i++)
			{
				PlayerBase playerCheck;
				Class.CastTo(playerCheck, players.Get(i));
				
				if (playerCheck.IsAlive())
				{
					vector playerPos = playerCheck.GetPosition();
					float distanceCheck = vector.Distance(playerPos, position);
					
					if (distanceCheck <= detectionRange)
					{
						bool inView = InPlayerFovCheck(playerCheck, scarecrowObject, orientation, angles);
						bool losCheck = LosCheck(scarecrowObject, playerCheck);
						
						if ((distance > distanceCheck || distance == -1) && !inView && losCheck)
						{
							distance = distanceCheck;
							nearestPerson = playerCheck;
						}
						
						if (inView && losCheck)
						{
							IsTeleportBlocked = true;	
						}
						
						InRange = true;
					}
					
					if (distanceCheck <= transmittingRange)
					{
						IsTransmitting = true;
					}
				}
			}
			
			if (nearestPerson)
			{
				PlayerBase playerTest = PlayerBase.Cast(nearestPerson);
				distanceCheck = vector.Distance(playerTest.GetPosition(), areaPosition);
						
				if (distanceCheck > areaResetRadius)
				{
					IsTeleportBlocked = true;
				}
			}

			if (!IsTeleportBlocked && nearestPerson && !attackTimeout)
			{
				PlayerBase player = PlayerBase.Cast(nearestPerson);
				float range;
				float x;
				float z;
				float y;
				
				if (distance <= teleportKillRange)
				{
					vector pos = player.GetPosition();
					angles[0] = angles[0] + 180;
					range = distance - 0.5;
					x = range * Math.Sin(angles[0] * Math.DEG2RAD);
					z = range * Math.Cos(angles[0] * Math.DEG2RAD);
					y = GetGame().SurfaceY(position[0] + x, position[2] + z);
					scarecrowObject.SetPosition(Vector(position[0] + x, pos[1] + scarecrowModelHeightOffset, position[2] + z));
					scarecrowObject.SetOrientation(orientation);
					attackTimeoutTimeslice = 0;
					attackTimeout = true;
					scarecrowObjectBase.RequestPlayKill();
					player.RequestScarecrowKill(name);
				}
				else
				{
					angles[0] = angles[0] + 180;
					range = teleportRange * Math.RandomFloatInclusive(0.5, 1);
					x = range * Math.Sin(angles[0] * Math.DEG2RAD);
					z = range * Math.Cos(angles[0] * Math.DEG2RAD);
					y = GetGame().SurfaceY(position[0] + x, position[2] + z);
					scarecrowObject.SetPosition(Vector(position[0] + x, y + scarecrowModelHeightOffset, position[2] + z));
					scarecrowObject.SetOrientation(orientation);
					scarecrowObjectBase.RequestPlayTeleport();
				}
			}
		}
	}
}