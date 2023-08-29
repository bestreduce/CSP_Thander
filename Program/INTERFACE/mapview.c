// Ugeen && Warship --> интерфейс картографического атласа

ref xi_refCharacter;
string CurRow;
int iSelected = 1; // курсор в таблице
int iStartX = 20;
int iStartY = 62;
int iLengthX = 580;//606;
int iLengthY = 520;//542
object oMapTeleport;

void InitInterface(string iniName)
{
	GameInterface.title = "titleMapView";

	xi_refCharacter = pchar;

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("SelectRColony","SelectRColony",0);
	SetEventHandler("OpenMapBest", "OpenMapBest",0);

	FillMapsTable();
	InitMapTeleport();
}

void ProcessBreakExit()
{
	IDoExit(-1);
}

void ProcessCancelExit()
{
	IDoExit(-1);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("SelectRColony","SelectRColony");
	DelEventHandler("OpenMapBest", "OpenMapBest");

	// По всему файлу мне лень править, а здесь оно тоже будет работать прекрасно
	if(CheckAttribute(PChar, "ShowMapsAtlas")) // Смотрим из меню
	{
		DeleteAttribute(PChar, "ShowMapsAtlas");
		interfaceResultCommand = RC_INTERFACE_TO_ITEMS;
	}
	else
	{
		interfaceResultCommand = exitCode;
	}

	EndCancelInterface(true);
}

void OpenMapBest()
{
	IDoExit(RC_INTERFACE_BEST_MAP);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
		case "TABLE_MAPS":
			if(comName == "click")
			{
				nodName = "TABLE_MAPS";
			}
		break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void FillMapsTable()
{
	int n, i;
	string row;
	string sGood, selectedId = "";
	int  idLngFile;
	bool ok = true;
	aref rootItems, arItem;
	aref  curItem;

	n = 1;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	if(CheckAttribute(pchar, "showlastmap")) { selectedId = pchar.showlastmap; }

	GameInterface.TABLE_MAPS.hr.td1.str = "";
	GameInterface.TABLE_MAPS.hr.td1.sorttype = "string";
	SetFormatedText("STR_1", XI_ConvertString("Select map"));
	Table_UpdateWindow("TABLE_MAPS");

	// Заполним картами
	makearef(rootItems, xi_refCharacter.Items);
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		if (Items_FindItem(GetAttributeName(curItem), &arItem)>=0 )
		{
			row = "tr" + n;
			sGood = arItem.id;
			if(CheckAttribute(arItem,"mapSpecial"))
			{
				ok = false;
			}
			else
			{
				ok = true;
			}
			if (arItem.ItemType != "MAP" || !ok) continue;

			if (selectedId == sGood) { iSelected = n; }
			if (GetCharacterItem(xi_refCharacter, sGood) > 0)
			{
				GameInterface.TABLE_MAPS.(row).index = GetItemIndex(arItem.id);
				GameInterface.TABLE_MAPS.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_MAPS.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_MAPS.(row).td1.icon.offset = "-2, -1";
				GameInterface.TABLE_MAPS.(row).td1.icon.width = 20;
				GameInterface.TABLE_MAPS.(row).td1.icon.height = 20;
				GameInterface.TABLE_MAPS.(row).td1.textoffset = "20,0";
				GameInterface.TABLE_MAPS.(row).td1.str = LanguageConvertString(idLngFile, arItem.name);
				GameInterface.TABLE_MAPS.(row).td1.scale = 0.9;
				n++;
			}
		}
    }
	GameInterface.TABLE_MAPS.select = iSelected;
	CurRow   =  "tr" + (iSelected);
	SetNewMapPicture();
	SortTable("TABLE_MAPS", 1);
	Table_UpdateWindow("TABLE_MAPS");
	LanguageCloseFile(idLngFile);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurRow   =  "tr" + (iSelected);
    SetNewMapPicture();
}

void SetNewMapPicture()
{
	int  iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
	ref itmRef = &Items[iGoodIndex];

	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;
		if (itmGroup == MAPS_ITEM_TYPE)
		{
			if (itmRef.id != "Map_Best")
			{
				SetNewPicture("MAP", "interfaces\Maps\" + itmRef.imageTga + ".tga");
				SetNodeUsing("OPEN_MAP_BEST", false);
			}
			else
			{
				SetNewPicture("MAP", "");
				SetNodeUsing("OPEN_MAP_BEST", true);
			}
			pchar.showlastmap = itmRef.id;
		}
	}
}

void ShowInfoWindow()
{
	int  iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
	ref  itmRef = &Items[iGoodIndex];
	int  idLngFile;

	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup = itmRef.picTexture;
	string sGroupPicture = "itm" + itmRef.picIndex

	sPicture = "-1";

	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	sHeader = LanguageConvertString(idLngFile, itmRef.name);
	sText1  = GetItemDescribe(itmRef.id);
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	LanguageCloseFile(idLngFile);
}

