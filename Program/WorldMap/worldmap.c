/*
	Programm interface:

	Init world map in start
		void wdmInitWorldMap();
	Create world map object
		void wdmCreateMap();
	Release world map object
		void wdmReleaseMap();


	SPI (Script program interface):
	Получение данных от карты
	(const) поля только для прочтения
	(var) поля только для записи и прочтения, запись в них приводит к обновления остальных полей,
	      принадлежащих этой группе

	Шторма
	worldMap.storm.num - текущие количество штормов в карте (const)
	worldMap.storm.cur - индекс текущего шторма 0..num-1, надо перезаписывать для обновления полей (var)
	worldMap.storm.x - позиция шторма по x (const)
	worldMap.storm.z - позиция шторма по z (const)
	worldMap.storm.time - оставшееся время жизни в секундах (const)

	Кораблики событий
	worldMap.encounter.num - текущие количество корабликов в карте (const)
	worldMap.encounter.cur - индекс текущего кораблика в карте (var)
	worldMap.encounter.x - позиция кораблика по x (const)
	worldMap.encounter.z - позиция кораблика по z (const)
	worldMap.encounter.time - оставшееся время жизни в секундах (const)
	worldMap.encounter.type - тип события, обозначаемый этим корабликом (define в таблице типов энкоунтеров)
	worldMap.encounter.attack - индекс кораблика, который атакуем (стоя на месте)
	worldMap.encounter.id - название описания энкоунтера: worldMap.encounters.(worldMap.encounter.id)...

	Разная информация
	worldMap.info.playerInStorm - если 1 то плеер находиться в шторме
	worldMap.info.updateinfo - апдейт информации


	//Внутреняя информация - !!!Осторожно, ни каких проверок!!!
	worldMap.enemyshipViewDistMin;		//Растояние на котором корабль начинает исчезать
	worldMap.enemyshipViewDistMax;		//Растояние на котором корабль исчезает полностью
	worldMap.enemyshipDistKill;			//Расстояние на котором убиваем корабль
	worldMap.enemyshipBrnDistMin;		//Минимальное растояние на котором рожается корабль
	worldMap.enemyshipBrnDistMax;		//Максимальное растояние на котором рожается корабль

	worldMap.stormViewDistMin;			//Растояние на котором шторм начинает исчезать
	worldMap.stormViewDistMax;			//Растояние на котором шторм исчезает полностью
	worldMap.stormDistKill;				//Расстояние на котором убиваем шторм
	worldMap.stormBrnDistMin;			//Минимальное растояние на котором рожается шторм
	worldMap.stormBrnDistMax;			//Максимальное растояние на котором рожается шторм

*/

#include "worldmap\worldmap_globals.c"
#include "worldmap\worldmap_events.c"
#include "worldmap\worldmap_reload.c"
#include "worldmap\worldmap_encgen.c"
#include "worldmap\worldmap_coords.c"


//=========================================================================================


#event_handler("WorldMap_EncounterCreate", "wdmEvent_EncounterCreate");
#event_handler("WorldMap_PlayerInStorm", "wdmEvent_PlayerInStorm");
#event_handler("WorldMap_ShipEncounter", "wdmEvent_ShipEncounter");
#event_handler("WorldMap_UpdateDate", "wdmEvent_UpdateDate");
#event_handler("ExitFromWorldMap", "wdmReloadToSea");
//#event_handler("NextDay", "wdmNextDayUpdate");

#event_handler("EventTimeUpdate", "wdmTimeUpdate");


//=========================================================================================
// Programm interface
//=========================================================================================


