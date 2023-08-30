#include "DIALOGS\russian\Common_Duel.c"

#define MAX_PGG_STORIES 		12
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		8

string PGG_Stories[MAX_PGG_STORIES] = {
	"... только я и дьявол знаем это место, и последний, кто останется в живых, заберёт себе всё!..\n",
	"... а Мейнард ответил: 'Я не жду от тебя пощады, и ты тоже не дождёшься её от меня'.\n",
	"... Кошки впились в борт нам! По местам стоять! И морскому дьяволу тут не устоять!..\n",
	"... В правой руке сабля! В левой - пистолет! Вместе мы отправим сотни на тот свет!..\n",
	"... Нас припёрли к мачте! Дыму - как в аду! Лучше сдохнуть в схватке, чем висеть в порту!\n",
	"... однажды в море, будучи немного пьяным, он предложил: 'Давайте здесь сейчас устроим себе сами ад и посмотрим, кто дольше выдержит'.\n",
	"... А вот презабавная история, которая случилась с моим давним приятелем в Портобэлло. Идём как-то мы вечерними улицами от порта к горячему кварталу. Я на фоке, а спутник мой уже и грот-марсель взял на риф, тут навстречу нам пара бригантин. Что регели, что транец – всё при них. И как только мы поравнялись бортами, мой приятель как даст из двух бортов! Ха-ха-ха-ха...\n",
	"... Ха-ха-ха!.. А вот в Сантакрузе был случай во время швартовки. С криком 'Полундра!' кидает мой матрос выбраску и попадает местному зеваке прямёхонько в лоб! Тот – брык! – и падает без чувств. Матрос испугался, не дожидаясь трапа прыгает на пирс и давай отливать бедолагу водой из ендовы. Наконец тот приходит в себя и говорит матросу: - Когда бросаешь полундру, кричать нужно 'Па-берегись!'. Ах-ха-ха ...",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues"
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
	"...Как-то застряли мы во Флориде - пережидали штиль. Когда в таверне закончились запасы рома, угораздило нас завалиться в бордель. И будучи под рифом, я, видать, сболтнул одной из девок про золотишко, что припрятал на чёрный день. Так представьте - когда через месяц я наведался в свой тайник, он был пуст, как голова с похмелья! Укуси меня сардина, если эта языкатая бестия не выболтала о моей заначке первому же проходимцу. Так что веры женщинам у меня ни на пол песо нет!..\nА вот к нашему столу пожаловал бывалый повеса. Он уж наверняка имеет к девицам особый подход. Или я не прав? Укуси меня сардина, ха-ха-ха!..",
	"...а он так с издёвкой ей и говорит: 'Пойдём, мол, наверх. Прежде, чем принимать в команду, надо бы проверить что ты умеешь, как офицер'. А девка эта выхватила тесак чуть не с неё размером и говорит: 'Сначала проверим, годитесь ли вы мне в капитаны!' Ха-ха-ха... Она гоняла его, как акула треску по всей таверне, и было бы это очень смешно, джентльмены, не прикончи она того бедолагу прямо посреди зала на глазах у всех. Упокой Господь его душу... Да только я с тех пор на Бермудах гляжу в оба, вдруг она ещё там обретается!\nХо, поприветствуем достойного капитана, который наверняка бы нашёл способ поладить с этой фурией! Ах-ха-ха-ха...",
	"TBD in InitDynamicValues"
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
	"Редко встретишь порядочного капитана в этих морях.",
	"Благородство не в моде в наше время.",
	"А вот и честный капитан, не чета вам, головорезы! Хе-хе!",
	"Редко встретишь порядочного капитана в этих местах.",
	"Чёрт возьми, благородство нынче не в моде.",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues"
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
	"А вот и ещё один пират!",
	"Запахло порохом и кровью, флибустьер справа по борту!",
	"Чувствую, запахло порохом... Джентльмены, к нам присоединился ещё один славный корсар, которому уж наверняка будет что порассказать на исповеди. Ха-ха-ха",
	"Запахло порохом и кровью справа по борту!",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues",
	"TBD in InitDynamicValues"
};

string PGGQuestID = "Gen_PGGQuest1";
bool isSetSail = false; // флаг того, что поймали ПГГ на море
bool isPGGInitiative = false; // флаг того, что ПГГ сам подошел

