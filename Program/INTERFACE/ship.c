/// BOAL меню корабль
int nCurScrollNum;
ref xi_refCharacter;
int shipIndex;

string CurTable, CurRow;
int iSelected; // курсор в таблице

// для выкидывания
int iShipQty, iUnits, iCurGoodsIdx;

string sMessageMode;
void InitInterface_R(string iniName, ref _chr) // _chr нужно для читового просмотра НПС в море
{
    InterfaceStack.SelectMenu_node = "LaunchShipState"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleShip";

	xi_refCharacter = _chr;

	FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("confirmShipChangeName","confirmShipChangeName",0);
	SetEventHandler("CheckForRename","CheckForRename",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("GoodsExitCancel", "GoodsExitCancel", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ShipChange", "ShipChange", 0);
	SetEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("GoToShipChange", "GoToShipChange", 0);
	SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	SetEventHandler("ExitPartitionWindow", "ExitPartitionWindow", 0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
    XI_RegistryExitKey("IExit_F2");
    //////////////////
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",156,78,366,313); // tak from SHIP_BIG_PICTURE
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161,284,361,1, 4);
    EI_CreateFrame("SHIP_BIG_PICTURE_BORDER",20,85,134,199);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,225,147,1, 4);
    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8,204,147,1, 4);

    EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 657,214,789,1, 4);
    SetNewGroupPicture("CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");

    SetNewGroupPicture("EXTRAHULLON", "SHIP_UPGRADES", "EXTRAHULLON");
    SetNewGroupPicture("EXTRASAILON", "SHIP_UPGRADES", "EXTRASAILON");
    SetNewGroupPicture("EXTRAGUNSON", "SHIP_UPGRADES", "EXTRAGUNSON");
    SetNewGroupPicture("EXTRAHULLKRENGON", "SHIP_UPGRADES", "EXTRAHULLKRENGON");
    SetNewGroupPicture("EXTRACAPACITYON", "SHIP_UPGRADES", "EXTRACAPACITYON");
    SetNewGroupPicture("EXTRABIGSIDESON", "SHIP_UPGRADES", "EXTRABIGSIDESON");

    SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));

    GameInterface.TABLE_LIST.hr.td1.str = "Товары в трюме";
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = "Кол-во";
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = "Вес";
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = "Пачка";
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = "Вес пачки";
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;
	GameInterface.TABLE_LIST.select = 0;
//--> mod tablesort
	GameInterface.TABLE_LIST.hr.td1.sorttype = "string";
	GameInterface.TABLE_LIST.hr.td2.sorttype = "";
	GameInterface.TABLE_LIST.hr.td3.sorttype = "";
	GameInterface.TABLE_LIST.hr.td4.sorttype = "";
	GameInterface.TABLE_LIST.hr.td5.sorttype = "";
//<-- mod tablesort
	SetCurrentNode("SHIPS_SCROLL");
	OnShipScrollChange();
	sMessageMode = "";
	SetFormatedText("SHIPS_WEIGHTS", GetShipsWeights());
	SetNodeUsing("Soil_TEXT", true);
	SetNodeUsing("SoilN_TEXT", true);
	SetNodeUsing("SoilS_TEXT", true);
	SetNodeUsing("SoilM_TEXT", true);
}

string GetShipsWeights()
{
	int unno = 0;
	int twaa = 0;
	int tree = 0;
	int cn, iShipType;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(xi_refCharacter, i);
		if(cn != -1)
		{
			iShipType = sti(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				unno += makeint(GetCargoMaxSpace(characters[cn])-GetCargoLoad(characters[cn]));
				twaa += makeint(GetCargoLoad(characters[cn]));
				tree += makeint(GetCargoMaxSpace(characters[cn]));
			}
		}
	}
	return "Дедвейт эскадры: Своб: "+unno+"ц. | Занято: "+twaa+"ц. | Макс: "+tree+"ц.";
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("confirmShipChangeName","confirmShipChangeName");
	DelEventHandler("CheckForRename","CheckForRename");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("GoodsExitCancel", "GoodsExitCancel");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ShipChange", "ShipChange");
	DelEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("GoToShipChange", "GoToShipChange");
	DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");

	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("ExitPartitionWindow", "ExitPartitionWindow");
	DelEventHandler("OnTableClick", "OnTableClick");
	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
	//#20200329-01
	if(bSeaActive) RefreshBattleInterface();
}
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		/////  пушки -->
        case "CANNONS_OK":
			if(comName=="click")
			{
				HideCannonsMenu(); // применить уже сущ изменения
				OnShipScrollChange();
				Ship_ResearchCannons(xi_refCharacter);
			}
		break;

		case "CANNONS_REMOVE_ALL":
			if(comName=="click")
			{
			    CanonsRemoveAll();
			}
		break;

		case "CANNONS_SET_ALL":
			if(comName=="click")
			{
			    CanonsSetAll(xi_refCharacter);
			}
		break;

		case "CANNONS_LEFT_F":
			if(comName=="click")
			{
				ChangeCannonNum("fcannon", -1);
			}
		break;
		case "CANNONS_RIGHT_F":
			if(comName=="click")
			{
    			ChangeCannonNum("fcannon", 1);
			}
		break;

		case "CANNONS_LEFT_B":
			if(comName=="click")
			{
                ChangeCannonNum("bcannon", -1);
			}
		break;
		case "CANNONS_RIGHT_B":
			if(comName=="click")
			{
                ChangeCannonNum("bcannon", 1);
			}
		break;

		case "CANNONS_LEFT_R":
			if(comName=="click")
			{
                ChangeCannonNum("rcannon", -1);
			}
		break;
		case "CANNONS_RIGHT_R":
			if(comName=="click")
			{
                ChangeCannonNum("rcannon", 1);
			}
		break;

		case "CANNONS_LEFT_L":
			if(comName=="click")
			{
                ChangeCannonNum("lcannon", -1);
			}
		break;
		case "CANNONS_RIGHT_L":
			if(comName=="click")
			{
                ChangeCannonNum("lcannon", 1);
			}
		break;
		/////  пушки <--
		case "CREW_MORALE_BUTTON":
			if(comName=="click")
			{
			    ShowMoraleMessage();
			}
		break;

		case "PARTITION_OK":
			if(comName=="click")
			{
			    DoPartitionPay();
			}
		break;

		case "CREW_PARTITION":
			if(comName=="click")
			{
			    ShowPartitionWindow();
			}
		break;

		case "RESORT":
			if(comName=="click")
			{
				SortCompanionsBy("speedrate");
			}
		break;

		case "QTY_OK_BUTTON":
			if(comName=="leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;

		case "QTY_CANCEL_BUTTON":
			if(comName=="leftstep")
			{
	            ADD_BUTTON();
			}
			if(comName=="rightstep")
			{
	            REMOVE_BUTTON();
			}
			if(comName=="speedleft")
			{
	      		ADD_ALL_BUTTON();
			}
			if(comName=="speedright")
			{
	            REMOVE_ALL_BUTTON();
			}
		break;
		// мины 07.07.07
		case "QTY_BOMB_BUTTON":
			if(comName=="click")
			{
			    SetMineFree(xi_refCharacter, 1);
			    iShipQty = GetCargoGoods(xi_refCharacter, GOOD_POWDER);
			    OnShipScrollChange();
			}
		break;
		/////////////////////////////////////////////
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_TRADEBOOK";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_TRADEBOOK" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}
///////////////////////////////////////////////////////////////////////////////////////////
void FillShipsScroll()
{
	nCurScrollNum = -1;
	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}

	string attributeName;
	string shipName;
	int iShipType, cn;
	GameInterface.SHIPS_SCROLL.ImagesGroup.t0 = "BLANK_SHIP2";

	FillShipList("SHIPS_SCROLL.ImagesGroup", xi_refCharacter);
	GameInterface.SHIPS_SCROLL.BadTex1 = 0;
	GameInterface.SHIPS_SCROLL.BadPic1 = "Not Used2";

	int m = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(xi_refCharacter, i);
		if(cn != -1)
		{
			iShipType = sti(characters[cn].ship.type);
			if(iShipType != SHIP_NOTUSED)
			{
				attributeName = "pic" + (m+1);
				//Boyer change #20170430-03
				//iShipType = sti(RealShips[iShipType].basetype);
				//shipName = ShipsTypes[iShipType].Name;

				ref rBaseShip = GetRealShip(iShipType);
				iShipType = rBaseShip.basetype;
                //#20170430-03 Companion ships are appended with a "1"
				shipName = rBaseShip.BaseName;
				string shipClass = rBaseShip.Class;

				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				//Boyer change #20170430-03
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#"+"Класс "+ShipsTypes[iShipType].Class;
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = shipName;
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "ship";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("SHIPS_SCROLL.ImagesGroup","SHIPS_"+shipName);
				m++;
			}
			else
			{
				attributeName = "pic" + (m+1);
				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = "NoneBoat";
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
				m++;
			}
		}
	}

	GameInterface.SHIPS_SCROLL.ListSize = m;
	GameInterface.SHIPS_SCROLL.NotUsed = COMPANION_MAX - m + 1;
}

