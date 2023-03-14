//0.HP.0.MAST.Speed.Turn.WAS.Capacity.Crew.Cannon
string g_ShipBermudeTuningGoods[10] = {"","Mahogany","","Planks","Silk","Linen","Cotton","Sandal","Leather","Ebony"};
string g_ShipBermudeTuningItems[10] = {"","jewelry17","","jewelry11","jewelry2","jewelry3","jewelry4","jewelry5","jewelry1","icollection"};

void SetShipTuningF(ref chr, string sStat, float fBonus)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	float value = stf(rShip.(sStat));
	float defaultValue = value;
	if (CheckAttribute(rShip, "Untuned." + sStat))
	{
		defaultValue = stf(rShip.Untuned.(sStat));
	}
	else
	{
		rShip.Untuned.(sStat) = defaultValue;
	}
	value = value + defaultValue * fBonus;
	rShip.(sStat) = value;
	chr.ship.(sStat) = value;
}

void SetShipTuningI(ref chr, string sStat, float fBonus)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	int value = sti(rShip.(sStat));
	int defaultValue = value;
	if (CheckAttribute(rShip, "Untuned." + sStat))
	{
		defaultValue = sti(rShip.Untuned.(sStat));
	}
	else
	{
		rShip.Untuned.(sStat) = defaultValue;
	}
	value = value + makeint(defaultValue * fBonus);
	rShip.(sStat) = value;
	chr.ship.(sStat) = value;
}

void SetShipTuningAdditiveF(ref chr, string sStat, float fBonus)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	float value = stf(rShip.(sStat));
	if (!CheckAttribute(rShip, "Untuned." + sStat))
	{
		rShip.Untuned.(sStat) = value;
	}
	value = value + fBonus;
	rShip.(sStat) = value;
	chr.ship.(sStat) = value;
}

void SetShipTuningAdditiveI(ref chr, string sStat, int fBonus)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	int value = sti(rShip.(sStat));
	if (!CheckAttribute(rShip, "Untuned." + sStat))
	{
		rShip.Untuned.(sStat) = value;
	}
	value = value + fBonus;
	rShip.(sStat) = value;
	chr.ship.(sStat) = value;
}

void SetShipTuningMastMultiplier(ref chr, float fValue)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	float value = stf(rShip.MastMultiplier);
	if (!CheckAttribute(rShip, "Untuned.MastMultiplier"))
	{
		rShip.Untuned.MastMultiplier = value;
	}
	value = value - fValue;	
	rShip.MastMultiplier = value; 
	chr.ship.MastMultiplier = value; 
}

void SetShipBermudeTuningF(ref chr, string sStat)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	if (CheckAttribute(rShip, "Tuning." + sStat)) { return; }
	rShip.Tuning.(sStat) = true;
	SetShipTuningF(chr, sStat, SHIP_STAT_UPGRADE_BERMUDE);
}

void SetShipBermudeTuningI(ref chr, string sStat)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	if (CheckAttribute(rShip, "Tuning." + sStat)) { return; }
	rShip.Tuning.(sStat) = true;
	SetShipTuningI(chr, sStat, SHIP_STAT_UPGRADE_BERMUDE);
}

//увеличение прочности мачт
void SetShipBermudeTuningMastMultiplier(ref chr)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	if (CheckAttribute(rShip, "Tuning.MastMultiplier")) { return; }
	rShip.Tuning.MastMultiplier = true;
	SetShipTuningMastMultiplier(chr, 0.3);
}

//увеличение калибра и количества пушек
void SetShipBermudeTuningMaxCaliber(ref chr)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	if (CheckAttribute(rShip, "Tuning.MaxCaliber") || (sti(rShip.MaxCaliber) >= 36)) { return; }

	int iCaliber = sti(rShip.MaxCaliber);
	switch(iCaliber)
	{
		case 8:
			iCaliber = 12;
		break;
		case 12:
			iCaliber = 16;
		break;
		case 16:
			iCaliber = 20;
		break;
		case 20:
			iCaliber = 24;
		break;
		case 24:
			iCaliber = 32;
		break;
		case 32:
			iCaliber = 36;
		break;
	}
	rShip.MaxCaliber = iCaliber;
	rShip.Tuning.Cannon = true;
}

