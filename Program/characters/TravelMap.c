//navy -- полная карта, единая для всех задач (метро, ПГГ)
void InitTravelMap()
{
//////////////////////////////////////////////////////////////////////////////
/////////////////////////// INIT SHORES //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
	NullCharacter.TravelMap.Islands.Trinidad.Shore.t0		= "Shore60";
	NullCharacter.TravelMap.Islands.Trinidad.Shore.t1		= "Mayak1";
	NullCharacter.TravelMap.Islands.Cumana.Shore.t0			= "Shore19";
	NullCharacter.TravelMap.Islands.Caracas.Shore.t0		= "shore21";
	NullCharacter.TravelMap.Islands.Maracaibo.Shore.t0		= "shore37";
	NullCharacter.TravelMap.Islands.Cartahena.Shore.t0		= "Shore25";
	NullCharacter.TravelMap.Islands.Cartahena.Shore.t1		= "Mayak11";
	NullCharacter.TravelMap.Islands.PortoBello.Shore.t0		= "shore47";
	NullCharacter.TravelMap.Islands.SantaCatalina.Shore.t0		= "shore54";
	NullCharacter.TravelMap.Islands.Jamaica.Shore.t0		= "shore36";
	NullCharacter.TravelMap.Islands.Cuba1.Shore.t0			= "Shore12";
	NullCharacter.TravelMap.Islands.Cuba1.Shore.t1			= "Mayak9";
	NullCharacter.TravelMap.Islands.Cuba2.Shore.t0			= "shore13";
	NullCharacter.TravelMap.Islands.Cuba2.Shore.t1			= "Mayak10";
	NullCharacter.TravelMap.Islands.Beliz.Shore.t0			= "shore8";
	NullCharacter.TravelMap.Islands.Bermudes.Shore.t0		= "Shore3";
	NullCharacter.TravelMap.Islands.SentMartin.Shore.t0		= "shore41";
	NullCharacter.TravelMap.Islands.Nevis.Shore.t0			= "shore43";
	NullCharacter.TravelMap.Islands.Nevis.Shore.t1			= "Mayak5";
	NullCharacter.TravelMap.Islands.Antigua.Shore.t0		= "shore1";
//NullCharacter.TravelMap.Islands.Antigua.Shore.t1		= "shore2";		//ПОЧЕМУ убран Залив Уиллоуби из генерации?
	NullCharacter.TravelMap.Islands.Barbados.Shore.t0		= "Shore5";
	NullCharacter.TravelMap.Islands.Barbados.Shore.t1		= "Mayak2";
	NullCharacter.TravelMap.Islands.Curacao.Shore.t0		= "shore23";
	NullCharacter.TravelMap.Islands.Martinique.Shore.t0		= "shore38";
	NullCharacter.TravelMap.Islands.Guadeloupe.Shore.t0		= "shore28";
	NullCharacter.TravelMap.Islands.Guadeloupe.Shore.t1		= "Mayak4";
	NullCharacter.TravelMap.Islands.PuertoRico.Shore.t0		= "shore45";
	NullCharacter.TravelMap.Islands.Hispaniola1.Shore.t0		= "shore33";
	NullCharacter.TravelMap.Islands.Hispaniola1.Shore.t1		= "Mayak8";
	NullCharacter.TravelMap.Islands.Hispaniola2.Shore.t0		= "shore34";
//NullCharacter.TravelMap.Islands.Hispaniola2.Shore.t1		= "Mayak7";	//ПОЧЕМУ убран маяк?
	NullCharacter.TravelMap.Islands.Tortuga.Shore.t0		= "shore58";
	NullCharacter.TravelMap.Islands.Tortuga.Shore.t1		= "Mayak6";

	NullCharacter.TravelMap.Islands.Caiman.Shore.t0			= "shore16";
	NullCharacter.TravelMap.Islands.Caiman.Shore.t1			= "shore17";
	NullCharacter.TravelMap.Islands.Dominica.Shore.t0		= "shore26";
	NullCharacter.TravelMap.Islands.Dominica.Shore.t1		= "shore27";
	NullCharacter.TravelMap.Islands.Terks.Shore.t0			= "shore56";
	NullCharacter.TravelMap.Islands.Terks.Shore.t1			= "shore57";
	NullCharacter.TravelMap.Islands.Bahames.Shore.t0		= "shore68";
	//NullCharacter.TravelMap.Islands.Bahames.Shore.t1		= "shore69"; //тупиковая бухта - убираю, чтобы после кораблекрушения не выкидывало


///////////////// клады //////////////////////////////////////////
    NullCharacter.TravelMap.Islands.Antigua.Treasure.Antigua_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Antigua.Treasure.SentJons_TownCave.t0="box1";
	NullCharacter.TravelMap.Islands.Antigua.Treasure.SentJons_TownCave.t1="box2";
	NullCharacter.TravelMap.Islands.Antigua.Treasure.SentJons_TownCave.t2="box3";
	NullCharacter.TravelMap.Islands.Barbados.Treasure.Barbados_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Bahames.Treasure.Bahames_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Beliz.Treasure.Beliz_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Beliz.Treasure.Beliz_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.Beliz.Treasure.Beliz_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.Beliz.Treasure.Beliz_Cave_2.t0="box1";
	NullCharacter.TravelMap.Islands.Bermudes.Treasure.Bermudes_Dungeon.t0="box1";
	NullCharacter.TravelMap.Islands.Bermudes.Treasure.Bermudes_Dungeon.t1="box2";
	NullCharacter.TravelMap.Islands.Bermudes.Treasure.Bermudes_Dungeon.t2="box3";
	NullCharacter.TravelMap.Islands.Bermudes.Treasure.Bermudes_Dungeon.t3="box4";
	NullCharacter.TravelMap.Islands.Caracas.Treasure.Caracas_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Cartahena.Treasure.Cartahena_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Cartahena.Treasure.Cartahena_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.Cartahena.Treasure.Cartahena_Cave.t2="box3";
	//NullCharacter.TravelMap.Islands.Caiman.Treasure.Caiman_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Nevis.Treasure.Charles_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Cuba1.Treasure.Cuba_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Cumana.Treasure.Cumana_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Cumana.Treasure.Cumana_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.Cumana.Treasure.Cumana_Cave.t2="box3";
	//NullCharacter.TravelMap.Islands.Cumana.Treasure.Cumana_Cave_2.t0="box1";
	NullCharacter.TravelMap.Islands.Curacao.Treasure.Curacao_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Curacao.Treasure.Curacao_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.Curacao.Treasure.Curacao_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.Dominica.Treasure.Dominica_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Guadeloupe.Treasure.Guadeloupe_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Guadeloupe.Treasure.Guadeloupe_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.Guadeloupe.Treasure.Guadeloupe_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.Hispaniola1.Treasure.Hispaniola_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Hispaniola1.Treasure.Hispaniola_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.Hispaniola1.Treasure.Hispaniola_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.Jamaica.Treasure.Jamaica_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Maracaibo.Treasure.Maracaibo_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Maracaibo.Treasure.Maracaibo_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.Maracaibo.Treasure.Maracaibo_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.SentMartin.Treasure.Marigo_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.SentMartin.Treasure.Marigo_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.SentMartin.Treasure.Marigo_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.Panama.Treasure.Panama_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Pearl.Treasure.Pearl_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.PortoBello.Treasure.PortoBello_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.PuertoRico.Treasure.SanJuan_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.PuertoRico.Treasure.SanJuan_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.PuertoRico.Treasure.SanJuan_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_Cave.t1="box2";
	NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_PearlCave.t0="box1";
	NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_PearlCave.t1="box2";
	NullCharacter.TravelMap.Islands.SantaCatalina.Treasure.SantaCatalina_PearlCave.t2="box3";
	//NullCharacter.TravelMap.Islands.Tenotchitlan.Treasure.Tenotchitlan_Cave.t0="box1";
	//NullCharacter.TravelMap.Islands.Tenotchitlan.Treasure.Tenotchitlan_Cave.t1="box2";
	//NullCharacter.TravelMap.Islands.Tenotchitlan.Treasure.Tenotchitlan_Cave.t2="box3";
	NullCharacter.TravelMap.Islands.Terks.Treasure.Terks_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Tortuga.Treasure.Tortuga_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Tortuga.Treasure.Tortuga_Cave.t0="box1";
	NullCharacter.TravelMap.Islands.Trinidad.Treasure.Trinidad_Grot.t0="box1";
	NullCharacter.TravelMap.Islands.Martinique.Treasure.FortFrance_Dungeon.t0="box1";
	NullCharacter.TravelMap.Islands.Martinique.Treasure.FortFrance_Dungeon.t1="box2";
	NullCharacter.TravelMap.Islands.Martinique.Treasure.FortFrance_Dungeon.t2="box3";
	NullCharacter.TravelMap.Islands.Martinique.Treasure.FortFrance_Dungeon.t3="box4";
	NullCharacter.TravelMap.Islands.Martinique.Treasure.FortFrance_Dungeon.t4="box5";
	// Lugger <--
}
//бррррррр.... я чуть не помер :(