void ProcessFrame()
{
	string attributeName;
	int iCharacter;

	string sNode = GetCurrentNode();
	if(sNode == "SHIPS_SCROLL")
	{
		if(sti(GameInterface.SHIPS_SCROLL.current)!= nCurScrollNum)
		{
			DeleteAttribute(&GameInterface, "TABLE_LIST.BackUp");
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			attributeName = "pic" + (nCurScrollNum+1);

			iCharacter = sti(GameInterface.SHIPS_SCROLL.(attributeName).character);

			if(iCharacter > 0)
			{
				string sChrId = characters[iCharacter].id;

				xi_refCharacter = characterFromID(sChrId);
				shipIndex= nCurScrollNum+ 1;
				if (shipIndex< 0)
				{
					shipIndex= 0;
				}
				if (sti(xi_refCharacter.ship.type) == SHIP_NOTUSED)
				{
					shipIndex= -1;
				}
				// boal оптимизация скилов -->
			    DelBakSkillAttr(xi_refCharacter);
			    ClearCharacterExpRate(xi_refCharacter);
			    RefreshCharacterSkillExpRate(xi_refCharacter);

			    SetEnergyToCharacter(xi_refCharacter);
			    // boal оптимизация скилов <--
				OnShipScrollChange();
			}
			else
			{
				shipIndex= -1;
			}
			return;
		}
	}
}
void OnShipScrollChange()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullName(xi_refCharacter));
	SetFormatedText("HERO_RANK",xi_refCharacter.Rank);
	// нулим все формы, тк корабля может не быть
	SetFormatedText("SHIP_RANK","");
	SetFormatedText("CREW_QTY","");
	SetFormatedText("FOOD", "");
	SetFormatedText("FOOD_SHIP", "");
	SetFormatedText("MONEY_SHIP", "");
	SetFormatedText("CREW_MORALE_TEXT", "");
	SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(1));
	SetSelectable("CREW_MORALE_BUTTON", false);
	Table_Clear("TABLE_LIST", false, true, false);
	Table_Clear("TABLE_OTHER", false, true, false);
	Table_Clear("TABLE_CREW", false, true, false);
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN,MONEY_DELIVER));
	int iShip = sti(xi_refCharacter.ship.type);

	SetNodeUsing("CREW_PARTITION", false);
	SetNodeUsing("RESORT", false);
	if (iShip != SHIP_NOTUSED)
	{
        // xi_refCharacter.ship.sp = CalculateShipSP(xi_refCharacter);
		// оптимизация скилов -->
	    DelBakSkillAttr(xi_refCharacter);
	    ClearCharacterExpRate(xi_refCharacter);
	    RefreshCharacterSkillExpRate(xi_refCharacter);
	    // оптимизация скилов <--

		if (CheckAttribute(xi_refCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(xi_refCharacter.Ship.Cargo.RecalculateCargoLoad))
		{
			RecalculateCargoLoad(xi_refCharacter);
			xi_refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
		}
		ref refShip = GetRealShip(iShip);
		string sShip = refShip.BaseName;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".tga.tx");
		if (!CheckAttribute(refShip,"QuestShip")) SetNodeUsing("SHIP_BIG_PICTURE_VIDEO",false);
		else {SetNodeUsing("SHIP_BIG_PICTURE_VIDEO",true); SetNewVideoPicture("SHIP_BIG_PICTURE_VIDEO","SHIP_"+sShip);}

		GameInterface.edit_box.str = xi_refCharacter.ship.name;
		SetFormatedText("SHIP_RANK", refShip.Class);
		SetFormatedText("CLASS_ARMOR", refShip.HullArmor);
		SetNewGroupPicture("CLASS_ARMOR_ICON", "ICONS_CHAR", "Reputation");
		FillGoodsTable();

		SetShipOTHERTable("TABLE_OTHER", xi_refCharacter);
		SetShipQualityTable(xi_refCharacter, "BAR_HP", "BAR_Mast", "BAR_Speed", "BAR_TurnRate", "BAR_WAS", "BAR_Capacity", "BAR_Crew");
		// еда -->
		int iColor, iFood;
		string sText;
		// на одном корабле
		SetFoodShipInfo(xi_refCharacter, "FOOD_SHIP");
		// в эскадре
		if (GetCompanionQuantity(pchar) > 1) SetSquadronFoodShipInfo(xi_refCharacter, "FOOD_SHIP"); // больше 1 ГГ
		// еда <--
		SetRumShipInfo(xi_refCharacter,"FOOD");
		if (GetRemovable(xi_refCharacter)) // считаем только своих, а то вских сопровождаемых кормить!!!
		{
		    // для каждого корабля учитываем класс и считаем отдельно
		    SetFormatedText("MONEY_SHIP", "Содержание корабля: " + NewStr() + FindRussianMoneyString(GetSalaryForShip(xi_refCharacter)));
		}
		SetFormatedText("CREW_QTY", ""+GetCrewQuantity(xi_refCharacter));
		if (GetCrewQuantity(xi_refCharacter) > GetOptCrewQuantity(xi_refCharacter) || GetCrewQuantity(xi_refCharacter) < GetMinCrewQuantity(xi_refCharacter))
		{
			iColor = argb(255,255,64,64);
		}
		else
		{
			iColor = argb(255,255,255,255);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY", 8,-1,iColor);
		SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(stf(xi_refCharacter.ship.crew.morale)));
		SetFormatedText("CREW_MORALE_TEXT", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(xi_refCharacter.Ship.crew.morale))));
		if (sti(xi_refCharacter.Ship.crew.morale) < MORALE_MAX && GetCrewQuantity(xi_refCharacter) > 0)
		{
			SetSelectable("CREW_MORALE_BUTTON", true);
		}
		SetNodeUsing("BAR_Sailors", true);
		SetNodeUsing("BAR_Cannoners", true);
		SetNodeUsing("BAR_Soldiers", true);
		SetNodeUsing("BAR_CrewMoral", true);
		SetCrewExpTable(xi_refCharacter, "TABLE_CREW", "BAR_Sailors", "BAR_Cannoners", "BAR_Soldiers");
		//BAR_CrewMoral
		GameInterface.StatusLine.BAR_CrewMoral.Max   = 100;
    	GameInterface.StatusLine.BAR_CrewMoral.Min   = 0;
    	GameInterface.StatusLine.BAR_CrewMoral.Value = sti(xi_refCharacter.Ship.crew.morale);
    	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, "BAR_CrewMoral", 0);
    	if (xi_refCharacter.id == pchar.id)
    	{
    		SetNodeUsing("CREW_PARTITION", true);
			SetNodeUsing("RESORT", true);
    	}

		if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.HullSpecial")) SetNewGroupPicture("EXTRAHULLON", "SHIP_UPGRADES", "EXTRAHULLON");
		else SetNewGroupPicture("EXTRAHULLON", "SHIP_UPGRADES", "EXTRAHULLOFF");
		if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.SailsSpecial")) SetNewGroupPicture("EXTRASAILON", "SHIP_UPGRADES", "EXTRASAILON");
		else SetNewGroupPicture("EXTRASAILON", "SHIP_UPGRADES", "EXTRASAILOFF");
		if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.CannonsSpecial")) SetNewGroupPicture("EXTRAGUNSON", "SHIP_UPGRADES", "EXTRAGUNSON");
		else SetNewGroupPicture("EXTRAGUNSON", "SHIP_UPGRADES", "EXTRAGUNSOFF");
		if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.CuBot")) SetNewGroupPicture("EXTRAHULLKRENGON", "SHIP_UPGRADES", "EXTRAHULLKRENGON");
		else SetNewGroupPicture("EXTRAHULLKRENGON", "SHIP_UPGRADES", "EXTRAHULLKRENGOFF");
		if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.BotPack")) SetNewGroupPicture("ExtraCapacityOn", "SHIP_UPGRADES", "ExtraCapacityOn");
		else SetNewGroupPicture("ExtraCapacityOn", "SHIP_UPGRADES", "ExtraCapacityOff");
		if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.HighBort")) SetNewGroupPicture("ExtraBigSidesOn", "SHIP_UPGRADES", "ExtraBigSidesOn");
		else SetNewGroupPicture("ExtraBigSidesOn", "SHIP_UPGRADES", "ExtraBigSidesOff");
		float SoilS, SoilM;
		if( !CheckAttribute(xi_refCharacter, "ship.soiling")){ xi_refCharacter.ship.soiling = 0;}
		SoilS = 100*(1 - ShipSpeedBonusFromSoiling(xi_refCharacter));
		SoilM = 100*(1 - ShipTurnRateBonusFromSoiling(xi_refCharacter));
		string sSoil = xi_refCharacter.ship.soiling +"%";

		sText = "Загрязнение дна: ";
		SetFormatedText("Soil_TEXT", sText);
		SetFormatedText("SoilN_TEXT", sSoil);
		if (SoilS < 0.1) sSoil = "0%"; else sSoil = fts(SoilS, 3) + "%";
		sText = "Штраф к скорости: " + sSoil;
		SetFormatedText("SoilS_TEXT", sText);
		if (SoilM < 0.1) sSoil = "0%"; else sSoil = fts(SoilM, 3) + "%";
		sText = "к маневренности: " + sSoil;
		SetFormatedText("SoilM_TEXT", sText);
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\blank_ship2.tga.tx");
		GameInterface.edit_box.str = XI_Convertstring("NoneBoat");
		SetNodeUsing("BAR_Sailors", false);
		SetNodeUsing("BAR_Cannoners", false);
		SetNodeUsing("BAR_Soldiers", false);
		SetNodeUsing("BAR_CrewMoral", false);
	}
	Table_UpdateWindow("TABLE_LIST");
	Table_UpdateWindow("TABLE_OTHER");
	Table_UpdateWindow("TABLE_CREW");
}

