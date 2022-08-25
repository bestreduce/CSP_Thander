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
			//LAi_group_Attack(NPChar, Pchar);
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_MONSTERS);
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			DialogExit();
		break;
	}
}
