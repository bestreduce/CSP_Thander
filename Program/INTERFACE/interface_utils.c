string sEType[8] = {"blade","cirass","talisman","jewelry_indian_left","jewelry_indian_right","indian_center","idols_left","idols_right"};
int CheckItemInSets(ref _character, string sItemName)
{
	if (!checkattribute(_character, "selectedSet")) return 0; //у этого персонажа не было сохранено комплектов
	int i, q;
	string sSET, sTemp;
	for(i=1;i<10;i++)//9 комплектов???
	{
		if (_character.selectedSet == i) continue;//текущий комплект уже скрыт в списке перемещения предметов
		sSET = "Set" + i;
		if (!checkattribute(_character, sSET)) continue; //нет комплекта
		for (q=0;q<8;q++)
		{
			sTemp = sEType[q];
			if(_character.(sSET).(sTemp) == sItemName && GetCharacterEquipByGroup(_character, sTemp) != sItemName) return i;
				//предмет есть в неактивном комплекте И не экипирован прямо сейчас						//возвращаем номер комплекта
		}
	}
	return 0;
}
//---------------------------------------------------------------------------------------------------
// scrollimage
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithCompanionShips(string sNodeName, int iNotUsed)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "BLANK_SHIP2";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "Not Used2";

	FillShipList(sNodeName + ".ImagesGroup", pchar);

	string attributeName, shipName;
	int iShipType, cn;
	int iListSize = 0;

	int isPossibleToFill = 1;
	for(int i= 0; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1)
		{
			/*if(GetShipRemovable(&characters[cn]) == 0 && cn != nMainCharacterIndex)
			{
				isPossibleToFill = 0;
			}
			else
			{  */
				isPossibleToFill = 1;
			//}
			if(isPossibleToFill == 1)
			{
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					//Boyer change #20170430-03
					//iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
					    //Boyer change #20170430-03
						//shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						//Boyer change #20170430-03
                        ref rBaseShip = GetRealShip(iShipType);
                        iShipType = rBaseShip.basetype;
                        //#20170430-03 Companion ships are appended with a "1"
                        if(strlen(rBaseShip.Name)>2)
                            shipName = strcut(rBaseShip.Name, 0, strlen(rBaseShip.Name)-2);
                        else
                            shipName = "";


						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).companionIndex = cn;
						GameInterface.(sNodeName).(attributeName).img1 = "ship";
						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

						iListSize++;
					}
				}
			}
			/*else
			{
				attributeName = "pic" + (i+1);
				GameInterface.(sNodeName).(attributeName).tex1= 0;
			}  */
		}
		/*else
		{
			attributeName = "pic" + (i+1);
			GameInterface.(sNodeName).(attributeName).tex1= 0;
		} */
	}

	GameInterface.(sNodeName).ListSize = iListSize;
	//GameInterface.(sNodeName).NotUsed = iNotUsed;
	GameInterface.SHIPS_SCROLL.NotUsed = iNotUsed - iListSize + 1;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}

void FillScrollImageWithCompanions(string sNodeName, int iNotUsed)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "BLANK_SHIP2";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "Not Used2";

	FillShipList(sNodeName + ".ImagesGroup", pchar);

	string attributeName, shipName;
	int iShipType, cn;
	int iListSize = 0;

	int isPossibleToFill = 1;
	for(int i= 1; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1)
		{
			/*if(GetShipRemovable(&characters[cn]) == 0 && cn != nMainCharacterIndex)
			{
				isPossibleToFill = 0;
			}
			else
			{  */
				isPossibleToFill = 1;
			//}
			if(isPossibleToFill == 1)
			{
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					//Boyer change #20170430-03
					//iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
					    //Boyer change #20170430-03
						//shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						//Boyer change #20170430-03
                        ref rBaseShip = GetRealShip(iShipType);
                        iShipType = rBaseShip.basetype;
                        //#20170430-03 Companion ships are appended with a "1"
                        if(strlen(rBaseShip.Name)>2)
                            shipName = strcut(rBaseShip.Name, 0, strlen(rBaseShip.Name)-2);
                        else
                            shipName = "";


						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).companionIndex = cn;
						GameInterface.(sNodeName).(attributeName).img1 = "ship";
						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

						iListSize++;
					}
				}
			}
			/*else
			{
				attributeName = "pic" + (i+1);
				GameInterface.(sNodeName).(attributeName).tex1= 0;
			}  */
		}
		/*else
		{
			attributeName = "pic" + (i+1);
			GameInterface.(sNodeName).(attributeName).tex1= 0;
		} */
	}

	GameInterface.(sNodeName).ListSize = iListSize;
	//GameInterface.(sNodeName).NotUsed = iNotUsed;
	GameInterface.SHIPS_SCROLL.NotUsed = iNotUsed - iListSize + 1;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}