void confirmShipChangeName()
{
	if (shipIndex== -1) return;
	xi_refcharacter.ship.name = GameInterface.edit_box.str;
	GameInterface.edit_box.str = xi_refcharacter.ship.name;
	//SetCurrentNode("SHIP_INFO_TEXT");
	if(GameInterface.EDIT_BOX.lastkey != " ") SetCurrentNode("SHIPS_SCROLL");
}

void CheckForRename()
{
	if (GetShipRemovable(xi_refCharacter) == true && shipIndex!= -1)
	{
		SetCurrentNode("EDIT_BOX");
	}
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;
	int xx = 256;
	int yy = 256;

	//Boyer fix #20170401-01 Can't load texture -1.tx log errors
	//sPicture = "-1";
	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	int iShip;
	ref refBaseShip;

	bool  bShowHint = true;
	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			if (shipIndex != -1)
			{
			    iShip = sti(xi_refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat", "ShipsDescribe.txt");
			}
		break;

		case "SHIPS_SCROLL":
			if (shipIndex != -1)
			{
			    iShip = sti(xi_refCharacter.ship.type);
			    refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
				sText2 = GetRPGText("shipChoose_hint");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1  = GetConvertStr("NoneBoat", "ShipsDescribe.txt");
			}
		break;

		case "MAIN_CHARACTER_PICTURE":
			// отдельная форма
			bShowHint = false;
			ShowRPGHint();
		break;

		case "TABLE_LIST":
			sHeader = XI_Convertstring("Goods");
			sText1  = GetRPGText("GoodsCargo_hint");
		break;

		case "TABLE_CREW":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break;

		case "CLASS_ARMOR_ICON":
			sHeader = GetConvertStr("Class_Armor", "ShipsDescribe.txt");
			sText1  = GetConvertStr("Class_Armor_hint", "ShipsDescribe.txt");
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(xi_refCharacter.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
		    {
		    	ref Cannon = GetCannonByType(sti(xi_refCharacter.Ship.Cannons.Type));
		    	sText2 = "Тип: " + XI_ConvertString(GetCannonType(sti(xi_refCharacter.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "Калибр: " + XI_ConvertString("caliber" + GetCannonCaliber(sti(xi_refCharacter.Ship.Cannons.Type)));
		    	sText2 = sText2 + NewStr() + "Дальность: "  + sti(Cannon.FireRange);
		    	sText2 = sText2 + NewStr() + "Урон: x"  + FloatToString(stf(Cannon.DamageMultiply), 1);
		    	sText2 = sText2 + NewStr() + "Перезарядка: "  + sti(GetCannonReloadTime(Cannon)) + " сек.";
		    	sText2 = sText2 + NewStr() + "Вес: "  + sti(Cannon.Weight) + " ц.";

		    	sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(xi_refCharacter.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(xi_refCharacter.Ship.Cannons.Type));

				sText3 = "Двойной клик или Enter по этому полю вызывает интерфейс экипировки орудий по бортам, где их можно снять или установить из запасов в трюме.";
		    }
		    if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText2 = "Команды может быть больше максимальной, но это вызывает перегруз и условия жизни на корабле становятся ужасными, что влечет ежедневное падение морали. В среднем можно взять на борт до 25% больше матросов.";
				sText2 = sText2 + NewStr() + "Максимальное количество экипажа с учетом перегруза: " + GetMaxCrewQuantity(xi_refCharacter);
			}
			// процент ремонта
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
                if (GetHullPercent(xi_refCharacter)<100.0 )
                {
					sText2 = "Ремонт " + FloatToString(GetHullRepairDay(xi_refCharacter, false),2) + " % в день, расход " + makeint(GetHullRepairDay(xi_refCharacter, true)) + " шт. досок";
				}
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(xi_refCharacter), 1)  + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
                if (GetSailPercent(xi_refCharacter)<100.0 )
                {
					sText2 = "Ремонт " + FloatToString(GetSailRepairDay(xi_refCharacter, false),2) + " % в день, расход " + makeint(GetSailRepairDay(xi_refCharacter, true))+ " шт. парусины";
				}
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(xi_refCharacter), 1) + " %";
			}
			// трюм
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(xi_refCharacter.ship.type) != SHIP_NOTUSED)
			{
				sText3 = "Занято: " + FloatToString((stf(GetCargoLoad(xi_refCharacter))  /  stf(GetCargoMaxSpace(xi_refCharacter))) * 100.0, 1)+ " %";
			}
		break;
		case "CREW_PARTITION":
			sHeader = XI_Convertstring("PartitionCaption");
			sText1  = GetRPGText("Partition_hint");
		break;
		case "RESORT":
			sHeader = XI_Convertstring("RESORTCaption");
			sText1  = GetRPGText("Resort_hint");
		break;
		case "Soil_TEXT":
			sHeader = XI_ConvertString("Soil_Tooltip");
			sText1 = XI_ConvertString("Soil_descr_Tooltip");
		break;
		case "SoilS_TEXT":
			sHeader = XI_ConvertString("SoilS_Tooltip");
			sText1 = XI_ConvertString("SoilS_descr_Tooltip");
		break;
		case "SoilM_TEXT":
			sHeader = XI_ConvertString("SoilM_Tooltip");
			sText1 = XI_ConvertString("SoilM_descr_Tooltip");
		break;

		// LEO - чудим с доп инфой
		case "EXTRAHULLON":
			sHeader = XI_ConvertString("EXTRAHULLON");
			sText1 = GetConvertStr("SUP_HULL_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.HullSpecial")) sGroupPicture = "EXTRAHULLON";
			else sGroupPicture = "EXTRAHULLOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRASAILON":
			sHeader = XI_ConvertString("EXTRASAILON");
			sText1 = GetConvertStr("SUP_SAIL_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.SailsSpecial")) sGroupPicture = "EXTRASAILON";
			else sGroupPicture = "EXTRASAILOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRAGUNSON":
			sHeader = XI_ConvertString("EXTRAGUNSON");
			sText1 = GetConvertStr("SUP_CANNONS_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.CannonsSpecial")) sGroupPicture = "EXTRAGUNSON";
			else sGroupPicture = "EXTRAGUNSOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRAHULLKRENGON":
			sHeader = XI_ConvertString("EXTRAHULLKRENGON");
			sText1 = GetConvertStr("SUP_HULLCOPPER_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.CuBot")) sGroupPicture = "EXTRAHULLKRENGON";
			else sGroupPicture = "EXTRAHULLKRENGOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRACAPACITYON":
			sHeader = XI_ConvertString("EXTRACAPACITYON");
			sText1 = GetConvertStr("SUP_CAPACITY_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.BotPack")) sGroupPicture = "EXTRACAPACITYON";
			else sGroupPicture = "EXTRACAPACITYOFF";
			xx = 256;
			yy = 256;
		break;
		case "EXTRABIGSIDESON":
			sHeader = XI_ConvertString("EXTRABIGSIDESON");
			sText1 = GetConvertStr("SUP_BIGSIDES_descr", "ShipsDescribe.txt");

			sGroup = "SHIP_UPGRADES";
			if (CheckAttribute(RealShips[sti(xi_refCharacter.Ship.Type)],"Tuning.HighBort")) sGroupPicture = "EXTRABIGSIDESON";
			else sGroupPicture = "EXTRABIGSIDESOFF";
			xx = 256;
			yy = 256;
		break;
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, xx, yy);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    NullSelectTable("TABLE_LIST");
    NullSelectTable("TABLE_OTHER");
    NullSelectTable("TABLE_CREW");
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", false);
		sMessageMode = "";
	}
}

