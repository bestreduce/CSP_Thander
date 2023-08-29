#define MAX_CANNON_DAMAGE_DISTANCE	2.0 //дальность расчета урона по пушке, если снаряд попал ближе этого числа(в метрах?), то расчёт идёт


void DeleteCannonsEnvironment()
{
	DelEventHandler(CANNON_GET_RECHARGE_TIME, "Cannon_GetRechargeTime");
	DelEventHandler(CANNON_GET_FIRE_TIME, "Cannon_GetFireTime");
	DelEventHandler(CANNON_GET_FIRE_HEIGHT, "Cannon_GetFireHeight");
	DelEventHandler(CANNON_FIRE, "Cannon_FireCannon");
	DelEventHandler(CANNON_UNLOAD, "Cannon_UnloadBall");
	DelEventHandler(CANNON_LOAD, "Cannon_LoadBall");
	DelEventHandler(CANNON_RECALCULATE_PARAMETERS, "Cannon_RecalculateParametersEvent");
	DelEventHandler(CANNON_DAMAGE, "Cannon_DamageEvent");
}

void CreateCannonsEnvironment()
{
	SetEventHandler(CANNON_GET_RECHARGE_TIME, "Cannon_GetRechargeTime", 0);
	SetEventHandler(CANNON_GET_FIRE_TIME, "Cannon_GetFireTime", 0);
	SetEventHandler(CANNON_GET_FIRE_HEIGHT, "Cannon_GetFireHeight", 0);
	SetEventHandler(CANNON_FIRE, "Cannon_FireCannon", 0);
	SetEventHandler(CANNON_UNLOAD, "Cannon_UnloadBall", 0);
	SetEventHandler(CANNON_LOAD, "Cannon_LoadBall", 0);
	SetEventHandler(CANNON_RECALCULATE_PARAMETERS, "Cannon_RecalculateParametersEvent", 0);
	SetEventHandler(CANNON_DAMAGE, "Cannon_DamageEvent", 0);

	SendMessage(&AISea, "lff", AI_MESSAGE_CANNONS_PARAMS, MAX_CANNON_DAMAGE_DISTANCE, 1.0);	// fMaxCannonDamageDistance, fMaxCannonDamageRadiusPoint
}

bool Cannon_LoadBall()
{
	aref	aCharacter = GetEventData();

	int iBallType = sti(aCharacter.Ship.Cannons.Charge.Type);
	int iNumBalls = GetCargoGoods(aCharacter, iBallType);
 	// boal -->
	int iNumPowder = GetCargoGoods(aCharacter, GOOD_POWDER);
	if (iNumBalls > 0 && iNumPowder > 0)
	{
		AddCharacterGoodsCannon(aCharacter, iBallType, -1);
		AddCharacterGoodsCannon(aCharacter, GOOD_POWDER, -1);
		if (IsMainCharacter(aCharacter)) BI_UpdateLoadedProjectiles();
		// boal <--
		return true;
	}
	return false;
}

void Cannon_UnloadBall()
{
	aref aCharacter = GetEventData();
	if(CheckAttribute(aCharacter, "Ship.Cannons"))
	{
		AddCharacterGoodsCannon(aCharacter, sti(aCharacter.Ship.Cannons.Charge.Type), 1);
	}
	// boal -->
	AddCharacterGoodsCannon(aCharacter, GOOD_POWDER, 1);
	// boal <--
}

void AddCharacterGoodsCannon(aref aCharacter, int iGood, int iQuantity)
{
	string sGoodName = Goods[iGood].name;
	aCharacter.Ship.Cargo.Goods.(sGoodName) = sti(aCharacter.Ship.Cargo.Goods.(sGoodName)) + iQuantity;
	aCharacter.Ship.Cargo.RecalculateCargoLoad = true;
}

void Cannon_RecalculateParametersEvent()
{
	int iCharacterIndex = GetEventData();
	Cannon_RecalculateParameters(iCharacterIndex);
}

void Cannon_RecalculateParameters(int iCharacterIndex)
{
	if (sti(Characters[iCharacterIndex].Ship.Cannons.Type) == CANNON_TYPE_NONECANNON) { return; }

	ref	rCharacter = GetCharacter(iCharacterIndex);
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	ref	rBall = GetGoodByType(sti(rCharacter.Ship.Cannons.Charge.Type));
	int p = GetCharacterSPECIALSimple(rCharacter, SPECIAL_P)-3;
	if (p < 0) p = 0;
	if (CheckAttribute(rCharacter, "TmpPerks.LongRangeShoot"))
	{
		rCharacter.Ship.Cannons.SpeedV0 = stf(rCannon.SpeedV0) * stf(rBall.SpeedV0) * sqrt(AIShip_isPerksUse(rCharacter.TmpPerks.LongRangeShoot, 1.0, 1.15) + p * 0.03); //slib
	}
	else
	{
	    rCharacter.Ship.Cannons.SpeedV0 = stf(rCannon.SpeedV0) * stf(rBall.SpeedV0) * sqrt(1.0 + p * 0.03);
	}
	rCharacter.Ship.Cannons.FireAngMax = rCannon.FireAngMax;
	rCharacter.Ship.Cannons.FireAngMin = rCannon.FireAngMin;
}

