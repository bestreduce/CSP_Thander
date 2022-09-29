/////////////////////////
// GOF 1.2
/////////////////////////

#define DIRECTSAILDEBUG	0;

// #define DIRECTENCOUNTERCHANCE 50   // chance in percent that an encounter fleet appears every hour
#define DIRECTENCOUNTERDISTANCE 1000 // distance from player at which random ships appear

#define DIR_PORTBOW 1
#define DIR_FORWARD 2
#define DIR_STARBOW 3
#define DIR_STAR 4
#define DIR_PORT 5
#define DIR_PORTSTERN 6
#define DIR_ABAFT 7
#define DIR_STARSTERN 8

void CheckIslandChange()
{
	float 		RTplayerShipX;
    float 		RTplayerShipZ;
    int 		scale;
    bool 		isStorm, isTornado;
	
    getRTplayerShipXZ(&RTplayerShipX, &RTplayerShipZ, &scale);

    float 		distToClosestIsland, distStorm;
    bool 		bScaleDiff;
    bool 		bCheckEnc = true;
	
	int 		nextisland = getRTclosestIsland(RTplayerShipX, RTplayerShipZ, scale, &distToClosestIsland, &bScaleDiff);
	
	while(nextisland > -1 && nextisland != FindIsland(worldMap.island))
	{
		ref rIsland 		= GetIslandByIndex(nextisland);
		string sNewIslandId = rIsland.id;
		string sIslandNow 	= worldMap.island;

		float distToCurIsland;
		
		if (worldMap.island == WDM_NONE_ISLAND) 
		{	
			distToCurIsland = 2500000000.0;
		}	
		else
		{		
			distToCurIsland = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, stf(worldMap.islands.(sIslandNow).position.x), stf(worldMap.islands.(sIslandNow).position.z));
		}	
		
		if (bScaleDiff) 
		{
            if(distToClosestIsland * 1.12 > distToCurIsland)
                break;
        }
        else 
		{
            if(distToClosestIsland * 1.85 > distToCurIsland)
                break;
		}

		bCheckEnc = false;
		
		aref rSituation;
		makearef(rSituation, pchar.SeaAI.Update.Situation);
/*
		nextenemy = sti(rSituation.MinEnemyIndex);
		enemydist = stf(rSituation.MinEnemyDistance);
		//if (DIRECTSAILDEBUG) trace("DirectsailCheck; next enemy: "+nextenemy + " dist: "+enemydist);
		if(nextenemy!= -1 && enemydist<enemyDistLimit )
		{
			//if (DIRECTSAILDEBUG) trace("Directsail aborted due to hostile ship, dist = " + enemydist);	
			break;
		}
		
		nextenemy = sti(rSituation.MinNeutralIndex);
		enemydist = stf(rSituation.MinNeutralDistance);

		//if (DIRECTSAILDEBUG) trace("DirectsailCheck; next neutral ship: "+nextenemy + " dist: "+enemydist);
		if(nextenemy!= -1 && enemydist<neutralDistLimit && sti(Characters[nextenemy].ship.type) != SHIP_FORT ) 
		{
		  //if (DIRECTSAILDEBUG) trace("Directsail aborted due to neutral ship, dist = " + enemydist);	
		  break;
		}
*/		
		if(!bMapEnter) 
		{
			if (DIRECTSAILDEBUG) trace("Directsail aborted in battle");
			break;
		}		
		
		// mitrokosta проверка перегруза итд
		if(!CheckMapEnterConditions()) 
		{
			break;
		}
		
		sIslandID = sNewIslandId;
		
		SetEventHandler("FaderEvent_StartFade", "ChangeSeaMapNew", 0);
        SetEventHandler("FaderEvent_EndFade", "Sea2Sea_Reload", 0);
		
        CreateEntity(&wdm_fader, "fader");
		if(IsEntity(wdm_fader) == 0) Trace("Fader not created!!!");
		
        float fadeOutTime = 0.5;
		
        SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
        SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
		
		string imageName = "Loading\jonny_load\sea\sea_" + rand(3) + ".tga";
		SendMessage(&wdm_fader, "ls", FADER_PICTURE0, imageName);
	
		break;
	}
}