void FillScrollImageWithCompanionsUp(string sNodeName, int iNotUsed)
{
	FillShipList(sNodeName + ".ImagesGroup", pchar);

	string attributeName, shipName;
	int iShipType, cn;
	int iListSize = 0;

	int isPossibleToFill = 1;
	for(int i= 1; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1)
		{
			/*if(GetShipRemovable(&characters[cn]) == 0 && cn != nMainCharacterIndex)
			{
				isPossibleToFill = 0;
			}
			else
			{  */
				isPossibleToFill = 1;
			//}
			if(isPossibleToFill == 1)
			{
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					//Boyer change #20170430-03
					//iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
					    //Boyer change #20170430-03
						//shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						//Boyer change #20170430-03
                        ref rBaseShip = GetRealShip(iShipType);
                        iShipType = rBaseShip.basetype;
                        //#20170430-03 Companion ships are appended with a "1"
                        if(strlen(rBaseShip.Name)>2)
                            shipName = strcut(rBaseShip.Name, 0, strlen(rBaseShip.Name)-2);
                        else
                            shipName = "";


						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

						iListSize++;
					}
				}
			}
		}
	}
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithFaces(string sNodeName, int iNotUsed, bool bCompanions, bool bPassengers)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "EMPTYFACE";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "emptyface";

	ref refCharacter = pchar;

	int iListSize = 0;
	int cn;
	string attributeName;
	aref pRef,pRef2;
	string PsgAttrName;


	if (bCompanions){

		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 1); // companions

		for(int n= 0; n< COMPANION_MAX; n++)
		{
			attributeName = "pic" + (iListSize+1);
			cn = GetCompanionIndex(refCharacter, n);

			if(cn!= -1)
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}

	if (bPassengers){


		makearef(pRef,refCharacter.Fellows.Passengers);
		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 2); // passengers

		for(int i= 0; i< GetPassengersQuantity(refCharacter); i++)
		{
			attributeName = "pic" + (iListSize+1);
			PsgAttrName = "id"+(i+1);
			cn = sti(pRef.(PsgAttrName));

			if(cn!=-1 && !CheckAttribute(&characters[cn], "isfree"))
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}
	/*
	if (bOfficers)
	{
	makearef(pRef,refCharacter.Fellows.Passengers);

	FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 0); // officers

	for(int o= 0; o< 4; o++)
	{
	attributeName = "pic" + (iListSize+1);
	cn = sti(pRef.(PsgAttrName));
	if(cn!=-1)
	{
	GameInterface.(sNodeName).(attributeName).character = cn;
	GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
	GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName+ ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

	iListSize++;
	}
	}
	}
	*/
	GameInterface.(sNodeName).ListSize = iListSize;
	GameInterface.(sNodeName).NotUsed = iNotUsed;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
/// boal -->
void StartAboveForm(bool _pauseTime)
{
    ChangeShowIntarface();

	EngineLayersOffOn(true);
    if (_pauseTime)
    {
		SetTimeScale(0.0);
	}
	locCameraSleep(true);
	LAi_CharacterDisableDialog(pchar);
}

void EndAboveForm(bool _pauseTime)
{
    if (_pauseTime)
    {
		SetTimeScale(1.0);
		TimeScaleCounter = 0;
	 	DelPerkFromActiveList("TimeSpeed");
	 	DeleteAttribute(pchar, "pause");
	}
	locCameraSleep(false);
	LAi_CharacterEnableDialog(pchar);
	ChangeShowIntarface();
}

void ChangeShowIntarface()
{
    if (bSeaActive && !bAbordageStarted)
    {
        if (!IsEntity(BattleInterface))
        {
            InitBattleInterface();
            StartBattleInterface();
            RefreshBattleInterface();
        }
        else DeleteBattleInterface();
    }
    else
    {
		if (!IsEntity(worldMap))
		{
			if (!bLandInterfaceStart)
	        {
	            StartBattleLandInterface();
	        }
	        else EndBattleLandInterface();
        }
    }
}
// вернуть тип по номеру скрола в ф2 персонаж
string GetOfficerTypeByNum(int nCurScrollNum)
{
    string ret = "";

	switch (nCurScrollNum)
	{
		case 1:
   			ret = "navigator";
		break;

		case 2:
   			ret = "boatswain";
		break;

		case 3:
   			ret = "cannoner";
		break;

		case 4:
   			ret = "doctor";
		break;

		case 5:
   			ret = "treasurer";
		break;

		case 6:
   			ret = "carpenter";
		break;

		//Boyer mod
		/*
		case 7:
  			ret = "fighter";
		break;

		case 8:
   			ret = "fighter";
		break;

		case 9:
   			ret = "fighter";
		break;

		case 10:
			ret = "fighter";
		break;
		//Boyer add
		case 11:
   			ret = "fighter";
		break;

		case 12:
			ret = "fighter";
		break;
		*/
		//default
			ret = "fighter";
		//End Boyer add
	}
	return ret;
}

