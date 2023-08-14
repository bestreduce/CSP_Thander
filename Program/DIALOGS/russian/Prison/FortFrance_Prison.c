// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Говорите, я слушаю.";
			link.l1 = "Я "+ GetSexPhrase("ошибся","ошиблась") +". Прощайте.";
			link.l1.go = "Exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_SS"))
			{
				link.l1 = "У меня к вам дело, офицер. Думаю, вас это заинтересует. Один из ваших солдат, Джори, пытался через моё посредничество купить вина в городе. Зная ваши порядки...";
				link.l1.go = "PDM_PJ_SS_1";
			}
		break;
		
		case "PDM_PJ_SS_1":
			dialog.text = "Что?! Я строжайше запретил выпивку на стратегических объектах! Ну что же, он поплатится за это. За вашу бдительность я вознаграждаю вас в размере 5000 золотых, а Джори отправлю на три дня на гауптвахту.";
			link.l1 = "Благодарю, "+GetFullName(NPChar)+". Пресекать подобные нарушения - наш общий долг.";
			link.l1.go = "PDM_PJ_SS_2";
			DeleteAttribute(pchar, "questTemp.PDM_PJ_SS");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			AddMoneyToCharacter(pchar, 5000);
		break;
		
		case "PDM_PJ_SS_2":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_1")
			LAi_SetLoginTime(sld, 0.0, 24.0);
			sld = CharacterFromID("PDM_PJ_Strajnik_2")
			LAi_SetLoginTime(sld, 0.0, 24.0);
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			LAi_SetActorType(pchar);
			DoQuestReloadToLocation("FortFrance_town", "goto", "goto2", "PDM_PJ_Arest_0");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
