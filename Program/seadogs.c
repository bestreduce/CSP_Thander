#include "storm-engine\layers.h"
#include "storm-engine\events.h"

#include "_mod_on_off.h"
#include "globals.c"
#include "animals.c"
#include "NumberUtilities.c" // Warship 26.07.09. Работа с числами
#include "sea_ai\sea.c"
#include "ships\ships.c"
#include "Encounters\Encounters.c"
#include "worldmap\worldmap.c"
#include "locations\locations.c"
#include "Loc_ai\LAi_init.c"
#include "store\goods.h"
#include "cannons\cannons.c"
#include "nations\nations.c"
#include "particles.c"
#include "characters\characters.c"
#include "interface\interface.h"
#include "store\storeutilite.c"
#include "dialog.c"
#include "quests\quests.c"
#include "islands\islands.c"
#include "colonies\colonies.c"
#include "reload.c"
#include "battle_interface\loginterface.c"
#include "calendar.c"
#include "teleport.c"
#include "utils.c"
#include "weather\WhrWeather.c"
#include "controls\controls.c"
#include "ITEMS\items.h"
#include "ITEMS\itemLogic.c"
#include "ITEMS\items_utilite.c"
#include "store\store.h"
#include "interface\interface.c"
#include "OnLoadReinit.c"
// Addon things -->
#include "Addons\utils.c"
// Addon things <--
#include "Controls\hotkey_travel.c"
//// {*} BUHO-CIC - ADDED CODE - CIC vars and routines.
#include "BUHO_CIC.c"
//// {*} BUHO END ADDITION

extern void ShipsInit(); //Boyer add
extern void InitBaseCannons();
extern void InitCharacters();
extern void InitBaseInterfaces();

extern void wdmInitWorldMap();
extern void InitGoods();
extern void InitStores();
extern int InitItems();
extern void InitCharactersTables();
extern void InitCharactersNames();
extern void InitPiratesNames();
extern void InitGeneratorNames();
extern void InitIndianNames();
extern void CreateCharacters();

extern void ActiveF4Control(); // boal debuger
extern void ActiveF5Control(); // boal debuger
extern void ActiveF7Control(); // boal debuger
extern void ActiveF10Control(); // boal debuger
extern void ActiveF12Control(); // boal debuger
extern void ActiveINSERTControl(); // boal debuger

