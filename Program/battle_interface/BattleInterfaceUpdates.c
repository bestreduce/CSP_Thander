int BI_CannonsUpdate = 0;
int BI_icons_ProjectilesUpdate = 0;

int LoadedChars[MAX_SHIPS_ON_SEA];

void BI_UpdateShipsRollSpeed()
{
	ref chref;
	for (i = 0; i < MAX_SHIPS_ON_SEA; i++)
	{
		if (LoadedChars[i] <= 0) continue;
		chref = GetCharacter(LoadedChars[i])
		BI_UpdateRSRollSpeed(chref);
	}
	PostEvent("BI_CallUpdateShipsRollSpeed", 1000); // once every second, on x1 time
}

void BI_UpdateRSRollSpeed(ref chref) // скорость подъема/спуска парусов
{
	if (HasSubStr(chref.id, "_DriftCap_"))
	{
		chref.Ship.RollSpeed = 3.0;
		return;
	}

	int iShip = sti(chref.ship.type);
	if (iShip < 0 || iShip >= REAL_SHIPS_QUANTITY)
	{
		chref.Ship.RollSpeed = 0.0;
		return;
	}

	int crewQ = GetCrewQuantity(chref);
	//int crewMin = sti(RealShips[iShip].MinCrew);
	if (!CheckAttribute(&RealShips[iShip], "MaxCrew"))
	{
		Log_TestInfo("GetRSRollSpeed нет MaxCrew у корабля НПС ID=" + chref.id);
		chref.Ship.RollSpeed = 0.0;
		return;
	}

	int crewMax = sti(RealShips[iShip].MaxCrew);
	int crewOpt = sti(RealShips[iShip].OptCrew);//boal
	if (crewMax < crewQ) crewQ = crewMax; // boal

	// опыт матросов
	float  fExp;

	if (crewOpt <= 0) crewOpt = 0; // fix для профилактики деления на ноль

	fExp = 0.05 + stf(GetCrewExp(chref, "Sailors") * crewQ) / stf(crewOpt * GetCrewExpRate());
	if (fExp > 1) fExp = 1;

	float fRollSpeed = 0.5 + 0.05 * makefloat(GetSummonSkillFromNameToOld(chref, SKILL_SAILING)); //fix skill
	fRollSpeed = fRollSpeed * fExp;

	// мораль
	float  fMorale = stf(stf(GetCharacterCrewMorale(chref)) / MORALE_MAX);
	fRollSpeed = fRollSpeed * (0.7 + fMorale / 2.0);

	if (iArcadeSails != 1) fRollSpeed = fRollSpeed / 2.5;
	if (CheckOfficersPerk(chref, "SailsMan")) fRollSpeed = fRollSpeed * 1.1; // 10 процентов
	if (CheckAttribute(&RealShips[iShip], "Tuning.SailsSpecial")) fRollSpeed = fRollSpeed * 1.25;

	chref.Ship.RollSpeed = fRollSpeed;
}

void BI_UpdateLoadedProjectiles()
{  // обновление иконок и текстов в BattleInterface
	if (!CheckAttribute(pchar, "Ship.Cannons.Charge.Type"))
	{
		trace("ОШИБКА: Не нашли Ship.Cannons.Charge.Type для ГГ")
			return;
	}

	switch (sti(pchar.Ship.Cannons.Charge.Type))
	{
	case GOOD_BALLS:
		BI_icons_ProjectilesUpdate = 32;
		BattleInterface.textinfo.Ammo.text = "" + sti(pchar.ship.cargo.goods.balls);
		break;
	case GOOD_GRAPES:
		BI_icons_ProjectilesUpdate = 35;
		BattleInterface.textinfo.Ammo.text = "" + sti(pchar.ship.cargo.goods.grapes);
		break;
	case GOOD_KNIPPELS:
		BI_icons_ProjectilesUpdate = 34;
		BattleInterface.textinfo.Ammo.text = "" + sti(pchar.ship.cargo.goods.knippels);
		break;
	case GOOD_BOMBS:
		BI_icons_ProjectilesUpdate = 33;
		BattleInterface.textinfo.Ammo.text = "" + sti(pchar.ship.cargo.goods.bombs);
		break;
	}
}

void BI_UpdateCannons()
{ // обновление состояния пушек в BattleInterface
	int nShipType = sti(pchar.ship.type);
	if (nShipType == SHIP_NOTUSED)
	{
		trace("ОШИБКА: ГГ без корабля");
		return;
	}

	ref refBaseShip = GetRealShip(nShipType);

	int fcannonsIntactCount = GetBortIntactCannonsNum(pchar, "fcannon", sti(refBaseShip.fcannon));
	int bcannonsIntactCount = GetBortIntactCannonsNum(pchar, "bcannon", sti(refBaseShip.bcannon));
	int lcannonsIntactCount = GetBortIntactCannonsNum(pchar, "lcannon", sti(refBaseShip.lcannon));
	int rcannonsIntactCount = GetBortIntactCannonsNum(pchar, "rcannon", sti(refBaseShip.rcannon));

	int allcannonsIntactCount = fcannonsIntactCount + bcannonsIntactCount + lcannonsIntactCount + rcannonsIntactCount;
	BI_CannonsUpdate = (allcannonsIntactCount == 0);

	BattleInterface.textinfo.CannonsNumF.text = fcannonsIntactCount + "/" + refBaseShip.fcannon;
	BattleInterface.textinfo.CannonsNumB.text = bcannonsIntactCount + "/" + refBaseShip.bcannon;
	BattleInterface.textinfo.CannonsNumL.text = lcannonsIntactCount + "/" + refBaseShip.lcannon;
	BattleInterface.textinfo.CannonsNumR.text = rcannonsIntactCount + "/" + refBaseShip.rcannon;
}