float Cannon_GetFireHeight()
{
	aref aCharacter = GetEventData();
	aref aEnemy = GetEventData();

	ref rBallType = GetGoodByType(sti(aCharacter.Ship.Cannons.Charge.Type));
	ref rEnemyShip = GetRealShip(sti(aEnemy.Ship.Type));

	string sBallName = rBallType.Name;

	float Y,DY;
	Y = stf(rEnemyShip.Height.(sBallName).Y);
	DY = stf(rEnemyShip.Height.(sBallName).DY);
	Y = (Y + (frnd()-0.5) * DY);
	
	return Y;
}

// calculate recharge time for cannon
float Cannon_GetRechargeTime()
{
	aref	aCharacter = GetEventData();

	float	fCannonSkill = 1.0 - stf(aCharacter.TmpSkill.Cannons) / 3.0;

	ref		rCannon = GetCannonByType(sti(aCharacter.Ship.Cannons.Type));
	float	fReloadTime = GetCannonReloadTime(rCannon); // boal 28.01.03 - 09.02.05

	float fMultiply = 1.0;
	// boal -->
    fMultiply = AIShip_isPerksUse(aCharacter.TmpPerks.FastReload, 1.0, 0.9);
	fMultiply = AIShip_isPerksUse(aCharacter.TmpPerks.ImmediateReload, fMultiply, 0.5);
	if (CheckAttribute(&RealShips[sti(aCharacter.Ship.Type)], "Tuning.CannonsSpecial")) fMultiply *= 0.9;
	fMultiply *= (1+CheckOfficersPerk(aCharacter,"InstantRepair"));//х2 времени при активной быстрой починке
	//fMultiply = isEquippedArtefactUse(aCharacter, "talisman13", fMultiply, 0.9);

	ref refBaseShip = GetRealShip(sti(aCharacter.ship.Type));
	if (sti(refBaseShip.BaseType) != SHIP_FORT)
	{
        // boal 060804 для компа поблажки
		//Boyer remove reload speed boost for enemies
		if (sti(aCharacter.index) != GetMainCharacterIndex())
		{
		   fReloadTime -= MOD_SKILL_ENEMY_RATE*3/2; // -10c на невозможном
		   // if(aCharacter.id == "GhostCapt") fReloadTime = fReloadTime/2;
		}
		// boal <--
		float crewQty  = GetCrewQuantity(aCharacter);
	    float OptCrew  = GetOptCrewQuantity(aCharacter);
	    float MaxCrew  = GetMaxCrewQuantity(aCharacter);
	    float fMorale  = GetCharacterCrewMorale(aCharacter);

	    if (crewQty > MaxCrew) crewQty = MaxCrew; // fix 14/03/05
	    if (OptCrew > 0)
	    {
            float  fExp;
			fExp = 0.001 + stf(GetCrewExp(aCharacter, "Cannoners") * crewQty) / stf(OptCrew * GetCrewExpRate());
			if (fExp > 1) fExp = 1;
			fReloadTime = fReloadTime * (1.0 + (1.0 - fExp) * 3.0);
        }
	    fReloadTime = fReloadTime * (1.0 + (1.0 - fMorale / MORALE_NORMAL) * 0.2);

        if (crewQty <= (GetMinCrewQuantity(aCharacter)))
        {
            fReloadTime = fReloadTime * 3.0; //меньше команды - тормозим
        }
    // boal  корректный учет команды <--
    }
	return  fMultiply * fReloadTime * fCannonSkill;
}

// calculate delay before fire
float Cannon_GetFireTime()
{
	//aref aCharacter = GetEventData();
	aref aCharacter = GetEventData();
	ref refBaseShip = GetRealShip(sti(aCharacter.ship.Type));

	// make 10 seconds random delay between fire from fort cannons
	if (refBaseShip.Name == ShipsTypes[SHIP_FORT].Name) { return frnd() * 20.0; }   // иначе пулеметный залп

	float fCannonSkill = stf(aCharacter.TmpSkill.Cannons);
	float fFireTime = 1 - fCannonSkill*0.5;
	//fFireTime = fFireTime * Bring2RangeNoCheck(3.0, 1.0, 0.0, 1.0, stf(aCharacter.Ship.Crew.MinRatio));
	fFireTime = frnd() * fFireTime * 6.0;
	if (iArcadeSails) { fFireTime = fFireTime * 0.5; }

	float crewQ   = GetCrewQuantity(aCharacter);
 	float crewMax = stf(refBaseShip.MaxCrew);
 	float crewOpt = stf(refBaseShip.OptCrew);
 	if (crewMax < crewQ) crewQ  = crewMax;

	float fCrewMorale = GetCharacterCrewMorale(aCharacter);

    float  fExp;
	fExp = 0.05 + stf(GetCrewExp(aCharacter, "Cannoners") * crewQ) / stf(crewOpt * GetCrewExpRate());
	if (fExp > 1) fExp = 1;

	fFireTime = fFireTime * (2.0 - fExp);
	fFireTime = fFireTime * (1 + (1 - fCrewMorale/MORALE_NORMAL)/5.0);

	return fFireTime;
}