void ShowRPGHint()
{
	SetSPECIALMiniTable("TABLE_SMALLSKILL", xi_refCharacter);
    SetOTHERMiniTable("TABLE_SMALLOTHER", xi_refCharacter);
    SetFormatedText("OFFICER_NAME", GetFullName(xi_refCharacter));

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}

void FillGoodsTable()
{
	int n, i, qty;
	string row;
	ref rShip;
	string sGood;
	aref refGoods;

	n = 1;
	if (!CheckAttribute(&GameInterface, "TABLE_LIST.BackUp"))
	{
		GameInterface.TABLE_LIST.select = 0;
		GameInterface.TABLE_LIST.top    = 0;
		GameInterface.TABLE_LIST.BackUp = true;
	}
    for (i = 0; i< GOODS_QUANTITY; i++)
	{
        row = "tr" + n;
		sGood = Goods[i].name;
		qty = GetCargoGoods(xi_refCharacter, i);
		if (qty <= 0) continue; // только не нули

		GameInterface.TABLE_LIST.(row).index = i;

		GameInterface.TABLE_LIST.(row).td2.str = qty;
		GameInterface.TABLE_LIST.(row).td3.str = GetGoodWeightByType(i, qty);
		GameInterface.TABLE_LIST.(row).td4.str = Goods[i].Units;
		GameInterface.TABLE_LIST.(row).td5.str = Goods[i].Weight;

        GameInterface.TABLE_LIST.(row).td1.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td1.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td1.icon.offset = "0, 0";
		GameInterface.TABLE_LIST.(row).td1.icon.width = 20;
		GameInterface.TABLE_LIST.(row).td1.icon.height = 20;
		GameInterface.TABLE_LIST.(row).td1.textoffset = "10,0";
		GameInterface.TABLE_LIST.(row).td1.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).td1.scale = 0.88;
		n++;
	}
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void ShowItemInfo()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) // нет товара вообще
	{
	    ShowGoodsInfo(sti(GameInterface.(CurTable).(CurRow).index));
		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", true);
		SetCurrentNode("QTY_CANCEL_BUTTON");
		if (GetRemovable(xi_refCharacter))
		{
		    SetSelectable("QTY_OK_BUTTON", true);
		}
		else
		{
		    SetSelectable("QTY_OK_BUTTON", false);
		}
		// мины
	    if (sti(GameInterface.(CurTable).(CurRow).index) == GOOD_POWDER)
	    {
	        SetNodeUsing("QTY_BOMB_BUTTON", true);
	        if (bSeaActive && !bAbordageStarted && GetRemovable(xi_refCharacter))
	        {
	            SetSelectable("QTY_BOMB_BUTTON", true);
	        }
	        else
	        {
	            SetSelectable("QTY_BOMB_BUTTON", false);
	        }
		}
		else
		{
		    SetNodeUsing("QTY_BOMB_BUTTON", false);
		}
	}
}

