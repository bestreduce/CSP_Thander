
void WhrDeleteSeaEnvironment()
{
	DeleteAttribute(&Sea,"");
}
	
void WhrCreateSeaEnvironment()
{
	aref	aCurWeather = GetCurrentWeather();
	aref	aSea; makearef(aSea,aCurWeather.Sea);
	aref	aSea2; makearef(aSea2, aCurWeather.Sea2);
	aref	aCommon; makearef(aCommon, WhrCommonParams.Sea);
	int   i;
	float fMaxSeaHeight;

	if (CheckAttribute(&Sea,"MaxSeaHeight")) { fMaxSeaHeight = stf(Sea.MaxSeaHeight); }
	if(fMaxSeaHeight < 0.0) return;
	DeleteAttribute(&Sea,"");

	Sea.Clear = "";

	Sea.Transparency = Whr_GetFloat(aSea,"Transparency");
	Sea.FrenelCoefficient = Whr_GetFloat(aSea,"FrenelCoefficient");
	Sea.WaterReflection = Whr_GetFloat(aSea,"WaterReflection");
	Sea.WaterAttenuation = Whr_GetFloat(aSea,"WaterAttenuation");

	// Sea.Sea2.BumpScale = Whr_GetFloat(aSea2, "BumpScale");

	ref mchr = GetMainCharacter();
	string sLocation = mchr.location;

	float FogDensity = 5.0;
	float FogSeaDensity = 5.0;

	if (FindLocation(sLocation) != -1 && !bCabinStarted)
		{
			Sea.LodScale = 32.0;
			Sea.MaxVertices = 2000;
			Sea.MaxIndices = 2600;
			Sea.MaxWaveDistance = 10.0;
			Sea.MaxDim = 65536 * 8;
			Sea.MinDim = 128;
			Sea.GridStep = GridStepPC*5.0;
			if (CheckAttribute(aCurWeather, "Storm") && sti(aCurWeather.Storm) == true)
			{
				fMaxSeaHeight = 4.5;
			}
			else
            {
				fMaxSeaHeight = 1.5;
				// fMaxSeaHeight = 200.0;
			}
			FogDensity = 10.0;
			FogSeaDensity = 10.0;

			Sea.Sea2.LodScale = 0.5;
			Sea.Sea2.GridStep = 0.05;
			Sea.Sea2.BumpScale = 0.3;
		}
		else
		{
        if (CheckAttribute(aCurWeather, "Storm") && sti(aCurWeather.Storm) == true)
		{
		    SetSeaSettings();
			fMaxSeaHeight = 200.0;
			Log_TestInfo("Шторм включен, волны по Мах разрешены");
		}
		else
		{
			i = FindIsland(sLocation);
			if ( i != -1)
			{
				SetSeaSettings();
				fMaxSeaHeight = SetMaxSeaHeight(i);
				// fMaxSeaHeight = 200.0;
			}
			else
			{
				SetSeaSettings();
				fMaxSeaHeight = 200.0;
			}
		}
	}
	Sea.Lights = aCurWeather.Lights;

	Sea.Water.Color = Whr_GetColor(aSea,"Water.Color");

	Sea.Sun.Color = Whr_GetColor(aCurWeather,"Sun.Color");
	Sea.Sun.HeightAngle = Whr_GetFloat(aCurWeather,"Sun.HeightAngle");
	Sea.Sun.AzimuthAngle = Whr_GetFloat(aCurWeather,"Sun.AzimuthAngle");

	string sCurFog = Whr_GetCurrentFog();
	Sea.Fog.Color = Whr_GetColor(aCurWeather, sCurFog + ".Color");
	Sea.Fog.Enable = Whr_GetLong(aCurWeather, sCurFog + ".Enable");
	Sea.Fog.Start = Whr_GetFloat(aCurWeather, sCurFog + ".Start");
	Sea.Fog.Density = Whr_GetFloat(aCurWeather, sCurFog + ".Density") * FogDensity;
	Sea.Fog.SeaDensity = Whr_GetFloat(aCurWeather, sCurFog + ".SeaDensity") * FogSeaDensity;
	
	Sea.Pena.Color = Whr_GetColor(aSea,"Pena.Color");
	Sea.Pena.DepthSmall = 20.0;
	Sea.Pena.DepthBig = 20.0;
	Sea.Pena.BigIslandMultiply = Whr_GetFloat(aCommon, "Pena.BigIslandMultiply");
	Sea.Pena.SmallIslandMultiply = Whr_GetFloat(aCommon, "Pena.SmallIslandMultiply");
	
	Sea.Bump.Dir = Whr_GetString(aSea, "Bump.Dir");
	Sea.Bump.Tile = Whr_GetFloat(aSea, "Bump.Tile");
	Sea.Bump.Ang = Whr_GetFloat(aSea, "Bump.Ang");
	Sea.Bump.Speed = Whr_GetFloat(aSea, "Bump.Speed");
	Sea.Bump.Scale = Whr_GetFloat(aSea, "Bump.Scale");
	Sea.Bump.AnimSpeed = Whr_GetFloat(aSea, "Bump.AnimSpeed");
	Sea.Bump.MipLevels = 4;
	Sea.Bump.Size = 128;

	Sea.GF2MX.BumpDir = Whr_GetString(aSea, "GF2MX.Bump.Dir");
	Sea.GF2MX.BumpTile = Whr_GetFloat(aSea, "GF2MX.Bump.Tile");
	Sea.GF2MX.BumpAnimSpeed = Whr_GetFloat(aSea, "GF2MX.Bump.AnimSpeed");
	Sea.GF2MX.WaterColor = Whr_GetColor(aSea, "GF2MX.Water.Color");
	Sea.GF2MX.SkyColor = Whr_GetColor(aSea, "GF2MX.Sky.Color");

	Sea.GF3.BumpDir = Whr_GetString(aSea, "Bump.Dir");
	Sea.GF3.BumpTile = Whr_GetFloat(aSea, "Bump.Tile");
	Sea.GF3.BumpAnimSpeed = Whr_GetFloat(aSea, "Bump.AnimSpeed");
	Sea.GF3.WaterColor = Whr_GetColor(aSea, "Water.Color");
	Sea.GF3.SkyColor = Whr_GetColor(aSea, "Sky.Color");

	// Sun road section
	Sea.Road.Start = Whr_GetFloat(aSea, "SunRoad.Start");
	Sea.Road.Color1 = Whr_GetColor(aSea, "SunRoad.Color1");
	Sea.Road.Color2 = Whr_GetColor(aSea, "SunRoad.Color2");
	Sea.Road.Power = Whr_GetFloat(aSea, "SunRoad.Power");

	if (CheckAttribute(aSea, "SunRoad.Special"))
	{
		Sea.Sun.HeightAngle = Whr_GetFloat(aSea, "SunRoad.Special.HeightAngle");
		Sea.Sun.AzimuthAngle = Whr_GetFloat(aSea, "SunRoad.Special.AzimuthAngle");
	}
	Sea.CubeMap.Size = 2048;	
	Sea.CubeMap.VectorsSize = 1024;
	
	Sea.CubeMap.Format = "r5g6b5";

	Sea.Sky.Color = Whr_GetColor(aSea, "Sky.Color");

	Sea.Sea2.FoamEnable = false;
	if(FindLocation(sLocation) == -1)
	{
		WhrSetNewSea(fWeatherSpeed);
		Sea.Sea2.FoamEnable = true;
		if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
		Sea.Fog.SeaDensity = 0.0025;
		Sea.Sea2.Reflection = 0.5;
		Sea.Sea2.Transparency = 0.3;
		}
	} else {
		ref loc;
		loc = &Locations[FindLocation(sLocation)];
		if(loc.type == "seashore" 
			|| loc.type == "x_seashore"
			|| loc.type == "questisland"
			|| loc.type == "mayak"){
		fMaxSeaHeight = 1.1;
		WhrSetNewSea(fWeatherSpeed);
		Sea.Sea2.FoamEnable = true;
		Sea.Sea2.Reflection = 0.8;
		if( GetTime() >= 23.0 || GetTime() < 6.0 ) {
			Sea.Sea2.Transparency = 0.5;
			Sea.Sea2.Reflection = 0.3;
			Sea.Sea2.WaterColor = argb(0,0,30,40);
		} else {
		if( GetTime() >= 6.0 && GetTime() < 9.0 ) {
			Sea.Sea2.Transparency = 1.4;
			Sea.Sea2.WaterColor = argb(0,0,120,140);
		} else {
		if( GetTime() >= 9.0 && GetTime() < 10.0 ) {
			Sea.Sea2.Transparency = 1.4;
			Sea.Sea2.WaterColor = argb(0,0,150,170);
		} else {
		if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
			Sea.Sea2.Transparency = 1.4;
			Sea.Sea2.WaterColor = argb(0,0,200,225);
			if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				Sea.Fog.SeaDensity = 0.02;
				Sea.Sea2.Reflection = 0.3;
				Sea.Sea2.Transparency = 1.0;
				Sea.Sea2.WaterColor = argb(0,50,235,215);
			}
		} else {
		if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
			Sea.Sea2.Transparency = 1.0;
			Sea.Sea2.WaterColor = argb(0,0,150,170);
		} else {
		if( GetTime() >= 21.0 && GetTime() < 23.0 ) {
			Sea.Sea2.Transparency = 1.0;
			Sea.Sea2.WaterColor = argb(0,0,110,130);	
		}}}}}}}
	} else {
		if(loc.type == "fort"){
		fMaxSeaHeight = 1.1;
		WhrSetNewSea(fWeatherSpeed);
		Sea.Fog.SeaDensity = 0.001;
		Sea.Sea2.Scale1 = 3.0;
		Sea.Sea2.Scale2 = 3.0;
		Sea.Sea2.FoamEnable = true;
		Sea.Sea2.FoamK = 1.5;
		Sea.Sea2.FoamUV = 1.0;
		Sea.Sea2.Reflection = 0.6;
		Sea.Sea2.Transparency = 0.6;
		if( GetTime() >= 23.0 || GetTime() < 7.0 ) {
			Sea.Sea2.FoamK = 1.0;	
			Sea.Sea2.WaterColor = argb(0,0,30,40);
		} else {
		if( GetTime() >= 7.0 && GetTime() < 9.0 ) {
			Sea.Sea2.FoamK = 1.0;
			Sea.Sea2.WaterColor = argb(0,0,80,100);
		} else {
		if( GetTime() >= 9.0 && GetTime() < 10.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,130,150);
		} else {
		if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
			Sea.Sea2.WaterColor = argb(0,0,150,170);
			if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				Sea.Fog.SeaDensity = 0.002;
				Sea.Sea2.Reflection = 0.3;
				Sea.Sea2.Transparency = 0.3;
				Sea.Sea2.WaterColor = argb(0,0,100,120);
			}
		} else {
		if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
			Sea.Sea2.FoamK = 1.25;
			Sea.Sea2.WaterColor = argb(0,0,70,90);	
		} else {
		if( GetTime() >= 21.0 && GetTime() < 23.0 ) {
			Sea.Sea2.FoamK = 1.0;
			Sea.Sea2.WaterColor = argb(0,0,50,70);	
		}}}}}}}
		} else {
		if(loc.type == "cave"
			|| loc.type == "Dungeon"){
		fMaxSeaHeight = 1.1;
		WhrSetNewSea(fWeatherSpeed);
		Sea.Sea2.FoamEnable = true;
		Sea.Sea2.Reflection = 0.6;
		Sea.Sea2.Transparency = 1.3;
		if( GetTime() >= 23.0 || GetTime() < 7.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,15,20);
		} else {
		if( GetTime() >= 7.0 && GetTime() < 9.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,15,20);
		} else {
		if( GetTime() >= 9.0 && GetTime() < 10.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,15,20);
		} else {
		if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
			Sea.Sea2.WaterColor = argb(0,0,15,20);
		} else {
		if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
			Sea.Sea2.WaterColor = argb(0,0,15,20);	
		} else {
		if( GetTime() >= 21.0 && GetTime() < 23.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,15,20);
		}}}}}}}
	} else {
		if(loc.type == "town"){
		fMaxSeaHeight = 1.1;
		WhrSetNewSea(fWeatherSpeed);
		Sea.Sea2.FoamEnable = true;
		Sea.Sea2.Reflection = 0.6;
		Sea.Sea2.Transparency = 1.3;
		if( GetTime() >= 23.0 || GetTime() < 7.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,30,30);
		} else {
		if( GetTime() >= 7.0 && GetTime() < 9.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,75,110);
		} else {
		if( GetTime() >= 9.0 && GetTime() < 10.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,90,140);
		} else {
		if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
			Sea.Sea2.WaterColor = argb(0,0,160,200);
			if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				Sea.Fog.SeaDensity = 0.01;
				Sea.Sea2.Reflection = 0.3;
				Sea.Sea2.Transparency = 0.3;
				Sea.Sea2.WaterColor = argb(0,0,110,120);
			}
		} else {
		if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
			Sea.Sea2.WaterColor = argb(0,0,110,120);	
		} else {
		if( GetTime() >= 21.0 && GetTime() < 23.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,60,70);
		}}}}}}}
	} else {
		WhrSetNewSea(fWeatherSpeed);
		//fMaxSeaHeight = 1.1;
		Sea.Sea2.Reflection = 0.6;
		Sea.Sea2.Transparency = 0.3;
		if( GetTime() >= 23.0 || GetTime() < 7.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,30,30);
		} else {
		if( GetTime() >= 7.0 && GetTime() < 9.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,110,110);
		} else {
		if( GetTime() >= 9.0 && GetTime() < 10.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,140,140);
		} else {
		if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
			Sea.Sea2.WaterColor = argb(0,0,160,200);
			if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				Sea.Fog.SeaDensity = 0.01;
				Sea.Sea2.Reflection = 0.3;
				Sea.Sea2.Transparency = 0.3;
				Sea.Sea2.WaterColor = argb(0,0,110,120);
			}
		} else {
		if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
			Sea.Sea2.WaterColor = argb(0,0,110,120);	
		} else {
		if( GetTime() >= 21.0 && GetTime() < 23.0 ) {
			Sea.Sea2.WaterColor = argb(0,0,60,70);	
		}}}}}}
	}

	Sea.Sea2.SimpleSea = sti(InterfaceStates.SimpleSea);

	if(CheckAttribute(aSea2, "LodScale"))
        Sea.Sea2.LodScale = Whr_GetFloat(aSea2, "LodScale");
    if(CheckAttribute(aSea2, "GridStep"))
        Sea.Sea2.GridStep = Whr_GetFloat(aSea2, "GridStep");

	Sea.MaxSeaHeight = fMaxSeaHeight;
	Sea.isDone = "";
	//Log_TestInfo("Whether Sea.MaxSeaHeight " + Sea.MaxSeaHeight);

	if (bSeaActive && !bAbordageStarted)
	{
		pchar.SystemInfo.ScaleSeaHeight = GetScaleSeaHeight();
	}
}

