// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Что вы хотели? Спрашивайте.", "Я слушаю вас, что за вопрос?"), "Второй раз за день вы пытаетесь задать ворпос...", "В третий раз за день вы опять пытаетесь задать вопрос...",
                          "Да когда же это кончится?! У меня дел полно по управлению делами города, а ты все вопросы пытаешься задать!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я передумал"+ GetSexPhrase("","а") +"...", "Не сейчас, не место и не время..."), "Да, верно... Но не сейчас, позже...",
                      "Задам, задам... Только позже...", "Извините, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_Gde_Deti"))	//Sinistra квест "Странные вещи творятся на архипелаге"
			{
				link.l1 = "Я здесь по просьбе женщин, которые сидят в беседке у вашей резиденции.";
				Link.l1.go = "PKM_Animists_1";
			}
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_Gubernator_Final"))	//Sinistra квест "Странные вещи творятся на архипелаге"
			{
				link.l1 = "Ваше задание выполнено, и дети возвращены счастливым родителям.";
				Link.l1.go = "PKM_SvtvA_Final";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Вы уже все забрали. Что вам ещё нужно?", "Неужели осталось ещё что-то, что вы не прихватили?");
            link.l1 = RandPhraseSimple("Осматриваюсь напоследок...", "Проверяю, может забыл"+ GetSexPhrase("","а") +" что забрать...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		//==> Sinistra квест "Странные вещи творятся на архипелаге"
		case "PKM_Animists_1":
			dialog.text = "Ах, вы это хотели обсудить...";
			link.l1 = "Простите, что напоминаю об этом, но ваша задача - обеспечивать безопасность жителей колонии.";
			link.l1.go = "PKM_Animists_2";
        break;
		
		case "PKM_Animists_2":
			dialog.text = "Вы не сдержаны на язык, капитан. Если вы не хотите потерять моё расположение, то впредь воздержитесь от подобных заявлений.\nЧто касается этих женщин... Ваша репутация позволяет мне рассказать вам некоторые подробности.";
			link.l1 = "Я "+ GetSexPhrase("весь","вся") +" во внимании.";
			link.l1.go = "PKM_Animists_3";
        break;
		
		case "PKM_Animists_3":
			dialog.text = "Около трёх часов пополуночи капитан торгового судна, входившего в порт, видел чёрный фрегат, под всеми парусами уходящий от острова.\n А утром в порту были обнаружены два мёртвых солдата, один из которых сжимал в руке обрывок странной красной материи.\n Вполне вероятно, что похищенных детей уже нет на острове. Мы же не располагаем нужными средствами, чтобы снарядить поисковую партию.\nОчевидно, что найти их будет весьма не просто, капитан.\nВпрочем, если вы хотите принять участие в судьбе этих женщин, я готов наделить вас необходимыми полномочиями.\nОбещаю в случае успеха вознаградить вас.";
			link.l1 = "Да, минхер. Я хочу разыскать детей и вернуть их несчастным матерям. Капитан, видевший фрегат, ещё не покинул остров?";
			link.l1.go = "PKM_Animists_4";
			link.l2 = "Нет, минхер. Без аванса я работать не буду. Прощайте.";
			link.l2.go = "PKM_Animists_NET";
        break;
		
		case "PKM_Animists_NET":
			DialogExit();
			AddQuestRecord("PKM_Animists", "2");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader("PKM_Animists");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Gde_Deti");
			
			sld = CharacterFromID("PKM_SvtvA_Devushka_1")
			sld.lifeday = 0;
			sld = CharacterFromID("PKM_SvtvA_Devushka_2")
			sld.lifeday = 0;
			sld = CharacterFromID("PKM_SvtvA_Devushka_3")
			sld.lifeday = 0;
        break;
		
		case "PKM_Animists_4":
			dialog.text = "Вы берётесь за это дело?! Превосходно! Капитана, полагаю, вы сможете найти в таверне. Его судно всё ещё стоит в порту.";
			link.l1 = "Не смею занимать более ваше время, минхер.";
			link.l1.go = "PKM_Animists_5";
        break;
		
		case "PKM_Animists_5":
			DialogExit();
			AddQuestRecord("PKM_Animists", "3");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Gde_Deti");
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_SvpvA_Capitan_1", "officer_43", "man", "man", 10, HOLLAND, -1, true));
			sld.name = "Геред";
			sld.lastname = "Драббе";
			FreeSitLocator("Marigo_tavern", "sit3");
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Capitan_v_taverne_1";
			LAi_SetSitType(sld);
			if(InterfaceStates.EnabledQuestsMarks)
			{
				sld.quest.questflag.model = "questionmarkY";
			}
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit3");			
        break;
		
		case "PKM_SvtvA_Final":
			dialog.text = "Удачное завершение этой неприятной истории. Рад вознаградить вас, капитан. Я знаю, на вас можно положиться в щекотливых делах.";
			link.l1 = "Благодарю, минхер.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Gubernator_Final");
			AddMoneyToCharacter(pchar, 30000);
            AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("PKM_Animists", "38");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.PKM_Animists_GuberMarigo = true;
			if (CheckAttribute(pchar, "questTemp.PKM_Animists_MamaDeti") && CheckAttribute(pchar, "questTemp.PKM_Animists_GuberMarigo") && CheckAttribute(pchar, "questTemp.PKM_Animists_OtetsKlermon") && CheckAttribute(pchar, "questTemp.PKM_Animists_PadreDominges"))
			{
				CloseQuestHeader("PKM_Animists");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_MamaDeti");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_GuberMarigo");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_OtetsKlermon");
				DeleteAttribute(pchar, "questTemp.PKM_Animists_PadreDominges");
			}
        break;
		
        //==> Одиннадцатый квест исп.линейки: разорение Виллемстада и Мариго.
        case "SpaLine11Quest_DestrHol":
			dialog.text = "Почему Испания напала на голландские поселения? Меж нами нет войны!!";
			link.l1 = "Де-факто вы ведёте войну на стороне французов. Вы помогаете им деньгами.";
			link.l1.go = "Step_S11_1";
			AfterTownBattle();
        break;
        case "Step_S11_1":
			dialog.text = "Доказательства у вас есть?";
			link.l1 = "Они нам не нужны. Ваше торговое могущество на Карибах надолго подорвано, а теперь попробуйте ссужать деньги Людовику. Если найдёте свободные средства...";
			link.l1.go = "Step_S11_2";
        break;
        case "Step_S11_2":
			dialog.text = "Будь проклята Испания...";
			link.l1 = "Осторожней в выражениях, иначе глотку перережу! Минхер голландский...";
			link.l1.go = "exit";
            AddQuestRecord("Spa_Line_11_DestrHolland", "3");
            pchar.questTemp.Q11_Marigo = 1;
            NextDiag.TempNode = "Cupture_after";
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			AddDialogExitQuestFunction("TWN_ExitForPay");
            SetReturn_Gover_Dialog_Exit(NPChar);
            chrDisableReloadToLocation = false;
        break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

