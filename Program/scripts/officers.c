// BOAL полностью переделано под нужны ВМЛ

// -> ugeen 27.01.09 - лочим лояльность квестовых офф-ов (всегда максимальная)
void OfficersReaction(string alignment)
{
	int iPassenger;
	int i, cn;
	ref sld;

	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (sld.alignment == alignment)
				{
					sld.loyality = makeint(sld.loyality) + 1;
				}
				else
				{
					sld.loyality = makeint(sld.loyality) - 1;
				}
			}
		}
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (sld.alignment == alignment)
				{
					sld.loyality = makeint(sld.loyality) + 1;
					if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy
				}
				else
				{
					sld.loyality = makeint(sld.loyality) - 1;
					// специально не далею приведение к 0 и мах. потому чтоб был запас минусов для проверок
					if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
				}
			}
		}
	}
}
//-> ugeen

void ChangeOfficersLoyality(string alignment, int iLoyality)
{ // aliggnment types : "bad" , "good" , "bad_all" , "good_all"

	int iPassenger;
	int i, cn;
	ref sld;

	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				switch (alignment)
				{
					case "bad":
						if (sld.alignment == alignment) sld.loyality = makeint(sld.loyality) + iLoyality;
						else 							sld.loyality = makeint(sld.loyality) - iLoyality;
					break;
					case "good":
						if (sld.alignment == alignment) sld.loyality = makeint(sld.loyality) + iLoyality;
						else 							sld.loyality = makeint(sld.loyality) - iLoyality;
					break;
					case "bad_all":
						sld.loyality = makeint(sld.loyality) - iLoyality;
					break;
					case "good_all":
						sld.loyality = makeint(sld.loyality) + iLoyality;
					break;
				}
			}
		}
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				switch (alignment)
				{
					case "bad":
						if (sld.alignment == alignment) {
							sld.loyality = makeint(sld.loyality) + iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy
						}
						else
						{
							sld.loyality = makeint(sld.loyality) - iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
						}
					break;
					case "good":
						if (sld.alignment == alignment) {
							sld.loyality = makeint(sld.loyality) + iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy
						}
						else
						{
							sld.loyality = makeint(sld.loyality) - iLoyality;
							if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
						}
					break;
					case "bad_all":
						sld.loyality = makeint(sld.loyality) - iLoyality;
						if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, -1); //navy
					break;
					case "good_all":
						sld.loyality = makeint(sld.loyality) + iLoyality;
						if (CheckAttribute(sld, "PGGAi")) PGG_ChangeRelation2MainCharacter(sld, 1); //navy
					break;
				}
			}
		}
	}
}

