//Jason общий диалог уличных матросов
#include "DIALOGS\russian\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (CheckAttribute(npchar, "City"))//фикс ошибок в логе. у наёмных скелетов в пещере нет города.
	{
		NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
	    if (LoadSegment(NPChar.FileDialog2))// вызов диалога по городам <--
		{
	        ProcessCommonDialog(NPChar, Link, NextDiag);
			UnloadSegment(NPChar.FileDialog2);
		}
	}

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch(Dialog.CurrentNode)
	{
		case "First time":
            if (Pchar.questTemp.CapBloodLine == true)
            {
                dialog.Text = "Здравствуйте, доктор.";
                Link.l1 = "И вам не хворать.";
				Link.l1.go = "exit";
				break;
    		}

			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "Здравствуйте, "+GetAddress_Form(NPChar)+". Как мне известно, вы - капитан собственного корабля. У меня к вам деловой разговор.";
					link.l1 = "Слушаю вас внимательно, "+GetAddress_FormToNPC(NPChar)+". О чём речь?";
					link.l1.go = "crew";
					link.l2 = "Простите, "+GetAddress_FormToNPC(NPChar)+", но я очень спешу.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
					{
						dialog.text = "Приветствую тебя в нашей уютной пещере! Чувствуй себя как дома.";
						link.l1 = "Благодарю, сородич. Я тут осмотрюсь.";
						link.l1.go = "UP_Skelet_Vihod";
						if (!checkattribute(pchar, "questTemp.UP_SkeletyVPeshere"))//Sinistra Нежить
						{
							link.l2 = "У меня есть к тебе предложение.";
							link.l2.go = "crew";
						}
					}
					break;
				}
				dialog.text = LinkRandPhrase("Приветствую, капитан! Что вам угодно от простого матроса?","Здравствуйте, суда"+ GetSexPhrase("рь","рыня") +". Чем могу быть вам полезен?","Доброго дня, уважаем"+ GetSexPhrase("ый","ая") +". Вы что-то хотели?");
				link.l1 = "Рад встрече, уважаемый! Моё имя - "+GetFullName(pchar)+". Не найдётся минутки поболтать?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация о делах в этой колонии.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Просто решил"+ GetSexPhrase("","а")+" поздороваться. Бывай!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.AnjelikaTichPrologue") && pchar.questTemp.AnjelikaTichPrologue == "ATP")	//Sinistra Пролог Анжелика Тич
				{
					dialog.text = "Приветствую, сударыня! Что вам угодно от простого матроса?";
					link.l1 = "Да так, жениха моей сестре ищу.";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
					DeleteAttribute(link, "l3");
				}
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")//Sinistra Нежить
				{
					dialog.text = "Приветствую тебя в нашей уютной пещере! Чувствуй себя как дома.";
					link.l1 = "Благодарю, сородич. Я тут осмотрюсь.";
					link.l1.go = "UP_Skelet_Vihod";
					DeleteAttribute(link, "l2");
					DeleteAttribute(link, "l3");
				}
			}
			else
			{
				dialog.text = "Это опять вы, "+ GetSexPhrase("сударь","сударыня") +"? Вы ещё что-то хотели?";
				link.l1 = "Не найдётся ли минутки поболтать о том, о сём?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("У меня есть вопрос к тебе.", "Мне нужна информация о делах в этой колонии.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Нет, приятель, ничего. Удачи!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" к вашим услугам, милейш"+ GetSexPhrase("ий","ая") +"! Что вы хотели узнать?",
				"Рад поболтать, капитан!",
				"Ну, пожалуй, у меня есть ещё время...",
                "К сожалению, мне пора идти. Всего доброго!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Может, расскажете что интересное?",
				"Может, расскажете что интересное?",
                "Может, расскажете что интересное?",
				"Да, конечно. Удачи вам!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (drand(2))
			{
				case 0: sTemp = "Я и несколько моих друзей были списаны на берег после полученных ранений. Теперь мы выздоровели и хотим вновь наняться на службу матросами. Не желаете ли пополнить свою команду?"; break;
				case 1: sTemp = "Меня и нескольких ребят недавно списали на берег с купеческого судна - закончился срок действия уговора с хозяином. Мы уже который день на мели и хотим наняться матросами. Нет ли у вас нужды в опытных моряках для вашей команды?"; break;
				case 2: sTemp = "Мы с друзьями две недели назад вернулись из рейса, хозяин нас рассчитал, и мы здорово повеселились эти денёчки. Однако ветер свищет в матросском кармане - значит, снова пора в море. Не наймёте ли нас на своё судно, капитан?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Ну что же, я готов"+ GetSexPhrase("","а")+" рассмотреть ваше предложение. Сколько вас человек, и что вы умеете делать на судне?";
			link.l1.go = "crew_1";
			link.l2 = "Сожалею, матрос, но моя команда полностью укомплектована. Так что придётся тебе поискать другого капитана.";
			link.l2.go = "exit";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = "И что ты хочешь мне предложить?";
				link.l1 = "У меня есть корабль, и я хочу нанять твоих костлявых ребят к себе в команду, что скажешь?";
				link.l1.go = "crew_1";
				link.l2 = "А знаешь, я передумал.";
				link.l2.go = "UP_Skelet_Vihod";
			}
			if (pchar.sex == "Skeleton" && npchar.sex == "man")	//Sinistra Нежить
			{
				link.l1 = "Жаль тебя разочаровывать, матрос, но... Мне 'живые' в команду не нужны. Хе-хе.";
				link.l1.go = "exit";
				DeleteAttribute(link, "l2");
			}
		break;

		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "Хотя лучше всего прочего мы умеем обращаться с парусами и снастями. Без лишней скромности скажу: мы на этом деле собаку съели, так что не подведём даже в самый свирепый шторм!"; break;
				case 1: sTemp = "Однако больше всего нам по душе пушечная палуба. Мы умеем обращаться с орудиями так, как никто другой в вашей команде, уверяю. Во время жаркой баталии можете без опаски положиться на нас!"; break;
				case 2: sTemp = "Но наша стихия - это абордажная схватка. Блеск сабель, запах пороха и крови - вот наше призвание. В бою с нами нелегко совладать, так что в случае опасности наши клинки выручат вас, капитан!"; break;
			}
			dialog.text = "Нас "+sti(npchar.quest.crew.qty)+" человек, и пойдём мы на службу только все вместе. Умеем мы всё, что положено матросу. "+sTemp+"";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = "Нас "+sti(npchar.quest.crew.qty)+" скелетов, и мы рады будем служить тебе как преданные слуги.";
			}
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Звучит весьма заманчиво. Сколько вы хотите аванса?";
				link.l1.go = "crew_2";
				link.l2 = "Сожалею, матрос, но я рассчитывал на несколько... иное. Придётся вам поискать другого капитана.";
				link.l2.go = "exit";
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					link.l1 = "Да, столько мне подойдёт, и сколько вы хотите?";
					link.l1.go = "crew_2";
					link.l2 = "Этого недостаточно, забудь.";
					link.l2.go = "UP_Skelet_Vihod";
				}
			}
			else
			{
				if(GetCompanionQuantity(PChar) > 1)
				{
					ref rChar;
					for(int i = 1; i<GetCompanionQuantity(PChar); i++)
					{
						if (GetCompanionIndex(PChar,i)>-1)
						{
							rChar = &characters[GetCompanionIndex(PChar,i)];
							if(sti(rChar.index) != -1 && GetFreeCrewQuantity(rChar) >= sti(npchar.quest.crew.qty))
							{
								link.l1 = "Сожалею, матрос, но для всех вас у меня нет мест на корабле. Придётся вам пойти к моему компаньону, его зовут "+ rChar.name + " " + rChar.lastname + ".";
								link.l1.go = "crew_comp";
								pchar.addcrew.character = rChar.id;
								if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
								{
									link.l1 = "Сожалею, сородич, но для всех вас у меня нет мест на корабле. Придётся вам пойти к моему компаньону, его зовут "+ rChar.name + " " + rChar.lastname + ".";
									link.l1.go = "crew_comp";
								}
								break;
							}
						}
						else
						{
							link.l1 = "Сожалею, матрос, но для всех вас у меня нет мест ни на одном корабле. Придётся вам поискать другого капитана.";
							link.l1.go = "exit";
							if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
							{
								link.l1 = "Сожалею, сородич, но для всех вас у меня нет мест ни на одном корабле. Оставайтесь здесь в пещере.";
								link.l1.go = "UP_Skelet_Vihod";
							}
						}

					}
				}
				else
				{
					link.l1 = "Сожалею, матрос, но для всех вас у меня нет мест ни на одном корабле. Придётся вам поискать другого капитана.";
					link.l1.go = "exit";
				}
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					link.l1 = "Сожалею, сородич, но для всех вас у меня нет мест ни на одном корабле. Оставайтесь здесь в пещере.";
					link.l1.go = "UP_Skelet_Vihod";
				}
				link.l2 = "Сожалею, матрос, но я рассчитывал на несколько... иное. Придётся вам поискать другого капитана.";
				link.l2.go = "exit";
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					DeleteAttribute(link, "l2");
				}
			}
		break;

		case "crew_comp":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" на брата. Потом - обычное матросское жалование. Мы лишнего не попросим, кэп.";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" на скелета. Потом - обычное матросское жалование. Мы лишнего не попросим.";
			}
			if (sti(pchar.money) >= iTemp)
			{
				rChar = CharacterFromID(pchar.addcrew.character);
				link.l1 = "Договорились! Вот здесь вся сумма. Отправляйтесь на корабль, он называется '"+rChar.ship.name+"', стоит на рейде. Боцман выделит вам места в кубрике и даст работу.";
				link.l1.go = "crew_comp1";
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					link.l1 = "Договорились! А теперь подняли свои костлявые задницы и марш на корабль, он называется '"+rChar.ship.name+"'. Чтоб через час все были на месте.";
					link.l1.go = "crew_comp1";
				}
			}
			link.l2 = "К сожалению, я не могу себе позволить оплатить ваши услуги. Придётся вам поискать другого капитана.";
			link.l2.go = "exit";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				link.l2 = "Вы слишком много просите, давай забудем об этом.";
				link.l2.go = "UP_Skelet_Vihod";
			}	
		break;

		case "crew_comp1":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Уже идём, капитан! Я соберу ребят, и мы отправимся на борт немедленно!";
			link.l1 = "Давайте, поторапливайтесь, я долго задерживаться тут не планирую.";
			link.l1.go = "crew_comp2";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = "Слушаемся и повинуемся, " + RandPhraseSimple("о повелитель!", "тёмный господин!");
				link.l1 = "Так-то лучше!";
				link.l1.go = "crew_comp2";
			}
		break;

		case "crew_comp2":
			DialogExit();
			rChar = CharacterFromID(pchar.addcrew.character);
			AddCharacterCrew(rChar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(rChar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(rChar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(rChar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(rChar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(rChar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				for (i=1; i<=15; i++)
				{
				sld = CharacterFromID("Skelet_Drug_"+i)
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 20.0);
				}
				pchar.questTemp.UP_SkeletyVPeshere = "SVP";
				SetTimerCondition("UP_SkeletyVPeshere_NanyatSnova", 0, 0, 2, false);	//Sinistra: скелетов можно будет нанимать через два дня!
			}
		break;

		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" на брата. Потом - обычное матросское жалование. Мы лишнего не попросим, кэп.";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" на скелета. Потом - обычное матросское жалование. Мы лишнего не попросим.";
			}
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "Договорились! Вот здесь вся сумма. Отправляйтесь на мой корабль, он называется '"+pchar.ship.name+"', стоит на рейде. Боцман выделит вам места в кубрике и даст работу.";
				link.l1.go = "crew_3";
				if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
				{
					link.l1 = "Договорились! А теперь подняли свои костлявые задницы и марш на корабль, он называется '"+pchar.ship.name+"'. Чтоб через час все были на месте.";
					link.l1.go = "crew_3";
				}
			}
			link.l2 = "К сожалению, я не могу себе позволить оплатить ваши услуги. Придётся вам поискать другого капитана.";
			link.l2.go = "exit";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				link.l2 = "Вы слишком много просите, давай забудем об этом.";
				link.l2.go = "UP_Skelet_Vihod";
			}			
		break;

		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Уже идём, капитан! Я соберу ребят, и мы отправимся на борт немедленно!";
			link.l1 = "Давайте, поторапливайтесь, я долго задерживаться тут не планирую.";
			link.l1.go = "crew_4";
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				dialog.text = "Слушаемся и повинуемся, " + RandPhraseSimple("о повелитель!", "тёмный господин!");
				link.l1 = "Так-то лучше!";
				link.l1.go = "crew_4";
			}
		break;

		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			if (pchar.sex == "Skeleton" && npchar.sex == "Skeleton")
			{
				for (i=1; i<=15; i++)
				{
				sld = CharacterFromID("Skelet_Drug_"+i)
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 20.0);
				}
				pchar.questTemp.UP_SkeletyVPeshere = "SVP";
				SetTimerCondition("UP_SkeletyVPeshere_NanyatSnova", 0, 0, 2, false);	//Sinistra: скелетов можно будет нанимать через два дня!
			}
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Послушайте, я, как гражданин этого города, прошу вас не ходить у нас с обнажённым клинком.", "Знаете, я, как гражданка этого города, прошу вас не ходить у нас с обнажённым клинком.");
			link.l1 = LinkRandPhrase("Хорошо.", "Ладно.", "Как скажете...");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// спайчекинг
		case "SeekSpy_Checking":
			dialog.text = "Да, я подтверждаю, " + NPCharSexPhrase(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)], "он действительно местный житель.", "она действительно местная жительница.");
			link.l1 = RandPhraseSimple("Я понял"+ GetSexPhrase("","а") +". Спасибо за помощь.", "Всё ясно. Спасибо за помощь.");
			link.l1.go = "SeekSpy_Checking_1";
		break;

		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		
		case "UP_Skelet_Vihod":
			DialogExit();
			sld = CharacterFromID("Skelet_Drug")
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
	}
}