void Cannon_FireCannon()
{
	float fX, fY, fZ, fSpeedV0, fFireDirection, fFireHeightAngle, fCannonDirAng, fMaxFireDistance, fAngle;

	aref aCharacter = GetEventData();

	DeleteAttribute(aCharacter, "Sea_AI.Cannon.Charge"); //должно располагаться здесь, а не выше

	fX = GetEventData();
	fY = GetEventData();
	fZ = GetEventData();
	fSpeedV0 = GetEventData();
	fFireDirection = GetEventData();
	fFireHeightAngle = GetEventData();
	fCannonDirAng = GetEventData();
	fMaxFireDistance = GetEventData();
	fAngle = GetEventData();
	 // boal навел порядок по оптимизации
	Ball_AddBall(aCharacter, fX, fY, fZ, fSpeedV0, fFireDirection, fFireHeightAngle, fCannonDirAng, fMaxFireDistance, fAngle);
}

// Damage 2 cannon from balls
float Cannon_DamageEvent()
{
	//return 0.0;
	aref	aCharacter = GetEventData();
	float	fBallDamage = GetEventData();	// ball damage
	float	fCurDamage = GetEventData();	// current cannon damage (0.0 .. 1.0)
	float	fDistance = GetEventData();		// distance from ball 2 cannon
	float	x = GetEventData();				// x, y, z - cannon position
	float	y = GetEventData();
	float	z = GetEventData();

	if(CheckAttribute(aCharacter, "chr_ai.immortal"))
	{
		if(sti(aCharacter.chr_ai.immortal) == 1)
		{
			return 0.0;
		}
	}

	if(CheckCharacterPerk(aCharacter, "SeaWolf") && rand(2) == 0) return 0.0;
	if(IsEquipCharacterByArtefact(aCharacter, "talisman3")) return 0.0;
	if (CheckAttribute(&RealShips[sti(aCharacter.Ship.Type)], "Tuning.CannonsSpecial") && rand(9)<4) return 0.0;
	ref	rCannon = GetCannonByType(sti(aCharacter.Ship.Cannons.Type));

	float fMaxCHP = stf(rCannon.hp);
	//fCurDamage = (fCurDamage * fMaxCHP + fBallDamage * (1.0 - fDistance / MAX_CANNON_DAMAGE_DISTANCE)) / fMaxCHP;
    //Log_TestInfo("fBallDamage "  + fBallDamage + " fCurDamage " +fCurDamage + " fMaxCHP " + fMaxCHP + " fDistance " +fDistance);
    fBallDamage *= 0.1 / fDistance;
    fCurDamage =  fCurDamage  + fBallDamage / fMaxCHP;  // TO_DO

	//fCurDamage = fCurDamage - fCurDamage/100*(sti(aCharacter.ship.upgrades.cannons)-1)*20;
	if (fCurDamage >= 1.0)
	{
		fCurDamage = 1.0;
		CreateBlast(x,y,z);
		CreateParticleSystem("blast_inv", x, y, z, 0.0, 0.0, 0.0, 0);
		Play3DSound("cannon_explosion", x, y, z);
		if (IsMainCharacter(aCharacter))
		{
		    Log_Info(XI_ConvertString("Cannon_DamageEvent"));
		    BI_UpdateCannons();
		}
		aCharacter.Ship.Cargo.RecalculateCargoLoad = true; // boal 27.07.06 пушки - груз
	}

	return fCurDamage;
}

int GetBortIntactCannonsNum(ref rCharacter, string sBort, int iNumCannonsOnBort)
{
	// if (rCharacter.ship.cannons=="") return 0; //фикс вылета от корабля кораблекрушения с 0 пушек // LEO: Нихуя это не фикс, это баг
	string sBort_real = sBort;
	float fDamage;

	if(sBort == "rcannon") sBort_real = "cannonr";
	if(sBort == "lcannon") sBort_real = "cannonl";
	if(sBort == "fcannon") sBort_real = "cannonf";
	if(sBort == "bcannon") sBort_real = "cannonb";

	if (!CheckAttribute(rCharacter, "Ship.Cannons.Borts." + sBort_real + ".damages") &&
	    !CheckAttribute(rCharacter, "Ship.Cannons.Borts." + sBort + ".damages")) return iNumCannonsOnBort;

	if(!CheckAttribute(rCharacter, "Ship.Cannons.Borts." + sBort_real + ".damages"))
	{
		sBort_real = sBort;
	}

	string attr;
	int iNumIntactCannons = 0;
	for (int i=0; i<iNumCannonsOnBort; i++)
	{
		attr = "c"+i;
		fDamage = stf(rCharacter.Ship.Cannons.Borts.(sBort_real).damages.(attr));
		if (fDamage < 1.0) { iNumIntactCannons++; }
	}
	int iNumRealCannons = iNumIntactCannons;

	return iNumIntactCannons;
}
