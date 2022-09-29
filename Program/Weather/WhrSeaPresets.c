// -------------------------------------------------------------
// Mett: настройки мор¤
// Sith: доработка настроек и адаптаци¤ под разное врем¤ суток, добавлена суша
// заготовки на разные типы волнени¤ и врем¤ суток:
// штиль, легкий ветер, слабый ветер, умеренный ветер, свежий ветер,
// сильный ветер, крепкий ветер, очень крепкий ветер, шторм
// -------------------------------------------------------------

object PSea;	//объект дл¤ хранени¤ настроек пресетов

//выбераем нужный пресет от силы ветра в море
string WhrGetSeaPresetFromWind(float fWind)

{
	ref mchr = GetMainCharacter();
	string sLocation = mchr.location;
	string sPreset = "calm";
	if(fWind > 1.6) sPreset = "light_breeze";
	if(fWind > 3.4) sPreset = "gentle_breeze";
	if(fWind > 5.5) sPreset = "moderate_breeze";
	if(fWind > 8.0) sPreset = "fresh_breeze";
	if(fWind > 10.8) sPreset = "strong_breeze";
	if(fWind > 13.9) sPreset = "near_gale";
	if(fWind > 17.2) sPreset = "gale";
	if(CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) sPreset = "storm";
	if(FindLocation(sLocation) != -1){
		if (fWind > 10.0) sPreset = "strong_breeze_land";
		else{
			sPreset = "light_breeze_land";
		}
	}
	return sPreset;
}

