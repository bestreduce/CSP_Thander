// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Все сплетни города "+ GetCityName(npchar.city) +" к вашим услугам. Что бы вы хотели узнать?",
                          "Мы только что поднимали это тему. Вы, вероятно, запамятовали...", "Сегодня вы уже третий раз говорите о каком-то вопросе...",
                          "Что ты "+ GetSexPhrase("заладил","заладила") +" как попугай одно и то же...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Знаешь, " + NPChar.name + ", как-нибудь в следующий раз.", "Точно, "+ GetSexPhrase("забыл","забыла") +" что-то...",
                      "Да уж, действительно в третий раз...", "Да уж...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "questTemp.PDM_ONV_SanJuan"))	//Квест "Охота на ведьму"
            {
                link.l1 = "Тебе ни о чём не говорит имя Карла?";
                link.l1.go = "PDM_ONV_SJ_1";
            }
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_PoiskPadre_Tavern"))	//Квест "Странные вещи творятся на архипелаге"
            {
                link.l1 = "Хотелось бы узнать, какие слухи ходят о похищении местного священника.";
                link.l1.go = "PKM_SvtvA_PPT_1";
            }

            // ==> Проверяем поле состояния квестов. Эдди.
			switch(pchar.questTemp.State)
            {
                case "MorrisWillams_PinnaceNotFound":
                    link.l2 = "Давненько я у вас не был"+ GetSexPhrase("","а") +"... Что нового в Сан-Хуане?";
                    link.l2.go = "Step_E6_1";
                break;
            }
		break;
        //---------------- квесты --------------------
        case "Step_E6_1":
			dialog.text = "В общем, все по старому. Город процветает.";
			link.l1 = "Понятно... Слушай, в город не заходил пинас 'Санта Агуэда'?";
			link.l1.go = "Step_E6_2";
		break;
        case "Step_E6_2":
			dialog.text = "Да, прибыл прямиком не откуда-нибудь, а из Порт-Рояля!";
			link.l1 = "Вот это да! С англичанами мир?";
			link.l1.go = "Step_E6_3";
		break;
        case "Step_E6_3":
			dialog.text = "Да не сказать, чтобы мир, но уже и не война. У англичан сейчас с голландцами столкновения, так что в Старом Свете отношения налаживаются.";
			link.l1 = "Ну что же, это к лучшему... А пинас этот где сейчас?";
			link.l1.go = "Step_E6_4";
		break;
        case "Step_E6_4":
			dialog.text = "Разгрузил трюмы и ушёл. Теперь Сан-Хуан завален индиго да серебром. Цены упали...";
			link.l1 = "Так что, груз с пинаса распродан?";
			link.l1.go = "Step_E6_5";
		break;
        case "Step_E6_5":
			dialog.text = "Ещё бы! А тебе-то зачем этот пинас понадобился?";
			link.l1 = "Да я "+ GetSexPhrase("договаривался","договаривалась") +", что груз этот мне уступят, а они продали все здесь...";
			link.l1.go = "Step_E6_6";
		break;
        case "Step_E6_6":
			dialog.text = "Ну что же, в следующий раз договаривайся с кем-нибудь другим.";
			link.l1 = "Это верно, приятель. Спасибо тебе, будь здоров.";
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_2PinnaceNotFound";
		break;

		case "PDM_ONV_SJ_1":	//Квест "Охота на ведьму"
			dialog.text = "Мне это имя ни о чём не говорит. Но вам повезло, тот мужчина за столиком не раз произносил это имя, когда в неистовой злобе глотал ром.";
			link.l1 = "Как же ты меня выручил. Спасибо!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_SanJuan");
		break;
		
		case "PKM_SvtvA_PPT_1":	//Квест "Странные вещи творятся на архипелаге"
			dialog.text = "Да об этом вся колония говорит! Представляете, прямо посреди белого дня ворвались в церковь, и похитили его! Никто даже глазом не успел моргнуть, как они исчезли!";
			link.l1 = "И кто это были? Люди в красных балахонах?";
			link.l1.go = "PKM_SvtvA_PPT_2";
		break;
		
		case "PKM_SvtvA_PPT_2":
			dialog.text = "Нет. Это были обычные головорезы. Но странно, что вы упомянули о людях в красных балахонах...";
			link.l1 = "Да? Почему же?";
			link.l1.go = "PKM_SvtvA_PPT_3";
		break;
		
		case "PKM_SvtvA_PPT_3":
			dialog.text = "Дело в том, что недавно появился тут парень одетый точь-в-точь, как вы сказали...";
			link.l1 = "Да неужели? И что же произошло дальше?";
			link.l1.go = "PKM_SvtvA_PPT_4";
		break;
		
		case "PKM_SvtvA_PPT_4":
			dialog.text = "Да ничего, что могло бы вас заинтересовать. Это наши внутренние проблемы.";
			link.l1 = "Может быть, ты, всё-таки, мне о них расскажешь? Мне кажется, что эти два события связанны между собой.";
			link.l1.go = "PKM_SvtvA_PPT_5";
		break;
		
		case "PKM_SvtvA_PPT_5":
			dialog.text = "Может вы и правы. Так и быть расскажу. Значится так\nНедели три назад появился у нас этот парень в красной хламиде. Вежливый такой, никому слова дурного не скажет\n";
			link.l1 = "Продолжай.";
			link.l1.go = "PKM_SvtvA_PPT_6";
		break;
		
		case "PKM_SvtvA_PPT_6":
			dialog.text = "Ну, на него как-то все начали коситься, но ничего плохого он не делал, с молодёжью вот, правда, общался, но мы даже рады были - в кои-то веки они не шлялись без дела.";
			link.l1 = "И?";
			link.l1.go = "PKM_SvtvA_PPT_7";
		break;
		
		case "PKM_SvtvA_PPT_7":
			dialog.text = "Хех, а потом что-то произошло. Теперь почитай все молодые парни собираются в какой-то поход вместе с ним\nСын кузнеца вон вообще из дома ушёл, кузнец пошёл разговаривать с этим типом, да выбежал из его дома, как ошпаренный, а ночью напился да утоп - понесла его нелёгкая на пристань\nА сын его даже глазом не повёл. Живёт, как ни в чём ни бывало.";
			link.l1 = "Да, странно всё это. А где я могу найти этого парня??";
			link.l1.go = "PKM_SvtvA_PPT_8";
		break;
		
		case "PKM_SvtvA_PPT_8":
			dialog.text = "Сына кузнеца-то? Да он шляется где-то по городу. А этот тип в балахоне пропал куда-то.";
			link.l1 = "Хорошо, схожу, поговорю с ним, как его звать?";
			link.l1.go = "PKM_SvtvA_PPT_9";
		break;
		
		case "PKM_SvtvA_PPT_9":
			dialog.text = "Джордано, его имечко.";
			link.l1 = "Спасибо.";
			link.l1.go = "PKM_SvtvA_PPT_10";
		break;
		
		case "PKM_SvtvA_PPT_10":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_PoiskPadre_Tavern");
			AddQuestRecord("PKM_Animists", "25");
			AddQuestUserData("PKM_Animists", "sSex", GetSexPhrase("","а"));
			
			sld = GetCharacter(NPC_GenerateCharacter("PKM_Jordano", "Jordano", "man", "man1", 10, PIRATE, -1, false));
			sld.name = "Джордано";
			sld.lastname = "";
			LAi_SetStayType(sld);
			sld.City = "SanJuan";
			sld.dialog.filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Джордано_1";
			ChangeCharacterAddressGroup(sld, "SanJuan_town", "patrol", "patrol16");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