native float Bring2RangeNoCheck(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Bring2Range(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Degree2Radian(float fDegree);
native float Clampf(float fValue);
native int RDTSC_B();
native int RDTSC_E(int iRDTSC);

native int SetTexturePath(int iLevel, string sPath);
native int SetGlowParams(float fBlurBrushSize, int Intensivity, int BlurPasses);
native int RPrint(int x, int y, string sPrint);
native int GetTexture(string name);
native void ReleaseTexture(int texId);

#libriary "script_libriary_test"
#libriary "dx9render_script_libriary"

#event_handler(NEW_GAME_EVENT,"NewGame");
#event_handler(GAME_OVER_EVENT,"GameOverE");
#event_handler("Control Activation","ProcessControls");
#event_handler("MainMenuKey","ProcessMainMenuKey");
#event_handler("InterfaceKey","ProcessInterfaceKey");
#event_handler("CameraPosAng","ProcessCameraPosAng");
#event_handler("Cheat","ProcessCheat");
#event_handler("SeaDogs_ClearSaveData", "ClearLocationsSaveData");
#event_handler("StopQuestCheckProcessFreeze","ProcessStopQuestCheckProcessFreeze"); // boal 240804
//#20171009-03
#event_handler("ResetDevice", "ResetDevice");

float fHighPrecisionDeltaTime;

#define CONFIRMMODE_PROFILE_DELETE	1
#define CONFIRMMODE_SAVE_DELETE		2
#define CONFIRMMODE_SAVE_OVERWRITE	3
#define CONFIRMMODE_LOAD_GAME		4

int g_nConfirmMode;
string g_sConfirmReturnWindow;
int g_nInterfaceFileID = -1;

void DoConfirm( int nConfirmMode )
{
	g_sConfirmReturnWindow = "MAIN_WINDOW";
	if( XI_IsWindowEnable("PROFILE_WINDOW") ) {
		g_sConfirmReturnWindow = "PROFILE_WINDOW";
	}
	XI_WindowDisable( g_sConfirmReturnWindow, true );
	// enable confirm window
	XI_WindowDisable( "CONFIRM_WINDOW", false );
	XI_WindowShow( "CONFIRM_WINDOW", true );
	SetCurrentNode( "CONFIRM_YES" );

	g_nConfirmMode = nConfirmMode;
	switch( nConfirmMode )
	{
	case CONFIRMMODE_PROFILE_DELETE:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Delete profile confirm") );
		break;
	case CONFIRMMODE_SAVE_DELETE:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Delete savefile confirm") );
		break;
	case CONFIRMMODE_SAVE_OVERWRITE:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Overwrite savefile confirm") );
		break;
	case CONFIRMMODE_LOAD_GAME:
		SetFormatedText( "CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID,"Load game confirm") );
		break;
	}
	SendMessage( &GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONFIRM_TEXT", 5 ); // центрируем по вертикали
}

void ProcessStopQuestCheckProcessFreeze() // boal 240804
{
    bQuestCheckProcessFreeze = false;
    wdmLockReload            = false;
    QuestsCheck(); // выполнить отложенные

    if (rand(20) == 10) // 16.01.06 не помню уже зачем разлочивал ГГ, но на деле мешает до квестам, но если где повиснет, то спасет ф2
    {
    	DoQuestCheckDelay("pchar_back_to_player", 0.5); // если в диалоге залочило, вернем управление
    }
}

void ProcessVersionCheck() // boal 271004
{
    ref mc = GetMainCharacter();

    if (CheckAttribute(mc, "HeroParam")) // признак, что есть герой
    {
        if (!CheckAttribute(mc, "VersionNumber"))
    	{
            Log_Info("Загружена старая сохраненная запись.");
            Log_Info("Возможна нестабильная работа программы.");
    	}
        else
        {
            if (sti(mc.VersionNumberCompatibility) < VERSION_NUM_PRE && mc.VersionNumber != GetVerNum())
            {
                Log_Info("Загружена сохраненная запись версии " + mc.VersionNumber +".");
                Log_Info("Возможна нестабильная работа программы.");
            }
        }
    }

	if (pchar.versionnumber == VERSION_NUMBER2 || pchar.versionnumber == VERSION_NUMBER2 + "  DEV") 
	{}//{log_info("РЕИНИТ не требуется");}
	else
	{
		if (!CheckAttribute(pchar, "fixsaveNG0") && HasSubStr(pchar.versionnumber, ".02.2023"))//для версии от февраля
		{
			if (sti(pchar.rank)>2) DozorPrepare_2();//фикс дозора без НИ

			ref rLoc = LocFromID("FortOrange_town");//фикс локатора церкви в ФортОранж без НИ
			rLoc.reload.l10.name = "reload17";
			rLoc = LocFromID("FortOrange_church");
			rLoc.reload.l1.emerge = "reload17";

			rLoc = LocFromID("Shore35");//фикс локаторов перехода ФортОранжа для квестов без НИ
			rLoc.reload.l1.name = "gate_back";
			rLoc = LocFromID("FortOrange_ExitTown");
			rLoc.reload.l2.name = "reload3";
			rLoc.reload.l2.emerge = "gate_back";
			rLoc = LocFromID("FortOrange_town");
			rLoc.questSeekCap = 8;
			rLoc.reload.l1.name = "gate_back";
			rLoc.reload.l1.emerge = "reload3";
			rLoc.reload.l2.emerge = "gate_back";

			//новое ПЛЖ
			rLoc = LocFromID("Shore51");//коронадо
			rLoc.reload.l1.go = "Pearl_town_2";
			rLoc.reload.l1.emerge = "reload2";
			rLoc.reload.l1.label = "Pearl";
			rLoc.locators_radius.reload.reload2_back = 2;

			rLoc = LocFromID("Pearl_Jungle_06");
			rLoc.reload.l1.go = "Pearl_Jungle_07";
			rLoc.reload.l1.emerge = "reload2";
			rLoc.reload.l1.label = "Jungle";
			rLoc.reload.l3.go = "Pearl_Jungle_08";
			rLoc.reload.l3.emerge = "reload2";
			rLoc.reload.l3.label = "jungle";

			rLoc = LocFromID("Pearl_CaveEntrance");
			rLoc.reload.l1.emerge = "reload1";

			rLoc = LocFromID("Pearl_town_2");
			rLoc.image = "loading\jonny_load\outside\Pearl.tga";
			rLoc.filespath.models = "locations\Outside\Villagepearl";
			rLoc.models.always.pirateFort = "Pearl";
			rLoc.models.always.locators = "Pearl_locators";
			rLoc.models.always.grassPatch = "Pearl_grass";
			rLoc.models.day.charactersPatch = "Pearl_patch";
			rLoc.models.day.fonars = "Pearl_fd";
			rLoc.models.night.charactersPatch = "Pearl_patch";
			rLoc.models.night.fonars = "Pearl_fn";
			rLoc.reload.l1.go = "Pearl_Jungle_07";
			rLoc.reload.l2.name = "reload2_back";
			rLoc.reload.l2.go = "Shore51";
			rLoc.reload.l2.label = "Jungle";
			rLoc.reload.l2.autoreload = 1;
			rLoc.locators_radius.reload.reload2_back = 2;
			rLoc.reload.l3.name = "reloadH2";
			rLoc.reload.l3.go = "PearlTown2_Townhall";
			rLoc.reload.l4.name = "reloadH5";
			rLoc.reload.l4.go = "PearlTown2_House6";
			rLoc.reload.l5.name = "reloadH4";
			rLoc.reload.l5.go = "PearlTown2_HK2";
			rLoc.reload.l6.name = "reloadH1";
			rLoc.reload.l6.go = "PearlTown2_Hut1";
			rLoc.reload.l7.name = "reloadH3";
			rLoc.reload.l7.go = "PearlTown2_Hut1";
			rLoc.reload.l7.emerge = "reload2";
			rLoc.reload.l7.label = "house";

			rLoc = LocFromID("PearlTown2_Townhall");
			rLoc.reload.l1.emerge = "reloadH2";

			rLoc = LocFromID("PearlTown2_House6");
			rLoc.reload.l1.emerge = "reloadH5";

			rLoc = LocFromID("Temple_h");//фикс травы у Кхаэль Роа
			rLoc.models.always.grassPatch.texture = "grass\algaeU1.tga.tx";

			ref sld = characterFromID("Pirates_trader");//фикс торговцев-барменов без НИ
			LAi_SetOwnerType(sld);
			sld = characterFromID("Dominica_trader");//в ините есть, но непися не находит...	это странно.
			LAi_SetOwnerType(sld);
			sld = characterFromID("FortOrange_trader");
			LAi_SetOwnerType(sld);
			sld = characterFromID("LaVega_trader");
			LAi_SetOwnerType(sld);
			sld = characterFromID("LeFransua_trader");
			LAi_SetOwnerType(sld);
			sld = characterFromID("PuertoPrincipe_trader");
			LAi_SetOwnerType(sld);

			//погода обновится сама

			//инит кораблей обновится сам?

			for(int j=0;j<REAL_SHIPS_QUANTITY;j++)	//фикс без НИ ватерлинии и числа пушек у кораблей, уже сгенерировавшихся
			{

				if (!checkattribute(RealShips[j], "basetype")) continue;
				if (sti(RealShips[j].Class) == 7) RealShips[j].CabinType = "New_Cabin3";//каюты тартанам, заводы - рабочим
				if (sti(RealShips[j].basetype) == SHIP_LUGGER) RealShips[j].WaterLine = -0.35;
				if (sti(RealShips[j].basetype) == SHIP_NEPTUN) RealShips[j].WaterLine = -0.4;
				if (sti(RealShips[j].basetype) == SHIP_REQUIN) RealShips[j].WaterLine = -0.4;
				if (sti(RealShips[j].basetype) == SHIP_LUGGER_H) RealShips[j].hullNums = 5;

				if (sti(RealShips[j].basetype) == SHIP_HERCULES)
				{
					RealShips[j].Cannons = sti(RealShips[j].Cannons)-4;
					RealShips[j].CannonsQuantity = sti(RealShips[j].CannonsQuantity)-4;
					RealShips[j].CannonsQuantityMax = sti(RealShips[j].CannonsQuantityMax)-4;
					RealShips[j].fcannon = sti(RealShips[j].fcannon)-2;
					RealShips[j].bcannon = sti(RealShips[j].bcannon)-2;
				}
			}

			if(bFillEncyShips) 
			{
				aref aShips;
				makearef(aShips, Pchar.Encyclopedia);
				int Sum = 0;
				for (j=SHIP_LUGGERQUEST;j<=SHIP_FORT;j++)
				{
					DeleteAttribute(aShips, ShipsTypes[j].name);//стираем записи об исследовании квестовых, лодки, форта
				}
				Sum = GetAttributesNum(aShips);//суммируем оставшиеся открытые корабли
				if (Sum != sti(pchar.questTemp.shipsearchcount))
				{
					pchar.questTemp.shipsearchcount = Sum;
					log_info("Исследовано кораблей - " + pchar.questTemp.shipsearchcount + "!");
					if (pchar.questTemp.shipsearchcount == "124") UnlockAchievement("AchShipSearch",3);
				}
			}

			int n = GetArraySize(&Items);//+5 предметов для странных дел
			SetArraySize(&Items,ITEMS_QUANTITY);
			SetArraySize(&itemModels,ITEMS_QUANTITY);//ХЗ, что это...
ref itm;
for(j=n; j<ITEMS_QUANTITY; j++)
{
	makeref(itm,Items[j]);
	itm.id = "item"+(j+1);
	itm.describe = "";
	itm.index = j;
	itm.model = "";
	itm.shown = false;
	itm.startLocation = "";
	itm.startLocator = "";
	itm.useLocation = "";
	itm.useLocator = "";
	itm.describe = "";
    itm.Weight = 0.0; // boal
    itm.uniq  = false;
    itm.price = 1;
    itm.ItemType = "VARIETY";
}
			makeref(itm,Items[n]);	//Квест "Странные вещи творятся на архипелаге"
			itm.id = "PKM_SvtvA_amulet";	//Амулет главного сатаниста
			itm.name = "itmname_PKM_SvtvA_amulet";
			itm.describe = "itmdescr_PKM_SvtvA_amulet";
			itm.picIndex = 11;
			itm.picTexture = "ITEMS_20";
			itm.price = 30000;
			itm.weight = 0.5;
			n++;
			makeref(itm,Items[n]);	//Квест "Странные вещи творятся на архипелаге"
			itm.id = "PKM_SvtvA_znachok";	//Значок рядового сатаниста
			itm.name = "itmname_PKM_SvtvA_znachok";
			itm.describe = "itmdescr_PKM_SvtvA_znachok";
			itm.picIndex = 12;
			itm.picTexture = "ITEMS_4";
			itm.price = 66;
			itm.weight = 0.1;
			n++;
			makeref(itm,Items[n]);	//Квест "Странные вещи творятся на архипелаге"
			itm.id = "PKM_SvtvA_pismo1";	//Письмо для падре Домингеса
			itm.name = "itmname_PKM_SvtvA_pismo1";
			itm.describe = "itmdescr_PKM_SvtvA_pismo1";
			itm.picIndex = 7;
			itm.picTexture = "ITEMS_12";
			itm.price = 0;
			itm.weight = 0.1;
			itm.ItemType = "QUESTITEMS";
			n++;
			makeref(itm,Items[n]);	//Квест "Странные вещи творятся на архипелаге"
			itm.id = "PKM_SvtvA_pismo2";	//Письмо для отца Клермона
			itm.name = "itmname_PKM_SvtvA_pismo2";
			itm.describe = "itmdescr_PKM_SvtvA_pismo2";
			itm.picIndex = 7;
			itm.picTexture = "ITEMS_12";
			itm.price = 0;
			itm.weight = 0.1;
			itm.ItemType = "QUESTITEMS";
			n++;
			makeref(itm,Items[n]);
			itm.id = "PKM_SvtvA_pismo3";	//Книга Хаоса
			itm.name = "itmname_PKM_SvtvA_pismo3";
			itm.describe = "itmdescr_PKM_SvtvA_pismo3";
			itm.picIndex = 2;
			itm.picTexture = "ITEMS_20";
			itm.price = 5000;
			itm.weight = 0.7;
			n++;

			//Джеки
			sld = GetCharacter(NPC_GenerateCharacter("MG_Obezyana", "Koata1", "monkey", "monkey", 1, PIRATE, -1, false));
			LAi_SetHP(sld, 1.0, 1.0);
			sld.name = "Джеки";
			sld.lastname = "";
			LAi_SetWarriorType(sld);
			//LAi_SetMonkeyType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Guadeloupe_deadlock", "monsters", "monster6");

			PChar.quest.MG_ObezyanaKill.win_condition.l1 = "NPC_Death";
			PChar.quest.MG_ObezyanaKill.win_condition.l1.character = "MG_Obezyana";
			PChar.quest.MG_ObezyanaKill.win_condition = "MG_ObezyanaKill";

			sld = characterFromID("PortRoyal_Priest");
			sld.name	= "отец Бернард";
			sld.lastname = "";
			sld.model	= "Priest_2";
			sld = characterFromID("FortFrance_Priest");
			sld.name	= "отец Клермон";
			sld.lastname = "";
			sld = characterFromID("SanJuan_Priest");
			sld.name	= "падре Домингес";
			sld.lastname = "";

			PKMQuestsInit();

			n = GetArraySize(&locations);	//nLocationsNum	//старое число локаций
			SetArraySize(&locations, 900);	//MAX_LOCATIONS
//базовый инит для новых локаций
ref loc;
for(int i = n; i < 881; i++)
{
	makeref(loc, Locations[i]);
	DeleteAttribute(loc, "");
	loc.id = "";
	loc.index = i;
	loc.image = "jonny_load\sea\sea_"+rand(3)+".tga";
	loc.music = "enplav.ogg";
	loc.locators_radius.reload = 1.0;
	loc.locators_radius.rld = 1.0;
	loc.locators_radius.camdetector = 1.0;
	loc.locators_radius.camera = 0.3;
	loc.locators_radius.characters = 0.5;
	loc.locators_radius.goto = 0.5;
	loc.locators_radius.sit = 0.5;
	loc.locators_radius.item = 0.5;
	loc.locators_radius.officers = 0.5;
	loc.locators_radius.merchant = 1.0;
	loc.locators_radius.box = 1.0;
	loc.locators_radius.candles = 0.1;
	loc.locators_radius.candles_medium = 0.2;
	loc.locators_radius.chandeliers = 0.5;
	loc.locators_radius.heaters = 1.0;
	loc.locators_radius.torchlightes = 0.3;
	loc.locators_radius.torchlightes_o = 0.3;
	loc.locators_radius.fonar = 0.4;
	loc.locators_radius.outside = 2.0;
	loc.locators_radius.incas_light = 0.8;
	loc.locators_radius.incas_sky = 1.0;
	loc.locators_radius.randitem = 1.5;
	loc.locators_radius.waitress = 1.0;
	loc.locators_radius.tables = 0.5;
	loc.locators_radius.barmen = 1.0;
	loc.locators_radius.lamp = 0.2;
	loc.locators_radius.blueteleport = 0.2;
	loc.locators_radius.redteleport = 0.2;
	loc.locators_radius.greenteleport = 0.2;
	loc.locators_radius.magsteleport = 0.2;
	loc.locators_radius.EncDetector = 8.0;
	loc.locators_radius.Enc01 = 0.5;
	loc.locators_radius.Enc02 = 0.5;
	loc.locators_radius.Enc03 = 0.5;
	loc.locators_radius.Enc04 = 0.5;
	loc.locators_radius.teleport = 1.0;
	loc.locators_radius.quest = 1.0;

	// видимость новых (и старых) локаторов
	loc.locators_radius.Actor = 1.0;
	loc.locators_radius.ships_other = 1.0;
	loc.locators_radius.ships = 1.0;
	loc.locators_radius.Genres = 1.0;

	if (MOD_BETTATESTMODE == "On")
	{// чтоб было видно в отладке Boal 18.08.06
		loc.locators_radius.soldiers = 0.5;
		loc.locators_radius.patrol = 0.5;
		loc.locators_radius.Smugglers = 0.5;
		loc.locators_radius.monsters = 0.5;
		loc.locators_radius.prison = 0.2;
	}

	//Day dynamic light
	loc.models.day.lights.candles = "candle";
	loc.models.day.lights.candles_medium = "candelabrum";
	loc.models.day.lights.chandeliers = "chandelier";
	loc.models.day.lights.heaters = "heater";
	loc.models.day.lights.torchlightes = "torchlight";
	loc.models.day.lights.outside = "outside_day";
	loc.models.day.lights.incas_light = "incas";
	loc.models.day.lights.incas_sky = "incasskyday";
	loc.models.day.lights.lamp = "lamp";
	loc.models.day.lights.blueteleport = "blueteleport";
	loc.models.day.lights.redteleport = "redteleport";
	loc.models.day.lights.greenteleport = "greenteleport";
	loc.models.day.lights.magsteleport = "magsteleport";

	//Night dynamic light
	loc.models.night.lights.candles = "candle";
	loc.models.night.lights.candles_medium = "candelabrum";
	loc.models.night.lights.chandeliers = "chandelier";
	loc.models.night.lights.heaters = "heater";
	loc.models.night.lights.torchlightes = "torchlight";
	loc.models.night.lights.torchlightes_o = "torchlight";
	loc.models.night.lights.fonar = "lamp";
	loc.models.night.lights.outside = "outside_night";
	loc.models.night.lights.incas_light = "incas";
	loc.models.night.lights.incas_sky = "incasskynight";
	loc.models.night.lights.lamp = "lamp";
	loc.models.night.lights.blueteleport = "blueteleport";
	loc.models.night.lights.redteleport = "redteleport";
	loc.models.night.lights.greenteleport = "greenteleport";
	loc.models.night.lights.magsteleport = "magsteleport";
}
			Locations[n].id = "New_Cabin3"; //НОВАЯ КАЮТА
			Locations[n].id.label = "cabine";
			Locations[n].filespath.models = "locations\decks\nc_cabin3";
		    Locations[n].image = "loading\jonny_load\inside ship\nc_cabin3.tga";
			locations[n].type = "boarding_cabine";
			Locations[n].models.always.l1 = "nc_cabin3";
			Locations[n].models.always.window = "nc_cabin3_glass";
			Locations[n].models.always.window.tech = "LocationWindows";
			Locations[n].models.always.window.level = 65531;
			Locations[n].models.day.vlight = "nc_cabin3_rays";
			Locations[n].models.day.vlight.uvslide.v0 = -0.05;
		    Locations[n].models.day.vlight.uvslide.v1 = 0.0;
			Locations[n].models.day.vlight.tech = "LocationWaterFall";
			Locations[n].models.day.vlight.level = 99950;
			Locations[n].models.day.locators = "nc_cabin3_ld";
			Locations[n].models.day.charactersPatch = "nc_cabin3_pd";
			Locations[n].models.night.locators = "nc_cabin3_ln";
			Locations[n].models.night.charactersPatch = "nc_cabin3_pn";
			Locations[n].environment.sea = "true";
			Locations[n].environment.weather = "true";
			Locations[n].locators_radius.reload.reload1 = 0.5;
		    Locations[n].locators_radius.rld.loc0 = 0.5;
		    Locations[n].locators_radius.rld.loc1 = 0.5;
		    Locations[n].locators_radius.box.box1 = 0.6;
		    Locations[n].boarding = "true";
			Locations[n].boarding.nextdeck = "";
			Locations[n].camshuttle = 1;
			Locations[n].boarding.locatorNum = 1;
			Locations[n].CabinType = true;
			locations[n].environment.weather.rain = false;
			Locations[n].boarding.Loc.Hero = "loc0";
		    Locations[n].boarding.Loc.Capt = "loc1";
			n++;

			Locations[n].id = "My_New_Cabin3"; // peace
			Locations[n].id.label = "cabine";
			Locations[n].filespath.models = "locations\decks\nc_cabin3";
		    Locations[n].image = "loading\jonny_load\inside ship\nc_cabin3.tga";
			locations[n].type = "ship_cabin"; // nc_mod
			Locations[n].models.always.l1 = "nc_cabin3";
			Locations[n].models.always.window = "nc_cabin3_glass";
			Locations[n].models.always.window.tech = "LocationWindows";
			Locations[n].models.always.window.level = 65531;
			Locations[n].models.day.vlight = "nc_cabin3_rays";
			Locations[n].models.day.vlight.uvslide.v0 = -0.05;
		    Locations[n].models.day.vlight.uvslide.v1 = 0.0;
			Locations[n].models.day.vlight.tech = "LocationWaterFall";
			Locations[n].models.day.vlight.level = 99950;
			Locations[n].models.day.locators = "nc_cabin3_ld";
			Locations[n].models.day.charactersPatch = "nc_cabin3_pd";
			Locations[n].models.night.locators = "nc_cabin3_ln";
			Locations[n].models.night.charactersPatch = "nc_cabin3_pn";
			Locations[n].environment.sea = "true";
			Locations[n].environment.weather = "true";
			locations[n].box1 = Items_MakeTime(0, 1, 1, 2003);
			Locations[n].locators_radius.reload.reload1 = 0.5;
		    Locations[n].locators_radius.rld.loc0 = 0.5;
		    Locations[n].locators_radius.rld.loc1 = 0.5;
		    Locations[n].locators_radius.box.box1 = 0.6;
		    LAi_LocationFightDisable(&Locations[n], true);
		    Locations[n].reload.l1.name = "reload1";
			Locations[n].reload.l1.go = "My_Deck";
			Locations[n].reload.l1.emerge = "reload1";
			Locations[n].reload.l1.label = "Deck.";
			Locations[n].boarding = "true";
			Locations[n].camshuttle = 1;
			locations[n].environment.weather.rain = false;
			n++;

			locations[n].id = "Pearl_Jungle_07";//+9 локаций в ПЛЖ
			locations[n].id.label = "Jungle";
			locations[n].image = "loading\jonny_load\jungle\Jungle10.tga";
			locations[n].type = "jungle";
			locations[n].islandId = "Mein";
			locations[n].islandIdAreal = "Pearl";
			locations[n].filespath.models = "locations\Outside\Jungles\Jungle10";
			Locations[n].models.always.jungle = "jungle10";
			Locations[n].models.always.locators = "jungle10_locators";
			Locations[n].models.always.grassPatch = "jungle10_grass";
			Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
			Locations[n].models.always.l1 = "plan1";
			Locations[n].models.always.l1.level = 9;
			Locations[n].models.always.l1.tech = "DLightModel";
			Locations[n].models.always.l2 = "plan2";
			Locations[n].models.always.l2.level = 8;
			Locations[n].models.always.l2.tech = "DLightModel";
			Locations[n].models.always.l3 = "plan3";
			Locations[n].models.always.l3.level = 7;
			Locations[n].models.always.l3.tech = "DLightModel";
			locations[n].models.day.charactersPatch = "jungle10_patch";
			locations[n].models.night.charactersPatch = "jungle10_patch";
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			locations[n].reload.l1.name = "reload1_back";
			locations[n].reload.l1.go = "Pearl_town_2";
			locations[n].reload.l1.emerge = "reload1";
			locations[n].reload.l1.autoreload = "1";
			locations[n].reload.l1.label = "Village";
			locations[n].locators_radius.reload.reload1_back = 2;
			locations[n].reload.l2.name = "reload2_back";
			locations[n].reload.l2.go = "Pearl_Jungle_06";
			locations[n].reload.l2.emerge = "reload1";
			locations[n].reload.l2.autoreload = "1";
			locations[n].reload.l2.label = "Jungle";
			locations[n].locators_radius.reload.reload2_back = 2;
			n++;
		
			locations[n].id = "Pearl_Jungle_08";
			locations[n].id.label = "Jungle";
			locations[n].image = "loading\jonny_load\jungle\Jungle7.tga";
			locations[n].DisableEncounters = true;
			locations[n].type = "jungle";
			locations[n].islandId = "Mein";
			locations[n].islandIdAreal = "Pearl";
			locations[n].filespath.models = "locations\Outside\Jungles\Jungle7";
			Locations[n].models.always.jungle = "jungle7";
			Locations[n].models.always.locators = "jungle7_locators";
			Locations[n].models.always.grassPatch = "jungle7_grass";
			Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
			Locations[n].models.always.l1 = "plan1";
			Locations[n].models.always.l1.level = 9;
			Locations[n].models.always.l1.tech = "DLightModel";
			Locations[n].models.always.l2 = "plan2";
			Locations[n].models.always.l2.level = 8;
			Locations[n].models.always.l2.tech = "DLightModel";
			Locations[n].models.always.l3 = "plan3";
			Locations[n].models.always.l3.level = 7;
			Locations[n].models.always.l3.tech = "DLightModel";
			locations[n].models.day.charactersPatch = "jungle7_patch";
			locations[n].models.night.charactersPatch = "jungle7_patch";
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			locations[n].reload.l1.name = "reload2_back";
			locations[n].reload.l1.go = "Pearl_Jungle_06";
			locations[n].reload.l1.emerge = "reload3";
			locations[n].reload.l1.autoreload = "1";
			locations[n].reload.l1.label = "Jungle";
			locations[n].locators_radius.reload.reload2_back = 2;
			locations[n].reload.l2.name = "reload1_back";
			locations[n].reload.l2.go = "Pearl_Jungle_09";
			locations[n].reload.l2.emerge = "reload1";
			locations[n].reload.l2.autoreload = "1";
			locations[n].reload.l2.label = "Jungle";
			locations[n].locators_radius.reload.reload1_back = 2; 
			locations[n].reload.l3.name = "reload3_back";
			locations[n].reload.l3.go = "IndianVillage";
			locations[n].reload.l3.emerge = "reload1";
			locations[n].reload.l3.autoreload = "1";
			locations[n].reload.l3.label = "IndianVillage";
			locations[n].locators_radius.reload.reload3_back = 2;
			n++;
		
			locations[n].id = "Pearl_Jungle_09";
			locations[n].id.label = "Jungle";
			locations[n].image = "loading\jonny_load\jungle\Jungle9.tga";
			locations[n].DisableEncounters = true;
			locations[n].type = "jungle";
			locations[n].islandId = "Mein";
			locations[n].islandIdAreal = "Pearl";
			locations[n].filespath.models = "locations\Outside\Jungles\Jungle9";
			Locations[n].models.always.jungle = "jungle9";
			Locations[n].models.always.nowall = "jungle9_nowall";
			Locations[n].models.always.jungle9_wall = "jungle9_wall";
			Locations[n].models.always.locators = "jungle9_locators";		
			Locations[n].models.always.grassPatch = "jungle9_grass";
			Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
			Locations[n].models.always.l1 = "plan1";
			Locations[n].models.always.l1.level = 9;
			Locations[n].models.always.l1.tech = "DLightModel";
			Locations[n].models.always.l2 = "plan2";
			Locations[n].models.always.l2.level = 8;
			Locations[n].models.always.l2.tech = "DLightModel";
			Locations[n].models.always.l3 = "plan3";
			Locations[n].models.always.l3.level = 7;
			Locations[n].models.always.l3.tech = "DLightModel";	
			locations[n].models.day.charactersPatch = "jungle9_patch2";
			locations[n].models.night.charactersPatch = "jungle9_patch2";	
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			locations[n].reload.l1.name = "reload1_back";
			locations[n].reload.l1.go = "Pearl_Jungle_08";
			locations[n].reload.l1.emerge = "reload1";
			locations[n].reload.l1.autoreload = "1";
			locations[n].reload.l1.label = "Jungle";
			locations[n].locators_radius.reload.reload1_back = 2;
			locations[n].private1.key = "keyMorgan";
			locations[n].private1.key.delItem = true;
			locations[n].private1.items.Map_Best = 1;
			locations[n].private1.items.icollection = 1;
			locations[n].private1.items.jewelry9 = 500;
			locations[n].private1.items.Map_Best = 1;
			n++;
		
			locations[n].id = "PearlTown2_HK2";
			locations[n].filespath.models = "locations\inside\Smallhome";
			locations[n].id.label = "House";
			locations[n].image = "loading\jonny_load\inside\Smallhome_k2.tga";
			locations[n].MustSetReloadBack = true;
			locations[n].townsack = "Pearl_town_2";
			locations[n].lockWeather = "Inside";
			locations[n].type = "house";
			locations[n].islandId = "Mein";
			locations[n].islandIdAreal = "Pearl";
			locations[n].models.always.locators = "SH_l";
			locations[n].models.always.tavern = "SH";
			locations[n].models.always.tavern.level = 65538;
			locations[n].models.always.window = "SH_w";
			locations[n].models.always.window.tech = "LocationWindows";
			locations[n].models.always.window.level = 65539;
			locations[n].models.always.back = "..\inside_back";
			locations[n].models.always.back.level = 65529;
			locations[n].models.day.charactersPatch = "SH_p";
			locations[n].models.night.charactersPatch = "SH_p";
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			locations[n].reload.l1.name = "reload1";
			locations[n].reload.l1.go = "Pearl_town_2";
			locations[n].reload.l1.emerge = "reloadH4";
			locations[n].reload.l1.autoreload = "0";
			locations[n].reload.l1.label = "Street";
			LAi_LocationFightDisable(&locations[n], true);
			n++;
		
			locations[n].id = "PearlTown2_Hut1";
			locations[n].id.label = "House";
			locations[n].image = "loading\jonny_load\inside\Hut1_KNS.tga";
			locations[n].MustSetReloadBack = true;
			locations[n].townsack = "LaVega";
			locations[n].lockWeather = "Inside";
			locations[n].islandId = "Hispaniola";
			locations[n].type = "house";
			locations[n].fastreload = "LaVega";
			locations[n].filespath.models = "locations\inside\Hut1_KNS";
			locations[n].models.always.locators = "Hut1_locators";
			locations[n].models.always.tavern = "Hut1";
			locations[n].models.always.tavern.level = 65538;
			locations[n].models.always.window = "Hut1_window";
			locations[n].models.always.window.tech = "LocationWindows";
			locations[n].models.always.window.level = 65539;
			locations[n].models.always.back = "..\inside_back";
			locations[n].models.always.back.level = 65529;
			locations[n].models.day.charactersPatch = "Hut1_patch";
			locations[n].models.night.charactersPatch = "Hut1_patch";
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			Locations[n].QuestlockWeather = "23 Hour";
			locations[n].reload.l1.name = "reload1";
			locations[n].reload.l1.go = "Pearl_town_2";
			locations[n].reload.l1.emerge = "reloadH1";
			locations[n].reload.l1.autoreload = "0";
			locations[n].reload.l1.label = "Street";
			locations[n].reload.l2.name = "reload2";
			locations[n].reload.l2.go = "Pearl_town_2";
			locations[n].reload.l2.emerge = "reloadH3";
			locations[n].reload.l2.autoreload = "0";
			locations[n].reload.l2.label = "Street";
			n++;
		
			Locations[n].id = "IndianVillage";
			locations[n].id.label = "Village";
			locations[n].image = "loading\jonny_load\outside\IndianVillage.tga";
			locations[n].IndianVillage = true;
			locations[n].type = "jungle";
			locations[n].islandId = "Mein";
			locations[n].islandIdAreal = "IndianVillage";
			Locations[n].filespath.models = "locations\Outside\IndianVillage";
			Locations[n].models.always.pirateFort = "village";
			Locations[n].models.always.locators = "village_locators";
			Locations[n].models.always.grassPatch = "village_grass";
			Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
			Locations[n].models.always.l1 = "plan1";
			Locations[n].models.always.l1.level = 9;
			Locations[n].models.always.l1.tech = "DLightModel";
			Locations[n].models.always.l2 = "plan2";
			Locations[n].models.always.l2.level = 8;
			Locations[n].models.always.l2.tech = "DLightModel";
			Locations[n].models.always.l3 = "plan3";
			Locations[n].models.always.l3.level = 7;
			Locations[n].models.always.l3.tech = "DLightModel";
			locations[n].models.day.charactersPatch = "village_patch";
			locations[n].models.night.charactersPatch = "village_patch";
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			Locations[n].reload.l1.name = "reload1_back";
			Locations[n].reload.l1.go = "Pearl_Jungle_08";
			Locations[n].reload.l1.emerge = "reload3";
			Locations[n].reload.l1.label = "Jungle";
			Locations[n].reload.l1.autoreload = 1;
			Locations[n].locators_radius.reload.reload1_back = 2;
			Locations[n].reload.l2.name = "reload2";
			Locations[n].reload.l2.go = "Indian_Hut1";
			Locations[n].reload.l2.emerge = "reload1";
			Locations[n].reload.l2.label = "Hut";
			Locations[n].reload.l2.autoreload = 0;
			Locations[n].reload.l3.name = "reload3";
			Locations[n].reload.l3.go = "Indian_Hut2";
			Locations[n].reload.l3.emerge = "reload1";
			Locations[n].reload.l3.label = "Hut";
			Locations[n].reload.l3.autoreload = 0;
			Locations[n].reload.l4.name = "reload4";
			Locations[n].reload.l4.go = "Indian_Hut3";
			Locations[n].reload.l4.emerge = "reload1";
			Locations[n].reload.l4.label = "Hut";
			Locations[n].reload.l4.autoreload = 0;
			n++;
		
			locations[n].id = "Indian_Hut1";
			locations[n].id.label = "Village";
			locations[n].image = "loading\jonny_load\inside\IndianHut1.tga";
			locations[n].townsack = "Pearl_town_2";
			locations[n].lockWeather = "Inside";
			locations[n].type = "Hut";
			locations[n].islandId = "Mein";
			locations[n].islandIdAreal = "IndianVillage";
			locations[n].filespath.models = "locations\inside\HutIndian1";
			locations[n].models.always.mediumhouse01 = "Hut_1_inside";
			locations[n].models.always.mediumhouse01.level = 65538;
			locations[n].models.always.locators = "Hut_1_inside_locators";
			locations[n].models.always.back = "..\inside_back2";
			locations[n].models.always.back.level = 65529;
			locations[n].models.day.charactersPatch = "Hut_1_inside_patch";
			locations[n].models.night.charactersPatch = "Hut_1_inside_patch";
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			locations[n].reload.l1.name = "reload1";
			locations[n].reload.l1.go = "IndianVillage";
			locations[n].reload.l1.emerge = "reload2";
			locations[n].reload.l1.autoreload = "0";
			locations[n].reload.l1.label = "IndianVillage";
			LAi_LocationFightDisable(&locations[n], true);
			n++;
		
			locations[n].id = "Indian_Hut2";
			locations[n].id.label = "Village";
			locations[n].image = "loading\jonny_load\inside\IndianHut2.tga";
			locations[n].townsack = "Pearl_town_2";
			locations[n].lockWeather = "Inside";
			locations[n].type = "Hut";
			locations[n].islandId = "Mein";
			locations[n].islandIdAreal = "IndianVillage";
			locations[n].filespath.models = "locations\inside\HutIndian2";
			locations[n].models.always.Hut_2_inside = "Hut_2_inside";
			locations[n].models.always.Hut_2_inside.level = 65538;
			Locations[n].models.always.Hut_2_insiderand = "Hut_2_inside_rand_1";
			locations[n].models.always.Hut_2_back = "Hut_2_back";
			locations[n].models.always.Hut_2_back.level = 65538; 
			locations[n].models.always.back = "..\inside_back2";
			locations[n].models.always.back.level = 65529;
			locations[n].models.day.charactersPatch = "Hut_2_inside_patch";
			locations[n].models.day.locators = "Hut_2_inside_locators";
			locations[n].models.night.charactersPatch = "Hut_2_inside_patch";
			locations[n].models.night.locators = "Hut_2_inside_locators";
			locations[n].models.night.l2 = "Hut_2_inside_ln";
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			locations[n].reload.l1.name = "reload1";
			locations[n].reload.l1.go = "IndianVillage";
			locations[n].reload.l1.emerge = "reload3";
			locations[n].reload.l1.autoreload = "0";
			locations[n].reload.l1.label = "IndianVillage";
			LAi_LocationFightDisable(&locations[n], true);
			n++;
		
			locations[n].id = "Indian_Hut3";
			locations[n].id.label = "Village";
			locations[n].image = "loading\jonny_load\inside\IndianHut2.tga";
			locations[n].townsack = "Pearl_town_2";
			locations[n].lockWeather = "Inside";
			locations[n].type = "Hut";
			locations[n].islandId = "Mein";
			locations[n].islandIdAreal = "IndianVillage";
			locations[n].filespath.models = "locations\inside\HutIndian2";
			locations[n].models.always.Hut_2_inside = "Hut_2_inside";
			locations[n].models.always.Hut_2_inside.level = 65538;
			Locations[n].models.always.Hut_2_insiderand = "Hut_2_inside_rand_2";
			locations[n].models.always.back = "..\inside_back2";
			locations[n].models.always.back.level = 65529;
			locations[n].models.day.charactersPatch = "Hut_2_inside_patch";
			locations[n].models.day.locators = "Hut_2_inside_locators";
			locations[n].models.day.l2 = "Hut_2_inside_ln";
			locations[n].models.night.charactersPatch = "Hut_2_inside_patch";
			locations[n].models.night.locators = "Hut_2_inside_locators";
			locations[n].models.night.l2 = "Hut_2_inside_ln";
			locations[n].environment.weather = "true";
			locations[n].environment.sea = "false";
			locations[n].reload.l1.name = "reload1";
			locations[n].reload.l1.go = "IndianVillage";
			locations[n].reload.l1.emerge = "reload4";
			locations[n].reload.l1.autoreload = "0";
			locations[n].reload.l1.label = "IndianVillage";
			LAi_LocationFightDisable(&locations[n], true);
			n++;

			nLocationsNum = n;//чтобы знать, сколько локаций в массиве фактически. Не обязательно совпадает с MAX_LOCATIONS
			Trace("Number of locations: " + nLocationsNum);

			string segmentName = "Characters\" + LanguageGetLanguage() + "\Indian_names.c";
			if( LoadSegment(segmentName) )	{InitIndianNames(); UnloadSegment(segmentName);} 
				else {Trace("Error! Can`t Load Segment: " + segmentName);}

			pchar.fixsaveNG0 = GetVerNum();//08.03.2023
		}
	}
}

void ProcessCheat()
{
	string sCheatName;
	ref mc;
	sCheatName = GetEventData();
	mc = GetMainCharacter();

	switch(sCheatName)
	{
		case "Immortal":
			if(LAi_IsImmortal(GetMainCharacter()))
			{
				LAi_SetImmortal(GetMainCharacter(), false);
				Log_SetStringToLog("God mode OFF");
			}else{

				LAi_SetImmortal(GetMainCharacter(), true);
				Log_SetStringToLog("God mode ON");
			}
		break;
		case "ShotGun":
			if(globalSGMode != false)
			{
				globalSGMode = false;
				Log_SetStringToLog("Shotgun mode OFF");
			}else{
				globalSGMode = true;
				Log_SetStringToLog("Shotgun mode ON");
			}
		break;
		case "Gold":
			mc.money = sti(mc.money) + 100000;
			Log_SetStringToLog(" + 100000 G");
		break;
		case "Skill":
			mc.skill.freeskill = 1;

			mc.skill.freeskill = sti(mc.skill.freeskill) + 50;
			Log_SetStringToLog(" + 50 SP");
		break;
		case "Reputation":
			mc.reputation = REPUTATION_NEUTRAL;
			Log_SetStringToLog("Reputation Set to NEUTRAL");
		break;
		case "Morale":

		break;
		case "Encounters":
			if(CheckAttribute(mc,"worldmapencountersoff") == 0)
			{
				mc.worldmapencountersoff = "1";
				Log_SetStringToLog("Worldmap encounters OFF");
			}
			else
			{
				if(mc.worldmapencountersoff == "1")
				{
					mc.worldmapencountersoff = "0";
					Log_SetStringToLog("Worldmap encounters ON");
				}
				else
				{
					mc.worldmapencountersoff = "1";
					Log_SetStringToLog("Worldmap encounters OFF");
				}
			}
		break;
		case "MainCharacter":
			mc.model	= "Danielle";
			mc.sex = "woman";
			mc.FaceId = 30;
			mc.model.animation = "woman";
			mc.model.height = 1.75;
		break;
		case "soundoff":
			SendMessage(&Sound,"ll",MSG_SOUND_SET_ENABLED,0);
			Log_SetStringToLog("Sound OFF");
		break;
	}
}

object Camera;

void ProcessCameraPosAng()
{
	Camera.Pos.x = GetEventData();
	Camera.Pos.y = GetEventData();
	Camera.Pos.z = GetEventData();

	Camera.Ang.x = GetEventData();
	Camera.Ang.y = GetEventData();
	Camera.Ang.z = GetEventData();
}

void proc_break_video()
{
	PictureAsVideoBreak();
	if (sti(InterfaceStates.videoIdx) != 1)
	{
	}
}

void Main()
{
	if (!CheckAttribute(InterfaceStates,"VISUAL_CIRASS")) InterfaceStates.VISUAL_CIRASS = 0;
	screenscaling = BI_COMPARE_HEIGHT;
    //LayerCreate(REALIZE, 1);
	//LayerCreate(SEA_REALIZE, 1);
	//LayerCreate("net_realize", 1);
	//LayerCreate(INTERFACE_REALIZE, 1);
	//LayerCreate("fader_realize", 1);
	//LayerCreate("inf_realize", 1);

	ReloadProgressStart();

	ControlsInit(GetTargetPlatform(),true, 0);
	nTeleportLocation = 1;

	NationsInit();
	ReloadProgressUpdate();

	EncountersInit();
	ReloadProgressUpdate();

	CannonsInit();
	ReloadProgressUpdate();

	ShipsInit();
	ReloadProgressUpdate();

	IslandsInit();
	ReloadProgressUpdate();

	WeatherInit();
	ReloadProgressUpdate();

	InitPerks();
	ReloadProgressUpdate();

	// Init network, clear massives and load favorite list
	ReloadProgressUpdate();

	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	SetEventHandler("Control Activation","proc_break_video",0);
	InterfaceStates.Launched = false;
	SetEventHandler(EVENT_END_VIDEO,"Main_LogoVideo",0);
	InterfaceStates.videoIdx = 1;
	Event(EVENT_END_VIDEO);
	ReloadProgressEnd();

	SetGlowParams(1.0, 50, 2);
}

void Main_InitGame()
{
    //LayerCreate(REALIZE, 1);
	//LayerCreate(SEA_REALIZE, 1);
	//LayerCreate("net_realize", 1);
	//LayerCreate(INTERFACE_REALIZE, 1);
	//LayerCreate("fader_realize", 1);
	//LayerCreate("inf_realize", 1);

	nTeleportLocation      = 1;
    bDisableLandEncounters = false;
	bDisableCharacterMenu  = false;
	bWorldAlivePause       = true;
	bPauseContrabandMetro  = false;
	bMonstersGen           = false;
	bLandEncountersGen     = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	bDisableMapEnter           = false;
	bDisableSailTo             = false;
	bEnableIslandSailTo        = false;
	bReloadCanBe               = false;
	bMapEnter                  = false;
	bQuestDisableMapEnter      = false;
    bAbordageStarted           = false;
    bCabinStarted              = false;
	bDeckBoatStarted           = false;
	LAi_IsCapturedLocation     = false;
	LAi_IsBoarding             = false;
	LAi_restoreStates          = false;
	LAi_boarding_process       = false;
	boarding_location          = -1;

	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();
	// Init network, clear massives and load favorite list
	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
}
void Main_LogoVideo()
{
	int i = sti(InterfaceStates.videoIdx);
	switch(i)
	{
	case 1:
		InterfaceStates.videoIdx = 4;
		StartPostVideo("Title",1);
	break;

	default:
		DelEventHandler(EVENT_END_VIDEO,"Main_LogoVideo");
		DeleteClass(&aviVideoObj);
		Event("DoInfoShower","sl","game prepare",true);
		SetEventHandler("frame","Main_Start",1);
	break;
	}

}

void Main_Start()
{
	ReloadProgressStart();

	DelEventHandler("Control Activation","proc_break_video");
	DelEventHandler("frame","Main_Start");

	if( GetTargetPlatform()=="pc" )	ControlsInit(GetTargetPlatform(),false, 0);

	ReloadProgressUpdate();
	InitGame();
	ReloadProgressUpdate();

	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0;
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;


	InterfaceStates.Buttons.Load.enable = true;

	Event("DoInfoShower","sl","game prepare",false);

	StartLanguageSetting(LanguageGetLanguage());
 	LoadPlayerProfileDefault(); // boal
	LaunchMainMenu();
	//LaunchNetTopListScreen();

	CharacterIsDead(GetMainCharacter());

	ReloadProgressEnd();
}

void SaveGame()
{
	string saveName = GetEventData();
	string saveData = GetEventData();
	DelEventHandler("evntSave","SaveGame");

	aref arTmp;
	if( !GetEntity(arTmp,"fader") )
	{
		//implement interface
		//LaunchQuickSaveMenu();
		pchar.version_number = 104;
		SaveEngineState(saveName);
		ISetSaveData(saveName,saveData);
	}

	//hide interface
	PostEvent("DoInfoShower",1,"sl","save game",false);
	DeleteEntitiesByType("scrshoter");
	HideQuickSaveMenu();
}

void LoadGame()
{
    PauseParticles(true); //fix вылета у форта
    // не помогло DeleteFortEnvironment();  //fix

	PauseAllSounds(); // boal fix
    ResetSound();  // fix
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	string saveName = GetEventData();
	DelEventHandler("evntLoad","LoadGame");

	string retStr="";
	SendMessage(&GameInterface,"lse",MSG_INTERFACE_GET_SAVE_DATA,saveName,&retStr);
	if( retStr=="" ) {return;}

	DeleteEntities();
	ClearEvents();
	ClearPostEvents();
	SetTimeScale(1.0);
	TimeScaleCounter = 0;

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	SendMessage(&reload_fader, "ls",FADER_PICTURE0, "loading\jonny_load\load\load_03.tga");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	ReloadProgressStart();
	pchar.savegamename = saveName;
	SetEventHandler("frame","LoadGame_continue",1);
	iCalculateSaveLoadCount("Load");
}

void LoadGame_continue()
{
	DelEventHandler("frame","LoadGame_continue");
	FreezeGroupControls(curKeyGroupName,true);
	LoadEngineState(pchar.savegamename);
}

void InterfaceDoExit()
{
	DelEventHandler("frame","InterfaceDoExit");
	InterfaceStates.Launched=false;
	if(sti(InterfaceStates.doUnFreeze)==true)
	{
		SendMessage(&GameInterface,"l",MSG_INTERFACE_RELEASE);
		if(!IsEntity(&aviVideoObj))
		{
			if( bSeaActive && !bAbordageStarted )
			{
				LayerFreeze(SEA_REALIZE,false);
				LayerFreeze(SEA_EXECUTE,false);
			}
			else
			{
				LayerFreeze(REALIZE,false);
				LayerFreeze(EXECUTE,false);
			}
		}
		DeleteAttribute(&GameInterface,"");
	}
	switch(interfaceResultCommand)
	{
		case RC_INTERFACE_FORTCAPTURE_EXIT:
			ReloadAfterFortCapture();
			break;

		case RC_INTERFACE_DO_NOTHING:
			break;
		case RC_INTERFACE_MAIN_MENU_EXIT:
			break;
		case RC_INTERFACE_DO_NEW_GAME:
			InterfaceStates.doUnFreeze = false;
			DeleteEntities();
			ResetSound();  // fix
			ClearEvents();
			ClearPostEvents();

            if (CheckAttribute(pchar, "HeroParam")) // признак, что есть герой
            {
				trace("Main_InitGame");
				Main_InitGame(); // boal вынес все в одинметод, новая игра из страой глючит
			}
			else
			{
				if(LoadSegment("Interface\BaseInterface.c"))
				{
					InitBaseInterfaces_main();
					InitBaseInterfaces();
					UnloadSegment("Interface\BaseInterface.c");
				}
			}
			DeleteEntities();
			ClearEvents();
			SetEventHandler("frame","NewGame",1);
			InterfaceStates.doUnFreeze = false;
		break;
		case RC_INTERFACE_DO_LOAD_GAME:
			if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
			{
				LaunchLoadGame(false);
			}
			else
			{
				LaunchLoadGame(true);
			}
			break;
		case RC_INTERFACE_DO_SAVE_GAME:
			LaunchSaveGame();
			break;
		case RC_INTERFACE_DO_OPTIONS:
			LaunchOptionScreen();
			break;

		case RC_INTERFACE_LOCKPICK: //New Abilities - взлом сундука
			LaunchLockPicking();
		break;

		case RC_INTERFACE_DO_CREDITS:
		    LaunchAboutScreen();
		break;
		case RC_INTERFACE_DO_RESUME_GAME:
		break;
		case RC_INTERFACE_RANSACK_MAIN_EXIT:
			Return2SeaAfterAbordage();
			break;
		case RC_INTERFACE_CHARACTER_SELECT_EXIT:
			DoQuestFunctionDelay("WayBeginning", 1.0);
		break;
		case RC_INTERFACE_SPEAK_EXIT_AND_CAPTURE:
			string sTargetChr = pchar.speakchr;
			pchar.abordage = 1;
			Sea_AbordageStartNow(SHIP_ABORDAGE, GetCharacterIndex(sTargetChr), true, true);
			SetTimeScale(1.0);
			TimeScaleCounter = 0;
			DelPerkFromActiveList("TimeSpeed"); //boal
			pchar.speakchr = 0;
			pchar.whospeak = 0;
		break;
		case RC_INTERFACE_SPEAK_EXIT_AND_TRADE:
			LaunchStore(SHIP_STORE);
		break;
		case RC_INTERFACE_TO_CHAR:
			pchar = GetMainCharacter();
			LaunchCharacter(pchar);
		break;
		case RC_INTERFACE_TO_SHIP:
			LaunchShipState();
		break;
		case RC_INTERFACE_TO_LOGBOOK:
			LaunchQuestBook();
		break;
		case RC_INTERFACE_TO_ITEMS:
			LaunchItems(); // to_do
		break;
		case RC_INTERFACE_LAUNCH_GAMEMENU:
			LaunchGameMenuScreen();
			break;
		// boal -->
  		case RC_INTERFACE_DO_BOAL_BETA:
		     LaunchBoalBetaScreen();
        break;
		// boal <--

		// Warship -->
		case RC_INTERFACE_BEST_MAP:
			LaunchBestMapScreen(); // Смотрим отличную карту
			break;
		// <-- Warship

		case RC_INTERFACE_MAPVIEW:
			LaunchMapViewScreen(); // Смотрим атлас карт
			break;
		case RC_INTERFACE_POINTS_EX:
			LaunchPointsEX();
			break;
		// Крафт
		case RC_INTERFACE_CRAFT_ALL:
			LaunchCraftAll();
		break;
	}
}
void EngineLayersOffOn(bool on)
{
	on = !on;
	if( on ) {
		LayerFreeze(REALIZE,on);
		LayerFreeze(EXECUTE,on);
		LayerFreeze(SEA_REALIZE,on);
		LayerFreeze(SEA_EXECUTE,on);
	} else {
		if(bSeaActive && !bAbordageStarted) {
			LayerFreeze(SEA_REALIZE,on);
			LayerFreeze(SEA_EXECUTE,on);
		} else {
			LayerFreeze(REALIZE,on);
			LayerFreeze(EXECUTE,on);
		}
	}
}

string seadogs_saveFrom = "";

void OnSave()
{
	seadogs_saveFrom = "";
	if(IsEntity(&worldMap) != 0)
	{
		seadogs_saveFrom = "world map";
	}
	else
	{
		if(IsEntity(&AISea) != 0)
		{
			Sea_Save();
			seadogs_saveFrom = "sea";
		}
		else
		{
			int ldLoc = FindLoadedLocation();
			if(ldLoc >= 0)
			{
				seadogs_saveFrom = "location";
				SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_SETCHRPOSITIONS);
				LAi_SaveInfo();
				PostEvent("SeaDogs_ClearSaveData", 400, "a", &Locations[ldLoc]);
			}
			else
			{
				Trace("OnSave() -> unknown character location");
			}
		}
	}
	iCalculateSaveLoadCount("Save");
}

//#20180226-01
bool CanSave()
{
    bool bReturn = false;
    if(IsEntity(&worldMap) != 0)
	{
		bReturn = true;
	}
	else
	{
		if(IsEntity(&AISea) != 0)
		{
			bReturn = true;
		}
		else
		{
			int ldLoc = FindLoadedLocation();
			if(ldLoc >= 0)
			{
				bReturn = true;
			}
		}
	}
	return bReturn;
}

void ClearLocationsSaveData()
{
	aref loc = GetEventData();
	SendMessage(loc, "l", MSG_LOCATION_CLRCHRPOSITIONS);
}

int actLoadFlag = 0;

void OnLoad()
{
	actLoadFlag = 1;

	if(screenscaling < 50) screenscaling = BI_COMPARE_HEIGHT;

	bYesBoardStatus=false;
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");

	//Boyer add
	//onLoadReInit();
	SpecOfficersCirass();
	//Boyer change #20170418-01
	//restoreQuestItems(); не нужно в отсутствие реинитов - Gregg
	//End Boyer add
	DeleteAttribute( pchar, "abordage_active_count" );
	FreezeGroupControls(curKeyGroupName,false);

	if( CharacterIsDead(pchar) ) {
		pchar.chr_ai.hp = 1.0;
	}

	Nation_InitAfterLoading();
	ResetSound();

	//CreateClass("dummy");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		//InitBaseInterfaces_main();
		InitBaseInterfaces();
		InitInterfaceTables();
		UnloadSegment("Interface\BaseInterface.c");
	}

	ReloadProgressUpdate();

	DialogsInit();
	//IslandsInit();
	//LocationInit();

	ReloadProgressUpdate();

	//Boyer add to fix missing ship init
	ShipsInit();

	InitCharacterEvents();
	ReloadProgressUpdate();

	QuestsInit();
	ReloadProgressUpdate();

	InitTeleport();
	ReloadProgressUpdate();

	InitParticles();
	ReloadProgressUpdate();
	//ImportFuncTest();
	
	if (firstFreeCharacter == -1) {
		for (int i = GlobalCharacters; i < MAX_CHARACTERS; i++) {
			ref chr = GetCharacter(i);
			if (!CheckAttribute(chr, "id") || chr.id == "0") {
				FreeCharacter(i);
			}
		}
		trace("Освободили " + (firstFreeCharacter + 1));
	}

	WeatherInit();
	ReloadProgressUpdate();

	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;

	//#20190327-01
	if(!CheckAttribute(pchar, "camEye"))
        pchar.camEye = 0;

	SM_PusherOnLoad();

	if(seadogs_saveFrom == "location")
	{
		ref mainchar;
		mainchar = GetMainCharacter();
		// boal: лажа это!!  есть actLoadFlag  //mainchar.isload = 1;
		LoadMainCharacterInFirstLocation(mainchar.location,"", mainchar.location.from_sea);
		int ldLoc = FindLoadedLocation();
		if(ldLoc >= 0)
		{
			SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_TLPCHRPOSITIONS);
		}
	}
	else
	{
		if (seadogs_saveFrom == "sea")
		{
			Sea_Load();
 		}
		else
		{
			if(seadogs_saveFrom == "world map")
			{
				wdmLoadSavedMap();
			}
			else
			{
				Trace("Unknown seadogs_saveFrom == " + seadogs_saveFrom);
			}
		}
	}

	//ReloadEndFade();
	EngineLayersOffOn(true);
	//NewGame();
	DialogRun = false;
	InterfaceStates.Launched = false;

	ReloadProgressUpdate();

	PerkLoad(false);

	ReloadProgressUpdate();

	LoadGameOptions();

	ReloadProgressEnd();
    //#20200519-02
    BattleInterface.ShifInfoVisible = InterfaceStates.enabledshipmarks;
    BattleInterface.battleborder.used = InterfaceStates.ShowBattleMode;
	if( CheckAttribute(&InterfaceStates,"WorldSituationUpdateStep") &&
		sti(InterfaceStates.WorldSituationUpdateStep) < 10 )
	{
		Event("EvSituationsUpdate", "l", sti(InterfaceStates.WorldSituationUpdateStep));
	}

	actLoadFlag = 0;
	////
	ProcessVersionCheck();

	//#20181015-02
	if(bSeaActive && !bMapEnter)
        Sound_OnSeaAlarm555(seaAlarmed, true);

	iCalculateSaveLoadCount("Load");
}

void NewGame()
{
	DeleteEntities();
	DelEventHandler("frame","NewGame");

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	SendMessage(&reload_fader, "ls",FADER_PICTURE0, "loading\jonny_load\load\load_03.tga");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);

	bYesBoardStatus=false;
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");

	for (i = 0; i < TOTAL_CHARACTERS; i++) InitCharacter(&Characters[i], i);

	SetEventHandler("frame","NewGame_continue",1);
}

