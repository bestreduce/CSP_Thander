object	AIBalls;
aref	Grapes, Knippels, Balls, Bombs;

void DeleteBallsEnvironment()
{
	DeleteClass(&AIBalls);

	DelEventHandler(BALL_WATER_HIT, "Ball_WaterHitEvent");
	DelEventHandler(BALL_ISLAND_HIT, "Ball_IslandHit");
	DelEventHandler(BALL_FLY_UPDATE, "Ball_OnFlyUpdate");
	DelEventHandler(BALL_FORT_HIT, "Ball_FortHit");
	DelEventHandler(BALL_FLY_NEAR_CAMERA, "Ball_FlyNearCamera");
}

void CreateBallsEnvironment()
{
	CreateEntity(&AIBalls, "AIBalls");
	LayerAddObject(SEA_EXECUTE, &AIBalls, -1);
	LayerAddObject(SEA_REALIZE, &AIBalls, 65532);

	AIBalls.CurrentBallCannonType = -1;
	AIBalls.CurrentBallDistance = 0.0;
	AIBalls.CurrentMaxBallDistance = 0.0;
	AIBalls.BallFlySoundDistance = 15.0;
	AIBalls.BallFlySoundStereoMultiplyer = 2.0;

	AIBalls.SpeedMultiply = 3.0;
	AIBalls.Texture = "AllBalls.tga";
	AIBalls.SubTexX = 2;
	AIBalls.SubTexY = 2;

	makearef(Grapes,AIBalls.Balls.Grapes);
	makearef(Knippels,AIBalls.Balls.Knippels);
	makearef(Balls,AIBalls.Balls.Balls);
	makearef(Bombs,AIBalls.Balls.Bombs);

	Bombs.SubTexIndex = 0;		Bombs.Size = 0.3;		Bombs.GoodIndex = GOOD_BOMBS;
	Balls.SubTexIndex = 2;		Balls.Size = 0.2;		Balls.GoodIndex = GOOD_BALLS;
	Knippels.SubTexIndex = 3;	Knippels.Size = 0.2;	Knippels.GoodIndex = GOOD_KNIPPELS;
	switch (sti(InterfaceStates.BombsParticles))
	{
		case 0:
			Bombs.Particle = "bomb_smoke_old";
			Balls.Particle = "";
			Knippels.Particle = "";
		break;
		case 1:
			Bombs.Particle = "bomb_smoke_low";
			Balls.Particle = "ball_smoke_low";
			Knippels.Particle = "ball_smoke_low";
		break;
		case 2:
			Bombs.Particle = "bomb_smoke_high";
			Balls.Particle = "ball_smoke_high";
			Knippels.Particle = "ball_smoke_low";
		break;
	}

	Grapes.SubTexIndex = 1;		Grapes.Size = 0.2;		Grapes.GoodIndex = GOOD_GRAPES;

	AIBalls.isDone = 1;

	// cheat - fire from camera
	AIBalls.FireBallFromCamera = true;

	SetEventHandler(BALL_WATER_HIT, "Ball_WaterHitEvent", 0);
	SetEventHandler(BALL_ISLAND_HIT, "Ball_IslandHit", 0);
	SetEventHandler(BALL_FLY_UPDATE, "Ball_OnFlyUpdate", 0);
	SetEventHandler(BALL_FORT_HIT, "Ball_FortHit", 0);
	SetEventHandler(BALL_FLY_NEAR_CAMERA, "Ball_FlyNearCamera", 0);
}

void Ball_FlyNearCamera()
{
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();

	Play3DSound("fly_ball", x, y, z);
}

int ballNumber;

