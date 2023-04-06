
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
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Авторы Nikk и Sinistra
			dialog.text = "Ишик не ловит жемчуг?";
			link.l1 = "Ты ко мне что-ли обращаешься?";
			link.l1.go = "Знакомство_1";
		break;
		
		case "Знакомство_1":
			dialog.text = "Куали был хороший воин, а не глупый.";
			link.l1 = "Дураков здесь нет, чего тебе от меня нужно?";
			link.l1.go = "Знакомство_2";
		break;
		
		case "Знакомство_2":
			dialog.text = "Куали отдал свой макуаутль человек тунаку ловит жемчуг, макуаутль хочет обратно.";
			link.l1 = "Подожди, Куали это ты, а макуаутль твоё оружие, и зачем же ты тогда его отдал?";
			//link.l1.go = "Знакомство_3";
			link.l1.go = "exit";
		break;
		
		
	}
}