//настройки пресетов
void WhrSetSeaPreset(string sPreset)
{
	Sea.MaxSeaDistance = 2000.0;
	string sMoveSpeed1, sMoveSpeed2
	float fAmp1, fAnimSpeed1, fScale1;
	float fAmp2, fAnimSpeed2, fScale2;
	float fBumpScale, fPosShift;
	float fFoamK, fFoamV, fFoamUV, fFoamTexDisturb;
	float fReflection, fTransparency, fFrenel, fAttenuation;
	int iWaterColor;
	int iSkyColor = argb(0,255,255,255);

	switch(sPreset)
	{
		case "calm": //штиль
			fAmp1 = 2.0;
			fAnimSpeed1 = 1.0;
			fScale1 = 1.25;
			sMoveSpeed1 = "1.5, 0.0, 1.5";

			fAmp2 = 1.25;
			fAnimSpeed2 = 1.25;
			fScale2 = 2.0;
			sMoveSpeed2 = "-1.5, 0.0, -1.5";

			fBumpScale = 0.075; 
			fPosShift = 1.4;

			fFoamV = 1.75;
			fFoamUV = 1.0;
			fFoamTexDisturb = 0.5;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 21.0) {
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,50);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.8;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,80,120);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "light_breeze": //легкий ветер
			fAmp1 = 3.0;
			fAnimSpeed1 = 2.5;
			fScale1 = 1.0;
			sMoveSpeed1 = "0.0, 0.0, 2.5";

			fAmp2 = 1.75;
			fAnimSpeed2 = 2.5;
			fScale2 = 2.0;
			sMoveSpeed2 = "-2.5, 0.0, 0.0";

			fBumpScale = 0.08;
			fPosShift = 1.5;

			fFoamV = 4.0;
			fFoamUV = 1.0;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 21.0) {
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,50);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.8;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,80,120);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "gentle_breeze":	//слабый ветер
			fAmp1 = 4.0;
			fAnimSpeed1 = 1.25;
			fScale1 = 0.6;
			sMoveSpeed1 = "0.0, 0.0, 2.0";

			fAmp2 = 2.0;
			fAnimSpeed2 = 2.0;
			fScale2 = 1.5;
			sMoveSpeed2 = "-2.0, 0.0, 0.0";

			fBumpScale = 0.05;
			fPosShift = 1.1;

			fFoamV = 3.5;
			fFoamUV = 0.65;
			fFoamTexDisturb = 0.5;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 21.0) {
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,50);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.8;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,80,120);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "moderate_breeze":	//умеренный ветер
			fAmp1 = 6.0;
			fAnimSpeed1 = 3.0;
			fScale1 = 0.35;
			sMoveSpeed1 = "0.0, 0.0, 3.5";

			fAmp2 = 2.0;
			fAnimSpeed2 = 2.75;
			fScale2 = 2.0;
			sMoveSpeed2 = "-3.5, 0.0, 0.0";

			fBumpScale = 0.08;
			fPosShift = 1.75;

			fFoamV = 4.5;
			fFoamUV = 0.75;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 21.0) {
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,50);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.8;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,80,120);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "fresh_breeze":// свежий ветер
			fAmp1 = 8.0;
			fAnimSpeed1 = 1.5;
			fScale1 = 0.35;
			sMoveSpeed1 = "0.0, 0.0, 3.0";

			fAmp2 = 3.0;
			fAnimSpeed2 = 3.0;
			fScale2 = 1.25;
			sMoveSpeed2 = "1.0, 0.0, 1.0";

			fBumpScale = 0.075;
			fPosShift = 0.95;

			fFoamV = 6.0;
			fFoamUV = 0.45;
			fFoamTexDisturb = 0.5;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 21.0) {
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,50);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.8;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,80,120);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "strong_breeze":// сильный ветер
			fAmp1 = 12.0;
			fAnimSpeed1 = 2.0;
			fScale1 = 0.35;
			sMoveSpeed1 = "0.0, 0.0, 4.0";

			fAmp2 = 3.0;
			fAnimSpeed2 = 4.0;
			fScale2 = 1.0;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.08;
			fPosShift = 1.0;

			fFoamV = 8.0;
			fFoamUV = 0.2;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 21.0) {
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.2;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,50);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.3;
				fReflection = 0.8;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,80,120);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.3;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "near_gale"://крепкий ветер
			fAmp1 = 16.0;
			fAnimSpeed1 = 1.75;
			fScale1 = 0.20;
			sMoveSpeed1 = "0.0, 0.0, 5.0";

			fAmp2 = 4.0;
			fAnimSpeed2 = 4.0;
			fScale2 = 1.0;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.075;
			fPosShift = 2.0;

			fFoamV = 11.0;
			fFoamUV = 0.30;
			fFoamTexDisturb = 0.5;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 21.0) {
				fFoamK = 0.1;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,50);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.3;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,80,120);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 21.0 )	{
				fFoamK = 0.3;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "gale"://очень крепкий ветер
			fAmp1 = 32.0;
			fAnimSpeed1 = 2.0;
			fScale1 = 0.125;
			sMoveSpeed1 = "8.0, 0.0, 0.0";

			fAmp2 = 6.0;
			fAnimSpeed2 = 6.0;
			fScale2 = 0.75;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.08;
			fPosShift = 1.8;

			fFoamV = 20.0;
			fFoamUV = 0.2;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 20.0) {
				fFoamK = 0.05;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.05;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,60);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 20.0 )	{
				fFoamK = 0.2;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,90);
			}}}
		break;

		case "storm"://шторм
			fAmp1 = 64.0;
			fAnimSpeed1 = 2.25;
			fScale1 = 0.075;
			sMoveSpeed1 = "12.0, 0.0, 0.0";

			fAmp2 = 9.0;
			fAnimSpeed2 = 8.0;
			fScale2 = 0.5;
			sMoveSpeed2 = "0.0, 0.0, 4.0";

			fBumpScale = 0.05;
			fPosShift = 2.0;

			fFoamV = 36.0;
			fFoamUV = 0.25;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 20.0) {
				fFoamK = 0.02;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,10,20);
			} else {
			if( GetTime() >= 6.0 && GetTime() < 10.0 ) {
				fFoamK = 0.03;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,5,30,40);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 20.0 )	{
				fFoamK = 0.03;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,60);
			}}}
		break;

		case "light_breeze_land":	//легкий ветер суша
			fAmp1 = 0.5;
			fAnimSpeed1 = 1.0;
			fScale1 = 1.75;
			sMoveSpeed1 = "0.5, 0.0, 0.0";

			fAmp2 = 0.5;
			fAnimSpeed2 = 1.0;
			fScale2 = 1.75;
			sMoveSpeed2 = "0.0, 0.0, -0.5";

			fBumpScale = 0.15; 
			fPosShift = 1.75;

			fFoamV = 5.0;
			fFoamK = 0.0;
			fFoamUV = 0.3;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
			fAttenuation = 0.3;
		break;

		case "strong_breeze_land": //сильный ветер суша
			fAmp1 = 3.0;
			fAnimSpeed1 = 1.0;
			fScale1 = 2.5;
			sMoveSpeed1 = "0.5, 0.0, 0.0";

			fAmp2 = 3.0;
			fAnimSpeed2 = 1.0;
			fScale2 = 2.5;
			sMoveSpeed2 = "0.0, 0.0, -0.5";

			fBumpScale = 0.15; 
			fPosShift = 1.3;

			fFoamV = 0.45;
			fFoamK = 1.0;
			fFoamUV = 0.3;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.3;
			fAttenuation = 0.3;
		break;	
	}

	DeleteAttribute(PSea, "");				//чистим объект перед записью данных

	PSea.Amp1 = fAmp1;						//амплитуда 1 волны
	PSea.AnimSpeed1 = fAnimSpeed1; 			//скорость анимации
	PSea.Scale1 = fScale1;					//размеры волны
	PSea.MoveSpeed1 = sMoveSpeed1;			//скорость движени¤

	PSea.Amp2 = fAmp2;						//амплитуда 2 волны
	PSea.AnimSpeed2 = fAnimSpeed2;			//скорость анимации
	PSea.Scale2 = fScale2;					//размеры волны
	PSea.MoveSpeed2 = sMoveSpeed2;			//скорость движени¤

	PSea.BumpScale = fBumpScale;			//ћ≈Ћ »≈ ¬ќЋЌџ
	PSea.PosShift = fPosShift;				//остроконечность волн

	PSea.FoamK = fFoamK;					//¤ркость пены
	PSea.FoamV = fFoamV;					//высота с которой начинаетс¤ пена
	PSea.FoamUV = fFoamUV;					//тайлинг пены
	PSea.FoamTexDisturb = fFoamTexDisturb;	//сдвиг по нормали, значение от 0.0 до 1.0

	PSea.Reflection = fReflection;
	PSea.Transparency = fTransparency;
	PSea.Frenel = fFrenel;
	PSea.Attenuation = fAttenuation;
	PSea.WaterColor = iWaterColor;
	PSea.SkyColor = iSkyColor;

	Log_TestInfo("WhrSetSeaPreset: " + sPreset + " FoamK = " + fFoamK);
	Log_TestInfo("WindSpeed: " + fWeatherSpeed);
}