void GoodsExitCancel()
{

	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("TABLE_LIST");
	// пересчитаем новые пареметры от веса
	if (iShipQty != GetCargoGoods(xi_refCharacter, iCurGoodsIdx))
	{
		SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty); // вернем обратно
		OnShipScrollChange();
	}
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	int lngFileID = LanguageOpenFile("GoodsDescribe.txt");
	string sHeader = XI_ConvertString(GoodName);

    iCurGoodsIdx = iGoodIndex;
	string goodsDescr = GetAssembledString( LanguageConvertString(lngFileID,goodName+"_descr"), &Goods[iGoodIndex]);
    goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
	              ", пачка " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits  = sti(Goods[iGoodIndex].Units);
	//fWeight = stf(Goods[iGoodIndex].weight);
	if(checkAttribute(pchar, "ship.cargo.goods." + GoodName + ".isquest"))
	{
		string sTradeQ = pchar.ship.cargo.goods.(GoodName).isquest.quantity;
		string sColony = pchar.ship.cargo.goods.(GoodName).isquest.colony;
		goodsDescr += NewStr() + XI_ConvertString("YouNeedToDelivery") + sTradeQ + XI_ConvertString("QuantityOfGoodsToColony") + XI_ConvertString("Colony"+sColony) + ".";
	}

    SetFormatedText("QTY_TypeOperation", "Выкинуть?");
    SetFormatedText("QTY_Result", "");
    GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
    SetFormatedText("QTY_CAPTION", sHeader);
    SetFormatedText("QTY_GOODS_INFO", goodsDescr);
	LanguageCloseFile(lngFileID);

	iShipQty = GetCargoGoods(xi_refCharacter, iGoodIndex);
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty))
    SetFormatedText("QTY_INFO_STORE_QTY", its(GetGoodWeightByType(iGoodIndex, iShipQty)));

    SetFormatedText("QTY_INFO_STORE_PRICE", "Вес в трюме");
    SetFormatedText("QTY_INFO_SHIP_PRICE",  "Количество в трюме");
}

void TransactionOK()
{
	int nTradeQuantity;
	confirmChangeQTY_EDIT();

	nTradeQuantity = sti(GameInterface.qty_edit.str);

    SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty);

    if (!GetRemovable(xi_refCharacter)) return;
	if (nTradeQuantity > 0)
	{
		DropGoodsToSeaFromInterface(iCurGoodsIdx, nTradeQuantity); // остается плавать в море
		iShipQty = GetCargoGoods(xi_refCharacter, iCurGoodsIdx);
	}
	GoodsExitCancel();
	SetFormatedText("SHIPS_WEIGHTS", GetShipsWeights());
	//SetShipOTHERTable("TABLE_OTHER", xi_refCharacter);
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
    SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	int  iWeight;
	GameInterface.qty_edit.str = abs(sti(GameInterface.qty_edit.str));  // приведение к числу

	string GoodName = goods[iCurGoodsIdx].name;

    // проверка на колво доступное -->
    if (sti(GameInterface.qty_edit.str) > iShipQty)
    {
        GameInterface.qty_edit.str = iShipQty;
    }
    SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty - sti(GameInterface.qty_edit.str)))
	SetFormatedText("QTY_INFO_STORE_QTY", its(GetGoodWeightByType(iCurGoodsIdx, (iShipQty - sti(GameInterface.qty_edit.str)))));
	// прикидываем место в трюме
	iWeight = sti(GameInterface.qty_edit.str);
	SetCharacterGoods(xi_refCharacter, iCurGoodsIdx, iShipQty);
	if (iWeight > 0)
	{
		RemoveCharacterGoods(xi_refCharacter, iCurGoodsIdx, iWeight);
	}
	OnShipScrollChange();
	///iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
	//GameInterface.TABLE_OTHER.tr6.td3.str = (GetCargoLoad(xi_refCharacter) - iWeight) + " / " + GetCargoMaxSpace(xi_refCharacter);
	//Table_UpdateWindow("TABLE_OTHER");
}

void REMOVE_ALL_BUTTON()  // продать все
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = iShipQty;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + iUnits);
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	if (!GetRemovable(xi_refCharacter)) return;
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - iUnits);
	if (sti(GameInterface.qty_edit.str) < 0) GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT();
}

void DropGoodsToSeaFromInterface(int iGoodIndex, int iQuantity)
{
	ref rGood;
	string sGood;

	sGood = Goods[iGoodIndex].name;

	if (CheckAttribute(xi_refCharacter, "Ship.Cargo.Goods."+sGood))
	{
		RemoveCharacterGoods(xi_refCharacter, iGoodIndex, iQuantity);
		if (bSeaActive && !bAbordageStarted)  // море, но не каюта
		{
			iQuantity = iQuantity / sti(Goods[iGoodIndex].Units);

			int iSwimQuantity = makeint(iQuantity/3 + rand(makeint(iQuantity/3)) + rand(makeint(iQuantity/3)));

			if(iSwimQuantity < 1)
			{
				iSwimQuantity = 1;
			}

			RecalculateCargoLoad(xi_refCharacter);

			if (CheckAttribute(&Goods[iGoodIndex], "Swim"))
			{
				float fTime = stf(Goods[iGoodIndex].Swim.Time);
				string sModel = Goods[iGoodIndex].Swim.Model;

				fTime = fTime + (frnd() - 0.5) * fTime / 2.0;

				AISeaGoods_AddGood(xi_refCharacter, sGood, sModel, fTime * 60.0, iSwimQuantity);
			}
			PlaySound("Ships\jakor_002.wav");
		}
	}
}