void SetSeaSettings()
{
	Sea.LodScale = LodScale;
	Sea.MaxVertices = MaxVertices;
	Sea.MaxIndices = MaxIndices;
	Sea.MaxWaveDistance = MaxWaveDistance;
	Sea.MaxDim = 65536 * 8;
	Sea.MinDim = 128;
	Sea.GridStep = 0.1 + 0.1 * (1.0 - stf(InterfaceStates.SeaDetails));

	Sea.Sea2.LodScale = 0.5;
	Sea.Sea2.GridStep = 0.07 + 0.1 * (1.0 - stf(InterfaceStates.SeaDetails));
}

void SetSeaGridStep(float SeaDetails)
{
	if (!IsEntity(&Sea)) { return; }

	ref mchr = GetMainCharacter();
	string sLocation = mchr.location;

	// if current location is land - return
	if(FindLocation(sLocation) != -1)
	{
		if(CheckAttribute(&locations[FindLocation(sLocation)], "fastreload"))
		{
			return;
		}
	}

	Sea.Sea2.GridStep = 0.07 + 0.1 * (1.0 - SeaDetails);

	Sea.Sea2.SimpleSea = sti(InterfaceStates.SimpleSea);
}

float GetScaleSeaHeight()
{
	float fMaxSeaHeight = 0.0;

	if (CheckAttribute(&Sea, "MaxSeaHeight")) { fMaxSeaHeight = stf(Sea.MaxSeaHeight); }
	
	aref arWeath = GetCurrentWeather();
	float fAmp1, fAmp2;
	
	fAmp1 = stf(arWeath.Sea2.Amp1);
	fAmp2 = stf(arWeath.Sea2.Amp2);
	
	float fScale;
	if (fMaxSeaHeight >= (fAmp1 + fAmp2))
	{
		fScale = 1.0; 
	}
	else
	{
		fScale = fMaxSeaHeight / (fAmp1 + fAmp2);
	}

	fAmp1 = fAmp1 * fScale;
	fAmp2 = fAmp2 * fScale;
		
	return (fAmp1 + fAmp2) / 2.0;
}