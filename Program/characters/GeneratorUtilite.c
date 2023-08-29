// BOAL методы для генератора НПС

// здесь можно объявить глобальные переменные
int m_rank_bonus, e_rank_bonus;

// генерим НПС приблизительного ранга
void SetFantomParamFromRank(ref NPchar, int  rank, bool setEquip)
{
	SetRandSPECIAL(Npchar);
	CalculateSkillsFromRank(Npchar, rank);
	SetFantomHP(NPchar);

	if (setEquip) LAi_NPC_Equip(NPchar, sti(NPchar.rank), true, true); // выдаем эквип

	if (IsCharacterPerkOn(NPchar, "Ciras") && rand(4)==0) SetFantomWearCirass(NPChar) // одеваем кирасу

	if (!CheckAttribute(NPchar,"id")) { SetSpeciality(NPchar, PerksChars()); return; }

	RemoveSpeciality(NPchar);
	switch (NPchar.id)
	{
		case "Tichingitu": SetCharacterPerk(NPchar, "Buccaneer"); break;
		case "Andreas_Fickler": SetCharacterPerk(NPchar, "Trader"); break;
		case "OfMush1": SetCharacterPerk(NPchar, "Buccaneer"); break;
		case "OfMush2": SetCharacterPerk(NPchar, "Buccaneer"); break;
		case "OffMushketer": SetCharacterPerk(NPchar, "Buccaneer"); break;
		case "zpqCaptainOf": SetCharacterPerk(NPchar, "Adventurer"); break;
		case "Daniel": SetCharacterPerk(NPchar, "Grunt"); break;
		case "W_Lejitos": SetCharacterPerk(NPchar, "Grunt"); break;
		case "Jafarry": SetCharacterPerk(NPchar, "Fencer"); break;
		case "Beatrice": SetCharacterPerk(NPchar, "SeaWolf"); break;
		case "Angellica": SetCharacterPerk(NPchar, "SeaWolf"); break;
		case "SharpOf": SetCharacterPerk(NPchar, "SeaWolf"); break;
		case "W_Chinaman": SetCharacterPerk(NPchar, "SeaWolf"); break;
		case "Mechanic1": SetCharacterPerk(NPchar, "Adventurer"); break;
		case "DanielleOff": SetCharacterPerk(NPchar, "Fencer"); break;
		case "Sharp_Sibling": SetCharacterPerk(NPchar, "Fencer"); break;
		case "James_Callow": SetCharacterPerk(NPchar, "Fencer"); break;
		case "PGG_Undead": SetCharacterPerk(NPchar, "Buccaneer"); break;
		case "Undead_Jessika": SetCharacterPerk(NPchar, "Fencer"); break;
		case "Undead_Indeech": SetCharacterPerk(NPchar, "SeaWolf"); break;
		case "Undead_Blue": SetCharacterPerk(NPchar, "Grunt"); break;
		case "Undead_Red": SetCharacterPerk(NPchar, "Adventurer"); break;
		case "Undead_Green": SetCharacterPerk(NPchar, "SeaWolf"); break;
		case "Maltese": SetCharacterPerk(NPchar, "Fencer"); break;
		else: SetSpeciality(NPchar, PerksChars()); break;
	}
}

void SetFantomWearCirass(ref NPChar) {
	string cirnum;
	switch (rand(4))
	{
		case 0: cirnum = "cirass1"; break;
		case 1: cirnum = "cirass1"; break;
		case 2: cirnum = "cirass2"; break;
		case 3: cirnum = "cirass3"; break;
		case 4: cirnum = "cirass4"; break;
	}
	if (CheckAttribute(NPchar, "HeroModel")) // все, у кого есть что одеть
	{
		switch (cirnum)
		{
			case "cirass1": NPchar.model = GetSubStringByNum(NPchar.HeroModel, 1); break;
			case "cirass2": NPchar.model = GetSubStringByNum(NPchar.HeroModel, 2); break;
			case "cirass3": NPchar.model = GetSubStringByNum(NPchar.HeroModel, 3); break;
			case "cirass4": NPchar.model = GetSubStringByNum(NPchar.HeroModel, 4); break;
		}
	}
	NPchar.cirassId = Items_FindItemIdx(cirnum);
	Log_TestInfo("Персонаж "+NPchar.name+" получил кирасу "+cirnum);
}