void NewGame_continue()
{
	DeleteAttribute( pchar, "abordage_active_count" );  // это тут не рабоатет :)  Но и не мешает Boal

	ReloadProgressStart();

	DelEventHandler("frame","NewGame_continue");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	InitGame();

	ReloadProgressUpdate();

	CreateColonyCommanders();

	ReloadProgressUpdate();

	SetNames();
	ReloadProgressUpdate();

	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0; //boal
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;

	InterfaceStates.WorldSituationUpdateStep = 100;
	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;

	pchar = GetMainCharacter(); //fix
	//#20190327-01
    pchar.camEye = 0;
	setNewMainCharacter(pchar, 1);
	ReloadProgressUpdate();

    RumourInit();  //homo 23/06/06
	ReloadProgressUpdate();

	ActivateTimeEvents();

	ReloadProgressUpdate();

	SetDamnedDestinyVariable();
	ReloadProgressUpdate();

	pchar.questTemp.sbormoney = -1;

	//LoadMainCharacterInFirstLocation(sTeleportLocName, sTeleportLocator, sTeleportLocName);
	startGameWeather = true;
	//if (startHeroType > 6)
	//{//Стандартное начало
		InterfaceStates.startGameWeather = FindWeather("11 Hour");
		LoadMainCharacterInFirstLocationGroup("SelectMainCharacter_Cabine", "reload", "reload1");
		pchar.quest.SelectMainCharacterInCabine.win_condition.l1          = "location";
		pchar.quest.SelectMainCharacterInCabine.win_condition.l1.location = "SelectMainCharacter_Cabine";
		pchar.quest.SelectMainCharacterInCabine.function                  = "SelectMainCharacterInCabine";
	ReloadProgressUpdate();

	//InitTowns();
	UpdateCrewInColonies(); // пересчет наемников в городах
	ReloadProgressUpdate();

	//SetQuestForMenInTavernWhoGiveUsInfo(); // to_do
    //#20190909-01
    pchar.fix20190909 = true;
	ReloadProgressUpdate();
	ReloadProgressEnd();
}

