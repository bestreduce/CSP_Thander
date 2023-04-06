// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "toMaracaibo")
			{
				link.l1 = "Я бы "+ GetSexPhrase("хотел","хотела") +" узнать кое-что.";
				link.l1.go = "MCTavernMar";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_Maracaibo"))	//Квест "Охота на ведьму"
            {
                link.l1 = "Тебе ни о чём не говорит имя Карла?";
                link.l1.go = "PDM_ONV_MB_1";
            }
		break;
		//зачарованный город
		case "MCTavernMar":
			dialog.text = "Что именно вас интересует?";
			link.l1 = "Говорят, что Маракайбо попал под какое-то проклятье. Что здесь произошло?";
			link.l1.go = "MCTavernMar_1";
		break;
		case "MCTavernMar_1":
			dialog.text = "Маракайбо? У нас, как видите, всё в порядке. Есть, правда, ещё Дес-Мойнес, но это такое захолустье, что там никогда ничего не случается. Хотя странно – обычно у меня в таверне толчётся два-три рыбака оттуда, а тут давно никто не появлялся.";
			link.l1 = "Что за Дес-Мойнес?";
			link.l1.go = "MCTavernMar_2";
		break;
		case "MCTavernMar_2":
			dialog.text = "Рыбацкий городок в нашем заливе. К нему пройти можно через мыс Несбывшихся надежд.";
			link.l1 = "Что ж, информации немного, но и на том спасибо.";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toDesMoines";
		break;
		//Квест ***Охота на ведьму***
		case "PDM_ONV_MB_1":
			dialog.text = "Мне это имя ни о чём не говорит. Но вам повезло, тот мужчина за столиком не раз произносил это имя, когда в неистовой злобе глотал ром.";
			link.l1 = "Как же ты меня выручил. Спасибо!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Maracaibo");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

