
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;										// 						АВТОРЫ И БЛАГОДАРНОСТИ
			DialogExit();																	// Оригинальная идея квеста				    			 - Акелла
		break;																				// Написанный с нуля код и переосмысление квеста 	 	 - Sinistra
		case "First time":																	// Улучшенная и обновлённая локация "Логово Сатанистов"  - Nikk
			dialog.text = "Что? Тоже решил"+GetSexPhrase("","а")+" посмеяться над бедными женщинами!?";	// Улучшенный и обновлённый корабль "Мефисто"- Noctus
			link.l1 = "А что, собственно, происходит?";										// Новая анимация "Поклонения"							 - Antix
			link.l1.go = "Verni_detey_1";													// Улучшенная и обновлённая иконка "Амулет Хаоса"		 - LEOPARD
			PlayVoice("Kopcapkz\Voices\Quest\Dut_f_a_002.wav");								// Новая текстура модели для "Мальтийца" 				 - Gregg
		break;																				// Новая текстура модели для "Сатанистов" 				 - Ерилейн
		
		case "Verni_detey_1":
			dialog.text = "Нет, вы только посмотрите на "+GetSexPhrase("этого наглеца","эту нахалку")+"! И не стыдно насмехаться над нами?!";
			link.l1 = "Я действительно не понимаю, что произошло. Может быть, вы мне расскажете?";
			link.l1.go = "Verni_detey_2";
		break;
		
		case "Verni_detey_2":
			dialog.text = "Люди добрые, что же на свете творится! Детей у нас украли, прошлой ночью, а этот губернатишко, даже пальцем не пошевелил!";
			link.l1 = "Подождите, как это украли? Кто?";
			link.l1.go = "Verni_detey_3";
		break;
		
		case "Verni_detey_3":
			dialog.text = "Не знаю я! Заснула - дитё в колыбельке было, а ночью проснулась, оттого, что сердце нехорошо сжалось, гляжу, а ребёночка уже и нет!";
			link.l1 = "Это очень странно. А что говорит господин губернатор?";
			link.l1.go = "Verni_detey_4";
		break;
		
		case "Verni_detey_4":
			dialog.text = "Носу он не кажет из своего дома! Боится, значит! Нечего ему нам сказать!";
			link.l1 = "Подождите, прекратите шуметь, я попробую поговорить с ним.";
			link.l1.go = "Verni_detey_5";
		break;
		
		case "Verni_detey_5":
			dialog.text = "Да благословит тебя господь, "+GetSexPhrase("хороший человек","добрая девушка")+"!";
			link.l1 = "Ждите меня здесь.";
			link.l1.go = "Verni_detey_6";
		break;
		
		case "Verni_detey_6":
			DialogExit();
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_1")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_7";
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_2")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_7";
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_3")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Verni_detey_7";
			
			pchar.questTemp.PKM_SvtvA_Gde_Deti = "Gde_Deti";
			SetQuestHeader("PKM_Animists");
			AddQuestRecord("PKM_Animists", "1");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
		break;
		
		case "Verni_detey_7":
			dialog.text = "Ну что? Вы что-нибудь узнали? Как там наши дети?!";
			link.l1 = "Я попробую помочь вам. А теперь разойдитесь, пожалуйста.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Verni_detey_7";
			PlayVoice("Kopcapkz\Voices\Quest\Dut_f_a_002.wav");
		break;
		
		case "Capitan_v_taverne_1":
			dialog.text = "Хочешь поставить мне выпивку?";
			link.l1 = "Извини, приятель, выпивку не куплю, но вопросы тебе задам.";
			link.l1.go = "Capitan_v_taverne_1_5";
		break;
		
		case "Capitan_v_taverne_1_5":
			dialog.text = "Тогда задавай их поскорее и отваливай.";
			link.l1 = "Говорят, что ты видел какой-то чёрный фрегат, когда ты подходил к острову.";
			link.l1.go = "Capitan_v_taverne_2";
		break;
		
		case "Capitan_v_taverne_2":
			dialog.text = "Ну, видел и что?";
			link.l1 = "Каким курсом он шёл?";
			link.l1.go = "Capitan_v_taverne_3";
		break;
		
		case "Capitan_v_taverne_3":
			dialog.text = "Прямиком на Невис.";
			link.l1 = "Могли это быть пираты?";
			link.l1.go = "Capitan_v_taverne_4";
		break;
		
		case "Capitan_v_taverne_4":
			dialog.text = "Дьявол их знает! Пойди и спроси у них. Ха-ха!";
			link.l1 = "Спасибо, любезный.";
			link.l1.go = "Capitan_v_taverne_5";
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Capitan_v_taverne_5":
			DialogExit();
			AddQuestRecord("PKM_Animists", "4");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.PKM_SvtvA_SprositKapitanov_v_more = "SprositKapitanov";
			pchar.questTemp.PKM_SvtvA_NevisTaverna_1 = "Taverna";
			pchar.questTemp.PKM_SvtvA_NevisPortMan_1 = "PortMan";
			
			PChar.quest.PKM_SvtvA_SprositKapitanov_v_more.win_condition.l1 = "MapEnter";
			PChar.quest.PKM_SvtvA_SprositKapitanov_v_more.win_condition = "PKM_SvtvA_SprositKapitanov_v_more";
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvpvA_Shturman_1", "shipowner_17", "man", "man", 10, ENGLAND, -1, true));
			sld.name = "Баллтезар";
			sld.lastname = "Фигуейдал";
			FreeSitLocator("Charles_tavern", "sit_base4");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Shturman_v_taverne_1";
			LAi_SetSitType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Charles_tavern", "sit", "sit_base4");	
		break;
		
		case "Shturman_v_taverne_1":
			dialog.text = "Проваливай, "+ GetSexPhrase("приятель","девка") +"!";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shturman_v_taverne_1";
		break;
		
		case "Shturman_v_taverne_2":
			dialog.text = ""+ GetSexPhrase("Старина","Подруга") +"! Поставь выпивку не самому последнему штурману в Новом Свете!";
			link.l1 = "Что уже всё пропил, приятель?";
			link.l1.go = "Shturman_v_taverne_3";
		break;
		
		case "Shturman_v_taverne_3":
			dialog.text = "Всё, до пенса. Ну что, поставишь кружечку?";
			link.l1 = "Погоди, меня интересует, не видел ли ты чёрный фрегат во время плавания?";
			link.l1.go = "Shturman_v_taverne_4";
		break;
		
		case "Shturman_v_taverne_4":
			dialog.text = "Угости меня ромом, и я тебе всё расскажу!";
			link.l1 = "Хорошо, вот твой ром.";
			link.l1.go = "Shturman_v_taverne_5";
			link.l2 = "А, может приложить тебя пару раз о столешницу?";
			link.l2.go = "Shturman_v_taverne_9";
		break;
		
		case "Shturman_v_taverne_5":
			dialog.text = "Гульп-гульп. Хор-р-роший ром!";
			link.l1 = "Итак, ты видел чёрный фрегат?";
			link.l1.go = "Shturman_v_taverne_6";
			AddMoneyToCharacter(pchar, -10);
		break;
		
		case "Shturman_v_taverne_9":
			dialog.text = "Хм... Обойдёмся без этого.";
			link.l1 = "Итак, ты видел чёрный фрегат?";
			link.l1.go = "Shturman_v_taverne_6";
			ChangeCharacterReputation(pchar, -2);
		break;
		
		case "Shturman_v_taverne_6":
			dialog.text = "Фрегат-то? Чёрный?! Видел я его, как тебя вижу. Если бы шли не порожняком, то сейчас не разговаривал бы с тобой - у них то трюмы явно под завязку были\nИмечко ещё у него странное было, не христианское какое-то - 'Мефисто'.";
			link.l1 = "Он вас преследовал? А куда направился после того, как понял, что ему вас не догнать?";
			link.l1.go = "Shturman_v_taverne_7";
		break;
		
		case "Shturman_v_taverne_7":
			dialog.text = "А дьявол его знает. Куда-то на юг, а там, почитай только Ле Франсуа и лежит.";
			link.l1 = "Хорошо, можешь пить дальше.";
			link.l1.go = "Shturman_v_taverne_8";
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Shturman_v_taverne_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_NevisPortMan_1");
			AddQuestRecord("PKM_Animists", "6");
			pchar.questTemp.PKM_SvtvA_LeFrancuaTaverna_1 = "Taverna";
		break;
		
		case "Satanist_v_gorode_1":
			dialog.text = "Не спешите так, сеньор"+ GetSexPhrase("","ита") +"! Вы же не откажетесь побеседовать с нами?!";
			link.l1 = "Не думаю, что хочу с вами разговаривать.";
			link.l1.go = "Satanist_v_gorode_2";
		break;
		
		case "Satanist_v_gorode_2":
			dialog.text = "А ну живо отдавай письмо!";
			link.l1 = "А, может быть, выпьем по кружечке эля и пойдём каждый своей дорогой? Нет? Я так и знал"+ GetSexPhrase("","а") +".";
			link.l1.go = "Satanist_v_gorode_3";
		break;
		
		case "Satanist_v_gorode_3":		//Битва в городе
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for (i=1; i<=11; i++)
			{
				sld = CharacterFromID("SatanaElita_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PKM_SvtvA_DostavkaPisma_Gorod_2");
			LAi_SetFightMode(pchar, true);			
		break;
		
		case "Satanist_v_buhte_1":
			dialog.text = "Не спешите так, сеньор"+ GetSexPhrase("","ита") +"! Вы же не откажетесь побеседовать с нами?!";
			link.l1 = "Не думаю, что хочу с вами разговаривать.";
			link.l1.go = "Satanist_v_buhte_2";
			link.l2 = "Давайте поговорим, только побыстрее, я спешу.";
			link.l2.go = "Satanist_v_buhte_4";
		break;
		
		case "Satanist_v_buhte_2":
			dialog.text = "А ну живо отдавай письмо!";
			link.l1 = "А, может быть, выпьем по кружечке эля и пойдём каждый своей дорогой? Нет? Я так и знал"+ GetSexPhrase("","а") +".";
			link.l1.go = "Satanist_v_buhte_3";
		break;
		
		case "Satanist_v_buhte_3":		//Битва в бухте без разговора
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PKM_SvtvA_DostavkaPisma_Buhta_2");
			LAi_SetFightMode(pchar, true);			
		break;
		
		case "Satanist_v_buhte_4":
			dialog.text = "Нам стало известно, что вы везёте некое письмо, и нам нужно прочитать его\nНе беспокойтесь, у нас есть копия сургучной печати, которым оно запечатано, и адресат ничего не узнает о случившемся\nА в качестве вознаграждения за оказанную нам услугу мы согласны заплатить вам 20000 пиастров. Что скажете?";
			link.l1 = "Что скажу? Дайте подобрать подходящую фразу... Хм... А! Во - а не пойти ли вам прочь? А вашу печать можете засунуть себе сами знаете куда.";
			link.l1.go = "Satanist_v_buhte_5";
			link.l2 = "Хм... 20000 монет... Звучит заманчиво, думаю, что мы договорились. Вот письмо.";
			link.l2.go = "Satanist_v_buhte_7";
		break;
		
		case "Satanist_v_buhte_5":
			dialog.text = "В таком случае мы будем вынуждены вас убить.";
			link.l1 = "Попробуйте!";
			link.l1.go = "Satanist_v_buhte_6";
		break;
		
		case "Satanist_v_buhte_6":		//Битва в бухте с разговором и отказываемся отдавать письмо
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PKM_SvtvA_DostavkaPisma_Buhta_3");
			LAi_SetFightMode(pchar, true);			
		break;
		
		case "Satanist_v_buhte_7":
			dialog.text = "Вы поступили правильно, сеньор"+ GetSexPhrase("","ита") +". Вот ваши деньги, а теперь посмотрим письмо\nТак-так.. хм... я так и думал... Ну, тут они ошибаются... Что же, я узнал всё, что хотел. Запечатываю письмо обратно - видите, узор на печатях идентичен? Можете идти.";
			link.l1 = "Хорошо.";
			link.l1.go = "Satanist_v_buhte_8";
			AddMoneyToCharacter(pchar, 20000);
		break;
		
		case "Satanist_v_buhte_8":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
				sld.lifeday = 0;
				LAi_CharacterDisableDialog(sld);
				LAi_SetImmortal(sld, true);
			}
			LAi_LocationFightDisable(loadedLocation, false);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			AddQuestRecord("PKM_Animists", "12");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("ся","ась"));
			pchar.questTemp.PKM_SvtvA_SanJuanChurch_1_Zlo = "Church1";
			PChar.quest.PKM_SvtvA_SJ_B1.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B2.over = "yes";
			PChar.quest.PKM_SvtvA_SJ_B3.over = "yes";
		break;
		
		case "Satanist_zasada2":
			dialog.text = "Не думаю, что ты куда-нибудь пойдёшь! Живо отдавай письмо!";
			link.l1 = "А, может быть, выпьем по кружечке эля и пойдём каждый своей дорогой? Нет? Я так и знал"+ GetSexPhrase("","а") +".";
			link.l1.go = "Satanist_zasada2_2";	
		break;
		
		case "Satanist_zasada2_2":
			dialog.text = "Хватит паясничать! Я считаю до трёх, и если вы не отдаёте нам письмо, то можете пенять на себя. Раз...";
			link.l1 = "Три!";
			link.l1.go = "Satanist_zasada2_3";
		break;
		
		case "Satanist_zasada2_3":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PKM_SvtvA_Zasada2_Pobeda");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Сатанист_крыса":
			dialog.text = "Умрите! Сатана идёт! Вам не остановить его!";
			link.l1 = "Дьявол! Ваш помощник - сатанист!";
			link.l1.go = "Сатанист_крыса_2";
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Satanist_"+i, "Animists1", "man", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.FaceId = 297;
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				sld.DontChangeGun = true;
				sld.DeleteFood = true;
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1_back");
				GiveItem2Character(sld, "PKM_SvtvA_znachok");
				AddItems(sld, "mineral3", rand(7)-4);
			}
		break;
		
		case "Сатанист_крыса_2":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			sld = CharacterFromID("Satanist_Krisa")
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Satanist");
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("Satanist_"+i)
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Satanist");
			}
			LAi_group_SetRelation("Satanist", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Satanist", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("Satanist", "PKM_SvtvA_Нападение_в_церкви_Победа");
			LAi_SetFightMode(pchar, true);
			
			DoQuestFunctionDelay("PKM_SvtvA_Malta_na_pomosh", 15.0);
		break;
		
		case "Победа_в Церкви":
			dialog.text = "Кто бы мог подумать, отец Гарет поклонялся Князю Тьмы... Кто бы мог подумать...";
			link.l1 = "Зато теперь я знаю, из-за кого у меня было столько неприятностей! Это он докладывал этим монахам обо всех моих передвижениях.";
			link.l1.go = "Победа_в Церкви_2";
		break;
		
		case "Победа_в Церкви_2":
			dialog.text = "Монахам?! Нет, это не монахи. Это слуги Дьявола!";
			link.l1 = "Хм... Прошу прощения за оговорку, я имел"+GetSexPhrase("","а")+" в виду их одежды.";
			link.l1.go = "Победа_в Церкви_3";
		break;
		
		case "Победа_в Церкви_3":
			dialog.text = "Да, вы правы. Но сначала нам нужно узнать, где находится логово язычников. Думаю, что лучше всего будет, если вы отправитесь в Сан-Хуан и попробуете узнать там дополнительную информацию.";
			link.l1 = "Тогда благословите меня.";
			link.l1.go = "Победа_в Церкви_4";
		break;
		
		case "Победа_в Церкви_4":
			dialog.text = "Это ещё не всё. Я бы хотел представить одного человека...";
			link.l1 = "";
			link.l1.go = "Победа_в Церкви_5";
		break;
		
		case "Победа_в Церкви_5":
			DialogExit();
			StartInstantDialog("Maltese", "Победа_в Церкви_6", "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c");
		break;
		
		case "Победа_в Церкви_6":
			dialog.text = "Мы уже встречались, капитан "+pchar.name+".";
			link.l1 = "Жаквин! Как же ты вовремя здесь оказался! Од"+GetSexPhrase("ин","на")+" бы здесь я не справил"+GetSexPhrase("ся","ась")+", твоя помощь оказалась здесь очень кстати.";
			link.l1.go = "Победа_в Церкви_7";
		break;
		
		case "Победа_в Церкви_7":
			dialog.text = "Я рад, что оказался вам полезен. Но давайте перейдём к делу.\nНесколько лет назад я принимал участие в разгроме язычников в Италии...";
			link.l1 = "А, и теперь ты прибыл сюда, чтобы завершить начатое дело?";
			link.l1.go = "Победа_в Церкви_8";
		break;
		
		case "Победа_в Церкви_8":
			dialog.text = "Именно так. И, если вы не возражаете, я присоединюсь к вам.";
			link.l1 = "Что ж, ты знаешь врага в лицо, ты умеешь сражаться, не вижу причин для отказа.";
			link.l1.go = "Победа_в Церкви_9";
		break;
		
		case "Победа_в Церкви_9":
			dialog.text = "Рад вашему согласию. Что же, приказывайте, капитан.";
			link.l1 = "На Пуэрто Рико! Нам необходима дополнительная информация.";
			link.l1.go = "Победа_в Церкви_10";
		break;
		
		case "Победа_в Церкви_10":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			PChar.quest.PKM_SvtvA_MalteseMertv.over = "yes";
		
			sld = CharacterFromID("Maltese");
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetShipRemovable(sld, true);
			SetCharacterRemovable(sld, true);
			sld.location = "None";
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.FaceId = 296;
			sld.rank = 15;
			LAi_SetHP(sld, 400.0, 400.0);
			sld.HasNoFear = true;
		
			sld = CharacterFromID("FortFrance_Priest");
			LAi_SetPriestType(sld);
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Победа_в Церкви_11";
			
			sld = CharacterFromID("SanJuan_Priest");
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Падре_Робано";			
			
			PChar.quest.PKM_SvtvA_PriestVernuDialog.win_condition.l1 = "ExitFromLocation";
			PChar.quest.PKM_SvtvA_PriestVernuDialog.win_condition.l1.location = PChar.location;
			PChar.quest.PKM_SvtvA_PriestVernuDialog.win_condition = "PKM_SvtvA_PriestVernuDialog";
			
			pchar.questTemp.PKM_SvtvA_PoiskPadre_Tavern = true;
			
			AddQuestRecord("PKM_Animists", "21");
		break;
		
		case "Победа_в Церкви_11":
			dialog.text = "Можете не беспокоиться за меня, я здесь приберусь. Вам же лучше заняться поисками логова язычников.";
			link.l1 = "Да, я как раз собирал"+GetSexPhrase("ся","ась")+" уходить.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Победа_в Церкви_11";
		break;
		
		case "Падре_Робано":
			dialog.text = "Падре Домингес был похищен какими-то странными людьми? Что мне делать, что же мне делать...";
			link.l1 = "Дьявол! Мне перестаёт всё это нравиться!";
			link.l1.go = "Падре_Робано_2";
			locCameraFromToPos(2.00, 3.00, -2.00, true, -4.00, -0.20, -12.50);
		break;
		
		case "Падре_Робано_2":
			dialog.text = "Прекратите богохульствовать в доме Господнем!";
			link.l1 = "Да ну? И что мне будет если я ещё что-нибудь скажу? Во, например: Чёрт! Сатана!";
			link.l1.go = "Падре_Робано_3";
		break;
		
		case "Падре_Робано_3":
			dialog.text = "";
			link.l1 = "Ух-х-х... Что это было?!";
			link.l1.go = "Падре_Робано_4";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "hit_fire", "", 2);
			LAi_SetAfraidDead(pchar);
			DoQuestFunctionDelay("PKM_SvtvA_Gospod_nakazal", 1.15);
			LaunchBlood(pchar, 1.0, true);
			LaunchBlood(pchar, 2.0, true);
			LAi_SetCurHP(pchar, 30.0);
		break;
		
		case "Падре_Робано_4":
			dialog.text = "Чудо! Это было чудо! Господь по какой-то причине решил напомнить вам о своём существовании таким способом!\nО! Я сегодня, сейчас же, прочитаю 20 раз 'Отче наш' по этому поводу, и велю отслужить дополнительную службу!";
			link.l1 = "Кха-кха. Делай как знаешь, а я пожалуй пойду.";
			link.l1.go = "Падре_Робано_5";
		break;
		
		case "Падре_Робано_5":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("SanJuan_Priest");
			sld.dialog.filename = "Common_church.c";
			sld.dialog.currentnode = "First time";
		break;
		
		case "Джордано_1":
			dialog.text = "Ты прин"+GetSexPhrase("ёс","есла")+" новости от Учителя? Он сказал, что он пошлёт своего человека.";
			link.l1 = "Да, я от Учителя, только, может быть, ты не будешь орать об этом на всю улицу, сосунок?";
			link.l1.go = "Джордано_2";
			PlayVoice("Kopcapkz\Voices\Quest\Spa_m_b_001.wav");
		break;
		
		case "Джордано_2":
			dialog.text = "О! От Учителя! Я так и знал! Ой, извини, конечно, я буду потише. А где твой медальон?";
			link.l1 = "Ага, всё-таки вспомнил о нём, а то ты прыгаешь, как щенок, забыл обо всём. Вот он, медальон.";
			link.l1.go = "Джордано_3";
		break;
		
		case "Джордано_3":
			dialog.text = "О! Я так и знал, что это ты! Тогда я побегу, скажу остальным. Когда мы отчаливаем?";
			link.l1 = "Отплываем? Всё-то ты знаешь. Может быть, даже знаешь куда?";
			link.l1.go = "Джордано_4";
		break;
		
		case "Джордано_4":
			dialog.text = "Нет, Учитель нам не сказал.";
			link.l1 = "Это хорошо - нечего вам знать пока ещё такие вещи, а то разболтаете кому ни попадя. А где сам Учитель? Без него мы никуда не отплывём.";
			link.l1.go = "Джордано_5";
		break;
		
		case "Джордано_5":
			dialog.text = "Он говорил, что отправится в Порт-о-Принс на несколько дней. Правда, должен был вернуться ещё вчера, а его до сих пор нет.";
			link.l1 = "Странно. Тогда, думаю, что наше плавание откладывается.";
			link.l1.go = "Джордано_6";
		break;		
		
		case "Джордано_6":
			dialog.text = "Как? Почему?";
			link.l1 = "Неужели ты думаешь, что мы поплывём без него? Сначала мне нужно узнать, что с ним случилось, и только тогда мы отправимся в путь.";
			link.l1.go = "Джордано_7";
		break;
		
		case "Джордано_7":
			DialogExit();
			
			sld = CharacterFromID("PKM_Jordano");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "houseF2", "none", "", "", "PKM_SvtvA_IdemSledom", -1);
			
			AddQuestRecord("PKM_Animists", "26");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("ёл","ла"));
			AddQuestUserData("PKM_Animists", "sSex1", GetSexPhrase("","а"));
			
			pchar.questTemp.PKM_SvtvA_PoiskUchitel_Tavern = true;
		break;
		
		case "Разговор с тюремщиком":
			dialog.text = "" + TimeGreeting() + ", "+ GetSexPhrase("месье","мадмуазэль") +". Что вам угодно?";
			link.l1 = "Мне необходимо поговорить с одним заключённым.";
			link.l1.go = "Разговор с тюремщиком_2";
		break;
		
		case "Разговор с тюремщиком_2":
			dialog.text = "Вообще-то, у нас запрещены разговоры с заключёнными...";
			if (sti(pchar.reputation) < 40)
			{
				link.l1 = "(доставая пистолет) Вы сейчас же проводите меня к пленнику, или, клянусь Богом, я убью вас!";
				link.l1.go = "Угроза тюремщику_1";
			}
			else
			{
				link.l1 = "Но, позвольте! Я занимаюсь делом государственной важности!";
				link.l1.go = "Разговор с тюремщиком_3";
			}
		break;
		
		case "Разговор с тюремщиком_3":
			dialog.text = "Каким это ещё делом? О чём вы вообще говорите?!";
			if (sti(pchar.reputation) > 80)
			{
				link.l1 = "Вы, наверное, слышали о похищении детей, о том, что в последнее время в архипелаге творятся странные вещи? Так вот, ваш заключённый может помочь мне разобраться со всем этим!";
				link.l1.go = "Уговариваем тюремщика_1";
			}
			else
			{
				link.l1 = "Вы, наверное, слышали о похищении детей, о том, что...";
				link.l1.go = "Деньги тюремщику_1";
			}
		break;
		
		case "Уговариваем тюремщика_1":
			dialog.text = "Ладно, ладно, убедили. Я сам не в восторге от того, что происходит. Можете поговорить с этим ублюдком, всё равно его после полудня вздёрнут.";
			link.l1 = "Отлично! Спасибо вам!";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			NextDiag.TempNode = "Уговариваем тюремщика_2";
			
			AddQuestRecord("PKM_Animists", "30");
			
			sld = CharacterFromID("Satanist_Uchitel");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Учитель_Спасение";
		break;
		
		case "Уговариваем тюремщика_2":
			dialog.text = "Я надеюсь, вы вытрясите из этого подонка всю информацию, которая вам так нужна.";
			link.l1 = "Благодарю, офицер. Я уже в поиске его камеры.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Уговариваем тюремщика_2";
		break;
		
		case "Деньги тюремщику_1":
			dialog.text = "Вы только зря теряете время. Хотя... Если вы окажите мне одну услугу...";
			link.l1 = "Какую ещё услугу?";
			link.l1.go = "Деньги тюремщику_2";
		break;
		
		case "Деньги тюремщику_2":
			dialog.text = "У моего сына скоро свадьба, хотелось бы отпраздновать это событие на широкую ногу... В общем, если вы хотите поговорить с узником, то за 40000 пиастров я с удовольствием разрешу вам сделать это.";
			if (sti(pchar.Money) >= 40000)
			{
				link.l1 = "Вот ваши деньги.";
				link.l1.go = "Деньги тюремщику_3_да";
			}
			link.l2 = "Боюсь, у меня не остаётся другого выбора... Защищайтесь!";
			link.l2.go = "Деньги тюремщику_3_нет";
		break;
		
		case "Деньги тюремщику_3_нет":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			LAi_group_AttackGroup("FRANCE_CITIZENS", LAI_GROUP_PLAYER);
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Деньги тюремщику_3_да":
			dialog.text = "Хорошо, вы можете поговорить с заключённым.";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			NextDiag.TempNode = "Деньги тюремщику_4_да";
			
			AddQuestRecord("PKM_Animists", "29");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("Satanist_Uchitel");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Учитель_Спасение";
		break;
		
		case "Деньги тюремщику_4_да":
			dialog.text = "Что-то ещё?";
			link.l1 = "Нет. Просто осматриваю тюрьму.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Деньги тюремщику_4_да";
		break;
		
		case "Угроза тюремщику_1":
			dialog.text = "Что за... Вы за это ответите!";
			link.l1 = "Возможно, но сейчас вы мой пленник. Так что сидите спокойно, пока я не освобожу заключённого.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			NextDiag.TempNode = "Угроза тюремщику_2";
			
			AddQuestRecord("PKM_Animists", "28");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
		break;
		
		case "Угроза тюремщику_2":
			dialog.text = "Что вы ещё хотите?";
			link.l1 = "Ничего. Сиди и не дёргайся.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Угроза тюремщику_2";
		break;
		
		case "Учитель_Смерть":
			dialog.text = "Что вам от меня нужно?!";
			link.l1 = "Скажи, где находится ваше логово, и я позволю умереть тебе быстро.";
			link.l1.go = "Учитель_Смерть_1";
			PChar.quest.PKM_SvtvA_TuremchikKonets.over = "yes";
		break;
		
		case "Учитель_Смерть_1":
			dialog.text = "Вы пытаетесь испугать меня?! Я слуга сил хаоса! Я не боюсь смерти!";
			link.l1 = "Хм... действительно...";
			link.l1.go = "Учитель_Смерть_2";
		break;
		
		case "Учитель_Смерть_2":
			dialog.text = "Что значит смерть для меня! Для меня, кто собирается занять достойное место у подножия трона своего повелителя!";
			link.l1 = "Возможно, смерти ты и не боишься. А как насчёт пожизненного заключения в этой клетке?";
			link.l1.go = "Учитель_Смерть_3";
		break;
		
		case "Учитель_Смерть_3":
			dialog.text = "...";
			link.l1 = "А ведь это ещё вполне уютная камера, я могу походатайствовать о том, чтобы тебя перевели в более мрачное и сырое место.";
			link.l1.go = "Учитель_Смерть_4";
		break;
		
		case "Учитель_Смерть_4":
			dialog.text = "...";
			link.l1 = "Ледяная вода на полу, не дающая ни минуты отдыха, гниющая плоть... Заманчиво звучит, чёрт меня побери!";
			link.l1.go = "Учитель_Смерть_5";
		break;
		
		case "Учитель_Смерть_5":
			dialog.text = "Стойте! Я всё расскажу. Что вам надо?";
			link.l1 = "Где находится ваше логово?";
			link.l1.go = "Учитель_Смерть_6";
		break;
		
		case "Учитель_Смерть_6":
			dialog.text = "На острове Мария Галанте, возле...";
			link.l1 = "";
			link.l1.go = "Учитель_Смерть_7";
			npchar.lifeday = 0;
			LAi_SetHP(npchar, 1.0, 1.0);
		break;
		
		case "Учитель_Смерть_7":
			dialog.text = "Кха... не-е-е-ет... гхм...";
			link.l1 = "Что за?!";
			link.l1.go = "Учитель_Смерть_8";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "death_citizen_1", "", 2.0);
			DoQuestFunctionDelay("PKM_SvtvA_Uchitel_smert", 2.2);
		break;
		
		case "Учитель_Смерть_8":
			DialogExit();
			
			AddQuestRecord("PKM_Animists", "32");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition.l1 = "ExitFromLocation";  //Выход из локации
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition.l1.location = PChar.location;
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition = "PKM_SvtvA_TuremchikDialog";
				
			locations[FindLocation("Guadeloupe_deadlock")].models.day.charactersPatch = "jungle9_patch";
			locations[FindLocation("Guadeloupe_deadlock")].models.night.charactersPatch = "jungle9_patch";
			Locations[FindLocation("Guadeloupe_deadlock")].models.always.l4 = "jungle9_nowall";
			
			PChar.quest.LogovoSatanistov.win_condition.l1 = "location";
			PChar.quest.LogovoSatanistov.win_condition.l1.location = "Cave_Satanists";
			PChar.quest.LogovoSatanistov.win_condition = "LogovoSatanistov";
		break;
		
		case "Учитель_Спасение":
			dialog.text = "Что вам от меня нужно, грязные свиньи?!";
			link.l1 = "Мы пришли освободить вас.";
			link.l1.go = "Учитель_Спасение_1";
			PChar.quest.PKM_SvtvA_TuremchikKonets.over = "yes";
		break;
		
		case "Учитель_Спасение_1":
			dialog.text = "Как мило с вашей стороны. И с какой стати я удостоился такой милости?";
			link.l1 = "Времени нет объяснять. В любую минуту могут обнаружить, что бумаги на ваше освобождение подделаны.";
			link.l1.go = "Учитель_Спасение_2";
		break;
		
		case "Учитель_Спасение_2":
			dialog.text = "Даже так? Хорошо. Я разрешаю вам проводить меня до Сан-Хуана, а там решим, что делать с вами дальше.";
			link.l1 = "Как скажете.";
			link.l1.go = "Учитель_Спасение_3";
		break;
		
		case "Учитель_Спасение_3":
			DialogExit();
			
			AddQuestRecord("PKM_Animists", "31");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition.l1 = "ExitFromLocation";  //Выход из локации
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition.l1.location = PChar.location;
			PChar.quest.PKM_SvtvA_TuremchikDialog.win_condition = "PKM_SvtvA_TuremchikDialog";
			
			sld = CharacterFromID("Satanist_Uchitel");
			ChangeCharacterAddressGroup(sld, "PortPax_prison", "goto", "goto23");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			AddPassenger(pchar, sld, true);
			
			PChar.quest.PKM_SvtvA_UchitelPassakir.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_UchitelPassakir.win_condition.l1.location = "PuertoRico";
			PChar.quest.PKM_SvtvA_UchitelPassakir.win_condition = "PKM_SvtvA_UchitelPassakir";
		break;
		
		case "Обманываем Учителя":
			dialog.text = "Мы почти прибыли в Сан-Хуан, а ты пока ещё не успел"+GetSexPhrase("","а")+" зарекомендовать себя. Может быть ты исправишься?";
			link.l1 = "Как скажете.";
			link.l1.go = "Обманываем Учителя_2";
		break;
		
		case "Обманываем Учителя_2":
			dialog.text = "В таком случае, сразу после высадки я надеюсь увидеть вас в одной из комнат таверны.";
			link.l1 = "Хорошо.";
			link.l1.go = "Обманываем Учителя_3";
		break;
		
		case "Обманываем Учителя_3":
			DialogExit();
			
			if (GetDaysContinueNationLicence(SPAIN) < 2) GiveNationLicence(SPAIN, 2);
			DoQuestReloadToLocation("SanJuan_tavern_upstairs", "goto", "goto2", "PKM_SvtvA_UchitelvTaverne");
		break;
		
		case "Обманываем Учителя_4":
			dialog.text = "Да, я вижу, что вы не лукавите, и действительно связаны с нашим братством. Версия этого мальчишки полностью совпадает с вашей\nНе знаю, когда и где вы примкнули к нам, это сейчас и не важно\nВажно то, что нам необходимо срочно отправиться в наше убежище, так как подходит время для ритуала.\nДумаю, вы согласитесь спровадить меня и некоторых местных жителей в наш храм?";
			link.l1 = "Разумеется. Скажите только, куда нам нужно отправляться.";
			link.l1.go = "Обманываем Учителя_5";
		break;
		
		case "Обманываем Учителя_5":
			dialog.text = "Наш храм находится на острове Мария Галанте. Именно там мы и плани-и...";
			link.l1 = "...Ну а теперь, когда я узнал"+GetSexPhrase("","а")+" всё, что мне необходимо, думаю, тебе пришло время умереть.";
			link.l1.go = "Обманываем Учителя_6";
		break;
		
		case "Обманываем Учителя_6":
			dialog.text = "Что?! Так ты...";
			link.l1 = "Да, я не принадлежу к вашей братии. А теперь защищайся!";
			link.l1.go = "Обманываем Учителя_7";
			LAi_group_MoveCharacter(pchar, "PIRATE_CITIZENS");
		break;
		
		case "Обманываем Учителя_7":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_group_Attack(characterFromId("Satanist_Uchitel"), Pchar);
			LAi_SetFightMode(pchar, true);
			
			PChar.quest.PKM_SvtvA_UbivaemUchitelya.win_condition.l1 = "NPC_Death";
			PChar.quest.PKM_SvtvA_UbivaemUchitelya.win_condition.l1.character = "Satanist_Uchitel";
			PChar.quest.PKM_SvtvA_UbivaemUchitelya.win_condition = "PKM_SvtvA_UbivaemUchitelya";
		break;
		
		case "Спасите, помогите1":
			dialog.text = "Спасите! Вытащите нас!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Спасите, помогите1";
		break;
		
		case "Спасите, помогите2":
			dialog.text = "Не бросайте нас здесь! Я не хочу умирать!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Спасите, помогите2";
		break;
		
		case "Спасите, помогите3":
			dialog.text = "Отоприте решётку! Я хочу выбраться отсюда!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Спасите, помогите3";
		break;
		
		case "Домингес в клетке":
			dialog.text = ""+ GetSexPhrase("Сын мой","Дочь моя") +", это правда вы?";
			link.l1 = "Да, это я, святой отец.";
			link.l1.go = "Домингес в клетке_2";
		break;
		
		case "Домингес в клетке_2":
			dialog.text = "Меня схватили сразу же после вашего отплытия из Сан-Хуана. Но я рад, что вы сумели отыскать логово этих бездушных язычников. В тронном зале сидит их главарь, Чёрное Солнце. Вам нужно остановить его!";
			link.l1 = "Не волнуйтесь, святой отец. Я здесь как раз для того, чтобы положить конец этой дьявольской секте.";
			link.l1.go = "Домингес в клетке_3";
		break;
		
		case "Домингес в клетке_3":
			dialog.text = "В таком случае, я буду молиться за вас!";
			link.l1 = "Я не подведу!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Домингес в клетке_4";
		break;
		
		case "Домингес в клетке_4":
			dialog.text = "Я буду молиться за вас!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Домингес в клетке_4";
		break;
		
		case "Лорд_Хаоса_1":
			dialog.text = "Ты сдохнешь, и демоны спляшут на твоих костях, слизняк!";
			link.l1 = "Ну да, конечно, вот прямо сейчас возьму и сдохну. Размечтался!";
			link.l1.go = "Лорд_Хаоса_2";
			PlayVoice("Kopcapkz\Voices\Quest\Dark_teacher.wav");
		break;
		
		case "Лорд_Хаоса_2":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Chernoe_Solntse");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto57");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("Satanist_"+i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			}			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("Satanist_Oderjim_"+i);
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, "Chernoe_Solntse_sluga");
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Satanist_Turma_"+i);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
			}
			if (!CheckAttribute(pchar, "questTemp.PKM_SvtvA_Satanist_Kuhnya_Pobeda"))
			{
				for (i=1; i<=5; i++)
				{
					sld = CharacterFromID("Satanist_Kuhnya_"+i);
					LAi_SetHP(sld, 180.0, 180.0);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "Chernoe_Solntse");
					LAi_group_SetRelation("Chernoe_Solntse", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
					LAi_group_SetLookRadius("Chernoe_Solntse", 10.0);
					LAi_group_SetHearRadius("Chernoe_Solntse", 3.0);
					LAi_group_SetSayRadius("Chernoe_Solntse", 1.0);
					ChangeCharacterAddressGroup(sld, "Cave_Satanists", "goto",  "goto8");
				}
			}
			
			PChar.quest.PKM_SvtvA_KuhnyaStels1.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels2.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels3.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels4.over = "yes";
			PChar.quest.PKM_SvtvA_KuhnyaStels5.over = "yes";
			
			LAi_group_SetRelation("Chernoe_Solntse", "Chernoe_Solntse_sluga", LAI_GROUP_FRIEND);
			LAi_group_SetRelation("Chernoe_Solntse_sluga", "Chernoe_Solntse", LAI_GROUP_FRIEND);
			
			LAi_group_SetRelation("Chernoe_Solntse", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Chernoe_Solntse", LAI_GROUP_PLAYER, true);
			
			//LAi_group_SetRelation("Chernoe_Solntse_sluga", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//LAi_group_FightGroups("Chernoe_Solntse_sluga", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Chernoe_Solntse_sluga", "PKM_SvtvA_Lord_Haos_Padet");
		break;
		
		case "Лорд_Хаоса_3":
			dialog.text = "Нет! Этого не может быть!..";
			link.l1 = "Что? Не ожидал, что кто-то разнесёт твоё мрачное убежище в клочья?";
			link.l1.go = "Лорд_Хаоса_4";
			
			sld = CharacterFromID("Satanist_Oderjim_1");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Oderjim_2");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Oderjim_3");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Oderjim_4");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Satanist_Oderjim_5");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;
		
		case "Лорд_Хаоса_4":
			dialog.text = "Это ещё не конец...";
			link.l1 = "";
			link.l1.go = "Лорд_Хаоса_5";
		break;
		
		case "Лорд_Хаоса_5":
			dialog.text = "";
			link.l1 = "Э-э-э, ты куда? Трус!";
			link.l1.go = "exit";
			
			sld = CharacterFromID("Chernoe_Solntse");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "goto", "goto28", "none", "", "", "PKM_SvtvA_Lord_Haos_Pobeda_no_ne_sovsem2", 4);
		break;
		
		case "Verni_detey_11":
			dialog.text = "Вы вернулись? Где наши маленькие детки?";
			link.l1 = "Ваши дети в полной безопасности. Сейчас их как раз переправляют на берег с моего судна.";
			link.l1.go = "Verni_detey_12";
		break;
		
		case "Verni_detey_12":
			dialog.text = "О! Спасибо, спасибо вам, "+GetSexPhrase("добрый человек","добрая девушка")+"!";
			link.l1 = "Да не за что.";
			link.l1.go = "Verni_detey_13";
		break;
		
		case "Verni_detey_13":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterReputation(pchar, 12);
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_1")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_2")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_3")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			
			AddQuestRecord("PKM_Animists", "37");
			pchar.questTemp.PKM_Animists_MamaDeti = true;
			if (CheckAttribute(pchar, "questTemp.PKM_Animists_MamaDeti") && CheckAttribute(pchar, "questTemp.PKM_Animists_GuberMarigo") && CheckAttribute(pchar, "questTemp.PKM_Animists_OtetsKlermon"))
			{
				CloseQuestHeader("PKM_Animists");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_MamaDeti");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_GuberMarigo");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_OtetsKlermon");
			}
		break;
		
	}
}