bool CheckMapEnterConditions() 
{
    int cn;
    ref chref;
	bool canEnter = true;
	bool bLog = false;

    for (int i = 0; i<COMPANION_MAX; i++) 
	{
		cn = GetCompanionIndex(pchar, i);
		if (cn >= 0) 
		{
			chref = GetCharacter(cn);

			if (!GetRemovable(chref)) 
			{
				continue;
			}
			
            if (GetCargoLoad(chref) > GetCargoMaxSpace(chref)) 
			{
				Log_SetStringToLog("Корабль '" +  chref.Ship.Name + "' перегружен.");
				bLog = true;
				canEnter = false;
				break;
            }

            if (MOD_SKILL_ENEMY_RATE > 2) { // халява и юнга - послабление
	            if (i > 0 && GetMinCrewQuantity(chref) > GetCrewQuantity(chref)) 
				{
					Log_SetStringToLog("На корабле '" +  chref.Ship.Name + "' нет минимального экипажа.");
					bLog = true;
					canEnter = false;
					break;
	            }
			}
			
            if (GetMaxCrewQuantity(chref) < GetCrewQuantity(chref)) 
			{
				Log_SetStringToLog("На корабле '" +  chref.Ship.Name + "' перегруз экипажа больше допустимого.");
				bLog = true;
				canEnter = false;
				break;
			}
		}
    }

	if (canEnter && !CheckEnemyCompanionDistance2GoAway(false)) 
	{
		CheckEnemyCompanionDistance2GoAway(true); // получается по-дурацки - двойной вызов одной функции, но это нужно чтобы не было спама табличками
		canEnter = false;
	}
	
	if (bLog) 
	{
		Log_Info("Дальнейшее путешествие невозможно.");
		PlaySound("interface\knock.wav");
	}
	
	return canEnter;
}

//#20190624-01
void getRTplayerShipXZ(ref RTplayerShipX, ref RTplayerShipZ, ref scale)
{
	float zeroX = MakeFloat(worldMap.zeroX);
	float SeaX = stf(pchar.Ship.Pos.x);
	float zeroZ = MakeFloat(worldMap.zeroZ);
	float SeaZ = stf(pchar.Ship.Pos.z);
	string sIsland = worldMap.island;

	scale = WDM_MAP_TO_SEA_SCALE;
	if (sIsland == "Cuba1" || sIsland == "Cuba2" || sIsland == "Beliz" || sIsland == "SantaCatalina"
		|| sIsland == "PortoBello" || sIsland == "Cartahena" || sIsland == "Maracaibo"
		|| sIsland == "Caracas" || sIsland == "Cumana")
	{
		scale = 25;
	}
	RTplayerShipX = (SeaX/scale) + zeroX;
	RTplayerShipZ = (SeaZ/scale) + zeroZ;
	return;
}

float getRTplayerShipAY()
{
	float RTplayerShipAY = stf(pchar.Ship.Ang.y);
	return RTplayerShipAY;
}
//#20190628-01
int getRTclosestIsland(float RTplayerShipX, float RTplayerShipZ, int curScale, ref iDistanceNow, ref scaleDiff)
{
	bool 			tempDiff;
	float 			distance, iBearing, offShip, shipAY, iX, iZ;
	iDistanceNow 	= 2500000000.0; 
    scaleDiff 		= false;
	int nextisland 	= -1;
	ref 			rIsland;
	string 			islandTemp;
    shipAY 			= stf(pchar.Ship.Ang.y);
	
	for (int inum = 0; inum <= iNumIslands; inum++ )
	{
		rIsland = GetIslandByIndex(inum);
		islandTemp = rIsland.id;
		
		if(Islands[inum].visible == false) continue;
		
		iX = stf(worldMap.islands.(islandTemp).position.x);
		iZ = stf(worldMap.islands.(islandTemp).position.z);

		iBearing = GetAngleY(iX - RTplayerShipX, iZ - RTplayerShipZ);
        offShip = iBearing - shipAY;
        int nBear = ClosestDirFA(offShip);
        if(nBear != DIR_FORWARD) continue; 

		tempDiff = false;
		if(curScale == WDM_MAP_TO_SEA_SCALE) {
            if (islandTemp == "Cuba1" || islandTemp == "Cuba2" || islandTemp == "Beliz" || islandTemp == "SantaCatalina"
                || islandTemp == "PortoBello" || islandTemp == "Cartahena" || islandTemp == "Maracaibo"
                || islandTemp == "Caracas" || islandTemp == "Cumana")
            {
                tempDiff = true;
            }
		}

		distance = GetDistance2DRel(RTplayerShipX, RTplayerShipZ, iX, iZ);

		if (distance < iDistanceNow)
		{
			iDistanceNow = distance
			nextisland = inum;
			scaleDiff = tempDiff;
		}
	}

	return nextisland;
}

//#20180813-02
void ChangeSeaMapNew() //string sNewIslandId)
{
	//ShipsInit();
	DelEventHandler("FaderEvent_StartFade", "ChangeSeaMapNew");
    //PauseAllSounds();
	DeleteSeaEnvironment();
	//SetEventHandler("Sea2Sea_Reload", "Sea2Sea_Reload", 0);
	//PostEvent("Sea2Sea_Reload", 0);
	LayerAddObject(SEA_REALIZE, &wdm_fader, -1);
}