void SetFantomParamFromRank_PPG(ref NPchar, int  rank, bool setEquip)   //WW
{
    SetRandSPECIAL_PGG(Npchar);
    CalculateSkillsForRank(Npchar, rank);
    SetFantomHP(NPchar);
	if (setEquip)
    {
	    LAi_NPC_Equip(NPchar, sti(NPchar.rank), true, true);
    }
	SetSpeciality(NPchar, PerksChars());
	//SetCharacterPerk(NPchar, PerksChars());
	/*if (IsCharacterPerkOn(NPchar, "Ciras") && rand(4)==0)
	{
		string cirnum;
		switch (rand(4))
		{
			case 0: cirnum = "cirass1"; break;
			case 1: cirnum = "cirass1"; break;
			case 2: cirnum = "cirass2"; break;
			case 3: cirnum = "cirass3"; break;
			case 4: cirnum = "cirass4"; break;
		}
		NPchar.cirassId = Items_FindItemIdx(cirnum);
		Log_TestInfo("Персонаж "+NPchar.name+" получил кирасу "+cirnum);
	} */
}
void Train_PPG(ref NPchar, bool setEquip bool increaseRank)   //WW
{
	string prevPerk = "Adventurer";
	if (IsCharacterPerkOn(NPchar, "Adventurer")) { prevPerk = "Adventurer";}
	if (IsCharacterPerkOn(NPchar, "SeaWolf")) { prevPerk = "SeaWolf";}
	if (IsCharacterPerkOn(NPchar, "Agent")) { prevPerk = "Agent";}
	if (IsCharacterPerkOn(NPchar, "Grunt")) { prevPerk = "Grunt";}
	if (IsCharacterPerkOn(NPchar, "Fencer")) { prevPerk = "Fencer";}
	if (IsCharacterPerkOn(NPchar, "Trader")) { prevPerk = "Trader";}
	if (IsCharacterPerkOn(NPchar, "Buccaneer")) { prevPerk = "Buccaneer";}

	int rank, hp;
	if (increaseRank)
	{
		if (!CheckAttribute(NPchar, "PGGAi.Boosted"))
		{
			rank = sti(NPchar.rank) + (sti(NPchar.rank) * 0.2) + MOD_SKILL_ENEMY_RATE*3;
			NPchar.cirassId = Items_FindItemIdx("cirass"+(rand(3)+2));
			CalculateSkillsFromRank(Npchar, rank);
			Npchar.rank = rank;
			hp = LAi_GetCharacterMaxHP(NPchar);
			LAi_SetHP(NPchar, hp*1.7, hp*1.7);
			SetCharacterPerk(NPchar, prevPerk);
			NPchar.PGGAi.Boosted = true;
		}
		int moneyboost = sti(NPchar.rank) * 25000 + rand(1000) - rand(1000);
		PGG_AddMoneyToCharacter(NPchar, moneyboost);
	}
	else
	{
		if (!CheckAttribute(NPchar, "PGGAi.Boosted")) // фактически дыра без проверки атрибута
		{
			rank = sti(pchar.rank) + 10; 
			CalculateSkillsFromRank(Npchar, rank);
			Npchar.rank = rank;
			hp = LAi_GetCharacterMaxHP(NPchar);
			LAi_SetHP(NPchar, hp*1.6, hp*1.6);
			SetCharacterPerk(NPchar, prevPerk);
			NPchar.PGGAi.Boosted = true;
			NPchar.money = 0;
		}
	}

	if (setEquip)
	{
		LAi_NPC_Equip(NPchar, sti(NPchar.rank), true, true);
	}
	
	if (!CheckAttribute(npchar,"ssbackup")) //backup stats before buff
	{
		npchar.ssbackup = npchar.special.strength; 
		npchar.esbackup = npchar.special.endurance;
		npchar.isbackup = npchar.special.intellect;
		npchar.asbackup = npchar.special.agility;
		npchar.lsbackup = npchar.special.luck;
	} 
	
	if (sti(NPchar.SPECIAL.Strength) < 10)
	{
		NPchar.SPECIAL.Strength = sti(NPchar.SPECIAL.Strength)+rand(1);
	}
	if (sti(NPchar.SPECIAL.Endurance) < 10)
	{
		NPchar.SPECIAL.Endurance = sti(NPchar.SPECIAL.Endurance)+rand(1);
	}
	if (sti(NPchar.SPECIAL.Intellect) < 10) 
	{
		NPchar.SPECIAL.Intellect = sti(NPchar.SPECIAL.Intellect)+rand(1);
	}
	if (sti(NPchar.SPECIAL.Agility) < 10) 
	{
		NPchar.SPECIAL.Agility = sti(NPchar.SPECIAL.Agility)+rand(1);
	}
	if (sti(NPchar.SPECIAL.Luck) < 10) 
	{
		NPchar.SPECIAL.Luck = sti(NPchar.SPECIAL.Luck)+rand(1);
	}

	NPchar.perks.list.AgileMan = "1";
	ApplayNewSkill(NPchar, "AgileMan", 0);

	if (increaseRank)
	{
		int sailing = sti(Npchar.skill.Sailing) + 20;
		Npchar.rank = sti(Npchar.rank)+1;
		if (sailing > 100)
		{
			Npchar.skill.Sailing = 100
		}
		else
		{
			Npchar.skill.Sailing = sailing;
		}
	}

	TakeNItems(NPchar, "Food5", 5);
	TakeNItems(NPchar, "potion2", 5);
	SetCharacterPerk(NPchar, prevPerk);
	AddBonusEnergyToCharacter (NPchar, 15);
	npchar.buffamount = sti(npchar.buffamount) + 1;
}

void Restore_PGG(ref npchar)
{
	if (!CheckAttribute(npchar,"PGGAi.Boosted")) {return; }
	RemoveBonusEnergyFromCharacter(npchar,sti(npchar.buffamount) * 15);
	npchar.SPECIAL.Strength   = sti(npchar.ssbackup);
	npchar.SPECIAL.Endurance  = sti(npchar.esbackup);
	npchar.SPECIAL.Intellect  = sti(npchar.isbackup);
	npchar.SPECIAL.Agility    = sti(npchar.asbackup);
	npchar.SPECIAL.Luck       = sti(npchar.lsbackup);
	DeleteAttribute(npchar, "ssbackup");
	DeleteAttribute(npchar, "esbackup");
	DeleteAttribute(npchar, "isbackup");
	DeleteAttribute(npchar, "asbackup");
	DeleteAttribute(npchar, "lsbackup");
	CalculateSkillsForRank(npchar,sti(pchar.rank));
	SetHealthToCharacter(npchar);
	DeleteAttribute(npchar,"perks.list.AgileMan");
	if (npchar.model.animation == "man_fast") npchar.model.animation = "man";
	if (npchar.model.animation == "Jessika_fast") npchar.model.animation = "Jessika";
	if (npchar.model.animation == "YokoDias_fast") npchar.model.animation = "YokoDias";
	if (npchar.model.animation == "Milenace_fast") npchar.model.animation = "Milenace";
	if (npchar.model.animation == "Danielle_fast") npchar.model.animation = "Danielle";
	if (npchar.model.animation == "Giant_fast") npchar.model.animation = "Giant";
	if (npchar.model.animation == "Moscovit_fast") npchar.model.animation = "Moscovit";
	if (npchar.model.animation == "Chani_fast") npchar.model.animation = "Chani";
	if (npchar.model.animation == "skeleton_fast") npchar.model.animation = "skeleton";
}