////////////////////////////// общие методы для форм
void SetOTHERMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=5; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "-2, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "-2,-1";
		GameInterface.(_tabName).(row).td3.align = "right";
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Rank";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Rank";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Rank");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.rank);

	GameInterface.(_tabName).tr2.UserData.ID = "Life";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Life";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Life");
	GameInterface.(_tabName).tr2.td3.str = MakeInt(LAi_GetCharacterHP(_chr)) + " / " + MakeInt(LAi_GetCharacterMaxHP(_chr));

    GameInterface.(_tabName).tr3.UserData.ID = "Reputation";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Reputation";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Reputation");
	GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetReputationName(sti(_chr.reputation)));
	GameInterface.(_tabName).tr3.td3.scale = 0.8;
	GameInterface.(_tabName).tr3.td3.textoffset = "0,-1";

    GameInterface.(_tabName).tr4.UserData.ID = "Loyality";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Loyality";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Loyality");
	if (_chr.id == pchar.id)
	{
		GameInterface.(_tabName).tr4.td3.str = "-";
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.str = XI_ConvertString(GetLoyalityName(makeint(GetCharacterLoyality(_chr) * 100 / MAX_LOYALITY)));
	}
	GameInterface.(_tabName).tr4.td3.scale = 0.78;

	GameInterface.(_tabName).tr5.UserData.ID = "weight";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "weight";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("weight");
	GameInterface.(_tabName).tr5.td3.str = FloatToString(GetItemsWeight(_chr), 1) + " / "+GetMaxItemsWeight(_chr);
	GameInterface.(_tabName).tr5.td3.scale = 0.8;

	// прорисовка
	Table_UpdateWindow(_tabName);
}
void SetSPECIALMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     diff, skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	row = "tr1";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);

		GameInterface.(_tabName).(row).(col).fontidx = 0;
		//#20170627-01
		GameInterface.(_tabName).(row).(col).scale = 0.65;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-6";
		GameInterface.(_tabName).(row).(col).str = XI_ConvertString(skillName + "T");
	}
	row = "tr2";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
        skillVal = GetCharacterSPECIAL(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		//#20170627-01
		GameInterface.(_tabName).(row).(col).scale = 1.0;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-4";
		GameInterface.(_tabName).(row).(col).align = "center";

		diff = skillVal - GetSkillValue(_chr, SPECIAL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	row = "tr3";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
		GameInterface.(_tabName).(row).(col).icon.offset = "0,0";
	}
	row = "tr4";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		//#20170627-01
		GameInterface.(_tabName).(row).(col).scale = 0.8;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-4";
		GameInterface.(_tabName).(row).(col).align = "center";

		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}

	row = "tr5";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
		GameInterface.(_tabName).(row).(col).icon.offset = "0,0";
	}
	row = "tr6";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		//#20170627-01
		GameInterface.(_tabName).(row).(col).scale = 0.8;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-4";
		GameInterface.(_tabName).(row).(col).align = "center";

		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

// опыт команды нпс _chr
void SetCrewExpTable(ref _chr, string _tabName, string _bar1, string _bar2, string _bar3)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=3; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.scale = 0.8;
		//GameInterface.(_tabName).(row).td3.textoffset = "0,1";
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Sailors";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Class";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Sailors");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr1.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Sailors)));
	}
	else
	{
		GameInterface.(_tabName).tr1.td3.str = "";
	}

	GameInterface.(_tabName).tr2.UserData.ID = "Cannoners";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr2.td1.icon.image = "Cannons skill icon";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Cannoners");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr2.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Cannoners)));
	}
		else
	{
		GameInterface.(_tabName).tr2.td3.str = "";
	}

    GameInterface.(_tabName).tr3.UserData.ID = "Soldiers";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr3.td1.icon.image = "grappling skill icon";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Soldiers");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Soldiers)));
	}
		else
	{
		GameInterface.(_tabName).tr3.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);

	///  прогресбары
	GameInterface.StatusLine.(_bar1).Max   = 100;
    GameInterface.StatusLine.(_bar1).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar1).Value = sti(_chr.Ship.Crew.Exp.Sailors);
    }
    else
    {
    	GameInterface.StatusLine.(_bar1).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar1,0);

    GameInterface.StatusLine.(_bar2).Max   = 100;
    GameInterface.StatusLine.(_bar2).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar2).Value = sti(_chr.Ship.Crew.Exp.Cannoners);
    }
    else
    {
    	GameInterface.StatusLine.(_bar2).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar2,0);

    GameInterface.StatusLine.(_bar3).Max   = 100;
    GameInterface.StatusLine.(_bar3).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar3).Value = sti(_chr.Ship.Crew.Exp.Soldiers);
    }
    else
    {
    	GameInterface.StatusLine.(_bar3).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar3,0);
}