// FPSTODO: метод очень тяжелый, особенно в замесах проседания видны невооруженным глазом
void Ball_AddBall(aref aCharacter, float fX, float fY, float fZ, float fSpeedV0, float fDirAng, float fHeightAng, float fCannonDirAng, float fMaxFireDistance, float fAngle)
{
	int iCannonType = sti(aCharacter.Ship.Cannons.Type);
	ref rCannon = GetCannonByType(iCannonType);
	float fCannonHeightMultiply = stf(rCannon.HeightMultiply);

	EntityUpdate(0);
	AIBalls.CannonType = iCannonType;
	AIBalls.x = fX;
	AIBalls.y = fY;
	AIBalls.z = fZ;
	AIBalls.CharacterIndex    = aCharacter.Index;
	AIBalls.Type = Goods[sti(aCharacter.Ship.Cannons.Charge.Type)].Name;
	if(SeaCameras.Camera != "SeaDeckCamera")
	{
		if(AIBalls.Type == GOOD_KNIPPELS)
		{
			fTempDispersionX *= 3; 
		}
		fCannonHeightMultiply *= 0.3;//высота траектории
	}
	AIBalls.HeightMultiply    = fCannonHeightMultiply;
	AIBalls.SizeMultiply      = rCannon.SizeMultiply;
	AIBalls.TimeSpeedMultiply = rCannon.TimeSpeedMultiply;
	AIBalls.MaxFireDistance   = fMaxFireDistance;
	AIBalls.RawAng = fAngle;
	float fTempDispersionY = Degree2Radian(9.0); //отклонение по горизонтали	//LEO: Важные параметры разброса снарядов, ванильное: 15.0
	float fTempDispersionX = Degree2Radian(6.5); //отклонение по вертикали		//(5.0)

	//float fDamage2Cannons = 100.0;

	float fCannons = stf(aCharacter.TmpSkill.Cannons)*10;

	int nShipType = sti(aCharacter.ship.type);
	ref refBaseShip = GetRealShip(nShipType);
	int iCannonsNum = sti(refBaseShip.CannonsQuantity);
	
	float fCannonsNumPenalty = (MakeFloat(iCannonsNum)/35 - 1)/(10);//-0.06...0.2
	float fCaliberPenalty = (GetCannonCaliber(iCannonType) - 6 - fCannons*2)/160;//-0.05...0.15
    float fAccuracy = (1.5 - stf(aCharacter.TmpSkill.Accuracy))/2 + fCaliberPenalty + fCannonsNumPenalty;
	
	fCannons = 15.0 + MOD_SKILL_ENEMY_RATE*3 - fCannons;//сложность влияет на частоту нанесения урона! И на неписей тоже распространяется???

	if (fCannons > 0.0 && RealShips[sti(aCharacter.ship.type)].BaseName != "fort") // fix
	{
		if (fCannons > rand(100) && !IsEquipCharacterByArtefact(aCharacter, "talisman3"))
		{
            fCannons = (frnd() + 3.0*(1.65 - stf(aCharacter.TmpSkill.Cannons))) * 5;//уменьшаю рандомный разброс урона, и сам урон примерно в 2 раза
			SendMessage(&AISea, "laffff", AI_MESSAGE_CANNONS_BOOM_CHECK, aCharacter, fCannons, fx, fy, fz);  // fDamage2Cannons  там много делителей, потому много
		}
	}

	float fK = Bring2Range(0.33, 0.75, 0.25, 0.75, fAccuracy);
	
	AIBalls.Dir = fDirAng + fK * fTempDispersionY * (frnd() +frnd() - 1);//горизонтальная_наводка + разброс
	AIBalls.SpdV0 = fSpeedV0 + fAccuracy * (10.0 * fTempDispersionY) * (frnd() - 0.5);//скорость_снаряда + разброс_скорости
	AIBalls.Ang = fHeightAng + fAccuracy * (fTempDispersionX) * (frnd() + frnd() - 1);//вертикальная_наводка + разброс 

	AIBalls.Event = "";

	EntityUpdate(1);
	AIBalls.Add = "";

	string sParticleName = "cancloud_fire";		// if (sti(aCharacter.ship.type) < SHIP_CORVETTE)

	if (iCannonType >= CANNON_TYPE_CANNON_LBS48)
    {
        sParticleName = "Bombard";
    }
	else
	{
		if (iCannonType >= CANNON_TYPE_CANNON_LBS24)
		{
			sParticleName = "cancloud_fire_big";
		}
		else
		{
			sParticleName = "cancloud_fire";
		}
		if (iCannonType >= CANNON_TYPE_CULVERINE_LBS24)
		{
			sParticleName = "cancloud_fire_big";
		}
		else
		{
			sParticleName = "cancloud_fire";
		}
	}
	//if (rand(1) == 0) // boal оптимизация дыма
	CreateParticleSystem(sParticleName, fX, fY, fZ, -fHeightAng - (fCannonHeightMultiply - 1.0) * 0.1, fDirAng, 0.0, 5);
	
	if (sti(InterfaceStates.EnabledAltSoundsGun) != 0) 
	{
		Play3DSound(rCannon.Sound+"_alt", fX, fY, fZ);
	}
	else 
	{
		Play3DSound(rCannon.Sound, fX, fY, fZ);
	}
}

void Ball_WaterHitEvent()
{
	int		iCharacterIndex;
	float	x, y, z;

	iCharacterIndex = GetEventData();
	x = GetEventData();
	y = GetEventData();
	z = GetEventData();
	CreateParticleSystem("splash", X, Y, Z, 0.0, 0.0, 0.0, 5);
	Play3DSound("ball_splash", x, y, z);

/*	//Missing splash_big.xps		-нет такого файла, нет смысла и эффекты сортировать по размеру снарядов
	int nBallType = sti(AIBalls.CurrentBallCannonType);
	if (nBallType >= 0)
	{
		
		ref rCannon = GetCannonByType(nBallType);
		if (CheckAttribute(rCannon, "BigBall") && sti(rCannon.BigBall))
            CreateParticleSystem("splash_big", X, Y, Z, 0.0, 0.0, 0.0, 5);
		else
            CreateParticleSystem("splash", X, Y, Z, 0.0, 0.0, 0.0, 5);
	}
	else
	{
		CreateParticleSystem("splash", X, Y, Z, 0.0, 0.0, 0.0, 5);
	}
*/
}

void Ball_FortHit()
{
	int		iCharacterIndex;
	float	x, y, z;

	iCharacterIndex = GetEventData();

	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	if (rand(4) == 1) CreateParticleSystem("blast", x, y, z, 0.0, 0.0, 0.0, 0); // boal fix
	SendMessage(&AIFort, "llfff", AI_MESSAGE_FORT_HIT, iCharacterIndex, x, y, z);
}

void Ball_IslandHit()
{
	int		iCharacterIndex;
	float	x, y, z;

	iCharacterIndex = GetEventData();

	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	if (rand(2) == 1) CreateParticleSystem("blast", x, y, z, 0.0, 0.0, 0.0, 0); // boal fix

	//Ship_SetLightsOff(&Characters[1], 15.0, true, true, false);
}

void Ball_OnFlyUpdate()
{
	int charIndex = GetEventData();
	int ballAlive = GetEventData();
	float x = GetEventData();
	float y = GetEventData();
	float z = GetEventData();
	float lx = GetEventData();
	float ly = GetEventData();
	float lz = GetEventData();
	SendMessage(&SeaOperator, "lalffffff", MSG_SEA_OPERATOR_BALL_UPDATE, &Characters[charIndex], ballAlive, x, y, z, lx, ly, lz);
}