// расчитать скиллы персонажу для заданного ранга на основе ПИРАТЕС
void CalculateSkillsForRank (ref npchar, int rank)
{
	int i, ControlSum, Correction, CorrectionSum; 
	float TempF, CorrectionCoeff;
	string TempStr;
	if (rank <= 0) {Log_TestInfo("Wrong argument"); return;}
	npchar.rank_exp = 0;
	ClearCharacterExpRate(npchar);
	npchar.rank = rank;
	Correction = 0;
	for (i = 1; i < 15; i++) // вычисления общего кол-ва скиллов на 1 ранге
	{
		TempStr = GetSkillNameByIdx(i);
		TempF = MOD_EXP_RATE / GetCharacterExpRate(npchar,TempStr);
		Correction += makeint(TempF);
	}
	ControlSum = GetCharacterRankRate(npchar) * (rank - 1) + Correction; // необходимое кол-во скиллов на нужном ранге
	if (ControlSum >= 1400) // для высоких рангов
	{
		SetSelfSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
        SetShipSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
		return;
	}
	CorrectionCoeff = 0;
	for (i = 1; i < 8; i++)
	{
		TempStr = GetSkillNameByTRIdx("SPECIALType", i);
		CorrectionCoeff += sti(npchar.SPECIAL.(TempStr));
	}
	CorrectionCoeff = 70 / (70 - (70 - CorrectionCoeff)) / GetExpAcceleration(10 - (70 - CorrectionCoeff) / 7); // магия, уменьшает количество итераций требуемых для расчета
	Log_TestInfo("Coeff:" + FloatToString(CorrectionCoeff,3));
	
	Log_TestInfo("ControlSum:" + ControlSum);
	for (i = 1; i < 15; i++)
	{	
		TempStr = GetSkillNameByIdx(i);
		TempF = MOD_EXP_RATE / GetCharacterExpRate(npchar,TempStr);
		Log_TestInfo(TempStr + ":" + FloatToString(TempF,1));
		npchar.skill.(TempStr) = makeint(makeint(TempF) +  CorrectionCoeff * TempF / 10 * (rank - 1) * GetCharacterRankRate(npchar) / 14); 
	}
	Log_TestInfo("Total amount of skills on 1 rank:" + Correction);
	CorrectSkillParam(npchar);
	CorrectionSum = sti(Npchar.skill.FencingLight) + sti(Npchar.skill.FencingHeavy) + sti(Npchar.skill.Fortune) +
                    sti(Npchar.skill.Pistol) + sti(Npchar.skill.Leadership) + sti(Npchar.skill.Fencing) +
                    sti(Npchar.skill.Sailing) + sti(Npchar.skill.Accuracy) + sti(Npchar.skill.Cannons) +
                    sti(Npchar.skill.Grappling) + sti(Npchar.skill.Repair) + sti(Npchar.skill.Defence) +
                    sti(Npchar.skill.Commerce) + sti(Npchar.skill.Sneak);
	Log_TestInfo("CorrectionSum:" + CorrectionSum);
	Correction = ControlSum - CorrectionSum;
	Log_TestInfo("Correction2:" + Correction);
	if (Correction == 0) {return; Log_TestInfo("Finalized after first calculation");}
	while (Correction != 0)
	{
		if (Correction > 0)
		{
			for (i = 1; i < 15; i++) 
			{	
				if (Correction == 0) {Log_TestInfo("Finalized after correction"); return;}
				TempStr = GetSkillNameByIdx(i);
				if (npchar.skill.(TempStr) != SKILL_MAX)
				{
					npchar.skill.(TempStr) = sti(npchar.skill.(TempStr)) + 1;
					Correction -= 1;
				}
			}
		}
		else
		{
			for (i = 1; i < 15; i++) 
			{	
				if (Correction == 0) {Log_TestInfo("Finalized after correction"); return;}
				TempStr = GetSkillNameByIdx(i);
				if (npchar.skill.(TempStr) != SKILL_MAX)
				{
					npchar.skill.(TempStr) = sti(npchar.skill.(TempStr)) - 1;
					Correction += 1;
				}
			}
		}
	}
	return;
}

