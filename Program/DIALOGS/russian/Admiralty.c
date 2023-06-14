
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
			DialogExit()
		break;
		
		case "First time":
			dialog.text = "Если вы по вопросу торговых перевозок, уплаты пошлин, или найма, то вам нужно пройти в правое крыло здания. В этом крыле находится адмиралтейство, занимающееся исключительно вопросами судов, находящихся на службе его величества.";
			Link.l1 = "Понятно. Всего хорошего.";
			link.l1.go = "exit";
			if (pchar.questTemp.AnjelikaTichPrologue3 == "ATP3")
			{
				dialog.text = "";
				Link.l1 = "Моё имя Анжелика Ремедиос, я со срочным донесением губернатору. Мне сообщили, что он сейчас находится здесь.";
				link.l1.go = "AT_pr_Pochta1";
			}
			if (pchar.questTemp.AnjelikaTichPrologue3_1 == "ATP3_1")
			{
				dialog.text = "Вы заблудились?";
				Link.l1 = "Нет. Всё в порядке, уже ухожу.";
				link.l1.go = "exit";
			}
		break;
		
		//Sinistra Пролог Анжелика Тич
		case "AT_pr_Pochta1":
			dialog.text = "Ремедиос? Вы родственница бывшего управляющего нашей колонии Ла Вега.";
			Link.l1 = "Именно. Так губернатор здесь?";
			link.l1.go = "AT_pr_Pochta2";
		break;
		
		case "AT_pr_Pochta2":
			dialog.text = "Да, конечно. Пройдите этажом выше.";
			Link.l1 = "Благодарю.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue3");
			pchar.questTemp.AnjelikaTichPrologue3_1 = "ATP3_1";
			
			sld = CharacterFromID("SantoDomingo_Mayor")
			sld.Dialog.Filename = "Quest\MainheroPrologues\Prologue_AnjelikaTich.c";
			sld.dialog.currentnode = "ATpr_SD_Gubernator_1";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld,"SantoDomingo_Admiralty","quest","quest4");
			
			sld = GetCharacter(NPC_GenerateCharacter("ATpr_SD_Off_Guber_1", "off_spa_1", "man", "man", 30, SPAIN, -1, false));
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld,"SantoDomingo_Admiralty","quest","quest8");
			
			sld = GetCharacter(NPC_GenerateCharacter("ATpr_SD_Off_Guber_2", "off_spa_2", "man", "man", 30, SPAIN, -1, false));
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld,"SantoDomingo_Admiralty","quest","quest2");
		break;
		
		case "Strajniki":
			dialog.text = RandPhraseSimple("Я слежу за вами.", ""+ GetSexPhrase("Сеньор","Сеньорита") +", это государственное учреждение, держитесь здесь в соответствии его статусу.");
			Link.l1 = RandPhraseSimple("Буду иметь ввиду.", "Я понял"+ GetSexPhrase("","а") +".");
			link.l1.go = "exit";
			NextDiag.TempNode = "Strajniki";
		break;
	}
}