//записываем значени¤ из PSea в море Sea.Sea2
void WhrSetNewSea(float fWind)
{
	string sPreset = WhrGetSeaPresetFromWind(fWind);

	WhrSetSeaPreset(sPreset);

	Sea.Sea2.Amp1 = Whr_GetFloat(PSea, "Amp1");
	Sea.Sea2.AnimSpeed1 = Whr_GetFloat(PSea, "AnimSpeed1");
	Sea.Sea2.Scale1 = Whr_GetFloat(PSea, "Scale1");
	Sea.Sea2.MoveSpeed1 = Whr_GetString(PSea, "MoveSpeed1");

	Sea.Sea2.Amp2 = Whr_GetFloat(PSea, "Amp2");
	Sea.Sea2.AnimSpeed2 = Whr_GetFloat(PSea, "AnimSpeed2");
	Sea.Sea2.Scale2 = Whr_GetFloat(PSea, "Scale2");
	Sea.Sea2.MoveSpeed2 = Whr_GetString(PSea, "MoveSpeed2");

	Sea.Sea2.BumpScale = Whr_GetFloat(PSea, "BumpScale");
	Sea.Sea2.PosShift = Whr_GetFloat(PSea, "PosShift");
	
	Sea.Sea2.FoamK = Whr_GetFloat(PSea, "FoamK");
	Sea.Sea2.FoamV = Whr_GetFloat(PSea, "FoamV");
	Sea.Sea2.FoamUV = Whr_GetFloat(PSea, "FoamUV");
	Sea.Sea2.FoamTexDisturb = Whr_GetFloat(PSea, "FoamTexDisturb");

	Sea.Sea2.Reflection = Whr_GetFloat(PSea, "Reflection");
	Sea.Sea2.Transparency = Whr_GetFloat(PSea, "Transparency");
	Sea.Sea2.Frenel = Whr_GetFloat(PSea, "Frenel");
	Sea.Sea2.Attenuation = Whr_GetFloat(PSea, "Attenuation");
	Sea.Sea2.WaterColor = Whr_GetColor(PSea, "WaterColor");	

	Sea.Sea2.SkyColor = Whr_GetColor(PSea, "SkyColor");
}