// расчитать скиллы персонажу для заданного ранга и типа на основе ПИРАТЕС с коэффициентом динамики. (для офицеров)
void CalculateTypeSkillsForRank (ref npchar, int rank, string type, float coeff)
{
	int i, BasePriority, BaseSidePriority, ControlSum, Correction, CorrectionSum; 
	float TempF, CorrectionCoeff, Priority1, Priority2, Priority3, Priority4, Deviation;
	string TempStr, TypeMainPriority, TypeSidePriority;
	if (rank <= 0) {Log_TestInfo("Wrong argument"); return;}
	npchar.rank_exp = 0;
	ClearCharacterExpRate(npchar);
	npchar.rank = rank;
	Correction = 0;
	for (i = 1; i < 15; i++) // вычисления общего кол-ва скиллов на 1 ранге
	{
		TempStr = GetSkillNameByIdx(i);
		TempF = MOD_EXP_RATE / GetCharacterExpRate(npchar,TempStr);
		Correction += makeint(TempF);
	}

	ControlSum = GetCharacterRankRate(npchar) * (rank - 1) + Correction; // необходимое кол-во скиллов на нужном ранге
	if (ControlSum >= 1400) // для высоких рангов
	{
		SetSelfSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
        SetShipSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
		return;
	}
	CorrectionCoeff = 0;
	for (i = 1; i < 8; i++)
	{
		TempStr = GetSkillNameByTRIdx("SPECIALType", i);
		CorrectionCoeff += sti(npchar.SPECIAL.(TempStr));
	}
	CorrectionCoeff = 70 / (70 - (70 - CorrectionCoeff)) / GetExpAcceleration(10 - (70 - CorrectionCoeff) / 7); // магия, уменьшает количество итераций требуемых для расчета
	//Log_TestInfo("Coeff:" + FloatToString(CorrectionCoeff,3));
	//Log_TestInfo("ControlSum:" + ControlSum);
	Deviation = 1 - coeff + frand(coeff * 2); // коэффициент динамики
	//Log_TestInfo("Deviation:" + FloatToString(Deviation,2));
	BasePriority = makeint(15 * Deviation); // для базового усиления профильного навыка
	BaseSidePriority = makeint(5 * Deviation); // для базового усиления дополнительного навыка
	TypeSidePriority = "unknown";
	Priority3 = 1.5 * Deviation; // для упора на определённый основной навык
	Priority4 = 1.4 * Deviation; // для упора на определённый дополнительный навык
	switch(type)
	{
		case "boatswain":		
			Priority1 = 0.8 - (Priority3 - 1.2) / 12 - (Priority4 - 1.2) / 12; //для личных умений
			Priority2 = 1.2 - (Priority3 - 1.2) / 12 - (Priority4 - 1.2) / 12; // для корабельных умений
			if (rand(1) == 1)
			{
				TypeMainPriority = SKILL_GRAPPLING;
				TypeSidePriority = SKILL_DEFENCE;	
			}
			else
			{
				TypeSidePriority = SKILL_GRAPPLING;
				TypeMainPriority = SKILL_DEFENCE;	
			}
		break;
		case "cannoner":
			Priority1 = 0.8 - (Priority3 - 1.2) / 12 - (Priority4 - 1.2) / 12;
			Priority2 = 1.2 - (Priority3 - 1.2) / 12 - (Priority4 - 1.2) / 12;
			if (rand(1) == 1)
			{
				TypeMainPriority = SKILL_CANNONS;
				TypeSidePriority = SKILL_ACCURACY;	
			}
			else
			{
				TypeSidePriority = SKILL_CANNONS;
				TypeMainPriority = SKILL_ACCURACY;	
			}
		break;
		case "treasurer":
			Priority1 = 0.8 - (Priority3 - 1.2) / 12 - (Priority4 - 1.2) / 12;
			Priority2 = 1.2 - (Priority3 - 1.2) / 12 - (Priority4 - 1.2) / 12;
			if (rand(1) == 1)
			{
				TypeMainPriority = SKILL_REPAIR;
				TypeSidePriority = SKILL_COMMERCE;	
			}
			else
			{
				TypeSidePriority = SKILL_REPAIR;
				TypeMainPriority = SKILL_COMMERCE;	
			}
		break;
		case "navigator":
			Priority1 = 0.8 - (Priority3 - 1.2) / 13;
			Priority2 = 1.2 - (Priority3 - 1.2) / 13;
			TypeMainPriority = SKILL_SAILING;
		break;
		case "fighter": 
			Priority1 = 1.2 - (Priority3 - 1.2) / 13;
			Priority2 = 0.8 - (Priority3 - 1.2) / 13;
			switch(rand(2))
			{
				case 0: TypeMainPriority = SKILL_F_LIGHT; break;
				case 1:	TypeMainPriority = SKILL_FENCING; break;
				case 2:	TypeMainPriority = SKILL_F_HEAVY; break;
			}
		break;
	}
	for (i = 1; i < 8; i++) // личные скиллы с учетом приоритета типа
	{	
		TempStr = GetSkillNameByIdx(i);
		TempF = MOD_EXP_RATE / GetCharacterExpRate(npchar,TempStr);
		//Log_TestInfo(TempStr + ":" + FloatToString(TempF,1));
		npchar.skill.(TempStr) = makeint(makeint(TempF) +  CorrectionCoeff * TempF / 10 * (rank - 1) * GetCharacterRankRate(npchar) / 14 * Priority1); 
	}
	for (i = 8; i < 15; i++) // корабельные скиллы с учетом приоритета типа
	{	
		TempStr = GetSkillNameByIdx(i);
		TempF = MOD_EXP_RATE / GetCharacterExpRate(npchar,TempStr);
		//Log_TestInfo(TempStr + ":" + FloatToString(TempF,1));
		npchar.skill.(TempStr) = makeint(makeint(TempF) +  CorrectionCoeff * TempF / 10 * (rank - 1) * GetCharacterRankRate(npchar) / 14 * Priority2); 
	}
	TempF = MOD_EXP_RATE / GetCharacterExpRate(npchar,TypeMainPriority);
	npchar.skill.(TypeMainPriority) = makeint(makeint(TempF) +  CorrectionCoeff * TempF / 10 * (rank - 1) * GetCharacterRankRate(npchar) / 14 * Priority3); 
	TempF = MOD_EXP_RATE / GetCharacterExpRate(npchar,TypeSidePriority);
	npchar.skill.(TypeSidePriority) = makeint(makeint(TempF) +  CorrectionCoeff * TempF / 10 * (rank - 1) * GetCharacterRankRate(npchar) / 14 * Priority4); 
	if(sti(npchar.skill.(TypeMainPriority)) + BasePriority <= SKILL_MAX)
	{
		npchar.skill.(TypeMainPriority) = sti(npchar.skill.(TypeMainPriority)) + BasePriority;
		npchar.rank_exp = BasePriority;
		ControlSum += BasePriority;
	}
	else
	{
		npchar.skill.(TypeMainPriority) = SKILL_MAX;
		npchar.rank_exp = SKILL_MAX - sti(npchar.skill.(TypeMainPriority));
		ControlSum += sti(npchar.rank_exp);
	}
	if(TypeSidePriority != "unknown")
	{
		if(sti(npchar.skill.(TypeSidePriority)) + BaseSidePriority <= SKILL_MAX)
		{
			npchar.skill.(TypeSidePriority) = sti(npchar.skill.(TypeSidePriority)) + BaseSidePriority;
			npchar.rank_exp = sti(npchar.rank_exp) + BaseSidePriority;
			ControlSum += BaseSidePriority;
		}
		else
		{
			npchar.skill.(TypeSidePriority) = SKILL_MAX;
			npchar.rank_exp = sti(npchar.rank_exp) + SKILL_MAX - sti(npchar.skill.(TypeSidePriority));
			ControlSum += SKILL_MAX - sti(npchar.skill.(TypeSidePriority));
		}
	}
	//Log_TestInfo("Total amount of skills on 1 rank:" + Correction);
	CorrectSkillParam(npchar);
	CorrectionSum = sti(Npchar.skill.FencingLight) + sti(Npchar.skill.FencingHeavy) + sti(Npchar.skill.Fortune) +
                    sti(Npchar.skill.Pistol) + sti(Npchar.skill.Leadership) + sti(Npchar.skill.Fencing) +
                    sti(Npchar.skill.Sailing) + sti(Npchar.skill.Accuracy) + sti(Npchar.skill.Cannons) +
                    sti(Npchar.skill.Grappling) + sti(Npchar.skill.Repair) + sti(Npchar.skill.Defence) +
                    sti(Npchar.skill.Commerce) + sti(Npchar.skill.Sneak);
	//Log_TestInfo("CorrectionSum:" + CorrectionSum);
	Correction = ControlSum - CorrectionSum;
	//Log_TestInfo("Correction2:" + Correction);
	if (Correction == 0) {return; Log_TestInfo("Finalized after first calculation");}
	while (Correction != 0)
	{
		if (Correction > 0)
		{
			for (i = 1; i < 15; i++) 
			{	
				if (Correction == 0) {Log_TestInfo("Finalized after correction"); return;}
				TempStr = GetSkillNameByIdx(i);
				if (npchar.skill.(TempStr) != SKILL_MAX)
				{
					npchar.skill.(TempStr) = sti(npchar.skill.(TempStr)) + 1;
					Correction -= 1;
				}
			}
		}
		else
		{
			for (i = 1; i < 15; i++) 
			{	
				if (Correction == 0) {Log_TestInfo("Finalized after correction"); return;}
				TempStr = GetSkillNameByIdx(i);
				if (npchar.skill.(TempStr) != SKILL_MAX)
				{
					npchar.skill.(TempStr) = sti(npchar.skill.(TempStr)) - 1;
					Correction += 1;
				}
			}
		}
	}
	return;
}