//navy -- оптимизация, бухты хранятся отдельно, меньше аттрибутов.
//получить Id случайной бухты недалеко от города, может быть 2,3,...,n
string GetIslandRandomShoreId(string _island)
{
	int iNum;
	aref arDest;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands.(_island).Shore);
	iNum = GetAttributesNum(arDest);
	sAttr = "t" + rand(iNum-1);

	if (sAttr == "t-1")
	{
		Log_TestInfo("Can't find any shore on island: " + _island);
		return "";
	}
	return arDest.(sAttr);
}

string GetRandomIslandId()
{
	int iNum;
	aref arDest, arImt;
	string sAttr;

	makearef(arDest, NullCharacter.TravelMap.Islands);
	iNum = GetAttributesNum(arDest);
    iNum = rand(iNum-1);

    arImt = GetAttributeN(arDest, iNum);
	return GetAttributeName(arImt);
}

//navy--> переписано под полную карту
void SetSmugglersTravelDestination(aref arDest)
{
	string sIsland = Islands[GetCharacterCurrentIsland(pchar)].id;
	string sTown = FindTownOnIsland(sIsland);
	if (sTown == "")
	{
		trace("Can't find town on ISLAND: " + sIsland + ".");
		return;
	}

	int i = 1;
	string sTargetIsland = GetRandomIslandId();	//получаем рандомный остров
	while (GetCityNameByIsland(sTargetIsland) == "None") //ищем есть ли на острове колония
	{
		i++;
		sTargetIsland = GetRandomIslandId();	//ищем повторно
	}
	string sTargetTown = FindTownOnIsland(sTargetIsland); //присваеваем колонию, в которую направляемся

	DeleteAttribute(arDest, "destination");
	arDest.destination.days = rand(2) + CalculateColonyDistance(sTown, sTargetTown);	//новый расчет дней
	arDest.destination = sTargetTown;
	arDest.destination.loc = GetIslandRandomShoreId(sTargetIsland);
	//пишу стандартные аттрибуты, везде будут они.
	arDest.destination.group = "reload"; 
	arDest.destination.locator = "sea";

	Log_TestInfo("SetSmugglersTravelDestination: выбран остров " + sTargetIsland + ", количество попыток " + i);
}