void wdmCreateMap(float x, float z, float ay)
{
	//Координаты острова с которого уплыли
	float zeroX = MakeFloat(worldMap.zeroX);
	float zeroZ = MakeFloat(worldMap.zeroZ);
	float ShipX, ShipZ;
	//Находим новыве координаты на карте
	int scale = WDM_MAP_TO_SEA_SCALE;
	if (worldMap.island == "Cuba1" || worldMap.island == "Cuba2" || worldMap.island == "Beliz" || worldMap.island == "SantaCatalina"
		|| worldMap.island == "PortoBello" || worldMap.island == "Cartahena" || worldMap.island == "Maracaibo"
		|| worldMap.island == "Caracas" || worldMap.island == "Cumana")
	{
		scale = 25;
	}
	shipX = (x/scale) + zeroX;
	shipZ = (z/scale) + zeroZ;
	worldMap.playerShipX = (x/scale) + zeroX;
	worldMap.playerShipZ = (z/scale) + zeroZ;
	worldMap.playerShipAY = ay;
//	trace(" X :" + x + " Z :" + z + " scale :" + scale + " ZeroX :" + zeroX + " ZeroZ:" + zeroZ + " WDMShipX:"+worldMap.playerShipX + " WDMShipZ:" + worldMap.playerShipZ + " ShipX:" + ShipX + " ShipZ:" + ShipZ);
	//Загружаем карту
	wdmCreateWorldMap();
}

void wdmTimeUpdate()
{
	//QuestsTimeCheck();
	// boal -->
	QuestsCheck();
	PostEvent("EventTimeUpdate", 5000);
	// boal <--
}