// расчитать скилы заданного ранга, типа как от ГГ в будущем (ранг у НПС будет приблизительно, зависит от сложности)
void CalculateSkillsFromRank(ref NPchar, int  rank)
{
    float  iMiddleK;
	// вычислим средний скил к этому рангу
	iMiddleK = 6 + rank*GetCharacterRankRate(GetMainCharacter()) / 14.0;

	CalculateAppropriateSkillsParam(Npchar, iMiddleK, 5);
}
// расчет скилов от среднего скила
void CalculateAppropriateSkillsParam(ref NPchar, float  MiddleK, int _complex)
{
    //trace("CalculateAppropriateSkillsParam " + NPchar.id);
    float  fValue;

    fValue = (20 * _complex / 4.0);
    Npchar.skill.FencingLight = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.2)) - 24));
    Npchar.skill.Fencing      = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.0)) - 20));
    Npchar.skill.FencingHeavy = makeint(MiddleK + (frandSmall(fValue) + frandSmall((20* _complex / 3.5)) - 28));
    Npchar.skill.Pistol       = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Fortune      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));

    Npchar.skill.Leadership   = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Commerce     = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Sailing      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Accuracy     = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Cannons      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Grappling    = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Repair       = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Defence      = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));
    Npchar.skill.Sneak        = makeint(MiddleK + (frandSmall(fValue) + frandSmall(fValue) - 30));

    CorrectSkillParam(Npchar);

    SetRankFromSkill(Npchar);
}
void CalculateAppropriateSkills(ref NPchar)
{
    float   MiddleK;
    bool    ok;
    int     rank, i, j, k, sum, rank_bonus, base_rank;
    string  sTemp;

    SetRandSPECIAL(Npchar);
    if (false)
    {
    	MiddleK = GetMiddleMainSkill();

        CalculateAppropriateSkillsParam(Npchar, MiddleK, MOD_SKILL_ENEMY_RATE);
    }
    else
    // setting NPC skills based on main char rank and MOD_SKILL_ENEMY_RATE (Gray 14.12.2004)
    {
        rank_bonus = 0;
        sTemp = "";
		if (CheckAttribute(NPchar, "RankBonus"))
		{
			rank_bonus = sti(NPchar.RankBonus);
		    sTemp = "RankBonus: " + rank_bonus;
		}

		base_rank = 0;
		if (CheckAttribute(NPchar, "BaseRank"))
		{
			base_rank = sti(NPchar.BaseRank);
			sTemp += " BaseRank: " + base_rank;
		}

		if (sti(Pchar.rank) > base_rank) base_rank = sti(Pchar.rank);

		MiddleK = base_rank;

        ok =  (MOD_SKILL_ENEMY_RATE > 2) && (bNewCodeOn);
        if (!ok)
        {
        	ok =  (MOD_SKILL_ENEMY_RATE <= 2) && (!bNewCodeOn); // наоборот - есть - сложнее станет
        }
        ok =  (!CheckAttribute(NPchar, "OurMan")) || (ok);

  		if (!CheckAttribute(NPchar, "BaseRank") && ok) // токо Компы и не двойной учет для моря
  		{
            MiddleK = MiddleK + (MOD_SKILL_ENEMY_RATE*3-5) * 1.5;
            sTemp += " ComplexBonus = " + FloatToString((MOD_SKILL_ENEMY_RATE*3-5) * 1.5, 1);
  		}
  		rank = MakeInt(MiddleK + frandSmall(4) + frandSmall(4) + frandSmall(4) + frandSmall(4) - 8 + rank_bonus);

		if (rank < 1) rank = 1;
		if (rank > 300) rank = 300;

    	NPchar.rank = rank;
    	if (CheckAttribute(NPchar, "OurMan"))
    	{
            sTemp += " OurNPCRank: " + rank;
    	}
    	else
    	{
    	   sTemp += " NPCRank: " + rank;
        }
        //debug
        if (CheckAttribute(NPchar, "RankBonus") || CheckAttribute(NPchar, "BaseRank") || CheckAttribute(NPchar, "OurMan"))
        {
    	   //Log_TestInfo("Fantom_gen: " + sTemp);
    	}

    	if (rank > (1400 / GetCharacterRankRate(Npchar)))
		{
            SetSelfSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
            SetShipSkill(Npchar, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX, SKILL_MAX);
			return;
		}
        CalculateSkillsFromRank(Npchar, rank);
    }
}

void SetRankFromSkill(ref Npchar)
{	
	if (CheckAttribute(NPchar,"indeprank")) return;
    Npchar.rank = 1 + makeint( (sti(Npchar.skill.FencingLight) + sti(Npchar.skill.FencingHeavy) + sti(Npchar.skill.Fortune) +
                           sti(Npchar.skill.Pistol) + sti(Npchar.skill.Leadership) + sti(Npchar.skill.Fencing) +
                           sti(Npchar.skill.Sailing) + sti(Npchar.skill.Accuracy) + sti(Npchar.skill.Cannons) +
                           sti(Npchar.skill.Grappling) + sti(Npchar.skill.Repair) + sti(Npchar.skill.Defence) +
                           sti(Npchar.skill.Commerce) + sti(Npchar.skill.Sneak) - 84) / GetCharacterRankRate(Npchar) );
    if (sti(Npchar.rank) < 1)
    {
        Npchar.rank = 1;
    }
}

