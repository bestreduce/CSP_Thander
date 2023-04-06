// -------------------------------------------------------------
// Mett: настройки моря
// заготовки на разные типы волнения:
// штиль, легкий бриз, бриз, умеренный бриз, сильный бриз, шторм
// -------------------------------------------------------------

object PSea;	//объект для хранения настроек пресетов

//выбераем нужный пресет от силы ветра в море
string WhrGetSeaPresetFromWind(float fWind)

{
	ref mchr = GetMainCharacter();
	string sLocation = mchr.location;
	string sPreset = "calm";
	if(fWind > 1.5) sPreset = "light_breeze";
	if(fWind > 3.3) sPreset = "gentle_breeze";
	if(fWind > 5.4) sPreset = "moderate_breeze";
	if(fWind > 7.9) sPreset = "fresh_breeze";
	if(fWind > 10.7) sPreset = "strong_breeze";
	if(fWind > 13.8) sPreset = "near_gale";
	if(fWind > 17.1) sPreset = "gale";
	if(FindLocation(sLocation) != -1){
	if (fWind > 1.0) sPreset = "light_breeze_land";
	if (fWind > 10.0) sPreset = "strong_breeze_land";
	if (fWind > 18.0) sPreset = "storm_land";
	}
	if(CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm) == 1) sPreset = "storm";
	return sPreset;
}

