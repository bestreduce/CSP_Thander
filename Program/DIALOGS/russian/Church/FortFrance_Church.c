// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Какие вопросы, "+ GetSexPhrase("сын мой","дочь моя") +"?", "Спрашивай, я слушаю тебя..."), "Я слушаю тебя, говори, "+ GetSexPhrase("сын мой","дочь моя") +"...", "И в третий раз говорю тебе, "+ GetSexPhrase("сын мой","дочь моя") +": задавай свой вопрос.",
                          "Столько обязанностей у церковнослужителя, а тут ещё и ты донимаешь, "+ GetSexPhrase("сын мой","дочь моя") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Я "+ GetSexPhrase("передумал","передумала") +"...", "Не сейчас, падре..."), "Да, пока особо и нечего сказать...",
                      "Задам, задам... Только позже...", "Простите, святой отец...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_FortFranceChurch_1"))	//Квест "Странные вещи творятся на архипелаге"
            {
                link.l1 = "Святой отец, я слышал, что вы тоже разыскиваете загадочный чёрный фрегат, который похитил детей на Сан Мартине.";
                link.l1.go = "PKM_SvtvA_Ch1_1";
            }
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_PismoKlermon"))	//Квест "Странные вещи творятся на архипелаге"
            {
                link.l1 = "У меня письмо для вас.";
                link.l1.go = "PKM_SvtvA_Ch2_1";
            }
			if (CheckAttribute(pchar, "questTemp.PKM_SvtvA_Clermon_Final"))	//Квест "Странные вещи творятся на архипелаге"
            {
				dialog.text = "Сумели что-нибудь узнать, касаемо того дела, которое было вам поручено?";
                link.l1 = "Более того, я и мои люди уничтожили секту.";
                link.l1.go = "PKM_SvtvA_Ch3_1";
            }
		break;
		
		//Квест "Странные вещи творятся на архипелаге"
		case "PKM_SvtvA_Ch1_1":
			dialog.text = "Похитили детей?! Хм. Я не знал про это.\nНо мы действительно обеспокоены, так как в нашем городе в одном из домов были обнаружены следы проведения языческого ритуала, и там же лежали мёртвые тела наших добрых законопослушных граждан. У каждого из них были зверски вырваны сердца...";
			link.l1 = "Что за монстры могли сотворить такое?";
			link.l1.go = "PKM_SvtvA_Ch1_2";
		break;
		case "PKM_SvtvA_Ch1_2":
			dialog.text = "Если вам действительно небезразлично всё это, то может быть вы могли бы выполнить моё поручение?\nВаша информация про детей проливает кое-какой свет на эту картину.\nЯ хочу, чтобы вы доставили письмо на Пуэрто-Рико, и передали его лично в руки человеку, которого зовут падре Домингес. Вы найдёте его в соборе, и он даст вам дальнейшие указания, если сочтёт нужным.";
			link.l1 = "Это довольно простое задание. Я немедленно отправляюсь, Святой отец.";
			link.l1.go = "PKM_SvtvA_Ch1_3";
		break;
		case "PKM_SvtvA_Ch1_3":
			dialog.text = "Не спешите, "+ GetSexPhrase("сын мой","дочь моя") +". Человек, который должен был отвезти письмо сегодня, был найден умирающим на пороге своего дома\nВсё, что он успел сказать перед смертью, было то, что на него напали какие-то люди в красных рясах, вооруженные кинжалами.\nУ меня есть основания полагать, что дело тут не чисто - кто-то явно не хочет, чтобы письмо было доставлено.";
			link.l1 = "Стало быть, и меня могут попробовать перехватить по дороге?";
			link.l1.go = "PKM_SvtvA_Ch1_4";
		break;
		case "PKM_SvtvA_Ch1_4":
			dialog.text = "Да, боюсь, что вы правы, поэтому, если вы откажитесь доставить письмо, я вас пойму.";
			link.l1 = "Не вижу причин, по которым мне пришлось бы отказаться от этого дела.";
			link.l1.go = "PKM_SvtvA_Ch1_5";
		break;
		case "PKM_SvtvA_Ch1_5":
			dialog.text = "Вот и отлично. Итак, вот письмо, вы должны доставить его священнику по имени падре Домингес и только ему. Вы сможете найти его на Пуэрто Рико...";
			link.l1 = "";
			link.l1.go = "PKM_SvtvA_Ch1_5.1";
			GiveItem2Character(PChar, "PKM_SvtvA_pismo1");
		break;
		case "PKM_SvtvA_Ch1_5.1":
			dialog.text = "Также я вам выдам документ, который позволит вам находиться в Пуэрто-Рико на законных основаниях.\nИ умоляю вас - не заходите в порт. Высадитесь где-нибудь в укромной бухте, чтобы вас никто не видел. Это письмо имеет большую важность.";
			link.l1 = "Хорошо. не думаю, что это займёт у меня слишком много времени.";
			link.l1.go = "PKM_SvtvA_Ch1_6";
			GiveNationLicence(SPAIN, 8);
		break;
		case "PKM_SvtvA_Ch1_6":
			DialogExit();
			AddQuestRecord("PKM_Animists", "8");
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_FortFranceChurch_1");
			
			PChar.quest.PKM_SvtvA_SJ_B1.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_SJ_B1.win_condition.l1.location = "SanJuan_town";
			PChar.quest.PKM_SvtvA_SJ_B1.win_condition = "PKM_SvtvA_DostavkaPisma_Gorod_1";
			
			PChar.quest.PKM_SvtvA_SJ_B2.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_SJ_B2.win_condition.l1.location = "Shore44";
			PChar.quest.PKM_SvtvA_SJ_B2.win_condition = "PKM_SvtvA_DostavkaPisma_Buhta_1";
			
			PChar.quest.PKM_SvtvA_SJ_B3.win_condition.l1 = "location";
			PChar.quest.PKM_SvtvA_SJ_B3.win_condition.l1.location = "Shore45";
			PChar.quest.PKM_SvtvA_SJ_B3.win_condition = "PKM_SvtvA_DostavkaPisma_Buhta_1";
		break;
		
		case "PKM_SvtvA_Ch2_1":
			dialog.text = "Ага! А я всё гадал, успел ли падре Домингес отослать его или нет.";
			link.l1 = "Что вы хотите этим сказать?";
			link.l1.go = "PKM_SvtvA_Ch2_2";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_PismoKlermon");
			TakeItemFromCharacter(pchar, "PKM_SvtvA_pismo2");
		break;
		case "PKM_SvtvA_Ch2_2":
			dialog.text = "А, вы, наверное, ещё не знаете - человек, вручивший вам это письмо, был похищен. Боюсь, что случилось то, чего я так боялся.";
			link.l1 = "И что же это такое?";
			link.l1.go = "PKM_SvtvA_Ch2_3";
			
			sld = characterFromID("SanJuan_Priest");
			sld.name = "падре";
			sld.lastname = "Робано";
		break;
		case "PKM_SvtvA_Ch2_3":
			dialog.text = "Несколько лет назад в Италии было разгромлено логово служителей сатаны. К сожалению, главе ордена удалось бежать, и он обосновался в архипелаге\nТеперь, судя по пропаже детей и священника высокого ранга, он собирается провести один древний ритуал, и мы должны помешать ему!";
			link.l1 = "И какова моя роль во всём этом?";
			link.l1.go = "PKM_SvtvA_Ch2_4";
		break;
		case "PKM_SvtvA_Ch2_4":
			dialog.text = "Мне бы хотелось, чтобы вы взяли на себя роль карающего меча Господня. Я понимаю, что вы человек деловой, поэтому, как вы посмотрите на 50000 пиастров в качестве вознаграждения, за эту услугу?";
			link.l1 = "Что же, неплохо, совсем неплохо...";
			link.l1.go = "exit";
			AddDialogExitQuest("PKM_SvtvA_Нападение_в_церкви");
		break;
		case "PKM_SvtvA_Ch3_1":
			AddMoneyToCharacter(pchar, 50000);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			dialog.text = "О, слава Богу! Вы сделали это! Я прикажу отслужить службу во имя этого знаменательного события!";
			link.l1 = "А теперь, если простите меня, мне нужно идти.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PKM_SvtvA_Clermon_Final");
		break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}