void SetShipOTHERTable(string _tabName, ref _chr)
{
    int     i;
	string  row;

    int iShip = sti(_chr.ship.type);
	ref refBaseShip = GetRealShip(iShip);

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=10; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 24;
    	GameInterface.(_tabName).(row).td1.icon.height = 24;
    	GameInterface.(_tabName).(row).td1.icon.offset = "2, 1";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "0,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.scale = 0.8;
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Hull";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Hull";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Hull");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.ship.hp) + " / " + sti(refBaseShip.hp);
    if (!CheckAttribute(&RealShips[iShip], "Tuning.HP"))
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr2.UserData.ID = "Sails";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Sails";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Sails");
	GameInterface.(_tabName).tr2.td3.str = sti(_chr.ship.sp) + " / " + sti(refBaseShip.sp);

	GameInterface.(_tabName).tr3.UserData.ID = "MastHP";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "MastHP";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("MastHP");
	GameInterface.(_tabName).tr3.td3.str = FloatToString(stf(refBaseShip.MastMultiplier),2);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.MastMultiplier"))
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,128,200,225);
	}

    GameInterface.(_tabName).tr4.UserData.ID = "Speed";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Speed";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Speed");
	if (IsCompanion(_chr))
	{
		GameInterface.(_tabName).tr4.td3.str = FloatToString(FindShipSpeed(_chr),2) + " / " + FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr4.td3.str = FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.SpeedRate"))
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,128,200,225);
	}


    GameInterface.(_tabName).tr5.UserData.ID = "Maneuver";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "Maneuver";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("Maneuver");
	if (IsCompanion(_chr))
	{
  		GameInterface.(_tabName).tr5.td3.str = FloatToString((stf(refBaseShip.turnrate) * FindShipTurnRate(_chr)), 2) + " / " + FloatToString(stf(refBaseShip.TurnRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr5.td3.str = FloatToString(stf(refBaseShip.TurnRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.TurnRate"))
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr6.UserData.ID = "AgainstWind";
	GameInterface.(_tabName).tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr6.td1.icon.image = "AgainstWind";
	GameInterface.(_tabName).tr6.td2.str = XI_ConvertString("AgainstWind");
	GameInterface.(_tabName).tr6.td3.str = FloatToString(stf(refBaseShip.WindAgainstSpeed),2);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.WindAgainstSpeed"))
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,128,200,225);
	}


	RecalculateCargoLoad(_chr);
	GameInterface.(_tabName).tr7.UserData.ID = "Capacity";
	GameInterface.(_tabName).tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr7.td1.icon.image = "Capacity";
	GameInterface.(_tabName).tr7.td2.str = XI_ConvertString("Capacity");
	GameInterface.(_tabName).tr7.td3.str = GetCargoLoad(_chr) + " / " + GetCargoMaxSpace(_chr);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.Capacity"))
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr8.UserData.ID = "Crew";
	GameInterface.(_tabName).tr8.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr8.td1.icon.image = "Crew";
	GameInterface.(_tabName).tr8.td2.str = XI_ConvertString("Crew");
	GameInterface.(_tabName).tr8.td3.str = GetCrewQuantity(_chr) + " : "+ sti(refBaseShip.MinCrew) +" / " + sti(refBaseShip.OptCrew);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.MaxCrew"))
	{
		GameInterface.(_tabName).tr8.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr8.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr9.UserData.ID = "sCannons";
	GameInterface.(_tabName).tr9.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr9.td1.icon.image = "Caliber";
	GameInterface.(_tabName).tr9.td2.str = XI_ConvertString("sCannons"); //XI_ConvertString("Caliber");
	GameInterface.(_tabName).tr9.td3.str = XI_ConvertString("caliber" + refBaseShip.MaxCaliber) + " / " + sti(refBaseShip.CannonsQuantity);

	if (!CheckAttribute(&RealShips[iShip], "Tuning.Cannon"))
	{
		GameInterface.(_tabName).tr9.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr9.td3.color = argb(255,128,200,225);
	}

	GameInterface.(_tabName).tr10.UserData.ID = "CannonType";
	GameInterface.(_tabName).tr10.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr10.td1.icon.image = "Cannons";
	GameInterface.(_tabName).tr10.td2.str = XI_ConvertString(GetCannonType(sti(_chr.Ship.Cannons.Type)) + "s2");
	if (sti(_chr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
	{
		if(GetCannonsNum(_chr) > 0)
		{
		GameInterface.(_tabName).tr10.td3.str = XI_ConvertString("caliber" + GetCannonCaliber(sti(_chr.Ship.Cannons.Type))) + " / " + GetCannonsNum(_chr);
	}
	else
	{
			GameInterface.(_tabName).tr10.td3.str = GetCannonsNum(_chr);
		}
	}
	else
	{
	    GameInterface.(_tabName).tr10.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

void SetShipQualityTable(ref _chr, string _bar1, string _bar7, string _bar2, string _bar3, string _bar4, string _bar5, string _bar6)
{
	int iShip = sti(_chr.ship.type);
	float fHP = 100;
	float fMast = 100;
	float fSpeedRate = 100;
	float fTurnRate = 100;
	float fWAS = 100;
	float fCapacity = 100;
	float fCrew = 100;
	ref refShip = GetRealShip(iShip);

	if (sti(refShip.BaseType) <= SHIP_OCEAN)//рассчитываем качество только для НЕквестовых кораблей
	{
		ref rBaseShip = GetShipByType(sti(refShip.BaseType));
		float fTemp;

		fTemp = stf(refShip.Capacity);
		if (CheckAttribute(refShip, "Untuned.Capacity")) fTemp = refShip.Untuned.Capacity;
		fCapacity = 50 * (fTemp - stf(rBaseShip.Capacity)) / (stf(rBaseShip.Capacity) * SHIP_STAT_RANGE_MAX) + 50;

		fTemp = stf(refShip.HP);
		if (CheckAttribute(refShip, "Untuned.HP")) fTemp = refShip.Untuned.HP;
		fHP = 50 * (fTemp - stf(rBaseShip.HP)) / (stf(rBaseShip.HP) * SHIP_STAT_RANGE_MAX) + 50;

		fTemp = stf(refShip.SpeedRate);
		if (CheckAttribute(refShip, "Untuned.SpeedRate")) fTemp = refShip.Untuned.SpeedRate;
		fSpeedRate = 50 * (fTemp - stf(rBaseShip.SpeedRate)) / (stf(rBaseShip.SpeedRate) * SHIP_STAT_RANGE_MAX) + 50;

		fTemp = stf(refShip.TurnRate);
		if (CheckAttribute(refShip, "Untuned.TurnRate")) fTemp = refShip.Untuned.TurnRate;
		fTurnRate = 50 * (fTemp - stf(rBaseShip.TurnRate)) / (stf(rBaseShip.TurnRate) * SHIP_STAT_RANGE_MAX) + 50;

		fTemp = stf(refShip.MastMultiplier);
		if (CheckAttribute(refShip, "Untuned.MastMultiplier")) fTemp = refShip.Untuned.MastMultiplier;
		fMast = 50 * (stf(rBaseShip.MastMultiplier) - fTemp) / 0.3 + 50;

		fTemp = stf(refShip.WindAgainstSpeed);
		if (CheckAttribute(refShip, "Untuned.WindAgainstSpeed")) fTemp = refShip.Untuned.WindAgainstSpeed;
		fWAS = 50 * (fTemp - stf(rBaseShip.WindAgainstSpeed)) / (stf(rBaseShip.WindAgainstSpeed) * SHIP_STAT_RANGE_MAX) + 50;

		fTemp = stf(refShip.OptCrew); 	//тюнинг не влияет на оптимальную
		fCrew = 50 * (fTemp - stf(rBaseShip.OptCrew)) / (stf(rBaseShip.OptCrew) * SHIP_STAT_RANGE_MAX) + 50;
	}

	GameInterface.StatusLine.(_bar1).Max   = 100;
	GameInterface.StatusLine.(_bar1).Min   = 0;
	GameInterface.StatusLine.(_bar1).Value = fHP;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar1,0);

	GameInterface.StatusLine.(_bar2).Max   = 100;
	GameInterface.StatusLine.(_bar2).Min   = 0;
	GameInterface.StatusLine.(_bar2).Value = fSpeedRate;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar2,0);

	GameInterface.StatusLine.(_bar3).Max   = 100;
	GameInterface.StatusLine.(_bar3).Min   = 0;
	GameInterface.StatusLine.(_bar3).Value = fTurnRate;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar3,0);

	GameInterface.StatusLine.(_bar4).Max   = 100;
	GameInterface.StatusLine.(_bar4).Min   = 0;
	GameInterface.StatusLine.(_bar4).Value = fWAS;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar4,0);

	GameInterface.StatusLine.(_bar5).Max   = 100;
	GameInterface.StatusLine.(_bar5).Min   = 0;
	GameInterface.StatusLine.(_bar5).Value = fCapacity;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar5,0);

	GameInterface.StatusLine.(_bar6).Max   = 100;
	GameInterface.StatusLine.(_bar6).Min   = 0;
	GameInterface.StatusLine.(_bar6).Value = fCrew;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar6,0);

	GameInterface.StatusLine.(_bar7).Max   = 100;
	GameInterface.StatusLine.(_bar7).Min   = 0;
	GameInterface.StatusLine.(_bar7).Value = fMast;
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar7,0);
}