// результат реакции - действия офа - диалог
void OfficersReactionResult()
{
	int iPassenger;
	int i;
	ref sld;

	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return; // идёт некий другой квест с запретом выхода
	if (CheckAttribute(Pchar,"questTemp.MunityOfficerIDX") && Pchar.questTemp.MunityOfficerIDX.begin == "1") return;

	for (i = 0; i<GetPassengersQuantity(pchar); i++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
		iPassenger = GetPassenger(pchar, i);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (sld.name == "Виспер" && !CheckAttribute(sld, "PGGWhisperQuestStart") && !CheckAttribute(pchar,"GiantEvilSkeleton"))
			{
				if (GetCharacterShipClass(PChar) <= 4 && pchar.rank >= 15)
				{
					if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
					{
						sld.dialog.filename = "PGG_dialog.c";
						sld.dialog.currentnode = "Whisper_Officer";
						
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", 2.0, 0);
						chrDisableReloadToLocation = true;
						DoQuestCheckDelay("OpenTheDoors", 5.0);
					}
				}
			}
			if(sld.id == "W_Chinaman" && !CheckAttribute(sld, "ChinamanAskedSword") && sti(sld.rank) > 7)
			{
				if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
				{
					sld.dialog.filename = "Quest\WhisperLine\Whisper.c";
					sld.dialog.currentnode = "Chinaman_plead";

					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", 2.0, 0);
					//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
					//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
					chrDisableReloadToLocation = true;
					DoQuestCheckDelay("OpenTheDoors", 5.0);
				}
			}

			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld,"prisoned") && GetRemovable(sld) && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (sti(sld.loyality) < 1)
				{
					if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
					{
						sld.dialog.filename = "Enc_Officer_dialog.c";
						sld.dialog.currentnode = "WantToRemove";
				      	if (sld.sex != "woman")
						{
					    	sld.greeting = "Gr_Officer_Fired";
					    }
						DeleteAttribute(sld, "quest.officertype");

						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", 2.0, 0);
						//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
			    		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			    		chrDisableReloadToLocation = true;
			    		DoQuestCheckDelay("OpenTheDoors", 5.0);
						break;
					}
				}
			}
		}
	}
	if (chrDisableReloadToLocation) return; // уже увольняется

	if (CheckNPCQuestDate(pchar, "OfficerWantToGo") && rand(1) == 1) // только раз в день
	{
		SetNPCQuestDate(pchar, "OfficerWantToGo");
		for (i = 0; i<GetPassengersQuantity(pchar); i++)
		{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
			iPassenger = GetPassenger(pchar, i);
			if (iPassenger != -1)
			{
				sld = GetCharacter(iPassenger);
				if (!CheckAttribute(sld,"prisoned") && !CheckAttribute(sld, "OfficerWantToGo.DontGo") && GetRemovable(sld) && rand(10) == 5 && GetNpcQuestPastDayParam(sld, "HiredDate") > 60)
				{
					if (sld.dialog.filename == "Enc_Officer_dialog.c") // квестовые не достают
					{
						if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
						{
							sld.dialog.currentnode = "WantToGo";
							if (sld.sex != "woman")
							{
								sld.greeting           = "Gr_Officer_Salary";
							}
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", 2.0, 0);
							//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
				    		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
				    		chrDisableReloadToLocation = true;
				    		DoQuestCheckDelay("OpenTheDoors", 5.0);
							break;
						}
					}
				}
			}
		}
	}
}

bool isOfficerInShip(ref _chr, bool _withBoard)
{
	if(sti(pchar.Fellows.Passengers.navigator) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.boatswain) == sti(_chr.index))
	{
		return true;
	}

	if(sti(pchar.Fellows.Passengers.cannoner) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.doctor) == sti(_chr.index))
	{
  		return true;
	}

	if(sti(pchar.Fellows.Passengers.carpenter) == sti(_chr.index))
	{
  		return true;
	}
    if(sti(pchar.Fellows.Passengers.treasurer) == sti(_chr.index))
	{
  		return true;
	}
	if(_withBoard && IsOfficer(_chr))
	{
		return true;
	}
	return false;
}
// метод увольняет офицера - название левое, наследие к3
void CheckForReleaseOfficer(int iCharIndex)
{
	if(sti(pchar.Fellows.Passengers.navigator) == iCharIndex)
	{
		pchar.Fellows.Passengers.navigator = -1;
		DeleteAttribute(&characters[iCharIndex], "navigator"); // совместитель дожности
	}

	if(sti(pchar.Fellows.Passengers.boatswain) == iCharIndex)
	{
		pchar.Fellows.Passengers.boatswain = -1;
		DeleteAttribute(&characters[iCharIndex], "boatswain"); // совместитель дожности
	}

	if(sti(pchar.Fellows.Passengers.cannoner) == iCharIndex)
	{
		pchar.Fellows.Passengers.cannoner = -1;
		DeleteAttribute(&characters[iCharIndex], "cannoner"); // совместитель дожности
	}

	if(sti(pchar.Fellows.Passengers.doctor) == iCharIndex)
	{
		pchar.Fellows.Passengers.doctor = -1;
		DeleteAttribute(&characters[iCharIndex], "doctor"); // совместитель дожности
	}

	if(sti(pchar.Fellows.Passengers.carpenter) == iCharIndex)
	{
		pchar.Fellows.Passengers.carpenter = -1;
		DeleteAttribute(&characters[iCharIndex], "carpenter"); // совместитель дожности
	}

    if(sti(pchar.Fellows.Passengers.treasurer) == iCharIndex)
	{
		pchar.Fellows.Passengers.treasurer = -1;
		DeleteAttribute(&characters[iCharIndex], "treasurer"); // совместитель дожности
	}

	//if (IsOfficer(&characters[iCharIndex]) == true)
	//{
		// все проверки внутри,  иначе не работает на трупе
		RemoveOfficersIndex(pchar, iCharIndex);
		DeleteAttribute(&characters[iCharIndex], "fighter"); // совместитель дожности
	//}
	DeleteAttribute(&characters[iCharIndex], "isfree"); // для формы ф2, название странное - обратный смысл, если есть, то занят
}