//увеличение трюма
void SetShipBermudeTuningCapacity(ref chr)
{
	SetShipBermudeTuningI(chr, "Capacity");
}

//увеличение скорости
void SetShipBermudeTuningSpeedRate(ref chr)
{
	SetShipBermudeTuningF(chr, "SpeedRate");
}

//увеличение команды
void SetShipBermudeTuningMaxCrew(ref chr)
{
	SetShipBermudeTuningI(chr, "MaxCrew");
}

//увеличение маневренности
void SetShipBermudeTuningTurnRate(ref chr)
{
	SetShipBermudeTuningF(chr, "TurnRate");
}

//увеличение ХП
void SetShipBermudeTuningHP(ref chr)
{
	SetShipBermudeTuningI(chr, "HP");
}

//увеличение бейдевинда
void SetShipBermudeTuningWindAgainstSpeed(ref chr)
{
	ref rShip = &RealShips[sti(chr.ship.type)];
	if (CheckAttribute(rShip, "Tuning.WindAgainstSpeed")) { return; }
	rShip.Tuning.WindAgainstSpeed = true;
	SetShipTuningF(chr, "WindAgainstSpeed", 0.5 / stf(rShip.Class)); // странно, но пока оставим
}

//генератор "отбермуженных" статов для кораблей с ручным рандомом
void SetBermudeTuningShipStatesRandom(ref chr, int iRand)
{
	int iType = GetCharacterShipType(chr);
	if(iType == SHIP_NOTUSED)
	{
		return; //нет корабля - отсекаем
	}
	ref rShip = GetRealShip(iType);

	if(rShip.class == 7) return;	//мелкие корабли отсекаем

	if(rand(iRand) == 0) SetShipBermudeTuningMaxCaliber(chr);		//увеличение калибра
	if(rand(iRand) == 0) SetShipBermudeTuningCapacity(chr);			//увеличение трюма
	if(rand(iRand) == 0) SetShipBermudeTuningSpeedRate(chr);		//увеличение скорости
	if(rand(iRand) == 0) SetShipBermudeTuningMastMultiplier(chr);	//увеличение прочности мачт
	if(rand(iRand) == 0) SetShipBermudeTuningMaxCrew(chr);			//увеличение команды
	if(rand(iRand) == 0) SetShipBermudeTuningTurnRate(chr);			//увеличение маневренности
	if(rand(iRand) == 0) SetShipBermudeTuningHP(chr);				//увеличение ХП
	if(rand(iRand) == 0) SetShipBermudeTuningWindAgainstSpeed(chr);	//увеличение бейдевинда
}

// генератор "отбермуженных" статов для кораблей
void SetBermudeTuningShipStates(ref chr)
{
	SetBermudeTuningShipStatesRandom(chr, 30);
}

//установка назначенных "отбермуженных" статов для корабля
void SetBermudeTuningStates2Ship(ref chr, bool MaxCaliber, bool Capacity, bool SpeedRate, bool MaxCrew, bool TurnRate, bool HP, bool MastMulti, bool WAS)
{
	int iType = GetCharacterShipType(chr);
	if(iType == SHIP_NOTUSED)
	{
		return; //нет корабля - отсекаем
	}

	if (MaxCaliber)	SetShipBermudeTuningMaxCaliber(chr);		//увеличение калибра
	if (Capacity)	SetShipBermudeTuningCapacity(chr);			//увеличение трюма
	if (SpeedRate)	SetShipBermudeTuningSpeedRate(chr);		//увеличение скорости
	if (MastMulti)	SetShipBermudeTuningMastMultiplier(chr);	//увеличение прочности мачт
	if (MaxCrew)	SetShipBermudeTuningMaxCrew(chr);			//увеличение команды
	if (TurnRate)	SetShipBermudeTuningTurnRate(chr);			//увеличение маневренности
	if (HP)			SetShipBermudeTuningHP(chr);				//увеличение ХП
	if (WAS)		SetShipBermudeTuningWindAgainstSpeed(chr);	//увеличение бейдевинда
}