void InitGame()
{
	//LayerCreate(REALIZE, 1);
	//LayerCreate(SEA_REALIZE, 1);
	//LayerCreate(INTERFACE_REALIZE, 1);
	//LayerCreate("fader_realize", 1);
	//LayerCreate("inf_realize", 1);

	InitSound();

	ReloadProgressUpdate();

	DeleteSeaEnvironment();
	//CharactersInit();
	if(LoadSegment("worldmap\worldmap_init.c"))
	{
		wdmInitWorldMap();
		UnloadSegment("worldmap\worldmap_init.c");
	}
    InitPerks();
    ReloadProgressUpdate();

	IslandsInit();
	ReloadProgressUpdate();

	LocationInit();
	ReloadProgressUpdate();

	DialogsInit();
	ReloadProgressUpdate();

	InitTeleport();
	ReloadProgressUpdate();

	InitParticles();
	ReloadProgressUpdate();

    if(LoadSegment("items\initItems.c"))
	{
		InitItems();
		UnloadSegment("items\initItems.c");
	}
	ReloadProgressUpdate();
	//Boyer change #20170301-6...CharactersInit assigns RealShips, and after a bunch of 'New' games in a
	//session, RealShips array overflows, so call new function to reset
	ResetRealShipArray();
	ReloadProgressUpdate();

	CharactersInit();
	ReloadProgressUpdate();

	ColoniesInit();
	ReloadProgressUpdate();

	if(LoadSegment("store\initStore.c"))
	{
		InitStores();
		UnloadSegment("store\initStore.c");
	}

	QuestsInit();
	ReloadProgressUpdate();


	SeaAIGroupsInit();
	ReloadProgressUpdate();

	InitQuestMapEncounters();
	ReloadProgressUpdate();

	ResetQuestMovie();
	ReloadProgressUpdate();

	LoadGameOptions();

	ReloadProgressUpdate();
	InfoShowSetting();

}