//////////////// OFFICER ////////////////
void SetOfficerParam(ref Npchar, int _type)
{
	Npchar.quest.officertype_2 = ""; //mercen_";
    switch(_type)
	{
		case 0:
		    SetRandSPECIAL_K(Npchar);  // вот сюда методы  под каждого типа оффов
			Npchar.quest.officertype = "boatswain";
			Npchar.quest.officertype_2 = RandPhraseSimple("Могу и доктором побыть, если припрёт. ", "Ещё умею матросов беречь, кости им вправлять, когда подранят. ");
		break;

		case 1:
		    SetRandSPECIAL_K(Npchar);
			Npchar.quest.officertype = "cannoner";
		break;

		case 2:
		    SetRandSPECIAL_K(Npchar);
			Npchar.quest.officertype_2 = RandPhraseSimple("Могу и корабль починить помочь. ", "Ещё умею с пилой и рубанком обращаться. ");
			Npchar.quest.officertype = "treasurer";
		break;

		case 3:
		    SetRandSPECIAL_K(Npchar);
			Npchar.quest.officertype_2 = RandPhraseSimple("Ещё поверхностно медицину знаю. ", "Врачём, конечно, не считаюсь, но подскажу и в этом. ");
			Npchar.quest.officertype = "navigator";
		break;

        case 4:
		    SetRandSPECIAL_F(Npchar);
			Npchar.quest.officertype = "fighter";
		break;
	}
	CalculateTypeSkillsForRank(npchar, sti(pchar.rank) + rand(2), npchar.quest.officertype, 0.1);
    Npchar.reputation = 10 + rand(80);
    // пристрастие офицера -->
    Npchar.loyality = 5 + rand(10);
    if (sti(Npchar.reputation) >= 40)//почему нейтрал считается хорошим?
    {
        Npchar.alignment = "good";
    }
    else
    {
        Npchar.alignment = "bad";
    }

	Npchar.officerequip = true;
    LAi_NPC_Equip(Npchar, sti(Npchar.rank), true, true); // fix 101104 выдадим все заново!!!!

    SetFantomHP(Npchar);

    Npchar.quest.OfficerPrice    = (11 + 2*sti(Npchar.rank))*(150 + MOD_SKILL_ENEMY_RATE*20) + rand(5)*10;
    Npchar.quest.OfficerLowPrice = makeint(sti(Npchar.quest.OfficerPrice)/1.5 + 0.5);
	SetSpeciality(Npchar, PerksChars());
}

int FindFreeRandomOfficer()
{
	int Counter, OfficerIdx;
	string OfficerId;
	// special -->
	if (GetCharacterMaxOfficersQty(Pchar) < (GetNotQuestPassengersQuantity(Pchar) + GetCompanionQuantity(Pchar) - 1)) {pchar.LeadershipLose = true; return -1;}
	if (GetCharacterMaxOfficersQty(Pchar) == (GetNotQuestPassengersQuantity(Pchar) + GetCompanionQuantity(Pchar) - 1)) {DeleteAttribute(pchar,"LeadershipLose"); return 0;}
	else DeleteAttribute(pchar,"LeadershipLose");
	return 1;
}
void LandEnc_OfficerHired()
{
	ref sld = &Characters[sti(Pchar.questTemp.HiringOfficerIDX)];
    sld.Money = 0; // деньги
	sld.Payment = true;
	AddPassenger(pchar, sld, false);

	sld.location = "None";
	sld.Dialog.CurrentNode = "hired";
	/*if (sld.sex == "man") sld.greeting = "Gr_officer";
	else sld.greeting = "Gr_Danielle";*/
	// boal новый учет зп -->
	sld.Payment = true;  // признак офицера для +1 предметов
	sld.DontClearDead = true;  // не убирать труп
	// boal новый учет зп <--
	DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
	DeleteAttribute(sld, "LifeDay") // постоянный
	SaveCurrentNpcQuestDateParam(sld, "HiredDate"); // дата найма
}

