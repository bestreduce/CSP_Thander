string sNationNameglobal;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref arItem;

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string attrLoc, QuestName, sTemp;
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		case "First Time":
			dialog.text = "Приветствую, вы " + GetFullName(pchar) + ", верно?";
			link.l1 = "Да, вы правы. Что собственно случилось?";
			link.l1.go = "Invite";
		break;
		case "Invite":
			string sNationName = GetNationNameByType(sti(npchar.nation));
			sNationNameglobal = GetNationNameByType(sti(npchar.nation));
			dialog.text = "Ваши дела на благо " + XI_ConvertString(sNationName+"Dat") + " не остались незамеченными. Вас приглашает к себе сам генерал губернатор, для воздания почестей. В сроках прибытия вас не ограничивают.";
			link.l1 = "Это невероятно! Обязательно посещу его при возможности! Спасибо и прощайте.";
			link.l1.go = "exit";
			sld = CharacterFromID(NationShortName(sti(npchar.nation))+"_guber");
			sld.dialog.CurrentNode = "GivePatent";
			chrDisableReloadToLocation = false;
			pchar.(sNationName).quest.mayor.done = true;
		break;
	}
}