int counter = 0;
void ProcessControls()
{
	string ControlName;
	ControlName = GetEventData();
	// boal -->
 	aref  arItm;
    int   itmIdx;
	String itemID;
	bool bOk, bOk1;

    if (ControlName == "QuickSave") { MakeQuickSave(); return; }
    if (ControlName == "QuickLoad") { MakeQuickLoad(); return; }

    if (dialogRun) return;
	if (ControlName == "SaveDelete" && CurrentInterface == INTERFACE_SAVELOAD)
	{
		if (XI_IsWindowEnable("PROFILE_WINDOW")){DoConfirm(1); return;}
		else {DoConfirm(2); return;}
	}
	if (sti(InterfaceStates.Launched)==true) return;

	if (ControlName == "WhrPrevWeather")	{ Whr_LoadNextWeather(-1); return; }
	if (ControlName == "WhrNextWeather")	{ Whr_LoadNextWeather(1); return; }
	if (ControlName == "WhrUpdateWeather")	{ Whr_UpdateWeather(); return; }

	//if (ControlName == "Help") RunHelpChooser();

	if(bSeaActive && !bAbordageStarted)
	{
		switch(ControlName)
		{
		    case "Ship_Fire": Ship_DoFire(); return; break;
		    case "Interface": ProcessInterfaceKey(); return; break;
			case "MainMenu": ProcessMainMenuKey();	return; break;
			case "MainMenuDouble": ProcessMainMenuKey(); return; break;
			case "Sea_CameraSwitch": SeaCameras_Switch(); return; break;
			case "Ship_Fire": Ship_DoFire(); break;
			case "Tele": Sea_ReloadStart(); return; break;
			 //// {*} BUHO-CIC - ADDED CODE - Key event response.
            //#20180226-02
            case "CIC_LoadBalls" :
                Log_SetStringToLog("Эскадра, зарядить ядра!");
                CIC_SendCommand(ControlName);
                return;
            break;
            case "CIC_LoadGrapes" :
                Log_SetStringToLog("Эскадра, зарядить картечь!");
                CIC_SendCommand(ControlName);
                return;
            break;
            case "CIC_LoadChain" :
                Log_SetStringToLog("Эскадра, зарядить книпели!");
                CIC_SendCommand(ControlName);
                return;
            break;
            case "CIC_LoadBombs" :
                Log_SetStringToLog("Эскадра, зарядить бомбы!");
                CIC_SendCommand(ControlName);
                return;
            break;
            case "CIC_LoadAtWill" :
                Log_SetStringToLog("Эскадра, зарядка по усмотрению!");
                CIC_SendCommand(ControlName);
				PlayVoice("INTERFACE\SignalCompanion.wav");
                return;
            break;
            case "CIC_SailAway" :
                Log_SetStringToLog("Эскадра, уплыть!");
                CIC_SendCommand(ControlName);
				PlayVoice("INTERFACE\SignalCompanion.wav");
                return;
            break;
            case "CIC_LowerSails" :
                Log_SetStringToLog("Эскадра, спустить паруса!");
                CIC_SendCommand(ControlName);
				PlayVoice("INTERFACE\_strike_down.wav");
                return;
            break;
            case "CIC_ProtFlagship" :
                Log_SetStringToLog("Эскадра, защищать флагман!");
                CIC_SendCommand(ControlName);
				PlayVoice("INTERFACE\SignalCompanion.wav");
                return;
            break;
            //// {*} BUHO END ADDITION
		}
	}
	else
	{
		switch(ControlName)
		{
			case "ChrBlock":
			if (findsubstr(pchar.model.animation, "mushketer" , 0) != -1)
			{
				if (stf(pchar.chr_ai.charge) != 1.0)
				{
					pchar.chr_ai.charge = stf(pchar.chr_ai.charge) + 0.01;
				}
			}
			break;
/*		    // boal -->
            case "ChrBackward": //ChrStrafeLeft ChrStrafeRight
                if (bLandInterfaceStart && LAi_IsFightMode(pchar))
                {
                    pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
                    if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
                }
            return;
            break;
            case "ChrStrafeLeft":
                if (bLandInterfaceStart && LAi_IsFightMode(pchar))
                {
                    pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
                    if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
                }
            return;
            break;
            case "ChrStrafeRight":
                if (bLandInterfaceStart && LAi_IsFightMode(pchar))
                {
                    pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
                    if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
                }	
            return;
            break; */
            case "BOAL_UsePotion": // boal KEY_X
                if (bLandInterfaceStart)
				{
					bool bEnablePotion1 = true;
					if(CheckAttribute(PChar, "AcademyLand"))
					{
						if(PChar.AcademyLand == "Start")
						{
							bEnablePotion1 = sti(PChar.AcademyLand.Temp.EnablePotion);
						}
					}

					if(!bEnablePotion1)
					{
						Log_SetStringToLog("В данный момент запрещено использовать эликсиры.");
					}
					else
					{
						/*itmIdx = FindPotionFromChr(pchar, &arItm, 0);
						while(itmIdx>=0)
						{
						  if( EnablePotionUsing(pchar, arItm) )
						  {
							 DoCharacterUsedItem(pchar, arItm.id);
							 int idLngFile = LanguageOpenFile("save_load.txt");
							 Log_SetStringToLog(LanguageConvertString(idLngFile, "Potion"));
							 break;
						  }
						  itmIdx = FindPotionFromChr(pchar, &arItm, itmIdx+1);
						}*/
						if(LAi_IsPoison(pchar))
						{
							if (UseBestPotion(pchar, true) == 0)
							{
								if (UseBestPotion(pchar, false) == 0)
								{
									Log_SetStringToLog("Не найдено никаких лечебных средств.");
								}
							}
						}
						else
						{
							if (UseBestPotion(pchar, false) == 0)
							{
								if (UseBestPotion(pchar, true) == 0)
								{
									Log_SetStringToLog("Не найдено никаких лечебных средств.");
								}
							}
						}
					}
				}
            return;
            break;
			case "csmRunLootCollector":
				csmLootCollector();
			break;
            case "BOAL_ActivateRush":  // boal KEY_F
				if (bLandInterfaceStart)
				{
					if (GetCharacterPerkUsing(pchar, "Rush") && LAi_IsFightMode(pchar) && PChar.location != "FencingTown_Arena" && PChar.location != "FencingTown_ExitTown")
					{
						ActivateCharacterPerk(pchar, "Rush");
						PlayVoice(GetSexPhrase("interface\Bers_"+rand(5)+".wav","interface\Bersf_"+rand(4)+".wav"));
						pchar.chr_ai.energy    = pchar.chr_ai.energyMax;
					}
					else
                    {
                        PlaySound("knock");
                    }
                }
				return;
            break;

			case "AltModificatorOff":
				if (!IsEntity(&ILogAndActions)) return;
				if(loadedLocation.type == "Underwater") return;
				bAltInfo = false;
				ModifyTextInfo();
			break;

			case "AltModificator":
				if (!IsEntity(&ILogAndActions)) return;
				if(loadedLocation.type == "Underwater") return;
				bAltInfo = true;
				SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
				ModifyTextInfo();
			break;

			case "Fast_port":
				if(bAltInfo)  HKT_Button(ControlName);
			break;

			case "Fast_store":
				if(bAltInfo) HKT_Button(ControlName);

			break;

			case "Fast_Shipyard":
				 if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_tavern":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_townhall":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_bank":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_church":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_Brothel":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_PortOffice":
				if(bAltInfo) HKT_Button(ControlName);
			break;

			case "Fast_prison":
				if(bAltInfo) HKT_Button(ControlName);
			break;

            case "OfficersCharge":
                pchar.OfficerAttRange = 35.0;
                OfficersFollow();
                Log_SetStringToLog("Офицеры, в атаку!");
                return;
            break;
            case "OfficersFree":
                pchar.OfficerAttRange = 35.0;
                OfficersFree();
                Log_SetStringToLog("Офицеры, вольно!");
                return;
            break;
            case "OfficersFollow":
                pchar.OfficerAttRange = 7.0;
                OfficersFollow();
                Log_SetStringToLog("Офицеры, за мной!");
                return;
            break;
            case "OfficersHold":
                pchar.OfficerAttRange = 7.0;
                OfficersHold();
                Log_SetStringToLog("Офицеры, стоять!");
                return;
            break;
			case "MainMenu": ProcessMainMenuKey();	return; break;
			case "MainMenuDouble": ProcessMainMenuKey(); return; break;
			case "Interface": ProcessInterfaceKey();return; break;
			case "Tele":
				StartQuickTeleport();
			return;
            break;
			case "TeleBack": Teleport(-1); return; break;
			case "Action":
			return;
            break;
		}
	}

    // boal 27.11.03 time -->
  	if (ControlName=="TimeScaleFaster" || ControlName == "TimeScaleSlower" ||
		ControlName=="TimeScaleFasterBA" || ControlName=="TimeScaleSlowerBA")
  	{
        //Boyer change #20170318-38
        // if (CheckAttribute(&loadedLocation, "type") && loadedLocation.type == "underwater") return; //запрет ускорения под водой.
		//if (bAltBalance && !bSeaActive && ControlName == "TimeScaleSlower" && TimeScaleCounter == 0)
		if (bAltBalanceTimeSlow && TimeScaleCounter == 0)
		{
			if (ControlName == "TimeScaleSlower" || ControlName == "TimeScaleSlowerBA")
			{
				Log_SetStringToLog("Замедление времени заблокировано.");
				return;
			}

		}
		if (PChar.location == "FencingTown_Arena" || PChar.location == "FencingTown_ExitTown")
		{
			if (InterfaceStates.Buttons.Save.enable == false)
			{
				if (CheckAttribute(pchar,"SkipBattle") && pchar.SkipBattle == true)
				{
					float EffHp1,EffHp2, ASkill1, ASkill2;
					ASkill1 = LAi_GetCharacterFightLevel(CharacterFromID(pchar.ArenaAttack));
					ASkill2 = LAi_GetCharacterFightLevel(CharacterFromID(pchar.ArenaEnemy));
					if (ASkill1 > ASkill2)
					{
						EffHp1 = GetCharacterEffectiveHp(CharacterFromID(pchar.ArenaAttack)) / (1.0 + 0.7 * (ASkill2 - ASkill1));
						EffHp2 = GetCharacterEffectiveHp(CharacterFromID(pchar.ArenaEnemy));
					}
					else
					{
						EffHp1 = GetCharacterEffectiveHp(CharacterFromID(pchar.ArenaAttack));
						EffHp2 = GetCharacterEffectiveHp(CharacterFromID(pchar.ArenaEnemy)) / (1.0 + 0.7 * (ASkill1 - ASkill2));
					}
					Log_TestInfo("Effhp1:" + sti(effhp1) + " Effhp2:" + sti(effhp2));
					if (EffHp1 > EffHp2) 
						LAi_KillCharacter(CharacterFromID(pchar.ArenaEnemy));
					else
						LAi_KillCharacter(CharacterFromID(pchar.ArenaAttack));
					pchar.SkipBattle = false;
					return;
				}
				Log_SetStringToLog("В данный момент запрещены манипуляции временным потоком.");
				return;
			}
		}

		DeleteAttribute(pchar, "pause");
		if (ControlName == "TimeScaleFaster" || ControlName == "TimeScaleFasterBA")
     	{
			if (TimeScaleCounter >= 16){TimeScaleCounter += 16;}
			else
			{
				if (TimeScaleCounter >= 8){TimeScaleCounter += 8;}
				else
				{
					if (TimeScaleCounter >= 4){TimeScaleCounter += 4;}
					else
					{
						if (TimeScaleCounter >= 2){TimeScaleCounter += 2;}
						else {TimeScaleCounter++;}
					}
				}
			}
		}
     	else
     	{
			if (TimeScaleCounter > 16){TimeScaleCounter -= 16;}
			else
			{
				if (TimeScaleCounter > 8){TimeScaleCounter -= 8;}
				else
				{
					if (TimeScaleCounter > 4){TimeScaleCounter -= 4;}
					else
					{
						if (TimeScaleCounter > 2){TimeScaleCounter -= 2;}
						else {TimeScaleCounter--;}
					}
				}
			}
		}
		if (true) // MOD_SKILL_ENEMY_RATE > 1) // запрет 0.25 скорости
        {
		   if (!bBettaTestMode && TimeScaleCounter < -2) TimeScaleCounter = -2;
		}
        if (bDisableMapEnter)
        {
            if (TimeScaleCounter > 48) TimeScaleCounter = 48;
        }
        else
        {   // без боя
            if (bSeaActive && !bAbordageStarted )
            {
            	if (TimeScaleCounter > 48) TimeScaleCounter = 48; // море
            }
            else
            {
            	if (TimeScaleCounter > 32) TimeScaleCounter = 32; // суша
            }
        }
        if (IsEntity(worldMap))
        {
            if (TimeScaleCounter > 32) TimeScaleCounter = 32;
        }
     	float newTimeScale = 1 + (TimeScaleCounter)*0.25; // GetSeaTimeScale()
     	if (newTimeScale < 0) //don't wanna crash the game
     	{
        		TimeScaleCounter = -4;
        		newTimeScale = 0;
     	}

     	Log_SetStringToLog("x" + newTimeScale);
     	if (TimeScaleCounter == 0) //back to normal
     	{
			if(IsPerkIntoList("TimeSpeed"))
        	{
        		SetTimeScale(1.0);
        		DelPerkFromActiveList("TimeSpeed");
        	}
     	}
     	else
     	{
        	SetTimeScale(newTimeScale);
        	//if perk not in list
        	if(!IsPerkIntoList("TimeSpeed"))
        	{
				AddPerkToActiveList("TimeSpeed");
			}
     	}
        return;
	}
	// boal <--
	switch(ControlName)
	{
        case "TimeScale":
            DeleteAttribute(pchar, "pause");
            //Boyer change #20170318-38
            /* if (CheckAttribute(&loadedLocation, "type") && loadedLocation.type == "Underwater") {
				return; //запрет ускорения под водой.
			} */
			if (PChar.location == "FencingTown_Arena" || PChar.location == "FencingTown_ExitTown")
			{
				if (InterfaceStates.Buttons.Save.enable == false)
				{
					Log_SetStringToLog("В данный момент запрещены манипуляции временным потоком.");
					return;
				}
			}
			if(IsPerkIntoList("TimeSpeed"))
			{
				SetTimeScale(1.0);
				TimeScaleCounter = 0;
                Log_SetStringToLog("Time x1");
				DelPerkFromActiveList("TimeSpeed");
			}
			else
			{
				SetTimeScale(GetSeaTimeScale());
				TimeScaleCounter = 4;
                Log_SetStringToLog("Time x2");
				AddPerkToActiveList("TimeSpeed");
			}
		break;

		case "VK_PAUSETimePause":
			if (PChar.location == "FencingTown_Arena" && PChar.location == "FencingTown_ExitTown")
			{
				if (InterfaceStates.Buttons.Save.enable == false)
				{
					Log_SetStringToLog("В данный момент запрещены манипуляции временным потоком.");
					return;
				}
			}
			if (!CheckAttribute(pchar, "pause"))
			{
				pchar.pause = true;
				SetTimeScale(0.0);
			    TimeScaleCounter = -3;
			    AddPerkToActiveList("TimeSpeed");
			}
			else
			{
                DeleteAttribute(pchar, "pause");
				SetTimeScale(1.0);
				DelPerkFromActiveList("TimeSpeed");
				TimeScaleCounter = 0;
			}
		break;
		case "WMapCancel":
			if(IsEntity(&worldMap))
			{
				pchar.space_press = 1;
				DeleteAttribute(pchar, "SkipEshipIndex");// boal
			}
		break;

		case "MushketHotkey":
			if (!CheckAttribute(pchar,"mushket")) break;
			if (!CheckCharacterItem(pchar, pchar.mushket)) break;
			if(LAi_CheckFightMode(pchar))
			{
				if (!CheckAttribute(pchar,"mushket.timer")) pchar.mushket.timer = false;
				if (pchar.mushket.timer) break;
				pchar.mushket.timer = true;
				LAi_SetFightMode(pchar, false);
				LAi_SetActorType(pchar);
				if(pchar.model.animation == "man_fast" || pchar.model.animation == "YokoDias_fast" || pchar.model.animation == "Milenace_fast")
				{
					PostEvent("Event_SwapWeapon", 1400);
					DoQuestFunctionDelay("ReloadMyGun", 1.5);
				}
				if(pchar.model.animation == "man" || pchar.model.animation == "YokoDias" || pchar.model.animation == "Milenace")
				{
					PostEvent("Event_SwapWeapon", 1800);
					DoQuestFunctionDelay("ReloadMyGun", 1.9);
				}
				if(findsubstr(pchar.model.animation, "mushketer" , 0) != -1)
				{
					PostEvent("Event_SwapWeapon3", 800);
					DoQuestFunctionDelay("ReloadMyGun", 0.9);
				}
			}
		break;

		case "PusherHotkey":
			if (!CheckCharacterPerk(pchar, "Buldozer")) break;

			if (!CheckAttribute(pchar,"CSM.CrowdPusher"))
			{
				Log_Info("''Громила'' активирован.");
				SM_PusherEnable();
			}
			else
			{
				Log_Info("''Громила'' деактивирован.");
				SM_PusherDisable();
			}
		break;

		case "Map_Best":
			// if (bBettaTestMode) LaunchPaperMapScreen();
			if(CheckCharacterItem(PChar, "Map_Best") || bBettaTestMode) LaunchBestMapScreen();
		break;

		// --> ugeen
		case "MapView":
			bOk = bSeaActive && !bAbordageStarted;
			bOk1 = bLandInterfaceStart && !LAi_IsFightMode(pchar);
			if(bOk || bOk1)
			{ // изврат - но по другому никак :(
				if(CheckCharacterItem(PChar, "MapsAtlas") && pchar.MapsAtlasCount > 0) LaunchMapViewScreen();
			}
		break;
		// <-- ugeen
	/*	// boal -->
		case "ChrBackward": //ChrStrafeLeft ChrStrafeRight
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;

		case "ChrStrafeLeft":
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;

		case "ChrStrafeRight":
            if (bLandInterfaceStart && LAi_IsFightMode(pchar))
            {
				pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
 				if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
	        }
		break;
*/
		case "BOAL_UsePotion": // boal KEY_C
            if (bLandInterfaceStart)
            {
				bool bEnablePotion = true;
				if(CheckAttribute(PChar, "AcademyLand"))
				{
					if(PChar.AcademyLand == "Start")
					{
						bEnablePotion = sti(PChar.AcademyLand.Temp.EnablePotion);
					}
				}

				if(!bEnablePotion)
				{
					Log_SetStringToLog("В данный момент запрещено использовать эликсиры.");
				}
				else
				{
					if(LAi_IsPoison(pchar))
					{
						if (UseBestPotion(pchar, true) == 0)
						{
							if (UseBestPotion(pchar, false) == 0)
							{
								Log_SetStringToLog("No Potion Found!");
							}
						}
					}
					else
					{
						if (UseBestPotion(pchar, false) == 0)
						{
							if (UseBestPotion(pchar, true) == 0)
							{
								Log_SetStringToLog("No Potion Found!");
							}
						}
					}
				}
	        }
		break;

		// Warship 13.06.09 Выпить противоядие KEY_V
		case "UseAntidote":
			if(bLandInterfaceStart)
            {
				if(FindCharacterAntidote(PChar, &itemID)) // В itemID запишется ID предмета, который можно использовать
				{
					DoCharacterUsedItem(PChar, itemID);
					Log_Info("Use antidote");
				}
			}
		break;
		case "PaperMap":
			LaunchPaperMapScreen();
		break;

        case "BOAL_ActivateRush":  // boal KEY_F
			if (bLandInterfaceStart)
            {
				if (GetCharacterPerkUsing(pchar, "Rush") && LAi_IsFightMode(pchar))
				{
					ActivateCharacterPerk(pchar, "Rush");
					PlayVoice(GetSexPhrase("interface\Bers_"+rand(5)+".wav","interface\Bersf_"+rand(4)+".wav"));
					pchar.chr_ai.energy    = pchar.chr_ai.energyMax;
				}
				else
                {
                    PlaySound("interface\knock.wav");
                }
            }
	    break;

//JA 16/8/09 -->
		case "BOAL_ActivateTurn180":
		if (!CheckOfficersPerk(pchar, "Turn180") && GetOfficersPerkUsing(pchar, "Turn180"))
		{
			ActivateCharacterPerk(pchar,"Turn180");
		}
		else
		{
			Log_Info("Навык не доступен!");
			PlaySound("interface\knock.wav");
		}
		break;

		case "BOAL_ActivateImmediateReload":
		if(bSeaActive == true)
		{
			if (!CheckOfficersPerk(pchar, "ImmediateReload") && GetOfficersPerkUsing(pchar, "ImmediateReload"))
			{
				ActivateCharacterPerk(pchar,"ImmediateReload");
			}
			else
			{
				Log_Info("Навык не доступен!");
				PlaySound("interface\knock.wav");
			}
		}
		break;

		case "BOAL_ActivateLightRepair":
		if(bSeaActive == true)
		{
			if (!CheckOfficersPerk(pchar, "LightRepair") && GetOfficersPerkUsing(pchar,"LightRepair"))
			{
				ActivateCharacterPerk(pchar,"LightRepair");
				ActivateSpecRepair(pchar,0);
			}
			else
			{
				Log_Info("Навык не доступен!");
				PlaySound("interface\knock.wav");
			}
		}
		break;

		case "BOAL_ActivateInstantRepair":
		if(bSeaActive == true)
		{
			if (CheckInstantRepairCondition (pchar))
			{
				ActivateCharacterPerk(pchar,"InstantRepair");
				ActivateSpecRepair(pchar,1);
			}
			else
			{
				Log_Info("Навык не доступен!");
				PlaySound("interface\knock.wav");
			}
		}
		break;
	    case "BOAL_DeadSearch":  // boal KEY_1
			if (bLandInterfaceStart && !bAltInfo)
            {
                itmIdx = Dead_FindCloseBody();
			    if (itmIdx != -1)
			    {
					Dead_OpenBoxProcedure();
				}
				else
				{
                    Log_Info("Некого обыскивать");
				}
		    }
	    break;
//<--JA
		case "BOAL_SetCamera":
		    // по F10
		    //CameraHoldPos();
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF10Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
			else LaunchPsHeroScreen();
		break;
        case "BOAL_Control":
		    // по F11 вызывает окно отладчика
		    if (MOD_BETTATESTMODE == "On" || MOD_BETTATESTMODE == "Test")
		    {
		       LaunchDebuderMenu();
		    }
		break;
		case "BOAL_Control3":
		    // по F9 вызывает окно отладчика
		    if (MOD_BETTATESTMODE == "On")
		    {
		       //LaunchBoalDebugScreenSecond();
		    }
		break;
		case "Person_Say": // KEY_T
			// Интерфейс отдыха
			/*if(bLandInterfaceStart) // В "Мыслях вслух"
				LaunchTavernWaitScreen();*/
		break;

		case "Say": // KEY_Y
			// Интерфейс автозакупки товаров
			if(bLandInterfaceStart && IsPCharHaveTreasurer()) // Если есть казначей и ГГ находится на суше
				LaunchTransferGoodsScreen();
		break;
        case "TeleportActive":
		    if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveF4Control();
            		UnloadSegment("Debuger.c");
            	}
		    }
		break;
		case "BOAL_ControF5":
            if (MOD_BETTATESTMODE == "On")
            {
                if(LoadSegment("Debuger.c"))
                {
                    ActiveF5Control();
                    UnloadSegment("Debuger.c");
                }
                Statistic_AddValue(PChar, "Cheats.F5", 1);
            }
        break;
        case "BOAL_ControF7":
            // по F7 вызывает окно отладчика
            if (MOD_BETTATESTMODE == "On")
            {
                if(LoadSegment("Debuger.c"))
                {
                    ActiveF7Control();
                    UnloadSegment("Debuger.c");
                }
                Statistic_AddValue(PChar, "Cheats.F7", 1);
            }
        break;
        case "BOAL_Control2": // F12
            //Найти ближайшего видимого персонажа в заданном радиусе
            if(LoadSegment("Debuger.c"))
        	{
                ActiveF12Control(); // можно меять пряв в рабочей игре
        		UnloadSegment("Debuger.c");
        	}
        break;
        case "BOAL_ControlDebug": // VK_INSERT
            if (MOD_BETTATESTMODE == "On")
		    {
                if(LoadSegment("Debuger.c"))
            	{
                    ActiveINSERTControl();
            		UnloadSegment("Debuger.c");
            	}
        	}
        break;
		case "UseFood":
			if (bLandInterfaceStart)
			{
				bool bEnableFood = true;
				if(CheckAttribute(PChar, "AcademyLand"))
				{
					if(PChar.AcademyLand == "Start")
					{
						bEnableFood = sti(PChar.AcademyLand.Temp.EnableFood);
					}
				}

				if(!bEnableFood)
				{
					Log_SetStringToLog("В данный момент запрещено использовать еду.");
				}
				else
				{
					pchar.pressedFoodButton = true;
					EatSomeFood();
				}
			}
		break;
        // boal <--
		case "CreateNotice":
			LaunchCreateNotice();
		break;
		case "InterfaceDisabler":
			ChangeShowIntarface();
		break;
	}
}