void ShipChange()
{
	bool bOk;
	if (xi_refCharacter.id != pchar.id && sti(pchar.ship.type) != SHIP_NOTUSED)
	{
		SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("companionship"));
		SetFormatedText("REMOVE_WINDOW_TEXT", "Перейти в режим обмена между кораблями?");
		SetSelectable("REMOVE_ACCEPT_OFFICER", true);
		bOk = !bSeaActive && LAi_grp_alarmactive;
		if (bDisableMapEnter || bOk || chrDisableReloadToLocation)
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", "Во время боя обмен с кораблями возможен только борт к борту.");
			SetSelectable("REMOVE_ACCEPT_OFFICER", false);
		}
		if (bSeaActive && GetShipEscape())
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", "Использование способности 'спасение на шлюпке' позволяет обмениваться с кораблями в бою. Продолжить?");
			SetSelectable("REMOVE_ACCEPT_OFFICER", true);
		}
		if (!GetRemovable(xi_refCharacter))
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", "Обмен с кораблем этого компаньона невозможен.");
			SetSelectable("REMOVE_ACCEPT_OFFICER", false);
		}
		if (sti(pchar.ship.type) == SHIP_NOTUSED)
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", "Обмен невозможен. У героя нет корабля.");
			SetSelectable("REMOVE_ACCEPT_OFFICER", false);
		}
		sMessageMode = "ShipChange";
		ShowShipChangeMenu();
	}
}

void ExitShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void ShowShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("REMOVE_CANCEL_OFFICER");
}

bool GetShipEscape()
{
    if (CheckCharacterPerk(PChar, "ShipEscape") && GetHullPercent(PChar) <= 15.0)
    {
        return true;
    }
    return false;
}

void ShowOtherClick()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".UserData.ID") && GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
	{
		ShowCannonsMenu();
	}
}

void GoToShipChange()
{
	if (sMessageMode == "MoraleMessage") // мораль
	{
		AddMoneyToCharacter(pchar, -GetCharacterRaiseCrewMoraleMoney(xi_refCharacter));
		Statistic_AddValue(pchar, "PartitionPay", GetCharacterRaiseCrewMoraleMoney(xi_refCharacter));
		AddCrewMorale(xi_refCharacter, 10);
		ExitShipChangeMenu();
		OnShipScrollChange();
	}
	if (sMessageMode == "ShipChange") // обмен с кораблем
	{
		pchar.TransferChar = xi_refCharacter.index;
		InterfaceStates.ReloadMenuExit = true;
		IDoExit(RC_INTERFACE_ANY_EXIT);
		PostEvent("LaunchIAfterFrame",1,"sl", "TransferMain", 2);
	}
}

void ShowMoraleMessage()
{
	int  sum = GetCharacterRaiseCrewMoraleMoney(xi_refCharacter);
	SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("RaiseMorale"));
	SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("RaiseMoraleMoney") + FindRussianMoneyString(sum));

	if (sum <= sti(pchar.money))
	{
		SetSelectable("REMOVE_ACCEPT_OFFICER", true);
	}
	else
	{
		SetSelectable("REMOVE_ACCEPT_OFFICER", false);
	}
	sMessageMode = "MoraleMessage";
	ShowShipChangeMenu();
}

void ShowCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", true);
	XI_WindowDisable("CANNONS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("CANNONS_CANCEL");

    SetBackupCannons(); // запомнить, для отката

    bool bOk  = !bSeaActive && LAi_grp_alarmactive;
    bool bOk2 = bAbordageStarted && !bCabinStarted; // в абордаже не жать пушки
	if (bDisableMapEnter || bOk || bOk2)
    { // идёт бой, запрет смены орудий
    	SetSelectable("CANNONS_OK", false);
	}
	else
	{
		SetSelectable("CANNONS_OK", true);
	}
	if (!GetRemovable(xi_refCharacter))
	{
		SetSelectable("CANNONS_OK", false);
	}
    DeleteAttribute(&GameInterface, "CANNONS_TABLE.BackUp")
    CannonsMenuRefresh();
}
void CannonsMenuRefresh()
{
	int idx = GetCannonGoodsIdxByType(sti(xi_refCharacter.Ship.Cannons.Type));
	if (idx != -1)
	{
	    SetNewGroupPicture("CANNONS_PIC", "GOODS", Goods[idx].Name);
		SetFormatedText("CANNONS_TEXT", XI_ConvertString(Goods[idx].Name));

		SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQty(xi_refCharacter, "fcannon")));
		SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQty(xi_refCharacter, "bcannon")));
		SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQty(xi_refCharacter, "rcannon")));
		SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQty(xi_refCharacter, "lcannon")));
		/// всего GetCannonsNum(xi_refCharacter)
	}
	else
	{
		SetNewGroupPicture("CANNONS_PIC", "GOODS", "");
		SetFormatedText("CANNONS_TEXT", "");
		SetFormatedText("CANNONS_QTY_F", "0");
		SetFormatedText("CANNONS_QTY_B", "0");
		SetFormatedText("CANNONS_QTY_R", "0");
		SetFormatedText("CANNONS_QTY_L", "0");
	}
	FillCannonsTable();
	if (IsMainCharacter(xi_refCharacter)) BI_UpdateCannons();
}
void ExitCannonsMenu()
{
	HideCannonsMenu();

	GetBackupCannons(); // отмена
	OnShipScrollChange();
}

void HideCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", false);
	XI_WindowDisable("CANNONS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

/// установить орудия по борту (сперва расчитать дельту было стало - лишнее в запасы)
void SetCannonsToBort(ref chr, string sBort, int iQty)
{
	int     curQty = GetBortCannonsQty(chr, sBort);
	int     maxQty = GetBortCannonsMaxQty(chr, sBort);
	int     i, delta;
	string  attr;
	int     center, left, right; // счетчики орудий для распределения
	bool    bLeft; // направление хода
	string  sBort_real;

	if(sBort == "rcannon") sBort_real = "cannonr";
	if(sBort == "lcannon") sBort_real = "cannonl";
	if(sBort == "fcannon") sBort_real = "cannonf";
	if(sBort == "bcannon") sBort_real = "cannonb";

	if (iQty > maxQty) iQty = maxQty;
	if (iQty < 0) iQty = 0;

	int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));
    delta = iQty - curQty;
    if (delta > 0)
    {
    	if (GetCargoGoods(chr, idx) < delta) iQty = curQty + GetCargoGoods(chr, idx);
    }
	if (iQty > curQty)
	{ // списать со склада
		RemoveCharacterGoodsSelf(chr, idx, (iQty - curQty));
	}
	else
	{
		if (iQty < curQty)
		{// лишние на склад
			SetCharacterGoods(chr, idx, GetCargoGoods(chr, idx) + (curQty - iQty)); // этот метод, тк перегруз может быть, а  AddCharacterGoodsSimple режет перегруз
		}
	}
	// нулим колво пушек на борту и распределяем заново от центра (как они на модели по номерам не знаю, допуск, что подряд)
	for (i = 0; i < maxQty; i++)
	{
		attr = "c" + i;
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0; // поломана на 100 процентов, не палит, те нет её
		chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0; // поломана на 100 процентов, не палит, те нет её
	}
	// распределяем
	if (iQty > 0)
	{
		center = makeint(maxQty / 2); // целочисленное деление
		left   = center - 1;
		right  = center;
		i = 0; // сколько распределили уже
		bLeft = true;
		while (i < iQty)
		{
			if (bLeft)
			{
				if (left >= 0)
				{
					attr = "c" + left;
					left--;
				}
				else
				{
					attr = "c" + right;
					right++;
				}
				if (right < maxQty) bLeft = false;
			}
			else
			{
				if (right < maxQty)
				{
					attr = "c" + right;
					right++;
				}
				else
				{
					attr = "c" + left;
					left--;
				}
				if (left >= 0) bLeft = true;
			}
			chr.Ship.Cannons.borts.(sBort).damages.(attr) = 0.0; // новая, не битая
			chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 0.0; // новая, не битая
			i++;
		}
	}
	RecalculateCargoLoad(chr);  // пересчет, тк пушки снялись
}

