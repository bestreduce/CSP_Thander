void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
		break;

		case "Gravedigger":
			dialog.text = GetSexPhrase("Он","Она")+" шевелится!!! Пресвятая дева, помилуй!";
			link.l1 = "МОЗГИИИ!!!";
			link.l1.go = "exit_fight";
			
			//Продолжение
			PChar.quest.UP_KrovPismo1.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo1.win_condition.l1.location = "My_Cabin_Small";
			PChar.quest.UP_KrovPismo1.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo2.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo2.win_condition.l1.location = "My_Cabin_Medium";
			PChar.quest.UP_KrovPismo2.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo3.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo3.win_condition.l1.location = "My_Cabin_Medium2";
			PChar.quest.UP_KrovPismo3.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo4.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo4.win_condition.l1.location = "My_New_Cabin1";
			PChar.quest.UP_KrovPismo4.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo5.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo5.win_condition.l1.location = "My_New_Cabin2";
			PChar.quest.UP_KrovPismo5.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo6.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo6.win_condition.l1.location = "My_Cabin_Huge";
			PChar.quest.UP_KrovPismo6.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_KrovPismo7.win_condition.l1 = "location";
			PChar.quest.UP_KrovPismo7.win_condition.l1.location = "My_Cabin_Quest";
			PChar.quest.UP_KrovPismo7.win_condition = "UP_KrovPismo";
			
			PChar.quest.UP_DrugPridet.win_condition.l1 = "item";
			PChar.quest.UP_DrugPridet.win_condition.l1.item = "UP_PismoZagadka";
			PChar.quest.UP_DrugPridet.win_condition = "UP_DrugPridet";
		break;

		case "DeadmansGod":
			dialog.text = "Ты знаешь, кто я?";
			link.l1 = "Смерть.";
			link.l1.go = "DeadmansGod_1";
			LAi_CharacterPlaySoundAtOnce(NPChar, "DeadmansGod_0");
		break;
		case "DeadmansGod_1":
			dialog.text = "Я - равновесие! Я отделяю души от плоти и слежу за балансом в мире живых и мёртвых. Всё живое пройдёт через мой суд. Ты – подсудим"+GetSexPhrase("ый","ая")+".";
			link.l1 = "Я помню... Жизнь... Меня судить должен другой бог. Не ты!";
			link.l1.go = "DeadmansGod_2";
			LAi_CharacterPlaySoundAtOnce(NPChar, "DeadmansGod_1");
		break;
		case "DeadmansGod_2":
			dialog.text = "Ты умер"+GetSexPhrase(" ","ла")+" далеко от мест, где силён твой бог. Да и какое ему дело до вас, жадных, порочных, неверующих?";
			link.l1 = "Позволь...";
			link.l1.go = "DeadmansGod_3";
			LAi_CharacterPlaySoundAtOnce(NPChar, "DeadmansGod_2");
		break;
		case "DeadmansGod_3":
			dialog.text = "МОЛЧИ!\nТы не заслуживаешь ни покоя, ни наказания. Здесь нет твоих предков, и твой бог здесь бессилен, тут не место ни твоей душе, ни твоему праху. Я мог бы стереть то, что от тебя осталось, из реальностей и вероятностей! Легко!\nНо хоть Я и беспристрастный судья, поиграть с рабом чужого бога совсем не прочь. Я заберу твою смерть и дам взамен НЕЖИЗНЬ. Есть и другие, подобные тебе, и они пробудились. А что из этого получится... Хм... Надеюсь будет не скучно. Слышишь стук? Это глупцы ломают крышку твоего гроба. Иди, пока я не передумал!";
			link.l1 = "...";
			link.l1.go = "DeadmansGod_4";
			LAi_CharacterPlaySoundAtOnce(NPChar, "DeadmansGod_3");
		break;
		case "DeadmansGod_4":
			DialogExit();
			DoReloadCharacterToLocation("Common_CryptBig2", "goto", "goto9");
			PlaySound("interface\grob.waw");
			DoQuestFunctionDelay("Undead_Start_Graveyard", 0.1);
			DoQuestFunctionDelay("Undead_Start_Graveyard_1", 1.0);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_fight":
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
		
		case "PGG_Undead_1":
			dialog.text = "Хватит здесь дрыхнуть!";
			link.l1 = "Что, ты как сюда попал?";
			link.l1.go = "PGG_Undead_2";
		break;
		
		case "PGG_Undead_2":
			dialog.text = "Бог мёртвых не доволен твоим бездействием.";
			link.l1 = "Я уже давно перестал слышать голос бога мёртвых, теперь я занимаюсь своими делами.";
			link.l1.go = "PGG_Undead_3";
		break;
		
		case "PGG_Undead_3":
			dialog.text = "Не спеши, у Миктлантекутли на тебя большие планы. Но тебе нужно ещё подрасти. Для армии мёртвых нужен сильный лидер, и тёмный повелитель ждёт, когда ты будешь готов.\nОставляю тебя переваривать эту информацию. Мы ещё увидимся, прощай.";
			link.l1 = "Эй, постой...";
			link.l1.go = "PGG_Undead_4";
		break;
		
		case "PGG_Undead_4":
			DialogExit();
			sld = CharacterFromID("PGG_Undead")
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "UD_DrugUshel", -1);
			pchar.questTemp.UndeadPrologue3 = "UP3";
		break;
		
		case "PGG_Undead_5":
			dialog.text = "Вот я тебя и нашёл.";
			link.l1 = "Снова ты?";
			link.l1.go = "PGG_Undead_6";
		break;
		
		case "PGG_Undead_6":
			dialog.text = "Время пришло. Миктлантекутли требует, чтобы ты взял ЕГО громадный зачарованный меч, и возглавил армию мёртвых, чтобы нести смерть всему живому! Муа-ха-ха.\n(неуверенно) ...ха-ха... Да... Есть одна малю-ю-ю-ю-ю-юсенькая проблемочка. Э-э...";
			link.l1 = "Мне даже интересно стало.";
			link.l1.go = "PGG_Undead_7";
		break;
		
		case "PGG_Undead_7":
			dialog.text = "Мне было поручено вручить тебе этот меч, но я его потерял. Хы.\nТеперь он в руках живых, что не есть хорошо, ведь через него они могут общаться с САМИМ богом мёртвых, что УМУ НЕПОСТИЖИМО! Это КОШМАР, КАТАСТРОФА!!!";
			link.l1 = "Да успокойся ты.";
			link.l1.go = "PGG_Undead_7_1";
		break;
		
		case "PGG_Undead_7_1":
			dialog.text = "Только не говори пожалуйста Миктлантекутли, а то он из меня котлету сделает, правду говорю!";
			link.l1 = "Вижу, дела у тебя совсем хреновые.";
			link.l1.go = "PGG_Undead_8";
		break;
		
		case "PGG_Undead_8":
			dialog.text = "Это ещё полбеды! Вот если воришки догадаются, как работает меч, и позвонят самому Миктлантекутли... Сам понимаешь, что будет...";
			link.l1 = "Я понял, но от меня-то ты что хочешь?";
			link.l1.go = "PGG_Undead_9";
		break;
		
		case "PGG_Undead_9":
			dialog.text = "Ты с дуба рухнул?! Найди меч, он ведь необычный, а - 'Говорящий меч'. Ты ведь нежить, а значит должен чувствовать энергетику меча. Он должен звать тебя, притягивать своим магнетизмом. Просто выйди в море, и ты сразу поймёшь, куда держать курс.";
			link.l1 = "Безумие какое-то. Ну ладно, пойдём искать твой меч.";
			link.l1.go = "PGG_Undead_10";
		break;
		
		case "PGG_Undead_10":
			DialogExit();
			sld = CharacterFromID("PGG_Undead")
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "UD_DrugUshel_2", -1);
			
			PChar.quest.UP_PGGUndead_Off.win_condition.l1 = "ExitFromLocation";
			PChar.quest.UP_PGGUndead_Off.win_condition.l1.location = PChar.location;
			PChar.quest.UP_PGGUndead_Off.win_condition = "UP_PGGUndead_Off";
		break;
	}
}
