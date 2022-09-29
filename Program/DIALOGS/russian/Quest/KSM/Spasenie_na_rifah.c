
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sBlade;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = "Капитан, как хорошо, что я вас встретил! Вы можете мне помочь?";
			link.l1 = "В чём дело?";
			link.l1.go = "1";
			UnmarkCharacter(npchar);
			
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Я шёл курсом на Невис, но жестокий шторм спутал все мои планы. Из-за ошибки в навигации мы оказались возле Рифа скелета и корабль крепко сел на скалы. Мне повезло добраться до этой колонии на единственной уцелевшей шлюпке... Умоляю вас, спасите ценный груз и мою команду!";
			link.l1 = "Риф скелета недалеко отсюда... Не припомню... о каком вознаграждении вы говорили?";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "Я дам вам половину от стоимости товара, но нужно спешить. Припасов у моих людей осталось в лучшем случае на две недели.";
			link.l1 = "Хм, так где именно вы посадили на скалы свой корабль?";
			link.l1.go = "3";
			link.l2 = "Нет, капитан, у меня полно своих дел. Выпутывайтесь без меня.";
			link.l2.go = "2.5";
			DeleteAttribute(npchar, "talker");
			UnmarkCharacter(npchar);
		break;
		
		case "2.5":
			sld = CharacterFromID("KSM_Alloka")
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "3":
			dialog.text = "Примерно на северо-востоке от центральной скалы в форме высокой арки. Ошибиться трудно.";
			link.l1 = "По рукам, попробуем найти вашу собственность.";
			link.l1.go = "Exit1";
		break;

		case "REEFS":
			dialog.text = "Вы великолепно выполнили свою работу, капитан. Пришло время расплатиться с вами.";
			link.l1 = "О чём вы? А как же ваша умирающая от голода команда, гниющий в трюме ценный груз?";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "Ещё не поняли? Как же вы доверчивы. Мой корабль действительно разбился на этих скалах, и заполучить новый можно было только одним способом...";
			link.l1 = "Заманить в западню "+ GetSexPhrase("какого-нибудь доверчивого простофилю","какую-нибудь наивную лохушку") +".";
			link.l1.go = "5";
		break;

		case "5":
			dialog.text = "Совершенно верно, капитан, и именно "+ GetSexPhrase("таким простофилей","такой наивной лохушкой") +", к моей величайшей радости, оказались вы. Прощайте...";
			link.l1 = "Это засада! К оружию!";
			link.l1.go = "Exit2";
		break;

		case "Piers":
			dialog.text = "Капитан, ваша нерасторопность будет стоить вам жизни!";
			link.l1 = "Да, я понимаю... Признаться мне было не до спасения ваших людей...";
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = "Мои люди? К чёрту моих людей. Вы не попались в ловушку, не дали захватить ваш корабль! О, вы заплатите за это!";
			link.l1 = "Чёртов интриган!";
			link.l1.go = "Exit3";
		break;
		
		
		case "Exit1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("KSM_Snr_EndloosTraider");
		break;

        case "Exit2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("KSM_Snr_EndloosTraiderKill");
		break;
	}
}