void InitDynamicValues(ref NPChar) {
	isSetSail = CheckAttribute(NPChar, "PGGAi.Task.SetSail");
	isPGGInitiative = CheckAttribute(NPChar, "PGGAi.ActiveQuest");
	if (NPChar.sex == "woman") PGGQuestID = "Gen_PGGQuest1" + NPChar.sex;

	PGG_Stories[8] = "... Нет, джентльмены, это всё анекдоты... А вот история, в которой я собственнолично был" + NPCharSexPhrase(NPChar, "", "а") + " не только свидетель, а в некотором роде и участник. Направляюсь как-то в таверну Чарльстауна прямёхонько из дока, где наблюдал" + NPCharSexPhrase(NPChar, "", "а") + " кренгование своего старого 'Кондора', а навстречу мне из двери таверны вываливается сам капитан Шарп! Штормит его нещадно, бизань уже сорвало напрочь, и только блиндом он пытается маневрировать по ступеням. Не успел" + NPCharSexPhrase(NPChar, "", "а") + " я предложить ему услуги лоцмана, как перила под ним–хрясть!!! Хо-хо-хо-хо...\n",
	PGG_Stories[9] = "... Ничего не могу сказать о Летучем Голландце. Ни мне, ни кому-либо из моих матросов видеть его, слава Богу, не доводилось... Но был случай не менее загадочный. К востоку от Бермуды встретилась нам бригантина под всеми парусами, но шла она странным курсом – эдакими зигзагами. Я ничего такого не замышлял" + NPCharSexPhrase(NPChar, "", "а") + ", но шлюпку выслал" + NPCharSexPhrase(NPChar, "", "а") + ". Каково же было наше удивление, когда на борту не оказалось ни единой души!.. А в трюме – 1700 баррелей отличного вина!.. Вот что я называю удачей! И без единого выстрела! Ха-ха-ха..\n",
  PGG_Stories[10] = "... Всё же я склон" + NPCharSexPhrase(NPChar, "ен", "нa") + " думать, джентльмены, что все эти россказни о Летучем Голландце не более чем досужие выдумки трусливых торгашей, которые в каждом парусе на горизонте готовы видеть кровожадного капера с пьяным чудовищем на капитанском мостике, а в каждом встреченном люггере – предвестника несчастий...\n";
	PGG_Stories[11] = "... Может быть кто помнит тот случай южнее Ки-Уэста, когда меня бимсом контузило?.. Хотя видимых повреждений и не было, – провалял" + NPCharSexPhrase(NPChar, "ся", "ась") + " я месяца два. " + NPCharSexPhrase(NPChar, "И тогдашняя моя пассия уговорила", "И тогдашний мой друг уговорил") + " меня исповедаться. Мол, с Божьей помощью дело на лад пойдёт... Ну, пош" + NPCharSexPhrase(NPChar, "ёл", "ла") + " я, а священник и спрашивает: 'А много ли ты людей погубил" + NPCharSexPhrase(NPChar, "", "а") + ", " + NPCharSexPhrase(NPChar, "сын мой", "дочь моя") + "? А много ли кораблей потопил" + NPCharSexPhrase(NPChar, "", "а") + "?' – 'Мно-ого', – отвечаю. А он не унимается: 'А много ли ты " + NPCharSexPhrase(NPChar, "жён", "мужчин") + " соблазнил" + NPCharSexPhrase(NPChar, "", "а") + "?'. Тут я и говорю: 'Падре, я же сюда не хвастаться приш" + NPCharSexPhrase(NPChar, "ёл", "ла") + "!'. Ха-ха-ха-ха...\n";

	// TODO: не подходят по контексту, надо бы заменить для женского ПГГ
	if (NPChar.sex == "woman") {
		PGG_QuestStories[0] = "... В правой руке сабля! В левой - пистолет! Вместе мы отправим сотни на тот свет!..";
		PGG_QuestStories[1] = "... Нас припёрли к мачте! Дыму - как в аду! Лучше сдохнуть в схватке, чем висеть в порту!";
	}
	PGG_QuestStories[2] = "...Уж не знаю, как сам 'Летучий Голландец', но корабль с призраками я видел" + NPCharSexPhrase(NPChar, "", "a") + " своими глазами, как сейчас вижу вас, джентльмены!.. Чёртов фрегат, чёрный как ночь, вылетел из тумана и пошёл на абордаж без единого выстрела! Признаться, я изрядно струхнул" + NPCharSexPhrase(NPChar, "", "a") + ", но мы увернулись левым галсом и только приготовились дать залп картечью, как он исчез, так же внезапно, как и появился! Он летел по волнам словно птица! Я лишь название успел" + NPCharSexPhrase(NPChar, "", "a") + " рассмотреть на транце - 'Королева'... И разрази меня гром - на палубе и вантах этой посудины было полно живых мертвяков...\nВот такая вот дьявольщина... А кто бы не струхнул? Вдруг за штурвалом там стоял сам Морской Дьявол? хо-хо-хо!.. Рому всем!",

  PGG_Meet_BadRep[4] = "О-о джентльмены, а вот и бывалый корсар, у которого наверняка есть что порассказать в дружной компании за кружкой рома... " + IfPhraseSimple(isSetSail, "", "Не желаете присоединиться?");
	PGG_Meet_BadRep[5] = "Джентльмены, у " + IfPhraseSimple(isSetSail, "нас на палубе", "нашего стола") + " джентльмен удачи, я полагаю.";
	PGG_Meet_BadRep[6] = "А вот и ещё од" + GetSexPhrase("ин баловень Фортуны","на морская волчица") + "!";
	PGG_Meet_BadRep[7] = GetSexPhrase("Очередной джентльмен удачи","Очередная покорительница морей") + ", я полагаю.";

  PGG_Meet_GoodRep[5] = "А вот и ещё од" + GetSexPhrase("ин  славный корсар, который не привык", "нa покорительница морских просторов, которая не привыкла") + " искать лёгких путей..."
	PGG_Meet_GoodRep[6] = "А вот и героическая личность, уже наслышан" + NPCharSexPhrase(NPChar, "", "a") + " о вас!";
	PGG_Meet_GoodRep[7] = "Джентльмены, у " + IfPhraseSimple(isSetSail, "нас на корабле", "нашего столика") + " достойн" + GetSexPhrase("ый капитан", "aя морская волчица") + ", котор" + GetSexPhrase("ый", "aя") + " бывал" + GetSexPhrase("", "а") + " ещё не в таких переделках. О чём поведаете, уважаем" + GetSexPhrase("ый", "aя") + "?";
}

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	InitDynamicValues(NPChar);

  ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";

	switch(Dialog.CurrentNode)
	{
	case "Enemy_town":
		Dialog.text = "Хм... Я конечно, сорвиголова, но так рисковать.... Ну уж нет, я пойду своей дорогой...";
		link.l1 = RandPhraseSimple("Эх... Да и ладно...", "Всего хорошего.");
		link.l1.go = "Exit";
		break;	

	case "First time":
		if (!CheckAttribute(PChar, "questTemp.DuelTimer"))
		{//Запускаем счётчик для отката
			PChar.questTemp.DuelTimer = true;
			SaveCurrentQuestDateParam("PChar.questTemp.DuelCooldown");
		}

		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(PChar, "questTemp.PGGContra.Know"))
		{
			ContrabandDialog(link);
			break;
		}

		if(rand(10) == 0)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else {
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd] + LinkRandPhrase("... Разрази меня гром!.. ", "... Укуси меня змея!.. ", "... Держите меня семеро!.. ") + PCharRepPhrase(PGG_Meet_BadRep[iAns], PGG_Meet_GoodRep[iAns]);
		}

		if (sti(PChar.Ship.Type) != SHIP_NOTUSED) {
			link.l1 = PCharRepPhrase(
				RandSwear() + RandPhraseSimple(
					"Я капитан " + GetFullName(PChar) + ".",
					"Я капитан посудины '" + PChar.Ship.Name + "' и пары сотен отчаянных сукиных детей! Хе-хе! Моё имя " + GetFullName(PChar) + "."
				),
				RandPhraseSimple(
					"Позвольте представиться. Я капитан " + GetFullName(PChar) + ".", 
					"Не имел" + GetSexPhrase("","а") + " чести быть вам представленн" + GetSexPhrase("ым","ой") + ". Я капитан корабля '" + PChar.Ship.Name + "' под флагом " + NationNameGenitive(sti(PChar.nation)) + ". Моё имя " + GetFullName(PChar) + "."
				)
			);
		} else {
			link.l1 = "Позвольте представиться, меня зовут " + GetFullName(PChar) + ". По воле случая оказался без корабля.";
		}

		link.l1.go = "Second time";
		NPChar.onceGreeting = true;
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(PChar, "questTemp.PGGContra.Know")) {
			ContrabandDialog(link);
			break;
		}
		
		// если репа позволяет, общаемся по-человечески
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd] + PCharRepPhrase(PGG_Meet_BadRep[iAns], PGG_Meet_GoodRep[iAns]) + 
				RandPhraseSimple(" Какие вести?", " Что нового творится на архипелаге?");

			if(rand(10) == 0)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd] + PCharRepPhrase(" Какие вести?", " Что нового творится на архипелаге?");
			}
		} else {
			Dialog.text = RandPhraseSimple(
				"Что тебе надо " + GetFullName(PChar) + "?", 
				RandPhraseSimple(
					"Кто это? А, ты... Проваливай, я не в настроении...", 
					"А, это ты... Гуляй мимо, я не в настроении..."
				)
			);
		}

		link.l1 = "Как на счёт дельца?";
		link.l1.go = "quest";

		// && !CheckAttribute(NPChar, "PGGWhisperQuestEnd") && !CheckAttribute(PChar, "PGGWhisperComplete")	//выглядит избыточно - достаточно 1го должно быть
		if (NPChar.name == "Виспер" && !CheckAttribute(NPChar, "PGGWhisperQuestStart") && GetCharacterShipClass(PChar) < 4 && PChar.rank >= 15)
		{			
			Dialog.Text = "Знаешь, ты как нельзя вовремя, есть одно дело.";
			link.l1 = "Ты о чём?";
			link.l1.go = "Quest_Whisper";
			//DeleteAttribute(PChar, "GenQuest.PGG_Quest");//Зачем это здесь? Какая связь с ПП и квестом Виспер? 
			//разобраться, сможет ли ВИспер после квеста выдавать ПП нормально?
		}

		link.lgame = "Не хочешь развеяться?";
		link.lgame.go = "Play_Game";

		if(!CheckAttribute(PChar, "PGG_hired"))
		{
			if (sti(PChar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = "Я тут подумал"+ GetSexPhrase("","а") +", не хочешь ко мне присоединиться? " + 
					"С двумя кораблями мы сможем хорошие дела провернуть.";
				link.l2.go = "companion";
			}

			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				link.l3 = RandPhraseSimple(
					"Не хочешь пойти офицером ко мне на корабль?", 
					"Пожалуй, такой офицер как ты, мне бы не помешал. Что скажешь?"
				);
				link.l3.go = "officer";
			}
		}

		// потерял корабль, переопределяем все выше сказанное
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED) {
			Dialog.Text = RandPhraseSimple(
				"Эх, горе мне, горе... Корабль мой на дне!", 
				"Кого я вижу?! Каким ветром занесло в наши края? А я вот без корабля остал" + NPCharSexPhrase(NPChar, "ся","ась") + "..."
			);
		}

		// первый раз встретили, переопределяем все выше сказанное
		if (CheckAttribute(NPChar, "onceGreeting")) {
			Dialog.Text = "Ну, а меня здесь все знают! Я - " + GetFullName(NPChar);
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED) {
				Dialog.Text = Dialog.Text + ", капитан " + XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen") + " '" + NPChar.Ship.Name + "'";
			}
			Dialog.Text = Dialog.Text + ". Приятно познакомиться, чем могу быть полез" + NPCharSexPhrase(NPChar, "ен", "на") + "?";
			DeleteAttribute(NPChar, "onceGreeting");
		}
		
		if (bBettaTestMode)
		{
			link.l5 = "(Бетта-Тест) Квесты.";
			link.l5.go = "BT_Quest";
			link.l6 = "(Бетта-Тест) Дуэли.";
			link.l6.go = "outraged";
		}

		if (GetQuestPastDayParam("PChar.questTemp.DuelCooldown") >= 3 || bBettaTestMode)
		{
			if (sti(PChar.reputation < 20) && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 51 && !isSetSail)
			{
				link.l8 = PCharRepPhrase(
					"Эта таверна слишком тесна для нас двоих. Я хочу, что бы ты исчез" + NPCharSexPhrase(NPChar, "", "ла") + ".",
					"Если бы ты знал" + NPCharSexPhrase(NPChar, "", "а") + " с кем говоришь, по другому запел" + NPCharSexPhrase(NPChar, "", "а") + " бы, " + NPCharSexPhrase(NPChar, "ублюдок", "портовая шалава") + "."
				);
				link.l8.go = "outraged";
			}
		}

		link.l9 = "Ничего.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow && !CheckAttribute(NPChar, "HiringMoneyPaid"))
		{
			Dialog.Text = RandPhraseSimple(
				"Я тебе уже говорил" + NPCharSexPhrase(NPChar, "", "а") + ", что мне это не интересно.", 
				"Мне казалось, мы уже все обсудили."
			);
			link.l1 = RandPhraseSimple("Как я мог"+ GetSexPhrase("","ла") +" забыть?!", "А и правда. Ну, бывай.");
			link.l1.go = "exit";
			break;
		}

		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("Хм... пожалуй, нет. Второй раз нет желания.", "И ты думаешь, я клюну на эту удочку дважды?!!");
			link.l1 = RandPhraseSimple("Как хочешь...", "Ну.., береги себя.");
			link.l1.go = "exit";
			break;
		}

		//если отношение ниже 70, то в 70 процентов случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && drand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("Хм.. пожалуй, нет... ", "Нет, это не по мне! Я не хочу быть офицером!");
			link.l1 = RandPhraseSimple("Ну, как хочешь...", "Что ж, счастливо оставаться.");
			link.l1.go = "exit";
			NPChar.HiringMoney = sti(NPChar.rank)*100000;
			link.l2 = "Тогда я сделаю предложение, от которого ты уже не сможешь отказаться. " + NPChar.HiringMoney + " пиастров.";
			link.l2.go = "officer_pay";

			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple(
				"Да у тебя и так полный комплект.", 
				"Не думаю, что ты готов"+ GetSexPhrase("","а") +" командовать мной."
			);
			link.l1 = RandPhraseSimple("Жаль...", "Значит не судьба.");
			link.l1.go = "exit";
			
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}

		if (!CheckAttribute(NPChar, "Quest.Officer.Price")) NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE*3 - MakeInt(GetSummonSkillFromNameToOld(PChar, SKILL_COMMERCE)*1000);
		
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
			RandPhraseSimple(
				"Это - то, что нужно! Наши клинки напьются вражеской крови! Одна проблемка, мне нужно " + NPChar.Quest.Officer.Price + " пиастров, чтобы расплатиться с долгами.",
				"Ты выглядишь настоящ" + GetSexPhrase("им морским волком","ей морской волчицей") + ". И если ты готов" + GetSexPhrase("","а") + " заплатить " + NPChar.Quest.Officer.Price + " пиастров, то, пожалуй, мы сработаемся."
			),
			LinkRandPhrase(
				"Ваше предложение весьма лестно для меня. Я согласен за весьма умеренную плату в размере " + NPChar.Quest.Officer.Price + " пиастров.",
				"Хм... Вы выглядите бывал" + GetSexPhrase("ым","ой") + " моря" + GetSexPhrase("ком","чкой") + ". Возможно, мне стоит принять предложение, если вы согласны заплатить мне " + NPChar.Quest.Officer.Price + " пиастров.",
				"Думаю, мы сработаемся капитан. Всего " + NPChar.Quest.Officer.Price + " пиастров и мы ударим по рукам."
			)
		);

		MakeRandomLinkOrderTwo(link, 
			PCharRepPhrase(RandSwear() + 
				RandPhraseSimple(
					"Меня это устраивает. Но, надеюсь, ты не каждый день будешь требовать столько.", 
					"Это чертовски дорого, но, думаю, ты того стоишь."
				),
				LinkRandPhrase(
					"Я соглас"+ GetSexPhrase("ен","на") +". Считай себя зачисленным в команду.", 
					"Хм... Пожалуй, я готов"+ GetSexPhrase("","а") +" расстаться с этой суммой.", 
					"Похоже, ты стоишь этих денег. Держи!"
				)
			), "officer_hired",
			PCharRepPhrase(RandSwear() + 
				RandPhraseSimple(
					"Ты не стоишь столько. Бывай...", 
					"Это чертовски дорого, я не готов"+ GetSexPhrase("","а") +" выкидывать столько денег."
				),
				LinkRandPhrase(
					"Да... жадность не порок...", 
					"Да ты смеёшься надо мной? За такие деньги я могу купить десяток таких, как ты.", 
					"Это грабеж... где я возьму тебе такую сумму?"
				)
			), "exit"
		);

		link.l3 = "Хм... а что ты представляешь из себя?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (!CheckAttribute(NPChar, "HiringMoneyPaid") && sti(PChar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "Похоже, у вас проблемы с наличностью, капитан.";
			link.l1 = "Ах... действительно.";
			link.l1.go = "exit";
			break;
		}

		Restore_PGG(NPChar);
		PChar.questTemp.HiringOfficerIDX = NPChar.index;
		if (NPChar.model.animation == "man" || NPChar.model.animation == "YokoDias" || NPChar.model.animation == "Milenace") NPChar.CanTakeMushket = true;
		if(NPChar.model == "PGG_Whisper_6") EquipCharacterByItem(NPChar, "suit_1");
		if (!CheckAttribute(NPChar, "HiringMoneyPaid")) AddMoneyToCharacter(PChar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		if (NPChar.sex == "woman") {
			NPChar.greeting = "Gr_Danielle";
		}

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");
		
		Dialog.Text = RandPhraseSimple("Вот и отлично!", "Я не сомневал" + NPCharSexPhrase(NPChar, "ся","ась") + " в вас, капитан.");
		link.l1 = "Не опаздывай к отплытию.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion
//==================================================
	case "companion":
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow  && !CheckAttribute(NPChar, "HiringMoneyPaid"))
		{
			Dialog.Text = RandPhraseSimple("Я тебе уже говорил" + NPCharSexPhrase(NPChar, "", "а") + ", что мне это неинтересно.", "Мне казалось, мы всё обсудили.");
			link.l1 = RandPhraseSimple("Как я мог"+ GetSexPhrase("","ла") +" забыть?!", "И правда. Ну, бывай.");
			link.l1.go = "exit";
			break;
		}

		// если разница в кораблях больше 1 класса, отказываем
		if (GetCharacterShipClass(PChar) - 1 > GetCharacterShipClass(NPChar))
		{
			Dialog.Text = RandPhraseSimple("Плавать с тобой!?? Корабль побольше найди!", "Не думаю, что мне это интересно!");
			link.l1 = RandPhraseSimple("Ну, как хочешь...", "Что ж, счастливо оставаться.");
			link.l1.go = "exit";

			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}

		if (GetCompanionQuantity(PChar) >= COMPANION_MAX) {
			MaxCompanionsExceededDialog(link, NPChar)
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}

		//если отношение ниже 70, то в 100 процентов случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70)
		{
			Dialog.Text = RandPhraseSimple(
				"Хм.. пожалуй, нет... Я тебя совсем не знаю. Для начала нам стоит как-нибудь вместе на дельце сходить.", 
				"Нет, спасибо. Не люблю плавать под чьим-то началом. Да и я тебя совсем не знаю. Нам стоит как-нибудь вместе на дельце сходить, прежде чем такие предложения друг другу делать."
			);
			link.l1 = RandPhraseSimple("Ну, как хочешь...", "Что ж, счастливо оставаться.");
			link.l1.go = "exit";
			NPChar.HiringMoney = sti(NPChar.rank)*100000;
			link.l2 = "Тогда я сделаю предложение, от которого ты уже не сможешь отказаться. "+ NPChar.HiringMoney+ " пиастров.";
			link.l2.go = "companion_pay";

			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}

		SetCompanionIndex(PChar, -1, sti(NPChar.index));
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
			RandPhraseSimple(
				"Ты мне нравишься! По рукам! Я уже слышу звон пиастров в наших карманах!",
				"А ты "+ GetSexPhrase("парень","девка") +" не промах... Думаю, мы сработаемся!"
			),
			LinkRandPhrase(
				"Ваше предложение мне нравится. Я соглас" + NPCharSexPhrase(NPChar, "ен", "на") + ".",
				"Это интересно. Я тоже думаю, что вместе мы сможем больше!", 
				"Пожалуй, это будет занятно. По рукам."
			)
		);
		link.l1 = RandPhraseSimple("Отлично, жду тебя в море!", "По рукам! Мы будем отличной командой.");
		link.l1.go = "exit";

		Restore_PGG(NPChar);
		NPChar.PGGAi.IsPGG = false;
		NPChar.PGGAi.location.town = "none";
		NPChar.Dialog.TempNode = "hired";
		NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
		NPChar.Payment = true;
		NPChar.Money   = 0;

		if (NPChar.model.animation == "man" || NPChar.model.animation == "YokoDias" || NPChar.model.animation == "Milenace") NPChar.CanTakeMushket = true;
		if(NPChar.model == "PGG_Whisper_6") EquipCharacterByItem(NPChar, "suit_1");
		PGG_Disband_Fleet(NPChar);
		SetBaseShipData(NPChar);
		DeleteAttribute(NPChar,"ship.sails");
		DeleteAttribute(NPChar,"ship.masts");
		DeleteAttribute(NPChar,"ship.blots");
		Fantom_SetCannons(NPChar, "pirate");
		Fantom_SetBalls(NPChar, "pirate");

		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");
		SetCharacterRemovable(NPChar, true);
		SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		LAi_SetImmortal(NPChar, false);

		break;

	case "companion_pay":
		if (sti(PChar.money) < sti(NPChar.HiringMoney))
		{
			NotEnoughMoneyDialog(link, NPChar);
			break;
		}
		
		Dialog.Text = RandSwear() + "И правда не могу."
		PGG_ChangeRelation2MainCharacter(NPChar, 100);
		AddMoneyToCharacter(PChar, -sti(NPChar.HiringMoney));
		NPChar.HiringMoneyPaid = true;

		link.l1 = "Вот твои деньги.";
		link.l1.go = "companion";

		break;

	case "officer_pay":
		if (sti(PChar.money) < sti(NPChar.HiringMoney))
		{
			NotEnoughMoneyDialog(link, NPChar);
			break;
		}
		
		Dialog.Text = RandSwear() + "И правда не могу."
		PGG_ChangeRelation2MainCharacter(NPChar, 100);
		AddMoneyToCharacter(PChar, -sti(NPChar.HiringMoney));
		NPChar.HiringMoneyPaid = true;
		link.l1 = "Вот твои деньги.";
		link.l1.go = "officer_hired";
	break;

	case "companion_leave":		
		Dialog.Text = RandSwear() + NPCharRepPhrase(NPChar,
			RandPhraseSimple("Разорви тебя акула!!! Я выхожу из состава эскадры!", "Моё терпенье лопнуло! Я ухожу."),
			RandPhraseSimple("С меня достаточно, 'адмирал'!... Я иду своим курсом!", "С меня хватит! Я выхожу из состава эскадры.")
		);

		link.l1 = PCharRepPhrase(
			RandPhraseSimple("Ну и проваливай " + NPCharSexPhrase(NPChar, "на здоровье", "отсюда, дешёвка") + "!", "Можешь катиться ко всем чертям" + NPCharSexPhrase(NPChar, ".", "шмара каютная!")),
			RandPhraseSimple("Что ж, держать не буду.", "Вольному воля. Попутного ветра в паруса.")
		);
		link.l1.go = "Exit_Companion_Leave";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple("Э... как на счёт небольшой премии?", "Каррамба!!! Может, останешься? Я готов"+ GetSexPhrase("","а") +" даже выплатить премию твоей команде!"),
			RandPhraseSimple("Жаль расставаться... Может, небольшое вознаграждение решит наши разногласия?", "Как на счёт прибавки к жалованию?")
		);
		link.l2.go = "companion_stay";
		
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion.Price"))
		{
			Dialog.Text = RandPhraseSimple("Хватит с меня одного раза. Больше я не верю в твои обещания!", "Никакими деньгами меня не соблазнишь. Моё решение окончательно!");
			link.l1 = RandPhraseSimple("Ну что же, тогда всех благ.", "Тогда проваливай, и чтобы я тебя больше не видел"+ GetSexPhrase("","а") +"!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}

		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear() + NPCharRepPhrase(NPChar,
			RandPhraseSimple(
				"Премия? Отлично! Сумма в " + NPChar.Quest.Companion.Price + " пиастров, меня устроит.",
				"Пожалуй, если ты выплатишь моей команде " + NPChar.Quest.Companion.Price + " пиастров, я уговорю их остаться."
			),
			RandPhraseSimple(
				"Хорошо! Я готов" + NPCharSexPhrase(NPChar, "", "а") + " остаться за скромную премию в размере " + NPChar.Quest.Companion.Price + " пиастров!",
				NPChar.Quest.Companion.Price + " пиастров устроят на некоторое время меня и мою команду."
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Да ты смеёшься надо мной! Проваливай ко всем чертям.", 
				"Ха... да я лучше потрачу эти деньги на что-то более полезное!"
			),
			RandPhraseSimple(
				"Ну уж нет. Я не настолько богат" + GetSexPhrase("","а") +"!", 
				"Прощай. Я не желаю платить так много."
			)
		);
		link.l1.go = "Exit_Companion_Leave";

		if (sti(PChar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(
				RandPhraseSimple(
					"Вот и отлично! Держи премиальные!", 
					"Я не сомневал"+ GetSexPhrase("ся","ась") +", что дело только в деньгах!"
				),
				RandPhraseSimple(
					"Прекрасно! Я рад"+ GetSexPhrase("","а") +", что ты остаёшься!", 
					"Вот обещанная премия. И теперь мы снова вместе."
				)
			);
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(PChar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
		GetCharacterPos(NPChar, &locx, &locy, &locz);
		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(PChar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "Выберите шаблон!";
		link.l1 = "Квест 1 Шаблон - морской.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "Квест 2 Шаблон - сухопутный.";
		link.l2.go = "BT_Quest_2";
		link.l3 = "Квест 3 Шаблон - сухопутный.";
		link.l3.go = "HelpBackShip";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "ВЫБРАН! Квест 1 Шаблон - морской.";
		link.l1 = "Ах да...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "ВЫБРАН! Квест 1 Шаблон - сухопутный.";
		link.l1 = "Ах да...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;

		Dialog.Text = RandPhraseSimple("Какие дела?.. Ик... Не видишь мы с друзьями отдыхаем!.. Ик..", "Э... Никаких дел сегодня!");
		link.l1 = "Понятно...";
		link.l1.go = "exit";

		if (!PGG_IsQuestAvaible() && !isSetSail) {
			Log_TestInfo("Неправильная локация для ПП")
			break; // локация не подходит
		}

		if (CheckAttribute(NPChar, "mapEnc") && findsubstr(NPChar.mapEnc.Name, "торговцев" , 0) != -1) // ПГГ с прицепом
		{
			Dialog.Text = "У меня сейчас своих дел хватает. Ты же видишь, что я плыву не " + NPCharSexPhrase(NPChar, "один", "одна") + "?";
			link.l1 = "Понятно...";
			link.l1.go = "exit";
			break;
		}

		if (!CheckAttribute(PChar, "Ship.Type") || sti(PChar.Ship.Type) == SHIP_NOTUSED) // гг без корабля
		{
			PCharNoShipDialog(link, NPChar);
			break;
		}

		if (!CheckAttribute(NPChar, "Ship.Type") || sti(NPChar.Ship.Type) == SHIP_NOTUSED) // пгг без корабля
		{
			PGGNoShipDialog(link, NPChar);
			break;
		}

		if (GetCharacterShipClass(PChar) > 4) // класс не подходит
		{
			PCharShipClassIsLowDialog(link, NPChar);
			break;
		}

		if (GetCompanionQuantity(PChar) >= COMPANION_MAX) // компаньонов максимальное количество
		{
			MaxCompanionsExceededDialog(link, NPChar);
			break;
		}

		int iDays = GetQuestPastDayParam("QuestTalk");
		if (isSetSail && iDays < 7) // поймали в море и с прошлого ПП прошло менее недели
		{
			Log_TestInfo("Не прошло время с предыдущего ПП (нулевой день создания НГ тоже считается)")
			Log_TestInfo("Дней прошло: " + iDays + ", дней осталось: " + sti(7 - iDays))
			PGGQuestNotEnoughtTimePassedDialog(link, NPChar);
			break;
		}

		if (iDays < 14) // поймали в городе и с прошлого ПП прошло менее двух недель
		{
			Log_TestInfo("Не прошло время с предыдущего ПП (нулевой день создания НГ тоже считается)")
			Log_TestInfo("Дней прошло: " + iDays + ", дней осталось: " + sti(14 - iDays))
			PGGQuestNotEnoughtTimePassedDialog(link, NPChar);
			break;
		}

		// квест Виспер постоянно ломал ПП
		if (CheckAttribute(PChar, "PGGWhisperComplete") || CheckAttribute(pchar, "PGGWhisperQuest")) {
			if (CheckAttribute(PChar, "GenQuest.PGG_Quest") && NPChar.name != "Виспер")
			DeleteAttribute(PChar, "GenQuest.PGG_Quest");
		}

 		// TODO: тут неведомая хуйня, вот это иногда багает и так и остается флажок, будто мы на ПП еще, хотя квест закрыт
		// пытался дебажить, но причину найти не смог, вроде во всех исходах мы подчищаем это
		// есть подозрение, что были ошибки до подчистки флага -> мы вылетели к хуям, либо скипнули дальнейшую обработку -> флаг так и остался в подвешенном состоянии
		if (CheckAttribute(PChar, "GenQuest.PGG_Quest"))
		{
			PGGQuestAlreadyActive(link, NPChar);
			break;
		}

		if (drand1(100) > 60 || isSetSail) // шанс 40% на дельце, либо поймали в море
		{
			Dialog.Text = "Что за разговор? Хотя ты вовремя. Дело или дельце - это мы завсегда!";
			link.l1 = "Хм. Ты о чем?";

			if (isSetSail) link.l1.go = "Quest_1_Ship";
			else link.l1.go = "Quest_1_Work";

			NPChar.PGGAi.ActiveQuest = true;
			isPGGInitiative = true;
			PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
			SaveCurrentQuestDateParam("QuestTalk");
		}

		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		SaveCurrentQuestDateParam("QuestTalk");
		Dialog.Text = "Поосторожнее!!! О! Кажется, я знаю тебя, ты - известная личность! Наслышан" + NPCharSexPhrase(NPChar, "", "а") + ", наслышан" + NPCharSexPhrase(NPChar, "", "а") + "."; 

		if (CheckAttribute(NPChar, "meeting") && sti(NPChar.meeting))
		{
			link.l1 = "Привет, " + GetFullName(NPChar) + ". Как дела?";
			link.l1.go = "Quest_1_Work";
			break;
		}
			
		link.l1 = PCharRepPhrase(
			RandSwear() + RandPhraseSimple(
				"Я капитан " + GetFullName(PChar) + ".",
				"Я капитан посудины '" + PChar.Ship.Name + "' и пары сотен отчаянных сукиных детей! Хе-хе! " + 
				"Моё имя " + GetFullName(PChar) + "."
			),
			RandPhraseSimple(
				"Позвольте представиться. Я капитан " + GetFullName(PChar) + ".", 
					"Позвольте представиться. Я капитан " + GetFullName(PChar) + ".", 
				"Позвольте представиться. Я капитан " + GetFullName(PChar) + ".", 
				"Не имел" + GetSexPhrase("","а") + " чести быть вам представленн" + GetSexPhrase("ым","ой") +
				". Я капитан корабля '" + PChar.Ship.Name + "' под флагом " + NationNameGenitive(sti(PChar.nation)) + 
				". Моё имя - " + GetFullName(PChar) + "."
			)
		);
		link.l1.go = "Quest_1_Meeting";
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		Dialog.Text = "Я - " + GetFullName(NPChar) + ", капитан " + XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen") + " '" + NPChar.Ship.Name + "'"
		NPCharSexPhrase(NPChar, 
			NPCharRepPhrase(NPChar, ". Самый известный корсар всего испанского Мэйна.", ". Обычный моряк."), 
			NPCharRepPhrase(NPChar, ". Самая известная покорительница морей на всех Карибах.", ". Самая обычная девушка-пират.")
		);
		link.l1 = "Да, теперь я тебя запомню.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		GeneratePGGQuestLocation(NPChar);

		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"У меня есть отличненькое дельце для Вас и для ваших чертей. ",
				"Объединим силы и мы сможем взять отличный куш! Ну, придётся кое-кого убить, естественно. Хе-хе. "
			),
			RandPhraseSimple(
				"У меня есть к вам деловое предложение, капитан. ",
				"Капитан, ваша репутация хорошо известна и, поэтому, я хочу вам предложить участие в одном заманчивом деле. "
			)
		) + RandPhraseSimple(
			"Только между нами. Давайте-ка, обсудим все у меня в кают-компании на '" + NPChar.Ship.Name + "' за бочонком отличного эля. Сегодня.", 
			"Здесь говорить об этом не резон, потолкуем у меня на судне '" + NPChar.Ship.Name + "' в тишине и в спокойствии. Не затягивайте с визитом."
		);

		link.l1 = PCharRepPhrase(
			RandSwear() + RandPhraseSimple(
				"К чёрту проволочки! Хорошее хочу знать быстро, а плохое ещё быстрее!",
				"Незачем откладывать! В таверне есть комната, там и обсудим!"
			),
			RandPhraseSimple(
				"Почему бы не обсудить ваше предложение прямо сейчас, в комнате таверны?",
				"Боюсь, у меня нет желания посещать ваше судно. Если вам что-то нужно, выкладывайте здесь!"
			)
		);
		link.l1.go = "Quest_1_Work_1";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple(
				"Я приду! Но, если ты попусту потратишь моё время, я вырву тебе язык!",
				RandSwear() + "Жди, надеюсь, дело стоящее. И не вздумай шутить со мной!"
			),
			RandPhraseSimple(
				"Я с удовольствием принимаю ваше приглашение, капитан.",
				"Вы меня заинтриговали. Разумеется, я приду."
			)
		);
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Да тебя, небось, от качки тошнит! Иди, найди себе мамашу с соской!!!",
				"Что, "+ GetSexPhrase("приятель","подруга") +", в штаны наложил"+ GetSexPhrase("","а") +" от страха?!! Вали! Ты мне не пара."
			),
			RandPhraseSimple(
				"Нет - так нет. Неволить не буду, значит, неинтересно тебе золото.",
				"Или так, или никак. Тебе решать. На золото много охотников."
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Ха! А ты с перчиком! И не боишься... Приду!",
				"Умеешь настоять на своём, капитан. Жди."
			),
			RandPhraseSimple(
				"Хорошо, я соглас"+ GetSexPhrase("ен","на") +".",
				"Вы очень убедительны. Я готов"+ GetSexPhrase("","а") +" обсудить дела на вашем судне."
			)
		);
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple(
				"Ха! Думал" + NPCharSexPhrase(NPChar, "", "а") + " заманить меня на свой корабль и убить? Не выйдет!",
				"Слова твои не стоят и пенни! Ни к чему мне с тобой дела иметь!"
			),
			RandPhraseSimple(
				"Сомнительное предложение. Я вынужден"+ GetSexPhrase("","а") +" отказаться.",
				"Приятно было познакомиться, капитан " + GetFullName(NPChar) + ". Прощайте."
			)
		);
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Рому мне! А ты убирайся с глаз моих!",
				"Мы уже все обсудили, не так ли?"
			),
			RandPhraseSimple(
				"Идите своей дорогой, я занят" + NPCharSexPhrase(NPChar, "", "а") + ".",
				"Полагаю, у нас с вами нет общих тем."
			)
		);
		link.l1 = RandSwear();
		link.l1.go = "Exit_2";

		SaveCurrentQuestDateParam("QuestTalk");
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "Я же сказал" + NPCharSexPhrase(NPChar, "", "а") + ", что жду тебя на корабле!";
		link.l1 = "А... конечно...";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader(PGGQuestID);
		if (isPGGInitiative) {
			AddQuestRecord(PGGQuestID, "q1_Tavern");
		} else {
			AddQuestRecord(PGGQuestID, "q1_Tavern_1");
			AddQuestUserData(PGGQuestID, "sSex", GetSexPhrase("","а"));
		}
		AddQuestUserData(PGGQuestID, "sShipName", NPChar.Ship.Name);
		AddQuestUserData(PGGQuestID, "sPGGName", GetFullName(NPChar));

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") 	LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 20);

		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";

		if (GetCharacterShipClass(PChar) > 4) // класс не подходит
		{
			PCharShipClassIsLowDialog(link, NPChar);

			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}

		if (GetCompanionQuantity(PChar) >= COMPANION_MAX) // компаньонов максимальное количество
		{
			MaxCompanionsExceededDialog(link, NPChar);

			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}

		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (isSetSail) {
			GeneratePGGQuestLocation(NPChar)

			Dialog.Text = "Удачное время вы выбрали, чтобы ступить ко мне на палубу, капитан! " + 
			"У меня есть для вас выгодное предложение – взять немного бесхозного добра.";
		} else {
			Dialog.Text = RandPhraseSimple(
				"Добро пожаловать на борт, капитан!",
				"Ну, вот и славно, теперь я уверен" + NPCharSexPhrase(NPChar, "", "а") + " - лишних ушей нет, мои матросы уже в курсе."
			) + " Предложение такое – взять немного бесхозного добра.";
		}
		link.l1 = RandPhraseSimple(
			"А что тут сложного? И почему ты делишься этим со мной" + NPCharSexPhrase(NPChar, "", ", милочка") + "?",
			"Бесхозного? " + NPCharSexPhrase(NPChar, "Да ты, приятель, шутишь", "Да ты шутишь, милая") + "!"
		);
		link.l1.go = "Quest_1_Ship_1";

		break;

	case "Quest_1_Ship_1":
		Dialog.Text = RandPhraseSimple(
			"Ну, есть люди, которые считают его своим, а нужно убедить их в обратном.",
			"Ну конечно, придётся кое-кого убить. Но ведь за этим дело не станет?!"
		);
		link.l1 = PCharRepPhrase(RandSwear() + 
			RandPhraseSimple(
				"Ближе к делу!",
				"Это уже пахнет хорошей резнёй! Где они?"
			),
			RandPhraseSimple(
				"Хотелось бы узнать подробности вашего предложения.",
				"Что конкретно вы хотите мне предложить?"
			)
		);
		link.l1.go = "Quest_1_Ship_Detail";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple(
				"Что-то ты темнишь. Не хочу я с тобой в это ввязываться!",
				"Выглядит просто, да я тебе не верю! Хочешь чужими руками жар загребать? Я не соглас"+ GetSexPhrase("ен","на") +"!"
			),
			RandPhraseSimple(
				"Предложение заманчивое, но вынужден"+ GetSexPhrase("","а") +" отказаться.",
				"Нет, чужое я с детства не беру, предпочитаю, что бы дарили. Я пас."
			)
		);
		link.l2.go = "Quest_1_Ship_Refuse";
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "Караван, принадлежащий " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", перевозящий ";
		PChar.GenQuest.PGG_Quest.Goods.Text = GetStrSmallRegister(XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name + "Acc"));
		sTmp += PChar.GenQuest.PGG_Quest.Goods.Text;

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetConvertStr(PChar.GenQuest.PGG_Quest.Island, "LocLables.txt");
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}

		if (sti(PChar.GenQuest.PGG_Quest.Template))
		{
			sTmp +=	", будет проходить около острова " + sLoc + " у бухты " + GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + ", им пришлось отклониться от привычного маршрута.";
		}
		else
		{
			sTmp += ", попал в шторм недалеко от " + sLoc + " и пошёл на дно. Но они успели спасти часть груза и высадились в " + 
				GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt") + " Сейчас они ждут прихода своей эскадры.";
		}

		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear() + 
			RandPhraseSimple(
				"Не тяни, выкладывай все поживее!",
				"Я в тебе не ошиб"+ GetSexPhrase("ся","лась") +", что ты ещё знаешь?"
			),
			RandPhraseSimple(
				"Очень интересно, продолжайте!",
				"Я в"+ GetSexPhrase("есь","ся") +" внимание!"
			)
		);
		link.l1.go = "Quest_1_Ship_Detail_1";

		link.l2 = PCharRepPhrase(
			RandPhraseSimple(
				"Дельце неплохое, но откажусь. Не резон мне с " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + " ссорится.",
				"Караван? Бесхозное? Да там тысяча солдат при нем! Не годится. Я ухожу."
			),
			RandPhraseSimple(
				"Нет, с " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + " я не воюю, не интересно.",
				"Мой ответ – нет! Я не собираюсь портить отношения с " + NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation)) + "!"
			)
		);
		link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");

		if (sti(PChar.GenQuest.PGG_Quest.Template))
		{
			AddQuestRecord(PGGQuestID, "q1_Detail_A");
		}
		else
		{
			AddQuestRecord(PGGQuestID, "q1_Detail_B");
		}
		AddQuestUserData(PGGQuestID, "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData(PGGQuestID, "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData(PGGQuestID, "sColony", sLoc);
		AddQuestUserData(PGGQuestID, "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

	case "Quest_1_Ship_Detail_1":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Через " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " караван уйдёт и нам их уже не догнать.",
				"У нас есть ровно " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " дней, чтобы успеть их вырезать и забрать добычу!"
			),
			RandPhraseSimple(
				"В нашем распоряжении " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + " дней на всю операцию.",
				"Нам стоит поторопиться, " + PChar.Name + ". У нас в запасе всего " + FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)) + "."
			)
		);
		link.l1 = RandPhraseSimple(
			"Мы успеем! Отплываем сегодня же.", 
				"Мы успеем! Отплываем сегодня же.", 
			"Мы успеем! Отплываем сегодня же.", 
			"Не будем медлить. Прикажите отплывать сегодня же."
		);
		link.l1.go = "Exit_Quest_1_Accept";

		AddQuestRecord(PGGQuestID, "q1_Accept");
		AddQuestUserData(PGGQuestID, "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));

		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "Не будем медлить! В путь!";
		link.l1 = "В путь!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		ReOpenQuestHeader(PGGQuestID);

		PGG_Disband_Fleet(NPChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1AcceptedQuestDeleteFantom("");
			Map_ReleaseQuestEncounter(NPChar.id);
			group_DeleteGroup(NPChar.id+"_Group");
			if (sti(PChar.GenQuest.PGG_Quest.Template))
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.CompanionEnemyEnable = true;
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);

			SetBaseShipData(NPChar);
			DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");

			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear() + "Вы меня разочаровали, капитан. А вы думали, что я вас приглашу на "+ RandPhraseSimple("воскресную мессу?!!", "детский утренник!??"));
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Это твоё дело" + NPCharSexPhrase(NPChar, "", ", дорогуша") + ". А решать моё.",
				"Я не хочу сушиться на солнце из-за пары пиастров."
			),
			RandPhraseSimple(
				"Моё решение окончательное, капитан.",
				"Нам не о чем больше говорить."
			)
		);
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord(PGGQuestID, "q1_Close");
			AddQuestUserData(PGGQuestID, "sSex", GetSexPhrase("ся","ась"));
			CloseQuestHeader(PGGQuestID);
			
			DeleteAttribute(NPChar, "AlwaysFriend");
			SaveCurrentQuestDateParam("QuestTalk");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Да брось, все пройдёт как по маслу и никто не узнает. Мы всех зарежем.",
				"Узнал"+ GetSexPhrase("","а") +" все и сам"+ GetSexPhrase("","а") +" хочешь дельце провернуть? Не выйдет!"
			),
			RandPhraseSimple(
				"Куда это вы заторопились, капитан? Уж не к властям ли?",
				"Весьма неумно влезть в логово тигра и думать, что сможешь запросто выбраться оттуда."
			)
		);
		link.l1 = PCharRepPhrase(RandSwear() + 
			RandPhraseSimple(
				"Убирайся к морскому дьяволу! Я капитан " + GetFullName(PChar) + " и ты мне не указ! Я ухожу!",
				"Клянусь дьяволом, ты меня выводишь из себя!"
			),
			RandPhraseSimple(
				"Ваше предложение мне неинтересно, и говорить нам более не о чем. Прощайте.",
				"Полагаю, нам не о чем более говорить. Меня ждут дела."
			)
		);
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear() + PCharRepPhrase(
			RandPhraseSimple(
				"Схватить е"+ GetSexPhrase("го","ё") +"! Привяжите е"+ GetSexPhrase("го","ё") +" к пушке! Посмотрим, какого цвета у не"+ GetSexPhrase("го","ё") +" кишки!!!",
				"Эй, Джонни! Хендерсон! Хватайте мерзав"+ GetSexPhrase("ца","ку") +"! Не пускайте е"+ GetSexPhrase("го","ё") +" к шлюпке!!!"
			),
			RandPhraseSimple(
				"Жаль, капитан! Надеюсь, в нашем трюме тебе будет уютно. Ну, а потом решим, что с тобой делать.",
				"Белые рабы долго не живут, капитан, так что решайте: или Хендс прострелит вам голову из мушкета, или вы остаток жизни проведёте в каменоломнях."
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Я заставлю тебя жрать твои поганые внутренности, " + GetFullName(NPChar) + "!!!",
				"А ну прочь с дороги! Мерзавцы! Раскрою башку, как гнилую тыкву!"
			),
			RandPhraseSimple(
				"Ваше предложение неприемлемо... И весьма неблагоразумно!!!",
				"А вы не очень гостеприимны... С дороги!!!"
			)
		);
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
		GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);

		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);

		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(PChar, "questTemp.PGGContra.Know")) sTmp = "PGGTmp";
		else sTmp = "PGGQst";
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(PChar, true);
		break;

	case "Quest_1_Time2Late":
		DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)],"DisableEncounters");
		chrDisableReloadToLocation = false;
		SaveCurrentQuestDateParam("QuestTalk");

		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Гром и молния! Мы опоздали! А всё из-за вас, ленивые олухи! Нечего нам с тобой теперь делить, " + GetFullName(PChar) + ". Поднять стаксель! Травить марс помалу! ",
				"Так, " + GetFullName(PChar) + ", что-то зря я с тобой связал" + NPCharSexPhrase(NPChar, "ся", "ась") + ", добыча утекла сквозь пальцы как вода. Прощай!"
			),
			RandPhraseSimple(
				"Они исчезли! Виной всему ваша нерасторопность! Нам с вами не по пути " + GetFullName(PChar) + ".",
				"Караван мы не догоним, можно сушить весла. Зря я с вами связал" + NPCharSexPhrase(NPChar, "ся", "ась") + "! Прощайте."
			)
		)
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Да и чёрт с этим караваном! Ловцы жемчуга ничуть не хуже, а риска никакого!",
				"Удача с нами, ещё не вечер! Море изобилует жалкими торгашами, ждущими, пока мы отнимем их денежки!"
			),
			RandPhraseSimple(
				"Действительно, жаль, что такая блестящая операция закончилась полным фиаско! Прощайте!",
				"Человек предполагает, а бог располагает... Прощайте!"
			)
		);
		link.l1.go = "Exit_Quest_1_2Late";

		AddQuestRecord(PGGQuestID, "q1_Time2Late");
		CloseQuestHeader(PGGQuestID);
		break;

	case "Exit_Quest_1_2Late":
		LAi_SetPlayerType(PChar);
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(PChar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck") PChar.quest.Munity = "Deads";
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;
		SaveCurrentQuestDateParam("QuestTalk");

		//не взяли груз...
		PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Кровожадн"+ GetSexPhrase("ый ублюдок","ая дрянь") +"! Всё ушло на дно к морскому дьяволу! " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " пиастров на бочку, и я видеть тебя больше не желаю!",
				"Ты себя адмиралом Нельсоном вообразил"+ GetSexPhrase("","а") +"? Потопил"+ GetSexPhrase("","а") +" всю добычу, "+ GetSexPhrase("идиот","дура") +"! Отсыпь мне " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " пиастров и проваливай!"
			),
			RandPhraseSimple(
				"Вы здесь войну решили устроить! Это совершенно никуда не годится! Полагаю, мы всё забудем, если вы уплатите нам " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " пиастров ",
				"Ваши методы недопустимы в такого рода делах! Вы провалили всё дело! Немедленно уплатите нашу долю в размере " + FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + " пиастров и отправляйтесь на все четыре стороны! "
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Если бы не я, ты бы сейчас крабов кормил" + NPCharSexPhrase(NPChar, "", "а") + NPCharSexPhrase(NPChar, ", жадная образина!", ", обезьяна корявая!"),
				"Лучше было позволить флагману взять на абордаж твоё корыто, тогда бы ты уже болтал" + NPCharSexPhrase(NPChar, "ся", "ась") + " на рее и не отравлял" + NPCharSexPhrase(NPChar, "", "а") + " воздух! "
			),
			RandPhraseSimple(
				"Ваши требования неуместны, а намёки оскорбительны!",
				"Договора о неустойке не было, стало быть, и платить я не буду!"
			)
		);
		link.l1.go = "Quest_1_NotPay";

		if (sti(PChar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
		{
			link.l2 = PCharRepPhrase(
				RandPhraseSimple(
					"Я не могу тебе дать сейчас бой, и ты это знаешь! Подавись своими пиастрами! Вот!",
					"Пиастры!!! Что же, фортуна сейчас не на моей стороне. Я соглас"+ GetSexPhrase("ен","на") +"."
				),
				RandPhraseSimple(
					"Ваши требования возмутительны, но выбора у меня, похоже, нет.",
					"Ваши аппетиты чрезмерны, но я вынужден"+ GetSexPhrase("","а") +" согласиться!"
				)
			);
			link.l2.go = "Exit_Quest_1_Failed";
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) <= MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3)) {
			AddQuestRecord(PGGQuestID, "q1_Fail");
			break;
		}

		PChar.GenQuest.PGG_Quest.Ok = 1;
		Dialog.Text = PCharRepPhrase(
			"Жаркое дельце! Добыча составила " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".",
			"Отлично сработали, капитан! Добыча составила " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "."
		);
		DeleteAttribute(PChar, "PGGShoreQuest");
		int greedyPGG = 0;
		string greed = "";
		if (GetCharacterShipClass(NPChar) > GetCharacterShipClass(PChar))
		{
			PChar.GenQuest.PGG_Quest.Parts = (GetCharacterShipClass(NPChar) - GetCharacterShipClass(PChar));
			i = sti(PChar.GenQuest.PGG_Quest.Parts)+2-greedyPGG;
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
		}
		else
		{
			if (makeint(NPChar.reputation) < 40 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && drand(200) > sti(GetSummonSkillFromName(PChar, SKILL_LEADERSHIP)))
			{
				greedyPGG = 2;
				greed = " И не советую тебе рыпаться.";
				NPChar.Greed = true;
			}
			PChar.GenQuest.PGG_Quest.Parts = (GetCharacterShipClass(PChar) - GetCharacterShipClass(NPChar));
			i = sti(PChar.GenQuest.PGG_Quest.Parts)+2+greedyPGG;
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken)) - MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
		}

		Dialog.Text = Dialog.Text + PCharRepPhrase(" Моя доля ", " Доля, приходящаяся на моё судно - ") + PChar.GenQuest.PGG_Quest.Goods.Part + "."+greed;
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Справедливо! Уже грузят шлюпки!", 
				"Да, всё точно... Уговор дороже денег."
			),
			RandPhraseSimple(
				"Ваши расчёты правильны. Я соглас"+ GetSexPhrase("ен","на") +".", 
				"В дележе вы безупречны."
			)
		);
		link.l1.go = "Exit_Quest_1_End";

		if (!CheckAttribute(NPChar, "Greed")) {
			link.l2 = PCharRepPhrase(
				RandPhraseSimple(
					"И ты ещё требуешь свою долю? Да тебя надо вздёрнуть на рее и не мешкать!",
					"Долю? Здесь каждый сам за себя, и если тебе ничего не досталось, то это твои проблемы!"
				),
				RandPhraseSimple(
					"Не думаю, что вы на что-то можете рассчитывать.",
					"Мой ответ – нет! Я не собираюсь делиться с " + NPCharSexPhrase(NPChar, "разными проходимцами", "разным отребьем") + "!"
				)
			);
		} else {
			link.l2 = "Ты что, надуть меня хочешь? В таком случае я забираю себе всё!";
		}
		link.l2.go = "Quest_1_NotPay";
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(
			RandPhraseSimple(
				"Нет, так нет! Спорить не буду! Прощай!",
				"Не будем проливать кровь и усугублять неудачу! В другой раз повезёт больше!"
			),
			RandPhraseSimple(
				"Что же, прощайте, капитан, я не в том положении, чтобы настаивать...",
				"Повреждения моего корабля и потери не позволяют мне настаивать на справедливом решении вопроса. Оставлю это на вашей совести, капитан!"
			)
		);
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Попутного ветра!", 
				"Семь футов под килем!"
			),
			RandPhraseSimple(
				"Прощайте! Полагаю, свежий морской воздух пойдёт вам на пользу!",
				"Надеюсь, что ваши неудачи не сделают ваш характер ещё более несносным, прощайте!"
			)
		);
		link.l1.go = "Exit_Quest_1_Failed";

		PChar.GenQuest.PGG_Quest.Stage = -1;

		if (!CheckAttribute(NPChar, "Greed"))	ChangeCharacterReputation(PChar,-20);
		else	NPChar.PGG_Hunter = true;
		DeleteAttribute(NPChar, "Greed");

		bOk = makeint(NPChar.reputation) < 40 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(
				RandPhraseSimple(
					"Ты не понял"+ GetSexPhrase("","а") +"! Этим ты мог"+ GetSexPhrase("","ла") +" бы купить себе жизнь! Схватить "+ GetSexPhrase("ублюдка","мерзавку") +"!",
					"Ты, наверное, думаешь, что с тобой шутят? Пропустим тебя под килем, и сразу станешь сговорчивей!"
				),
				RandPhraseSimple(
					"Придётся подсократить вашу жизнь, капитан! Не хотите по-хорошему, познакомитесь со святым Мартином!",
					"Вы не оставляете мне выбора, " + GetFullName(PChar) + "! Я возьму своё, хотите вы того или нет!"
				)
			);
			link.l1 = PCharRepPhrase(
				RandPhraseSimple(
					"Клянусь дьяволом, ты за это заплатишь!!!",
					"Йхо-хо! Иди и возьми меня, капитана " + GetFullName(PChar) + "! "
				),
				RandPhraseSimple(
					"Разрез будет глубокий и длинный! ",
					"Вы хотите сразу умереть или немного помучиться?"
				)
			);
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord(PGGQuestID, "q1_FailPay");
			AddQuestUserData(PGGQuestID, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(PGGQuestID, "sSex1", GetSexPhrase("ен","на"));
		}
		ChangeCharacterReputation(NPChar, 10);
		CloseQuestHeader(PGGQuestID);
		RemoveCharacterCompanion(PChar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -10);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "Не хочу больше иметь с тобой дел!";
		link.l1 = "Да и не нужно.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "Сегодня мы отчаливаем в " + XI_ConvertString("Colony"+NPChar.PGGAi.location.town) + " пропивать добычу! Если хочешь, присоединяйся! В любом случае, приятно иметь с тобой дело! Удачи.";
		link.l1 = "И тебе.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(PChar, NPChar);

		ChangeCharacterReputation(NPChar, -5);
		LAi_LockFightMode(PChar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");

		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		if (PChar.location != "Ship_Deck") sTmp = "sea";
		NPChar.location = PChar.location;

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(PChar, true);
		break;

	case "Exit_Quest_1_End":
		DeleteAttribute(NPChar, "Greed");
		RemoveCharacterCompanion(PChar, NPChar);
		ChangeCharacterReputation(PChar, 5);
		PGG_ChangeRelation2MainCharacter(NPChar, 30);
		NPChar.PGGAi.location.town = PGG_FindRandomTownByNation(sti(NPChar.nation));
		NPChar.PGGAfterShare = true;
		NPChar.PGGAi.AfterSail.TaskCounter = 0;
		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
		PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
		PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		AddQuestRecord(PGGQuestID, "q1_OkShare");
		CloseQuestHeader(PGGQuestID);

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		SaveCurrentQuestDateParam("QuestTalk");
		Dialog.Text = PCharRepPhrase(
			NPCharSexPhrase(NPChar, "Настоящее побоище, жаль, девок с ними не было", "Настоящая бойня, книпель мне в зад!, жаль, кончилось быстро") + "! Добыча составила " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + ".", 
			"Неплохо, капитан! Добыча составила " + PChar.GenQuest.PGG_Quest.Goods.Taken + " " + PChar.GenQuest.PGG_Quest.Goods.Text + "."
		);

		PChar.PGGShoreQuest = true;
		PChar.GenQuest.PGG_Quest.Parts = 2;
		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
    SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		
		Dialog.Text = Dialog.Text + " Моя доля " + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
		link.l1 = PCharRepPhrase(
			RandPhraseSimple(
				"Справедливо, разрази меня гром!", 
				"Да, всё точно, разрази меня гром!"
			),
			RandPhraseSimple(
				"Ваши расчёты правильны. Я соглас"+ GetSexPhrase("ен","на") +".", 
				"В дележе вы безупречны."
			)
		);
		link.l1.go = "Exit_Quest_1_End";

		break;
//===================================
//              Exits
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Exit_PIRATES":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetPlayerType(PChar);
		break;

	case "Exit_2":
		if (CheckAttribute(PChar, "GenQuest.PGG_Quest")) DeleteAttribute(PChar, "GenQuest.PGG_Quest");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		NPChar.willDie = true;
		CloseQuestHeader("Gen_StrangeInfo");
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(PChar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}

void ContrabandDialog(aref link) {
	Dialog.text = "Слушай, проваливай отсюда! Сорвёшь " + GetSexPhrase("сделку, и я вырву тебе сердце!", "мне дело, и я тебе зенки поганые выдавлю!");
	link.l1 = RandPhraseSimple("Ты смеешь мне угрожать, " + GetSexPhrase("собака", "тварь") + "?", GetSexPhrase("Ты подавишься своими словами, каналья!", "Да я тебя сейчас на ремни нарежу, сука!"));
	link.l1.go = "Exit_Smugglers_Fight";
	link.l2 = "Да ладно, я знаю, что такое бизнес. До встречи.";
	link.l2.go = "Exit";
}

void MaxCompanionsExceededDialog(aref link, ref NPChar) {
	Dialog.Text = RandPhraseSimple("Похоже, тебе уже достаточно компаньонов.", "У тебя и так много кораблей. Зачем тебе ещё один?");
	link.l1 = "Да... Может ты и прав" + NPCharSexPhrase(NPChar, "", "а") + ".";
	link.l1.go = "exit";
}

void NotEnoughMoneyDialog(aref link, ref NPChar) {
	Dialog.Text = RandSwear() + "Это была шутка? У тебя же в карманах ветер свищет!"
	link.l1 = "И правда... Пойду я.";
	link.l1.go = "exit";
}

void PGGNoShipDialog(aref link, ref NPChar) {
	Dialog.Text = "Да я вот без корабля остал" + NPCharSexPhrase(NPChar, "ся", "ась") + ".";
	link.l1 = RandSwear() + "Тогда позже поговорим, как корабль достанешь.";
	link.l1.go = "exit";
}

void PCharNoShipDialog(aref link, ref NPChar) {
	Dialog.Text = "А ты мне на что? Кораблик достань для начала, потом поговорим!";
	link.l1 = RandSwear() + "Ну и не нужно!";
	link.l1.go = "exit";
}

void PCharShipClassIsLowDialog(aref link, ref NPChar) {
	Dialog.Text = "Дело с тобой!?? Достойный корабль сначала найди! Ну твоей скорлупке только почту возить...";
	link.l1 = RandSwear() + "Ну и не нужно!";
	link.l1.go = "exit";
}

void PCharRankLowDialog(aref link, ref NPChar) {
	Dialog.Text = "Дело с тобой!?? Опыта наберись сначала!";
	link.l1 = RandSwear() + "Ну и не нужно!";
	link.l1.go = "exit";
}

void PGGQuestNotEnoughtTimePassedDialog(aref link, ref NPChar) {
	Dialog.Text = NPCharRepPhrase(NPChar, 
		"Никаких дел сегодня, проваливай.", 
		"Извини, ничего не могу предложить."
	);
	link.l1 = PCharRepPhrase(RandSwear(), "Что ж, до встречи.");
	link.l1.go = "exit";
}

void PGGQuestAlreadyActive(aref link, ref NPChar) {
	int currQuestPGGid = GetCharacterIndex(PChar.GenQuest.PGG_Quest.PGGid);
	if (currQuestPGGid < 0 || currQuestPGGid > TOTAL_CHARACTERS) {
		Dialog.Text = "Если видите это, то отпишите в баги, стоит метка, что ПП уже взято, однако айди ПГГ '"+ PChar.GenQuest.PGG_Quest.PGGid +"' не нашли.";
		link.l1 = "Мда, навасянили...";
		link.l1.go = "exit";
	}

	ref currQuestPGG = &characters[currQuestPGGid];
	Dialog.Text = "А я вам на что, интересно? Приходи, как закончишь все дела с кэпом по имени " + GetFullName(currQuestPGG) + "!";
	link.l1 = "Действительно, что-то я подзабыл" + GetSexPhrase("", "а") + ".";
	link.l1.go = "exit";
}

void GeneratePGGQuestLocation(ref NPChar) {
	PChar.GenQuest.PGG_Quest.Template = drand(1);
	if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
	{
		PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
	}
	PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
	PChar.GenQuest.PGG_Quest.Nation = rand(3);

	// генерим остров и пляж, пока не найдем пустой(без квеста)
	PChar.GenQuest.PGG_Quest.Island.Shore = "";
	while(PChar.GenQuest.PGG_Quest.Island.Shore == "" || 
		PChar.GenQuest.PGG_Quest.Island == "Pearl" || 
        PChar.GenQuest.PGG_Quest.Island == "Panama" ||		
		PChar.GenQuest.PGG_Quest.Island == "KhaelRoa" ||
		PChar.GenQuest.PGG_Quest.Island == "Reefs")
	{
		if (sti(PChar.GenQuest.PGG_Quest.Template)) {
			PChar.GenQuest.PGG_Quest.Island = GetRandomUninhabitatIsland();
			if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) {
				PChar.GenQuest.PGG_Quest.Island.Shore = "";
				continue;
			}
		} else {
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandId();
		}

		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
	}
	
	PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);

	if (isSetSail) PChar.GenQuest.PGG_Quest.Days = rand(4) + 5;
	else PChar.GenQuest.PGG_Quest.Days = GetMaxDaysFromIsland2Island(GetCharacterCurrentIslandId(PChar), PChar.GenQuest.PGG_Quest.Island) + 1;
	
	if(CheckAttribute(PChar, "BSStart") && !CheckAttribute(PChar, "BSInProgress"))	PChar.GenQuest.PGG_Quest.Goods = GOOD_GOLD;
	else PChar.GenQuest.PGG_Quest.Goods = GOOD_SLAVES + drand(2);
	
	PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;
	NPChar.Nation.Bak = NPChar.Nation;
}