void Teleport(int step)
{
	nTeleportLocation = nTeleportLocation + step;
	if(nTeleportLocation >=	nLocationsNum) nTeleportLocation = 1;
	if(nTeleportLocation <=	0) nTeleportLocation = nLocationsNum - 1;

	sTeleportLocName = Locations[nTeleportLocation].id;
	Trace("Teleport to '" + sTeleportLocName + "'");

    ReleaseSound(0);
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();
	SetEventHandler("frame","NewGame",1);
}

void ProcessMainMenuKey()
{
	if (interfacestates.buttons.resume.enable == "1")
	{
		//LaunchMainMenu();
		LaunchGameMenuScreen();
	}
}
// вызов меню по Ф2
void ProcessInterfaceKey()
{
	if( CharacterIsDead(GetMainCharacter()) ) {return;}
	if(bSeaActive && !bAbordageStarted)
	{
		if( CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0 )
			{return;}
	}
	else
	{
		if( SendMessage(GetMainCharacter(),"ls",MSG_CHARACTER_EX_MSG,"IsFightMode") != 0 )
			{return;}
		if( CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0 )
			{return;}
	}
	if (bDisableCharacterMenu) // boal
	{
		Log_SetStringToLog(XI_ConvertString("You can`t launch menu"));
		return;
	}
	if (bAbordageStarted && !bCabinStarted && !bDeckBoatStarted)
	{
		Log_SetStringToLog(XI_ConvertString("You can`t launch menu"));
		return;
	}
	LaunchSelectMenu();
}