void CorrectSkillParam(ref Npchar)
{
    int i;
    string  skillName;

    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        if(sti(Npchar.skill.(skillName)) > SKILL_MAX) Npchar.skill.(skillName) = SKILL_MAX;
        if(sti(Npchar.skill.(skillName)) < 1)         Npchar.skill.(skillName) = 1;
    }
}
float GetMiddleMainSkill()
{
    float MiddleK;

    MiddleK = makefloat(GetSkillSum(Pchar) / 14.0) ;

    return  MiddleK;
}
int GetSkillSum(ref Npchar)
{
    int i, sum;
    string  skillName;

	sum = 0;
    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        sum += sti(Npchar.skill.(skillName));
    }
    return sum;
}

int GetSPECIALSum(ref Npchar)
{
    int i, sum;
    string  skillName;

	sum = 0;
    for (i=15; i<22; i++)
    {
        skillName = GetSkillNameByIdx(i);
        sum += sti(Npchar.SPECIAL.(skillName));
    }
    return sum;
}
// boal new formula 10.12.03 // очень важная раздача скилов, зависит от сложности <--

void SetFantomParam(ref _pchar)
{
    SetFantomParamCommon(_pchar);
	SetSpeciality(_pchar, PerksChars());
}

void SetFantomParamCommon(ref _pchar)
{
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
    // тут трем накопивщиеся сабли и корабли 290704 BOAL -->
    DeleteAttribute(_pchar, "Items");
    // тут трем накопивщиеся сабли и корабли 290704 BOAL <--
    LAi_NPC_Equip(_pchar, sti(_pchar.rank), true, true);
    //AntiCheat(_pchar);
}

void SetFantomParamEncout(ref _pchar)  // выдача сабель и НР отдельно	//TO DO - не используется - удалить функцию
{
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
    // тут трем накопивщиеся сабли и корабли 290704 BOAL -->
    DeleteAttribute(_pchar, "Items");
    DeleteAttribute(_pchar, "equip");
	//DeleteAttribute(_pchar, "perks.list");
	DeleteAllPerksExceptChar(_pchar);
    //LAi_NPC_EquipPerk(_pchar, "fantom");
	//GiveItem2Character(_pchar, "unarmed");
	//EquipCharacterByItem(_pchar, "unarmed");
    // тут трем накопивщиеся сабли и корабли 290704 BOAL <--
    //AntiCheat(_pchar);
}

void SetSeaFantomParam(ref _pchar, string type)
{
//похоже, это уже неактуально
/*	ref MChar;
	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		Log_TestInfo("If you see this, feel free to kick Gray: " + MChar.EnemyRank);
		DeleteAttribute(MChar, "EnemyRank");
	}
*/
	Fantom_SetRandomSkills(_pchar, type); // там вызов CalculateAppropriateSkills(_pchar); + бонус от класса корабля
	Fantom_SetRandomMoney(_pchar, type);
	Fantom_SetRandomCrewExp(_pchar, type);
	DeleteAttribute(_pchar, "items");

	SetFantomHP(_pchar);

	SetSpeciality(_pchar, PerksChars()); //выдаём характер кэпам случайных энкаунтеров, убрал его из экипировки
	LAi_NPC_Equip(_pchar, sti(_pchar.rank), true, true);
	//AntiCheat(_pchar);
}
/////////////////////////////////////////////////////
// из AIFantom.c
void Fantom_SetRandomSkills(ref rFantom, string sFantomType)
{
	aref aFSkills;
	int iSClass;

    makearef(aFSkills, rFantom.Skill);

	CalculateAppropriateSkills(rFantom);

	if(sFantomType == "special")
	{
		iSClass = 2 + rand(4);
	}
	else
	{
		iSClass = GetCharacterShipClass(rFantom);
	}
    // boal 15.03.04 -->
    /*
			aFSkills.Commerce	= Fantom_CalcSkill(rFantom, SKILL_COMMERCE,	iSClass, 0, 1, 0, 0, 0, 0, 0, 0, 0);
			aFSkills.Grappling	= Fantom_CalcSkill(rFantom, SKILL_GRAPPLING, iSClass, 0, 1, 0, 0, 0, 0, 0, 0, 0);
			aFSkills.Fencing	= Fantom_CalcSkill(rFantom, SKILL_FENCING,	iSClass, 0, 1, 0, 0, 0, 0, 0, 0, 0);
			aFSkills.Repair		= Fantom_CalcSkill(rFantom, SKILL_REPAIR,	iSClass, 0, 1, 0, 0, 0, 0, 0, 0, 0);
			aFSkills.Sneak		= Fantom_CalcSkill(rFantom, SKILL_SNEAK,	    iSClass, 0, 1, 0, 0, 0, 0, 0, 0, 0);
			aFSkills.Pistol   	= Fantom_CalcSkill(rFantom, SKILL_PISTOL,	iSClass, 0, 1, 0, 0, 0, 0, 0, 0, 0);
    */
    // boal 15.03.04 <--
	switch (sFantomType)
	{
		case "trade":
		// комментируем лишеие - всё равно ничего не меняют boal
            // умножение на 10 идёт внутри метода
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 2, 3, 4);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 1, 2, 3, 5, 6, 7);
			aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
		break;
		case "war":
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 5);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 1, 2, 3, 4, 6, 7);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 1, 2, 3, 4, 7, 8);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 1, 3, 4, 6, 7, 8);
			aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 7);
		break;
		case "pirate":
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 4);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 2, 3, 4, 6, 7, 8);
            aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 6);
		break;
		case "special":
            aFSkills.Leadership = Fantom_CalcSkill(rFantom, SKILL_LEADERSHIP,iSClass, 0, 0, 0, 1, 1, 2, 3, 4, 4);
            aFSkills.Accuracy	= Fantom_CalcSkill(rFantom, SKILL_ACCURACY,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Cannons	= Fantom_CalcSkill(rFantom, SKILL_CANNONS,	iSClass, 0, 0, 0, 2, 3, 4, 5, 6, 7);
			aFSkills.Sailing	= Fantom_CalcSkill(rFantom, SKILL_SAILING,	iSClass, 0, 0, 0, 2, 3, 5, 6, 8, 9);
            aFSkills.Defence	= Fantom_CalcSkill(rFantom, SKILL_DEFENCE,	iSClass, 0, 0, 0, 1, 2, 3, 4, 5, 6);
		break;
	}
    //if (sti(rFantom.rank) < 50)
    //{
	SetRankFromSkill(rFantom);
	//}
}

