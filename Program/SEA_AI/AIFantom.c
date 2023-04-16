#define FANTOM_SHIPS_QTY 150
#define INVALID_SHIP_TYPE			-1

int seaFantomsNum; // mitrokosta перенес из глобалов
int seaFantoms[MAX_SHIPS_ON_SEA];

ref CreateSeaFantom() {
	int index = FindFirstEmptyCharacter();
	seaFantoms[seaFantomsNum] = index;
	seaFantomsNum++;
	return GetCharacter(index);
}

void ClearSeaFantoms() {
	for (int i = 0; i < seaFantomsNum; i++) {
		int index = seaFantoms[i];
		if (!CheckAttribute(GetCharacter(index),"lifeday")) continue;
		InitCharacter(GetCharacter(index), index);
		FreeCharacter(index);
	}
	
	seaFantomsNum = 0;
}
// -> ugeen 26.01.09
int Fantom_GenerateEncounterExt(string sGroupName, int iEType, int iNumWarShips, int iNumMerchantShips, int iNation)
{
	aref	aWar, aMerchant;
	ref		rEnc;
	int		i;
	int		iWarClassMax, iWarClassMin, iMerchantClassMax, iMerchantClassMin;

	makeref(rEnc, EncountersTypes[iEType]);
	makearef(aWar, rEnc.War);
	makearef(aMerchant, rEnc.Merchant);

	if(iEType == ENCOUNTER_TYPE_BARREL || iEType == ENCOUNTER_TYPE_BOAT)
	{
		ref rFantom = CreateSeaFantom();

		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		rFantom.SeaAI.Group.Name = sGroupName;
		return 0;
	}

	int iRank = sti(pchar.Rank);
	Encounter_GetClassesFromRank(iEType, iRank, &iMerchantClassMin, &iMerchantClassMax, &iWarClassMin, &iWarClassMax);

	int iFantomIndex, iShipType;

	for (i=0; i<iNumMerchantShips; i++)
	{
		iShipType = Fantom_GetShipTypeExt(iMerchantClassMin, iMerchantClassMax, "Merchant", sGroupName, "Trade", iEType, iNation );
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	for (i=0; i<iNumWarShips; i++)
	{
		iShipType = Fantom_GetShipTypeExt(iWarClassMin, iWarClassMax, "War", sGroupName, "War", iEType, iNation);
		if (iShipType == INVALID_SHIP_TYPE) continue;
	}

	return iNumWarShips + iNumMerchantShips;
}

int Fantom_GenerateShips_ForEnc_v2(ref rEnc, int iEType, string sGroupName)//iEType вообще не нужен??? просто не ставить атрибут новой системы на эти типы энок и они будут работать по старой функции
{																			//хотя - это бред. всё равно старую полностью вырежем
	ref rFantom;
	int iShipSum = 0;
	if(iEType == ENCOUNTER_TYPE_BARREL || iEType == ENCOUNTER_TYPE_BOAT)
	{
		rFantom = CreateSeaFantom();

		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");

		rFantom.SeaAI.Group.Name = sGroupName;
		iNumFantoms++;
		return 0;
	}

	aref arShips, arShipModes, arShipType;
	makearef(arShips, rEnc.shiptypes);
	makearef(arShipModes, rEnc.shipmodes);
	int iShipType;
	string sFantomType;

	for (int i=0; i<GetAttributesNum(arShips); i++)
	{
		rFantom = CreateSeaFantom();

		DeleteAttribute(rFantom, "relation");
		DeleteAttribute(rFantom, "abordage_twice");
		DeleteAttribute(rFantom, "QuestDate");
		DeleteAttribute(rFantom, "ransom");
		DeleteAttribute(rFantom, "DontRansackCaptain");

		iShipType = GetAttributeValue(GetAttributeN(arShips, i));
		sFantomType = GetAttributeValue(GetAttributeN(arShipModes, i));
		rFantom.Ship.Type = GenerateShipExt(iShipType, 0, rFantom);
		rFantom.Ship.Mode = sFantomType;
		rFantom.SeaAI.Group.Name = sGroupName;
		rFantom.Charge.Type = GOOD_BALLS;

		iNumFantoms++;
		iShipSum++;
	}
	return iShipSum;
}

int Fantom_GetShipTypeExt(int iClassMin, int iClassMax, string sShipType, string sGroupName, string sFantomType, int iEncounterType, int iNation)
{
	int iShips[FANTOM_SHIPS_QTY];
	int i, iShipsNum;
	iShipsNum = 0;
	aref aNation;
	string sAttr;
	bool bOk;

	for (i=SHIP_TARTANE; i<=SHIP_OCEAN; i++)  //энкаунтеры только до мановара, квестовые корабли отдельно
	{
		object rShip = GetShipByType(i);
		if (!checkAttribute(rship, "class"))
		{
		trace ("bad ship is: " + rship.name);
		}
		int iClass = MakeInt(rShip.Class);

		if (iClass > iClassMin) { continue; }
		if (iClass < iClassMax) { continue; }
		if (sti(rShip.CanEncounter) != true) { continue; }
		if (sti(rShip.Type.(sShipType)) != true) { continue; }
		bOk = false;
		if(CheckAttribute(rShip, "nation"))
		{
		makearef(aNation, rShip.nation);
		int q = GetAttributesNum(aNation);
		for(int j = 0; j < q; j++)
		{
		sAttr = GetAttributeName(GetAttributeN(aNation, j));
		if(GetNationTypeByName(sAttr) == iNation && rShip.nation.(sAttr) == true ) bOk = true;
		}
		}
		if(!bOk) { continue; }

		iShips[iShipsNum] = i;
		iShipsNum++;
	}
	if (iShipsNum==0)
	{
		Trace("Can't find ship type '" + sShipType + "' with ClassMin = " + iClassMin + " and ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}

	int iBaseShipType = iShips[rand(iShipsNum - 1)];

	ref rFantom = CreateSeaFantom();

	DeleteAttribute(rFantom, "relation");
	DeleteAttribute(rFantom, "abordage_twice");
	DeleteAttribute(rFantom, "QuestDate");
	DeleteAttribute(rFantom, "ransom");
	DeleteAttribute(rFantom, "DontRansackCaptain");

	rFantom.SeaAI.Group.Name = sGroupName;
	rFantom.Ship.Mode = sFantomType;
	rFantom.Charge.Type = GOOD_BALLS;



	int iRealShipType = GenerateShipExt(iBaseShipType, 0, rFantom);

	rFantom.Ship.Type = iRealShipType;

	return iRealShipType;

}
// -> ugeen 26.01.09

int Fantom_GenerateEncounter(string sGroupName, object oResult, int iEType, int iNumWarShips, int iNumMerchantShips)
{
	aref	aWar, aMerchant;
	ref		rEnc;
	int		i;
	int		iWarClassMax, iWarClassMin, iMerchantClassMax, iMerchantClassMin;

	makeref(rEnc, EncountersTypes[iEType]);
	makearef(aWar, rEnc.War);
	makearef(aMerchant, rEnc.Merchant);

	int iRank = sti(pchar.Rank);
	Encounter_GetClassesFromRank(iEType, iRank, &iMerchantClassMin, &iMerchantClassMax, &iWarClassMin, &iWarClassMax);

	int iFantomIndex, iShipType;

	for (i=0; i<iNumMerchantShips; i++)
	{
		iShipType = Fantom_GetShipType(iMerchantClassMin, iMerchantClassMax, "Merchant");
		if (iShipType == INVALID_SHIP_TYPE) continue;
		Fantom_AddFantomCharacter(sGroupName, iShipType, "Trade", iEType);
	}

	for (i=0; i<iNumWarShips; i++)
	{
		iShipType = Fantom_GetShipType(iWarClassMin, iWarClassMax, "War");
		if (iShipType == INVALID_SHIP_TYPE) continue;
		Fantom_AddFantomCharacter(sGroupName, iShipType, "War", iEType);
	}

	return iNumWarShips + iNumMerchantShips;
}

int Fantom_GetShipType(int iClassMin, int iClassMax, string sShipType)
{
	int iShips[FANTOM_SHIPS_QTY];
	int i, iShipsNum;
	iShipsNum = 0;

	for (i=SHIP_TARTANE; i<=SHIP_OCEAN; i++)  //энкаунтеры только до мановара, квестовые корабли отдельно
	{
		object rShip = GetShipByType(i);
		if (!checkAttribute(rship, "class"))
		{
			trace ("bad ship is: " + rship.name);
		}
		int iClass = MakeInt(rShip.Class);

		if (iClass > iClassMin) { continue; }
		if (iClass < iClassMax) { continue; }
		if (sti(rShip.CanEncounter) != true) { continue; }
		if (sti(rShip.Type.(sShipType)) != true) { continue; }
		iShips[iShipsNum] = i;
		iShipsNum++;
	}
	if (iShipsNum==0)
	{
		Trace("Can't find ship type '" + sShipType + "' with ClassMin = " + iClassMin + " and ClassMax = " + iClassMax);
		return INVALID_SHIP_TYPE;
	}

	int iBaseShipType = iShips[rand(iShipsNum - 1)];
	//trace(ShipsTypes[iBaseShipType].name);
	int iRealShipType = GenerateShip(iBaseShipType, 0);
	return iRealShipType;
}

// return new added fantom character
// мктод этот походу левый, тк перекрывается в сиа.с
void Fantom_AddFantomCharacter(string sGroupName, int iShipType, string sFantomType, int iEncounterType)
{
	ref rFantom = CreateSeaFantom();



	DeleteAttribute(rFantom, "relation");
	DeleteAttribute(rFantom, "abordage_twice");
	DeleteAttribute(rFantom, "QuestDate");
	DeleteAttribute(rFantom, "ransom");
	DeleteAttribute(rFantom, "DontRansackCaptain");

	//#20170912-02 Fix for RealShips/Character sails
    	DeleteAttribute(rFantom, "ship.sails");
    	//#20170918-01 Fix for Abordage.Enable
    	DeleteAttribute(rFantom, "Abordage.Enable");

	rFantom.SeaAI.Group.Name = sGroupName;
	rFantom.Ship.Type = iShipType;
	rFantom.Ship.Mode = sFantomType;
	rFantom.Charge.Type = GOOD_BALLS;
}
// на деле этот метод бесполезен, тк золото в сундуке генерится в др месте, а то что, в к3 тут были распределения опыта и команды вообще позорище.
void Fantom_SetRandomMoney(ref rFantom, string sFantomType)
{
	// clear money from character
	rFantom.Money = 0;

	//GenerateBootyItems(rFantom); // to_do del
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix

    int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	// clear money from character
	rFantom.Money = 0;

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	switch (sFantomType)
	{
		case "trade":
			rFantom.Money = (10 - iSClass) * 100 + rand((10 - iSClass) * 800);
			return;
		break;
		case "war":
			rFantom.Money = (10 - iSClass) * 40 + rand((10 - iSClass) * 350);
			return;
		break;
		case "pirate":
		    rFantom.Money = (10 - iSClass) * 80 + rand((10 - iSClass) * 500);
			return;
		break;
	}
}

// boal перенес из ВМЛ
int Fantom_CalcSkill(ref rMainCharacter, string sSkill, int iShipClass, int iSkillMin, int iSkillMax, int iSClass7, int iSClass6, int iSClass5, int iSClass4, int iSClass3, int iSClass2, int iSClass1)
// Stone-D : It was all backwards!
{
	int iSkill = GetSummonSkillFromName(rMainCharacter, sSkill);
    // boal 15.03.04 -->
    int minSkillLevel = 0;
	iSkill = iSkill + iSkillMin + rand(iSkillMax - iSkillMin);
	switch (iShipClass)
	{
		case 1: minSkillLevel =  iSClass1; break;
		case 2: minSkillLevel =  iSClass2; break;
		case 3: minSkillLevel =  iSClass3; break;
		case 4: minSkillLevel =  iSClass4; break;
		case 5: minSkillLevel =  iSClass5; break;
		case 6: minSkillLevel =  iSClass6; break;
		case 7: minSkillLevel =  iSClass7; break;
	}
	minSkillLevel = minSkillLevel*10; // приведение скила к 1-100

    if (iSkill < minSkillLevel)	iSkill = minSkillLevel;
    // boal 15.03.04 <--
	if (iSkill < 1)		    	iSkill = 1;
	if (iSkill > SKILL_MAX)     iSkill = SKILL_MAX;
	return iSkill;
}

void Fantom_SetCannons(ref rFantom, string sFantomType)
{
	ref rShip = GetRealShip(GetCharacterShipType(rFantom));
	if (sti(rShip.Cannon) == CANNON_TYPE_NONECANNON)
	{
		rFantom.Ship.Cannons.Type = CANNON_TYPE_NONECANNON;
		return;
	}

	int iCaliber = sti(rShip.MaxCaliber);
    switch(iCaliber)
	{
		case 8: iCaliber = 0; break;
		case 10: iCaliber = 1; break;
		case 12: iCaliber = 2; break;
		case 16: iCaliber = 3; break;
		case 20: iCaliber = 4; break;
		case 24: iCaliber = 5; break;
		case 28: iCaliber = 6; break;
		case 32: iCaliber = 7; break;
		case 36: iCaliber = 8; break;
		case 42: iCaliber = 9; break;
	}
	if (iCaliber > 0)
	{
		if (sFantomType == "trade" && iCaliber > 3) iCaliber -= 1 + rand(iCaliber/4); //понижение калибра торговым
	}
	else
	{
		iCaliber = 0;
	}
	switch(iCaliber)
	{
		case 0: iCaliber = 8; break;
		case 1: iCaliber = 10; break;
		case 2: iCaliber = 12; break;
		case 3: iCaliber = 16; break;
		case 4: iCaliber = 20; break;
		case 5: iCaliber = 24; break;
		case 6: iCaliber = 28; break;
		case 7: iCaliber = 32; break;
		case 8: iCaliber = 36; break;
		case 9: iCaliber = 42; break;
	}
	if (iCaliber < 8) iCaliber = 8;
	if (iCaliber > sti(rShip.MaxCaliber)) { iCaliber=sti(rShip.MaxCaliber); }

	string sCannonType = "cannon";
	switch (sFantomType)
	{
        case "trade":
		    if (rand(1000) < 800) {sCannonType = "culverine";} else {sCannonType = "cannon";}
		break;

		case "war":
		    if (rand(1000) < 200) {sCannonType = "culverine";} else {sCannonType = "cannon";}
	    break;

		case "pirate":
		    if (rand(1000) < 400) {sCannonType = "culverine";} else {sCannonType = "cannon";}
	    break;
	}
	if (iCaliber == 42) sCannonType = "cannon";

	rFantom.Ship.Cannons.Type = GetCannonByTypeAndCaliber(sCannonType, iCaliber);
}

void Fantom_SetSails(ref rFantom, string sFantomType)
{
	rFantom.Ship.Sails.Gerald = false;
	if (sFantomType == "war") rFantom.Ship.Sails.Gerald = true;
}

void Fantom_SetBalls(ref rFantom, string sFantomType)
{
	int iKClass = 7 - GetCharacterShipClass(rFantom);
	float fK = 2;	
	
	int nShipType = sti(rFantom.ship.type);
	ref refBaseShip = GetRealShip(nShipType);
	int iCannons = sti(refBaseShip.CannonsQuantity);
	int iCrew, iPlanks;
	
	if (iKClass <= 0) fK = 0.7; // баркас
	switch (sFantomType)
	{
		case "war":
			iCrew = GetMaxCrewQuantity(rFantom);
			iPlanks = 130;
			fK = fK * 1.5;
		break;
		case "trade":
			iCrew = GetOptCrewQuantity(rFantom);
			fK = fK * 0.7;
			iPlanks = 20;
		break;
		case "pirate":
			iCrew = GetMaxCrewQuantity(rFantom);
			fK = fK * 1.0;
			iPlanks = 70;
		break;
	}
	iKClass = iKClass * fK;
    // boal 20.01.2004 -->
	Fantom_SetCharacterGoods(rFantom, GOOD_BALLS,    MakeInt(19 * iCannons * fK + rand(MakeInt(10 * iKClass))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_BOMBS,    MakeInt(11 * iCannons * fK + rand(MakeInt(20 * iKClass))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_KNIPPELS, MakeInt(9 * iCannons * fK + rand(MakeInt(10 * iKClass))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_GRAPES,   MakeInt(7 * iCannons * fK + rand(MakeInt(10 * iKClass))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_POWDER,   MakeInt(35 * iCannons * fK + rand(MakeInt(30 * iKClass))), 0);

	Fantom_SetCharacterGoods(rFantom, GOOD_SAILCLOTH, 	MakeInt(50 * iKClass + rand(MakeInt(10 * iKClass))), 0);
	Fantom_SetCharacterGoods(rFantom, GOOD_PLANKS, 		MakeInt(iPlanks * iKClass + rand(MakeInt(20 * iKClass))), 0);

    Fantom_SetCharacterGoods(rFantom, GOOD_FOOD, 		MakeInt(60 + 20 * iKClass + rand(MakeInt(8 * iKClass))), 0);  //WW
    Fantom_SetCharacterGoods(rFantom, GOOD_WEAPON, 		MakeInt(iCrew + rand(MakeInt(8 * iKClass))), 0);   //WW
    Fantom_SetCharacterGoods(rFantom, GOOD_RUM, 		MakeInt(60 + 12 * iKClass + rand(MakeInt(8 * iKClass))), 0);  //WW
    Fantom_SetCharacterGoods(rFantom, GOOD_MEDICAMENT, 	MakeInt(iCrew + rand(MakeInt(10 * iKClass))), 0);   //WW
    // boal 20.01.2004 <--
}

void Fantom_SetGoods(ref rFantom, string sFantomType)
{
 	int iMultiply = 10;
	int iRandMultiply = 1;
    int iShipClass = 7 - GetCharacterShipClass(rFantom);  // для баркаса = 0
    // boal 20.01.2004 -->
    int iStart = GOOD_PLANKS + 1;
	int iFinish = GOOD_CANNON_8 - iStart - 1; // исключая пушки
	int i, iGoods, iRandGoods, iGoodName, iGoodQuantity;
	float fModifikator = 0.0;
	bool isLock;
	bool bOk = false;

	if(CheckAttribute(rFantom, "situation")) bOk = true;

	switch (sFantomType)
    {
		case "war":  // на военных кораблях золото и серебро теперь не возят !!!!
		    iMultiply = (rand(5)+5) * (rand(iShipClass) + 1);
			iRandMultiply = 1 + rand(iShipClass);
			iRandGoods = rand(4)+1; // может быть от одного до 5-и видов товара (а не строго 3 как было раньше)
			isLock = 0; isLock = isLock || bOk;
			for (i = 0; i < iRandGoods; i++)
			{
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish - 2), iMultiply * rand(iRandMultiply * 3), isLock);
			}
		break;
		case "trade":
			if (CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_ESCORT_LARGE)
			{
				//генерим товар (может быть до 12-и видов )
				iGoods = rand(6) + 6; // в больших торговых  караванах  до 12-и видов товара
				fModifikator = 0.4 + 12.0/iGoods;
				iMultiply = (rand(10)+iGoods*3) * (rand(iShipClass) + 4);
				iRandMultiply = 2 + rand(iShipClass);
				if (MOD_SKILL_ENEMY_RATE < rand(12))
				{
    					iFinish = GOOD_CANNON_8 - iStart - 1;
				}
				else
				{
					iFinish = GOOD_GOLD - iStart - 1;
				}
				for (i = 0; i < iGoods; i++)
				{
					iGoodName = iStart + rand(iFinish);
					iGoodQuantity = makeint(fModifikator * iMultiply * (1 + rand(iRandMultiply * 3)));
					if(iGoodName == GOOD_GOLD || iGoodName == GOOD_SILVER)
					{
						iRandMultiply = 2 + rand(iShipClass);
						iMultiply = (rand(10)+ 10) * (rand(iShipClass) + 2);
						iGoodQuantity = makeint((fModifikator * 50 + iMultiply * (1 + rand(iRandMultiply * 3)))/(1.2 * MOD_SKILL_ENEMY_RATE));
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
					else
					{
						isLock = 0;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
				}
			}
			else
			{
				iGoods = rand(4) + 4; // у обычных купчишек до 8-и видов товара
				fModifikator = 0.2 + 8.0/iGoods;
				if (CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_MERCHANT_LARGE)
				{
					iGoods = rand(6) + 6; // в торговых  караванах  до 12-и видов товара
					fModifikator = 0.3 + 12.0/iGoods;
				}
				iMultiply = (rand(10)+iGoods*3) * (rand(iShipClass) + 4);
				iRandMultiply = 2 + rand(iShipClass);
				if (MOD_SKILL_ENEMY_RATE < rand(12))
				{
    					iFinish = GOOD_CANNON_8 - iStart - 1;
				}
				else
				{
					iFinish = GOOD_GOLD - iStart - 1;
				}
				for (i = 0; i < iGoods; i++)
				{
					iGoodName = iStart + rand(iFinish);
					iGoodQuantity = makeint(fModifikator * iMultiply * (1+rand(iRandMultiply * 3)));
					if(iGoodName == GOOD_GOLD || iGoodName == GOOD_SILVER)
					{
						iRandMultiply = 2 + rand(iShipClass);
						iMultiply = (rand(10)+ 5) * (rand(iShipClass) + 2);
						iGoodQuantity = makeint((fModifikator * 50 + iMultiply * (1 + rand(iRandMultiply * 3)))/(1.1 * MOD_SKILL_ENEMY_RATE));
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1; isLock = isLock || bOk;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
					else
					{
						isLock = 0; isLock = isLock || bOk;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
					}
				}
			}
		break;
		case "pirate":
			fModifikator = 1.2;
			iMultiply = (rand(10)+3) * (rand(iShipClass) + 1);
			iRandMultiply = 2 + rand(iShipClass);
			iRandGoods = rand(5)+1;
			if (MOD_SKILL_ENEMY_RATE < rand(12))
			{
    				iFinish = GOOD_CANNON_8 - iStart - 1;
			}
			else
			{
				iFinish = GOOD_GOLD - iStart - 1;
			}
			for (i = 0; i < iRandGoods; i++)
			{
				iGoodName = iStart + rand(iFinish);
				iGoodQuantity = makeint(fModifikator * iMultiply * (1+rand(iRandMultiply * 3)));
				if(iGoodName == GOOD_GOLD || iGoodName == GOOD_SILVER)
				{
						iRandMultiply = 2 + rand(iShipClass);
						iMultiply = (rand(10)+ 30) * (rand(iShipClass) + 2);
						iGoodQuantity = makeint((fModifikator * 50 + iMultiply * (1 + rand(iRandMultiply * 3)))/(0.9 * MOD_SKILL_ENEMY_RATE));
						if(iGoodQuantity < 1) iGoodQuantity = 1;
						isLock = 1; isLock = isLock || bOk;
						Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
				}
				else
				{
					isLock = 0; isLock = isLock || bOk;
					Fantom_SetCharacterGoods(rFantom, iGoodName, iGoodQuantity, isLock);
				}
			}
		break;
	}
    // boal 20.01.2004 <--
    // есть ещё осталось место, то дать запасных орудий в трюм -->
    iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
    if (iMultiply != -1)
    {
    	iRandMultiply = rand(6) - 2;  // 0..4 пушки
    	if (iRandMultiply > 0)
    	{
    		Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);
    	}
    }
    // есть ещё осталось место, то дать запасных орудий в трюм <--
	RecalculateCargoLoad(rFantom);
}

void Fantom_SetGoodsOld(ref rFantom, string sFantomType)
{
 	int iMultiply = 10;
	int iRandMultiply = 1;
    int iShipClass = 7 - GetCharacterShipClass(rFantom);  // для баркаса = 0
    // boal 20.01.2004 -->
    int iStart = GOOD_PLANKS + 1;
    int iFinish = GOOD_GOLD - iStart - 1; // исключая пушки, серебро и золото
    int i, iGoods;

    // разрешим золото от сложности
    if (MOD_SKILL_ENEMY_RATE < rand(12))
    {
    	iFinish = GOOD_CANNON_8 - iStart - 1;
    }
	switch (sFantomType)
	{
		case "war":
		    iMultiply = (rand(5)+5) * (rand(iShipClass) + 1);
			iRandMultiply = 1 + rand(iShipClass);
			for (i = 0; i < 3; i++)
			{
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * rand(iRandMultiply * 3), 0);
			}
		break;
		case "trade":
			iGoods = 8;
			if (CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_ESCORT_LARGE)
			{
                iGoods = 12;
                // золото, если повезет
                if (MOD_SKILL_ENEMY_RATE < rand(12))
                {
					iMultiply = (rand(10)+ 10) * (rand(iShipClass) + 1);
	            	iRandMultiply = 1 + rand(iShipClass);
					if (rand(1) == 0)
					{
						Fantom_SetCharacterGoods(rFantom, GOOD_GOLD, 50 + iMultiply * (1 + rand(iRandMultiply * 3)), 1);
					}
					else
					{
			        	Fantom_SetCharacterGoods(rFantom, GOOD_SILVER, 100 + iMultiply * (1 + rand(iRandMultiply * 3)), 1);
			        }
		        }
			}

			if (CheckAttribute(rFantom, "RealEncounterType") && sti(rFantom.RealEncounterType) == ENCOUNTER_TYPE_MERCHANT_LARGE)
            {
                iGoods = 11;
            }
			iMultiply = (rand(10)+iGoods*3) * (rand(iShipClass) + 4);
        	iRandMultiply = 2 + rand(iShipClass);
			for (i = 0; i < iGoods; i++)
			{
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * (1+rand(iRandMultiply * 3)), 0);
			}
		break;
		case "pirate":
			iMultiply = (rand(10)+3) * (rand(iShipClass) + 1);
			iRandMultiply = 2 + rand(iShipClass);
			for (i = 0; i < 4; i++)
			{
			    Fantom_SetCharacterGoods(rFantom, iStart + rand(iFinish), iMultiply * rand(iRandMultiply * 3), 0);
			}
		break;
	}
    // boal 20.01.2004 <--
    // есть ещё осталось место, то дать запасных орудий в трюм -->
    iMultiply = GetCannonGoodsIdxByType(sti(rFantom.Ship.Cannons.Type));
    if (iMultiply != -1)
    {
    	iRandMultiply = rand(6) - 2;  // 0..4 пушки
    	if (iRandMultiply > 0)
    	{
    		Fantom_SetCharacterGoods(rFantom, iMultiply, iRandMultiply, 0);
    	}
    }
    // есть ещё осталось место, то дать запасных орудий в трюм <--
	RecalculateCargoLoad(rFantom);
}
// доработал метод, теперь возвращает сколько взял
int Fantom_SetCharacterGoods(ref rFantom, int iGoods, int iQuantity, bool isLock)
{
	if (iQuantity == 0) { return 0; }

	string sGood = Goods[iGoods].name;
	int iFreeQuantity = GetGoodQuantityByWeight( iGoods, GetCargoFreeSpace(rFantom) );
	if (iFreeQuantity < 0) { iFreeQuantity = 0; }

	if (iQuantity > iFreeQuantity) { iQuantity = iFreeQuantity; }
    rFantom.Ship.Cargo.Goods.(sGood) = iQuantity;
	if(isLock) {rFantom.Ship.Cargo.Goods.(sGood).Lock = true;}
	RecalculateCargoLoad(rFantom);
	return iQuantity;
}

// опыт матросов
void Fantom_SetRandomCrewExp(ref rFantom, string sFantomType)
{
    if (!CheckAttribute(rFantom, "ship.type")) return; // fix

	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);

	switch (sFantomType)
	{
		case "trade":
			rFantom.Ship.Crew.Exp.Sailors   = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Cannoners = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
			rFantom.Ship.Crew.Exp.Soldiers  = 20 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(70);
		break;
		case "war":
			rFantom.Ship.Crew.Exp.Sailors   = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Cannoners = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
			rFantom.Ship.Crew.Exp.Soldiers  = 30 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(60);
		break;
		case "pirate":
		    rFantom.Ship.Crew.Exp.Sailors   = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Cannoners = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
			rFantom.Ship.Crew.Exp.Soldiers  = 35 - iSClass*2 + MOD_SKILL_ENEMY_RATE + rand(55);
		break;
	}
}

void Fantom_SetQuestSitiation(ref rFantom, string sFantomType)
{
	string sSituation;
	bool CanGenerateSituation = false;
	if (!CheckAttribute(rFantom, "ship.type")) return;

	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return;

	switch (sFantomType)
	{
		case "pirate": // пираты или ДУ
			if(rand(100) < 5)
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}
		break;
		case "hunter": // ОЗГ
			if(rand(100) < 5)
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}
		break;
		case "war": // военные корабли
			if(rand(100) < 5)
			{
				sSituation = "Explosion";
				CanGenerateSituation = true;
			}
		break;
		case "trade": // торговцы
			if(rand(100) < 5)
			{
				sSituation = "Epidemy";
				CanGenerateSituation = true;
			}
		break;
	}
	if(CanGenerateSituation == true)
	{
		rFantom.situation = sSituation;
		rFantom.situation.type = sFantomType;
		rFantom.DontRansackCaptain = true; // Врагу не сдается наш гордый Варяг !!
	}
}

// ugeen 03.06.09 - вероятность корабликов быть проапгрейженными на 1, 2 ...  все параметры
void Fantom_SetUpgrade(ref rFantom, string sFantomType)
{
	if (!CheckAttribute(rFantom, "ship.type")) return; // fix

	int iShip = sti(rFantom.ship.type);
	if (iShip == SHIP_NOTUSED) return; // fix

	// ship class
	int iSClass = GetCharacterShipClass(rFantom);
	int i = rand(100);

	switch (sFantomType)
	{
		case "pirate":   // апгрейдим параметр(ы)  шипа пиратских случаек
			if(i < (7 - iSClass)*4)
			{
				GenerateShipBermudes(rFantom);
			}
		break;
		case "hunter":   // апгрейдим параметр(ы) шипа ДУ или ОЗГов
			if(i < ((7 - iSClass)*4 +10))
			{
				GenerateShipBermudes(rFantom);
			}
		break;
	}
}

void GenerateShipBermudes(ref rFantom)//бермудки не должны идти группами. Каждая должна генерится сама по себе
{
	int iP = 0;
	int iT = 0; 
	int iW = 0;
	string sFantomType = rFantom.Ship.Mode;
	switch (sFantomType)
	{
		case "pirate":	iP = 20; break;//допшансы конкретных бермудок от типа фантома
		case "trade":	iT = 20; break;
		case "war":		iW = 20; break;
	}
	if ( rand(100) > 15 ) SetShipBermudeTuningSpeedRate(rFantom); //85% для всех типов - и кто прошёл рандом в предыдущих функциях
	if ( rand(100) > (60-iW) ) SetShipBermudeTuningTurnRate(rFantom);  
	if ( rand(100) > (60-iP) ) SetShipBermudeTuningWindAgainstSpeed(rFantom);
	if ( rand(100) > (80-iT) ) SetShipBermudeTuningCapacity(rFantom);
	if ( rand(100) > (80-iP-iW) ) SetShipBermudeTuningMaxCrew(rFantom);
	if ( rand(100) > (90-iP-iW) ) SetShipBermudeTuningMaxCaliber(rFantom);//например, повышенный шанс пиратам и военным. 30% вместо 10% у торговцев
	if ( rand(100) > (90-iW) ) SetShipBermudeTuningHP(rFantom);
	if ( rand(100) > (90-iT) ) SetShipBermudeTuningMastMultiplier(rFantom);
}

// eddy. подбор типа корабля для фантома от ранга ГГ с учётом нац. принадлежности, и типа занятий
void SetShipToFantom(ref _chr, string _type, bool _setgoods)
{
	int ShipType;
	int Nation = sti(_chr.nation);
	int Rank = sti(pchar.rank);
	int iClassMin,iClassMax;

	if (Rank >= 1 && Rank <= 5) {iClassMin = 6; iClassMax = 6;} // 6 класс
	if (Rank >= 5 && Rank <= 10) {iClassMin = 6; iClassMax = 5;} // 6 - 5 класс
	if (Rank >= 10 && Rank <= 15) {iClassMin = 5; iClassMax = 4;} // 5 - 4 класс
	if (Rank >= 15 && Rank <= 20) {iClassMin = 4; iClassMax = 3;} // 4 - 3 класс
	if (Rank >= 20 && Rank <= 30) {iClassMin = 3; iClassMax = 2;} // 3 - 2 класс
	if (Rank > 30) {iClassMin = 2; iClassMax = 1;} // 2 - 1 класс
	string sType = "";
	if (_type == "trade") sType = "merchant";
	if (_type == "pirate") sType = "war";
	ShipType = GetShipTypeExt(iClassMin, iClassMax, sType, Nation);

	_chr.Ship.Type = GenerateShipExt(ShipType, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, _type);
    Fantom_SetBalls(_chr, _type);
	Fantom_SetUpgrade(_chr, _type);

    if (_setgoods)
    {
        Fantom_SetGoods(_chr, _type);
    }
}