void SetFoodShipInfo(ref chr, string _textName)
{
	int iColor, iFood;
	string sText;

	SetFormatedText(_textName, "");
	if (sti(chr.ship.type) != SHIP_NOTUSED)
	{
		sText = "Провианта на корабле на ";
		iFood = CalculateShipFood(chr);
		sText = sText + FindRussianDaysString(iFood);
		SetFormatedText(_textName, sText);
		if(iFood >= 5)
		{
			iColor = argb(255,255,255,192);
		}
		if(iFood > 10)
		{
			iColor = argb(255,192,255,192);
		}
		if(iFood < 5)
		{
			iColor = argb(255,255,192,192);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, _textName, 8,-1,iColor);
	}
}

void SetSquadronFoodShipInfo(ref chr, string _textName)
{
	int iColor, iFood;
	string sText;

	SetFormatedText(_textName, "");
	if (sti(chr.ship.type) != SHIP_NOTUSED)
	{
		sText = "Провианта на:\n корабле / в эскадре\n на ";
		iFood = CalculateShipFood(chr);
		sText = sText + iFood+" / "+FindRussianDaysString(CalculateFood());
		SetFormatedText(_textName, sText);
		if(iFood >= 5)
		{
			iColor = argb(255,255,255,192);
		}
		if(iFood > 10)
		{
			iColor = argb(255,192,255,192);
		}
		if(iFood < 5)
		{
			iColor = argb(255,255,192,192);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, _textName, 8,-1,iColor);
	}
}

