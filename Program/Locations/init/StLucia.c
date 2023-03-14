
int LocationInitStLucia(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Остров Санта-Люсия
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Залив Буканьеров
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore65";
	locations[n].id.label = "Shore65";
	locations[n].image = "loading\jonny_load\shores\Shore06.tga";
	locations[n].worldmap = "StLucia";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "StLucia";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore06";
	Locations[n].models.always.Shore06 = "Shore06";
	locations[n].models.always.Shore06.sea_reflection = 1;
	Locations[n].models.always.Shore06seabed = "Shore06_sb";
	Locations[n].models.always.locators = "Shore06_locators"; 
		
	Locations[n].models.always.grassPatch = "Shore06_grass";
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
	locations[n].models.day.charactersPatch = "Shore06_patch";
	//Night
	locations[n].models.night.charactersPatch = "Shore06_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";		
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "StLucia_Jungle_09";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "StLucia";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "StLucia_Jungle_09";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle9.tga";
	//Sound
	locations[n].type = "Jungle";
	locations[n].islandId = "StLucia";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle9";
	Locations[n].models.always.jungle = "jungle9";
	Locations[n].models.always.bones = "jungle9_bones";
	//Locations[n].models.always.jungle = "jungle9_wall";
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
	//Day
	locations[n].models.day.charactersPatch = "jungle9_patch";
	//Night
	//Locations[n].models.always.jungle = "jungle9_bones";
	locations[n].models.night.charactersPatch = "jungle9_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore65";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore65";
	locations[n].locators_radius.reload.reload1_back = 2;
	
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Ruins";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Ruins";
	locations[n].locators_radius.reload.reload1_back = 2;
	
	locations[n].private1.key = "keyMorgan";
	locations[n].private1.key.delItem = true;
	locations[n].private1.items.Map_Best = 1;
	locations[n].private1.items.icollection = 1;
	locations[n].private1.items.jewelry9 = 500;
	locations[n].private1.items.Map_Best = 1;
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "StLucia_Jungle_10";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\jonny_load\jungle\Jungle10.tga";
	//Sound
	locations[n].type = "Jungle";
	locations[n].islandId = "StLucia";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle10";
	Locations[n].models.always.jungle = "jungle10";
	//Locations[n].models.always.jungle = "jungle9_wall";
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
	//Day
	locations[n].models.day.charactersPatch = "jungle10_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle10_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore66";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore66";
	locations[n].locators_radius.reload.reload1_back = 2;
	
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "StLucia_CaveEntrance";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Ruins";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "StLucia_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\jonny_load\jungle\caveEnt1.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "StLucia";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt1";
	Locations[n].models.always.caveEnt1 = "caveEnt1";
	Locations[n].models.always.locators = "caveEnt1_locators";
	Locations[n].models.always.grassPatch = "caveEnt1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";
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
	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "StLucia_Grot";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "StLucia_jungle_10";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Руины
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Ruins";
	locations[n].id.label = "Ruins";
	locations[n].image = "loading\jonny_load\outside\Ruins.tga";
	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "StLucia";
	locations[n].DisableEncounters = true;
	//Models
	//Always
	Locations[n].filespath.models = "locations\Ruins";
    Locations[n].models.always.ruins = "ruins1";
    Locations[n].models.always.l1 = "plan1";
    Locations[n].models.always.l1.level = 9;
    Locations[n].models.always.l1.tech = "DLightModel";
    Locations[n].models.always.l2 = "plan2";
    Locations[n].models.always.l2.level = 8;
    Locations[n].models.always.l2.tech = "DLightModel";
    Locations[n].models.always.l3 = "plan3";
    Locations[n].models.always.l3.level = 7;
    Locations[n].models.always.l3.tech = "DLightModel";
	Locations[n].models.always.locators = "ruins1_locators";
	
	Locations[n].models.always.grassPatch = "ruins1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
    //Day
    Locations[n].models.day.charactersPatch = "ruins1_patch";
    //Night
    Locations[n].models.night.charactersPatch = "ruins1_patch";
    //Environment
    Locations[n].environment.weather = "true";
    Locations[n].environment.sea = "false";	
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "dungeon_02";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "dungeon";
	locations[n].locators_radius.reload.reload2 = 1.3;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "StLucia_jungle_09";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Подземелье ПКМ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "dungeon_02";
	locations[n].id.label = "dungeon";
	locations[n].image = "loading\jonny_load\inside\DungeonVault2.tga";
	//Sound
	locations[n].type = "dungeon";
	locations[n].islandId = "StLucia";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\DungeonOld2";
	locations[n].models.always.locators = "DungeonOld2_locators";
	locations[n].models.always.Dungeon = "DungeonOld2";
	//locations[n].models.always.treasure = "Treasures";
	Locations[n].models.always.treasure.locator.group = "monsters";
	Locations[n].models.always.treasure.locator.name = "monster3";
	//locations[n].models.always.door = "door_old";
	//Locations[n].models.always.door.locator.group = "reload";
	//Locations[n].models.always.door.locator.name = "reload2";
	//Day
	locations[n].models.day.charactersPatch = "DungeonOld2_patch";
	//Night
	locations[n].models.night.charactersPatch = "DungeonOld2_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "ruins";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "ruins";

	/*locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Shore66";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Shore66";
	locations[n].reload.l2.disable = 1;*/
	
	locations[n].locators_radius.item.key = 1.0;
	
	locations[n].private1.items.key1 = 1;
	locations[n].private1.items.potion4 = 3;
	locations[n].private1.items.potion3 = 6;
	locations[n].private1.items.jewelry10 = 1;
	//locations[n].private1.items.blade20 = 1;
	
	locations[n].private2.items.chest = 40;
	
	locations[n].private3.items.pistol1 = 1;
	locations[n].private3.items.bullet = 1;
	locations[n].private3.items.gunpowder = 1;
	
	locations[n].private4.items.topor_05 = 1;
	locations[n].private4.items.CompCraft_Magnesium = 1;
	
	locations[n].private5.items.CompCraft_Magnesium = 5;
	locations[n].private5.items.CompCraft_Lead = 1;
	
	locations[n].private6.items.potion3 = 2;
	
	locations[n].private7.items.jewelry13 = 15;
	
	locations[n].private8.items.CompCraft_PowderMixture = 1;
	locations[n].private8.items.CompCraft_SulfurCrush = 1;
	
	locations[n].DisableEncounters = true;
	locations[n].DisableOfficers = "1";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Мыс Пеликана
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore66";
	locations[n].id.label = "Shore66";
	locations[n].image = "loading\jonny_load\shores\Shore11.tga";
	locations[n].worldmap = "StLucia";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "StLucia";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore11";
	Locations[n].models.always.shore11 = "Shore11";
	locations[n].models.always.shore11.sea_reflection = 1;
	Locations[n].models.always.shore11seabed = "Shore11_sb";
	Locations[n].models.always.locators = "Shore11_locators";
		
	Locations[n].models.always.grassPatch = "Shore11_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	locations[n].models.always.l1.sea_reflection = 1;
	
	Locations[n].models.always.Waterfall1 = "WaterFall1";
	Locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
    Locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall1.level = 50;
	
	Locations[n].models.always.Waterfall2 = "WaterFall2";
	Locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	Locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	Locations[n].models.always.Waterfall2.level = 49;	
	//Day
	locations[n].models.day.charactersPatch = "shore11_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore11_patch";
	// Jump patch
	Locations[n].models.day.jumpPatch = "shore11_jump_patch";
	Locations[n].models.night.jumpPatch = "shore11_jump_patch";
	
	Locations[n].animals = "true";
	Locations[n].heaters_night_only = 1;	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";					
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "StLucia_Jungle_10";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "StLucia";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	
	locations[n].reload.l3.name = "reload4";
	locations[n].reload.l3.go = "SantaQuiteriaInside";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "SantaQuiteriaInside";
	
	locations[n].reload.l4.name = "reload3_back";
	locations[n].reload.l4.go = "StLucia_GrotKNS";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Grot";
	
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Фрегат Санта-Квитерия - внутри корабля
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantaQuiteriaInside";
	locations[n].id.label = "SantaQuiteriaInside";
	locations[n].filespath.models = "locations\Inside\squit";
	locations[n].image = "loading\jonny_load\quest\externalringinside.tga";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "questisland";
	locations[n].islandId = "StLucia";	
	//Models
	//Always	
	Locations[n].models.always.inside = "squit";
	Locations[n].models.always.inside.level = 65538;
	Locations[n].models.always.windows = "squit_win";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 65539;	
	Locations[n].models.always.locators = "squit_loc";
	//Day
	locations[n].models.day.charactersPatch = "squit_patch";
	//Night
	locations[n].models.night.charactersPatch = "squit_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//locations[n].alwaysStorm = true;
	//locations[n].storm = true;
	//locations[n].tornado = true;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Shore66";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shore66";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Shore66";
	locations[n].reload.l2.emerge = "reload5";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Shore66";
	locations[n].locators_radius.item.item1 = 1.2;
	
	locations[n].private1.key = "key1";
	locations[n].private1.key.delItem = true;
	locations[n].private1.items.topor_01 = 1;
	locations[n].private1.items.coins = 663;
	locations[n].private1.items.keyMorgan = 1;
	
	locations[n].private2.items.potion3 = 7;
	locations[n].private2.items.blade5 = 1;
	
	locations[n].private3.items.mineral4 = 10;
	locations[n].private3.items.potionrum = 15;
	
	locations[n].private4.items.indian12 = 1;
	locations[n].private4.items.blade_01 = 1;
	locations[n].private4.items.map_bad = 1;
	
	locations[n].private5.items.shotgun_cartridge = 13;
	locations[n].private5.items.cartridge = 33;
	
	locations[n].private6.items.indian3 = 1;
	locations[n].private6.items.blade_02 = 1;	
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "StLucia_Grot";
	locations[n].id.label = "Grot";
    locations[n].image = "loading\jonny_load\inside\grotto1.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "StLucia";
	locations[n].onUninhabitedIsland = true;
	locations[n].DisableEncounters = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto1";
	locations[n].models.always.grotto1 = "grotto1";
	locations[n].models.always.grotto1alpha = "grotto1_alpha";
	Locations[n].models.always.grotto1alpha.tech = "LocationWindows";	
	locations[n].models.always.grotto1alpha.level = 65532;
	locations[n].models.always.chest = "chest";	
	locations[n].models.always.locators = "grotto1_locators";

	locations[n].locators_radius.item.duhi1 = 0.0;
	
	Locations[n].models.always.rays = "grotto1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech = "LocVisRays";
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
	locations[n].reload.l1.go = "StLucia_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "CaveEntrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот КНС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "StLucia_GrotKNS";
	locations[n].id.label = "Grot";
	locations[n].image = "loading\jonny_load\inside\grotto3.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "StLucia";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\GrotI";
	locations[n].models.always.GrotI = "GrotI";
	locations[n].models.always.locators = "GrotI_locators";

	//Day
	locations[n].models.day.charactersPatch = "GrotI_patch";
	//Night
	locations[n].models.night.charactersPatch = "GrotI_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore66";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shore66";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;

	return n;
}