void CanonsRemoveAll()
{
    SetCannonsToBort(xi_refCharacter, "fcannon", 0);
    SetCannonsToBort(xi_refCharacter, "bcannon", 0);
    SetCannonsToBort(xi_refCharacter, "rcannon", 0);
    SetCannonsToBort(xi_refCharacter, "lcannon", 0);
    OnShipScrollChange();
    CannonsMenuRefresh();
}

// бакап значений, до применения
void SetBackupCannons()
{
	aref    arTo, arFrom;
	NullCharacter.ShipBak.Cannons = "";
	NullCharacter.ShipBak.Cargo   = "";

	makearef(arTo,   NullCharacter.ShipBak.Cannons);
	makearef(arFrom, xi_refCharacter.Ship.Cannons);
	CopyAttributes(arTo, arFrom);

	makearef(arTo,   NullCharacter.ShipBak.Cargo);
	makearef(arFrom, xi_refCharacter.Ship.Cargo);
	CopyAttributes(arTo, arFrom);
}

void GetBackupCannons()
{
	aref    arTo, arFrom;

	makearef(arFrom,   NullCharacter.ShipBak.Cannons);
	makearef(arTo, xi_refCharacter.Ship.Cannons);
	CopyAttributes(arTo, arFrom);

	makearef(arFrom,   NullCharacter.ShipBak.Cargo);
	makearef(arTo, xi_refCharacter.Ship.Cargo);
	CopyAttributes(arTo, arFrom);
}

void CanonsSetAll(ref chr)
{
    if (GetCannonQuantity(chr) <= 0) return;
    //if (GetCannonQuantity(chr) <= GetCannonsNum(chr)) return;
	// сначала все убрать
    if (GetCannonsNum(chr) > 0)
    {
		SetCannonsToBort(chr, "fcannon", 0);
	    SetCannonsToBort(chr, "bcannon", 0);
	    SetCannonsToBort(chr, "rcannon", 0);
	    SetCannonsToBort(chr, "lcannon", 0);
    }
    //новый калибр назначить
    if (CurTable == "CANNONS_TABLE" && CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
    {
		chr.Ship.Cannons.Type = sti(Goods[sti(GameInterface.(CurTable).(CurRow).index)].CannonIdx);
	}
    // потом все выставить раскидав по бортам
    int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));
    int fb, lb, rb, bb;
    int qty;

    if (idx != -1)
    {
    	qty = GetCargoGoods(chr, idx);

    	rb = GetBortCannonsMaxQty(chr, "rcannon");

    	if (rb  > (qty / 2)) rb = qty / 2;
    	qty = qty - rb;
    	if (qty < 0) qty = 0;

    	lb = GetBortCannonsMaxQty(chr, "lcannon");
    	if (lb > qty) lb = qty;
    	qty = qty - lb;
    	if (qty < 0) qty = 0;

    	bb = GetBortCannonsMaxQty(chr, "bcannon");
    	if (bb > qty) bb = qty;
    	qty = qty - bb;
    	if (qty < 0) qty = 0;

    	fb = GetBortCannonsMaxQty(chr, "fcannon");
    	if (fb > qty) fb = qty;

    	SetCannonsToBort(chr, "fcannon", fb);
	    SetCannonsToBort(chr, "bcannon", bb);
	    SetCannonsToBort(chr, "rcannon", rb);
	    SetCannonsToBort(chr, "lcannon", lb);
    }
    // рефреш
    OnShipScrollChange();
    CannonsMenuRefresh();
}

void ChangeCannonNum(string sBort, int add)
{
    SetCannonsToBort(xi_refCharacter, sBort, GetBortCannonsQty(xi_refCharacter, sBort) + add);
    OnShipScrollChange();
	CannonsMenuRefresh();
}

void FillCannonsTable()
{
	int n, i, qty;
	string row;
	ref rShip;
	string sGood;
	aref refGoods;

	n = 1;
	Table_Clear("CANNONS_TABLE", false, true, false);
	GameInterface.CANNONS_TABLE.hr.td1.str = "Орудий в трюме";
	GameInterface.CANNONS_TABLE.hr.td1.scale = 0.8;
	GameInterface.CANNONS_TABLE.hr.td2.str = "Кол-во";
	GameInterface.CANNONS_TABLE.hr.td2.scale = 0.8;
	GameInterface.CANNONS_TABLE.hr.td3.str = "Дистан.";
	GameInterface.CANNONS_TABLE.hr.td3.scale = 0.8;
	GameInterface.CANNONS_TABLE.hr.td4.str = "Урон";
	GameInterface.CANNONS_TABLE.hr.td4.scale = 0.8;
	GameInterface.CANNONS_TABLE.hr.td5.str = "Время";
	GameInterface.CANNONS_TABLE.hr.td5.scale = 0.8;

	if (!CheckAttribute(&GameInterface, "CANNONS_TABLE.BackUp"))
	{
		GameInterface.CANNONS_TABLE.select = 0;
		GameInterface.CANNONS_TABLE.top    = 0;
		GameInterface.CANNONS_TABLE.BackUp = true;
	}
	if (GetCannonQuantity(xi_refCharacter) > 0)
	{
	    for (i = 0; i< GOODS_QUANTITY; i++)
		{
	        row = "tr" + n;
			sGood = Goods[i].name;
			qty = GetCargoGoods(xi_refCharacter, i);
			if (qty <= 0) continue; // только не нули

	        if (!CheckAttribute(&Goods[i], "type")) continue;
	        if (sti(Goods[i].type) != TRADE_TYPE_CANNONS) continue;

	        if (GetCannonCaliber(sti(Goods[i].CannonIdx)) > GetMaximumCaliber(xi_refCharacter)) continue;
			GameInterface.CANNONS_TABLE.(row).index = i;

			GameInterface.CANNONS_TABLE.(row).td2.str = qty;
			GameInterface.CANNONS_TABLE.(row).td2.scale = 0.85;
			GameInterface.CANNONS_TABLE.(row).td3.str = sti(Goods[i].FireRange);
			GameInterface.CANNONS_TABLE.(row).td3.scale = 0.85;
			GameInterface.CANNONS_TABLE.(row).td4.str = "x"+FloatToString(stf(Goods[i].DamageMultiply), 1);
			GameInterface.CANNONS_TABLE.(row).td4.scale = 0.85;
			GameInterface.CANNONS_TABLE.(row).td5.str = sti(Goods[i].ReloadTime);
			GameInterface.CANNONS_TABLE.(row).td5.scale = 0.85;

	        GameInterface.CANNONS_TABLE.(row).td1.icon.group = "GOODS";
			GameInterface.CANNONS_TABLE.(row).td1.icon.image = sGood;
			GameInterface.CANNONS_TABLE.(row).td1.icon.offset = "0, 0";
			GameInterface.CANNONS_TABLE.(row).td1.icon.width = 32;
			GameInterface.CANNONS_TABLE.(row).td1.icon.height = 32;
			GameInterface.CANNONS_TABLE.(row).td1.textoffset = "28,0";
			GameInterface.CANNONS_TABLE.(row).td1.str = XI_ConvertString(sGood);
			GameInterface.CANNONS_TABLE.(row).td1.scale = 0.75;
			n++;
		}
	}
	Table_UpdateWindow("CANNONS_TABLE");
}