void LandEnc_OfficerStay()
{
    SetCharacterTask_Stay(Characters[makeint(Pchar.questTemp.HiringOfficerIDX)]);
    Characters[makeint(Pchar.questTemp.HiringOfficerIDX)].chr_ai.tmpl = LAI_TMPL_STAY;
    DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
}

void LandEnc_OfficerFired()
{
	ref sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
	RemoveCharacterCompanion(pchar, sld);
	LAi_SetCitizenType(sld);
	sld.location = "none";
	if (sld.sex != "woman")
	{
    	sld.greeting = "Gr_Officer_Fired";
    }
    sld.LifeDay = 0; // стереть при выходе
    DeleteAttribute(sld, "Payment"); // признак офицера для +1 предметов
	if (CheckAttribute(sld,"OfficerInStockMan"))
	{
		DeleteAttribute(sld, "OfficerInStockMan");
		ref ch = CharacterFromID("MalteseOrderCharacter");
		ch.Portman	= sti(ch.Portman) - 1;
		pchar.OfficerInStock = sti(pchar.OfficerInStock) - 1;
	}
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");
}

bool SetOfficerToMushketer(ref rCharacter, string sMushket, bool _ToMushketer)
{
	int iItem;
	string sLastGun = "";

	if(_ToMushketer && sMushket != "") // Делаем мушкетером
	{
		iItem = GetItemIndex(sMushket);
		if(iItem == -1) return false;
		sLastGun = GetCharacterEquipByGroup(rCharacter, GUN_ITEM_TYPE);
		rCharacter.DefaultAnimation = rCharacter.model.Animation;
		rCharacter.IsMushketer = true; // Ставим флаг "мушкетер"
		rCharacter.IsMushketer.MushketID = sMushket; // Запомним, какой мушкет надели
		rCharacter.IsMushketer.LastGunID = sLastGun; // Запомним ID предыдущего пистоля
		rCharacter.model = rCharacter.model + "_mush";
		if (rCharacter.sex != "woman")
		{
			rCharacter.model.animation = "mushketer"; // Сменим анимацию
		}
		else
		{
			aref weapon;
			Items_FindItem(sMushket, &weapon);
			if (CheckAttribute(weapon, "fromHip"))
			{
				rCharacter.model.animation = "mushketer_whisper_short"; // Сменим анимацию
			}
			else
			{
				rCharacter.model.animation = "mushketer_whisper"; // Сменим анимацию
			}
		}
		Characters_RefreshModel(rCharacter); // Обновим модель. Важно: обновлять модель нужно ДО экипировки мушкетом
		EquipCharacterByItem(rCharacter, sMushket); // Экипируем мушкет
		rCharacter.Equip.TempGunID = sLastGun; // Пистоль оставляем экипированным, но в другой группе
		if (!CheckAttribute(rCharacter, "MusketerDistance")) rCharacter.MusketerDistance = 10.0;
		rCharacter.isMusketer = true;
		rCharacter.isMusketer.weapon = true;
		LAi_SetOfficerType(rCharacter);
	}
	else // Делаем обычным фехтовальщиком
	{
		rCharacter.model = FindStringBeforeChar(rCharacter.model, "_mush"); // Вернем модель и анимацию
		rCharacter.model.Animation = rCharacter.DefaultAnimation;
		Characters_RefreshModel(rCharacter);
		RemoveCharacterEquip(rCharacter, GUN_ITEM_TYPE); // cнимем мушкет
		if(rCharacter.IsMushketer.LastGunID != "" && GetCharacterItem(rCharacter, rCharacter.IsMushketer.LastGunID) > 0)
		{
			EquipCharacterByItem(rCharacter, rCharacter.IsMushketer.LastGunID); // Оденем прошлый пистоль
		}
		DeleteAttribute(rCharacter, "IsMushketer");
		DeleteAttribute(rCharacter, "Equip.TempGunID");
		DeleteAttribute(rCharacter, "MusketerDistance");
		DeleteAttribute(rCharacter, "isMusketer");
		LAi_SetOfficerType(rCharacter);
	}
	return true;
}
