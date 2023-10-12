# Scarecrow
<p>Scarecrow creature mod for Dayz, sort of Designators and Will-o'-the-Wisp crossover. Scarecrow tries to catch (by teleporting) player when he turns back to it and charge into him causing unconscious state for 10 seconds, small random damage and optionally steals one random item from player. After charge, Scarecrow is idle for 20 seconds giving 10s for recovery and escape. It is possible to hide from it or just run away. It makes player aware of its presence with crow sounds.</p>
<p>https://youtu.be/eZJKgZt-3FA</p>
<p>Scarecrow code has been written reusing some parts from my Designators and Will-o'-the-Wisp mods. All sounds are from free sources. Scarecrow model is vanilla dayz model.</p>

### INSTALLATION AND SETUP
This is both server and client mod. Client needs just subscribe to mod or adds it manually. 

At server side open your mission Init.c and find void main(). Put following code at the end of main function.

```
Get_ab_ScarecrowManager().CreateRandomScarecrowController("Shachovka Forrest", "9089.700195 315.509003 7558.310059", 500, 50, Math.RandomIntInclusive(1, 3));

array<string> scarecrowPositions = {
"4464.140137 315.640991 8250.669922",
"4456.279785 315.337006 8264.139648",
"4424.439941 314.873993 8269.299805",
"4472.290039 315.575012 8286.809570",
"4456.529785 315.414001 8315.379883",
"4491.459961 317.023987 8273.509766",
"4486.479980 316.333008 8326.230469",
"4504.129883 317.686005 8297.540039",
"4532.600098 318.393005 8298.469727",
"4547.910156 319.480988 8345.040039",
"4566.259766 319.893005 8382.780273",
"4574.899902 319.507996 8330.860352",
"4572.330078 319.339996 8351.759766",
"4545.560059 319.109009 8316.230469",
"4531.149902 317.933990 8278.950195",
"4561.479980 319.721008 8249.519531",
"4591.509766 320.345001 8242.500000",
"4575.390137 319.764008 8292.790039",
"4571.290039 319.854004 8221.280273",
"4553.089844 319.207001 8287.849609",
"4471.229980 315.656006 8301.559570"
};
Get_ab_ScarecrowManager().CreatePredefinedScarecrowController("Veresnik Military Base", "4537.540039 318.433014 8297.910156", 500, scarecrowpPositions );
```

### API
**_Get_ab_ScarecrowManager().CreateRandomScarecrowController(string name, vector position, float resetRadius, float radius, int scarecrowCount)_**

Creates circular Scarecrow infested area with size of radius at position and randomly fills it with scarecrowCount Scarecrows. Area resets everytime no players are inside resetRadius. You can name area with name parameter to see it in logs.

**_Get_ab_ScarecrowManager().CreatePredefinedScarecrowController(string name, vector position, float resetRadius, ref array<string> scarecrowPositions)_**
  
Creates predefined Scarecrow infested area with logical center position and fills it with Scarecrows from scarecrowPositions string array that contains coords in vector format. Area resets everytime no players are inside resetRadius. You can name area with name parameter to see it in logs.

**_ab_Scarecrow_Stealable_Items_**
Static string array that defines stealable items that Scarecrow is allowed to steal from knocked down player after successful attack. Array is initialized and empty by default.
In your init.c before spawning any Scarecrow set items with following code:

```
ab_Scarecrow_Stealable_Items.Clear();
ab_Scarecrow_Stealable_Items.Insert("NVGoggles");
ab_Scarecrow_Stealable_Items.Insert("BandageDressing");
ab_Scarecrowp_Stealable_Items.Insert("DisinfectantSpray");
ab_Scarecrow_Stealable_Items.Insert("DisinfectantAlcohol");
```

### CREDITS
<ul>
  <li>Code by ataribaby.</li>
</ul>

### LICENSE
Mod is open source and you are free to modify, repack and publish. If you fix or enhance it please consider push it to me for intergration into official version.

Steam Workshop link: https://steamcommunity.com/sharedfiles/filedetails/?id=3048316138
