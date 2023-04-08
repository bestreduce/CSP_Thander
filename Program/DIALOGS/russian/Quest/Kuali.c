
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
			link.l1.go = "Знакомство_3";
		break;
		
		case "Знакомство_3":
			dialog.text = "Хороший воин, а не глупый. Человек тунаку ловит жемчуг, носит ружьё.";
			link.l1 = "У него было ружьё значит, никаких стрел издающих гром. Понятно, здесь был человек с жемчужных промыслов, он направил на тебя ружьё и ты отдал свой маку-у... тьфу, чёрт, как его там?.. Своё оружие и теперь хочешь, чтоб я тебе его вернул"+GetSexPhrase("","а")+".";
			link.l1.go = "Знакомство_4";
		break;
		
		case "Знакомство_4":
			dialog.text = "Мали-мали! Вернул"+GetSexPhrase("","а")+" обратно.";
			link.l1 = "Не глупый воин должен понимать, что мне нужно что-то взамен.";
			link.l1.go = "Знакомство_5";
		break;
		
		case "Знакомство_5":
			dialog.text = "Жизнь даст.";
			link.l1 = "Ты сохранишь мне жизнь? Не похоже на угрозу, в твоём-то положении, значит свою отдашь?";
			link.l1.go = "Знакомство_6";
		break;
		
		case "Знакомство_6":
			dialog.text = "Жизнь ишик мальова.";
			link.l1 = "Что ж, попробую я поискать твое оружие, вдруг и правда ты дашь мне что-то ценное.";
			link.l1.go = "Согласие";
			link.l2 = "Я тебя не понимаю. Бегать тут по джунглям ради кота в мешке, искать неизвестно кого. Нет, Куали, я за это не возьмусь.";
			link.l2.go = "Отказ";
		break;
		
		case "Отказ":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Согласие":
			DialogExit();
			
			SetQuestHeader("Kuali");
			AddQuestRecord("Kuali", "1");
			AddQuestUserData("Kuali", "sSex", GetSexPhrase("","ла"));
			
			sld = CharacterFromID("Kuali");
			sld.dialog.filename = "Quest\Kuali.c";
			sld.dialog.currentnode = "ЕщёРаз_1";
			
			pchar.questTemp.Kuali_1 = true;
		break;
		
		case "ЕщёРаз_1":
			dialog.text = "Ишик найти мой макуаутль?";
			link.l1 = "Ещё не наш"+GetSexPhrase("ёл","ла")+".";
			link.l1.go = "exit";
			NextDiag.TempNode = "ЕщёРаз_1";
		break;
		
		
	}
}