// Warship 11.07.09 Вывести в текстовое поле инфу о количестве дней, на сколько хватит рому на судне
void SetRumShipInfo(ref _character, String _node)
{
	int color, rum;
	String text;

	SetFormatedText(_node, "");

	if(sti(_character.ship.type) != SHIP_NOTUSED)
	{
		text = "Рома на корабле на ";
		rum = CalculateShipRum(_character);
		text = text + FindRussianDaysString(rum);
		SetFormatedText(_node, text);

		if(rum < 3)
		{
			color = argb(255, 255, 192, 192);
		}

		if(rum >= 3)
		{
			color = argb(255, 255, 255, 192);
		}

		if(rum >= 10)
		{
			color = argb(255, 192, 255, 192);
		}

		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, _node, 8, -1, color);
	}
}

int GetTradeItemPrice(string sItemID, int tradeType)
{
	int itmIdx = Items_FindItemIdx(sItemID);
	if (itmIdx < 0 || itmIdx > ITEMS_QUANTITY) return 0;

	int itmprice = GetItemPrice(sItemID);
	if (itmprice < 0) itmprice = 0;

	float skillDelta = GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE);
	float skillModify;
	if(tradeType == PRICE_TYPE_BUY)
	{
		skillModify = 1.45 - skillDelta*0.019;
		if(CheckOfficersPerk(pchar,"Trader")) { skillModify -= 0.05; }
		if(CheckOfficersPerk(pchar,"AdvancedCommerce"))	{ skillModify -= 0.2; }
		else
		{
			if(CheckOfficersPerk(pchar,"BasicCommerce"))	{ skillModify -= 0.1; }
		}
		if(CheckAttribute(&Items[itmIdx],"groupID"))
		{
			if(Items[itmIdx].groupID == BLADE_ITEM_TYPE || Items[itmIdx].groupID == GUN_ITEM_TYPE) skillModify *= 10.0;//меняем после всех перков, иначе скидка от перков непропорциональная
		}
	}
	else
	{
		skillModify = 0.70 + skillDelta*0.019;
		if (CheckOfficersPerk(pchar,"AdvancedCommerce"))	skillModify += 0.05;
		if (CheckOfficersPerk(pchar,"Trader")) { skillModify += 0.05; }
	}

	return makeint(makefloat(itmprice)*skillModify);
}

