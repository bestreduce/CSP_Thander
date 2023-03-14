/// BOAL меню предметов
#include "interface\character_all.h"

int nCurScrollOfficerNum;
int iEQUIP_SET = 0;
string sMapDescribe;//переменная для текста описания карты
bool bMapCross, isPassenger;
float fOffsetX, fOffsetY;
int iCurTab;

void InitInterface(string iniName)
{
	GetXYWindowOffset(&fOffsetX, &fOffsetY);
	InterfaceStack.SelectMenu_node = "LaunchItems"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleItems";
	xi_refCharacter = pchar;
	isPassenger = 0;
	FillCharactersScroll();
	FillPassengerScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("ShowMapDesc","ShowMapDesc",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);

	SetEventHandler("ExitOfficerMenu","ExitOfficerMenu",0);
	SetEventHandler("OfficerChange","OfficerChange",0);
	SetEventHandler("acceptaddofficer","AcceptAddOfficer",0);
	SetEventHandler("ExitRemoveOfficerMenu","ExitRemoveOfficerMenu",0);
	SetEventHandler("AcceptRemoveOfficer","AcceptRemoveOfficer",0);

	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("ExitMapWindow","ExitMapWindow",0);
	SetEventHandler("ExitItemFromCharacterWindow","ExitItemFromCharacterWindow",0);

	SetEventHandler("ShowItemFromCharacterWindow","ShowItemFromCharacterWindow",0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ShowBladeEquipInfo", "ShowBladeEquipInfo", 0);
	SetEventHandler("ShowGunEquipInfo", "ShowGunEquipInfo", 0);
	SetEventHandler("ShowSpyglassEquipInfo", "ShowSpyglassEquipInfo", 0);
	SetEventHandler("ShowCirassEquipInfo", "ShowCirassEquipInfo", 0);
	SetEventHandler("ShowBackPackEquipInfo", "ShowBackPackEquipInfo", 0);
	SetEventHandler("ShowTalismanEquipInfo", "ShowTalismanEquipInfo", 0);
	SetEventHandler("ShowBookEquipInfo", "ShowBookEquipInfo", 0);
	SetEventHandler("Show1EquipInfo", "Show1EquipInfo", 0);
	SetEventHandler("Show2EquipInfo", "Show2EquipInfo", 0);
	SetEventHandler("Show3EquipInfo", "Show3EquipInfo", 0);
	SetEventHandler("Show4EquipInfo", "Show4EquipInfo", 0);
	SetEventHandler("Show5EquipInfo", "Show5EquipInfo", 0);
	SetEventHandler("ClickShow1", "ClickShow1", 0);
	SetEventHandler("ClickShow2", "ClickShow2", 0);
	SetEventHandler("ClickShow3", "ClickShow3", 0);
	SetEventHandler("ClickShow4", "ClickShow4", 0);
	SetEventHandler("ClickShow5", "ClickShow5", 0);
	SetEventHandler("ClickBook", "ClickBook", 0);
	SetEventHandler("ClickTalisman", "ClickTalisman", 0);
	SetEventHandler("ClickBackPack", "ClickBackPack", 0);
	SetEventHandler("ClickMushket", "ClickMushket", 0);
	SetEventHandler("ClickCirass", "ClickCirass", 0);
	SetEventHandler("ClickSpyGlass", "ClickSpyGlass", 0);
	SetEventHandler("ClickGun", "ClickGun", 0);
	SetEventHandler("ClickSaber", "ClickSaber", 0);
	SetEventHandler("CheckButtonChange", "CheckButtonChange", 0);
	SetEventHandler("SaveSETName", "SaveSETName", 0);
	SetEventHandler("ShowEditBox", "ShowEditBox", 0);
	SetEventHandler("HideEditBox", "HideEditBox", 0);

	switch (xi_refCharacter.sex)
	{
		case "man": SetNewPicture("SETUP_BIG_PICTURE", "interfaces\sith\CharEquip_Man.tga");
		break;
		case "woman": SetNewPicture("SETUP_BIG_PICTURE", "interfaces\sith\CharEquip_Woman.tga");
		break;
		case "skeleton": SetNewPicture("SETUP_BIG_PICTURE", "interfaces\sith\CharEquip_Skeleton.tga");
		break;
	}

	XI_RegistryExitKey("IExit_F2");
	SetVariable();
	HideEditBox();
	SetNewGroupPicture("Weight_PIC", "ICONS_CHAR", "weight");
	SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");
	SetNodeUsing("EXCHANGE", false);
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	string PsgAttrName;
	int _curCharIdx;
	ref _refCurChar;
	aref pRef, pRef2;
	bool  ok;

	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;
	makearef(pRef,pchar.Fellows.Passengers);

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = GetFreePassengersQuantity(pchar);

	GameInterface.PASSENGERSLIST.NotUsed = 6;
	GameInterface.PASSENGERSLIST.ListSize = nListSizeFree + 2;

	GameInterface.PASSENGERSLIST.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("PASSENGERSLIST.ImagesGroup", pchar, 2); // passengers

	GameInterface.PASSENGERSLIST.BadTex1 = 0;
	GameInterface.PASSENGERSLIST.BadPic1 = "emptyface";

	int m = 0;
	for(i=0; i<nListSize; i++)
	{
		attributeName = "pic" + (m+1);
		PsgAttrName = "id"+(i+1);
		makearef(pRef2,GameInterface.PASSENGERSLIST.(attributeName));

		_curCharIdx = sti(pRef.(PsgAttrName));

		if (_curCharIdx!=-1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			if (!ok && GetRemovable(&characters[_curCharIdx]))
			{
				// совместители должностей -->
				howWork = 1;
				if (CheckCharacterPerk(&characters[_curCharIdx], "ByWorker"))
				{
					howWork = 2;
				}
				if (CheckCharacterPerk(&characters[_curCharIdx], "ByWorker2"))
				{
					howWork = 3;
				}
				ok = !CheckAttribute(&characters[_curCharIdx], "isfree") || sti(characters[_curCharIdx].isfree) < howWork;
				PsgAttrName = GetOfficerTypeByNum(nCurScrollNum);
				// совместители должностей <--
				if (ok && !CheckAttribute(&characters[_curCharIdx], PsgAttrName))
				{
					GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
					GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
					GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup","FACE128_"+Characters[_curCharIdx].FaceID);
					m++;
				}
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // не знаю зачем, но для совместимости с "было"
}

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CHARACTERS_SCROLL");
}

void OfficerChange()
{
	string attributeName = "pic" + (nCurScrollNum+1);

	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		xi_refCharacter = &characters[iCharacter];

		if (CheckAttribute(xi_refCharacter, "prisoned") && xi_refCharacter.prisoned == true) {;}
		else {if (GetRemovable(xi_refCharacter)) isPassenger = 0; else isPassenger = 1;}

		if (isOfficerInShip(xi_refCharacter, true) && xi_refCharacter.id != pchar.id)
		{
			XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
			XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", true);

			SetCurrentNode("REMOVE_CANCEL_OFFICER");
		}
	}
	else
	{
		//Boyer mod
		//if (nCurScrollNum <= 9 && nCurScrollNum != 0)
		if (nCurScrollNum <= 6 + MAX_NUM_FIGHTERS && nCurScrollNum != 0)
		{
			FillPassengerScroll();
			SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"PASSENGERSLIST",-1);
			SetCurrentNode("PASSENGERSLIST");
			ProcessFrame();
			SetOfficersSkills();

			XI_WindowShow("OFFICERS_WINDOW", true);
			XI_WindowDisable("OFFICERS_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", true);
		}
	}
}

void SetOfficersSkills()
{
	string sCharacter = "pic"+(sti(GameInterface.PASSENGERSLIST.current)+1);
	if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter))
	{
		if (checkAttribute(GameInterface, "PASSENGERSLIST."+sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
			SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
			SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
			SetFormatedText("OFFICER_NAME", GetFullName(otherchr));
			SetSelectable("ACCEPT_ADD_OFFICER", true);
		}
		else
		{
			Table_Clear("TABLE_SMALLSKILL", false, true, true);
			Table_Clear("TABLE_SMALLOTHER", false, true, true);
			SetFormatedText("OFFICER_NAME", "");
			SetSelectable("ACCEPT_ADD_OFFICER", false);
		}
	}
	else
	{
		Table_Clear("TABLE_SMALLSKILL", false, true, true);
		Table_Clear("TABLE_SMALLOTHER", false, true, true);
		SetFormatedText("OFFICER_NAME", "");
		SetSelectable("ACCEPT_ADD_OFFICER", false);
	}
}

void AcceptAddOfficer()
{
	int iCurrentNode = nCurScrollNum;
	bool bNeedFollow = false;
	bool bOk;

	string attributeName2 = "pic"+(nCurScrollOfficerNum+1);
	int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);
	sld = &characters[iChar];
	if(sld.id != "pet_crab" || (nCurScrollNum > 6))
	{
		if (checkAttribute(GameInterface, "PASSENGERSLIST."+attributeName2 + ".character"))
		{
			iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);

			if (!CheckAttribute(&characters[iChar], "isfree"))
			{
				characters[iChar].isfree = 1;
			}
			else
			{
				characters[iChar].isfree = sti(characters[iChar].isfree) + 1; // совместители
			}
			bOk = (Characters[iChar].location != pchar.location);  // ниже локация перебивается на ГГ
			switch (nCurScrollNum)
			{
				case 1:
					pchar.Fellows.Passengers.navigator = iChar;
				break;

				case 2:
					pchar.Fellows.Passengers.boatswain = iChar;
				break;

				case 3:
					pchar.Fellows.Passengers.cannoner = iChar;
				break;

				case 4:
					pchar.Fellows.Passengers.doctor = iChar;
				break;

				case 5:
					pchar.Fellows.Passengers.treasurer = iChar;
				break;

				case 6:
					pchar.Fellows.Passengers.carpenter = iChar;
				break;
				//default:
					SetOfficersIndex(pchar, -1, iChar);
					bNeedFollow = true;
				break;
			}
			attributeName2 = GetOfficerTypeByNum(nCurScrollNum);
			characters[iChar].(attributeName2) = true; // совместитель дожности
			//SetCharacterTask_FollowCharacter(&Characters[iChar], PChar);
			if (bNeedFollow) // только для офов
			{

				//if (Characters[iChar].location.group == "sit")
				//{// найм прямо в таверне
				//if (bOk && IsEntity(loadedLocation) && !CheckAttribute(loadedLocation, "DisableOfficers"))
				if (IsEntity(loadedLocation) && loadedLocation.type == "tavern")
				{   //  пусть всегда будут появляться
					PlaceCharacter(&Characters[iChar], "goto", "random_must_be_near");
				}
				LAi_tmpl_SetFollow(&Characters[iChar], GetMainCharacter(), -1.0);
			}
			FillCharactersScroll();
			GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
		}
	}
	ExitOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	ProcessFrame();
	SetVariable();
}

void ExitRemoveOfficerMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("CHARACTERS_SCROLL");
}

void AcceptRemoveOfficer()
{
	int iCurrentNode = nCurScrollNum;
	string attributeName2 = "pic"+(nCurScrollNum+1);

	int iChar = sti(GameInterface.CHARACTERS_SCROLL.(attributeName2).character);

	characters[iChar].isfree = sti(characters[iChar].isfree) - 1; // совместители
	if (sti(characters[iChar].isfree) <= 0)
	{
		DeleteAttribute(&characters[iChar], "isfree");
	}

	switch (nCurScrollNum)
	{
		case 1:
			pchar.Fellows.Passengers.navigator = -1;
		break;

		case 2:
			pchar.Fellows.Passengers.boatswain = -1;
		break;

		case 3:
			pchar.Fellows.Passengers.cannoner = -1;
		break;

		case 4:
			pchar.Fellows.Passengers.doctor = -1;
		break;

		case 5:
			pchar.Fellows.Passengers.treasurer = -1;
		break;

		case 6:
			pchar.Fellows.Passengers.carpenter = -1;
		break;
		//default:
			RemoveOfficersIndex(pchar, iChar);
		break;
	}
	attributeName2 = GetOfficerTypeByNum(nCurScrollNum);
	DeleteAttribute(&characters[iChar], attributeName2); // совместитель дожности

	FillCharactersScroll();
	GameInterface.CHARACTERS_SCROLL.current = iCurrentNode;
	ExitRemoveOfficerMenu();
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_SCROLL_CHANGE,"CHARACTERS_SCROLL",-1);
	SetVariable();
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	SaveEquipSet();
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("ShowMapDesc","ShowMapDesc");
	DelEventHandler("MouseRClickUp","HideInfoWindow");

	DelEventHandler("ExitOfficerMenu","ExitOfficerMenu");
	DelEventHandler("OfficerChange","OfficerChange");
	DelEventHandler("acceptaddofficer","AcceptAddOfficer");
	DelEventHandler("ExitRemoveOfficerMenu","ExitRemoveOfficerMenu");
	DelEventHandler("AcceptRemoveOfficer","AcceptRemoveOfficer");

	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("ExitMapWindow","ExitMapWindow");
	DelEventHandler("ExitItemFromCharacterWindow","ExitItemFromCharacterWindow");
	DelEventHandler("ShowItemFromCharacterWindow","ShowItemFromCharacterWindow");

	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");

	DelEventHandler("ShowBladeEquipInfo", "ShowBladeEquipInfo");
	DelEventHandler("ShowGunEquipInfo", "ShowGunEquipInfo");
	DelEventHandler("ShowSpyglassEquipInfo", "ShowSpyglassEquipInfo");
	DelEventHandler("ShowCirassEquipInfo", "ShowCirassEquipInfo");
	DelEventHandler("ShowBackPackEquipInfo", "ShowBackPackEquipInfo");
	DelEventHandler("ShowTalismanEquipInfo", "ShowTalismanEquipInfo");
	DelEventHandler("ShowBookEquipInfo", "ShowBookEquipInfo");
	DelEventHandler("Show1EquipInfo", "Show1EquipInfo");
	DelEventHandler("Show2EquipInfo", "Show2EquipInfo");
	DelEventHandler("Show3EquipInfo", "Show3EquipInfo");
	DelEventHandler("Show4EquipInfo", "Show4EquipInfo");
	DelEventHandler("Show5EquipInfo", "Show5EquipInfo");
	DelEventHandler("ClickShow1", "ClickShow1");
	DelEventHandler("ClickShow2", "ClickShow2");
	DelEventHandler("ClickShow3", "ClickShow3");
	DelEventHandler("ClickShow4", "ClickShow4");
	DelEventHandler("ClickShow5", "ClickShow5");
	DelEventHandler("ClickBook", "ClickBook");
	DelEventHandler("ClickTalisman", "ClickTalisman");
	DelEventHandler("ClickBackPack", "ClickBackPack");
	DelEventHandler("ClickMushket", "ClickMushket");
	DelEventHandler("ClickCirass", "ClickCirass");
	DelEventHandler("ClickSpyGlass", "ClickSpyGlass");
	DelEventHandler("ClickGun", "ClickGun");
	DelEventHandler("ClickSaber", "ClickSaber");
	DelEventHandler("CheckButtonChange", "CheckButtonChange");
	DelEventHandler("SaveSETName", "SaveSETName");
	DelEventHandler("ShowEditBox", "ShowEditBox");
	DelEventHandler("HideEditBox", "HideEditBox");

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
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	ref itm;
	switch(nodName)
	{
		case "EQUIP_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				EquipPress();
			}
		break;
		case "EXCHANGE":
			if (comName=="activate" || comName=="click")
			{
				PostEvent("OpenExchange", 150, "a", xi_refCharacter);
				ProcessExitCancel();
			}
		break;
		case "DISCARD_BTN":
			if (comName=="activate" || comName=="click")
			{
				DiscardTreasureMap();
			}
		break;

		case "I_CHARACTER_2":
			if(comName=="click")
			{
				nodName = "I_CHARACTER";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
				return;
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
				nodName = "I_SHIP";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
				nodName = "I_QUESTBOOK";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
				nodName = "I_TRADEBOOK";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
				nodName = "I_NATIONS";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
				nodName = "I_ITEMS";
				InterfaceStates.ReloadMenuExit = true;
				IDoExit(RC_INTERFACE_ANY_EXIT);
				PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			}
		break;
		case "QTY_ADD_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				ADD_BUTTON(GameInterface.(CurTable).(CurRow).id);
			}
		break;

		case "QTY_ADD_ALL_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				ADD_ALL_BUTTON(GameInterface.(CurTable).(CurRow).id);
			}
		break;

		case "QTY_REMOVE_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				REMOVE_BUTTON(GameInterface.(CurTable).(CurRow).id);
			}
		break;

		case "QTY_REMOVE_ALL_BUTTON":
			if(comName=="activate" || comName=="click")
			{
				REMOVE_ALL_BUTTON(GameInterface.(CurTable).(CurRow).id);
			}
		break;

		case "ITEM_FROM_CHARACTER_OK_BUTTON":
			RemoveItemsQuantity();
		break;
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
}

void ProcessFrame()
{
	if (GetCurrentNode() != "EDIT_BOX1") HideEditBox();

	if (sti(GameInterface.CHARACTERS_SCROLL.current)!=nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		SetButtonsState();
		return;
	}
	if (sti(GameInterface.PASSENGERSLIST.current)!= nCurScrollOfficerNum && GetCurrentNode() == "PASSENGERSLIST")
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
		return;
	}
}

void SetButtonsState()
{
	string attributeName = "pic" + (nCurScrollNum+1);
	if(GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		int iCharacter = sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character);
		SaveEquipSet();
		xi_refCharacter = &characters[iCharacter];

		if (CheckAttribute(xi_refCharacter, "prisoned") && xi_refCharacter.prisoned == true) {;}
		else {if (GetRemovable(xi_refCharacter)) isPassenger = 0; else isPassenger = 1;}

		switch (xi_refCharacter.sex)
		{
			case "man": SetNewPicture("SETUP_BIG_PICTURE", "interfaces\sith\CharEquip_Man.tga");
			break;
			case "woman": SetNewPicture("SETUP_BIG_PICTURE", "interfaces\sith\CharEquip_Woman.tga");
			break;
			case "skeleton": SetNewPicture("SETUP_BIG_PICTURE", "interfaces\sith\CharEquip_Skeleton.tga");
			break;
		}
		SetVariable();
	}
	else
	{
		if (xi_refCharacter.id != pchar.id)
		{
			xi_refCharacter = pchar;
			isPassenger = 0;
			SetVariable();
		}
	}
}

void SetVariable()
{
	if (xi_refCharacter.index != nMainCharacterIndex)
	{
		if (CheckForExchangeAllowed(xi_refCharacter)) SetNodeUsing("EXCHANGE", true);
		else SetNodeUsing("EXCHANGE", false);
	}
	else SetNodeUsing("EXCHANGE", false);

	SetFormatedText("SETUP_FRAME_CAPTION", XI_ConvertString("Equipment") + ": " + GetFullName(xi_refCharacter));
	SetControlsTabMode(1);
	for (int i=1;i<7;i++) {FillSetName(i);}//Заполняем имена комплектов снаряжения
	HideItemInfo();
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(xi_refCharacter.Money), MONEY_SIGN,MONEY_DELIVER));

	if (!checkattribute(xi_refCharacter, "selectedSet")) xi_refCharacter.selectedSet = 1;//первое открытие

	if (iEQUIP_SET == sti(xi_refCharacter.selectedSet)) ReEquipCharacter();//обновляем экипировку при открытии инвентаря - могло добавиться недостающее пока бегали где-то
	else
		{
		iEQUIP_SET = sti(xi_refCharacter.selectedSet);
		CheckButton_SetState("CHECK_EQUIP_SET", iEQUIP_SET, true);//тут тоже будет ReEquipCharacter()
		}
	SetNodeUsing("EQUIP_BUTTON" , true);
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
}