//получить ID города на острове.
string FindTownOnIsland(string _island)
{
	for (int i = 0; i < MAX_COLONIES; i++)
	{
		if (Colonies[i].island == _island)
		{
			return Colonies[i].id;
		}
	}
	return "";
}

//получить ID города на острове где сейчас ГГ.
string GetCurrentTown()
{
	ref loc;
	int iColony, iLoc;

	iLoc = FindLoadedLocation();
	if (iLoc < 0) return "";

	loc = &Locations[iLoc];
	iColony = -1;
	if(CheckAttribute(loc, "fastreload"))
	{
		iColony = FindColony(loc.fastreload);
	}
	if(iColony == -1)
	{
		return "";
	}
	return Colonies[iColony].id;
}

//максимальное время пути между двух островов.
int GetMaxDaysFromIsland2Island(string _isl1, string _isl2)
{
	if(_isl1 == "" || _isl2 == "")
	{
		return -1;
	}
	string _town1 = FindTownOnIsland(_isl1);
	string _town2 = FindTownOnIsland(_isl2);
	int _dist = CalculateColonyDistance(_town1, _town2);
	return makeint((_dist+1)*1.1); //было просто +2 дня, переделываю на частично пропорциональное
}

string GetRandomUninhabitatIsland()
{
	string sTemp;
	int iRand = rand(3);
	switch (iRand)
	{
		case 0:
			sTemp = "Dominica";
		break;
		case 1:
			if(PChar.ColonyBuilding.Stage != "0") sTemp = "Bermudes";
			else sTemp = "Caiman";
		break;
		case 2:
			sTemp = "Terks";
		break;
		case 3:
			sTemp = "Bermudes";
		break;
		case 4:
			sTemp = "StLucia";
		break;
	}
	return sTemp;
}