//--> mod tablesort		Qwerry, St.
//идея необходимости сортировки в таблицах:	DiamiR
//версия для OS		с визуальной индикацией и автозапоминанием и автоопределением параметров		на MS использовалось другое сравнение строк 	strcmp()
void SortTable(string sControl,int iColumn)
{
	int m, n;
	bool bIsString = false;
	string sColumn = "td" + iColumn;
	if (checkattribute(&GameInterface, sControl + ".hr." + sColumn + ".sorttype"))
		{if(GameInterface.(sControl).hr.(sColumn).sorttype == "string") bIsString = true;}
	else return; //если атрибут .sorttype не поставили, значит сортировать не нужно
//TO DO		убрать это деление на строки, автоматически определять - текст или число сортируем

	bool bAsc = true;
	if (checkattribute(&GameInterface, sControl + ".hr." + sColumn + ".sortdir"))
		{if(GameInterface.(sControl).hr.(sColumn).sortdir == "dec") bAsc = false;}
	//атрибут .sortdir = "dec" указываем, если нужно, чтобы при первом клике сортировалось в обратном направлении

	aref aRows;
	makearef(aRows, GameInterface.(sControl));
	//в коде заполнения таблиц не должно быть пустых строк - проверить везде, чтобы все фильтрации выполнялись до первой записи в строчку
	int iLinesCount = 0;
	for (n = 0; n < GetAttributesNum(aRows); n++)
	{
		if (HasSubStr(GetAttributeName(GetAttributeN(aRows, n)), "tr")) iLinesCount++;
	}

	if (iLinesCount < 3) return;//две строки нет смысла сортировать

	if (checkattribute(&GameInterface, sControl + ".hr.sortedColumn"))//таблица уже сортировалось ранее
	{
		if (iColumn == sti(GameInterface.(sControl).hr.sortedColumn)) //повторный клик по той же колонке - просто реверс
		{
			ReverseTable(sControl, iLinesCount);
			if (GameInterface.(sControl).hr.(sColumn).icon.image  == "downbutton") bAsc = true; else bAsc = false;
			DrawSortDir(sControl, iColumn, bAsc);
			return;
		}
		string sTemp = sControl + ".hr.td" + GameInterface.(sControl).hr.sortedColumn + ".icon";
		DeleteAttribute(&GameInterface, sTemp);//стираем стрелку сортировки с предыдушей колонки
	}

trace("SortTable(sControl = " + sControl + ", iColumn = " +  iColumn + ") iLinesCount = " + iLinesCount + ", bIsString = " + bIsString + ", bAsc = " + bAsc);

	string sRow, sNewRow, sSortedString, sLast;
	aref aCurRow, aNextRow, aRow;

	if (sti(GameInterface.(sControl).select))
	{
		sRow = "tr" + GameInterface.(sControl).select;
		sLast = GameInterface.(sControl).(sRow).index;//запоминаем номер выбранной строки, чтобы выделить её же после сортировки
//TO DO везде нужно заполнять индекс
	}

	if (bIsString)//строки
	{
		object oSorted, oTableCopy;
		string sAdd;
		int iAdd;
		for (n = 0; n < iLinesCount; n++)
		{
			sRow = "tr" + (n + 1);
			sSortedString = GameInterface.(sControl).(sRow).(sColumn).str;
			sSortedString = strreplace(sSortedString, ".", ",");//фикс краша из-за точек	подменяем их на запятые
			sAdd = ""; iAdd = 0;
			while (checkattribute(oSorted, sSortedString + sAdd)) {iAdd++; sAdd = DigitsToString(iAdd, 3);}//фикс Краша из-за дубликатов
																//до 1000 одинаковых значений в одной таблице - дальше краш, увеличьте
			sSortedString += sAdd;
			oSorted.(sSortedString) = sRow;
		}
		aref rootItems;
		makearef(rootItems, oSorted);
		sort(rootItems);
		aref aTable, aTableCopy;
		makearef(aTable, GameInterface.(sControl));
		makearef(aTableCopy, oTableCopy.(sControl));
		CopyAttributes(aTableCopy, aTable);
		for (n = 0; n < iLinesCount; n++)
		{
			sRow = "tr" + (n + 1);
			makearef(aCurRow, aTable.(sRow));
			sNewRow = GetAttributeValue(GetAttributeN(rootItems, n));
			makearef(aNextRow, aTableCopy.(sNewRow));
			CopyAttributes(aCurRow, aNextRow);
		}
		if (!bAsc) ReverseTable(sControl, iLinesCount); //нужна было сортировка по убыванию
	}
	else//числа
	{
		string sCurRow, sNextRow;
		sRow = "trx";//пузырёк
//TO DO		полный двойной цикл - поискать более оптимальную сортировку
		for (m = 0; m < iLinesCount-1; m++)
		{
			for (n = 0; n < iLinesCount-1; n++)
			{
				sCurRow = "tr" + (n + 1);
				sNextRow = "tr" + (n + 2);
				if (bAsc)//по возрастанию
				{
				if (stf(GameInterface.(sControl).(sCurRow).(sColumn).str) > stf(GameInterface.(sControl).(sNextRow).(sColumn).str))
					{
					makearef(aRow, GameInterface.(sControl).(sRow));
					makearef(aCurRow, GameInterface.(sControl).(sCurRow));
					makearef(aNextRow, GameInterface.(sControl).(sNextRow));
					CopyAttributes(aRow, aCurRow);
					CopyAttributes(aCurRow, aNextRow);
					CopyAttributes(aNextRow, aRow);
					}
				}
				else
				{
					if (stf(GameInterface.(sControl).(sCurRow).(sColumn).str) < stf(GameInterface.(sControl).(sNextRow).(sColumn).str))
					{
					makearef(aRow, GameInterface.(sControl).(sRow));
					makearef(aCurRow, GameInterface.(sControl).(sCurRow));
					makearef(aNextRow, GameInterface.(sControl).(sNextRow));
					CopyAttributes(aRow, aCurRow);
					CopyAttributes(aCurRow, aNextRow);
					CopyAttributes(aNextRow, aRow);
					}
				}
			}
		}
		DeleteAttribute(&GameInterface, sControl + "." + sRow);//удаляем пузырёк, будет портить число строк в таблице
	}
	DrawSortDir(sControl, iColumn, bAsc);
	ResetSelectedRow(sControl, sLast, iLinesCount)
}