void FillItemsTable(int _mode) // 1 - все 2 - оружие 3 - остальное
{
	int n, i, iTemp;
	string row, sGood, sItem;
	int  idLngFile;
	bool ok, ok2 = true;
	aref rootItems, arItem;
	ref rItem;

	GameInterface.TABLE_ITEMS.hr.td1.str = "Наименование предметов";
	GameInterface.TABLE_ITEMS.hr.td1.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td2.str = "Вес шт.";
	GameInterface.TABLE_ITEMS.hr.td2.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td3.str = "Кол-во";
	GameInterface.TABLE_ITEMS.hr.td3.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td4.str = "Вес";
	GameInterface.TABLE_ITEMS.hr.td4.scale = 0.8;
	GameInterface.TABLE_ITEMS.select = 0;
	GameInterface.TABLE_ITEMS.top = 0;
	idLngFile = LanguageOpenFile("ItemsDescribe.txt");
	Table_Clear("TABLE_ITEMS", false, true, false);

	object allItems;

    makearef(rootItems, xi_refCharacter.equip); // экипировка
    n = GetAttributesNum(rootItems);
    for(i = 0; i < n; i++)
    {
        arItem = GetAttributeN(rootItems, i);
        sItem = GetAttributeValue(arItem);
        if (sItem == "") continue; //патенты клинит
		iTemp = FindItem(sItem);
		if (iTemp < 0) continue;
		sGood = "00" + DigitsToString(iTemp, 4) + sItem;
		allItems.(sGood) = sItem;
    }

	makearef(rootItems, xi_refCharacter.Items);
	n = GetAttributesNum(rootItems);
	for (i = 0; i < n; i++)
	{
		arItem = GetAttributeN(rootItems, i);
		sItem = GetAttributeName(arItem);
		if (IsEquipCharacterByItem(xi_refCharacter, sItem)) continue;
		iTemp = FindItem(sItem);
		if (iTemp < 0) continue;
		sGood = DigitsToString(iTemp, 4) + sItem;

		if (CheckAttribute(Items[iTemp], "SortIndex"))
		{
			sGood = DigitsToString(sti(Items[iTemp].SortIndex) + 1, 2) + sGood;
		}
		else
		{
			sGood = "99" + sGood;
		}
		allItems.(sGood) = sItem;
	}

	makearef(rootItems, allItems);
	sort(rootItems);

	n = 1;
	for (i = 0; i < GetAttributesNum(rootItems); i++)
	{
		arItem = GetAttributeN(rootItems, i);
		sGood = GetAttributeValue(arItem);
		rItem = ItemsFromID(sGood);

		row = "tr" + n;
		ok = rItem.ItemType == "WEAPON" || rItem.ItemType == "SUPPORT";
		if (CheckAttribute(rItem,"kind")) ok = true;
		if (CheckAttribute(rItem,"mapSpecial"))
		{
			ok2 = false;
		}
		else
		{
			ok2 = true;
		}
		if (_mode == 1 && rItem.ItemType == "MAP" && ok2) continue;
		if (_mode == 2 && !ok && ok2) continue;
		ok = ok || rItem.ItemType == "MAP";
		if (_mode == 3 && ok && ok2) continue;
		if (_mode == 4 && rItem.ItemType != "MAP" && rItem.id != "MapsAtlas") continue;

		GameInterface.TABLE_ITEMS.(row).id = sGood;

		GameInterface.TABLE_ITEMS.(row).td1.icon.group = rItem.picTexture;
		GameInterface.TABLE_ITEMS.(row).td1.icon.image = "itm" + rItem.picIndex;
		GameInterface.TABLE_ITEMS.(row).td1.icon.offset = "-2, 0";
		GameInterface.TABLE_ITEMS.(row).td1.icon.width = 32;
		GameInterface.TABLE_ITEMS.(row).td1.icon.height = 32;
		GameInterface.TABLE_ITEMS.(row).td1.textoffset = "31,0";
		GameInterface.TABLE_ITEMS.(row).td1.str = LanguageConvertString(idLngFile, rItem.name);

		iTemp = CheckItemInSets(xi_refCharacter, sGood);
		if (iTemp > 0)
		{
			GameInterface.TABLE_ITEMS.(row).td1.str = GameInterface.TABLE_ITEMS.(row).td1.str + " (К" + iTemp + ")";
			GameInterface.TABLE_ITEMS.(row).td1.color = argb(255,196,196,255);//подцвечиваем предметы из комплектов
		}
		if (IsEquipCharacterByItem(xi_refCharacter, sGood)) GameInterface.TABLE_ITEMS.(row).td1.color = argb(255,196,196,255);//на этом интерфейсе надо подцвечивать и текущий комплект???

		GameInterface.TABLE_ITEMS.(row).td1.scale = 0.85;
		GameInterface.TABLE_ITEMS.(row).td2.str   = FloatToString(GetItemWeight(sGood), 1);
		GameInterface.TABLE_ITEMS.(row).td2.scale = 0.9;
		GameInterface.TABLE_ITEMS.(row).td3.str   = GetCharacterItem(xi_refCharacter, sGood);
		GameInterface.TABLE_ITEMS.(row).td3.scale = 0.9;
		GameInterface.TABLE_ITEMS.(row).td4.str   = FloatToString(GetItemWeight(sGood) * sti(GameInterface.TABLE_ITEMS.(row).td3.str), 1);
		GameInterface.TABLE_ITEMS.(row).td4.scale = 0.9;
		n++;
	}

	Table_UpdateWindow("TABLE_ITEMS");
	LanguageCloseFile(idLngFile);
	if (_mode == 1)
	{
		FillItemsSelected();
	}
}

