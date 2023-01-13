
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sName = GetNameLugger(PChar, "f");

	switch(Dialog.CurrentNode)
	{
		case "First time":

			if(PChar.Dozor == "0")
			{
				if(sti(PChar.rank) >= 3)
				{
					dialog.text = "Подойди ближе, " + GetSexPhrase("сынок","дочка") +"! Ближе, так чтобы я мог рассмотреть твоё лицо. Зрение моё к старости уже ни к чёрту. Да, вот так гораздо лучше.";
					link.l1 = "Далось тебе моё лицо, старик! Шёл бы своей дорогой, и не отвлекал бы занятых людей от дела.";
					link.l1.go = "1";
				}
				else
				{
					dialog.text = "Ты ещё слишком глуп"+ GetSexPhrase("","а") +", чтобы общаться со мной. Приходи позже...";
					link.l1 = "Глуп"+ GetSexPhrase("","а") +"? Да я тебя сейчас!.. Эх, старик.";
					link.l1.go = "exit";
				}
				break;
			}

			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "1":
			dialog.text = "Не стоит так обходиться со мной, " + GetSexPhrase("сынок","дочка") +", я ведь хочу дать тебе то, чего не смогут дать тебе другие. Кумекаешь?";
			link.l1 = "Звучит заманчиво. И что это за вещь? Опять какая-нибудь бесполезная безделушка?";
			link.l1.go = "2";
		break;

		case "2":
			dialog.text = "Не делай поспешных выводов, я вижу на твоём лице волю к победе, в твоих глазах искорки задора, а твоя одежда выдаёт в тебе искателя приключений.";
			link.l1 = "Постой-постой. Оглянись вокруг! Куда ни глянь, все здесь искатели приключений, это же Бермуды!";
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = "Нет, нет, все они обычные капитаны, из которых кто-то более удачлив, кто-то менее, не важно. В них нет того, что есть в тебе, того, что сразу бросается в глаза, того, из-за чего я тебя и заприметил. Понимаешь, " + GetSexPhrase("сынок","дочка") +"?";
			link.l1 = "Не совсем. И что же это?";
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = "Готовность с головой ринуться в схватку за коварным и, несомненно, опасным соперником имя которому - приключение!";
			link.l1 = "Видишь ли, друг, рисковать головой, ради приключения без выгоды я не готов"+ GetSexPhrase("","а") +", скажу тебе сразу. Так что если твоё приключение не обещает мне трюм серебра, или мешок галеонов, то разговор наш можно закончить.";
			link.l1.go = "5";
		break;

		case "5":
			dialog.text = "...(загадочно улыбается)... Разумеется, в накладе ты не останешься, а если голова у тебя светлая, и что главное - ты умеешь её использовать, то сможешь неплохо разбогатеть, ну, а если умнее тебя во всём архипелаге не сыщешь, то и пару вещичек ценных сможешь прихватить. Только вначале, я бы хотел тебе рассказать историю ...(причмокнув губами)..., послушай её, тебе полезно будет.";
			link.l1 = "Ну, давай, послушаем.";
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = "Мой отец служил как-то юнгой на одном пиратском бриге ''Фэйлоре''. Молодая кровь, горячая голова, сильные руки, зоркий взгляд. Да и смекалкой его бог не обделил, вот только больно суетливый он был, папаша мой, прямо как ты. \n И, если бы не суетливость его непомерная, быть ему капитаном меньше чем через пару лет, а так нет, засиделся в юнгах не один год. А когда опомнился, поздно уже было, время назад не воротишь. Так что, запомни, сынок, перво-наперво - не суетись. Ибо суета - причина провала...";
			link.l1 = "Ты что говоришь-то старик? В наше время, если не подсуетишься, останешься с носом у разбитого корыта. В прямом смысле слова.";
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = "А вот это ты обожди, не путай расторопность с суетливостью. Расторопность - успех. Суетливость - провал. Запомнил?";
			link.l1 = "Запомнил"+ GetSexPhrase("","а") +". Так что там с приключением-то?";
			link.l1.go = "8";
		break;

		case "8":
			dialog.text = "Эх, молодо, зелено, опять вот торопишь старика, и не стыдно тебе?";
			link.l1 = "А вот тут, твоя вина, у меня дела, а ты ходишь всё вокруг да около, отвлекаешь меня. Давай расторопнее.";
			link.l1.go = "9";
		break;

		case "9":
			dialog.text = "Хорошо-хорошо. Итак, ты слушаешь? Слушай внимательнее. Я предлагаю тебе приключение, а если быть более точным игру. Если ты смекалист"+ GetSexPhrase("","ка") +", не лишён"+ GetSexPhrase("","а") +" ума, да и с логикой в дружбе, тебе с приключением нашим по пути. А коли, туп"+ GetSexPhrase("","а") +", да глуп"+ GetSexPhrase("","а") +", то скатертью дорожка...";
			link.l1 = "Я не "+ GetSexPhrase("дурак","дурочка") +", если ты об этом! Или ты думаешь, я смог"+ GetSexPhrase("","ла") +" бы стать, капитаном корабля, будь я глуп"+ GetSexPhrase("ым","ой") +"?";
			link.l1.go = "10";
		break;

		case "10":
			dialog.text = "Коли так, готов"+ GetSexPhrase("","а") +" вступить в игру?";
			link.l1 = "А поподробней можно? Что это за игра-то такая?";
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = "Всё проще пареной репы! Вернее на словах это просто, а в жизни, глядишь всё куда сложнее. Хмф... Ты когда-нибудь слышал"+ GetSexPhrase("","а") +" об игре под названием Дозор, "+ GetSexPhrase("сынок","дочка") +"?";
			link.l1 = "Конечно, слышал"+ GetSexPhrase("","а") +"!";
			link.l1.go = "12";
			link.l2 = "Впервые слышу. Можно поподробнее? Что это за термин такой?";
			link.l2.go = "13";
		break;

		case "12":
			dialog.text = "Отлично! Тогда тебе и объяснять ничего не надо! Только в нашей игре, в отличие от настоящего Дозора всё проще: восемь заданий, без подсказок, уровней опасности и ограничений по времени. \n Раздуплил"+ GetSexPhrase("","а") +" - вводи данные в специальный прибор, который я тебе дам (мекахромом, зовётся), получай ключевую фразу, поднимай парус, и на очередной остров, к агенту! Говоришь ему ключевую фразу, и получаешь следующий Мекахром.";
			link.l1 = "А что это за Мекахром такой?";
			link.l1.go = "15";
		break;

		case "13":
			dialog.text = "В этой игре тебе предстоит пройти восемь заданий. Каждое задание - это загадка, головоломка, которую ты должен разгадать, или, говоря профессиональным языком, ''раздуплить''.";
			link.l1 = "Например?";
			link.l1.go = "14";
		break;

		case "14":
			dialog.text = "Ну слыхал"+ GetSexPhrase("","а") +", наверное, А и Б сидели на трубе, А упало, Б пропало, кто остался на трубе? Правильный ответ - И! Здесь по типу того же. Даётся тебе загадка. \n Разгадал"+ GetSexPhrase("","а") +" - вводи разгадку в специальный прибор, который я тебе дам (Мекахромом зовётся), получай ключевую фразу, поднимай парус, и на очередной остров, к агенту! Говоришь ему ключевую фразу, и получаешь следующее задание.";
			link.l1 = "А что это за Мекахром такой?";
			link.l1.go = "15";
		break;

		case "15":
			dialog.text = "Это устройство получения ключевых фраз.";
			link.l1 = "И как этим устройством пользоваться?";
			link.l1.go = "16";
		break;

		case "16":
			dialog.text = "Эхма, да чего там уметь-то? Наливай, да пей, сам"+ GetSexPhrase("","а") +" уж чай разберёшся, коли загадки взял"+ GetSexPhrase("ся","ась") +" разгадывать.";
			link.l1 = "Ну, хорошо, допустим, я разгадал"+ GetSexPhrase("","а") +" все восемь загадок, и что в конце? Ты вроде что-то упоминал про ценные предметы?";
			link.l1.go = "17";
		break;

		case "17":
			dialog.text = "Ну, если дойдёшь до конца игры, будет у тебя и деньги, и слава, и ценные вещи, будь уверен"+ GetSexPhrase("","а") +"! Ну что соглас"+ GetSexPhrase("ен","на") +"?";
			link.l1 = "Пожалуй, соглас"+ GetSexPhrase("ен","на") +". Только вот ещё вопрос, какой...";
			link.l1.go = "18";
		break;

		case "18":
			dialog.text = "Э, обожди, "+ GetSexPhrase("мил человек","добрая леди") +", обожди. Я над этой игрой 2 года трудился, и хочу что оплаты за свой труд...";
			link.l1 = "Оплаты?! И сколько же я долж"+ GetSexPhrase("ен","на") +" буду заплатить?";
			link.l1.go = "19";
		break;

		case "19":
			dialog.text = "Э, ты не кричи, так, не кричи. Я же толкую тебе о чём? О том, что я 2 года готовил эту игру! Искал агентов по всему архипелагу, придумывал загадки, то да сё.";
			link.l1 = "И сколько же ты хочешь?";
			link.l1.go = "20";
		break;

		case "20":
			dialog.text = "20000 пиастров.";
			link.l1 = "Чего?!";
			link.l1.go = "21";
		break;

		case "21":
			dialog.text = "...(усмехаясь)... Так ты так ничего и не понял"+ GetSexPhrase("","а") +", "+ GetSexPhrase("сынок","дочка") +"?";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +", что если соглашусь, то мои кровно заработанные 20000 - коту под хвост!";
			link.l1.go = "22";
		break;

		case "22":
			dialog.text = ""+ GetSexPhrase("Сынок","Дочка") +", пройдя эту игру, ты получишь такой богатый клад, который тебе и не снился! И славу одного из самых умных капитанов архипелага.";
			link.l1 = "А если я не дойду до конца?";
			link.l1.go = "23";
		break;

		case "23":
			dialog.text = "Что струсил"+ GetSexPhrase("","а") +"? Боишься?";
			link.l1 = "Я ничего и никого не боюсь!";
			link.l1.go = "24";
		break;

		case "24":
			dialog.text = "Тогда вперёд! Навстречу приключениям! Ты ведь за этим сюда приш"+ GetSexPhrase("ёл","ла") +", не так ли?!";
			link.l1 = "Да, за этим, только...";
			link.l1.go = "25";
		break;

		case "25":
			dialog.text = "Похоже, я бесполезно трачу своё время. В последний раз предлагаю тебе. Да или нет?";

			NPChar.NeedMoney = 20000;
			if(sti(PChar.money) >= sti(NPChar.NeedMoney))
			{
				link.l1 = "Хорошо я соглас"+ GetSexPhrase("ен","на") +".";
				link.l1.go = "26";
			}

			link.l2 = "Мне нужно время, чтобы собрать такую сумму.";
			link.l2.go = "27";
			link.l3 = "Да пошёл ты! Иди и поищи себе другого "+ GetSexPhrase("лоха","лохушку") +", я на такой развод не куплюсь.";
			link.l3.go = "29";
		break;

		case "26":
	        AddMoneyToCharacter(pchar,-sti(NPChar.NeedMoney));
			dialog.text = "Вот так бы сразу. Вот держи, это первый Мекахром, в нём информация о первой загадке. Удачи!";
			link.l1 = "И тебе удачи. Прощай.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DozorStart");
		break;

		case "27":
			dialog.text = "Поторопись, я долго ждать не буду.";
			link.l1 = "Как найду - сразу к тебе. До встречи, старик.";
			link.l1.go = "exit";
			NextDiag.TempNode = "28";
			AddDialogExitQuestFunction("DozorWait");
		break;

		case "28":
			dialog.text = "Наш"+ GetSexPhrase("ёл","ла") +" деньги?";
			NPChar.NeedMoney = 20000;
			if(sti(PChar.money) >= sti(NPChar.NeedMoney))
			{
				link.l1 = "Все 20000 здесь.";
				link.l1.go = "26";
			}

			link.l2 = "Ещё нет, как найду - сразу к тебе.";
			link.l2.go = "exit";

			link.l3 = "Знаешь, я тут подумал"+ GetSexPhrase("","а") +"... Да пошёл ты! Иди и поищи себе другого "+ GetSexPhrase("лоха","лохушку") +", я на такой развод не куплюсь.";
			link.l3.go = "29";
			NextDiag.TempNode = "28";
		break;

		case "29":
			DozorCancel();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
