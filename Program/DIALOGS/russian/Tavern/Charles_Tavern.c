// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы?", "Что вам угодно, " + GetAddress_Form(NPChar) + "?"), "Совсем недавно вы пытались задать мне вопрос, " + GetAddress_Form(NPChar) + "...", "В течение этого дня вы уже третий раз говорите о каком-то вопросе...",
                          "Опять вопросы будем задавать?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Сейчас мне не о чем говорить..."), "Хм, что-то с памятью моей стало...",
                      "Да уж, действительно в третий раз...", "Да нет, какие вопросы...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.MC == "toSeekSister")
			{
				link.l1 = "Дружище, я ищу юную леди по имени Элизабет Шеппард. Ты о такой не слышал?";
				link.l1.go = "MCLiz";
			}
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_NevisTaverna_1"))
			{
				link.l1 = "Меня интересует, не заходило ли в порт судно - чёрный фрегат.";
				link.l1.go = "BlackFregat_1";
			}
		break;
//========================  Квест "Странные вещи творятся на архипелаге" ==>
		case "BlackFregat_1":
			dialog.text = "Чёрный фрегат? Дайте подумать... Нет, к нам он точно не заходил\nНо, я знаю одного типа, который, похоже, с ним сталкивался.";
			link.l1 = "И? Как я могу поговорить с этим человеком?";
			link.l1.go = "BlackFregat_2";
		break;
		case "BlackFregat_2":
			dialog.text = "Да вон он сидит за маленьким круглым столиком. Если я не ошибаюсь, то его имя Баллтезар Фигуейдал.";
			link.l1 = "Хорошо. Пойду, поговорю с ним.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_NevisTaverna_1");
			
			sld = CharacterFromID("PKM_SvpvA_Shturman_1")
			sld.Dialog.Filename = "Quest\PKM\Strannie_veshi_tvorytsya_v_arhipelage.c";
			sld.dialog.currentnode = "Shturman_v_taverne_2";			
		break;
//========================  Квест "Странные вещи творятся на архипелаге" <==		
		case "MCLiz":
			dialog.text = "Мисс Лиз Шеппард - жительница нашего города. А что вам нужно от неё?";
			link.l1 = "Понимаешь, она кое-что забыла в заливе Маракайбо...";
			link.l1.go = "MCLiz_1";
		break;
		case "MCLiz_1":
			dialog.text = "Да, Лиз в последнее время что-то часто стала путешествовать. В городе её и не застать.";
			link.l1 = "А сейчас она где?";
			link.l1.go = "MCLiz_2";
		break;
		case "MCLiz_2":
			dialog.text = "Сейчас у себя в доме.";
			link.l1 = "У неё собственный дом?";
			link.l1.go = "MCLiz_3";
		break;
		case "MCLiz_3":
			dialog.text = "Да, дом её отца.";
			link.l1 = "А кто её отец?";
			link.l1.go = "MCLiz_4";
		break;
		case "MCLiz_4":
			dialog.text = "Ну, об этом особо распространяться не принято, но вам я расскажу.\n"+
				"Слышали вы о капитане Стейтоне? Нет? Хо-хо, тогда знайте, что капитан Стейтон, один из первых флибустьеров, и есть отец Лиз. В своё время, когда он был ещё жив, капитан много сделал для развития города, так что жители Невиса ему обязаны.";
			link.l1 = "Элизабет имеет фамилию Шеппард.";
			link.l1.go = "MCLiz_5";
		break;
		case "MCLiz_5":
			dialog.text = "Это капитан так решил. Когда он поселился с семьёй в городе, то взял другую фамилию. Так, на всякий случай...";
			link.l1 = "И Лиз теперь живёт одна?";
			link.l1.go = "MCLiz_6";
		break;
		case "MCLiz_6":
			dialog.text = "Да, её мать ненадолго пережила супруга и похоронена здесь же, на острове. А Даниэль не появлялась дома уже года два.";
			link.l1 = "Даниэль?";
			link.l1.go = "MCLiz_7";
		break;
		case "MCLiz_7":
			dialog.text = "Старшая сестра Лиз.";
			link.l1 = "Понятно. Ну что же, спасибо тебе, приятель.";
			link.l1.go = "MCLiz_8";
		break;
		case "MCLiz_8":
			dialog.text = "Не за что. Надеюсь, вы принесли Лиз хорошие новости. Она хорошая девушка, капитан...";
			link.l1 = "Во всяком случае, ничего плохого. Это уж точно.";
			link.l1.go = "exit";
			pchar.questTemp.MC = "toSeekSisterAT";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

