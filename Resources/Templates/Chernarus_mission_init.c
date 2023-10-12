void SpawnScarecrow()
{
	ab_Scarecrow_Stealable_Items.Clear();
	ab_Scarecrow_Stealable_Items.Insert("NVGoggles");
	ab_Scarecrow_Stealable_Items.Insert("GasMask_Filter");
	
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
	Get_ab_ScarecrowManager().CreatePredefinedScarecrowController("Veresnik Military Base", "4537.540039 318.433014 8297.910156", 500, scarecrowPositions );
}

void main()
{
	/*
	
		Your original main() content here
	
	*/
	
	SpawnScarecrow();
};