void wdmCreateWorldMap()
{
    float fHtRatio = stf(Render.screen_y) / screenscaling;
	wdmLockReload = false;
	//Уберём все сообщения для игрока
	ClearAllLogStrings();
	//
	ReloadProgressStart();
	//Настраиваем имена месяцев
	worldMap.date.monthnames.m01 = XI_ConvertString("target_month_1");
	worldMap.date.monthnames.m02 = XI_ConvertString("target_month_2");
	worldMap.date.monthnames.m03 = XI_ConvertString("target_month_3");
	worldMap.date.monthnames.m04 = XI_ConvertString("target_month_4");
	worldMap.date.monthnames.m05 = XI_ConvertString("target_month_5");
	worldMap.date.monthnames.m06 = XI_ConvertString("target_month_6");
	worldMap.date.monthnames.m07 = XI_ConvertString("target_month_7");
	worldMap.date.monthnames.m08 = XI_ConvertString("target_month_8");
	worldMap.date.monthnames.m09 = XI_ConvertString("target_month_9");
	worldMap.date.monthnames.m10 = XI_ConvertString("target_month_10");
	worldMap.date.monthnames.m11 = XI_ConvertString("target_month_11");
	worldMap.date.monthnames.m12 = XI_ConvertString("target_month_12");
	worldMap.date.font = "normal";
	worldMap.nationFlag.count = 8;
	if(iFlagAllWdm == 2) worldMap.nationFlag.width = 96;
	else worldMap.nationFlag.width = 48;
 	worldMap.nationFlag.height = 48;
	worldMap.nationFlag.texture = "WorldMap/Interfaces/WorldMapEnsigns" + iFlagAllWdm + ".tga";
	//#20200226-03
	//worldMap.outputRum = true;



	//float fHtRatio = stf(Render.screen_y) / iHudScale; // if it was not set earlier
	float cx = stf(showWindow.right) - (128.0) * fHtRatio - 16.0 + 64.0;
	float cy = -40.0 + 128.0 * fHtRatio;

/*	текст из сломавшего флаги PR	https://github.com/storm-devs/storm-engine/pull/440
	worldMap.sky.texture     = "WorldMap\Interfaces\sky.tga.tx";
	worldMap.sky.maskTexture = "WorldMap\Interfaces\sky_mask.tga.tx";
	worldMap.sky.leftPos = cx - 64.0 * fHtRatio;
	worldMap.sky.topPos = cy - 64.0 * fHtRatio;
	worldMap.sky.width = 128.0 * fHtRatio;
	worldMap.sky.height = 128.0 * fHtRatio;
	worldMap.sky.color = argb(128, 255, 255, 255);

	worldMap.windPointer.texture = "WorldMap\Interfaces\wind_pointer.tga.tx";
	worldMap.windPointer.leftPos = cx - 16.0 * fHtRatio;
	worldMap.windPointer.topPos = cy - 64.0 * fHtRatio;
	worldMap.windPointer.width = 32.0 * fHtRatio;
	worldMap.windPointer.height = 128.0 * fHtRatio;
	worldMap.windPointer.color = argb(255, 255, 255, 255);

	worldMap.windBar.texture     = "WorldMap\Interfaces\bar.tga.tx";
	worldMap.windBar.maskTexture = "WorldMap\Interfaces\bar_mask.tga.tx";
	worldMap.windBar.leftPos = cx - 64.0 * fHtRatio;
	worldMap.windBar.topPos = cy;
	worldMap.windBar.width = 128.0 * fHtRatio;
	worldMap.windBar.height = 128.0 * fHtRatio;
	worldMap.windBar.color = argb(255, 255, 255, 255);

	worldMap.frame.texture = "WorldMap\Interfaces\back.tga.tx";
	worldMap.frame.leftPos = cx - 64.0 * fHtRatio;
	worldMap.frame.topPos = cy - 128.0 * fHtRatio;
	worldMap.frame.width = 128.0 * fHtRatio;
	worldMap.frame.height = 256.0 * fHtRatio;
	worldMap.frame.color = argb(255, 255, 255, 255);

	worldMap.dateText.font = "normal";
	worldMap.dateText.scale = fHtRatio;
	worldMap.dateText.color = argb(255, 255, 255, 255);
	worldMap.dateText.pos.x = cx;
	worldMap.dateText.pos.y = cy + (98.0 - 16.0 * 0.5) * fHtRatio;
*/
	// Center
	cy = cy + 128.0 * fHtRatio + 32.0;

	worldMap.morale.texture     = "WorldMap\Interfaces\morale.tga.tx";
	worldMap.morale.barTexture  = "WorldMap\Interfaces\morale_bar.tga.tx";
	worldMap.morale.maskTexture = "WorldMap\Interfaces\morale_mask.tga.tx";
	worldMap.morale.leftPos = cx - 64.0 * fHtRatio;
	worldMap.morale.topPos = cy - 32.0 * fHtRatio;
	worldMap.morale.width = 128.0 * fHtRatio;
	worldMap.morale.height = 64.0 * fHtRatio;
	worldMap.morale.color = argb(255, 255, 255, 255);

	worldMap.foodText.font = "normal";
	worldMap.foodText.scale = fHtRatio;
	worldMap.foodText.color = argb(255, 255, 255, 255);
	worldMap.foodText.pos.x = cx - 24.0 * fHtRatio;
	worldMap.foodText.pos.y = cy + 30.0 * fHtRatio;

	worldMap.rumText.font = "normal";
	worldMap.rumText.scale = fHtRatio;
	worldMap.rumText.color = argb(255, 255, 255, 255);
	worldMap.rumText.pos.x = cx + 24.0 * fHtRatio;
	worldMap.rumText.pos.y = cy + 30.0 * fHtRatio;

/*	worldMap.coord.texture = "WorldMap\Interfaces\coord.tga.tx";
	worldMap.coord.leftPos = cx - 64.0 * fHtRatio;
	worldMap.coord.topPos = cy + 64.0 * fHtRatio;
	worldMap.coord.width = 128.0 * fHtRatio;
	worldMap.coord.height = 64.0 * fHtRatio;
	worldMap.coord.color = argb(255, 255, 255, 255);

	worldMap.stCoordText.font = "normal";
	worldMap.stCoordText.scale = fHtRatio;
	worldMap.stCoordText.color = argb(255, 255, 255, 255);
	worldMap.stCoordText.pos.x = cx;
	worldMap.stCoordText.pos.y = cy + (64.0 + 13.0) * fHtRatio;
	worldMap.stCoordText.text = XI_ConvertString("Coordinates");

	worldMap.coordText.font = "normal";
	worldMap.coordText.scale = fHtRatio;
	worldMap.coordText.color = argb(255, 255, 255, 255);
	worldMap.coordText.pos.x = cx;
	worldMap.coordText.pos.y = cy + (64.0 + 32.0) * fHtRatio;
*/





	worldMap.resizeRatio = fHtRatio;
	//Удалим все устаревшие энкаунтеры
	wdmRemoveOldEncounters();
//	Trace("Save check ---------------================--------------")
//	DumpAttributes(&worldMap);
//	Trace("Save check ###########----================--------------")
	worldMap.playerInStorm = "0";
	//Сбросим счётчики генерации энкоунтеров
	wdmReset();
	//Создаём карту
	CreateEntity(&worldMap,"worldmap");
	worldMap.isLoaded = "true";
	//Обновляем параметры
	worldMap.update = "";
	//Фейдер
	CreateEntity(&wdm_fader, "fader");
	if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");
	float fadeInTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_IN, fadeInTime, true);
	SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "jonny_load\sea\sea_"+rand(3)+".tga");
	//Установим звуковую схему
	SetSchemeForMap();
	//Сообщим, что загрузились
	PostEvent("EventWorldMapInit", 830); //fix boal
	ReloadProgressEnd();
	PostEvent("EventTimeUpdate", 1000);
	//Создаём накопившиеся квестовые энкоунтеры
	worldMap.addQuestEncounters = "updateQuest";
	InitWmInterface();
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_SET_NATION_FLAG,  sti(pchar.nation));
}

