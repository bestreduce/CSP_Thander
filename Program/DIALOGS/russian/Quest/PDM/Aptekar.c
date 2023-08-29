
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int Bonus = sti(pchar.rank);
	if (Bonus <= 6) Bonus = 1;
	if (Bonus >= 7 && Bonus <= 12) Bonus = 1.2;
	if (Bonus >= 13) Bonus = 1.5;
	int Plata1 = 3000 + 200 * sti(pchar.rank) * Bonus;
	int Plata2 = 15000 + 500 * sti(pchar.rank) * Bonus;
	pchar.PDM_Apt_Plata1.Money = 3000 + 200 * sti(pchar.rank) * Bonus;
	pchar.PDM_Apt_Plata2.Money = 15000 + 500 * sti(pchar.rank) * Bonus;

	int i, iOfficer;
	string attrL, offtype;
	ref chref;

	attrL = Dialog.CurrentNode;

	if(HasSubStr(attrL, "OfficerConfusedSel_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.OfficerToHealConfuse = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "OfficerConfused";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":							//Автор Sinistra
			dialog.text = "Приветствую вас, я доктор алхимии и медицины. Моё имя Алюмнус. А как зовут вас, "+ GetSexPhrase("молодой человек","девушка") +"?";
			link.l1 = "Можете звать меня "+pchar.name+".";
			link.l1.go = "Alumnus_PervoeZadanie_1";
		break;
		
		case "Alumnus_PervoeZadanie_1":
			dialog.text = "Как хорошо, что вы зашли, "+pchar.name+"! Послушайте, не могли бы вы мне оказать небольшую помощь, а то сам я отлучиться надолго не могу...";
			link.l1 = "А что нужно делать?";
			link.l1.go = "Alumnus_PervoeZadanie_2";
		break;
		
		case "Alumnus_PervoeZadanie_2":
			dialog.text = "Здесь в Мариго лежит один из моих пациентов, его зовут Будевин. Вам нужно отнести ему лекарство, и он вам сам заплатит за доставку.";
			link.l1 = "Вроде бы ничего сложного. Я отнесу ему лекарство.";
			link.l1.go = "Alumnus_PervoeZadanie_3";
			link.l2 = "Доктор Алюмнус, наймите себе курьера, а у меня есть более серьёзные дела.";
			link.l2.go = "Alumnus_PervoeZadanie_Net";
		break;
		
		case "Alumnus_PervoeZadanie_3":
			dialog.text = "О, я знал, что вы не откажете, "+pchar.name+", спасибо! Чтобы найти его дом, вам нужно подняться вверх по горе, он стоит рядом с выходом в джунгли.\nВот, держите лекарство. Заходите ко мне ещё, у меня найдётся для вас работа.";
			link.l1 = "Зайду обязательно. До свидания!";
			link.l1.go = "Alumnus_PervoeZadanie_4";
			NextDiag.TempNode = "Alumnus_PervoeZadanie_3_EsheRaz";
		break;
		
		case "Alumnus_PervoeZadanie_3_EsheRaz":
			dialog.text = "Вы отнесли лекарство Будевину?";
			link.l1 = "Ещё нет, но я скоро буду у него.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_PervoeZadanie_3_EsheRaz";
		break;
		
		case "Alumnus_PervoeZadanie_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetQuestHeader("PDM_Aptekar");
			AddQuestRecord("PDM_Aptekar", "1");
			GiveItem2Character(PChar, "PDM_Heal_Poroshok");
			
			sld = GetCharacter(NPC_GenerateCharacter("PDM_Markus", "prison_3", "man", "man", 10, HOLLAND, -1, false));
			sld.name	= "Будевин";
			sld.lastname	= "";
			sld.Dialog.Filename = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Markus_1";
			LAi_SetGroundSitType(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld,"Smallhome_K2","quest","quest1");
		break;
		
		case "Alumnus_PervoeZadanie_Net":
			dialog.text = "Очень жаль, "+pchar.name+". Сейчас я кое-чем занят, поэтому не могу вас осмотреть.";
			link.l1 = "Ну что же, тогда я пойду.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Obijen";
		break;
		
		case "Alumnus_Obijen":
			dialog.text = "Здравствуйте, "+pchar.name+", чем я могу быть вам полезен?";
			link.l1 = "Да так, мимо проходил"+GetSexPhrase("","а")+".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Obijen";
		break;
		
		case "Markus_1":
			dialog.text = "(кашляет)... Да, что вы хотели?";
			link.l1 = "Я от доктора Алюмнуса, он просил передать вам это лекарство.";
			link.l1.go = "Markus_2";
			locCameraFromToPos(1.00, 2.00, 0.00, false, -4.00, -1.20, -4.00);
		break;
		
		case "Markus_2":
			dialog.text = "О, "+GetAddress_Form(NPChar)+", как же вы вовремя, эта боль невыносима... Этой ночью на меня напали какие-то бандиты. Забрали у меня всё ценное, но слава богу, живой я остался. Стража всё ещё их ищет, но надеюсь, негодяи получат по заслугам.";
			link.l1 = "Да, неприятная ситуация с вами приключилась. Доктор Алюмнус говорил, что вы заплатите за доставку.";
			link.l1.go = "Markus_3";
			TakeItemFromCharacter(pchar, "PDM_Heal_Poroshok");
		break;
		
		case "Markus_3":
			dialog.text = "Ах да, конечно. Держите, "+Plata1+" пиастров ваши. Сейчас бы мне поспать...";
			link.l1 = "Выздоравливайте, минхер, а теперь я покину вас.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Plata1));
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("PDM_Aptekar", "2");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("ёс","есла"));
			AddQuestUserData("PDM_Aptekar", "sSex2", GetSexPhrase("","а"));
			
			sld = CharacterFromID("Doktor_Alumnus");
			sld.dialog.filename   = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_VtoroeZadanie";
		break;

		case "Alumnus_VtoroeZadanie":
			dialog.text = "А-а, это вы, "+ GetSexPhrase("мой юный и нетерпеливый капитан","моя юная и нетерпеливая знакомая") +"! Что вам угодно от меня?";
			link.l1 = "Захотел"+GetSexPhrase("","а")+" проведать вас и узнать, не требуется ли вам какая-то помощь?";
			link.l1.go = "Alumnus_VtoroeZadanie_2";
		break;

		case "Alumnus_VtoroeZadanie_2":
			dialog.text = "Да, действительно, мне сейчас нужна помощь. Мне необходимо небольшое количество одной редкой травы, что произрастает на карибских островах. Без неё я не могу готовить свои чудодейственные целебные отвары. Если бы вы достали для меня эту траву, я бы мог лечить вас и ваших офицеров от любых ранений и болезней. Однажды я приобрёл немного этой травы у одного индейца... Как же его звали? Ах да, у Туантуха.";
			link.l1 = "Расскажите мне об этом Туантухе.";
			link.l1.go = "Alumnus_VtoroeZadanie_3";
		break;

		case "Alumnus_VtoroeZadanie_3":
			dialog.text = "Он довольно странный... Даже его соплеменники сторонятся его. На своей лодочке он плавает от одного острова к другому, собирая разные редкие травы и снадобья, и потом продаёт их докторам, аптекарям и повивальным бабкам. Но мне кажется, что он умный человек, несмотря на его привычки - он дал мне пару очень полезных советов насчёт местных болезней и психологии индейцев. Он живёт обособленно от людей, и в последний раз его видели где-то на Багамах. Так как у него есть лодка, то живёт он рядом с морем, на скалах.";
			link.l1 = "Я привезу вам эту травку. А как она называется?";
			link.l1.go = "Alumnus_VtoroeZadanie_4";
		break;

		case "Alumnus_VtoroeZadanie_4":
			dialog.text = "А-а. Вот здесь небольшая проблема. Я не могу в точности припомнить её название. Я уверен, что Туантух называл мне эту траву при продаже, но я просто забыл название, оно звучит крайне странно для слуха европейца, знаете ли.";
			link.l1 = "И как же я долж"+ GetSexPhrase("ен","на") +" искать эту траву, когда не знаю, как она называется?";
			link.l1.go = "Alumnus_VtoroeZadanie_5";
		break;

		case "Alumnus_VtoroeZadanie_5":
			dialog.text = "Ну, я скажу вам, как опознать эту траву. Её запах напоминает одновременно запахи корицы и аниса. Достаточно пахучая смесь, надо сказать. Я думаю, что это происходит из-за влияния Нептуна и Европы на процесс созревания этой травы. Гинденбург написал целый труд о влиянии внешних планет на созревание трав в период весеннего равноденствия. Впрочем, я отвлекаюсь.";
			link.l1 = "Да, вы отвлекаетесь. Спасибо за лекцию. Я постараюсь найти для вас эту траву. До встречи.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_VtoroeZadanie_6";

			sld = GetCharacter(NPC_GenerateCharacter("Pablo_Loco", "indsar1", "man", "man", 10, PIRATE, -1, false));
			sld.name = "Туантух";
			sld.lastname = "";
			sld.greeting = "GR_Pablo_Loco";
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetStayType(sld);
			sld.dialog.filename   = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Pablo_Loco_FT";
			ChangeCharacterAddressGroup(sld,"Shore68","quest","quest18");

			AddQuestRecord("PDM_Aptekar", "3");
			AddQuestUserData("PDM_Aptekar", "sSex", GetSexPhrase("","а"));
		break;

		case "Alumnus_VtoroeZadanie_6":
			dialog.text = "Добро пожаловать назад! Удалось ли вам найти необходимое мне растение?";
			link.l1 = "Ещё нет, доктор. Продолжаю поиски.";
			link.l1.go = "exit";
			link.l2 = "Доктор, напомните мне, как опознать эту траву.";
			link.l2.go = "Alumnus_Novoe_Kak_Opoznat";
			NextDiag.TempNode = "Alumnus_VtoroeZadanie_6";
		break;

		case "Alumnus_Novoe_Kak_Opoznat":
			dialog.text = "Запоминайте: эта редкая трава произрастает на карибских островах, её запах напоминает одновременно корицы и аниса. Я думаю, что это происходит из-за влияния Нептуна и Европы на процесс созревания этой травы. Гинденбург написал целый труд о влиянии внешних планет на созревание трав в период весеннего равноденствия...";
			link.l1 = "Ладно, доктор, этого достаточно, я побежал"+ GetSexPhrase("","а") +".";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_VtoroeZadanie_6";
		break;

		case "Pablo_Loco_FT":
			dialog.text = "А! Твоя желать золота, да? Твоя желать много золота. Слеп"+ GetSexPhrase("ой дурак","ая дура") +"! Неужели твоя не заботиться о состоянии своя душа?";
			link.l1 = "О чём ты говоришь? Кто ты?";
			link.l1.go = "Pablo_Loco_1";
			NextDiag.TempNode = "Pablo_Loco_ER_1";
		break;

		case "Pablo_Loco_ER_1":
			dialog.text = "Твоя выбросить свою жадность в море?";
			link.l1 = "О чём ты говоришь?";
			link.l1.go = "Pablo_Loco_ER_2";
		break;

		case "Pablo_Loco_ER_2":
			dialog.text = "Жадность делает твоё сердце тяжёлым, как само золото. Твоя долж"+ GetSexPhrase("ен","на") +" выбросить её в море, чтобы очиститься.";
			link.l1 = "Расскажи мне свою историю.";
			link.l1.go = "Pablo_Loco_2";
		break;

		case "Pablo_Loco_1":
			dialog.text = "Я Туантух. Тот, чьи уши тосковать по птичьему пению и голосам братьев, но слышать лишь вопли и крики. Тот, чей нос тосковать по благоуханию цветов и солёного моря, но чувствовать лишь горький чёрный порох.";
			link.l1 = "Ты, несомненно, несчастный человек. Расскажи мне свою историю.";
			link.l1.go = "Pablo_Loco_2";
			link.l2 = "Твой разум явно вышел погулять, а у меня везде есть неотложные дела. До свидания.";
			link.l2.go = "exit";
		break;

		case "Pablo_Loco_2":
			dialog.text = "Я жил в Иначетле. Я быть найден в лодке, дрейфующей в океане, малое дитя, живое среди множества мертвецов. Я вырос сильным. Я чувствовать дух этого острова, и я чувствовать дух моря. Мои братья рыбачили в море на маленьких лодках. Они черпали жизнь из моря. Но потом море приносить им смерть.";
			link.l1 = "Что ты имеешь в виду?";
			link.l1.go = "Pablo_Loco_3";
		break;

		case "Pablo_Loco_3":
			dialog.text = "Однажды мои братья увидели огромные корабли на море. Они никогда не видели таких больших кораблей, и они подумать, что это огромные крылатые птицы, посланные богами. Они направились к этим кораблям, крича и размахивая своими острогами в радостном приветствии. Но это не были корабли богов. Это были корабли белых людей. Бледнолицые испугаться моих братьев и подумать, что на них нападают. Так что они убили моих братьев, а потом пошли в мою деревню и убили всех, кто был там - всех, кроме меня, снова оставшегося живым среди мертвецов. Так что теперь я остался единственным, кто чувствовать дух острова и моря. Вот моя история.";
			link.l1 = "Я скорблю о твоей потере... Э-э, это ты Туантух, травник?";
			link.l1.go = "Pablo_Loco_Trava";
		break;

		case "Pablo_Loco_Trava":
			dialog.text = "Да, это я. Я могу чувствовать дух природы: зов моря, шёпот семян, смех цветов. Туантух: вот кто я такой.";
			link.l1 = "Действительно. 'Смех цветов', а? Это, э-э, очень всё интересно. Ну, Туантух, мне нужна трава, которая пахнет, как...";
			link.l1.go = "Pablo_Loco_5";
		break;

		case "Pablo_Loco_5":
			dialog.text = "Какой запах у этой травы?";
			Link.l1.edit = 1;
			Link.l1 = "";
			link.l1.go = "Pablo_Loco_Pravilno";
			NextDiag.TempNode = "Pablo_Loco_5";
		break;

		case "Pablo_Loco_Pravilno":
			string answer = GetStrSmallRegister(dialogEditStrings[1])
			if (HasSubStr(answer, "кориц") && HasSubStr(answer, "анис"))
			{
				Dialog.text = "Пахнет корицей и анисом? Я знать такую траву. Она может лечить, а может убить. Скажи мне, зачем тебе нужна эта трава?";
				Link.l1 = "Доктор Алюмнус послал меня за ней.";
				Link.l1.go = "Pablo_Loco_6";
				break;
			}
			else
			{
				Dialog.text = "Моя не знать травы с таким запахом.";
				{
					Link.l1 = "Щас ещё раз попробую.";
					Link.l1.go = "Pablo_Loco_5";
				}
				link.l2 = "Мне надо подумать.";
				link.l2.go = "exit";
			}
		break;

		case "Pablo_Loco_6":
			dialog.text = "Так, Алюмнус, ты сказал"+ GetSexPhrase("","а") +"? Моя знать этого человека - мудрый дурак. Это опасно, давать тзескатлат умтат в руки 'человека знания'. Но я знать, что он не будет использовать траву, чтобы намеренно убить другого - это не тот человек. Очень хорошо. Чтобы найти эту траву, мне нужен лодка, потому что моя должна плыть туда, где она расти. Травы не растут все в одном месте, белый человек.";
			link.l1 = "Я куплю её тебе.";
			link.l1.go = "Pablo_Loco_7";
		break;

		case "Pablo_Loco_7":
			dialog.text = "Нет, нет! Лодка нельзя 'покупать'! Золотая зараза испортить дух лодка! Ты должен построить лодка своими собственными руками и своим собственным сердцем, а не заражать её золотым ядом!";
			link.l1 = "Ты трудный человек, Туантух, ты знаешь об этом? Ну ладно: что я долж"+ GetSexPhrase("ен","на") +" сделать, чтобы помочь тебе построить лодку?";
			link.l1.go = "Pablo_Loco_8";
		break;

		case "Pablo_Loco_8":
			dialog.text = "Мне нужно особенное дерево. Это дерево называется Тешкатали. Если твоя хотеть, чтобы я достать для тебя твою траву, ты долж"+ GetSexPhrase("ен","на") +" доставить мне дерево Тешкатали. Оно растёт на континенте в джунглях, рядом с лагуной Каратаска.";
			link.l1 = "Дерево Тешкатали? Я понял"+ GetSexPhrase("","а") +" и не забуду. До свидания, Туантух. Я вернусь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_9";

			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition.l1 = "location";
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition.l1.location = "Shore10";
			PChar.quest.PDM_Apt_Prihov_v_buhtu.win_condition = "PDM_Apt_Prihov_v_buhtu";

			AddQuestRecord("PDM_Aptekar", "4");
		break;

		case "Pablo_Loco_9":
			dialog.text = "Зачем ты докучаешь мне? Единственное, что мне нужно от тебя, это дерево Тешкатали. Когда ты привезёшь его мне, я построю себе новая лодка. И тогда ты получишь тзескатлат умтат. Это всё, что я могу сказать.";
			link.l1 = "Я понял"+ GetSexPhrase("","а") +". До свидания.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_9";
		break;

		case "Nashel_Derevo":
			dialog.text = "Ты опять? Ты доставил"+ GetSexPhrase("","а") +" дерево Тешкатали?";
			link.l1 = "У меня есть дерево, которое тебе нужно. Вот оно. Теперь давай, строй свою лодку, чтобы ты мог привезти мне мою тзеска... тла.. ла... мумат... или как там называется эта чёртова травка.";
			link.l1.go = "Nashel_Derevo_2";
		break;

		case "Nashel_Derevo_2":
			TakeItemFromCharacter(pchar, "PDM_Derevo_Teshkali");
			dialog.text = "Приходи через неделю, в это время нужная тебе трава будет уже у меня.";
			link.l1 = "Давай я позову своих матросов, вместе с ними ты сделаешь лодку в пять раз быстрее.";
			link.l1.go = "Nashel_Derevo_3";
		break;

		case "Nashel_Derevo_3":
			dialog.text = "(смотрит на вас сердитым взглядом)";
			link.l1 = "Ладно, ладно, не буду мешать. Увидимся через неделю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_Stroit_lodku";

			SetTimerCondition("PDM_Apt_Lodka_Postroena", 0, 0, 7, false);

			AddQuestRecord("PDM_Aptekar", "7");
		break;

		case "Pablo_Loco_Stroit_lodku":
			dialog.text = "Лодка ещё не быть готова, приходи позже.";
			link.l1 = "Хорошо, Туантух, делай как умеешь.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pablo_Loco_Stroit_lodku";
		break;

		case "Pablo_Loco_Lodka_Postroena":
			dialog.text = "Белый человек, моя найти твоя трава.";
			link.l1 = "Моя благодарить, Туантух. Твоя не должна волноваться, эта трава не приносить смерть, а приносить пользу медицине. Моя прощаться с твоя.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;

			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 150);

			GiveItem2Character(PChar, "PDM_Trava_Tzes_Umrat");
			AddQuestRecord("PDM_Aptekar", "8");

			sld = CharacterFromID("Doktor_Alumnus");
			sld.dialog.filename   = "Quest\PDM\Aptekar.c";
			sld.dialog.currentnode   = "Alumnus_Finish_Zadanie";
		break;

		case "Alumnus_Finish_Zadanie":
			dialog.text = "Вы вернулись. Потрясающе. Вы принесли мне траву, что я у вас просил, "+ GetSexPhrase("мой юный капитан","мефрау") +"?";
			link.l1 = "Тзескатлат Умтат?";
			link.l1.go = "Alumnus_Finish_Zadanie_2";
		break;

		case "Alumnus_Finish_Zadanie_2":
			dialog.text = "Простите, что??";
			link.l1 = "Вот она.";
			link.l1.go = "Alumnus_Finish_Zadanie_3";
		break;

		case "Alumnus_Finish_Zadanie_3":
			dialog.text = "А-а! Вы принесли её! Какая удача! Я смогу теперь готовить свои целебные отвары, а также продолжить одно незаконченное исследование!";
			link.l1 = "Скажите, доктор, если это не секрет - зачем вам эта вонючая трава?";
			link.l1.go = "A_pravda_ZACHEM???";
			TakeItemFromCharacter(pchar, "PDM_Trava_Tzes_Umrat");
		break;

		case "A_pravda_ZACHEM???":
			dialog.text = "Видите ли, "+ GetSexPhrase("мой юный капитан","сударыня") +", я собираюсь разрешить главную загадку натуральной философии - секрет бессмертия! С помощью этой травки я намереваюсь создать зелье, которое позволит мне жить вечно!";
			link.l1 = "Ясно. Ладно, если после того, как вы проглотите это зелье, вы вдруг обнаружите, что от вас отскакивают ядра - сообщите мне, пожалуйста.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alumnus_Lechenie_s_voprosom";

			CloseQuestHeader("PDM_Aptekar");
		break;

		case "Alumnus_Lechenie_s_voprosom":	//Для Грегга
			dialog.text = "...но здесь элемент огня представлен ароматом корицы, чьё доминирование уравновешивается запахом... Ой, капитан, я вас не заметил, чем я могу быть вам полезен?";
			link.l1 = "Здравствуйте, доктор Алюмнус, я бы хотел"+ GetSexPhrase("","а") +", чтобы вы осмотрели моих раненных офицеров.";
			link.l1.go = "CheckForConfuse";
			link.l2 = "Чего это у вас закрыта дверь с улицы? Клиентов упускаете.";
			link.l2.go = "Alumnus_Lechenie_s_voprosom_2";
			link.l3 = "Решил"+ GetSexPhrase("","а") +" проведать вас. До свидания.";
			link.l3.go = "exit";	//Для выхода
			if(CheckAttribute(PChar,"Luke.BadPoison"))
			{
				link.l4 = "Доктор, мне очень нужна ваша помощь, меня отравили очень сильным ядом!";
				link.l4.go = "LukePoison";
			}
		break;

		case "Alumnus_Lechenie_s_voprosom_2":
			dialog.text = "Понимаете ли, мой дом расположен аккурат между доками и таверной, если я держу дверь открытой, сюда постоянно наведываются случайные посетители, которые так и норовят опрокинуть одну из моих настоек. Одного такого 'гостя' мне потом пришлось приводить в чувства целую неделю, а недостатка в клиентах я никак не испытываю, эту лавку в городе знают все местные, от губернатора до портового грузчика.";
			link.l1 = "Ладно, я понял"+ GetSexPhrase("","а") +". Вы можете осмотреть моих раненных офицеров?";
			link.l1.go = "CheckForConfuse";
			link.l2 = "Это было очень интересно. До свидания.";
			link.l2.go = "exit";

			NextDiag.TempNode = "Alumnus_Lechenie";
		break;

		case "Alumnus_Lechenie":
			dialog.text = "...но здесь элемент огня представлен ароматом корицы, чьё доминирование уравновешивается запахом... Ой, капитан, я вас не заметил, чем я могу быть вам полезен?";
			link.l1 = "Здравствуйте, доктор Алюмнус, я бы хотел"+ GetSexPhrase("","а") +", чтобы вы осмотрели моих раненных офицеров.";
			link.l1.go = "CheckForConfuse";
			link.l2 = "Решил"+ GetSexPhrase("","а") +" проведать вас. До свидания.";
			link.l2.go = "exit";
			if(CheckAttribute(PChar,"Luke.BadPoison"))
			{
				link.l3 = "Доктор, мне очень нужна ваша помощь, меня отравили очень сильным ядом!";
				link.l3.go = "LukePoison";
			}
		break;

		case "CheckForConfuse":
			dialog.text = "Кому именно требуется медицинская помощь, капитан?";
			for(i=0; i<GetPassengersQuantity(pchar); i++)
			{
				iOfficer = GetPassenger(pchar, i);
				sld = GetCharacter(iOfficer);
				if (!GetRemovable(sld)) continue;
				if (!CheckAttribute(sld, "HPminusDaysNeedtoRestore")) continue;
				attrL = "l"+i;
				Link.(attrL)	= "Офицер " + GetFullName(sld) + ".";
				Link.(attrL).go = "OfficerConfusedSel_" + i;
			}
			Link.l99 = "В данный момент никому.";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));

			if (!CheckAttribute(chref,"quest.officertype")) offtype = "Универсал";
			else offtype = XI_ConvertString(chref.quest.officertype);
			dialog.Text = "Вы имеете в виду "+GetFullName(chref)+", специализация - "+offtype+".";
			Link.l1 = "Да, именно.";
			Link.l1.go = "OfficerConfused_2";
			Link.l99 = "Нет, я передумал"+ GetSexPhrase("","а") +".";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused_2":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			if (CheckAttribute(chref,"chr_ai.max_hp")) npchar.HealPrice = (makeint(chref.chr_ai.max_hp)*100)+makeint((sti(chref.rank)*500)*(MOD_SKILL_ENEMY_RATE*3/2));
			else npchar.HealPrice = (makeint(chref.health.maxhp)*100)+makeint((sti(chref.rank)*500)*(MOD_SKILL_ENEMY_RATE*3/2));
			dialog.Text = "По прогнозам, этому офицеру до полного излечения естественным путём ещё дней так..."+(sti(chref.HPminusDaysNeedtoRestore)-sti(chref.HPminusDays))+". Я мог бы попробовать ускорить процесс выздоровления, но это обойдётся вам в... "+FindRussianMoneyString(sti(npchar.HealPrice));
			if (sti(pchar.money)>=sti(npchar.HealPrice))
			{
				Link.l1 = "Хорошо, я гото"+ GetSexPhrase("в","ва")+" заплатить.";
				Link.l1.go = "OfficerConfused_3";
			}
			Link.l99 = "Пожалуй нет, я пока несколько стесн"+ GetSexPhrase("ён","ена") +" в средствах.";
			Link.l99.go = "exit";
		break;

		case "OfficerConfused_3":
			chref = GetCharacter(sti(NPChar.OfficerToHealConfuse));
			AddMoneyToCharacter(pchar,-sti(npchar.HealPrice));
			LAi_Fade("", "");
			WaitDate("",0,0,0, 0, 60);
			DeleteAttribute(chref, "HPminusDays");
			DeleteAttribute(chref, "HPminusDaysNeedtoRestore");
			Log_Info("Офицер " + GetFullName(chref) + " выздоровел.");
			dialog.Text = "Мне удалось полностью исцелить " + GetFullName(chref) + ". Хотя надо признать, что это было весьма непросто...  У вас всё или кому-то ещё требуется моя помощь?";
			Link.l1 = "Нет, есть ещё нуждающиеся.";
			Link.l1.go = "CheckForConfuse";
			Link.l99 = "Пока всё. Благодарю вас за помощь.";
			Link.l99.go = "exit";
		break;

		case "LukePoison":
			dialog.text = "Капитан, дайте мне вас осмотреть... Да, этот яд был приготовлен из очень редких и вредоносных трав! Но не волнуйтесь, я знаю, как это лечить. А сейчас, "+pchar.name+", ложитесь в кровать, я скоро вами займусь.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("HealingPoison");
		break;
		
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Грабёж среди бела дня!!! Это что же такое делается?! Ну, погоди, "+ GetSexPhrase("приятель","подруга") +"...", "Эй, ты чего это там копаешься?! Никак, вздумал"+ GetSexPhrase("","а") +" ограбить меня? Ну, тогда тебе конец...", "Постой, ты куда это полез"+ GetSexPhrase("","ла") +"? Да ты вор"+ GetSexPhrase("","овка") +", оказывается! Ну, считай, что ты приплыл"+ GetSexPhrase("","а") +", родн"+ GetSexPhrase("ой","ая") +"...");
			link.l1 = LinkRandPhrase("Дьявол!!", "Каррамба!!", "А-ать, чёрт!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