void HideInfoWindow()
{
	CloseTooltip();
}

void SelectRColony()
{
	float X, Y;

	float fMouseX = stf(GameInterface.mousepos.x);
	float fMouseY = stf(GameInterface.mousepos.y);

	int  iGoodIndex = sti(GameInterface.TABLE_MAPS.(CurRow).index);
	ref  itmRef = &Items[iGoodIndex];
	
	if (!chrDisableReloadToLocation && !LAi_group_IsActivePlayerAlarm()) DoTeleport(fMouseX,fMouseY,itmRef.id);
}

void DoTeleport(float x, float y, string mapid)
{
	//log_info(FloatToString(x,1)+" "+FloatToString(y,1)+" "+mapid+" "+loadedLocation.islandId);
	
	aref mapname,shorename,shorenum;
	string shore_name,shore_numname;
	int i,j;
	int gridsize = 30;
	//if (mapid == "map_maine_1" || mapid == "map_maine_2") gridsize = 15;

	makearef(mapname,oMapTeleport.(mapid));
	if (CheckAttribute(loadedLocation,"islandId") && mapname.island == loadedLocation.islandId)
	{
		for(i=0; i<GetAttributesNum(mapname); i++)
		{
			shorename = GetAttributeN(mapname,i);
			shore_name = GetAttributeName(shorename);
			for (j=0; j< GetAttributesNum(shorename); j++)
			{
				shorenum = GetAttributeN(shorename,j);
				shore_numname = GetAttributeName(shorenum);
				if (CC(x,y,sti(shorename.(shore_numname).X),sti(shorename.(shore_numname).Y),gridsize) && loadedLocation.id != shore_name)
				{
					pchar.quest.waithours = 1+rand(1);
					if (!HasSubStr(shore_name,"Entr") && !HasSubStr(shore_name,"ExitTown"))
					{
						setCharacterShipLocation(pchar, shore_name);
						setWDMPointXZ(shore_name);
						pchar.quest.waithours = sti(pchar.quest.waithours) + 1+ rand(1);
						if (mapname.island == "Mein") pchar.quest.waithours = sti(pchar.quest.waithours) + 1 + rand(2);
					}
					DoQuestFunctionDelay("WaitNextHours", 0.0);
					log_info("Прошло часов в пути: "+pchar.quest.waithours);
					DoQuestReloadToLocation(shore_name, "reload", "reload1", "");
					return;
				}
			}
		}
	}
}

bool CC(float x, float y, int dx, int dy, int gridsize)
{
	if (x >= dx && x <= dx+gridsize && y >= dy && y <= dy+gridsize) return true;
	return false;
}

bool CWMC(float x, float z, float x2, float z2)
{
	//log_info(worldMap.playerShipX+" "+worldMap.playerShipZ);
	if (stf(worldMap.playerShipX) >= x-100 && stf(worldMap.playerShipX) <= z+100 && stf(worldMap.playerShipZ) >= x2-100 && stf(worldMap.playerShipZ) <= z2+100) return true;
	return false;
}