void wdmLoadSavedMap()
{
	//Загружаем карту
	wdmCreateWorldMap();
}

void wdmRemoveOldEncounters()
{
	//Пометим протухшие энкаунтеры
	wdmMarkDeleteEncounters();
	//Собираем всех желающих
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	object forDelete;
	string attr, encID;
	int count = 0;
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "needDelete") != 0)
		{
			attr = "del" + count;
			forDelete.(attr) = GetAttributeName(enc);
			count = count + 1;
		}
	}
	for(i = 0; i < count; i++)
	{
		attr = "del" + i;
		encID = "encounters." + forDelete.(attr);
		DeleteAttribute(&worldMap, encID);
	}
}

float wdmGetDays(int year, int month, int day, int hour)
{
	//Считаем дни по годам
	if(year < 0) year = 0;
	if(year > 3000) year = 3000;
	year = year*365;
	//Считаем целые дни
	for(int i = 1; i < month; i++)
	{
		day = day + GetMonthDays(i, year);
	}
	//Считаем полные дни
	float days = year + day + (hour/24.0);
	return days;
}

void wdmMarkDeleteEncounters()
{
	//Получаем дату
	int year = sti(worldMap.date.year);
	int month = sti(worldMap.date.month);
	int day = sti(worldMap.date.day);
	int hour = sti(worldMap.date.hour);
	float days = wdmGetDays(year, month, day, hour);
	int encYear, encMonth, encDay, encHour;
	//Перебираем все энкоунтеры, помечая на удаление
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "Quest") != 0)
		{
			continue;
		}
		bool deleteMe = false;
		if(CheckAttribute(enc, "year") != 0)
		{
			encYear = sti(enc.year);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "month") != 0)
		{
			encMonth = sti(enc.month);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "day") != 0)
		{
			encDay = sti(enc.day);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "hour") != 0)
		{
			encHour = sti(enc.hour);
		}else{
			deleteMe = true;
		}
		if(deleteMe != true)
		{
			float deltaDays = wdmGetDays(encYear, encMonth, encDay, encHour) - days;
			if(deltaDays < 0)
			{
				deltaDays = -deltaDays;
			}
			if(deltaDays > 1.0)
			{
				deleteMe = true;
			}
		}
		if(deleteMe != false)
		{
			enc.needDelete = "Time delete";
		}
	}
}