void SetFantomHP(ref _pchar)
{
	int hp;
	hp = GetCharacterBaseHPValue(_pchar) + (sti(_pchar.rank) * GetCharacterAddHPValue(_pchar));
	LAi_SetHP(_pchar, hp, hp);
	LAi_SetCurHPMax(_pchar);
}

void SetMonsterLoginHP(ref _pchar) // жизнь у монстров больше (рейдеры тоже тут), как и пассажиры - потенциально читовые офицеры!!
{
	int hp;
	if (true)
	{
		int rank = makeint(sti(_pchar.rank) * (1 + MOD_SKILL_ENEMY_RATE*3 / 40.0));
		hp = LAI_DEFAULT_HP_MAX + rank * 5;
		_pchar.rank = rank;
		LAi_SetHP(_pchar, hp, hp);
		LAi_SetCurHPMax(_pchar);
	}
	else
	{
		hp = LAI_DEFAULT_HP_MAX + makeint(sti(_pchar.rank)*(MOD_SKILL_ENEMY_RATE*3 / 2.0 + 5.0)) + 10;
		LAi_SetHP(_pchar, hp, hp);
		LAi_SetCurHPMax(_pchar);
	}
}

/// метод расчета от опыта солдат, даёт бонус в НР (или пенальти)
bool GetBoardingHP(ref mchr, ref echr, ref float_boarding_player_hp, ref float_boarding_enemy_hp)
{
	float b_p_hp, b_e_hp;
	float moral;
	float exp;
	b_p_hp = LAi_GetCharacterMaxHP(mchr) / 3.0;  // треть от НР кэпа идёт в базу бонуса

	exp = GetCrewExp(mchr, "Soldiers") / GetCrewExpRate() - 0.7;
	moral = 0;
	if(CheckAttribute(mchr, "ship.crew.morale"))
	{
		moral = (stf(mchr.ship.crew.morale) - MORALE_NORMAL)/(MORALE_MAX - MORALE_MIN);
		if(moral < -0.5) moral = -0.5;
		if(moral > 0.5) moral = 0.5;
	}
	exp = exp + moral;  // может быть минус
	b_p_hp = b_p_hp*exp;

	b_e_hp = 0;  // не будем рандом городить рандомом, опыт и ещё скилы кэпа, все это не зависит от ГГ, а вот ГГ бонус от опыта даем
	/*
	b_e_hp = LAi_GetCharacterMaxHP(echr) / 3.0;
	exp = GetCrewExp(echr, "Soldiers") / GetCrewExpRate();
	moral = 0;
	if(CheckAttribute(echr, "ship.crew.morale"))
	{
		moral = (stf(echr.ship.crew.morale) - MORALE_NORMAL)/(MORALE_MAX - MORALE_MIN);
		if(moral < -0.5) moral = -0.5;
		if(moral > 0.5) moral = 0.5;
	}
	exp = exp + moral;
	b_e_hp = b_e_hp*exp;
	 */
	float_boarding_player_hp   =  b_p_hp;
	float_boarding_enemy_hp    =  b_e_hp;

	return true;
}
void AddCharHP(ref _pchar, int _bonus)
{
	int hp = LAi_GetCharacterMaxHP(_pchar) + _bonus;
	if (hp < 1) hp = 1;
	LAi_SetHP(_pchar, hp, hp);
	LAi_SetCurHPMax(_pchar);
}

// в коде далее
// boarding_player_hp = boarding_player_hp + GetBoarding_player_hp_Bonus;
// boarding_enemy_hp = boarding_enemy_hp + GetBoarding_enemy_hp_Bonus;

int GetBoarding_player_hp_Bonus(int mcrew, int ecrew) // бонус от перевеса, когда if (mcrew > ecrew)
{
    m_rank_bonus = 0;
    e_rank_bonus = 0;

    //Boyer fix divide by zero error
    if(ecrew == 0) ecrew = 1;
    if (true)
	{    // только этот код
		if (mcrew > ecrew)
		{
			m_rank_bonus = makeint(0.5 * MOD_SKILL_ENEMY_RATE*3 * makefloat((mcrew - ecrew) / makefloat(ecrew)));
			Log_TestInfo("Бонус к уровню игрока за перевес в численности: " + m_rank_bonus);
		}
		return 0;
	}
	else
	{
		return makeint(5 * MOD_SKILL_ENEMY_RATE*3 * makefloat((mcrew - ecrew) / makefloat(ecrew)));
	}
}

int GetBoarding_enemy_hp_Bonus(int mcrew, int ecrew) // бонус от перевеса
{
    m_rank_bonus = 0;
    e_rank_bonus = 0;
	if (mcrew < 1) mcrew = 1;
    if (true)
	{    // только этот код
		if (ecrew > mcrew)
		{
			e_rank_bonus = makeint(2 * MOD_SKILL_ENEMY_RATE*3 * makefloat((ecrew - mcrew) / makefloat(mcrew)));
			Log_TestInfo("Бонус к уровню врагов за перевес в численности: " + e_rank_bonus);
		}
		return 0;
	}
	else
	{
		return makeint(6 * MOD_SKILL_ENEMY_RATE*3 * makefloat((ecrew - mcrew) / makefloat(mcrew)));
	}
}

float GetBoarding_player_hp(float b_p_hp) // итоговое здоровье нашего матроса
{
	return b_p_hp; // нафиг случайность иначе мрут сильно + 6*rand(11 - MOD_SKILL_ENEMY_RATE*3) - 20;
}