void Sea2Sea_Reload()
{
    //#20180813-02
	//DelEventHandler("Sea2Sea_Reload", "Sea2Sea_Reload");
	DelEventHandler("FaderEvent_EndFade", "Sea2Sea_Reload");
    ReloadProgressStart();
	object seaLoginToSea;

	//#20190624-01
    float CX;
    float CZ;
    int scale = WDM_MAP_TO_SEA_SCALE;
    float fScrap;
    getRTplayerShipXZ(&CX, &CZ, &scale);

	float CAY = getRTplayerShipAY();
	//#20190628-01 //#20190628-01
	bool bScaleDiff;
	int nextisland = getRTclosestIsland(CX, CZ, scale, &fScrap, &bScaleDiff);
	ref rIsland = GetIslandByIndex(nextisland);
	string CIsland = rIsland.id;

	float ix = MakeFloat(worldMap.islands.(CIsland).position.x);
	float iz = MakeFloat(worldMap.islands.(CIsland).position.z);

	/*if (CIsland == "Cuba1" || CIsland == "Cuba2" || CIsland == "Beliz" || CIsland == "SantaCatalina"
		|| CIsland == "PortoBello" || CIsland == "Cartahena" || CIsland == "Maracaibo"
		|| CIsland == "Caracas" || CIsland == "Cumana")
	{
		scale = 25;
	}
	*/
	seaLoginToSea.playerGroup.x = (CX - ix)*scale;
	seaLoginToSea.playerGroup.z = (CZ - iz)*scale;
	seaLoginToSea.playerGroup.ay = CAY;
	seaLoginToSea.island = CIsland;

    //musicName = "";
    DeleteAttribute(pchar, "pirateFriendly");
	SeaLogin(&seaLoginToSea);
	LayerAddObject(SEA_REALIZE, &wdm_fader, -1);
	ReloadProgressEnd();

	//#20190624-01
    float RTplayerShipX;
    float RTplayerShipZ;
    getRTplayerShipXZ(&RTplayerShipX, &RTplayerShipZ, &scale);
	worldMap.playerShipX = RTplayerShipX;
	worldMap.playerShipZ = RTplayerShipZ;
	worldMap.playerShipAY = getRTplayerShipAY();
	worldMap.island = rIsland.id;
	worldMap.zeroX = ix;
	worldMap.zeroZ = iz;
}

//Returns #define DIR_XXX
int ClosestDirE(float dir)
{
    //float aX[8] {-0.5,0.0,0.5,1.0,-1.0,-0.5,0.0,0.5};
    //float aZ[8] {1.0,1.0,1.0,0.0,0.0,-1.0,-1.0,-1.0};
    float aX[8];
    float aZ[8];
    //Bug in compiler...float inits don't work: invalid operand
    aX[0] = -0.5; aX[1] = 0.0; aX[2] = 0.5; aX[3] = 1.0; aX[4] = -1.0; aX[5] = -0.5; aX[6] = 0.0; aX[7] = 0.5;
    aZ[0] = 1.0; aZ[1] = 1.0; aZ[2] = 1.0; aZ[3] = 0.0; aZ[4] = 0.0; aZ[5] = -1.0; aZ[6] = -1.0; aZ[7] = -1.0;

    float maxDot = -999999999.0;
    int nRet = 0;
    for(int i = 0; i < 8; i++) {
        float v = GetAngleY(aX[i], aZ[i]);
        float t = GetDotProduct(v, dir);
        if (t > maxDot) {
             //ret = dir;
             nRet = i + 1;
             maxDot = t;
         }
    }
    return nRet;
}

int ClosestDirFA(float dir)
{
    float aX[6];
    float aZ[6];
    //Bug in compiler...array inits don't work in .c files
    aX[0] = -1.0; aX[1] = 0.0; aX[2] = 1.0; aX[3] = -1.0; aX[4] = 0.0; aX[5] = 1.0;
    aZ[0] = 0.5; aZ[1] = 1.0; aZ[2] = 0.5; aZ[3] = 0.0; aZ[4] = -1.0; aZ[5] = 0.0;

    float maxDot = -99999999.0;
    int nRet = 0;
    for(int i = 0; i < 6; i++) {
        float v = GetAngleY(aX[i], aZ[i]);
        float t = GetDotProduct(v, dir);
        if (t > maxDot) {
             nRet = i + 1;
             maxDot = t;
         }
    }
    if(nRet < 4)
        nRet = DIR_FORWARD;
    else
        nRet = DIR_ABAFT;

    return nRet;
}
