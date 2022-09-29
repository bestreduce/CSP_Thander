void ProcessDialogEvent()
{
	ref NPChar;
    ref Pchar = GetMainCharacter();
    aref Link, NextDiag;

    DeleteAttribute(&Dialog, "Links");

    makeref(NPChar, CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "FirstTime":
			dialog.text = "Здравствуйте. Я работаю от имени губернатора и ищу вражеского лазутчика в городе. Кто вы "+GetSexPhrase("такой","такая") + "?";
			link.l1 = "Здравствуйте. Я не живу в этом городе, но я не шпион. Можем пойти к губернатору, он подтвердит.";
			link.l1.go = "TryNotBeCut";
			if (CheckNationLicence(sti(npchar.nation)))
			{
				link.l1 = "У меня имеется " + GetRusNameNationLicence(sti(npchar.nation)) + ", так что, я нахожусь здесь на законных основаниях. Прошу ознакомиться...";
				link.l1.go = "LicenceOk";
			}
			if (pchar.sex == "Skeleton")	//Проверка на скелета
			{
				if	(GetCharacterEquipSuitID(pchar)== "suit_1")
				{
					link.l1 = "Здравствуйте. Вы не поверите, но я живой мертвец.";
					link.l1.go = "TryNotBeCut";
				}
				else
				{
					dialog.text = "ЖИВОЙ СКЕЛЕТ? Ты что, с сундука вылез? А ну полезай обратно!";
					link.l1 = "Ну уж нет! Сейчас я попирую твоей кровью!";
					link.l1.go = "exit";
					AddDialogExitQuest("SeekerFight");
				}
			}
		break;
		case "TryNotBeCut":
			if(pchar.SpySeeker == "Enemy" && (10 + rand(50) + rand(50)) > sti(pchar.skill.sneak))
			{
				dialog.text = "Сдаётся мне, что ты меня обманываешь. Но хорошо, давай пройдём к губернатору.";
				link.l1 = "Никуда я с тобой не пойду! Защищайся!";
				link.l1.go = "exit";
				AddDialogExitQuest("SeekerFight");
			}
			else
			{
				dialog.text = "Хорошо, не нужно. Я вам верю. Удачи!";
				link.l1 = "Вот и славно. Удачи!";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				AddCharacterExpToSkill(pchar, "Sneak", 100);
				AddDialogExitQuest("SpySeekerGood");
				if (pchar.sex == "Skeleton")
				{
					dialog.text = "Ха-ха, хорошая шутка! Но я вижу, что вы не шпион, так что больше я вас не беспокою.";
				}
			}
		break;
		case "LicenceOk":
			dialog.text = "Хорошо. Не смею больше вас задерживать."
			link.l1 = "Отлично, прощайте.";
			link.l1.go = "exit";
			AddDialogExitQuest("SpySeekerGood");
		break;
	}
}