#define CALCULATE_DISTANCE_MAGIC_NUMBER            1.645

//получить позицию корабля ГГ относительно координат
void CalculateXZDistance(int iX, int iZ)
{
    int iM = 1024;
    int iN = 5;
    float fN = CALCULATE_DISTANCE_MAGIC_NUMBER;

    iX = sti(worldMap.playerShipX)/fN;
    iX = iM + iX - iN;

    iZ = sti(worldMap.playerShipZ)/fN;
    iZ = iM - iZ - iN;
}
//расчет между кораблем ГГ и колонией (в днях пути)
int CalculateDistance(string sColony)
{
    int playership_x, playership_z;
    int iX, iZ;
    CalculateXZDistance(&iX, &iZ);

    playership_x = iX;
    playership_z = iZ;

    int iColony = FindColony(sColony);
    ref rColony = GetColonyByIndex(iColony);

    iX = rColony.map.x;
    iZ = rColony.map.y;
    int ipX = playership_x - iX;
    int ipZ = playership_z - iZ;
    if(ipX < 0)
    {
        ipX = -ipX;
    }
    if(ipZ < 0)
    {
        ipZ = -ipZ;
    }
    iX = 0;
    iZ = 0;

    int iDist = (ipX * ipX) + (ipZ * ipZ);
    iDist = sti(sqrt(iDist) + 0.5);
    iDist = iDist / 100;

    int iDistance = iDist;
    iDistance = iDistance * stf(worldMap.date.hourPerSec);
    if(iDistance < 2)
    {
        iDistance = 2;
    }
    return iDistance;
}
//получить позицию колонии относительно координат
void CalculateColonyXZDistance(string sFromColony, int iX, int iZ)
{
    int iFromColony = FindColony(sFromColony);
    ref rColony = GetColonyByIndex(iFromColony);
    iX = sti(rColony.map.x);
    iZ = sti(rColony.map.y);
}
//расчет дистанции между колониями (в днях пути)
int CalculateColonyDistance(string sFromColony, string sToColony)
{
    int from_x, from_z;
    int to_x, to_z;

    CalculateColonyXZDistance(&sFromColony, &from_x, &from_z);
	CalculateColonyXZDistance(&sToColony, &to_x, &to_z);

    int ipX = from_x - to_x;
    int ipZ = from_z - to_z;
    if (ipX < 0)
    {
        ipX = -ipX;
    }
    if (ipZ < 0)
    {
        ipZ = -ipZ;
    }

    int iDist = (ipX * ipX) + (ipZ * ipZ);
    iDist = sti(sqrt(iDist) + 0.5);
    iDist = iDist / 100;

    int iDistance = iDist;
    iDistance = iDistance * stf(worldMap.date.hourPerSec);
    if(iDistance < 2)
    {
        iDistance = 2;
    }
    return iDistance;
}