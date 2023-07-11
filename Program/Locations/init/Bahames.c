
int LocationInitBahames(int n)
{
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "Bahames";
	
	locations[n].townsack = "Nassau";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	
	locations[n].filespath.models = "locations\Town_Nassau\Town\";
	locations[n].image = "loading\jonny_load\city\Nassau_town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//==> флаг генерации квестодателя по розыску кэпов, int значение - шанс что сам заговорит(1-10)
	locations[n].questSeekCap = 7;
	
	//Sound
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	//Always
	locations[n].models.always.town = "Nassau";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.seabed = "Nassau_sb";
	locations[n].models.always.locators = "Nassau_locators";
	locations[n].models.always.L1 = "Nassau_signsA";
	locations[n].models.always.grassPatch = "Nassau_grass";
	locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;

	//Day
	locations[n].models.day.fonar = "Nassau_fd";
	locations[n].models.day.charactersPatch = "Nassau_patch_day";
	locations[n].models.day.rinok = "Nassau_rinok";
	//Night
	locations[n].models.night.fonar = "Nassau_fn";
	locations[n].models.night.charactersPatch = "Nassau_patch_night";
	locations[n].models.night.locatorsL3 = "Nassau_gate";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Bahames";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.reload2_back = 1.8;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Nassau_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Nassau_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Nassau_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Nassau_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "Nassau_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	//locations[n].reload.l7.close_for_night = 1;

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "Nassau_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "Nassau_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "Nassau_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";

	locations[n].reload.lgate.name = "gate1";
	locations[n].reload.lgate.go = "Nassau_ExitTown";
	locations[n].reload.lgate.emerge = "reload2";
	locations[n].reload.lgate.autoreload = "1";
	locations[n].reload.lgate.label = "ExitTown";
	locations[n].locators_radius.reload.reload11_back = 3;

    // --> Квестовые локации.
	locations[n].reload.l12.name = "houseV1";
	locations[n].reload.l12.go = "Nassau_HouseHut2";
	locations[n].reload.l12.emerge = "reload1";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "DEstre House";
	locations[n].reload.l12.disable = 1; // закроем

	locations[n].reload.l13.name = "houseV2";
	locations[n].reload.l13.go = "Nassau_HouseHut2";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "DEstre House";
	locations[n].reload.l13.disable = 1; // закроем

	locations[n].reload.l14.name = "houseS2";
	locations[n].reload.l14.go = "Nassau_HouseSp2";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "DEstre House";
	locations[n].reload.l14.close_for_night = 1;

	locations[n].reload.l15.name = "houseD1";
	locations[n].reload.l15.go = "Nassau_HouseHut";
	locations[n].reload.l15.emerge = "reload2";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "DEstre House";
	locations[n].reload.l15.close_for_night = 1;

	locations[n].reload.l16.name = "houseD2";
	locations[n].reload.l16.go = "Nassau_HouseHut";
	locations[n].reload.l16.emerge = "reload1";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "DEstre House";
	locations[n].reload.l16.close_for_night = 1;

	locations[n].reload.l17.name = "houseH5";
	locations[n].reload.l17.go = "Nassau_Hut3_Kns";
	locations[n].reload.l17.emerge = "reload1";
	locations[n].reload.l17.autoreload = "0";
	locations[n].reload.l17.label = "DEstre House";
	locations[n].reload.l17.close_for_night = 1;

	locations[n].reload.l18.name = "houseV4";
	locations[n].reload.l18.go = "Nassau_HouseHut1";
	locations[n].reload.l18.emerge = "reload1";
	locations[n].reload.l18.autoreload = "0";
	locations[n].reload.l18.label = "DEstre House";
	locations[n].reload.l18.close_for_night = 1;

	locations[n].reload.l19.name = "houseS1";
	locations[n].reload.l19.go = "Nassau_CobHouse";
	locations[n].reload.l19.emerge = "reload1";
	locations[n].reload.l19.autoreload = "0";
	locations[n].reload.l19.label = "House";
	
    // --> Комоны, загрушки. Номера с начинаются с 20.
	locations[n].reload.l20.name = "houseF4";
	locations[n].reload.l20.go = "CommonRoom_MH3";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";

	locations[n].reload.l21.name = "houseSp2";
	locations[n].reload.l21.go = "CommonStoneHouse";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";

	locations[n].reload.l22.name = "houseH3";
	locations[n].reload.l22.go = "CommonRoom_MH";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";

	locations[n].reload.l23.name = "houseF1";
	locations[n].reload.l23.go = "CommonRoom_MH9";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseF2";
	locations[n].reload.l24.go = "CommonRoom_MH4";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";
     // <--

	locations[n].reload.l25.name = "reloadSk";
	locations[n].reload.l25.go = "Nassau_sklad02";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "sklad";

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern05\";
	locations[n].image = "loading\jonny_load\inside\Tavern05.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.tavern = "tavern05";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.nobsp = "tavern05NB";
	locations[n].models.always.locators = "tavern05_locators";
	locations[n].models.always.window = "tavern05_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "tavern05_patch";
	//Night
	locations[n].models.night.charactersPatch = "tavern05_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Nassau_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
				
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ НАВЕРХУ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_tavern_upstairs";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\jonny_load\inside\Tavern_room.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].models.always.locators = "Tavern_room_locators";
	locations[n].models.always.tavern = "Tavern_room";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "tavern_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Nassau_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\jonny_load\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\SmallResidence";
	locations[n].models.always.locators = "SmallResidence_locators";
	locations[n].models.always.house = "SmallResidence";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "SmallResidence_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SmallResidence_patch";
	//Night
	locations[n].models.night.charactersPatch = "SmallResidence_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.item.item1 = 0.9;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store03\";
	locations[n].image = "loading\jonny_load\inside\store03.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.locators = "Store03_locators";
	locations[n].models.always.store = "Store03";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store03_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store03_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.camdetector.camera1 = 5;
    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "packhouse";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ВЕРФЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard02\";
	locations[n].image = "loading\jonny_load\inside\shipyard02.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.locators = "Shipyard02_locators";
	locations[n].models.always.shipyard = "Shipyard02";
	locations[n].models.always.shipyard.level = 65538;
	locations[n].models.always.window = "shipyard02_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Shipyard02_patch";
	//Night
	locations[n].models.night.charactersPatch = "Shipyard02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "packhouse";
	locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_church";
	locations[n].id.label = "Church";
	locations[n].image = "loading\jonny_load\inside\church_IM.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	//Models
	locations[n].filespath.models = "locations\inside\church_IM\";
	//Always
	locations[n].models.always.church = "church_IM";
	locations[n].models.always.locators = "church_IM_locators";
	locations[n].models.always.window = "church_IM_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "church_IM_patch";
	//Night
	locations[n].models.night.charactersPatch = "church_IM_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Graveyard";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пиратский дом (ростовщик)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_bank";
	locations[n].id.label = "Usurer House";
	locations[n].image = "loading\jonny_load\inside\bank03.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Pirate_House";
	locations[n].models.always.locators = "PirH_l";
	locations[n].models.always.tavern = "PirH";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "PirH_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "PirH_p";
	//Night
	locations[n].models.night.charactersPatch = "PirH_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l2.name = "reload1";
	locations[n].reload.l2.go = "Nassau_town";
	locations[n].reload.l2.emerge = "reload8";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// БОРДЕЛЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].filespath.models = "locations\inside\Brothel\";
	locations[n].image = "loading\jonny_load\inside\brothel.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].models.always.locators = "Brothel_locators";
	locations[n].models.always.store = "Brothel";
	locations[n].models.always.window = "brothel_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Brothel_patch";
	//Night
	locations[n].models.night.charactersPatch = "Brothel_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Nassau_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  //закроем, но связка пусть будет для квестов.

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Nassau_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комнаты в борделе
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].filespath.models = "locations\inside\Brothel_room\";
	locations[n].image = "loading\jonny_load\inside\Brothel_room.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.locators = "Brothel_room_locators";
	locations[n].models.always.store = "Brothel_room";
	locations[n].models.always.window = "Brothel_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Brothel_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Brothel_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Nassau_Brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_SecBrRoom"; // вторая комната борделя
	locations[n].id.label = "Room";
	locations[n].image = "loading\jonny_load\inside\Residence07PKM.tga";
 	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Residence07";
	locations[n].models.always.locators = "Res07_l";
	locations[n].models.always.l1 = "Res07";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "Res07_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Res07_p";
	//Night
	locations[n].models.night.charactersPatch = "Res07_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ПОРТОВЫЙ ОФИС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\jonny_load\inside\PortOfficeNassau.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\PortOfficeNasao\";
	locations[n].models.always.housePortOffice = "PortOfficeNasao";
	locations[n].models.always.housePortOffice.level = 65538;
	locations[n].models.always.locators = "PortOfficeNasao_locators";
	//Day
	locations[n].models.day.charactersPatch = "PortOfficeNasao_patch";
	//Night
	locations[n].models.night.charactersPatch = "PortOfficeNasao_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
        locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом с подвалом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_HouseSp2";
	locations[n].filespath.models = "locations\inside\FlamHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.tavern = "FlamHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "FlamHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "FlamHouse_locators";
	locations[n].models.night.locators = "FlamHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "FlamHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "FlamHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "houseS2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload3";
	locations[n].reload.l2.go = "CommonRoom_MH3";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].reload.l3.name = "reload4";
	locations[n].reload.l3.go = "CommonRoom_MH4";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";

	locations[n].reload.l4.name = "reload2";
	locations[n].reload.l4.go = "Nassau_Cave";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Street";
	locations[n].reload.l4.disable = 1; // закроем
	n = n + 1;

  	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хижина с двумя входами
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_HouseHut";
	locations[n].filespath.models = "locations\inside\Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\hut.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.locators = "Hut_locators";
	locations[n].models.always.tavern = "Hut";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "houseD2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Nassau_town";
	locations[n].reload.l2.emerge = "houseD1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Хижина с камином
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_Hut3_Kns";
	locations[n].filespath.models = "locations\inside\Hut3";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\Hut3_Kns.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.locators = "Hut3_locators";
	locations[n].models.always.tavern = "Hut3";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut3_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut3_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "houseH5";
	locations[n].reload.l1.autoreload = "Hut3";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Изба рыбака
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_HouseHut1";
	locations[n].filespath.models = "locations\inside\Hut1_KNS";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\Hut1_KNS.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.locators = "Hut1_locators";
	locations[n].models.always.tavern = "Hut1";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut1_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut1_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut1_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l2.name = "reload1";
	locations[n].reload.l2.go = "Nassau_town";
	locations[n].reload.l2.emerge = "houseV4";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Большой дом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_CobHouse";
	locations[n].filespath.models = "locations\inside\CobHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\CobHouse.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].models.always.tavern = "CobHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "CobHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "CobHouse_locators";
	locations[n].models.night.locators = "CobHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "CobHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "CobHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "houseS1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Nassau_BedRoomK2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Спальня резиденции (ПКМ)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_BedRoomK2";
	locations[n].id.label = "BedRoom";
	locations[n].filespath.models = "locations\inside\ResBedRoom";
	locations[n].image = "loading\jonny_load\inside\ResBedroomPKM.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Nassau";
 	locations[n].islandId = "Bahames";
 	// стража
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
	//Models
	//Always
	locations[n].models.always.locators = "bed_l";
	locations[n].models.always.l1 = "bed";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "bed_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "bed_p";
	//Night
	locations[n].models.night.charactersPatch = "bed_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_CobHouse";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Townhall";
	n = n + 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Склад 02 не имеет отношение к магазину.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_sklad02";
	locations[n].id.label = "packhouse";
	locations[n].image = "loading\jonny_load\inside\sklad02.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "Nassau";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "sklad";
	locations[n].fastreload = "Nassau";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Sklad02";
	locations[n].models.always.locators = "sklad02_locators";
	locations[n].models.always.modelSklad = "sklad02";
	locations[n].models.always.modelSklad.level = 65538;
	//Day
	locations[n].models.day.charactersPatch = "sklad02_patch";
	//Night
	locations[n].models.night.charactersPatch = "sklad02_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "reloadSk";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Nassau_ExitTown";
	locations[n].fastreload = "Nassau";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle3.tga";
	//Town sack
	locations[n].townsack = "Nassau";
	//Sound
	locations[n].type = "jungle";
 	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle3";
	Locations[n].models.always.jungle = "jungle3";
	Locations[n].models.always.locators = "jungle3_locators";
	Locations[n].models.always.grassPatch = "jungle3_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle3_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "Nassau_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Nassau_town";
	locations[n].locators_radius.reload.reload3_back = 2.0;

	locations[n].reload.l2.name = "reload3_back";
	locations[n].reload.l2.go = "Bahames_jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Bahames_jungle_05";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bahames_jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle5.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";	
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Nassau_ExitTown";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Bahames_jungle_03";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Bahames_jungle_02";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bahames_jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle1.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle1\";
	Locations[n].models.always.jungle = "jungle1";
	Locations[n].models.always.locators = "jungle1_locators";		
	Locations[n].models.always.grassPatch = "jungle1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";	
	//Day
	locations[n].models.day.charactersPatch = "jungle1_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle1_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames_jungle_01";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 3.0;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Bahames_jungle_04";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Tortuga_BaseTere";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Bahames_jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle8.tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle8";
	Locations[n].models.always.jungle = "jungle8";	
	Locations[n].models.always.locators = "jungle8_locators";		
	Locations[n].models.always.grassPatch = "jungle8_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";	
	//Day
	locations[n].models.day.charactersPatch = "jungle8_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle8_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames_jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Tortuga_jungle_05";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Bahames_jungle_04";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bahames_jungle_04";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle6.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle6";
	Locations[n].models.always.jungle = "jungle6";	
	Locations[n].models.always.locators = "jungle6_locators";		
	Locations[n].models.always.grassPatch = "jungle6_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";	
	//Day
	locations[n].models.day.charactersPatch = "jungle6_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle6_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames_jungle_03";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Bahames_jungle_02";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Passage";
    locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Shore68";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Shore";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bahames_jungle_05";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle4.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle4";
	Locations[n].models.always.jungle = "jungle4";
	Locations[n].models.always.locators = "jungle4_locators";
	Locations[n].models.always.grassPatch = "jungle4_grass";
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
	//Day
	locations[n].models.day.charactersPatch = "jungle4_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle4_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Nassau_ExitTown";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Nassau_fort";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Nassau Fort";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Bahames_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Passage";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bahames_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\jonny_load\jungle\CaveEnt2.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt1";
	Locations[n].models.always.caveEnt1 = "caveEnt1";	
	Locations[n].models.always.locators = "caveEnt1_locators";		
	Locations[n].models.always.grassPatch = "caveEnt1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";	
	//Day
	locations[n].models.day.charactersPatch = "caveEnt1_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt1_patch";	
	//Environment	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames_Grot";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Grot";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Bahames_jungle_05";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bahames_Grot";
	locations[n].id.label = "Grot";
	locations[n].image = "loading\jonny_load\inside\grotto1.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto1";
	locations[n].models.always.grotto1 = "grotto1";
	locations[n].models.always.grotto1alpha = "grotto1_alpha";
	Locations[n].models.always.grotto1alpha.tech = "LocationWindows";	
	locations[n].models.always.grotto1alpha.level = 65532;
	locations[n].models.always.chest = "chest";	
	locations[n].models.always.locators = "grotto1_locators";
	locations[n].locators_radius.item.duhi1 = 1.3;
	Locations[n].models.always.rays = "grotto1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	
	//Day
	locations[n].models.day.charactersPatch = "grotto1_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Бухта Приватира
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore68";
	locations[n].id.label = "Shore68";
	locations[n].image = "loading\jonny_load\shores\Rockshore.tga";
	locations[n].worldmap = "Shore68";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Rockshore";
	Locations[n].models.always.rockshore = "rockshore";
	locations[n].models.always.rockshore.sea_reflection = 1;
	Locations[n].models.always.rockshoreseabed = "rockshore_sb";
	Locations[n].models.always.locators = "rockshore_locators";
	Locations[n].models.always.l1 = "rockshore_alpha";
	Locations[n].models.always.grassPatch = "rockshore_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";
	//Day
	locations[n].models.day.charactersPatch = "rockshore_patch";
	Locations[n].models.day.jumpPatch = "rockshore_jump_patch";
	//Night
	locations[n].models.night.charactersPatch = "rockshore_patch";
	Locations[n].models.night.jumpPatch = "rockshore_jump_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames_Jungle_04";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 1.5;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Bahames";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 7.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж Корсара (бухта с останками корабля)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore69";
	locations[n].id.label = "Shore69";
	locations[n].image = "loading\jonny_load\shores\ShoreShip2.tga";
	locations[n].worldmap = "Shore69";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\ShoreShip2";
	Locations[n].models.always.shore = "shoreShip2";
	locations[n].models.always.shore.sea_reflection = 1;
	Locations[n].models.always.shoreShip1seabed = "shoreShip2_sb";
	Locations[n].models.always.locators = "ShoreShip2_locators";
	Locations[n].models.always.grassPatch = "shoreShip2_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	//Day
	locations[n].models.day.charactersPatch = "shoreShip2_patch";
	//Night
	locations[n].models.night.charactersPatch = "shoreShip2_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames_Jungle_06";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 6;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Bahames";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли (сквозной пролёт)
 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bahames_Jungle_06";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle10B.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle10";
	Locations[n].models.always.jungle = "jungle10";
	Locations[n].models.always.locators = "jungle10_locators";
	Locations[n].models.always.grassPatch = "jungle10_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle10_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle10_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore69";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Bahames_deadlock";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 3;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли тупиковые
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Bahames_deadlock";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle9.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Bahames";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle9\";
	Locations[n].models.always.jungle = "jungle9";
	Locations[n].models.always.locators = "jungle9_locators";
	Locations[n].models.always.grassPatch = "jungle9_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";

	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	Locations[n].models.always.l4 = "jungle9_wall";

	//Day
	locations[n].models.day.charactersPatch = "jungle9_patch2";
	//Night
	locations[n].models.night.charactersPatch = "jungle9_patch2";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Bahames_Jungle_06";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.2;
	n = n + 1;

	return n;
}
