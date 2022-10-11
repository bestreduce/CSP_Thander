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
			dialog.text = "(колдует) Арменамо -- делькамано -- МРИСТО!";
			link.l1 = "Ээээ, ты кто такой и как сюда попал?";
			link.l1.go = "PGG_Undead_2";
		break;
		
		case "PGG_Undead_2":
			dialog.text = "Внеземные силы призывают нас. Ты что, не слышишь их зов?";
			link.l1 = "Я уже давно перестал слышать голоса, теперь я занимаюсь своими делами.";
			link.l1.go = "PGG_Undead_3";
		break;
		
		case "PGG_Undead_3":
			dialog.text = "Я здесь не просто так. Послушай, у нас мало времени. Если мы не выполним его просьбу, то даже наши оставшиеся кости растворятся от его влияния. Он силён и очень властен. Я даже не знаю, как это описать. Такого могущества еще никогда не было в нашем мире. У меня нет времени тебе объяснять детали, тебе нужно хорошо подготовиться к моему следующему визиту. Я не могу это контролировать, он сам направяет меня к тебе. Тебе лишь нужно заиметь опыта в два раза больше, чем есть сейчас. Увидимся, мой костяной товарищ....";
			link.l1 = "Чего? Эй, постой! Ты куда?";
			link.l1.go = "PGG_Undead_4";
		break;
		
		case "PGG_Undead_4":
			DialogExit();
			sld = CharacterFromID("PGG_Undead")
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "UD_DrugUshel", -1);
			pchar.questTemp.UndeadPrologue3 = "UP3";
		break;
		
		case "PGG_Undead_5":
			dialog.text = "Поторопись, он уже близко!";
			link.l1 = "Снова ты, что за дела? Рассказывай всё, иначе наши кости будут греметь на весь грод!";
			link.l1.go = "PGG_Undead_6";
			TakeItemFromCharacter(pchar, "UP_PismoZagadka");
		break;
		
		case "PGG_Undead_6":
			dialog.text = "Время пришло! Его сила и могущество издеваются надо мной. Я не в себе. Нам нужно найти своего хозяина! Он правит всеми нами, даже богами в этом мире! Мне кажется, что он ни перед чем не остановится. Пошли, нам нужно его найти, скорее!";
			link.l1 = "Да ты можешь нормально объяснить в чём проблема? Что? Кто? Зачем? Какой еще хозяин? Мой хозяин - Миктлантекутли. Только ему я могу подчиняться, до поры, до времени.";
			link.l1.go = "PGG_Undead_7";
		break;
		
		case "PGG_Undead_7":
			dialog.text = "Моей целью было - привести тебя к нему. Но всё не так просто, сначала он был у меня, но потом его отобрали у меня живые. Я не смог ничего сделать, кроме как скрыться. Прости меня, мой господин... Ой нет, мой господин не ты...! Я запутался! Лил... Лила... Всё, я искушён болью! Мне не выбраться....! Помоги мне, пожалуйста!";
			link.l1 = "Во дела! Что тебя так держит, костяной товарищ? Давай, успокаивайся и поподробнее расскажи, что мы должны сделать? Я помогу тебе, обещаю!";
			link.l1.go = "PGG_Undead_7_1";
		break;
		
		case "PGG_Undead_7_1":
			dialog.text = "Хорошо. Есть один... очень необычный... предмет, я... я... я не могу назвать его по имени, прости... Нам просто нужно его найти, тогда ты сам всё поймёшь и увидишь. Нам нужно простой выйти в открытое море и он сам приведёт живых к тебе. Только хорошенько подготовься. Он хоть и против живых, но всё же даёт силу и им.";
			link.l1 = "... ... Я... я... у меня нет слов. Ладно, собирай свои кости, пошли. Надеюсь, я достаточно готов, чтобы разобраться в этом деле.";
			link.l1.go = "PGG_Undead_8";
		break;
		
		case "PGG_Undead_8":
			dialog.text = "Набери побольше наших костяшек из пещер и подземелий. Живых может быть очень много и все они под его влиянием.";
			link.l1 = "Я понял, ты то куда отправишься? Давай со мной бороздить по архипелагу? Что ты как не родной?";
			link.l1.go = "PGG_Undead_9";
		break;
		
		case "PGG_Undead_9":
			dialog.text = "Да? Так то я с радостью к тебе присоединюсь. Надеюсь, вдвоём мы сможем противостоять ему и всем живым.";
			link.l1 = "Безумие какое-то. Вот же влип. Хотел тут новую жизнь начать, богов почитать. Ладно, посмотрим, что нас ждёт.";
			link.l1.go = "PGG_Undead_10";
		break;
		
		case "PGG_Undead_10":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			DoQuestCheckDelay("UD_DrugUshel_2", 1.5);
			
			sld = CharacterFromID("PGG_Undead");
			sld.name = "Ужасный";
			sld.lastname = "";
			sld.FaceId = 537;
			SetSPECIAL(sld, 8, 10, 8, 3, 8, 10, 8);
			GiveItem2Character(sld, "mushket");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "Energaiser");
			AddItems(sld, "bullet", 20);
			AddItems(sld, "GunPowder", 20);
			LAi_SetHP(sld, 180.0, 180.0);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.HalfImmortal = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			sld.OfficerWantToGo.DontGo = true;
		break;
	}
}