void GameOverE()
{
	// вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		PauseParticles(true); //fix вылета у форта
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	GameOver("sea");
	DeleteSeaEnvironment();
}

void GameOver(string sName)
{
	ref mc;
	int nSelect;
	string sFileName;
	//ResetSoundScheme();
	PauseAllSounds();
	ResetSound();
	EngineLayersOffOn(false);

	mc = GetMainCharacter();

	ClearEvents();
	ClearPostEvents();
	DeleteEntities();

	if(sti(InterfaceStates.Launched)) {
		UnloadSegment(Interfaces[CurrentInterface].SectionName);
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	InterfaceStates.showGameMenuOnExit = false;
	InterfaceStates.Buttons.Resume.enable = false;
	InterfaceStates.Buttons.Save.enable = false;

	InitSound();
	SetEventHandler(EVENT_END_VIDEO,"LaunchMainMenu_afterVideo",0);
	SetEventHandler("Control Activation","proc_break_video",0);
	FadeOutMusic(3);
	// PlayStereoOGG("music_ship_dead");
	switch(sName)
	{
		case "sea":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_sea_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_ship_dead");
		break;
		case "boarding":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_sea_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_ship_dead");
		break;
		case "land":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_death");
		break;
		case "mutiny":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_death");
		break;
		case "town":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_death");
		break;
		case "blood":
			StartPictureAsVideo( "loading\jonny_load\death\end_game_"+rand(1)+".tga", 4 );
			PlayStereoOGG("music_death");
		break;
	}
}

string its(int iNumber)
{
	string sText = iNumber;
	return sText;
}

// тяжкая игра - сайв токо в церкви 17.03.05 boal
bool QuickSaveGameEnabledHardcore()
{
    bool TmpBool = false;
    ref mchref = GetMainCharacter();

	if (bHardcoreGame)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if( idxLoadLoc!=-1 )
	    {
	        if (CheckAttribute(&Locations[idxLoadLoc], "type"))
	        {
	            if (Locations[idxLoadLoc].type == "church" || Locations[idxLoadLoc].id == "GloriaChurch")
	            {
	                TmpBool = true;
	            }
	        }
	    }
    }
    else
    {
        TmpBool = true;
    }

    return TmpBool;
}

