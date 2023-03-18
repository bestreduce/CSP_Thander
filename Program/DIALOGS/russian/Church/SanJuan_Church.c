// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	string sStr;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("сын мой","дочь моя") +"?", "Спрашивай, я слушаю тебя..."), "Я слушаю тебя, говори, "+ GetSexPhrase("сын мой","дочь моя") +"...", "И в третий раз говорю тебе, "+ GetSexPhrase("сын мой","дочь моя") +": задавай свой вопрос.",
                          "Столько обязанностей у церковнослужителя, а тут ещё и ты донимаешь, "+ GetSexPhrase("сын мой","дочь моя") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал...", "Не сейчас, падре..."), "Да, пока особо и нечего сказать...",
                      "Задам, задам... Только позже...", "Простите, святой отец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//============= Изабелла Росселини ================
            if (CheckAttribute(Pchar, "RomanticQuest.PriestAsk"))
			{
				link.l2 = "Могу я узнать, часто ли ходит в церковь жена дона Сальватора?";
				link.l2.go = "Romantic_1";
			}
			//Квест "Странные вещи творятся на архипелаге"
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro"))	//Письмо не вскрывали
			{
				link.l1 = "Мне было поручено доставить вот это письмо.";
				link.l1.go = "PKM_SvtvA_Ch1_1_Dobro";
				TakeItemFromCharacter(pchar, "PKM_SvtvA_pismo1");			
			}
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Zlo"))	//Письмо вскрыли
			{
				link.l1 = "Мне было поручено доставить вот это письмо.";
				link.l1.go = "PKM_SvtvA_Ch1_1_Zlo";
				TakeItemFromCharacter(pchar, "PKM_SvtvA_pismo1");			
			}
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_Dostavka_Malty"))	//Доставили Мальтильца
			{
				link.l1 = "Ваше поручение выполнено. Судно, которое вы просили меня сопроводить, стоит в порту.";
				link.l1.go = "PKM_SvtvA_Ch2_1";				
			}
		break;

		//Квест "Странные вещи творятся на архипелаге" (Доставили письмо)
		case "PKM_SvtvA_Ch1_1_Dobro":
			dialog.text = "Дайте-ка его мне сюда. Так-так... хм... Так я и думал! Хм... Что же, вы хорошо потрудились, но позвольте задать вам несколько вопросов.";
			link.l1 = "Да, что именно вы хотите узнать?";
			link.l1.go = "PKM_SvtvA_Ch1_2_Dobro";
			
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Zlo");
		break;

		case "PKM_SvtvA_Ch1_1_Zlo":
			dialog.text = "Дайте-ка его мне сюда. Так-так... хм... Так я и думал! Кстати, а кто вскрывал письмо?";
			link.l1 = "Его никто не вскрывал, что вы?! Вы думаете, я способ"+ GetSexPhrase("ен","на") +" на такое?!";
			link.l1.go = "PKM_SvtvA_Ch1_2_Zlo_Poka";
			link.l2 = "Вы догадались?! Так я и знал"+ GetSexPhrase("","а") +", что это добром не кончится.";
			link.l2.go = "PKM_SvtvA_Ch1_2_Zlo";
			
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Dobro");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_SanJuanChurch_1_Zlo");
		break;

		case "PKM_SvtvA_Ch1_2_Zlo":
			dialog.text = "Так кто же вскрывал письмо?";
			link.l1 = "Меня встретили в той бухте, где мне нужно было высадиться. И мне не оставалось ничего другого, как отдать им письмо. Какие-то люди в красных балахонах, они знали, что я причалю там!";
			link.l1.go = "PKM_SvtvA_Ch1_3_Zlo";
		break;

		case "PKM_SvtvA_Ch1_3_Zlo":
			dialog.text = "Хорошо. Вижу, что вам можно простить этот грех. Тем более, что мы предвидели такой исход событий, и для того, чтобы понять истинный смысл слов этого письма, нужно обладать кое-какими познаниями. Вы даже в чём-то помогли нам, введя этих людей в заблуждение. Думаю, я даже могу выплатить вам обещанную сумму.";
			link.l1 = "О, благодарю вас, благодарю!";
			link.l1.go = "PKM_SvtvA_Ch1_6";
			ChangeCharacterReputation(pchar, -15);
			AddMoneyToCharacter(pchar, 1000);
			AddQuestRecord("PKM_Animists", "13");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
		break;

		case "PKM_SvtvA_Ch1_2_Zlo_Poka":
			dialog.text = "Вижу, что вы не собираетесь раскаиваться в содеянном. Тоже, воля ваша, а теперь покиньте церковь!";
			link.l1 = "Как вам будет угодно.";
			link.l1.go = "PKM_SvtvA_Ch1_3_Zlo_Poka";
			link.l2 = "Нет, подождите, я раскаиваюсь! Бес попутал!";
			link.l2.go = "PKM_SvtvA_Ch1_2_Zlo";
		break;

		case "PKM_SvtvA_Ch1_3_Zlo_Poka":
			DialogExit();

			ChangeCharacterReputation(pchar, -30);
			AddQuestRecord("PKM_Animists", "14");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("PKM_Animists", "sSex2", GetSexPhrase("ся","ась"));
			CloseQuestheader("PKM_Animists");
		break;

		case "PKM_SvtvA_Ch1_2_Dobro":
			dialog.text = "Не было ли у вас в пути каких-либо неприятностей?";
			link.l1 = "Вы знаете, "+GetFullName(CharacterFromID("FortFrance_Priest"))+" попросил меня высадиться в укромной бухте, чтобы избежать неожиданностей, но дело в том, что меня там уже ждали...";
			link.l1.go = "PKM_SvtvA_Ch1_3_Dobro";
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_DralisVG"))	//Если дрались в городе
			{
				link.l1 = "Вы знаете, на причале меня уже ждали загадочные люди в красном... После моего отказа отдать им письмо, они напали на меня. Как видите, я здесь стою, жив"+ GetSexPhrase("ой","ая") +", что не скажешь о моих убийцах.";
				link.l1.go = "PKM_SvtvA_Ch1_4_Dobro";
			}
		break;

		case "PKM_SvtvA_Ch1_3_Dobro":
			dialog.text = "Вы хотите сказать...";
			link.l1 = "Я не хочу бросать ни на кого тень, просто примите это к сведению. В бухте меня встретили четверо в красных балахонах и очень интересовались письмом. Настолько сильно, что мне пришлось убить их.";
			link.l1.go = "PKM_SvtvA_Ch1_4_Dobro";
		break;

		case "PKM_SvtvA_Ch1_4_Dobro":
			dialog.text = "Хм, смотрю, "+GetFullName(CharacterFromID("FortFrance_Priest"))+" действительно не зря поручил вам это дело...";
			link.l1 = "Это ещё не всё. Обыскав тела нападавших, мне удалось найти на шее у каждого из них странные медальоны.";
			link.l1.go = "PKM_SvtvA_Ch1_5_Dobro";
		break;

		case "PKM_SvtvA_Ch1_5_Dobro":
			dialog.text = "Дайте-ка взглянуть на них... Хм... Как интересно... Но вернёмся к нашим делам. Вот ваша награда.";
			link.l1 = "Благодарю вас.";
			link.l1.go = "PKM_SvtvA_Ch1_6";
			AddMoneyToCharacter(pchar, 4000);
			ChangeCharacterReputation(pchar, 2);
		break;
		
		case "PKM_SvtvA_Ch1_6":
			dialog.text = "И у меня есть для вас ещё одно дело, если вы, конечно, согласитесь взяться за него\nКстати, оплата за его успешное завершение будет гораздо более щедрая, чем в этот раз.";
			link.l1 = "И что же вы хотите мне поручить?";
			link.l1.go = "PKM_SvtvA_Ch1_7";
		break;

		case "PKM_SvtvA_Ch1_7":
			dialog.text = "Из Европы должно прибыть судно, на котором плывут мальтийские рыцари, важные для нашего дела. У меня есть все основания полагать, что этому судну угрожает опасность, и ваша задача встретить его у острова Сан Мартин и препроводить в наш порт.";
			link.l1 = "Скажите мне название этого судна, и я сделаю всё, что в моих силах.";
			link.l1.go = "PKM_SvtvA_Ch1_8";
		break;

		case "PKM_SvtvA_Ch1_8":
			dialog.text = "Итак, вы должны встретить барк 'Маёнез', которым командует некто Жаквин де Массе, мальтийский офицер.";
			link.l1 = "Отлично, этой информации достаточно. Думаю, я могу отплывать - чем быстрее я это сделаю, тем выше шансы на успех.";
			link.l1.go = "PKM_SvtvA_Ch1_9";
		break;
		
		case "PKM_SvtvA_Ch1_9":
			DialogExit();
			AddQuestRecord("PKM_Animists", "15");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			if (CheckAttribute(Pchar, "questTemp.PKM_SvtvA_DralisVG")) sStr = "причале";
			else sStr = "пляже";
			AddQuestUserData("PKM_Animists", "sStr", sStr);
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_DralisVG");
			
			//Корабль 'Маёнез'
			sld = GetCharacter(NPC_GenerateCharacter("Maltese", "Maltese", "man", "man", 10, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, 10, 30, 30, "blade44", "pistol1", 50);
			SetSPECIAL(sld, 10, 6, 8, 10, 6, 5, 6);
			SetSelfSkill(sld, 18, 21, 70, 3, 40);
			SetShipSkill(sld, 60, 12, 18, 17, 32, 41, 60, 31, 26);
			LAi_SetHP(sld, 300.0, 300.0);
			sld.name = "Жаквин";
			sld.lastname = "де Массе";
			sld.FaceId = 296;
			sld.loyality = 20;
			FantomMakeCoolSailor(sld, SHIP_BARQUE, "Маёнез", CANNON_TYPE_CULVERINE_LBS16, 30, 50, 30);	//Корабль
			sld.AlwaysFriend = true;
			Group_FindOrCreateGroup("PKM_SvtvA_Malta");
			Group_SetType("PKM_SvtvA_Malta", "war");
			Group_AddCharacter("PKM_SvtvA_Malta", "Maltese");
			Group_SetTaskAttack("PKM_SvtvA_Malta", "PKM_SvtvA_TL");
			SetCharacterGoods(sld, GOOD_FOOD, 500);
			SetCharacterGoods(sld, GOOD_FRUITS, 700);

			Group_SetGroupCommander("PKM_SvtvA_Malta", "Maltese");
			Group_SetAddress("PKM_SvtvA_Malta", "SentMartin", "quest_ships", "Quest_ship_7");
			Group_LockTask("PKM_SvtvA_Malta");
			
			//Корабль 'Тёмный Ангел'
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvtvA_TA", "Animists1", "man", "man", 10, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 12, 40, 50, "blade26", "pistol1", 80);
			sld.name = "Тайная";
			sld.lastname = "личность";
			sld.FaceId = 297;
			FantomMakeCoolSailor(sld, SHIP_LA_MARIANNA, "Тёмный Ангел", CANNON_TYPE_CULVERINE_LBS24, 60, 60, 60);	//Корабль
			sld.AlwaysEnemy = true;
			Group_FindOrCreateGroup("PKM_SvtvA_TL");
			Group_SetType("PKM_SvtvA_TL", "war");
			Group_AddCharacter("PKM_SvtvA_TL", "PKM_SvtvA_TA");
			realships[sti(sld.ship.type)].HP = 6000;
			realships[sti(sld.ship.type)].SpeedRate = 13;
			realships[sti(sld.ship.type)].TurnRate  = 44;

			Group_SetGroupCommander("PKM_SvtvA_TL", "PKM_SvtvA_TA");
			Group_SetAddress("PKM_SvtvA_TL", "SentMartin", "quest_ships", "Quest_ship_7");
			Group_LockTask("PKM_SvtvA_TL");
			
			//Условия задания
			
			PChar.quest.PKM_SvtvA_TA_ploho.win_condition.l1 = "NPC_Death";		//Поражение
			PChar.quest.PKM_SvtvA_TA_ploho.win_condition.l1.character = "Maltese";
			PChar.quest.PKM_SvtvA_TA_ploho.win_condition = "PKM_SvtvA_Маёнез_потопили";
			
			PChar.quest.PKM_SvtvA_TA_horosho.win_condition.l1 = "NPC_Death";		//Победа
			PChar.quest.PKM_SvtvA_TA_horosho.win_condition.l1.character = "PKM_SvtvA_TA";
			PChar.quest.PKM_SvtvA_TA_horosho.win_condition = "PKM_SvtvA_Ангела_потопили";
		break;
		
		//Квест "Странные вещи творятся на архипелаге" (После сопровождения корабля мальтийских рыцарей)
		case "PKM_SvtvA_Ch2_1":
			dialog.text = "Вы отлично справились с задачей! Но расскажите мне, не было ли каких-нибудь неожиданностей в вашем плавании?";
			link.l1 = "Нет, за исключением того, что когда мне повстречался барк, на него насели пираты, пытавшиеся потопить его любыми средствами.";
			link.l1.go = "PKM_SvtvA_Ch2_2";
		break;

		case "PKM_SvtvA_Ch2_2":
			dialog.text = "Понятно. Теперь позвольте мне вручить вам вашу награду и предложить новое дело.";
			link.l1 = "Благодарю вас, а что за задание вы хотите мне поручить?";
			link.l1.go = "PKM_SvtvA_Ch2_3";
			AddMoneyToCharacter(pchar, 5000);
			PChar.quest.PKM_SvtvA_TA_ploho.over = "yes";
		break;

		case "PKM_SvtvA_Ch2_3":
			dialog.text = "Ничего сверхординарного. Просто отвезите вот это письмо отцу Клермону на Мартинику. И смотрите, чтобы оно не попало ни к кому, кроме него!";
			link.l1 = "Я сделаю это. Могу ли я покинуть вас?";
			link.l1.go = "PKM_SvtvA_Ch2_4";
			GiveItem2Character(PChar, "PKM_SvtvA_pismo2");
		break;

		case "PKM_SvtvA_Ch2_4":
			dialog.text = "Можете, и да пребудет с вами Бог.";
			link.l1 = "Аминь.";
			link.l1.go = "exit";
			
			AddQuestRecord("PKM_Animists", "19");
			sld = CharacterFromID("Maltese");
			RemoveCharacterCompanion(pchar, sld);
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Znakomstvo_s_Malta2");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Dostavka_Malty");
			
			PChar.quest.PKM_SvtvA_Zasada2.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_Zasada2.win_condition.l1.location = "SanJuan_town";
			PChar.quest.PKM_SvtvA_Zasada2.win_condition = "PKM_SvtvA_Zasada2";
			
			bDisableFastReload = true;
		break;

		//Квест "История прекрасной Изабеллы"
        case "Romantic_1":
			dialog.text = "Сальвотора Олеварес? Да, сын мой, часто, это достойная прихожанка... А в чём дело?";
			link.l1 = "Да просто так спросил, падре. До свидания...";
			link.l1.go = "exit";
			DeleteAttribute(Pchar, "RomanticQuest.PriestAsk");
		break;

        case "Romantic_2":
			dialog.text = GetFullName(pchar) + ", берёшь ли ты в жены Изабеллу де Вальдес и клянёшься жить с ней в мире и согласии, пока смерть не разлучит вас?";
			link.l1 = "Да, падре.";
			link.l1.go = "Romantic_3";
		break;
        case "Romantic_3":
			locCameraToPos(3.64, 3.25, -7.84, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = "А ты, Изабелла де Вальдес, берёшь ли ты в мужья " + GetMainCharacterNameGen() + " и клянёшься жить с ним в мире и согласии, пока смерть не разлучит вас?";
			link.l1 = "Да, падре.";
			link.l1.go = "Romantic_4";
		break;
        case "Romantic_4":
			locCameraToPos(-0.75, 3.85, -10.60, false);
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "goto", "goto5");
			dialog.text = "Если кто-то из присутсвующих знает причину, по которой этот мужчина и эта женщина не могут быть вместе - пусть скажет это прямо сейчас или молчит вечно.";
			link.l1 = "...";
			link.l1.go = "Romantic_5";
		break;
        case "Romantic_5":
			dialog.text = "Отныне вы муж и жена!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddDialogExitQuest("Romantic_Padre_3");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