//настройки пресетов
void WhrSetSeaPreset(int iCurWeatherNum, string sPreset, float fWind)
{
	ref Whr = &Weathers[iCurWeatherNum];
	Sea.MaxSeaDistance = 8000.0;
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
			fFrenel = 0.6;
			fAttenuation = 0.3;
			if (GetTime() < 5.0 || GetTime() >= 22.0) {
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,25,40);
			} else {
			if( GetTime() >= 5.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,40,70);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.7;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,105,170);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				fFoamK = 0.1;
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 22.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "light_breeze": //легкий ветер
			fAmp1 = fWind * 0.625 + 1;//3.0;
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
			fFrenel = 0.6;
			fAttenuation = 0.3;
			if (GetTime() < 5.0 || GetTime() >= 22.0) {
				fFoamK = 0.1;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,25,40);
			} else {
			if( GetTime() >= 5.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,40,70);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.7;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,100,160);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				fFoamK = 0.1;
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 22.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "gentle_breeze":	//слабый ветер
			fAmp1 = fWind * 0.75 + 1;//5.0;
			fAnimSpeed1 = 1.25;
			fScale1 = 0.6;
			sMoveSpeed1 = "0.0, 0.0, 2.0";

			fAmp2 = 2.0;
			fAnimSpeed2 = 2.0;
			fScale2 = 1.5;
			sMoveSpeed2 = "-2.0, 0.0, 0.0";

			fBumpScale = 0.05;
			fPosShift = 2.0;

			fFoamV = fAmp1 * 0.85;//4.25;
			fFoamUV = 0.65;
			fFoamTexDisturb = 0.5;
			fFrenel = 0.6;
			fAttenuation = 0.3;
			if (GetTime() < 5.0 || GetTime() >= 22.0) {
				fFoamK = 0.1;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,25,40);
			} else {
			if( GetTime() >= 5.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,40,70);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.7;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,95,160);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				fFoamK = 0.1;
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 22.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "moderate_breeze":	//умеренный ветер
			fAmp1 = fWind * 0.75 + 1;//7.0;
			fAnimSpeed1 = 3.0;
			fScale1 = 0.4;
			sMoveSpeed1 = "0.0, 0.0, 3.5";

			fAmp2 = 2.0;
			fAnimSpeed2 = 2.75;
			fScale2 = 2.0;
			sMoveSpeed2 = "-3.5, 0.0, 0.0";

			fBumpScale = 0.08;
			fPosShift = 1.75;

			fFoamV = fAmp1 * 0.75;//5.0;
			fFoamUV = 0.6;
			fFoamTexDisturb = 0.5;
			fFrenel = 0.7;
			fAttenuation = 0.3;
			if (GetTime() < 5.0 || GetTime() >= 22.0) {
				fFoamK = 0.1;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,25,40);
			} else {
			if( GetTime() >= 5.0 && GetTime() < 10.0 ) {
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,40,70);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.5;
				fReflection = 0.7;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,90,150);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				fFoamK = 0.1;
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 22.0 )	{
				fFoamK = 0.5;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "fresh_breeze":// свежий ветер
			fAmp1 = fWind * 0.75 + 1;//9.0;
			fAnimSpeed1 = 1.5;
			fScale1 = 0.30;
			sMoveSpeed1 = "0.0, 0.0, 3.0";

			fAmp2 = 3.0;
			fAnimSpeed2 = 3.0;
			fScale2 = 1.25;
			sMoveSpeed2 = "1.0, 0.0, 1.0";

			fBumpScale = 0.075;
			fPosShift = 0.95;

			fFoamV = fAmp1 * 0.75;//7.0;
			fFoamUV = 0.45;
			fFoamTexDisturb = 0.5;
			fFrenel = 0.6;
			fAttenuation = 0.3;
			if (GetTime() < 5.0 || GetTime() >= 22.0) {
				fFoamK = 0.1;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,25,40);
			} else {
			if( GetTime() >= 5.0 && GetTime() < 10.0 ) {
				fFoamK = 0.2;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,40,70);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 20.0 )	{
				fFoamK = 0.2;
				fReflection = 0.7;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,85,140);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				fFoamK = 0.1;
				}
			} else {
			if( GetTime() >= 20.0 && GetTime() < 22.0 )	{
				fFoamK = 0.3;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "strong_breeze":// сильный ветер
			fAmp1 = fWind * 1 + 1;//15;
			fAnimSpeed1 = 2.0;
			fScale1 = 0.30;
			sMoveSpeed1 = "0.0, 0.0, 4.0";

			fAmp2 = 3.0;
			fAnimSpeed2 = 3.0;
			fScale2 = 1.0;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.075;
			fPosShift = 3.0;

			fFoamV = fAmp1 * 0.65;//8.0;
			fFoamUV = 0.3;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.6;
			fAttenuation = 0.3;
			if (GetTime() < 5.0 || GetTime() >= 22.0) {
				fFoamK = 0.05;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,25,40);
			} else {
			if( GetTime() >= 5.0 && GetTime() < 10.0 ) {
				fFoamK = 0.1;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,40,70);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 20.0 )	{
				fFoamK = 0.2;
				fReflection = 0.7;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,80,130);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				fFoamK = 0.1;
				}
			} else {
			if( GetTime() >= 20.0 && GetTime() < 22.0 )	{
				fFoamK = 0.1;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,80);
			}}}}
		break;

		case "near_gale"://крепкий ветер
			fAmp1 = fWind * 1.15 + 1;//20.0;
			fAnimSpeed1 = 1.75;
			fScale1 = 0.20;
			sMoveSpeed1 = "0.0, 0.0, 5.0";

			fAmp2 = 4.0;
			fAnimSpeed2 = 4.0;
			fScale2 = 1.0;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.075;
			fPosShift = 4.0;

			fFoamV = fAmp1 * 0.70;//12.0;
			fFoamUV = 0.30;
			fFoamTexDisturb = 0.5;
			fFrenel = 0.6;
			fAttenuation = 0.3;
			if (GetTime() < 5.0 || GetTime() >= 22.0) {
				fFoamK = 0.1;
				fReflection = 0.3;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,25,40);
			} else {
			if( GetTime() >= 5.0 && GetTime() < 10.0 ) {
				fFoamK = 0.1;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,10,40,70);
			} else {
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.2;
				fReflection = 0.7;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,75,120);
				if (CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain) == true){
				iWaterColor = argb(0,0,55,80);
				fFoamK = 0.1;
				}
			} else {
			if( GetTime() >= 19.0 && GetTime() < 22.0 )	{
				fFoamK = 0.2;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,50,70);
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
			fPosShift = 3.8;

			fFoamV = 21.0;
			fFoamUV = 0.20;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.6;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 22.0) {
				fFoamK = 0.025;
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
			if( GetTime() >= 10.0 && GetTime() < 19.0 )	{
				fFoamK = 0.1;
				fReflection = 0.6;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,55,90);
			} else {
			if( GetTime() >= 19.0 && GetTime() < 22.0 )	{
				fFoamK = 0.1;
				fReflection = 0.5;
				fTransparency = 0.1;
				iWaterColor = argb(0,0,50,70);
			}}}}
		break;

		case "storm"://шторм
			fAmp1 = fWind * 3 + 1;//64;
			fAnimSpeed1 = 2.25;
			fScale1 = 0.075;
			sMoveSpeed1 = "12.0, 0.0, 0.0";

			fAmp2 = 9.0;
			fAnimSpeed2 = 8.0;
			fScale2 = 0.5;
			sMoveSpeed2 = "0.0, 0.0, 4.0";

			fBumpScale = 0.05;
			fPosShift = 5.0;

			fFoamV = fAmp1 * 0.6;//42.0;
			fFoamUV = 0.3;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.6;
			fAttenuation = 0.3;
			if (GetTime() < 6.0 || GetTime() >= 21.0) {
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
			if( GetTime() >= 10.0 && GetTime() < 21.0 )	{
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

		case "storm_land": //сильный ветер суша
			fAmp1 = 20.0;
			fAnimSpeed1 = 2.0;
			fScale1 = 0.125;
			sMoveSpeed1 = "8.0, 0.0, 0.0";

			fAmp2 = 6.0;
			fAnimSpeed2 = 6.0;
			fScale2 = 0.55;
			sMoveSpeed2 = "0.0, 0.0, -1.0";

			fBumpScale = 0.08;
			fPosShift = 3.8;

			fFoamV = 15.0;
			fFoamUV = 0.20;
			fFoamTexDisturb = 0.7;
			fFrenel = 0.6;
			fAttenuation = 0.3;
			fReflection = 0.3;
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

	WhrSetSeaPreset(iCurWeatherNum, sPreset, fWind);

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