void InitMapTeleport()
{
	oMapTeleport.map_bermudas.island = "Bermudes";
	oMapTeleport.map_bermudas.Shore3.Pos0.X = 380;
	oMapTeleport.map_bermudas.Shore3.Pos0.Y = 185;
	oMapTeleport.map_bermudas.Shore_Ship1.Pos0.X = 485;
	oMapTeleport.map_bermudas.Shore_Ship1.Pos0.Y = 305;
	oMapTeleport.map_bermudas.Bermudes_CaveEntrance.Pos0.X = 415;
	oMapTeleport.map_bermudas.Bermudes_CaveEntrance.Pos0.Y = 225;
	oMapTeleport.map_bermudas.Bermudes_CaveEntrance.Pos1.X = 465;
	oMapTeleport.map_bermudas.Bermudes_CaveEntrance.Pos1.Y = 275;
	oMapTeleport.map_bermudas.Pirates_town.Pos0.X = 380;
	oMapTeleport.map_bermudas.Pirates_town.Pos0.Y = 285;
	
	oMapTeleport.map_tortuga.island = "Tortuga";
	oMapTeleport.map_tortuga.Mayak6.Pos0.X = 520;
	oMapTeleport.map_tortuga.Mayak6.Pos0.Y = 390;
	oMapTeleport.map_tortuga.Shore58.Pos0.X = 530;
	oMapTeleport.map_tortuga.Shore58.Pos0.Y = 290;
	oMapTeleport.map_tortuga.Tortuga_CaveEntrance.Pos0.X = 425;
	oMapTeleport.map_tortuga.Tortuga_CaveEntrance.Pos0.Y = 230;
	oMapTeleport.map_tortuga.Tortuga_ExitTown.Pos0.X = 480;
	oMapTeleport.map_tortuga.Tortuga_ExitTown.Pos0.Y = 405;
	
	oMapTeleport.map_terks.island = "Terks";
	oMapTeleport.map_terks.Shore56.Pos0.X = 360;
	oMapTeleport.map_terks.Shore56.Pos0.Y = 300;
	oMapTeleport.map_terks.Shore57.Pos0.X = 315;
	oMapTeleport.map_terks.Shore57.Pos0.Y = 415;
	oMapTeleport.map_terks.Terks_CaveEntrance.Pos0.X = 305;
	oMapTeleport.map_terks.Terks_CaveEntrance.Pos0.Y = 328;
	
	oMapTeleport.map_sm.island = "SentMartin";
	oMapTeleport.map_sm.Marigo_ExitTown.Pos0.X = 300;
	oMapTeleport.map_sm.Marigo_ExitTown.Pos0.Y = 365;
	oMapTeleport.map_sm.Shore40.Pos0.X = 395;
	oMapTeleport.map_sm.Shore40.Pos0.Y = 135;
	oMapTeleport.map_sm.Shore41.Pos0.X = 285;
	oMapTeleport.map_sm.Shore41.Pos0.Y = 270;
	oMapTeleport.map_sm.Marigo_CaveEntrance.Pos0.X = 420;
	oMapTeleport.map_sm.Marigo_CaveEntrance.Pos0.Y = 375;
	
	oMapTeleport.map_puerto.island = "PuertoRico";
	oMapTeleport.map_puerto.SanJuan_ExitTown.Pos0.X = 475;
	oMapTeleport.map_puerto.SanJuan_ExitTown.Pos0.Y = 275;
	oMapTeleport.map_puerto.Shore45.Pos0.X = 595;
	oMapTeleport.map_puerto.Shore45.Pos0.Y = 375;
	oMapTeleport.map_puerto.Shore44.Pos0.X = 215;
	oMapTeleport.map_puerto.Shore44.Pos0.Y = 220;
	oMapTeleport.map_puerto.SanJuan_CaveEntrance.Pos0.X = 370;
	oMapTeleport.map_puerto.SanJuan_CaveEntrance.Pos0.Y = 350;
	
	oMapTeleport.map_hisp.island = "Hispaniola";
	oMapTeleport.map_hisp.SantoDomingo_ExitTown.Pos0.X = 575;
	oMapTeleport.map_hisp.SantoDomingo_ExitTown.Pos0.Y = 395;
	oMapTeleport.map_hisp.Mayak8.Pos0.X = 510;
	oMapTeleport.map_hisp.Mayak8.Pos0.Y = 410;
	oMapTeleport.map_hisp.Shore33.Pos0.X = 630;
	oMapTeleport.map_hisp.Shore33.Pos0.Y = 345;
	oMapTeleport.map_hisp.Shore32.Pos0.X = 430;
	oMapTeleport.map_hisp.Shore32.Pos0.Y = 200;
	oMapTeleport.map_hisp.LaVega_ExitTown.Pos0.X = 540;
	oMapTeleport.map_hisp.LaVega_ExitTown.Pos0.Y = 255;
	oMapTeleport.map_hisp.LaVega_town.Pos0.X = 515;
	oMapTeleport.map_hisp.LaVega_town.Pos0.Y = 230;
	oMapTeleport.map_hisp.PortPax_ExitTown.Pos0.X = 330;
	oMapTeleport.map_hisp.PortPax_ExitTown.Pos0.Y = 325;
	oMapTeleport.map_hisp.Shore34.Pos0.X = 320;
	oMapTeleport.map_hisp.Shore34.Pos0.Y = 235;
	oMapTeleport.map_hisp.Mayak7.Pos0.X = 285;
	oMapTeleport.map_hisp.Mayak7.Pos0.Y = 290;
	oMapTeleport.map_hisp.Hispaniola_CaveEntrance.Pos0.X = 450;
	oMapTeleport.map_hisp.Hispaniola_CaveEntrance.Pos0.Y = 350;
	
	oMapTeleport.map_nevis.island = "Nevis";
	oMapTeleport.map_nevis.Charles_ExitTown.Pos0.X = 295;
	oMapTeleport.map_nevis.Charles_ExitTown.Pos0.Y = 365;
	oMapTeleport.map_nevis.Mayak5.Pos0.X = 300;
	oMapTeleport.map_nevis.Mayak5.Pos0.Y = 425;
	oMapTeleport.map_nevis.Shore42.Pos0.X = 410;
	oMapTeleport.map_nevis.Shore42.Pos0.Y = 105;
	oMapTeleport.map_nevis.Shore43.Pos0.X = 435;
	oMapTeleport.map_nevis.Shore43.Pos0.Y = 495;
	oMapTeleport.map_nevis.Charles_CaveEntrance.Pos0.X = 450;
	oMapTeleport.map_nevis.Charles_CaveEntrance.Pos0.Y = 320;
	
	oMapTeleport.map_antigua.island = "Antigua";
	oMapTeleport.map_antigua.SentJons_ExitTown.Pos0.X = 285;
	oMapTeleport.map_antigua.SentJons_ExitTown.Pos0.Y = 265;
	oMapTeleport.map_antigua.Antigua_CaveEntrance.Pos0.X = 505;
	oMapTeleport.map_antigua.Antigua_CaveEntrance.Pos0.Y = 295;
	oMapTeleport.map_antigua.Shore1.Pos0.X = 310;
	oMapTeleport.map_antigua.Shore1.Pos0.Y = 140;
	oMapTeleport.map_antigua.Shore2.Pos0.X = 455;
	oMapTeleport.map_antigua.Shore2.Pos0.Y = 430;
	
	oMapTeleport.map_guad.island = "Guadeloupe";
	oMapTeleport.map_guad.BasTer_ExitTown.Pos0.X = 285;
	oMapTeleport.map_guad.BasTer_ExitTown.Pos0.Y = 440;
	oMapTeleport.map_guad.Guadeloupe_CaveEntrance.Pos0.X = 270;
	oMapTeleport.map_guad.Guadeloupe_CaveEntrance.Pos0.Y = 310;
	oMapTeleport.map_guad.Shore28.Pos0.X = 425;
	oMapTeleport.map_guad.Shore28.Pos0.Y = 155;
	oMapTeleport.map_guad.Shore29.Pos0.X = 350;
	oMapTeleport.map_guad.Shore29.Pos0.Y = 460;
	oMapTeleport.map_guad.Shore30.Pos0.X = 450;
	oMapTeleport.map_guad.Shore30.Pos0.Y = 465;
	oMapTeleport.map_guad.Shore31.Pos0.X = 535;
	oMapTeleport.map_guad.Shore31.Pos0.Y = 460;
	oMapTeleport.map_guad.Mayak4.Pos0.X = 245;
	oMapTeleport.map_guad.Mayak4.Pos0.Y = 385;
	
	oMapTeleport.map_dominica.island = "Dominica";
	oMapTeleport.map_dominica.Shore26.Pos0.X = 500;
	oMapTeleport.map_dominica.Shore26.Pos0.Y = 250;
	oMapTeleport.map_dominica.Shore27.Pos0.X = 390;
	oMapTeleport.map_dominica.Shore27.Pos0.Y = 480;
	oMapTeleport.map_dominica.Dominica_CaveEntrance.Pos0.X = 375;
	oMapTeleport.map_dominica.Dominica_CaveEntrance.Pos0.Y = 270;
	
	oMapTeleport.map_martiniqua.island = "Martinique";
	oMapTeleport.map_martiniqua.Shore38.Pos0.X = 235;
	oMapTeleport.map_martiniqua.Shore38.Pos0.Y = 175;
	oMapTeleport.map_martiniqua.Shore39.Pos0.X = 520;
	oMapTeleport.map_martiniqua.Shore39.Pos0.Y = 475;
	oMapTeleport.map_martiniqua.FortFrance_ExitTown.Pos0.X = 375;
	oMapTeleport.map_martiniqua.FortFrance_ExitTown.Pos0.Y = 325;
	oMapTeleport.map_martiniqua.LeFransua_ExitTown.Pos0.X = 485;
	oMapTeleport.map_martiniqua.LeFransua_ExitTown.Pos0.Y = 320;
	oMapTeleport.map_martiniqua.LeFransua_town.Pos0.X = 490;
	oMapTeleport.map_martiniqua.LeFransua_town.Pos0.Y = 260;
	
	oMapTeleport.map_barbados.island = "Barbados";
	oMapTeleport.map_barbados.Mayak2.Pos0.X = 290;
	oMapTeleport.map_barbados.Mayak2.Pos0.Y = 390;
	oMapTeleport.map_barbados.Bridgetown_ExitTown.Pos0.X = 275;
	oMapTeleport.map_barbados.Bridgetown_ExitTown.Pos0.Y = 435;
	oMapTeleport.map_barbados.Barbados_CaveEntrance.Pos0.X = 410;
	oMapTeleport.map_barbados.Barbados_CaveEntrance.Pos0.Y = 335;
	oMapTeleport.map_barbados.Shore4.Pos0.X = 280;
	oMapTeleport.map_barbados.Shore4.Pos0.Y = 120;
	oMapTeleport.map_barbados.Shore5.Pos0.X = 525;
	oMapTeleport.map_barbados.Shore5.Pos0.Y = 440;
	
	oMapTeleport.map_Curacao.island = "Curacao";
	oMapTeleport.map_Curacao.Villemstad_ExitTown.Pos0.X = 470;
	oMapTeleport.map_Curacao.Villemstad_ExitTown.Pos0.Y = 430;
	oMapTeleport.map_Curacao.Shore22.Pos0.X = 355;
	oMapTeleport.map_Curacao.Shore22.Pos0.Y = 315;
	oMapTeleport.map_Curacao.Shore23.Pos0.X = 345;
	oMapTeleport.map_Curacao.Shore23.Pos0.Y = 380;
	oMapTeleport.map_Curacao.Shore24.Pos0.X = 645;
	oMapTeleport.map_Curacao.Shore24.Pos0.Y = 470;
	oMapTeleport.map_Curacao.Curacao_CaveEntrance.Pos0.X = 475;
	oMapTeleport.map_Curacao.Curacao_CaveEntrance.Pos0.Y = 350;
	
	oMapTeleport.map_trinidad.island = "Trinidad";
	oMapTeleport.map_trinidad.PortSpein_ExitTown.Pos0.X = 250;
	oMapTeleport.map_trinidad.PortSpein_ExitTown.Pos0.Y = 420;
	oMapTeleport.map_trinidad.Trinidad_CaveEntrance.Pos0.X = 225;
	oMapTeleport.map_trinidad.Trinidad_CaveEntrance.Pos0.Y = 355;
	oMapTeleport.map_trinidad.Mayak1.Pos0.X = 205;
	oMapTeleport.map_trinidad.Mayak1.Pos0.Y = 480;
	oMapTeleport.map_trinidad.Mayak1.Pos1.X = 310;
	oMapTeleport.map_trinidad.Mayak1.Pos1.Y = 280;
	oMapTeleport.map_trinidad.Shore59.Pos0.X = 490;
	oMapTeleport.map_trinidad.Shore59.Pos0.Y = 160;
	oMapTeleport.map_trinidad.Shore60.Pos0.X = 420;
	oMapTeleport.map_trinidad.Shore60.Pos0.Y = 300;
	
	oMapTeleport.map_jam.island = "Jamaica";
	oMapTeleport.map_jam.PortRoyal_ExitTown.Pos0.X = 515;
	oMapTeleport.map_jam.PortRoyal_ExitTown.Pos0.Y = 335;
	oMapTeleport.map_jam.Mayak3.Pos0.X = 530;
	oMapTeleport.map_jam.Mayak3.Pos0.Y = 365;
	oMapTeleport.map_jam.Jamaica_CaveEntrance.Pos0.X = 445;
	oMapTeleport.map_jam.Jamaica_CaveEntrance.Pos0.Y = 240;
	oMapTeleport.map_jam.Shore36.Pos0.X = 455;
	oMapTeleport.map_jam.Shore36.Pos0.Y = 370;
	oMapTeleport.map_jam.FortOrange_port.Pos0.X = 185;
	oMapTeleport.map_jam.FortOrange_port.Pos0.Y = 275;
	oMapTeleport.map_jam.FortOrange_ExitTown.Pos0.X = 190;
	oMapTeleport.map_jam.FortOrange_ExitTown.Pos0.Y = 230;
	
	oMapTeleport.map_Bahames.island = "Bahames";
	oMapTeleport.map_Bahames.Nassau_ExitTown.Pos0.X = 360;
	oMapTeleport.map_Bahames.Nassau_ExitTown.Pos0.Y = 155;
	oMapTeleport.map_Bahames.Nassau_ExitTown.Pos1.X = 375;
	oMapTeleport.map_Bahames.Nassau_ExitTown.Pos1.Y = 190;
	oMapTeleport.map_Bahames.Bahames_CaveEntrance.Pos1.X = 375;
	oMapTeleport.map_Bahames.Bahames_CaveEntrance.Pos1.Y = 310;
	oMapTeleport.map_Bahames.Shore68.Pos1.X = 235;
	oMapTeleport.map_Bahames.Shore68.Pos1.Y = 290;
	oMapTeleport.map_Bahames.Shore69.Pos1.X = 435;
	oMapTeleport.map_Bahames.Shore69.Pos1.Y = 305;
	
	oMapTeleport.map_cayman.island = "Caiman";
	if (PChar.ColonyBuilding.Stage == "0" || PChar.ColonyBuilding.Stage == "1")
	{
		oMapTeleport.map_cayman.Shore16.Pos0.X = 550;
		oMapTeleport.map_cayman.Shore16.Pos0.Y = 295;
		oMapTeleport.map_cayman.Shore17.Pos0.X = 355;
		oMapTeleport.map_cayman.Shore17.Pos0.Y = 370;
	}
	else
	{
		oMapTeleport.map_cayman.Caiman_town.Pos0.X = 355;
		oMapTeleport.map_cayman.Caiman_town.Pos0.Y = 370;
	}
	oMapTeleport.map_cayman.Caiman_CaveEntrance.Pos0.X = 370;
	oMapTeleport.map_cayman.Caiman_CaveEntrance.Pos0.Y = 275;
	
	oMapTeleport.map_cuba.island = "Cuba";
	oMapTeleport.map_cuba.PuertoPrincipe_port.Pos0.X = 605;
	oMapTeleport.map_cuba.PuertoPrincipe_port.Pos0.Y = 255;
	oMapTeleport.map_cuba.PuertoPrincipe_ExitTown.Pos0.X = 600;
	oMapTeleport.map_cuba.PuertoPrincipe_ExitTown.Pos0.Y = 290;
	oMapTeleport.map_cuba.Santiago_ExitTown.Pos0.X = 550;
	oMapTeleport.map_cuba.Santiago_ExitTown.Pos0.Y = 345;
	oMapTeleport.map_cuba.Mayak9.Pos0.X = 565;
	oMapTeleport.map_cuba.Mayak9.Pos0.Y = 390;
	oMapTeleport.map_cuba.Shore11.Pos0.X = 510;
	oMapTeleport.map_cuba.Shore11.Pos0.Y = 205;
	oMapTeleport.map_cuba.Shore12.Pos0.X = 440;
	oMapTeleport.map_cuba.Shore12.Pos0.Y = 265;
	oMapTeleport.map_cuba.Mayak10.Pos0.X = 195;
	oMapTeleport.map_cuba.Mayak10.Pos0.Y = 200;
	oMapTeleport.map_cuba.Havana_ExitTown.Pos0.X = 220;
	oMapTeleport.map_cuba.Havana_ExitTown.Pos0.Y = 170;
	oMapTeleport.map_cuba.Cuba_CaveEntrance.Pos0.X = 375;
	oMapTeleport.map_cuba.Cuba_CaveEntrance.Pos0.Y = 205;
	oMapTeleport.map_cuba.Shore13.Pos0.X = 265;
	oMapTeleport.map_cuba.Shore13.Pos0.Y = 220;
	oMapTeleport.map_cuba.Shore14.Pos0.X = 200;
	oMapTeleport.map_cuba.Shore14.Pos0.Y = 300;
	oMapTeleport.map_cuba.Shore15.Pos0.X = 150;
	oMapTeleport.map_cuba.Shore15.Pos0.Y = 330;
	
	//log_info(FloatToString(worldMap.playerShipX,1)+" "+FloatToString(worldMap.playerShipZ,1))
	if (CWMC(-1023,-900,150,600))
	{
		oMapTeleport.map_beliz.island = "Mein";
		oMapTeleport.map_beliz.Beliz_ExitTown.Pos0.X = 190;
		oMapTeleport.map_beliz.Beliz_ExitTown.Pos0.Y = 500;
		oMapTeleport.map_beliz.Shore_ship2.Pos0.X = 160;
		oMapTeleport.map_beliz.Shore_ship2.Pos0.Y = 100;
		oMapTeleport.map_beliz.Shore6.Pos0.X = 240;
		oMapTeleport.map_beliz.Shore6.Pos0.Y = 105;
		oMapTeleport.map_beliz.Shore7.Pos0.X = 235;
		oMapTeleport.map_beliz.Shore7.Pos0.Y = 270;
		oMapTeleport.map_beliz.Shore8.Pos0.X = 210;
		oMapTeleport.map_beliz.Shore8.Pos0.Y = 370;
		oMapTeleport.map_beliz.Beliz_CaveEntrance_3.Pos0.X = 160;
		oMapTeleport.map_beliz.Beliz_CaveEntrance_3.Pos0.Y = 380;
		oMapTeleport.map_beliz.Beliz_CaveEntrance_1.Pos0.X = 135;
		oMapTeleport.map_beliz.Beliz_CaveEntrance_1.Pos0.Y = 440;
		oMapTeleport.map_beliz.Beliz_CaveEntrance_2.Pos0.X = 140;
		oMapTeleport.map_beliz.Beliz_CaveEntrance_2.Pos0.Y = 510;
	}
	if (CWMC(574,924,-1000,-900))
	{
		oMapTeleport.map_cumana.island = "Mein";
		oMapTeleport.map_cumana.Cumana_ExitTown.Pos0.X = 340;
		oMapTeleport.map_cumana.Cumana_ExitTown.Pos0.Y = 385;
		oMapTeleport.map_cumana.Cumana_CaveEntrance.Pos0.X = 260;
		oMapTeleport.map_cumana.Cumana_CaveEntrance.Pos0.Y = 515;
		oMapTeleport.map_cumana.Shore18.Pos0.X = 550;
		oMapTeleport.map_cumana.Shore18.Pos0.Y = 470;
		oMapTeleport.map_cumana.Shore19.Pos0.X = 420;
		oMapTeleport.map_cumana.Shore19.Pos0.Y = 415;
		oMapTeleport.map_cumana.Shore20.Pos0.X = 190;
		oMapTeleport.map_cumana.Shore20.Pos0.Y = 425;
	}
	if (CWMC(-486,-279,-1005,-907))
	{
		oMapTeleport.map_panama.island = "Mein";
		oMapTeleport.map_panama.PortoBello_ExitTown.Pos0.X = 455;
		oMapTeleport.map_panama.PortoBello_ExitTown.Pos0.Y = 275;
		oMapTeleport.map_panama.Panama_ExitTown.Pos0.X = 485;
		oMapTeleport.map_panama.Panama_ExitTown.Pos0.Y = 360;
		oMapTeleport.map_panama.Shore47.Pos0.X = 275;
		oMapTeleport.map_panama.Shore47.Pos0.Y = 430;
		oMapTeleport.map_panama.PortoBello_CaveEntrance.Pos0.X = 220;
		oMapTeleport.map_panama.PortoBello_CaveEntrance.Pos0.Y = 490;
		oMapTeleport.map_panama.Shore48.Pos0.X = 675;
		oMapTeleport.map_panama.Shore48.Pos0.Y = 410;
		oMapTeleport.map_panama.Panama_CaveEntrance.Pos0.X = 425;
		oMapTeleport.map_panama.Panama_CaveEntrance.Pos0.Y = 405;
	}
	if (CWMC(-115,440,-994,-828))
	{
		oMapTeleport.map_maracaibo.island = "Mein";
		oMapTeleport.map_maracaibo.Cartahena_ExitTown.Pos0.X = 230;
		oMapTeleport.map_maracaibo.Cartahena_ExitTown.Pos0.Y = 385;
		oMapTeleport.map_maracaibo.Mayak11.Pos0.X = 205;
		oMapTeleport.map_maracaibo.Mayak11.Pos0.Y = 345;
		oMapTeleport.map_maracaibo.Shore25.Pos0.X = 160;
		oMapTeleport.map_maracaibo.Shore25.Pos0.Y = 450;
		oMapTeleport.map_maracaibo.Cartahena_CaveEntrance.Pos0.X = 130;
		oMapTeleport.map_maracaibo.Cartahena_CaveEntrance.Pos0.Y = 535;
		oMapTeleport.map_maracaibo.Maracaibo_ExitTown.Pos0.X = 385;
		oMapTeleport.map_maracaibo.Maracaibo_ExitTown.Pos0.Y = 445;
		oMapTeleport.map_maracaibo.Shore37.Pos0.X = 390;
		oMapTeleport.map_maracaibo.Shore37.Pos0.Y = 310;
		oMapTeleport.map_maracaibo.Maracaibo_CaveEntrance_02.Pos0.X = 325;
		oMapTeleport.map_maracaibo.Maracaibo_CaveEntrance_02.Pos0.Y = 330;
		oMapTeleport.map_maracaibo.Maracaibo_CaveEntrance.Pos0.X = 335;
		oMapTeleport.map_maracaibo.Maracaibo_CaveEntrance.Pos0.Y = 390;
		oMapTeleport.map_maracaibo.Shore_ship3.Pos0.X = 445;
		oMapTeleport.map_maracaibo.Shore_ship3.Pos0.Y = 510;
		oMapTeleport.map_maracaibo.Caracas_ExitTown.Pos0.X = 665;
		oMapTeleport.map_maracaibo.Caracas_ExitTown.Pos0.Y = 470;
		oMapTeleport.map_maracaibo.Shore21.Pos0.X = 635;
		oMapTeleport.map_maracaibo.Shore21.Pos0.Y = 425;
		oMapTeleport.map_maracaibo.Caracas_CaveEntrance.Pos0.X = 555;
		oMapTeleport.map_maracaibo.Caracas_CaveEntrance.Pos0.Y = 400;
	}
	if (CWMC(-792,-26,-907,-331))
	{
		oMapTeleport.map_santa.island = "Mein";
		oMapTeleport.map_santa.SantaCatalina_ExitTown.Pos0.X = 260;
		oMapTeleport.map_santa.SantaCatalina_ExitTown.Pos0.Y = 245;
		oMapTeleport.map_santa.Shore46.Pos0.X = 300;
		oMapTeleport.map_santa.Shore46.Pos0.Y = 445;
		oMapTeleport.map_santa.Shore53.Pos0.X = 250;
		oMapTeleport.map_santa.Shore53.Pos0.Y = 75;
		oMapTeleport.map_santa.Shore54.Pos0.X = 265;
		oMapTeleport.map_santa.Shore54.Pos0.Y = 185;
		oMapTeleport.map_santa.Shore55.Pos0.X = 275;
		oMapTeleport.map_santa.Shore55.Pos0.Y = 365;
		oMapTeleport.map_santa.SantaCatalina_CaveEntrance.Pos0.X = 225;
		oMapTeleport.map_santa.SantaCatalina_CaveEntrance.Pos0.Y = 155;
		oMapTeleport.map_santa.SantaCatalina_PearlCaveEntrance.Pos0.X = 230;
		oMapTeleport.map_santa.SantaCatalina_PearlCaveEntrance.Pos0.Y = 410;
		oMapTeleport.map_santa.Pearl_CaveEntrance.Pos0.X = 220;
		oMapTeleport.map_santa.Pearl_CaveEntrance.Pos0.Y = 340;
		oMapTeleport.map_santa.Pearl_CaveEntrance.Pos1.X = 240;
		oMapTeleport.map_santa.Pearl_CaveEntrance.Pos1.Y = 310;
		oMapTeleport.map_santa.SantaCatalina_GrotEntrance.Pos0.X = 250;
		oMapTeleport.map_santa.SantaCatalina_GrotEntrance.Pos0.Y = 345;
		//oMapTeleport.map_santa.Cartahena_ExitTown.Pos0.X = 595;
		//oMapTeleport.map_santa.Cartahena_ExitTown.Pos0.Y = 420;
		oMapTeleport.map_santa.Shore25.Pos0.X = 560;
		oMapTeleport.map_santa.Shore25.Pos0.Y = 490;
		oMapTeleport.map_santa.PortoBello_ExitTown.Pos0.X = 430;
		oMapTeleport.map_santa.PortoBello_ExitTown.Pos0.Y = 455;
		oMapTeleport.map_santa.Panama_ExitTown.Pos0.X = 445;
		oMapTeleport.map_santa.Panama_ExitTown.Pos0.Y = 505;
		oMapTeleport.map_santa.Shore48.Pos0.X = 490;
		oMapTeleport.map_santa.Shore48.Pos0.Y = 515;
		oMapTeleport.map_santa.Shore47.Pos0.X = 375;
		oMapTeleport.map_santa.Shore47.Pos0.Y = 520;
	}
	if (CWMC(-1017,-627,-940,-33))
	{
		oMapTeleport.map_Pearl.island = "Mein";
		oMapTeleport.map_Pearl.Shore9.Pos0.X = 175;
		oMapTeleport.map_Pearl.Shore9.Pos0.Y = 75;
		oMapTeleport.map_Pearl.Shore10.Pos0.X = 270;
		oMapTeleport.map_Pearl.Shore10.Pos0.Y = 150;
		oMapTeleport.map_Pearl.Shore53.Pos0.X = 305;
		oMapTeleport.map_Pearl.Shore53.Pos0.Y = 285;
		oMapTeleport.map_Pearl.Shore54.Pos0.X = 325;
		oMapTeleport.map_Pearl.Shore54.Pos0.Y = 435;
		oMapTeleport.map_Pearl.Tenotchitlan_CaveEntrance.Pos0.X = 145;
		oMapTeleport.map_Pearl.Tenotchitlan_CaveEntrance.Pos0.Y = 165;
		oMapTeleport.map_Pearl.Temple.Pos0.X = 145;
		oMapTeleport.map_Pearl.Temple.Pos0.Y = 205;
		oMapTeleport.map_Pearl.Pearl_GrotEntrance.Pos0.X = 190;
		oMapTeleport.map_Pearl.Pearl_GrotEntrance.Pos0.Y = 300;
		oMapTeleport.map_Pearl.Pearl_Jungle_03.Pos0.X = 280;
		oMapTeleport.map_Pearl.Pearl_Jungle_03.Pos0.Y = 345;
		oMapTeleport.map_Pearl.SantaCatalina_ExitTown.Pos0.X = 325;
		oMapTeleport.map_Pearl.SantaCatalina_ExitTown.Pos0.Y = 525;
		oMapTeleport.map_Pearl.SantaCatalina_ExitTown.Pos1.X = 600;
		oMapTeleport.map_Pearl.SantaCatalina_ExitTown.Pos1.Y = 225;
		oMapTeleport.map_Pearl.Shore46.Pos0.X = 630;
		oMapTeleport.map_Pearl.Shore46.Pos0.Y = 415;
		oMapTeleport.map_Pearl.Shore55.Pos0.X = 615;
		oMapTeleport.map_Pearl.Shore55.Pos0.Y = 350;
		oMapTeleport.map_Pearl.SantaCatalina_GrotEntrance.Pos0.X = 570;
		oMapTeleport.map_Pearl.SantaCatalina_GrotEntrance.Pos0.Y = 330;
		oMapTeleport.map_Pearl.SantaCatalina_PearlCaveEntrance.Pos0.X = 550;
		oMapTeleport.map_Pearl.SantaCatalina_PearlCaveEntrance.Pos0.Y = 415;
		oMapTeleport.map_Pearl.Pearl_CaveEntrance.Pos0.X = 525;
		oMapTeleport.map_Pearl.Pearl_CaveEntrance.Pos0.Y = 325;
		oMapTeleport.map_Pearl.Pearl_CaveEntrance.Pos1.X = 560;
		oMapTeleport.map_Pearl.Pearl_CaveEntrance.Pos1.Y = 290;
	}
}