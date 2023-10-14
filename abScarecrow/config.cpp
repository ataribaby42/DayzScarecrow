class CfgPatches
{
	class abScarecrow
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class abScarecrow
	{
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"abScarecrow/scripts/3_game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"abScarecrow/scripts/4_world"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"abScarecrow/scripts/5_mission"
				};
			};
		};
	};
};
class CfgVehicles
{
	class HouseNoDestruct;
	class ab_scarecrow_model_base: HouseNoDestruct
	{
	};
	class ab_scarecrow_model_1: ab_scarecrow_model_base
	{
		scope=2;
		storageCategory=10;
		model="DZ\structures\Residential\Misc\Misc_Boogieman.p3d";
	};
};
class CfgSoundShaders
{
	class ab_scarecrow_sync_SoundShader
	{
		samples[]=
		{
			
			{
				"abScarecrow\sounds\sync.ogg",
				1
			}
		};
		range=200;
		volume=1.6;
	};
	class ab_scarecrow_teleport_SoundShader
	{
		samples[]=
		{
			
			{
				"abScarecrow\sounds\teleport1.ogg",
				1
			},
			
			{
				"abScarecrow\sounds\teleport2.ogg",
				1
			}
		};
		range=150;
		volume=1.8;
	};
	class ab_scarecrow_kill_SoundShader
	{
		samples[]=
		{
			
			{
				"abScarecrow\sounds\kill.ogg",
				1
			}
		};
		range=150;
		volume=5;
	};
	class ab_scarecrow_ambient_SoundShader
	{
		samples[]=
		{
			
			{
				"abScarecrow\sounds\ambient1",
				1
			},
			
			{
				"abScarecrow\sounds\ambient2",
				1
			},
			
			{
				"abScarecrow\sounds\ambient3",
				1
			},
			
			{
				"abScarecrow\sounds\ambient4",
				1
			},
			
			{
				"abScarecrow\sounds\ambient5",
				1
			}
		};
		range=300;
		volume=1.8;
	};
	class ab_scarecrow_creepy_SoundShader
	{
		samples[]=
		{
			
			{
				"abScarecrow\sounds\creepy1",
				1
			},
			
			{
				"abScarecrow\sounds\creepy2",
				1
			},
			
			{
				"abScarecrow\sounds\creepy3",
				1
			},
			
			{
				"abScarecrow\sounds\creepy4",
				1
			},
			
			{
				"abScarecrow\sounds\creepy5",
				1
			},
			
			{
				"abScarecrow\sounds\creepy6",
				1
			},
			
			{
				"abScarecrow\sounds\creepy7",
				1
			},
			
			{
				"abScarecrow\sounds\creepy8",
				1
			},
			
			{
				"abScarecrow\sounds\creepy9",
				1
			},
			
			{
				"abScarecrow\sounds\creepy10",
				1
			},
			
			{
				"abScarecrow\sounds\creepy11",
				1
			}
		};
		range=200;
		volume=1.8;
	};
};
class CfgSoundSets
{
	class ab_scarecrow_sync_SoundSet
	{
		soundShaders[]=
		{
			"ab_scarecrow_sync_SoundShader"
		};
	};
	class ab_scarecrow_teleport_SoundSet
	{
		soundShaders[]=
		{
			"ab_scarecrow_teleport_SoundShader"
		};
	};
	class ab_scarecrow_kill_SoundSet
	{
		soundShaders[]=
		{
			"ab_scarecrow_kill_SoundShader"
		};
	};
	class ab_scarecrow_ambient_SoundSet
	{
		soundShaders[]=
		{
			"ab_scarecrow_ambient_SoundShader"
		};
	};
	class ab_scarecrow_creepy_SoundSet
	{
		soundShaders[]=
		{
			"ab_scarecrow_creepy_SoundShader"
		};
	};
};