void FillItemsSelected()
{
	int	i;
	string sGood;
	int iLastGunItem;
	ref item, rLastGunItem;

	// Скроем по умолчанию
	SetNodeUsing("ITEM_1", false);
	SetNodeUsing("ITEM_2", false);
	SetNodeUsing("ITEM_3", false);
	SetNodeUsing("ITEM_4", false);
	SetNodeUsing("ITEM_5", false);
	SetNodeUsing("ITEM_6", false);
	SetNodeUsing("ITEM_7", false);
	SetNodeUsing("ITEM_8", false);
	SetNodeUsing("ITEM_9", false);
	SetNodeUsing("ITEM_10", false);
	SetNodeUsing("ITEM_11", false);
	SetNodeUsing("ITEM_12", false);
	SetNodeUsing("ITEM_13", false);
	SetNodeUsing("ITEM_14", false);

	aref arEquip;
	makearef(arEquip, xi_refCharacter.equip);
	int q = GetAttributesNum(arEquip);
	for(i = 0; i < q; i++)
	{
		sGood = GetAttributeValue(GetAttributeN(arEquip, i));
		if (sGood == "") continue;

		item = ItemsFromID(sGood);

		switch (item.groupID)
		{
			case BLADE_ITEM_TYPE:
				SetNewGroupPicture("ITEM_1", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_1" , true);
			break;
			case GUN_ITEM_TYPE:
				if (CheckAttribute(xi_refCharacter,"chr_ai.bullet"))
				{
					ref itms = ItemsFromID(xi_refCharacter.chr_ai.bullet);
					SetNodeUsing("ITEM_14" , true);
					SetNewGroupPicture("ITEM_14", itms.picTexture, "itm" + itms.picIndex);
				}
				if(CheckAttribute(xi_refCharacter, "IsMushketer"))
				{
					iLastGunItem = GetItemIndex(xi_refCharacter.IsMushketer.LastGunID);
					// Покажем картинку старого пистоля, если он ещё есть
					if(iLastGunItem != -1 && GetCharacterItem(xi_refCharacter, xi_refCharacter.IsMushketer.LastGunID) > 0)
					{
						rLastGunItem = &Items[iLastGunItem];
						SetNewGroupPicture("ITEM_2", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
						SetNodeUsing("ITEM_2" , true);
					}

					rLastGunItem = &Items[GetItemIndex(xi_refCharacter.IsMushketer.MushketID)];
					SetNodeUsing("ITEM_5", true);
					SetNewGroupPicture("ITEM_5", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
				}
				else
				{
					SetNewGroupPicture("ITEM_2", item.picTexture, "itm" + item.picIndex);
					SetNodeUsing("ITEM_2" , true);
					SetNodeUsing("ITEM_5" , false); // Мушкет не юзается - уберем картинку
				}
			break;
			case SPYGLASS_ITEM_TYPE:
				SetNewGroupPicture("ITEM_3", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_3" , true);
			break;
			case CIRASS_ITEM_TYPE:
				SetNewGroupPicture("ITEM_4", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_4" , true);
			break;
			case BACKPACK_ITEM_TYPE:
				SetNewGroupPicture("ITEM_6", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_6" , true);
			break;
			case TALISMAN_ITEM_TYPE:
				SetNewGroupPicture("ITEM_7", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_7" , true);
			break;
			case INDIAN_CENTER_ITEM_TYPE:
				SetNewGroupPicture("ITEM_8", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_8" , true);
			break;
			case BOOK_ITEM_TYPE:
				SetNewGroupPicture("ITEM_9", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_9" , true);
			break;
			case JEWELRY_INDIAN_LEFT_ITEM_TYPE:
				SetNewGroupPicture("ITEM_10", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_10" , true);
			break;
			case JEWELRY_INDIAN_RIGHT_ITEM_TYPE:
				SetNewGroupPicture("ITEM_11", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_11" , true);
			break;
			case IDOLS_LEFT_ITEM_TYPE:
				SetNewGroupPicture("ITEM_12", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_12" , true);
			break;
			case IDOLS_RIGHT_ITEM_TYPE:
				SetNewGroupPicture("ITEM_13", item.picTexture, "itm" + item.picIndex);
				SetNodeUsing("ITEM_13" , true);
			break;
		}
	}
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter));
}

//espkk. Returns attack coefficient by weapon. Writes perk multiplier in kPerk
float _GetAttackFactor(string sBladeID, ref rBlade, string sType, ref kPerk)
{
	float min, max, weight;
	GetBladeParams(sBladeID, &min, &max, &weight);

	kPerk = 1;
	float kAttackDmg = 1.0;

	float HeavyW = 1.0;//модификатор урона для тяжа
	float fgtlevel = 0.0;
	fgtlevel = GetCharacterSkill(xi_refCharacter, rBlade.FencingType); //определение скила по типу меча
	fgtlevel = fgtlevel/SKILL_MAX;//вычисление флоата

	//float bladeDmg = min + (max - min)*frandSmall(LAi_GetCharacterFightLevel(pchar));
	float bladeDmg = min + (max - min)*fgtlevel;

	switch(sType)
	{
		case "fast":
		kAttackDmg = 0.7;
		if (bAltBalanceProHits && rBlade.FencingType != "Fencing") kAttackDmg *= 0.7;
		break;

		case "force":
		kAttackDmg = 1.0;
		if (bAltBalanceProHits && rBlade.FencingType != "FencingLight") kAttackDmg *= 0.7;
		break;

		case "round":
		kAttackDmg = 0.6;
		if(CheckCharacterPerk(xi_refCharacter, "BladeDancer"))
		{
			kAttackDmg = kAttackDmg * 1.3;
		}
		if (bAltBalanceProHits && rBlade.FencingType != "Fencing") kAttackDmg *= 0.7;
		break;

		case "break":
		kAttackDmg = 3.0;
		if (bAltBalanceProHits && rBlade.FencingType != "FencingHeavy") kAttackDmg *= 0.7;
		//if (!CheckCharacterPerk(xi_refCharacter, "HardHitter")) kAttackDmg /= 2.0;
		break;

		case "fient":
		kAttackDmg = 0.5;
		if(CheckCharacterPerk(xi_refCharacter, "Agent")) kAttackDmg = kAttackDmg * 2;
		if (bAltBalanceProHits && rBlade.FencingType != "FencingLight") kAttackDmg *= 0.7;
		break;
	}
	float dmg = bladeDmg * kAttackDmg;

	return dmg;
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sPicture;
	string sGroup, sGroupPicture;
	int iText2Color = 0;

	//Boyer fix #20170401-01 Can't load texture -1.tx log errors
	//sPicture = "-1";
	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		/*case "CHARACTER_NATION_PICTURE":
			sHeader = XI_ConvertString("Nation");
			sText1 = GetRPGText("Nation_hint");
		break;   */
	}
	sHeader = "Предметы";
	sText1  = "Здесь Вы можете получить информацию об имеющихся предметах, изучить инвентарь или изменить экипировку главного героя. "+
			  "Так же можно посмотреть состояние инвентаря офицеров, компаньонов и пассажиров. Выбор оружия они делают сами при экипировке их новым снаряжением. "+
			  "Обмен предметами со своими офицерами осуществляется на суше через команду 'Обмен'.";

	if (sCurrentNode == "TABLE_ITEMS")
	{
		string sItemID = GameInterface.(CurTable).(CurRow).id;
		ref rBlade = ItemsFromID(sItemID);
		if (ThisItemCanBeEquip(sItemID))
		{
			if(rBlade.groupID == BLADE_ITEM_TYPE)
			{
				sHeader = "Урон клинка"
				sText1 = "";

				iText2Color = argb(255,120-30*(sti(rBlade.quality)+1),150,17);

				int ControlsLngFile = LanguageOpenFile("ControlsNames.txt");
				float aSkill = LAi_GetCharacterFightLevel(pchar);
				float kAttackDmg, kPerk;

				string sAttackTypes[5];
				sAttackTypes[0] = "fast";
				sAttackTypes[1] = "force";
				sAttackTypes[2] = "break";
				sAttackTypes[3] = "round";
				sAttackTypes[4] = "fient"; //feint = fient in lang file

				for (int index = 0; index < 5; index++)
				{
					kAttackDmg = _GetAttackFactor(sItemID, rBlade, sAttackTypes[index], &kPerk);

					sText2 += LanguageConvertString(ControlsLngFile, "ChrAttack" + sAttackTypes[index]) + " ";
					sText2 += MakeInt(kAttackDmg);

					sText2 += "\n\n";
				}

				sGroup = rBlade.picTexture;
				sGroupPicture = "itm" + rBlade.picIndex;

				LanguageCloseFile(ControlsLngFile);
			}
		}
	}

	if (sCurrentNode == "CHECK_EQUIP_SET")
	{
		sHeader = "Выбор комплекта снаряжения";
		sText1  = "Здесь Вы можете одним нажатием ЛКМ сменить комплект снаряжения. Сохранение изменений комплектов снаряжения происходит при выходе из интефейса предметов или при смене комплекта на другой.\nСменить НАЗВАНИЕ комплекта можно двойным ЛКМ по чекбоксу.";
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, iText2Color, "", 0, "", 0, "-1", sGroup, sGroupPicture, 64, 64);
}
void HideInfoWindow()
{
	CloseTooltip();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	CurTable = sControl;
	CurRow   =  "tr" + (iSelected);
	// отрисовка инфы
	SetItemInfo();
}

void SetItemInfo()
{
	string sItemID = GameInterface.(CurTable).(CurRow).id;
	if (sItemID == "letter_LSC" && CheckAttribute(pchar, "questTemp.LSC.poorName"))
	{
        AddQuestRecord("ISS_PoorsMurder", "11");
        AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ся","ась"));
        AddQuestUserData("ISS_PoorsMurder", "sName", pchar.questTemp.LSC.poorName);
        pchar.questTemp.LSC = "readyGoLSC";
        DeleteAttribute(pchar, "questTemp.LSC.poorName");
        int n = FindIsland("LostShipsCity");
        Islands[n].visible = true;
        Islands[n].reload_enable = true;
        Islands[n].alwaysStorm = true; //живём в штормах
        Islands[n].MaxSeaHeight = 2.0;
        Islands[n].storm = true;
        Islands[n].tornado = true;
	}
	ref item = ItemsFromID(sItemID);
	SetFormatedText("INFO_TEXT", GetItemDescribe(sItemID));
	SetNewGroupPicture("INFO_PIC", item.picTexture, "itm" + item.picIndex);
	SetNodeUsing("INFO_TEXT", true);
	SetNodeUsing("INFO_PIC", true);
	SetVAligmentFormatedText("INFO_TEXT");

	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(sItemID));
}

void HideItemInfo()
{
	SetNodeUsing("INFO_TEXT", false);
	SetNodeUsing("INFO_PIC", false);
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",false);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_ITEMS");
	HideItemInfo();
	if( sNodName == "TABBTN_1" )
	{
		SetControlsTabMode( 1 );
		return;
	}
	if( sNodName == "TABBTN_2" )
	{
		SetControlsTabMode( 2 );
		return;
	}
	if( sNodName == "TABBTN_3" )
	{
		SetControlsTabMode( 3 );
		return;
	}
	if( sNodName == "TABBTN_4" )
	{
		SetControlsTabMode( 4 );
		return;
	}
}

void SetControlsTabMode(int nMode)
{
	iCurTab = nMode;
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch (nMode)
	{
		case 1: //
			sPic1 = "TabDeSelected";
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabDeSelected";
			nColor2 = argb(255,255,255,255);
		break;
		case 3:
			sPic3 = "TabDeSelected";
			nColor3 = argb(255,255,255,255);
		break;
		case 4:
			sPic4 = "TabDeSelected";
			nColor4 = argb(255,255,255,255);
		break;
	}

	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS", sPic4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_3", 8,0,nColor3);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_4", 8,0,nColor4);
	FillControlsList(nMode);
}

void FillControlsList(int nMode)
{
	if ((nMode >= 1) && (nMode <= 4))
	{
		FillItemsTable(nMode);
	}
}

bool ThisItemCanBeEquip(string sItemID)
{
	ref rItem = ItemsFromID(sItemID);
	if (CheckAttribute(xi_refCharacter,"nonremovable")) return false;
	if (HasSubStr(loadedLocation.id,"FencingTown")) return false;
	if (rItem.id == "suit_2" && pchar.questTemp.AnjelikaTichPrologue5 == "ATP5")	//Пролог Анжелика Тич, не даём снять юбку
    {
        SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
        return false;
    }
	if (HasSubStr(sItemId,"Tube"))
	{
		return true;
	}
	if (HasSubStr(sItemId,"Strange"))
	{
		if (!CheckAttribute(xi_refCharacter, "StrangeMushrooms")) xi_refCharacter.StrangeMushrooms = 0;
		if (!CheckAttribute(xi_refCharacter, "StrangePotion")) xi_refCharacter.StrangePotion = 0;

		if (sItemID ==  "StrangeMushrooms" && sti(xi_refCharacter.StrangeMushrooms) < 5) return true;
		else {if (sItemID ==  "StrangePotion" && sti(xi_refCharacter.StrangePotion) < 5) return true;}
		else {if (sItemID ==  "StrangeElixir" && !CheckAttribute(xi_refCharacter, "StrangeElixir")) return true;}
	}
	if( !CheckAttribute(rItem,"groupID") )
	{
		return false;
	}
	string sGroupID = rItem.groupID;
	if (sGroupID == AMMO_ITEM_TYPE)
	{
		if (sItemID == "GunPowder" || sItemID == "shotgun_cartridge" || sItemID == "GunCap_colt" || sItemID == "12_gauge") return false;
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}
	if( !IsCanEquiping(xi_refCharacter, sGroupID) )
	{
		return false;
	}
	if(sItemID == "MapsAtlas")
	{
		return true;
	}

	if (sGroupID == BOOK_ITEM_TYPE)
	{
		string sId = rItem.id;
		if (!CheckAttribute(xi_refCharacter, "books." + sId))
		{
			return true;
		}
		return sti(xi_refCharacter.books.(sId)) > 0;
	}

	if (sGroupID == BLADE_ITEM_TYPE && CheckAttribute(xi_refCharacter, "DontChangeBlade")) return false;
	if (sGroupID == GUN_ITEM_TYPE && CheckAttribute(xi_refCharacter, "DontChangeGun")) return false;

	if (sGroupID == GUN_ITEM_TYPE)
	{
		if (!IsMainCharacter(xi_refCharacter) && !CheckAttribute(xi_refCharacter, "CanTakeMushket") && HasSubStr(sItemID, "mushket"))
		{
			return false;
		}
		if (!CheckAttribute(rItem,"chargeQ") )
		{
			return false;
		}
		if(sItemID == "mushket2x2") return false; // Мушкет квестового офа
		if(HasSubStr(sItemID, "mushket") && !HasSubStr(sItemID, "mushket_drob"))
		{
			if (!IsCharacterPerkOn(xi_refCharacter,"Gunman") && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional")) return false;
		}

		if (CheckAttribute(rItem,"ReqPerk"))
		{
			if (rItem.ReqPerk == "Gunman" && !IsCharacterPerkOn(xi_refCharacter,"Gunman") && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional")) return false;
			if (rItem.ReqPerk == "GunProfessional" && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional")) return false;
		}

		/*if(sItemID == "mushket_Shtuzer" && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional"))
		{
			return false;
		}
		if(sItemID == "mushket2" && !IsCharacterPerkOn(xi_refCharacter,"GunProfessional"))
		{
			return false;
		}*/

		// Нельзя экипировать мушкет в непредназначенных для этого локациях (Таверна)
		/*if(HasSubStr(sItemID, "mushket") && !CanEquipMushketOnLocation(xi_refCharacter.Location))
		{
			return false;
		}*/ //мушкеты в тавернах - Gregg

		if (HasSubStr(sItemID, "mushket") && IsMainCharacter(xi_refCharacter) && !IsPCharHaveMushketerModel())
		{
			return false;
		}
	}
	if (IsEquipCharacterByItem(xi_refCharacter, sItemID))
	{
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
		//aw013	if(sGroupID==BLADE_ITEM_TYPE || sGroupID==SPYGLASS_ITEM_TYPE || sGroupID==PATENT_ITEM_TYPE)
		if(sGroupID==PATENT_ITEM_TYPE)	//aw013
		{
			if (CheckAttribute(pchar,"questTemp.Ascold"))
			{
				if (pchar.questTemp.Ascold == "ReciveInformationManowar" || pchar.questTemp.Ascold == "Ascold_ImMummy")	return true;
			}
			return false;
		}
	}
	else
	{
		if (sGroupID == CIRASS_ITEM_TYPE && !IsCharacterPerkOn(xi_refCharacter,"Ciras") && rItem.Clothes == false)
		{
			return false;
		}

		if (HasSubStr(sItemID, "chest")) SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#Взломать");
		else SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
		if (sItemID == "Chest") {SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that")); return false;}
	}
	if (IsMainCharacter(xi_refCharacter) || CheckAttribute(xi_refCharacter, "CanTakeMushket"))
	{
		if(CheckAttribute(xi_refCharacter, "IsMushketer"))
		{
			if (xi_refCharacter.id == "OffMushketer" || xi_refCharacter.id == "OfMush1" || xi_refCharacter.id == "OfMush2")
			{
				if(HasSubStr(sItemID, "mushket") && !HasSubStr(sItemID, "mushket2x2") && sItemID != xi_refCharacter.IsMushketer.MushketID)
				{
					SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
					return true;
				}
				if(sGroupID == BLADE_ITEM_TYPE || sGroupID == SPYGLASS_ITEM_TYPE || sGroupID == GUN_ITEM_TYPE)
				{
					return false;
				}
			}
			else
			{
				if(sItemID == xi_refCharacter.IsMushketer.MushketID)
				{
					SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
					return true;
				}
				if(sGroupID == BLADE_ITEM_TYPE || sGroupID == SPYGLASS_ITEM_TYPE || sGroupID == GUN_ITEM_TYPE || sGroupID == CIRASS_ITEM_TYPE)
				{
					return false;
				}
			}
		}
	}
	if (sGroupID == CIRASS_ITEM_TYPE && xi_refCharacter.model == "Protocusto") return false;
	return true;
}

void EquipPress()
{
	string sItemID = GameInterface.(CurTable).(CurRow).id;
	ref itmRef = ItemsFromID(sItemID);
	string totalInfo;
	int  i;

	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;

		if (itmGroup == BLADE_ITEM_TYPE && CheckAttribute(xi_refCharacter, "DontChangeBlade")) return false;
		if (itmGroup == GUN_ITEM_TYPE && CheckAttribute(xi_refCharacter, "DontChangeGun")) return false;

		if (itmGroup == MAPS_ITEM_TYPE)
		{
			SetSelectable("DISCARD_BTN",false);
			// Warship. Отличная карта, у нее отдельный интерфейс
			if(sItemID == "Map_Best")
			{
				PChar.ShowBestMap = true; // Флаг, что смотрим из интерфейса придметов
				IDoExit(RC_INTERFACE_BEST_MAP);
				return;
			}
			// Ugeen --> интерфейс атласа карт
			if(sItemID == "MapsAtlas") // взяли атлас карт
			{
				PChar.ShowMapsAtlas = true; // Флаг, что смотрим из интерфейса предметов
				IDoExit(RC_INTERFACE_MAPVIEW);
				return;
			}
			// Ugeen --> специальная квестовая карта
			if(sItemID == "mapQuest")
			{
				totalInfo = GenQuest_GetQuestTreasureMapDescription(itmRef);
				SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map.tga");
				SetFormatedText("MAP_TEXT", totalInfo);
				SetVAligmentFormatedText("MAP_TEXT");
				ShowMapWindow();
				return;
			}
			//pchar.I_MAP_SHOW = true;
			//pchar.I_MAP_SHOW_ITEM = sItemID;
			//PostEvent("InterfaceBreak", 400);
			if (sItemID == "map_full" || sItemID == "map_part1" || sItemID == "map_part2")
			{// клады
				SetSelectable("DISCARD_BTN",true);
				SetNewPicture("MAP_PICTURE", "interfaces\Maps\map_1.tga");
				if (GetCharacterItem(pchar, "map_part1")>0  && GetCharacterItem(pchar, "map_part2")>0 && GetCharacterItem(pchar, "map_full")<=0)
				{
					TakeNItems(xi_refCharacter, "map_part1", -1);
					TakeNItems(xi_refCharacter, "map_part2", -1);
					TakeNItems(pchar, "map_full",   1);
					itmRef = ItemsFromID("map_full");
					// здесь генерация назначение и типа клада
					pchar.GenQuest.TreasureBuild = true;
					FillMapForTreasure(itmRef);
					SetVariable();
				}
				// тут применяем логику двух кусков, из них одна карта <--
				if (itmRef.mapType == "Full")
				{
					if (sti(itmRef.MapTypeIdx) == -1)
					{
						SetFormatedText("MAP_TEXT", GetConvertStr("type_fake", "MapDescribe.txt"));
						DeleteAttribute(itmRef, "MapIslId");
						TakeNItems(GetMainCharacter(), "map_full", -1);
					}
					else
					{
						if (!CheckAttribute(itmRef, "MapIslId"))
						{
							FillMapForTreasure(itmRef); //заполним если смотрим карту из сундука
						}
						//totalInfo = GetConvertStr(itmRef.MapIslId, "LocLables.txt");
						i = FindLocation(itmRef.MapLocId);  // ищем ареал
						if (i != -1 && locations[i].islandId != "Mein")
						{
							totalInfo = GetConvertStr(locations[i].islandId, "LocLables.txt");
							totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_isl", "MapDescribe.txt") + " " + totalInfo;
						}
						else
						{
							totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_mein", "MapDescribe.txt");
						}
						itmRef.MapIslName = totalInfo;
						totalInfo = GetConvertStr(itmRef.MapLocId, "MapDescribe.txt") + ", " + GetConvertStr(itmRef.MapLocId + "_" + itmRef.MapBoxId, "MapDescribe.txt");
						itmRef.MaplocName = totalInfo;

						totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx, "MapDescribe.txt");

						if (CheckAttribute(itmRef,"uniquep"))
						{
							string pirname = GetUniquePirateNameString(itmRef.uniquep);
							totalInfo = "Это #sMapIslName#. На карте указано место спрятанного клада - это #sMaplocName#.\nСудя по всему - это подлинная карта сокровищ легендарного пирата "+pirname+"."
						}

						totalInfo = GetAssembledString(totalInfo, itmRef);
						sMapDescribe = totalinfo;//в глобальную переменную, чтобы можно было в другой функции показывать/скрывать текст
						SetMapCross(itmRef.MapLocId);
					}
				}
				else
				{
		   			SetFormatedText("MAP_TEXT", GetConvertStr("type_part", "MapDescribe.txt"));
				}
				SetVAligmentFormatedText("MAP_TEXT");
			}
			else
			{
				SetNewPicture("MAP_PICTURE", "interfaces\Maps\" + itmRef.imageTga + ".tga");
				SetFormatedText("MAP_TEXT", "");
			}
			ShowMapWindow();
		}
		else
		{
			if (itmGroup == SPECIAL_ITEM_TYPE) // Jason, спецпредметы
			{
				if (sItemID == "RingCapBook") // СЖ пинаса 'Санта-Люсия' и дневник Колхауна
				{
					RemoveItems(pchar, sItemID, 1);
					AddTimeToCurrent(0,20);
					SetLaunchFrameFormParam("Прошло 20 минут, вы прочитали журнал капитана", "", 0.1, 5.0);
					LAi_Fade("","LaunchFrameForm");
					RefreshLandTime();
					AddQuestRecord("RingCapBook", "1");
					pchar.questTemp.LSC.Ring.ReadCapBook = "true";
				}

				if(HasSubStr(sItemID, "chest") && sItemID != "Chest" && xi_refCharacter.id == pchar.id)
				{
					if(CheckCharacterItem(xi_refCharacter, "Lockpick"))
					{
						pchar.questTemp.lockpicking.ID = sItemID;
						IDoExit(RC_INTERFACE_LOCKPICK);
						return;
					}
					else
					{
						Log_Info("Для взлома нужна отмычка.");
						PlaySound("interface\knock.wav");
					}
				}
			}
			else
			{
				bool bCanmakeMushketer = (IsMainCharacter(xi_refCharacter)) || (CheckAttribute(xi_refCharacter, "CanTakeMushket"))
				if(HasSubStr(sItemID, "Mushket") && bCanmakeMushketer)
				{
					if (IsMainCharacter(xi_refCharacter)) // ГГ
					{
						if(!CheckAttribute(PChar, "IsMushketer")) // Не мушкетер. Делаем мушкетером
						{
							pchar.mushket = sItemID;
							SetMainCharacterToMushketer(sItemID, true);
						}
						else // Мушкетер. Делаем обычным фехтовальщиком
						{
							SetMainCharacterToMushketer("", false);
						}
					}
					else
					{
						if (xi_refCharacter.id == "OffMushketer" || xi_refCharacter.id == "OfMush1" || xi_refCharacter.id == "OfMush2")
						{
							string sLastGun = GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE);
							xi_refCharacter.IsMushketer.MushketID = sItemID; // Запомним, какой мушкет надели
							EquipCharacterByItem(xi_refCharacter, sItemID); // Экипируем мушкет
						}
						else
						{
							if(!CheckAttribute(xi_refCharacter, "IsMushketer")) // Не мушкетер. Делаем мушкетером
							{
								SetOfficerToMushketer(xi_refCharacter, sItemID, true);
							}
							else // Мушкетер. Делаем обычным фехтовальщиком
							{
								SetOfficerToMushketer(xi_refCharacter, sItemID, false);
							}
						}

					}
				}
				else
				{
					if(IsEquipCharacterByItem(xi_refCharacter, sItemID))
					{
						RemoveCharacterEquip(xi_refCharacter, itmGroup);
						if (CheckAttribute(itmRef, "HeadAccessory")) SetNewModelToChar(xi_refCharacter);
					}
					else
					{
						EquipCharacterByItem(xi_refCharacter, sItemID);
					}
					else
					{
						if (itmGroup == AMMO_ITEM_TYPE)
						{
							string sGun = GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE);
							if (sItemID == "bullet" || sItemID == "cartridge")
							{
								if (sGun == "pistol3" || sGun == "howdah" || sGun == "pistol8" || sGun == "pistol_grapebok" || sGun == "mushket6" || sGun == "grape_mushket")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							if (sItemID == "grapeshot")
							{
								if (sGun != "pistol3" && sGun != "howdah" && sGun != "pistol8" && sGun != "pistol_grapebok" && sGun != "mushket6" && sGun != "mushket_drob" && sGun != "pistol7shotgun")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							if (sItemID == "GunEchin")
							{
								if (sGun != "howdah" && sGun != "pistol8" && sGun != "mushket6")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							if (sItemID == "harpoon")
							{
								if (sGun != "pistol8")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							if (sItemID == "powder_pellet" || sItemID == "grenade")
							{
								if (sGun != "grape_mushket")
								{
									PlaySound("interface\knock.wav");
									return;
								}
							}
							LAi_SetCharacterUseBullet(xi_refCharacter, sItemID);
							LAi_GunSetUnload(xi_refCharacter);
							log_info("Выбран боеприпас - "+GetConvertStr(itmRef.name, "ItemsDescribe.txt")+"");
							PlaySound("People Fight\reload1.wav");
							ref itms = ItemsFromID(xi_refCharacter.chr_ai.bullet);
							SetNodeUsing("ITEM_14" , true);
							SetNewGroupPicture("ITEM_14", itms.picTexture, "itm" + itms.picIndex);
							return;
						}
					}
					if (sItemID == "hatWhisper")
					{
						ChangeWhisperHeroModel();
					}
				}
			}
			FillItemsSelected();
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
			SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(sItemID));
			SetItemInfo();
		}
	}
	if (HasSubStr(sItemID,"Strange"))
	{
		int strangeHpBonus = 5;
		int strangeEnBonus = 2;
		if (HasSubStr(xi_refCharacter.model,"Lejitos") || HasSubStr(xi_refCharacter.model,"Shicoba") || xi_refCharacter.id == "Tichingitu")
		{
			//Персонажи с индейским прошлым получают более сильный эффект
			strangeHpBonus = 10;
			strangeEnBonus = 4;
		}

		if (sItemID == "StrangeMushrooms" && sti(xi_refCharacter.StrangeMushrooms) < 5)
		{
			LAi_SetHP (xi_refCharacter,1,LAi_GetCharacterMaxHP(xi_refCharacter) + strangeHpBonus);
			xi_refCharacter.StrangeMushrooms = sti(xi_refCharacter.StrangeMushrooms)+1;
			PlaySound("interface\heartbeat.wav");
			if (IsMainCharacter(xi_refCharacter)) Log_Info("Ваше максимальное здоровье увеличено на "+strangeHpBonus+"!");
			else Log_Info(GetFullName(xi_refCharacter)+" увеличивает максимальное здоровье на "+strangeHpBonus+"!")
			ApplayNewSkill(pchar, "", 0);
			TakeNItems(xi_refCharacter, sItemID, -1);
			FillItemsTable(iCurTab);
		}
		else
		{
			if (sItemID == "StrangePotion" && sti(xi_refCharacter.StrangePotion) < 5)
			{
				LAi_SetHP (xi_refCharacter,1,LAi_GetCharacterMaxHP(xi_refCharacter));
				AddBonusEnergyToCharacter(xi_refCharacter,strangeEnBonus);
				xi_refCharacter.StrangePotion = sti(xi_refCharacter.StrangePotion)+1;
				PlaySound("interface\heartbeat.wav");
				if (IsMainCharacter(xi_refCharacter)) Log_Info("Ваша максимальная энергия увеличилась на "+strangeEnBonus+"!");
				else {Log_Info(GetFullName(xi_refCharacter)+" увеличивает максимальную энергию на "+strangeEnBonus+"!")}
				ApplayNewSkill(pchar, "", 0);
				TakeNItems(xi_refCharacter, sItemID, -1);
				FillItemsTable(iCurTab);
			}
			else
			{
				if (sItemID == "StrangeElixir" && !CheckAttribute(xi_refCharacter, "StrangeElixir"))
				{
					xi_refCharacter.StrangeElixir = true;
					LAi_SetHP (xi_refCharacter,1,LAi_GetCharacterMaxHP(xi_refCharacter));
					PlaySound("interface\heartbeat.wav");
					if (IsMainCharacter(xi_refCharacter)) Log_Info("Ваш урон в ближнем бою навсегда увеличен на десять процентов!");
					else {Log_Info(GetFullName(xi_refCharacter)+" навсегда увеличивает урон в ближнем бою на десять процентов!")}
					ApplayNewSkill(pchar, "", 0);
					TakeNItems(xi_refCharacter, sItemID, -1);
					FillItemsTable(iCurTab);
				}
			}
			else PlaySound("interface\knock.wav");
		}
	}
	if (HasSubStr(sItemID,"Tube") && IsMainCharacter(xi_refCharacter))
	{
		switch (sItemID)
		{
			case "HealthTube":
				if (!CheckAttribute(pchar, "chr_ai.bonushptube"))
				{
					pchar.chr_ai.bonushptube = 0;
					pchar.PerkValue.HPBONUS = 50+rand(50)+sti(pchar.rank);
					float nphpp = LAi_GetCharacterMaxHP(pchar) + sti(pchar.PerkValue.HPBONUS);
					LAi_SetHP(pchar,nphpp,nphpp);
					SetTimerFunction("ClearHPTubeEffect",0,0,1);
				}
				else return;
			break;
			case "EnergyTube":
				if (!CheckAttribute(pchar, "chr_ai.bonusentube"))
				{
					pchar.chr_ai.bonusentube = 0;
					pchar.tubeBonusEnergy = 30+rand(20)+sti(pchar.rank);
					AddBonusEnergyToCharacter(pchar,sti(pchar.tubeBonusEnergy));
					SetTimerFunction("ClearENTubeEffect",0,0,1);
				}
				else return;
			break;
			case "StrengthTube":
				if (!CheckAttribute(pchar, "chr_ai.bonusweighttube"))
				{
					pchar.chr_ai.bonusweighttube = 0;
					SetTimerFunction("ClearSTubeEffect",0,0,1);
				}
				else return;
			break;
		}
		int drugEffects = 0;
		if (CheckAttribute(pchar,"chr_ai.bonusentube")) drugEffects++;
		if (CheckAttribute(pchar,"chr_ai.bonusweighttube")) drugEffects++;
		if (CheckAttribute(pchar,"chr_ai.bonushptube")) drugEffects++;
		if (drugEffects == 2 && rand(20) == 0) GetHigh();
		if (drugEffects == 2 && rand(4) == 0) GetHigh();
		if (drugEffects == 3) GetHigh();

		if (CheckAttribute(pchar,"drugstaken")) pchar.drugstaken = sti(pchar.drugstaken)+1;
		else {pchar.drugstaken = 1; SetTimerFunction("ClearDrugs",0,0,10);}
		ApplayNewSkill(pchar, "", 0);
		TakeNItems(pchar, sItemID, -1);
		FillItemsTable(iCurTab);
	}
}
void GetHigh()
{
	Log_Info("Кажется, последняя затяжка была лишней");
	pchar.HighOnDrugs = true;
	if (pchar.sex == "woman")
	{
		PlaySound("interface\baba_kxe_kxe.wav");
	}
	else
	{
		PlaySound("interface\man_kxe_kxe.wav");
	}

	for(int i = 0; i < MAX_CHARACTERS; i++)
	{
		ref chr;
		makeref(chr,Characters[i]);
		if(!CheckAttribute(chr, "BeforeDrugsModel") && chr.model.animation == "man")
		{
			chr.BeforeDrugsModel = chr.model;
			switch (rand(2))
			{
				case 0:
					chr.model = GetRandSkelModel();
				break;
				case 1:
					chr.model = GetRandSkelModelClassic();
				break;
				case 2:
					chr.model = "Canib_"+(rand(5)+1);
				break
			}
			if (rand(10) == 0)
			{
				switch (rand(1))
				{
					case 0:
						chr.model = "PotCMobCap";
					break;
					case 1:
						chr.model = "Canib_boss";
					break;
				}
			}
			SetNewModelToChar(chr);
		}
	}
}
void ExitMapWindow()
{
	XI_WindowShow("MAP_WINDOW", false);
	XI_WindowDisable("MAP_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetFormatedText("MAP_TEXT", "");
	sMapDescribe = "";//обнуляем при выходе из карты, иначе после просмотра карты сокровищ можно открыть карту острова и на ней будет работать показ описания запомненной карты
	SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_MSG_TO_NODE,"MAP_X_CROSS", 0, makeint(fOffsetX)+721, 25, makeint(fOffsetX)+743, 47);// Установить отметку на исходную позицию, под кнопку закрытия

	SetCurrentNode("TABLE_ITEMS");
}

void SetMapCross(string _MapLocId)
{
	int left, top;//координаты для отметки клада
	bMapCross = true;//текст описания карты не показывать сразу

	switch(_MapLocId)//список локаций беру из MapDescribe.txt
	{
	case "Antigua_Grot": left = 622; top = 235; break;	//{в пещере справа от залива Уиллогби}
	case "SentJons_TownCave": left = 601; top = 235; break;	//{в подземелье города Сент-Джонс}

	case "Beliz_Cave": left = 58; top = 181; break;	//{в пещере справа от выхода из Белиза}
	case "Beliz_Cave_2": left = 55; top = 225; break;	//{в пещере напротив выхода из Белиза}

	case "Panama_Cave": left = 229; top = 502; break;	//{в пещере слева от выхода из города Порто Белло}
	case "PortoBello_Cave": left = 195; top = 512; break;	//{в пещере справа от залива Москитос}

	case "Tortuga_Grot": left = 374; top = 53; break;	//{в пещере напротив пляжа Глаз Рыбы}
	case "Tortuga_Cave": left = 380; top = 61; break;	//{в подземелье города Тортуга}

	case "Caracas_Grot": left = 444; top = 484; break;	//{в пещере слева от выхода из Каракаса}
	case "Maracaibo_Cave": left = 369; top = 474; break;	//{в пещере напротив выхода из Маракайбо}
	case "Cartahena_Cave": left = 304; top = 510; break;	//{в пещере напротив выхода из Картахены}

	case "Pearl_Grot": left = 66; top = 345; break;	//{в пещере на западном побережье между Белизом и Санта Каталиной}
	case "SantaCatalina_Grot": left = 123; top = 445; break;	//{в пещере справа от залива Сан Хуан дель Норте}
	case "SantaCatalina_PearlCave": left = 109; top = 466; break;	//{в пещере слева от залива Сан Хуан дель Норте}
	case "SantaCatalina_Cave": left = 106; top = 375; break;	//{в пещере справа от мыса Перлас}
	case "Tenotchitlan_Cave": left = 55; top = 308; break;	//{в пещере на север от храма Инков}

	case "Barbados_Cave": left = 625; top = 385; break;	//{в пещере недалеко от Бриджтауна}
	case "Bermudes_Dungeon": left = 625; top = 29; break;	//{в подземелье под верьфью пиратского поселения}
	case "Caiman_Grot": left = 202; top = 173; break;	//{в пещере справа от пустынного пляжа}
	case "Charles_Grot": left = 550; top = 202; break;	//{в пещере справа от пляжа Бат}
	case "Cuba_Grot": left = 198; top = 44; break;	//{в пещере справа от мыса Камагуэй}
	case "Cumana_Cave": left = 530; top = 505; break;	//{в пещере справа от бухты Карупано}
	case "Curacao_Cave": left = 465; top = 435; break;	//{в пещере справа от берега Приют контрабандиста}
	case "Dominica_Grot": left = 574; top = 326; break;	//{в пещере справа от пляжа Касл Брус}
	case "Guadeloupe_Cave": left = 485; top = 269; break;	//{в пещере слева от маяка Гваделупы}
	case "Hispaniola_Cave": left = 383; top = 119; break;	//{в пещере недалеко от города Порт-о-Принс}
	case "Jamaica_Grot": left = 263; top = 287; break;	//{в пещере справа от маяка Порт-Рояля}
	case "Marigo_Cave": left = 619; top = 140; break;	//{в пещере напротив выхода из Мариго}
	case "SanJuan_Cave": left = 485; top = 153; break;	//{в пещере недалеко от Сан-Хуана}
	case "Bahames_Grot": left = 263; top = 26; break;	//{в гроте справа от бухты Приватира}
	case "Terks_Grot": left = 474; top = 33; break;	//{в пещере справа от залива Северный}
 	case "Trinidad_Grot": left = 591; top = 458; break;	//{в пещере напротив маяка Тринидада и Тобаго}
 	case "FortFrance_Dungeon": left = 499; top = 357; break;	//{в подземелье города Форт де Франс}
	}
	//to do - тогда уж можно выбирать ещё и карту отдельного острова для отображения
	//оставить плохую общую для карт с описанием "старая рваная", а качественные карты островов выбирать при описании "выглядит новой"???

	//position = 50,50,750,580 - позиция карты
	SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_MSG_TO_NODE,"MAP_X_CROSS", 0, 43+makeint(fOffsetX)+left, 50+top, 43+makeint(fOffsetX)+left+14, 50+top+14);// Установить картинку на новую позицию
}

void ShowMapDesc()
{
	if (bMapCross)
		{
		SetFormatedText("MAP_TEXT", sMapDescribe);
		SetVAligmentFormatedText("MAP_TEXT");
		bMapCross = false;
		}
	else
		{
		SetFormatedText("MAP_TEXT", "");
		bMapCross = true;
		}
}

void ShowMapWindow()
{
	XI_WindowShow("MAP_WINDOW", true);
	XI_WindowDisable("MAP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MAP_TEXT");
	SetCurrentNode("MAP_X_CROSS");
}

void ExitItemFromCharacterWindow()
{
	XI_WindowShow("ITEM_FROM_CHARACTER_WINDOW", false);
	XI_WindowDisable("ITEM_FROM_CHARACTER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetNodeUsing("ITEM_FROM_CHARACTER_OK_BUTTON", false);
	SetNodeUsing("ITEM_FROM_CHARACTER_CANCEL_BUTTON", false);
	SetNodeUsing("QTY_EDIT", false);
	SetNodeUsing("QTY_ADD_BUTTON", false);
	SetNodeUsing("QTY_ADD_ALL_BUTTON", false);
	SetNodeUsing("QTY_REMOVE_BUTTON", false);
	SetNodeUsing("QTY_REMOVE_ALL_BUTTON", false);

	GameInterface.qty_edit.str = 0;

	SetCurrentNode("TABLE_ITEMS");
}

void ShowItemFromCharacterWindow()
{
	if (CheckAttribute(xi_refCharacter,"nonremovable")) return;
	string sItemID = GameInterface.(CurTable).(CurRow).id;

	XI_WindowShow("ITEM_FROM_CHARACTER_WINDOW", true);
	XI_WindowDisable("ITEM_FROM_CHARACTER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetNodeUsing("ITEM_FROM_CHARACTER_OK_BUTTON", true);
	SetNodeUsing("ITEM_FROM_CHARACTER_CANCEL_BUTTON", true);
	SetNodeUsing("QTY_EDIT", true);
	SetNodeUsing("QTY_ADD_BUTTON", true);
	SetNodeUsing("QTY_ADD_ALL_BUTTON", true);
	SetNodeUsing("QTY_REMOVE_BUTTON", true);
	SetNodeUsing("QTY_REMOVE_ALL_BUTTON", true);

	SetCurrentNode("ITEM_FROM_CHARACTER_TEXT");
	SetCurrentNode("ITEM_FROM_CHARACTER_NAME");

	ref itm = ItemsFromID(sItemID);

	string sTexture = itm.picTexture;
	string sPicture = "itm" + itm.picIndex;

	SetNewGroupPicture("ITEM_FROM_CHARACTER_PICTURE", sTexture, sPicture);
	SetNewGroupPicture("ITEM_FROM_CHARACTER_WEIGHT_PICTURE", "ICONS", "weight icon");

	int lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sGood = itm.name;
	string sGoodName = LanguageConvertString(lngFileID, sGood);

	SetFormatedText("ITEM_FROM_CHARACTER_TEXT", GetItemDescribe(sItemID));
	if(sti(xi_refCharacter.index) != nMainCharacterIndex) SetFormatedText("ITEM_FROM_CHARACTER_NAME", "Передать предмет: " + sGoodName);
	else SetFormatedText("ITEM_FROM_CHARACTER_NAME", "Выкинуть предмет: " + sGoodName);

	int iQuantity = sti(GameInterface.qty_edit.str);
	float fItemQuantity = iQuantity * GetItemWeight(sItemID);
	float fWeight = GetItemsWeight(xi_refCharacter) - fItemQuantity;

	if(iQuantity <= 0)
	{
		fItemQuantity = GetItemsWeight(xi_refCharacter);
	}


	aref arTest;
	makearef(arTest, itm);
	string sTemp = "";
	int attrQ = GetAttributesNum(arTest);
	for(i=0; i<attrQ; i++)
	{
		sTemp = GetAttributeValue(GetAttributeN(arTest,i));
		log_testinfo(GetAttributeName(GetAttributeN(arTest,i)) + " = " + sTemp);
	}

	SetFormatedText("ITEM_FROM_CHARACTER_WEIGHT_TEXT", XI_ConvertString("weight") + ": " + FloatToString(fWeight, 1) + " / "+GetMaxItemsWeight(xi_refCharacter));
	LanguageCloseFile(lngFileID);
}


void confirmChangeQTY_EDIT()
{
	string sItemID = GameInterface.(CurTable).(CurRow).id;
	ChangeQTY_EDIT(sItemID);
	CheckAndSetOverloadMode(GetMainCharacter());
}

void ChangeQTY_EDIT(string sItem)
{
	if(sti(GameInterface.qty_edit.str) < 0 || isPassenger)
	{
		GameInterface.qty_edit.str = 0;
	}

	if(sti(GameInterface.qty_edit.str) > GetCharacterItem(xi_refCharacter, sItem))
	{
		GameInterface.qty_edit.str = GetCharacterItem(xi_refCharacter, sItem);
	}


	if(IsEquipCharacterByItem(xi_refCharacter, sItem))
	{
		if(sti(GameInterface.qty_edit.str) >= GetCharacterItem(xi_refCharacter, sItem))
		{
			GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str) - 1;
		}
	}

	if(IsQuestUsedItem(sItem))
	{
		GameInterface.qty_edit.str = 0;
	}

	int iQuantity = sti(GameInterface.qty_edit.str);
	float fItemQuantity = iQuantity * GetItemWeight(sItem);
	float fWeight = GetItemsWeight(xi_refCharacter) - fItemQuantity;

	if(iQuantity <= 0)
	{
		fItemQuantity = GetItemsWeight(xi_refCharacter);
	}

	if (sti(xi_refCharacter.index) != nMainCharacterIndex) 
	{
		if (GetItemsWeight(pchar) + (iQuantity * GetItemWeight(sItem)) >= GetMaxItemsWeight(pchar))
		{
			SetFormatedText("ITEM_FROM_CHARACTER_TEXT", GetItemDescribe(sItem)+"\n\nПревышается переносимый вес главного героя.\nЛишний вес будет выброшен.");
		}
		else SetFormatedText("ITEM_FROM_CHARACTER_TEXT", GetItemDescribe(sItem));
	}														
	SetFormatedText("ITEM_FROM_CHARACTER_WEIGHT_TEXT", XI_ConvertString("weight") + ": " + FloatToString(fWeight, 1) + " / "+GetMaxItemsWeight(xi_refCharacter));

}

void REMOVE_ALL_BUTTON(string sItem)  // выкинуть все
{
	if(IsQuestUsedItem(sItem))
	{
		return;
	}

	int iQuantity = GetCharacterItem(xi_refCharacter, sItem);

	GameInterface.qty_edit.str = iQuantity;
	ChangeQTY_EDIT(sItem);
}

void ADD_ALL_BUTTON(string sItem)  // сбросить
{
	GameInterface.qty_edit.str = 0;
	ChangeQTY_EDIT(sItem);
}

void REMOVE_BUTTON(string sItem)  // выкинуть
{
	if(IsQuestUsedItem(sItem))
	{
		return;
	}

	if(GetCharacterItem(xi_refCharacter, sItem) >= 1)
	{
		GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
	}

	if(sti(GameInterface.qty_edit.str) > GetCharacterItem(xi_refCharacter, sItem))
	{
		GameInterface.qty_edit.str = GetCharacterItem(xi_refCharacter, sItem);
	}
	ChangeQTY_EDIT(sItem);
}

void ADD_BUTTON(string sItem)  // не выкидывать
{
	GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);

	if(sti(GameInterface.qty_edit.str) < 0)
	{
		GameInterface.qty_edit.str = 0;
	}

	ChangeQTY_EDIT(sItem);
}

void RemoveItemsQuantity()
{
	string sItemID = GameInterface.(CurTable).(CurRow).id;
	ChangeQTY_EDIT(sItemID);

	int iQuantity = sti(GameInterface.qty_edit.str);
	if(iQuantity <= 0)
	{
		return;
	}

	float fItemQuantity = iQuantity * GetItemWeight(sItemID);

	TakeNItems(xi_refCharacter, sItemID, -iQuantity);
	if(sti(xi_refCharacter.index) != nMainCharacterIndex)
	{
		float fWeight = GetItemsWeight(pchar) + fItemQuantity;
		if (GetMaxItemsWeight(pchar)<=fWeight) 
		{
			if (GetItemsWeight(pchar) >= GetMaxItemsWeight(pchar)) {}
			else 
			{
				TakeNItems(pchar, sItemID, makeint(fItemQuantity - ((-1) * (GetMaxItemsWeight(pchar) - GetItemsWeight(pchar) - fItemQuantity))) / GetItemWeight(sItemID)));
			}
		}
		else TakeNItems(PChar, sItemID, iQuantity);
	}											 

	ExitItemFromCharacterWindow();
	SetVariable();
}

void ShowBladeEquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.blade")) return;
	if(xi_refCharacter.equip.blade == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "blade");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowGunEquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.gun")) return;
	if(xi_refCharacter.equip.gun == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "gun");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowSpyglassEquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.spyglass")) return;
	if(xi_refCharacter.equip.spyglass == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "spyglass");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowBackPackEquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.BackPack")) return;
	if(xi_refCharacter.equip.BackPack == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "BackPack");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowTalismanEquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.talisman")) return;
	if(xi_refCharacter.equip.talisman == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "talisman");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowCirassEquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.cirass")) return;
	if(xi_refCharacter.equip.cirass == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "cirass");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ShowBookEquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.book")) return;
	if(xi_refCharacter.equip.book == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "book");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show1EquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.jewelry_indian_left")) return;
	if(xi_refCharacter.equip.jewelry_indian_left == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "jewelry_indian_left");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show2EquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.jewelry_indian_right")) return;
	if(xi_refCharacter.equip.jewelry_indian_right == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "jewelry_indian_right");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show3EquipInfo()
{
  	if(!CheckAttribute(xi_refCharacter, "equip.indian_center")) return;
	if(xi_refCharacter.equip.indian_center == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "indian_center");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show4EquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.idols_left")) return;
	if(xi_refCharacter.equip.idols_left == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "idols_left");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void Show5EquipInfo()
{
	if(!CheckAttribute(xi_refCharacter, "equip.idols_right")) return;
	if(xi_refCharacter.equip.idols_right == "") return;

	int idLngFile = LanguageOpenFile("ItemsDescribe.txt");

	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;

	string sItem = GetCharacterEquipByGroup(xi_refCharacter, "idols_right");
	ref itm = ItemsFromID(sItem);

	sGroup = itm.picTexture;
	sGroupPicture = "itm" + itm.picIndex;

	sHeader = "";

	sHeader = itm.name;
	sHeader = LanguageConvertString(idLngFile, sHeader);

	sText1 = GetItemDescribe(sItem);

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 100, 100);
	LanguageCloseFile(idLngFile);
}

void ClickSaber()		{ClickItem("ITEM_1", "blade", 2);}
void ClickGun()			{ClickItem("ITEM_2", "gun", 2);}
void ClickSpyGlass()	{ClickItem("ITEM_3", "spyglass", 2);}
void ClickCirass()		{ClickItem("ITEM_4", "cirass", 2);}
void ClickMushket()		{ClickItem("ITEM_5", "gun", 2);}
void ClickBackPack()	{ClickItem("ITEM_6", "BackPack", 2);}
void ClickTalisman()	{ClickItem("ITEM_7", "talisman", 2);}
void ClickBook()		{ClickItem("ITEM_9", "book", 3);}
void ClickShow1()		{ClickItem("ITEM_10", "jewelry_indian_left", 3);}
void ClickShow2()		{ClickItem("ITEM_11", "jewelry_indian_right", 3);}
void ClickShow3()		{ClickItem("ITEM_8", "indian_center", 3);}
void ClickShow4()		{ClickItem("ITEM_12", "idols_left", 3);}
void ClickShow5()		{ClickItem("ITEM_13", "idols_right", 3);}

void ClickItem(string sItem, string sEquipType, int _tabNum)
{
	string sTemp, row;

	if(!CheckAttribute(xi_refCharacter, "equip." + sEquipType)) return;
	if(xi_refCharacter.equip.(sEquipType) == "") return;
	string sCurItem = GetCharacterEquipByGroup(xi_refCharacter, sEquipType);
	SetControlsTabMode(_tabNum);//выбираем вкладку с нужным
	for (int q=1;q<1000;q++)
	{
		row = "tr" + q;
		if (!checkattribute(&GameInterface,"TABLE_ITEMS." + row)) break;//кончились строки таблицы, конец цикла
		if (sCurItem == GameInterface.TABLE_ITEMS.(row).id)
		{
			Event("TableSelectChange", "sll", "TABLE_ITEMS", q, 1);//выбираем в таблице предмет снаряжения
			GameInterface.TABLE_ITEMS.select = q;
			if (q<5) q=5;
			GameInterface.TABLE_ITEMS.top = q-5;//стараемся красиво проскроллить таблицу на этот предмет
			Table_UpdateWindow("TABLE_ITEMS");
			SetCurrentNode("TABLE_ITEMS");
			break;
		}
	}
}

void CheckButtonChange()
{
	string sControl = GetEventData();
	int iSelectedCB = GetEventData();
	int iNewState = GetEventData();
//========================================//
	if (sControl == "CHECK_EQUIP_SET")
	{
		SaveEquipSet();
		iEQUIP_SET = iSelectedCB;
		ReEquipCharacter();
		FillItemsTable(iCurTab);
		return;
	}
}

void ReEquipCharacter()
{
	xi_refCharacter.selectedSet = iEQUIP_SET;//запоминаем выбор сэта
	string sSET = "Set" + iEQUIP_SET;
	if (!checkattribute(xi_refCharacter, sSET)) return; //не было сохранения этого комплекта

	string sTemp;
	for (int q=0;q<8;q++)
	{
	sTemp = sEType[q];
		if(xi_refCharacter.(sSET).(sTemp) != GetCharacterEquipByGroup(xi_refCharacter, sTemp))//если другой предмет, то снимаем старый, одеваем сохранённый
		{
			RemoveCharacterEquip(xi_refCharacter, sTemp);
			if (xi_refCharacter.(sSET).(sTemp) != "") {EquipCharacterByItem(xi_refCharacter, xi_refCharacter.(sSET).(sTemp));}
		}
	}
	FillItemsSelected();//обновляем картинки на кукле
}

void SaveEquipSet()
{
	string sSET = "Set" + iEQUIP_SET;//Set1, Set2, Set3
	xi_refCharacter.(sSET) = 1; //помечаем, что в этом комплекте что-то сохранено
	if (!checkattribute(xi_refCharacter, sSET + ".nameset")) xi_refCharacter.(sSET).nameset = "Комплект " + iEQUIP_SET;//в первый раз записываем "Комплект N"
	string sTemp;
	for (int q=0;q<8;q++)
	{
	sTemp = sEType[q];
	xi_refCharacter.(sSET).(sTemp) = GetCharacterEquipByGroup(xi_refCharacter, sTemp);
	}
	//книгу не запоминаем, потому что не надо
	//огнестрел не запоминаем, потому что сложно (пистоль+мушкет+патроны + нестандартные ситуации)
/*
//TODO - запоминать и огнестрел
//фрагмент кода для информации о способе хранения, но ещё надо разобраться как экипировать
					case GUN_ITEM_TYPE:
						ref itms = ItemsFromID(xi_refCharacter.chr_ai.bullet);									//пули
						if(CheckAttribute(xi_refCharacter, "IsMushketer"))
						{
							iLastGunItem = GetItemIndex(xi_refCharacter.IsMushketer.LastGunID);					//пистолет, который может быть под мушкетом
							// Покажем картинку старого пистоля, если он ещё есть
							if(iLastGunItem != -1 && GetCharacterItem(xi_refCharacter, xi_refCharacter.IsMushketer.LastGunID) > 0)
							{
								rLastGunItem = &Items[iLastGunItem];
								SetNewGroupPicture("ITEM_2", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
								SetNodeUsing("ITEM_2" , true);
							}

							rLastGunItem = &Items[GetItemIndex(xi_refCharacter.IsMushketer.MushketID)];			//мушкет
							SetNodeUsing("ITEM_5", true);
							SetNewGroupPicture("ITEM_5", rLastGunItem.picTexture, "itm" + rLastGunItem.picIndex);
						}
						else
						{
							SetNewGroupPicture("ITEM_2", Items[i].picTexture, "itm" + Items[i].picIndex);
							SetNodeUsing("ITEM_2" , true);
							SetNodeUsing("ITEM_5" , false); // Мушкет не юзается - уберем картинку
						}
					break;

*/
}

void FillSetName(int iNum)
{
	string sSET = "Set" + iNum;
	string sName;
	if (!checkattribute(xi_refCharacter, sSET))	sName = "Комплект " + iNum;	else sName = xi_refCharacter.(sSET).nameset;
	GameInterface.EDIT_BOX1.str = sName;
	SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"CHECK_EQUIP_SET", 1, iNum, sName);
}

void SaveSETName()
{
	if(GameInterface.EDIT_BOX1.lastkey == " ") return;
	string sSET = "Set" + iEQUIP_SET;
	xi_refCharacter.(sSET).nameset = GameInterface.EDIT_BOX1.str;
	FillSetName(iEQUIP_SET);
	HideEditBox();
}

void ShowEditBox()
{
	string sSET = "Set" + iEQUIP_SET;
	if (!checkattribute(xi_refCharacter, sSET))	GameInterface.EDIT_BOX1.str = "Комплект " + iEQUIP_SET;	else GameInterface.EDIT_BOX1.str = xi_refCharacter.(sSET).nameset;
	SetNodeUsing("EDIT_BOX1" , true);
	SetNodeUsing("EDIT_BOX1_FRAME" , true);
	SetCurrentNode("EDIT_BOX1");
}

void HideEditBox()
{
	SetNodeUsing("EDIT_BOX1" , false);
	SetNodeUsing("EDIT_BOX1_FRAME" , false);
}

void DiscardTreasureMap()
{
	TakeNItems(pchar, "map_full", -1);
	ref item;
	FillMapForTreasure(Items_FindItem("map_full", &item));
	ExitMapWindow();
	FillItemsTable(iCurTab);
}