void DrawSortDir(string sControl, int iColumn, bool bAsc)
{
	string sColumn = "td" + iColumn;
	GameInterface.(sControl).hr.(sColumn).icon.group  = "MAIN_ICONS";//рисуем стрелку направления сортировки
	GameInterface.(sControl).hr.(sColumn).icon.width  = 8;
	GameInterface.(sControl).hr.(sColumn).icon.height = 16;
	GameInterface.(sControl).hr.(sColumn).icon.valign = "bottom";
	GameInterface.(sControl).hr.(sColumn).icon.offset = "0,8";//смещаем на половину высоты ниже границы между заголовком и первой строкой	//Тут проблема - есть же таблицы, где заголовок спрятан - проверить
	if 	(bAsc) 	GameInterface.(sControl).hr.(sColumn).icon.image  = "upbutton";
		else	GameInterface.(sControl).hr.(sColumn).icon.image  = "downbutton"; //при изменении картинки - менять и чуть выше, искать: 	.icon.image  == "
	GameInterface.(sControl).hr.sortedColumn = iColumn;
}

void ReverseTable(string sControl,int iLinesCount)
{
	string sFirstRow, sLastRow;
	string sRow = "trx";
	aref aFirstRow, aLastRow, aRow;
	for (int n = 0; n < iLinesCount/2; n++)
	{
		sFirstRow = "tr" + (n + 1);
		sLastRow = "tr" + (iLinesCount - n);
		makearef(aRow, GameInterface.(sControl).(sRow));
		makearef(aFirstRow, GameInterface.(sControl).(sFirstRow));
		makearef(aLastRow, GameInterface.(sControl).(sLastRow));
		CopyAttributes(aRow, aFirstRow);
		CopyAttributes(aFirstRow, aLastRow);
		CopyAttributes(aLastRow, aRow);
	}
	if (sti(GameInterface.(sControl).select))//не меняем, если было 0
	{
		n = iLinesCount + 1 - sti(GameInterface.(sControl).select);
		GameInterface.(sControl).select = n;
	}
	DeleteAttribute(&GameInterface, sControl + "." + sRow);//удаляем пузырёк, будет портить число строк в таблице
}

void ResetSelectedRow(string sControl, string sLastIdx, int iLinesCount)
{
	string sRow;
	if (sti(GameInterface.(sControl).select))//не меняем, если было 0, т.е. ничего не выделено
	{
		for (int n = 1; n <= iLinesCount; n++)
		{
			sRow = "tr" + n;
			if (GameInterface.(sControl).(sRow).index == sLastIdx)
			{
				GameInterface.(sControl).select = n;
				break;
			}
		}
	}
}
//<-- mod tablesort