void ShowPartitionWindow()
{
    string str;
	string sTitul = "";
	if (isMainCharacterPatented())
	{
		sTitul = GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))
	}

	str = "Текущая дата: " + GetDateString() + " " + GetTimeString() + NewStr();
	if(CheckAttribute(pchar, "paymentdate"))
	{
		str += "Дата предыдущего платежа: " + pchar.paymentdate + NewStr();
	}
	str += sTitul + " " + GetFullName(pchar) + NewStr() + XI_ConvertString("Rank") + ": " + sti(pchar.rank) + NewStr();
	str += XI_ConvertString("m_Complexity") + ": " + GetLevelComplexity(MOD_SKILL_ENEMY_RATE) + NewStr() +
			XI_ConvertString("OurMoney") + FindRussianMoneyString(sti(pchar.money)) + NewStr() + "*****" + NewStr();
    str += "Доли в текущем месяце:" + NewStr() + "Доля капитана: " + GetPartitionAmount("Partition.MonthPart.Hero") + NewStr() +
		  "Доля офицеров: " + GetPartitionAmount("Partition.MonthPart.Officers") + NewStr() +
		  "Доля матросов: " + GetPartitionAmount("Partition.MonthPart.Crew") + NewStr() + // + "-----" + NewStr() +
		  "Долг текущего месяца: " + GetPartitionAmount("Partition.MonthPart") + NewStr();
	str += "*****" + NewStr() + "Долг за прошлый месяц: " + GetPartitionAmount("CrewPayment");

	SetFormatedText("PARTITION_WINDOW_TEXT", str);
    SetSelectable("PARTITION_OK", false);
	if (GetPartitionAmount("Partition.MonthPart") > 0 || GetPartitionAmount("CrewPayment") > 0)
	{
		if (sti(Pchar.Money) > 0)
		{
			SetSelectable("PARTITION_OK", true);
		}
	}
	XI_WindowShow("PARTITION_WINDOW", true);
	XI_WindowDisable("PARTITION_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("PARTITION_CANCEL");
}

void ExitPartitionWindow()
{
	XI_WindowShow("PARTITION_WINDOW", false);
	XI_WindowDisable("PARTITION_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void DoPartitionPay()
{
	int sum = 0;
	if (GetPartitionAmount("Partition.MonthPart") > 0 || GetPartitionAmount("CrewPayment") > 0)
	if (GetPartitionAmount("CrewPayment") > 0)
	{
	    sum = GetPartitionAmount("CrewPayment");
	    if (sti(Pchar.Money) < sum) sum = sti(Pchar.Money);
        Pchar.CrewPayment = sti(Pchar.CrewPayment) - sum;
        if (sti(Pchar.CrewPayment) <= 0) DeleteAttribute(Pchar, "CrewPayment");
	}
	else
	{
		if (GetPartitionAmount("Partition.MonthPart") > 0)
		{
		    sum = GetPartitionAmount("Partition.MonthPart");
		    if (sti(Pchar.Money) < sum) sum = sti(Pchar.Money);
	        Pchar.Partition.MonthPart = sti(Pchar.Partition.MonthPart) - sum;
	        AddCrewMorale(xi_refCharacter, 2);
		}
	}
	pchar.paymentdate = GetDateString() + " " + GetTimeString();
	AddMoneyToCharacter(Pchar, -sum);
	Statistic_AddValue(pchar, "PartitionPay", sum);
	OnShipScrollChange();
	ExitPartitionWindow();
}

int GetPartitionAmount(string _param)
{
    if (!CheckAttribute(Pchar, _param)) return 0;
    return sti(Pchar.(_param));
}

void SortCompanionsBy(string attrName) // сортируем по базовому атрибуту корабля
{
    Log_Info("123");
    int ids[7];
    int ids_num = 0;

    int cq = GetCompanionQuantity(pchar);
    if (cq <= 1) return;

    for(int i = 1; i < cq; i++) {
        int cn = GetCompanionIndex(pchar, i);
        if (cn == -1) {
            continue;
        }

        if(sti(characters[cn].ship.type) == SHIP_NOTUSED) {
            ids[ids_num] = cn;
            ids_num++;
            continue;
        }

        ref rBaseShip = GetRealShip(sti(characters[cn].ship.type));
		if (!CheckAttribute(rBaseShip, attrName)) {
			trace("ОШИБКА: не найден атрибут сортировки по '" + attrName + "' у корабля '" + rBaseShip.Name + "'");
            return; // чтобы ничего не сломать
		}

        {
			// insert
            int j;
            for(j = 0; j < ids_num; j++) {
                bool insert = false;
                int shipTypeLhs = sti(characters[ids[j]].ship.type);
                if(shipTypeLhs == SHIP_NOTUSED) {
                    // no ship
                    insert = true;
                } else {
                    // check if greater or (equal+type is greater)
                    ref rBaseShipLhs = GetRealShip(shipTypeLhs);

                    int rhsVal = makeint(stf(rBaseShip.(attrName))*100.0);
                    int lhsVal = makeint(stf(rBaseShipLhs.(attrName))*100.0);

                    bool valueLess = lhsVal < rhsVal;
                    bool typeLess = sti(characters[ids[j]].ship.type) < sti(characters[cn].ship.type);
                    bool valueEqTypeLess = rhsVal == lhsVal && typeLess;

                    insert = valueLess || valueEqTypeLess;
                }
                if(insert) {
                    // shift
                    for(int k=ids_num; k>j; k--) {
                        ids[k] = ids[k-1];
                    }
                    break;
                }
            }
            ids[j] = cn;
            ids_num++;
		}
	}

    for(i = 0; i < ids_num; i++)
	{
        string id = "id"+(i+1);
	    pchar.Fellows.Companions.(id) = ids[i];
	}

    Event(EVENT_CHANGE_COMPANIONS,"");
    IDoExit(RC_INTERFACE_TO_SHIP);
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	//string sRow = "tr" + (iRow + 1);
//--> mod tablesort
	if (sControl == "TABLE_LIST")
	{
		if (!SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, sControl, 1 )) SortTable(sControl, iColumn);
		Table_UpdateWindow(sControl);
	}
//<-- mod tablesort
}