bool CheckBattleSeaSaveEnabled()
{
	string sSaveEnable = GetConvertStr("SeaBattleMode_SaveEnable", KVL_MODS_FILE);
	string sSmallRegStr = GetStrSmallRegister(sSaveEnable);
	if(sSmallRegStr == "on" || sSmallRegStr == "да")
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CheckSaveGameEnabled()
{
    bool TmpBool = true;
    ref mchref = GetMainCharacter();

    if (CheckAttribute(&InterfaceStates, "Buttons.Save.enable"))
	{
		if(InterfaceStates.Buttons.Save.enable != 1)
		{
			TmpBool = false;
		}
	}
	else
	{
		TmpBool = false;
	}

	if (bAbordageStarted) {TmpBool = false;}

	if(LAi_IsBoardingProcess()) {TmpBool = false;}

	if( CharacterIsDead(mchref) ) {TmpBool = false;}

	// LEO: Слишком жётско даже для хардкора. Если будет ваще пздц, выпилим нахер.
	/* if(LAi_IsFightMode(mchref) && MOD_SKILL_ENEMY_RATE > 1) {TmpBool = false;}

	if(bDisableMapEnter && !CheckBattleSeaSaveEnabled()) {TmpBool = false;}  */

	if(LAi_IsFightMode(mchref) && MOD_SKILL_ENEMY_RATE > 1) TmpBool = false;

	if(bDisableMapEnter && !CheckBattleSeaSaveEnabled()) TmpBool = false;

	// if (bAltBalance && LAi_group_IsActivePlayerAlarm()) TmpBool = false;
	if (TmpBool)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if (idxLoadLoc != -1 )
	    {
	        if (Locations[idxLoadLoc].id == "Ship_deck" || Locations[idxLoadLoc].id == "Deck_Near_Ship" ) // сайв на палубе глюкавый
	        {
	            TmpBool = false;
	        }
			if (CheckAttribute(Locations[idxLoadLoc],"fastreload"))
			{
				if (Pchar.questTemp.CapBloodLine == false)
				{
					string sNation = Colonies[FindColony(Locations[idxLoadLoc].fastreload)].nation;//фикс ошибок в логах?
					if (sNation != "none" && sNation != "4")
					{
						int i = sti(sNation);
						bool bTmpBool = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
						if (HasSubStr(Locations[idxLoadLoc].id, "_Town") && bTmpBool) TmpBool = false;
					}
				}
			}
	    }

	}
    return TmpBool;
}

//Boyer change #20170418-01
void restoreQuestItems()
{
    ref		rItemRef;
    if(CheckAttribute(pchar, "restoreLSCKeymasterKey")){
        //From reaction_functions.c
        rItemRef =  ItemsFromID(pchar.restoreLSCKeymasterKey);
        rItemRef.shown = true;
        //From initItems.c
        rItemRef.startLocation = "Villemstad_houseSp5";
        rItemRef.startLocator = "item2";
    }
    if(CheckAttribute(pchar, "restoreLSCTrustLetter")){
        //From RelationAgent_dialog.c
        ChangeItemName(pchar.restoreLSCTrustLetter, "itmname_letter_LSC_1");
        ChangeItemDescribe(pchar.restoreLSCTrustLetter, "itmdescr_letter_LSC_1");
    }
	if(CheckAttribute(pchar, "HugtorpQuestStart") && !CheckAttribute(pchar, "HugtorpQuestFinish"))
	{
		ref itm = ItemsFromID("DOjeronRing");
		itm.picIndex = 15;
		itm.picTexture = "ITEMS_13";
		ChangeItemName("DOjeronRing", "itmname_HugtorpRing");
		ChangeItemDescribe("DOjeronRing", "itmdescr_HugtorpRing");
    }
}

//Boyer change #20170418-01
void removeQuestItemAttribute(string itemID)
{
    switch(itemID)
    {
        case "keyQuestLSC":
            if(CheckAttribute(pchar, "restoreLSCKeymasterKey"))
                DeleteAttribute(pchar, "restoreLSCKeymasterKey");
        break;
        case "letter_LSC":
            if(CheckAttribute(pchar, "restoreLSCTrustLetter"))
                DeleteAttribute(pchar, "restoreLSCTrustLetter");
        break;
    }
}

extern void SetCurrentProfile( string profileName );
//#20171009-03
void ResetDevice()
{
	if(InterfaceStates.Launched == true) {
        if(CurrentInterface == INTERFACE_SAVELOAD) {
            SetCurrentProfile( PlayerProfile.name );
        }
	}
	else {
        //Call twice to remove/replace
        ChangeShowIntarface();
        ChangeShowIntarface();
	}
}
int iCalculateSaveLoadCount(string _SaveLoad)
{
	int iCount;
	ref MChref = GetMainCharacter();
	string sAttrName = _SaveLoad + "Count";
	iCount = sti(MChref.SystemInfo.(sAttrName));
	iCount++;
	MChref.SystemInfo.(sAttrName) = iCount;
	return iCount;
}

void SpecOfficersCirass()
{
    if(CheckAttribute(pchar, "fix20210121")) return;

    pchar.fix20210121 = true;

    if(GetCharacterIndex("Daniel") != -1)
	{
    	sld = characterFromID("Daniel");
		// Прописка всех моделей для кирас. -->
    	sld.HeroModel = "PGG_YokoDias_0,PGG_YokoDias_1,PGG_YokoDias_2,PGG_YokoDias_3,PGG_YokoDias_4,PGG_YokoDias_5,PGG_YokoDias_6,PGG_YokoDias_7,PGG_YokoDias_8";
    	// Прописка всех моделей для кирас. <--
	}

	if(GetCharacterIndex("OffMushketer") != -1)
	{
    	sld = characterFromID("OffMushketer");
		// Прописка всех моделей для кирас. -->
        sld.HeroModel = "MusketeerEnglish_2,MusketeerEnglish_2_1,MusketeerEnglish_2_2,MusketeerEnglish_2_3,MusketeerEnglish_2_4,MusketeerEnglish_2_5,MusketeerEnglish_2,MusketeerEnglish_2,MusketeerEnglish_2";
	    // Прописка всех моделей для кирас. <--
	}

	if(GetCharacterIndex("OfMush1") != -1)
	{
    	sld = characterFromID("OfMush1");
        // Прописка всех моделей для кирас. -->
	    sld.HeroModel = "quest_mush_2,quest_mush_2_1,quest_mush_2_2,quest_mush_2_3,quest_mush_2_4,quest_mush_2_5,quest_mush_2,quest_mush_2,quest_mush_2";
	    // Прописка всех моделей для кирас. <--
	}

	if(GetCharacterIndex("OfMush2") != -1)
	{
    	sld = characterFromID("OfMush2");
	    // Прописка всех моделей для кирас. -->
	    sld.HeroModel = "quest_mush_1,quest_mush_1_1,quest_mush_1_2,quest_mush_1_3,quest_mush_1_4,quest_mush_1_5,quest_mush_1,quest_mush_1,quest_mush_1";
	    // Прописка всех моделей для кирас. <--
    }
	SetNewModelToChar(sld);
}