float GetBoarding_enemy_hp(float b_e_hp) // итоговое здоровье матроса врага
{
	return b_e_hp + 4*(MOD_SKILL_ENEMY_RATE*3 - 5); // нафиг случайность + 6*rand(MOD_SKILL_ENEMY_RATE*3+1) - 20;
}
// наши на абордаде (далее применяется НР капитана)
void SetFantomParamAbordOur(ref _pchar)
{
	_pchar.RankBonus = m_rank_bonus;
	_pchar.OurMan = true;
	SetFantomParamCommon(_pchar);
	DeleteAttribute(_pchar, "RankBonus");
	DeleteAttribute(_pchar, "OurMan");
}
void SetMushketerParamAbordOur(ref _pchar)
{
	_pchar.RankBonus = m_rank_bonus;
	_pchar.OurMan = true;
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
	DeleteAttribute(_pchar, "RankBonus");
	DeleteAttribute(_pchar, "OurMan");
}
// наши в форте НР не меняем
void SetFantomParamFortOur(ref _pchar)
{
	_pchar.RankBonus = m_rank_bonus;
	_pchar.OurMan = true;
	SetFantomParamCommon(_pchar);
	DeleteAttribute(_pchar, "RankBonus");
	DeleteAttribute(_pchar, "OurMan");
}
void SetMushketerParamFortOur(ref _pchar)
{
	_pchar.RankBonus = m_rank_bonus;
	_pchar.OurMan = true;
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
	DeleteAttribute(_pchar, "RankBonus");
	DeleteAttribute(_pchar, "OurMan");
}
// враги на абордаде (далее применяется НР капитана)
void SetFantomParamAbordEnemy(ref _pchar)
{
	ref MChar;

	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		_pchar.BaseRank = MChar.EnemyRank;
	}
	_pchar.RankBonus = e_rank_bonus;

	SetFantomParamCommon(_pchar);
	DeleteAttribute(_pchar, "BaseRank");
	DeleteAttribute(_pchar, "RankBonus");
}
void SetMushketerParamAbordEnemy(ref _pchar)
{
	ref MChar;
	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		_pchar.BaseRank = MChar.EnemyRank;
	}
	_pchar.RankBonus = e_rank_bonus;
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
	DeleteAttribute(_pchar, "BaseRank");
	DeleteAttribute(_pchar, "RankBonus");
}
// враги в форте НР меняем потом на GetBoarding_enemy_hp(LAi_GetCharacterMaxHP(НПС))
void SetFantomParamFortEnemy(ref _pchar)
{
	ref MChar;

	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		_pchar.BaseRank = MChar.EnemyRank;
	}
	_pchar.RankBonus = e_rank_bonus;

	SetFantomParamCommon(_pchar);
	DeleteAttribute(_pchar, "BaseRank");
	DeleteAttribute(_pchar, "RankBonus");
}
void SetMushketerParamFortEnemy(ref _pchar)
{
	ref MChar;
	MChar = GetMainCharacter();
	if (CheckAttribute(MChar, "EnemyRank"))
	{
		_pchar.BaseRank = MChar.EnemyRank;
	}
	_pchar.RankBonus = e_rank_bonus;
    CalculateAppropriateSkills(_pchar);
    SetFantomHP(_pchar);
	DeleteAttribute(_pchar, "BaseRank");
	DeleteAttribute(_pchar, "RankBonus");
}

//крутые парни -->
void SetFantomParamHunter(ref sld)
{
    SetSeaFantomParam(sld, "war");
    LAi_SetHP(sld, LAI_DEFAULT_HP_MAX + sti(sld.chr_ai.hp), LAI_DEFAULT_HP_MAX + sti(sld.chr_ai.hp));
    TakeNItems(sld,"potion2", MOD_SKILL_ENEMY_RATE);
}
//крутые парни <--
// boal 20.03.2004 <--
void AntiCheat(ref _pchar)
{
    /*ref mc = GetMainCharacter();
    if (sti(mc.chr_ai.hp) > 310)
    {
        LAi_SetHP(_pchar, 10000, 10000);
        mc.chr_ai.hp = 310;
    }
    SetRankFromSkill(mc);*/
}

void CheckAntiCheat()
{
 	if (CheckAttribute(PChar, "SystemInfo.CRC"))
 	{
		if (stf(PChar.SystemInfo.CRC) != GetCRCCheatSum(PChar))
		{
		    bPlayerIsCheater = true;
		}
	}
}

void SetAntiCheat()
{
	PChar.SystemInfo.CRC = GetCRCCheatSum(PChar);
}
float GetCRCCheatSum(ref _PChar)
{
	return makefloat(GetSPECIALSum(_PChar) + GetSkillSum(_PChar) + sti(_PChar.Ship.Type) + stf(_PChar.Health.HP) + sti(_PChar.rank) + sti(_PChar.Money) + stf(_PChar.chr_ai.hp));
}

////////////////////////////////////////
//   SEA
////////////////////////////////////////
float Sea_TurnRateMagicNumber();
{
    return 244.444; //162.962; //244.444; *2/3
}

float Sea_ApplyMaxSpeedZ(aref arCharShip, float fWindDotShip) //float fTRFromSailDamage
// arCharShip - корабль на НПС,  fTRFromSailDamage - паруса 0..1, fWindDotShip - направление ветра -1..1
{
    ref		rShip = GetRealShip(sti(arCharShip.Type)); // база
    float   fMaxSpeedZ;
    float   fWindAgainstSpeed;
    //fMaxSpeedZ = (0.16 + fTRFromSailDamage / 1.2) * stf(arCharShip.MaxSpeedZ);
    fMaxSpeedZ = stf(arCharShip.MaxSpeedZ);
    fWindAgainstSpeed = stf(rShip.WindAgainstSpeed);// / 1.7; // мин fWindAgainstSpeed = 0.8 - мах 10.5
	if (CheckAttribute(arCharShip,"GhostShipTuning")) fWindAgainstSpeed *= 1.05;
    //#20180207-01
    arCharShip.WindAgainstSpeed = rShip.WindAgainstSpeed;
    arCharShip.SpeedRate = rShip.SpeedRate;
	if (fWindDotShip >= -0.1)
    { //по ветру
        fMaxSpeedZ = fMaxSpeedZ * (0.81 + fWindDotShip / (1.9 + pow(fWindAgainstSpeed, 0.33)));
    }
    else
    { //против ветра
        fMaxSpeedZ = fMaxSpeedZ * (0.75 - fWindDotShip/3.2 - pow(abs(fWindDotShip), fWindAgainstSpeed)); // тут есть влияние кода в ЕХЕ
    }

    return fMaxSpeedZ;
}
