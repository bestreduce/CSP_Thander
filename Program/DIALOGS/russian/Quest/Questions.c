
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int iTermsValidity;

	int iNation;
	int LicenceValidity;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sTemp;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "exit_over":
			npchar.lifeDay = 0;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "SCQ_exit":
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		case "good_all":
			dialog.text = NPCStringReactionRepeat("Рад" + NPCharSexPhrase(npchar, "","а") + " видеть вас снова. Вы что-то ещё хотели?",
				"О-о, опять вы? Сегодня у нас уже был разговор. Что-то изменилось?",
				"Хм, может, хватит надоедать мне без дела?!",
                "Бр-р-р, тошнит уже от твоей физиономии...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Нет, ничего такого...",
				"Нет, все нормально.",
                "Да, конечно, извини...",
				"Хм, ну это вы зря, физиономия у меня что надо. Горжусь ею!", npchar, Dialog.CurrentNode);
			link.l1.go = "Exit";
			NextDiag.TempNode = "good_all";
		break;
		case "All_disagree":
			npchar.lifeDay = 0;
			NextDiag.TempNode = "All_bye";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "All_bye":
			dialog.text = "Я не желаю с вами разговаривать, прощайте.";
			link.l1 = "Хех, ну и не надо.";
			link.l1.go = "Exit";
			NextDiag.TempNode = "All_bye";
		break;
		//================================== в Порт оф Спейне ======================================
		case "PortSpein":
			NextDiag.TempNode = "PortSpein";
			dialog.text = "Здравствуйте, капитан. Не хотите поговорить о том, что вас, без сомнения, интересует?";
			link.l1 = "Нет, не хочу.";
			link.l1.go = "exit_over";
			link.l2 = "А откуда ты знаешь, что может меня заинтересовать?";
			link.l2.go = "PortSpein_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortSpein_1":
			dialog.text = "Слухи, " +  GetAddress_Form(NPChar) + ", ими земля полнится...";
			link.l1 = "Хех, ну давай, поговорим.";
			if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part1") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
			{
				link.l1.go = "PortSpein_2";
			}
			else
			{
				link.l1.go = "PortSpein_2_pistol";
			}
		break;
		case "PortSpein_2":
			dialog.text = "Полагаю, что вам будет интересна одна... вещь, так сказать.";
			link.l1 = "Бесспорно.";
			link.l1.go = "PortSpein_3";
		break;

		case "PortSpein_2_pistol":
			dialog.text = "Полагаю, что вам будет интересна информация о местонахождении одной очень нужной вещицы.";
			link.l1 = "Бесспорно.";
			link.l1.go = "PortSpein_3_pistol";
		break;

		case "PortSpein_3":
			dialog.text = "Очень хорошо. Но я должен быть уверен, что эта вещь попадёт именно тому, кто сумеет верно ею распорядиться - я обещал это одному человеку. Поэтому я предлагаю вам ответить на один вопрос, чтобы я мог понять, действительно ли вы т"+ GetSexPhrase("от","а") +", кто мне нуж"+ GetSexPhrase("ен","на") +". Согласны?";
			link.l1 = "Хех... Ну, соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "PortSpein_4";
			link.l2 = "Поищи кого-нибудь другого и будь в нем уверен. Я - пас.";
			link.l2.go = "All_disagree";
		break;

		case "PortSpein_3_pistol":
			dialog.text = "Очень хорошо. Но я должен быть уверен, что эта вещь попадёт именно тому, кто сумеет верно ею распорядиться - я обещал это одному человеку. Поэтому я предлагаю вам ответить на один вопрос, чтобы я мог понять, действительно ли вы т"+ GetSexPhrase("от","а") +", кто мне нуж"+ GetSexPhrase("ен","на") +". Согласны?";
			link.l1 = "Хех... Ну, соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "PortSpein_4";
			link.l2 = "Поищи кого-нибудь другого и будь в нем уверен. Я - пас.";
			link.l2.go = "All_disagree";
		break;

		case "PortSpein_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "В таком случае, слушайте вопрос. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";
		break;
		case "PortSpein_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Правильный ответ! Вы действительно "+ GetSexPhrase("знающий кэп","разбираетесь в морском деле, девушка") +".";
				link.l1 = "Хех, ещё бы! Говори, что там у тебя за вещица.";
				if (GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(pchar, "map_part1") == 0 && GetCharacterItem(pchar, "map_part2") == 0)
				{
					link.l1.go = "PortSpein_ok";
				}
				else
				{
					link.l1.go = "PortSpein_ok_pistol";
				}
			}
			else
			{
				dialog.text = "Ответ неверный. Может, подумаете и скажете правильный ответ?";
				link.l1 = "Да, попробую ещё раз.";
				link.l1.go = "PortSpein_5";
				link.l2 = "Нет, я не знаю ответа на этот вопрос.";
				link.l2.go = "PortSpein_6";
			}
		break;
		case "PortSpein_ok":
			dialog.text = "Это старая карта сокровищ. Говорят, их спрятал сам сэр Уолтер Райли. Отдаю её вам, согласно данному мной обету - передать из рук в руки опытному моряку. Удачи вам в поисках!";
			link.l1 = "Ну что же, я понял"+ GetSexPhrase("","а") +" тебя. Будем искать!";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
			GiveItem2Character(pchar, "map_full");
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "1");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			CloseQuestHeader("QuestionsMessages");
		break;

		case "PortSpein_ok_pistol":
			dialog.text = "Это отличный фитильный мушкет! Но он не у меня, я просто знаю, где его можно раздобыть. В пиратском поселении Ла Вега нужно зайти за дом слева от ворот - там в земле спрятано это оружие. Удачи!";
			link.l1 = "Ну что же, я понял"+ GetSexPhrase("","а") +" тебя. Будем искать!";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.LaVega_town = true;
			pchar.GenQuestRandItem.LaVega_town.randitem4 = "mushket";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "1_1");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			CloseQuestHeader("QuestionsMessages");
		break;

		case "PortSpein_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Очень хорошо! Тогда повторю свой вопрос. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";
		break;
		case "PortSpein_6":
			dialog.text = "Очень жаль, но в таком случае я не могу отдать вам то, что предназначается хорошему кэпу.\nНо я готов выслушать ваш ответ в другое время, если вы сможете меня застать. Я буду в городе ещё чуть больше недели.";
			link.l1 = "Хорошо, если узнаю ответ - попытаюсь опять.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortSpein_again";
		break;
		case "PortSpein_again":
			dialog.text = "А-а, вот и вы снова. Узнали ответ?";
			link.l1 = "Кажется, узнал"+ GetSexPhrase("","а") +".";
			link.l1.go = "PortSpein_5";
		break;
		//================================== Виллемстад: Найти пропавшего торговца ======================================
		case "Villemstad":
			NextDiag.TempNode = "Villemstad";
			dialog.text = "Здравствуйте, капитан. Я хотела попросить вас об одном одолжении.";
			link.l1 = RandPhraseSimple("Что у вас стряслось, " + GetAddress_FormToNPC(NPChar) + "?", "Излагайте суть проблемы, " + GetAddress_FormToNPC(NPChar) + ". Я постараюсь вам помочь.");
			link.l1.go = "SCQ_Hasband";
			link.l2 = RandPhraseSimple("Я занят"+ GetSexPhrase("","а") +", красавица, не сегодня!", "Прошу прощения, " + GetAddress_FormToNPC(NPChar) + ", но в данный момент я не имею времени...");
			link.l2.go = "exit";
		break;
		case "SCQ_Hasband":
			dialog.text = "Мой муж занимается коммерцией - доставляет грузы торговцам по всей округе. Так вот, он ушёл в море уже больше трёх месяцев назад, и до сих пор не вернулся!";
			link.l1 = "Вы думаете, с ним что-то случилось?";
			link.l1.go = "SCQ_Hasband_0";
		break;
		case "SCQ_Hasband_0":
			dialog.text = "Не знаю, но очень надеюсь, что он просто занят по работе. Хотя мог бы отправить весточку, знает ведь, что я волнуюсь!";
			link.l1 = "В море сейчас неспокойно, всякое может случиться...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			dialog.text = "Вот! Вы понимаете, о чем я говорю. По виду вы "+ GetSexPhrase("капитан бравый","девушка бравая") +", поэтому я и хотела попросить вас о том, чтобы вы нашли моего мужа. За это я готова заплатить вам 5000 пиастров и отдам свои драгоценности.";
			link.l1 = "Хорошо. Если я встречу вашего мужа в море или где-нибудь ещё, то сообщу ему о вашем беспокойстве. И скажите мне, как зовут вашего супруга и что у него за корабль?";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Такие деньги меня не интересуют. К сожалению, я вынужден"+ GetSexPhrase("","а") +" отказаться...";
			link.l2.go = "exit";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "Его зовут Мауритс Грун. А работает он на шняве с именем 'Луиза'. В последний раз его корабль видели на юге у Мейна.";
			link.l1 = "Понятно. Ну что же, теперь ожидайте. И постарайтесь находиться преимущественно в церкви, чтобы я не искал"+ GetSexPhrase("","а") +" вас по городу...";
			link.l1.go = "exit";
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			SetQuestHeader("SCQ_womanHasband");
			AddQuestRecord("SCQ_womanHasband", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("QuetionsVillemstad_MuzhTorgovets", "GrunMaurits", "man", "man", sti(PChar.rank), HOLLAND, -1, true));
			FantomMakeCoolSailor(sld, SHIP_SHNYAVA, "Луиза", CANNON_TYPE_CULVERINE_LBS12, 30, 30, 30);
			sld.name = "Мауритс";
			sld.lastname = "Грун";
			sld.dialog.filename   = "Quest\Questions.c";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			sld.Ship.Mode = "trade";
			Group_FindOrCreateGroup("QuetionsVillemstad_MuzhTorgovets_Ship");
			Group_SetType("QuetionsVillemstad_MuzhTorgovets_Ship", "pirate");
			Group_AddCharacter("QuetionsVillemstad_MuzhTorgovets_Ship", "QuetionsVillemstad_MuzhTorgovets");
			Group_SetGroupCommander("QuetionsVillemstad_MuzhTorgovets_Ship", "QuetionsVillemstad_MuzhTorgovets");
			int RandomLuiza;
			RandomLuiza = rand(2);
			if (RandomLuiza == 0)
			{ 
				Group_SetAddress("QuetionsVillemstad_MuzhTorgovets_Ship", "Maracaibo", "quest_ships", "Quest_ship_6");
			break;
			}
			if (RandomLuiza == 1)
			{ 
				Group_SetAddress("QuetionsVillemstad_MuzhTorgovets_Ship", "Caracas", "quest_ships", "Quest_ship_5");
			break;
			}
			if (RandomLuiza == 2)
			{ 
				Group_SetAddress("QuetionsVillemstad_MuzhTorgovets_Ship", "Cumana", "quest_ships", "Quest_ship_5");
			break;
			}
		break;
		case "HasbandCap_inDeck":
			dialog.text = "Здравствуйте. Чему обязан за честь видеть вас у себя на корабле?";
			link.l1 = "Вас зовут Мауритс Грин, не так ли?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Да, это я.";
			link.l1 = "Это, конечно, звучит глупо, но ваша жена просила меня передать, что очень за вас волнуется.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Фу, чёрт! А я, честно говоря, испугался - решил, что это знаменитый охотник за призами - Одноглазый Стид Хантер за мной увязался. Ну, хорошо, что ошибся\nВы знаете, я настолько закрутился с работой, что мне не до неё сейчас. Выгодные предложения следуют одни за другими, я не могу упускать возможную выгоду только потому, что моя жена волнуется.";			
			link.l1 = "Это конечно, но вы могли хотя бы написать ей, что с вами всё в порядке.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Да, вы правы. Я это обязательно сделаю в первом же порту на разгрузке... Спасибо вам огромное за участие в наших семейных делах!";
			link.l1 = "Не за что, дружище. Я тогда пойду.";
			link.l1.go = "HasbandCap_inDeck_4";			
		break;
		case "HasbandCap_inDeck_4":
			dialog.text = "Постойте, хочу с вами поделиться одной вещью. Дело в том, что мы с женой одно время жили в Пуэрто-Принсипе, но потом вынуждены были переехать в Виллемстад. И скажу я вам, это было одно из самых верных решений. Ноги моей больше не будет в этой дыре!";
			link.l1 = "Продолжайте...";
			link.l1.go = "HasbandCap_inDeck_5";			
		break;
		case "HasbandCap_inDeck_5":
			dialog.text = "Ну так вот, кое-какие там вещи остались у меня, и одна из них уж наверняка должна пригодиться "+ GetSexPhrase("такому капитану","такой бравой девушке-капитану") +", как вы.";
			link.l1 = "Что там за вещица, что мне будет нужна?";
			link.l1.go = "HasbandCap_inDeck_6";			
		break;
		case "HasbandCap_inDeck_6":
			dialog.text = "Это неплохая подзорная труба. Она закопана в земле под окном нашего бывшего дома в Пуэрто-Принсипе, слева от таверны.";
			link.l1 = "Понятно. Ну что же, спасибо вам и прощайте.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			npchar.dialog.filename   = "Quest\Questions.c";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			AddQuestRecord("SCQ_womanHasband", "2");
			sld = characterFromId("QuetionsVillemstad");
			sld.dialog.filename = "Quest\Questions.c";
			sld.dialog.currentnode = "womanHasbandover";
			pchar.GenQuestRandItem.PuertoPrincipe_town = true;
			pchar.GenQuestRandItem.PuertoPrincipe_town.randitem1 = "spyglass3";
			PChar.quest.SCQ_Hasband_Truba.win_condition.l1 = "locator";
			PChar.quest.SCQ_Hasband_Truba.win_condition.l1.location = "PuertoPrincipe_town";
			PChar.quest.SCQ_Hasband_Truba.win_condition.l1.locator_group = "randitem";
			PChar.quest.SCQ_Hasband_Truba.win_condition.l1.locator = "randitem1";
			PChar.quest.SCQ_Hasband_Truba.win_condition = "SCQ_Hasband_Truba";
			DeleteAttribute(pchar, "questTemp.SCQ_Hasband_Luiza");
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Ещё раз примите мою благодарность...";
			link.l1 = "Да не стоит, всё в порядке.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		
		//================================== Порт-о-Принс: Вызволение из плена мужа горожанки ======================================
		case "PortPax":
			NextDiag.TempNode = "PortPax";
			dialog.text = "Капитан, помогите мне, умоляю вас! Мой муж попал к пиратам! Вы можете спасти его?";		
			link.l1 = "Подождите, что-то я не очень понимаю, кто к кому попал...");
			link.l1.go = "SCQ_Pirates";
			DeleteAttribute(npchar, "talker");
		break;
		case "SCQ_Pirates":
			dialog.text = "Сейчас я вам объясню. Дело в том, мой муж, совершенно обычный человек, был захвачен пиратами! Они убивали всех, никого не щадили...";
			link.l1 = "Значит, капитан посмел оказать сопротивление. Если бы они сдались, никого бы не тронули.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Может быть, но мой муж тут совершенно ни при чём. Он был простым пассажиром на этом корабле. Так вот, чтобы спасти свою жизнь, ему пришлось сказать, что он сказочно богат. Пираты его пощадили, и даже не бросили в трюм.";
			link.l1 = "А откуда вы знаете?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "Мужу удалось отправить мне письмо, где он пишет, что с ним всё в порядке. Его держат в каюте, не как других пленников.";
			link.l1 = "И что вы намерены делать? Так долго продолжаться не может. Рано или поздно пираты его раскусят.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Вы ведь тоже пират? Да-да, я знаю... Умоляю вас, помогите нам, спасите моего мужа! В письме он описал пиратский корабль и назвал имя капитана. Вам ведь будет достаточно просто найти его!";
			link.l1 = "Не так это и просто, как вам кажется. Все пленники - законный приз захватившего корабль кэпа. Да и не могу я сделать это за короткий срок.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "Но вы же можете попытаться! К тому же, время на поиски есть. Мой муж далеко не дурак, он назвался негоциантом из Старого света, так что пираты не требуют за него денег немедленно - ехать за ними очень далеко. Если вы освободите его, то я отдам вам всё, что у меня есть!";
			link.l1 = "И что у вас есть?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			dialog.text = "Немного, 5000 пиастров и все мои драгоценности... Но я буду молиться за вашу душу до конца жизни!";
			link.l1 = "Да уж, действительно немного... Ну да ладно, я готов"+ GetSexPhrase("","а") +" помочь вам при случае.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Сожалею, но это слишком мало для того, чтобы я напал"+ GetSexPhrase("","а") +" на своего коллегу, члена Берегового братства.";
			link.l2.go = "exit";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Спасибо вам, спасибо!!";
			link.l1 = "Если всё получится, тогда и будете благодарить, а пока не стоит. Расскажите-ка лучше, как зовут вашего мужа и всё, что вы знаете об этих пиратах.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			dialog.text = "Мужа зовут Венсан Лаббе. Капитана пиратов зовут Кори Болл, он промышляет на шхуне с именем 'Колосс'. В последний раз его видели возле необитаемого острова Теркс.";
			link.l1 = "Ясно. Ну что же, теперь ожидайте и надейтесь, что мне удастся его поймать. Постарайтесь находиться в церкви, чтобы я мог"+ GetSexPhrase("","ла") +" вас там быстро найти.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			SetQuestHeader("SCQ_womanPirates");
			AddQuestRecord("SCQ_womanPirates", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax_KoriBoll", "officer_17", "man", "man", sti(PChar.rank), PIRATE, -1, true));
			FantomMakeCoolSailor(sld, SHIP_SCHOONERWAR, "Колосс", CANNON_TYPE_CULVERINE_LBS12, 30, 30, 30);
			sld.name = "Кори";
			sld.lastname = "Болл";
			sld.dialog.filename   = "Quest\Questions.c";
			sld.dialog.currentnode = "PiratesCap_Board";
			sld.AlwaysEnemy = true;
			Group_FindOrCreateGroup("QuetionsPortPax_KoriBoll_Ship");
			Group_SetType("QuetionsPortPax_KoriBoll_Ship", "pirate");
			Group_AddCharacter("QuetionsPortPax_KoriBoll_Ship", "QuetionsPortPax_KoriBoll");
			Group_SetGroupCommander("QuetionsPortPax_KoriBoll_Ship", "QuetionsPortPax_KoriBoll");
			Group_SetAddress("QuetionsPortPax_KoriBoll_Ship", "Terks", "quest_ships", "Quest_ship_3");
			
			PChar.quest.SCQ_womanPirates_Potunul.win_condition.l1 = "Character_sink";
			PChar.quest.SCQ_womanPirates_Potunul.win_condition.l1.character = "QuetionsPortPax_KoriBoll";
			PChar.quest.SCQ_womanPirates_Potunul.win_condition = "SCQ_womanPirates_Potunul";
			PChar.quest.SCQ_womanPirates_Nashli.win_condition.l1 = "location";
			PChar.quest.SCQ_womanPirates_Nashli.win_condition.l1.location = "Terks";
			PChar.quest.SCQ_womanPirates_Nashli.win_condition = "SCQ_womanPirates_Nashli";
		break;
		case "PiratesCap_Board":
			dialog.text = "Дьявол! Какого чёрта?!!";
			link.l1 = "Мне нужен твой пленник, по имени Венсан Лаббе.";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ха! Ну уж нет, только через мой труп...";
			link.l1 = "Как вам будет угодно.";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("SCQ_womanPirates_afterCabinFight");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "womanPirates_Board":
			dialog.text = "Кто вы?";
			link.l1 = "Я капитан " + GetFullName(pchar) + ". Вы не волнуйтесь, я приш"+ GetSexPhrase("ёл","ла") +" за вами для того, чтобы отвезти к жене.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Чёрт возьми, неужели это не сон?!";
			link.l1 = "Уверяю вас, это не сон... Ну что же, дело сделано, теперь уходим отсюда.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("QuetionsPortPax");
			sld.dialog.filename = "Quest\Questions.c";
			sld.dialog.currentnode = "womanPiratesover";
			AddQuestRecord("SCQ_womanPirates", "4");
		break;
		//================================== Сан-Хуан ======================================
		case "SanJuan":
			NextDiag.TempNode = "SanJuan";
			dialog.text = "Приветствую вас, капитан. Хочу кое-что вам предложить.";
			link.l1 = "Нет, меня это не интересует.";
			link.l1.go = "exit_over";
			link.l2 = "Внимательно вас слушаю, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l2.go = "SanJuan_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "SanJuan_1":
			dialog.text = "Есть у меня одна очень нужная капитанам вещь, которая, без сомнения, заинтересует вас.";
			link.l1 = "Ещё более внимательно вас слушаю. Что это за вещь?";
			link.l1.go = "SanJuan_2";
		break;
		case "SanJuan_2":
			dialog.text = "Документ, я бы сказал, достался мне по случаю и на определённых условиях. Я должен как можно быстрей передать его капитану, который в этом действительно нуждается и достоин того.";
			link.l1 = "Вот как? Ну, и что же это за таинственный документ?";
			link.l1.go = "SanJuan_3";
		break;
		case "SanJuan_3":
			dialog.text = "Я могу сказать вам это только после того, как вы ответите мне на один вопрос.";
			link.l1 = "Что ещё за вопрос?";
			link.l1.go = "SanJuan_4";
		break;
		case "SanJuan_4":
			dialog.text = "Вопрос на общие темы для кэпов. Я должен чётко представлять себе, с кем имею дело.";
			link.l1 = "Ну хорошо, задавай свой вопрос на общие темы.";
			link.l1.go = "SanJuan_5";
			link.l2 = "Ни на какие дурацкие вопросы я отвечать не желаю.";
			link.l2.go = "All_disagree";
		break;
		case "SanJuan_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Очень хорошо. Итак, капитан, вот мой вопрос. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";
		break;
		case "SanJuan_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Великолепно, "+ GetSexPhrase("капитан","девушка") +"! Совершенно правильно!";
				link.l1 = "Ну так!.. Так что там за таинственный документ?";
				link.l1.go = "SanJuan_ok";
			}
			else
			{
				dialog.text = "Нет, "+ GetSexPhrase("капитан","девушка") +", ответ неверный. Предлагаю всё-таки дать правильный ответ.";
				link.l1 = "Повторим...";
				link.l1.go = "SanJuan_6";
				link.l2 = "Нет, хватит с меня вопросов.";
				link.l2.go = "SanJuan_7";
			}
		break;
		case "SanJuan_ok":
			iNation = 5;
			LicenceValidity = 40;
			for (int i=0; i<4 ; i++)
			{
				if (GetRelation2BaseNation(i) == RELATION_ENEMY)
				{
					iNation = i;
					break;
				}
			}
			if (iNation == 5) //если со всеми в мире, то генерим лицензию случайной нации сроком 40 дней
			{
				iNation = rand(3);
			}
			GiveNationLicence(iNation, LicenceValidity + GetDaysContinueNationLicence(iNation));//фикс - продляю лицензию на весь срок, а не по сложным округлениям

			dialog.text = "Это " + GetRusNameNationLicence(iNation) + " сроком на " + LicenceValidity + " дней! С удовольствием вручаю её вам.";
			link.l1 = "Ого, довольно дорогой документ! Ну что же, спасибо вам, " + GetAddress_FormToNPC(NPChar) + ", за оказанную услугу. Прощайте.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
		break;
		case "SanJuan_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Прекрасно. Считаю своим долгом напомнить вам вопрос. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";
		break;
		case "SanJuan_7":
			dialog.text = "Ну, хватит - так хватит. Прощайте, "+ GetSexPhrase("капитан","девушка") +"...";
			link.l1 = "Желаю всего наилучшего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SanJuan_again";
		break;
		case "SanJuan_again":
			dialog.text = "Слушаю вас внимательно, капитан. Неужели решили повторить попытку и ответить на заданный вопрос?";
			link.l1 = "Да, кажется, мне известен правильный ответ.";
			link.l1.go = "SanJuan_6";
		break;
		//================================== Кумана ======================================
		case "Cumana":
			NextDiag.TempNode = "Cumana";
			dialog.text = "Приветствую вас, капитан! У меня к вам есть небольшое дельце. Вы не уделите мне минуту внимания?";
			link.l1 = "Нет, не уделю.";
			link.l1.go = "exit_over";
			link.l2 = "Да без проблем, минута твоя.";
			link.l2.go = "Cumana_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Cumana_1":
			dialog.text = "Очень хорошо. Хотел предложить вам маленькую сделку. У меня есть некий предмет, который может вас заинтересовать.";
			link.l1 = "Скажи, что это за предмет и назови цену.";
			link.l1.go = "Cumana_2";
		break;
		case "Cumana_2":
			dialog.text = "Денег за него я не возьму, вам нужно будет ответить мне на один вопрос. Если ответ будет верен - предмет ваш.";
			link.l1 = "Очень странно. А деньги тебе не нужны?";
			link.l1.go = "Cumana_3";
		break;
		case "Cumana_3":
			dialog.text = "Хех, деньги всем нужны, однако в этой сделке все решают ваши знания. Я не хочу дальше объяснять причины моего поведения, просто скажите - да или нет.";
			link.l1 = "Хм, пожалуй, что да. Само"+ GetSexPhrase("му","й") +" интересно стало.";
			link.l1.go = "Cumana_4";
			link.l2 = "Нет, нет, и ещё раз нет. Прощай.";
			link.l2.go = "All_disagree";
		break;
		case "Cumana_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Хех, на один вопрос вы уже ответили правильно. А теперь главное событие этого дня! Слушайте вопрос. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";
		break;
		case "Cumana_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Великолепно! Это правильный ответ!";
				link.l1 = "Понятно дело... Так что там за предмет, счастлив"+ GetSexPhrase("ым","ой") +" обладател"+ GetSexPhrase("ем","ьницей") +" которого я теперь являюсь?";
				link.l1.go = "Cumana_ok";
			}
			else
			{
				dialog.text = "Очень жаль, "+ GetSexPhrase("капитан","девушка") +". Мне действительно очень жаль... Ответ неверный! Попробуете ещё раз?";
				link.l1 = "Попробую!";
				link.l1.go = "Cumana_6";
				link.l2 = "Нет, пожалуй...";
				link.l2.go = "Cumana_7";
			}
		break;
		case "Cumana_ok":
			dialog.text = "Это статуя, дающая необычайную возможность лучше проводить ремонт корабля. Спрятана она в бухте близ Порто Белло. Называется эта бухта - лагуна Чирики. Внимательно все там осмотрите, и не бойтесь ноги замочить. Удачи, капитан!";
			link.l1 = "Знаешь, это действительно полезная вещица для кэпа. Спасибо тебе.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Shore46 = true;
			pchar.GenQuestRandItem.Shore46.randitem1 = "STATUE1";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "4");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			CloseQuestHeader("QuestionsMessages");
		break;
		case "Cumana_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Ну, тогда напоминаю вопрос! " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";
		break;
		case "Cumana_7":
			dialog.text = "Ну, не хотите - как хотите. Прощайте, капитан Незнайка...";
			link.l1 = "Чего?..";
			link.l1.go = "exit";
			NextDiag.TempNode = "Cumana_again";
		break;
		case "Cumana_again":
			dialog.text = "И что вам нужно от меня?";
			link.l1 = "Я хочу ещё раз попробовать ответить на твою загадку.";
			link.l1.go = "Cumana_6";
		break;
		//================================== Порт Рояль ======================================
		case "PortRoyal":
			NextDiag.TempNode = "PortRoyal";
			dialog.text = "Добрый день, капитан. Послушайте, мне кажется, что вы именно т"+ GetSexPhrase("от","а") +", кто мне нуж"+ GetSexPhrase("ен","на") +"...";
			link.l1 = "А вот я так не думаю.";
			link.l1.go = "exit_over";
			link.l2 = "В чем дело, " + GetAddress_FormToNPC(NPChar) + "?";
			link.l2.go = "PortRoyal_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortRoyal_1":
			dialog.text = "Я хочу предложить вам обмен. Дело в том, что у меня имеется вещь, которая мне совершенно ни к чему, ну, а вам пригодится уж точно.";
			link.l1 = "И что ты хочешь взамен?";
			link.l1.go = "PortRoyal_2";
		break;
		case "PortRoyal_2":
			dialog.text = "Ничего особенного. Я хочу знать, что эта вещь в надёжных руках.";
			link.l1 = "Ну так знай - она будет в действительно надёжных руках. Можешь не сомневаться.";
			link.l1.go = "PortRoyal_3";
		break;
		case "PortRoyal_3":
			dialog.text = "Охотно верю, но все же проверю. Ответите на один мой вопрос - и вещь ваша.";
			link.l1 = "Задавай свой вопрос, нет ничего проще!";
			link.l1.go = "PortRoyal_4";
			link.l2 = "Обойдусь как-нибудь...";
			link.l2.go = "All_disagree";
		break;
		case "PortRoyal_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Ну, вопрос достаточно прост. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";
		break;
		case "PortRoyal_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Я даже и не сомневалась, что вы правильно ответите.";
				link.l1 = "Естественно, другого и быть не могло. Так, ну а что там за вещь, которая уже моя?";
				link.l1.go = "PortRoyal_ok";
			}
			else
			{
				dialog.text = "Ответ неверный, "+ GetSexPhrase("капитан","девушка") +". Мне нужен правильный ответ. Ещё попытаетесь?";
				link.l1 = "Да, попытаюсь ещё!";
				link.l1.go = "PortRoyal_6";
				link.l2 = "Нет, не желаю я в отгадки играть.";
				link.l2.go = "PortRoyal_7";
			}
		break;
		case "PortRoyal_ok":
			dialog.text = "Это гвардейская кираса. Найти её ты сможешь на Ямайке в бухте Портленд.";
			link.l1 = "Да, в бою это штука нужная, "+ GetSexPhrase("а девушке уж точно ни к чему","мне точно пригодится") +". Спасибо тебе.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Shore36 = true;
			pchar.GenQuestRandItem.Shore36.randitem2 = "cirass3";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "5");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			CloseQuestHeader("QuestionsMessages");
		break;
		case "PortRoyal_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Хорошо. Полагаю, мне следует напомнить вопрос. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";
		break;
		case "PortRoyal_7":
			dialog.text = "Не желаете - как знаете. Хм, а на вид "+ GetSexPhrase("такой солидный капитан","такая боевая девушка") +"...";
			link.l1 = "Что ты хочешь этим сказать?";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_again";
		break;
		case "PortRoyal_again":
			dialog.text = "Не поняла! Что вам ещё нужно?";
			link.l1 = "Хочу ещё раз попробовать ответить на твою загадку.";
			link.l1.go = "PortRoyal_6";
		break;
		//================================== Сантьяго ======================================
		case "Santiago":
			NextDiag.TempNode = "Santiago";
			dialog.text = "Приветствую вас в Сантьяго, капитан! Я хотел с вами поговорить по одному маленькому дельцу. Вы не против?";
			link.l1 = "Не желаю разговаривать.";
			link.l1.go = "exit_over";
			link.l2 = "Ни в коей мере. Я к вашим услугам.";
			link.l2.go = "Santiago_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Santiago_1":
			dialog.text = "Прекрасно! Тогда приступим. Вышеуказанное дельце заключает в себе по сути сделку, или обмен, если хотите...";
			link.l1 = "Хочу, обмен хочу! Давайте меняться.";
			link.l1.go = "Santiago_2";
		break;
		case "Santiago_2":
			dialog.text = "К-хе, ну что же, давайте. Итак, я могу предложить вам один, без сомнения, нужный вам предмет. Взамен мне от вас ничего не нужно, я лишь хочу получить ответ на один поставленный мной вопрос.";
			link.l1 = "И что это за вопрос?";
			link.l1.go = "Santiago_3";
		break;
		case "Santiago_3":
			dialog.text = "Общего характера, по вашей специфике. Понимаете, я лишь хочу проверить уровень ваших знаний. Это необходимое условие. Вы согласны?";
			link.l1 = "Хм, хоть я и не понимаю, зачем вам это, тем не менее, я соглас"+ GetSexPhrase("ен","на") +".";
			link.l1.go = "Santiago_4";
			link.l2 = "Хех, проверяльщик выискался! Катись отсюда, пока не поздно...";
			link.l2.go = "All_disagree";
		break;
		case "Santiago_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Замечательно! Итак, слушайте, пожалуйста, мой вопрос. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";
		break;
		case "Santiago_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "Отлично, это правильный ответ! Поздравляю.";
				link.l1 = "Спасибо за поздравления, мне очень приятно. И чтобы мне вдвойне было приятно, давайте я немного послушаю о предмете нашей сделки...";
				link.l1.go = "Santiago_ok";
			}
			else
			{
				dialog.text = "Хм, "+ GetSexPhrase("капитан","девушка") +", этот ответ меня устроить не может. Он неправильный! Прошу вас, попробуйте ещё раз...";
				link.l1 = "Конечно, попробую.";
				link.l1.go = "Santiago_6";
				link.l2 = "Нет, откажусь. Надоело.";
				link.l2.go = "Santiago_7";
			}
		break;
		case "Santiago_ok":
			sTemp = GetConvertStr("itmname_pistol6", "ItemsDescribe.txt");
			dialog.text = "Это " + sTemp + "! Вы можете отыскать его в гроте на Кубе, чтобы туда попасть, вам нужно выйти за город и прогуляться по джунглям. Но согласитесь, что такое оружие - вещь, нужная вам в крайней степени.";
			link.l1 = "Да уж, с этим не поспоришь. Ну что же, придётся прогуляться. Спасибо вам и всего хорошего.";
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
 			pchar.GenQuestRandItem.Cuba_Grot = true;
			pchar.GenQuestRandItem.Cuba_Grot.randitem1 = "pistol6";
			ReOpenQuestHeader("QuestionsMessages");
			AddQuestRecord("QuestionsMessages", "6");
			AddQuestUserData("QuestionsMessages", "sName", GetFullName(npchar));
			AddQuestUserData("QuestionsMessages", "sBladeName", sTemp);
			CloseQuestHeader("QuestionsMessages");
		break;
		case "Santiago_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = "Прекрасно! В таком случае, напомню его вам. " + NullCharacter.questions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";
		break;
		case "Santiago_7":
			dialog.text = "Вы отказываетесь? Вам надоело?! Хм, но смысл вопроса - ваша профессия! Впрочем, мне до этого дела нет, прощайте...";
			link.l1 = "Всего хорошего.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Santiago_again";
		break;
		case "Santiago_again":
			dialog.text = "Чем я могу вам помочь?";
			link.l1 = "Хочу ответить на ваш вопрос.";
			link.l1.go = "Santiago_6";
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Ой, капитан, я так рада вас видеть! Расскажите мне быстрей, что вы узнали по моему делу?";
			link.l1 = "Хм, напомните, " + GetAddress_FormToNPC(NPChar) + ", о каком деле идёт речь?";
			link.l1.go = "SCQ_womanResult_exit";
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Вы что, забыли, что обещали мне найти моего мужа? Его зовут Мауритс Грун!";
					link.l1 = "О-о, да, конечно... Ничего я не забыл"+ GetSexPhrase("","а") +", просто я пока так и не сумел"+ GetSexPhrase("","а") +" его разыскать.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Я что-то не поняла! Вы забыли, что должны отправить на тот свет моего обидчика, капитана по имени " + npchar.quest.SeekCap.capName + "?!";
					link.l1 = "Ну что вы, " + GetAddress_FormToNPC(NPChar) + ", ни в коем разе. Ваш заказ в работе, ожидайте...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Господи, капитан, вы забыли, что обещали вызволить моего мужа из плена?!";
					link.l1 = "Я ничего не забыл"+ GetSexPhrase("","а") +", работаю над этим. Ждите, " + GetAddress_FormToNPC(NPChar) + " " + npchar.lastname + ".";
					link.l1.go = "exit";
				break;
			}
		break;
		case "womanHasbandover":
			dialog.text = "Ах, капитан, я получила письмо от мужа! В нём он пишет, что вы нашли его.";
			link.l1 = "Да, всё верно, " + GetAddress_FormToNPC(NPChar) + ". Ваш муж, Мауритс Грун, жив и здоров. Он просто заработался, так сказать...";
			link.l1.go = "SCQR_womanHasband";
		break;
		case "womanRevengeover":
			dialog.text = "Что скажете, капитан? Вы сделали то, о чем я вас просила? Капитан " + npchar.quest.SeekCap.capName + " мёртв?";
			link.l1 = "Да, он мёртв, " + GetAddress_FormToNPC(NPChar) + ". Перед смертью он узнал, кто стал причиной его смерти. Последнее, что он слышал в этой жизни - ваше имя.";
			link.l1.go = "SCQR_womanRevenge";
		break;
		case "womanPiratesover":
			dialog.text = "Вы всё-таки освободили моего мужа! Умоляю вас, скажите мне, это так?!!";
			link.l1 = "Да, сейчас он находится у меня на корабле. Можете его забирать, если Венсан Лаббе и есть ваш муж...";
			link.l1.go = "SCQR_womanPirates";
		break;

		case "SCQR_womanHasband":
			dialog.text = "Боже мой, как я вам благодарна! Да, кстати, вот ваши 5000 пиастров и 10 изумрудов. И ещё раз спасибо!";
			link.l1 = "Хм, да не за что...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(PChar,"jewelry4", 10);
			pchar.questTemp.womanHasband_Nagrada = true;
			if (CheckAttribute(pchar, "questTemp.womanHasband_Nagrada") && CheckAttribute(pchar, "questTemp.womanHasband_Truba"))
			{
				CloseQuestHeader("SCQ_womanHasband");
				DeleteAttribute(pchar, "questTemp.womanHasband_Nagrada");
				DeleteAttribute(pchar, "questTemp.womanHasband_Truba");
			}
		break;
		case "SCQR_womanPirates":
			dialog.text = "Конечно, это он!!! Господи, капитан, как же я вам благодарна! Я буду молиться за вас каждый день, пока жива!";
			link.l1 = "Это приятно, молитесь...";
			link.l1.go = "SCQR_womanPirates_2";
		break;		
		case "SCQR_womanPirates_2":
			dialog.text = "Вот ваши обещанные 5000 пиастров и 10 сапфиров. Но и это ещё не всё. Дело в том, что я знаю про одну спрятанную вещицу, которая была бы вам полезна.";
			link.l1 = "И что же это за вещица?";
			link.l1.go = "SCQR_womanPirates_3";
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(PChar,"jewelry1", 10);
		break;
		case "SCQR_womanPirates_3":
			dialog.text = "Это великолепный костюм, последний писк европейской моды! Спрятан он в подземелье под Тортугой, в одном из тупиков. Придётся поискать.";
			link.l1 = "Поищем, чего уж. Презентабельный внешний вид - это очень важно для капитана. Спасибо тебе.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("QuetionsPortPax_MuzhPassajir");
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddQuestRecord("SCQ_womanPirates", "5");
			AddQuestUserData("SCQ_womanPirates", "sSex", GetSexPhrase("ся","ась"));
			
			pchar.GenQuestRandItem.Tortuga_Cave = true;
			pchar.GenQuestRandItem.Tortuga_Cave.randitem1 = "suit_2";
			PChar.quest.SCQ_Pirates_Kostum.win_condition.l1 = "locator";
			PChar.quest.SCQ_Pirates_Kostum.win_condition.l1.location = "Tortuga_Cave";
			PChar.quest.SCQ_Pirates_Kostum.win_condition.l1.locator_group = "randitem";
			PChar.quest.SCQ_Pirates_Kostum.win_condition.l1.locator = "randitem1";
			PChar.quest.SCQ_Pirates_Kostum.win_condition = "SCQ_Pirates_Kostum";
		break;
	}
}
