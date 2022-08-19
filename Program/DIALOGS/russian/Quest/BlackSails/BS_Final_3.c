
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

		//Скипаем с отравления три дня. ГГ приходит в себя в комнате таверны. Запись в СЖ: «Неожиданно. Но предсказуемо. Флинт поимел нас всех. Кто бы мог подумать. Хорошо, что жив(ва) остался(лась)! Нужно разобраться в происходящем. Дьявол, как же мутит то!»

		//Далее, Вейна нет на Бермудах. Спускаемся в таверну. Подходит Макс

		case "BS_F3_1":	//Максин
			dialog.text = "Очнул"+ GetSexPhrase("ся","ась") +" наконец, ты дольше всех в отключке был"+ GetSexPhrase("","а") +"";
			link.l1 = "Все живы? Что нового?";
			link.l1.go = "BS_F3_2";
		break;

		case "BS_F3_2": //Максин
			dialog.text = "Все живы, он подмешал белладонну в вино. Мастер Алексус отпаивал нас всех, какой то дрянью из древесного угля и Бог знает чего ещё. Заблевали всю резиденцию, но выжили.";
			link.l1 = "Обязательно куплю ему что-нибудь техническое. Так какие новости? Флинт? Золото?";
			link.l1.go = "BS_F3_3";
		break;

		case "BS_F3_3":	//Максин
			dialog.text = "Ни Флинта, ни золота. На складе только один сундук с дублонами, там примерно по пятьдесят тысяч на всех. И записка. «Простите, поделите это и забудьте про 'Урку' и Флинта. Так нужно. Всё равно вам не понять. Ф.»";
			link.l1 = "Чертов ханжа! А я почти поверил"+ GetSexPhrase("ся","ась") +" в его 'дружбу'. Где остальные?";
			link.l1.go = "BS_F3_4";
		break;

		case "BS_F3_4":	//Максин
			dialog.text = "Элеонора в резиденции, с ней Рекхэм и Бонни, все трое злые как черти. Постоянно что–то бьют и орут друг на друга. Вейн как только встал на ноги, поднял паруса и умчался куда-то";
			link.l1 = "Думаю, в резиденцию пока лучше не соваться. Пойду, подышу воздухом.";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: «Трудно думать, когда тебя постоянно тошнит. Но нужно что-то делать. Попробую подключить разведку. Какой там пароль? На Антигуа! В путь».

		//В таверну Сен Джонса посадить непися, который отзовётся на пароль

		//На Антигуа, идём в таверну и начинаем донимать нпс паролем «Рыбалка удалась». Ответы в духе: «Пойди проспись!», «Закусывать надо!», «Что? О чем вы?».

		//Нужный непись:

		case "BS_F3_5":	//Агент
			dialog.text = "";
			link.l1 = "Рыбалка удалась!";
			link.l1.go = "BS_F3_6";
		break;

		case "BS_F3_6":	//Агент
			dialog.text = "Улов просто ...?";
			link.l1 = "Нет улова, удрал лосось, или угорь. Тунец? К чертям ваши игры! Есть разговор!";
			link.l1.go = "BS_F3_7";
		break;

		case "BS_F3_7":	//Агент
			dialog.text = "Кхгм. Что же… Слушаю вас.";
			link.l1 = "Организуйте мне встречу с вашим начальством. Срочно. Рыбка может совсем из рук выскользнуть, если вы понимаете, о чем я!";
			link.l1.go = "BS_F3_8";
		break;

		case "BS_F3_8":	//Агент
			dialog.text = "У меня нет таких полномочий, но информацию я передам. Как выйти с вами на связь?";
			link.l1 = "Я буду заглядывать в эту  таверну, время от времени.";
			link.l1.go = "BS_F3_9";
		break;

		case "BS_F3_9":	//Агент
			dialog.text = "Прекрасно, если не застанете меня на месте, обратитесь к подавальщице";
			link.l1 = "Хорошо, но передайте, что время дорого. Всех благ!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Весточку отправил(ла). Нужно вернуться на Бермуды и поискать Вейна. Как бы он дров не наломал".
		//Плывём на Бермуды. В резиденции Гатри, Бонни, Рекхэм.


		case "BS_F3_10":	//Гатри начинает диалог.
			dialog.text = "Наш"+ GetSexPhrase("ел","ла") +" Вейна?";
			link.l1 = "Нет. Есть идеи, куда он умчался?";
			link.l1.go = "BS_F3_11";
		break;

		case "BS_F3_11":	//Рэкхэм.
			dialog.text = "Сказал, что вытряхнет из чёрных образин душу, поставил мне синяк под глазом и был таков";
			link.l1 = "Образин? Всё интереснее и интереснее!";
			link.l1.go = "BS_F3_12";
		break;

		case "BS_F3_12":	//Бонни.
			dialog.text = "Флинт вёл какие-то дела с беглыми рабами. Возможно он сейчас у них";
			link.l1 = "Есть тут хоть кто-то, с кем у него нет связей и дел?";
			link.l1.go = "BS_F3_13";
		break;

		case "BS_F3_13":	//Гатри.
			dialog.text = "Он забил им головы идеей о свободном государстве в Новом Свете. Равные права, нет господ, мир и счастье. На деле же, использует их как пушечное мясо/NЯ говорила, что Флинт – человек жестокий и рациональный? Идеалистом его никак назвать нельзя, а тот, кто поверит его пламенным речам – станет инструментом, не более";
			link.l1 = "(Про себя) Думаю пока не стоит им знать о моём договоре с Бонсом. (Обращаясь ко всем) Джэк, Энн. Вы остались на берегу? Предлагаю вам места в моей команде. Найдём Чарльза, разберёмся с рабами, поищем следы Флинта по их укрытиям";
			link.l1.go = "BS_F3_14";
		break;

		case "BS_F3_14":	//Рэкхэм.
			dialog.text = "Мы бы с удовольствием, но Энн беременна. Я купил тут за гроши старую шхуну, мастер Алексус взялся её подлатать за спасибо. В общем, мы решили пока отойти от дел. Осядем в Чарльзтауне у отца Энн. Займусь каботажными перевозками, ну и так, промыслом по мелочи";
			link.l1 = "Вот, тут немного. Для молодой семьи, так сказать. Кхм… И не смейте отказываться! Что же. Удачи вам троим. Не пропадайте из виду."; //отдаём 75к
			link.l1.go = "BS_F3_15";
		break;

		case "BS_F3_15":	//Гатри.
			dialog.text = "Благородный жест! Но к делу. Рабы беглые, в джунглях прячутся, их буканьеры подкармливают. А значит искать их нужно или на Кубе, или на Эспаньоле. Но зачем тебе сдался Вейн? Пиратское братство? Я бы стала искать по представителям голландской Вест – Индской компании";
			link.l1 = "У нас с Вейном, есть дело незаконченное. Никаких сантиментов. А при чем тут голландские торгаши?";
			link.l1.go = "BS_F3_16";
		break;

		case "BS_F3_16":	//Гатри.
			dialog.text = "У Флинта – узнаваемый корабль и несколько тонн испанского золота. Было бы логично разделить груз на части и отправить торговыми галеонами под военной охраной куда угодно. В Каролину, например или вообще в Бостон. Не удивлюсь, если в этом замешан мой дражайший папочка";
			link.l1 = "Стоит проверить и это. Спасибо. Ещё что-нибудь?";
			link.l1.go = "BS_F3_17";
		break;

		case "BS_F3_17":	//Гатри.
			dialog.text = "Максин. Увези её отсюда. Если нужно будет, то силой!";
			link.l1 = "Вот как? Хорошо. Займусь поисками. В каком направлении – понятия не имею. Слишком много вводных. До встречи";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Возможное участие отца Элеоноры? Вест-Индская торговая компания? Джек и Энн – благочестивые плантаторы? Беглые рабы и ссора Элеоноры с Макс. Ах да, ещё британская военная разведка. Не хватает только мстительных испанцев, проклятого сокровища и древнего бога местных дикарей! Ну, начнем с простого. Макс. Проверю таверну"
		//Идём в таверну. Говорим с Макс.

		case "BS_F3_18":	//Максин.
			dialog.text = "Она требует, что бы я убралась с её острова! Да после всего, что у нас было! Я…";
			link.l1 = "Тссс. Знать не желаю, что там у вас было. Я отправляюсь на поиски наших денег и мне пригодятся твои таланты по добыче информации. Поэтому, на борт! Без возражений!";
			link.l1.go = "exit";
		break;

		//Макс в пассажиры. Выходим в море.
		//Запись в СЖ: "Доставлю Максин в Порт Рояль, пусть собирает слухи. А после решу, что делать дальше"
		//Отвозим Макс в ПР. Диалог на причале.

		case "BS_F3_19":	//Максин. Вариант с отказом от секаса.
			dialog.text = "Знаешь, мы через столько прошли уже вместе, а так и не познакомились поближе. Может, отложим на вечер все дела и проведём его за бутылкой хорошего вина?";
			link.l1 = "Мне вино поперёк горла станет, если понимаешь о чем я. Сначала дело – развлечения потом! Без обид.";
			link.l1.go = "BS_F3_20";
		break;

		case "BS_F3_20":	//Максин.
			dialog.text = "Никаких обид. До свидания капитан!";
			link.l1 = "(Про себя) А может...? Нет! Время не терпит!";
			link.l1.go = "exit";
		break;

		case "BS_F3_21":	//Максин. Вариант с секасом.
			dialog.text = "Знаешь, мы через столько прошли уже вместе, а так и не познакомились поближе. Может, отложим на вечер все дела и проведём его за бутылкой хорошего вина?";
			link.l1 = "Заманчивое предложение! Только от вина меня воротит, если понимаешь о чем я. Как насчет рома";
			link.l1.go = "BS_F3_22";
		break;

		case "BS_F3_22":	//Максин. Вариант с секасом.
			dialog.text = "Пусть будет ром! Идём же!";
			link.l1 = "Идём! У как раз с собой есть пара-тройка бутылок!"; //ТП в бордель, картинка с потрахушками.
			link.l1.go = "exit";
		break;

		//В обоих вариантах запись в СЖ: "Итак, я на перепутье. Искать Вейна и лагеря беглых рабов? Или узнать, чем может помочь британский флот? Или стоит проверить версию Элеоноры с торгашами? Распыляться не стоит, банально не хватит времени на всё сразу. Отмету голландцев сразу, пусть и логично звучит, но у Компании своя разведка есть, и Флинт немало им крови попортил. Значит поиски Вейна или помощь флота. Пора решать!"
		//Тут опять выбор. Одно блочит другое.
		//Ниже вариант помощи разведке и Бонсу.
		//Плывём на Антигуа, в локации острова запись в СЖ: "Вейн – большой мальчик, надеюсь, дров не наломает. Проверю таверну. Агент говорил, что если его не будет на месте, спросить разносчицу"

		case "BS_F3_23":	//Офицантка.
			dialog.text = "Вам что-нибудь принести, капитан?";
			link.l1 = "Нет. Дорогуша, ты не видела тут моего друга? Он большой любитель рыбалки, мы тут выпивали не так давно?";
			link.l1.go = "BS_F3_24";
		break;


		case "BS_F3_24":	//Офицантка.
			dialog.text = "Охотитесь за крупной рыбой? Он просил передать, что другой рыбак, будет ждать вас в водах Доминики у пляжа Касл Брус";
			link.l1 = "Спасибо. Вот тебе на эмм..., на что-нибудь красивое!"; //Отдаём 500 рублей
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Сбор рыбаков у Доминики. Нужно поспешить".
		//У пляжа стоит фрегат Бонса. Если решим пострелять - провал линейки. Высылаем шлюпку, разговор с Бонсом на борту.

		case "BS_F3_25":	//Бонс.
			dialog.text = "Вам бы память тренировать, капитан. Правильный пароль иногда может жизнь спасти!";
			link.l1 = "Мне плевать на ваши игры в пароли и явки. Я по делу! Флинт скрылся! Вместе с кораблём и золотом. Мы чудом выжили! По своим каналам, я зацепок не имею. Выкладывай, что есть у тебя. Может быть, вместе и поймаем твою рыбку. После чего разбежимся!";
			link.l1.go = "BS_F3_26";
		break;


		case "BS_F3_26":	//Бонс.
			dialog.text = "А как же почести? Награда? Помилование, наконец?";
			link.l1 = "На золото ‘Урки’, я себе хоть титул купить смогу. А благосклонность короны тоже покупается. Не томи, Билли. У меня руки чешутся кого-нибудь прирезать!";
			link.l1.go = "BS_F3_27";
		break;

		case "BS_F3_27":	//Бонс.
			dialog.text = "Начну издалека. ‘Скарборо’ и остальная эскадра, тут не только и не, сколько для поимки Флинта и устрашения пиратов. Первоочередная задача – не дать попасть золоту с ‘Урки’ в Европу. Испания легко погасит часть своих долгов этим золотом, а это лишит влияния на них, их кредиторов. К тому же, такое количество уже отчеканенной монеты – обесценит уже имеющиеся. Так что, если золото исчезнет на Карибах – это даже лучше. То есть, никто в Европе, его искать не станет, и заявлять права на него – тоже";
			link.l1 = "Понимаю. Политика, интриги, заговоры. Старушка Европа, всё никак не угомониться.";
			link.l1.go = "BS_F3_28";
		break;

		case "BS_F3_28":	//Бонс.
			dialog.text = "Мой формальный командир, Сэр Френсис Ньюм, капитан ‘Скарборо’, напыщенный болван, сын какого-то мелкого лордика. Раздаёт налево-направо патенты и помилования, вербует сторонников. Ищет, тоже, что и вы и, подозреваю, мои неудачи – его рук дело. У меня есть все основания полагать, что золото он прибрать к рукам собирается";
			link.l1 = "Я нить теряю, Билл. Флинт, золото. Чем ты можешь мне помочь?";
			link.l1.go = "BS_F3_29";
		break;

		case "BS_F3_29":	//Бонс.
			dialog.text = "Есть непроверенная информация о стоянках ‘Моржа’ в разных бухтах. Возможности проверить их быстро – у меня нет. Поэтому, разделимся. Я пойду к мысу Каточе и под испанским флагом двину на юг. Ты – к бухте Бока де ла Сьерпе, и пойдёшь оттуда на запад, проверяя каждую бухту. Встречаемся у лагуны Чирике. В порты не входить, столкновений избегать. Начиная с этого дня, двух недель должно хватить";
			link.l1 = "Ты сказал, что есть конкретная информация о стоянках! Это же нужно каждую бухту осмотреть!";
			link.l1.go = "BS_F3_30";
		break;

		case "BS_F3_30":	//Бонс.
			dialog.text = "Информатор был не очень точен в описаниях и быстро умер. Ньюм, мало того, что кретин, ещё и садист.";
			link.l1 = "Стало быть, Ньюм тоже ищет стоянки?";
			link.l1.go = "BS_F3_31";
		break;

		case "BS_F3_31":	//Бонс.
			dialog.text = "Скоро начнёт. На днях прибыл курьерский бриг из метрополии и ‘Скарборо’ снялся с якорей. Какие приказы получил Ньюм, я не знаю. Но это даёт нам фору.";
			link.l1 = "Значит, не будем медлить!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "От Бонса-Блэкхема проку немного, нужно исследовать большой кусок побережья Мэйна. Но это хоть что-то. Начну с бухты Бока де ла Сьерпе"
		//В бухте Бока де ла Сьерпэ, на берегу пусто. Запись в СЖ: "Пусто. Продолжу поиски. Нужно исключить бухты, которые находятся в виду фортов, Флинт не стал бы так рисковать. Сверюсь с картой. Ага, остаются: Пляж Лос Текес, бухта Гуахира, бухта Ковеньяс, залив Москитос. Что же, в путь."
		//В Лос Текес – пара агрессивных английских фрегатов. Бой. Высадка. На берегу штук 30 военных – файт. Запись в СЖ: "Похоже люди Ньюма. Ищут зацепки на месте гибели ‘Урки’. Нужно быть настороже".
		//Москитос. На берегу подбегает матрос.

		case "BS_F3_32":	//Матрос.
			dialog.text = "Капитан " + GetFullName(pchar) + "? Я от коллеги по рыбалке!";
			link.l1 = "Билли всё никак не наиграется? Что там у тебя?";
			link.l1.go = "BS_F3_33";
		break;

		case "BS_F3_33":	//Матрос.
			dialog.text = "Срочно прибудьте в Бриджтаун! Поиски потерпят. Так он сказал.";
			link.l1 = "И это всё? Что за срочность?";
			link.l1.go = "BS_F3_34";
		break;


		case "BS_F3_34":	//Матрос.
			dialog.text = "Понятия не имею"+ GetSexPhrase("сэр","мэм") +", я просто посыльный!" ;
			link.l1 = "Хорошо, я понял"+ GetSexPhrase("","а") +".";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Что-то произошло. Бонс требует срочно прибыть в Бриджтаун."
		//Плывём на Барбадос. В городе подходит Бонс.

		case "BS_F3_35":	//Бонс.
			dialog.text = "Ты здесь. Хорошо. Власти Барбадоса просят помощи, их гарнизон до сих пор не укомплектован, после набега испанцев. И ‘Скарборо’ неизвестно где" ;
			link.l1 = "Что стряслось то? Я, кстати, наткнул"+ GetSexPhrase("ся","ась") +" на пляже Лос-Текес на людей Ньюма. Рылись в обломках ‘Урки’";
			link.l1.go = "BS_F3_36";
		break;

		case "BS_F3_36":	//Бонс.
			dialog.text = "Много они там не нароют. На плантации, расположенные на острове, планируется нападение. Сегодня, завтра, скоро. И возглавит нападение, не поверишь кто. Сам Флинт!" ;
			link.l1 = "За каким дьяволом ему это нужно?";
			link.l1.go = "BS_F3_37";
		break;

		case "BS_F3_37":	//Бонс.
			dialog.text = "Где-то в колониях он создаёт армию из каторжан и беглых рабов, а тут королевская каторга. Головорезы всех мастей, вооружай и готово.  Вот для чего ему испанское золото. И делиться им, он не намерен. В местном гарнизоне одни новобранцы и ополчение из колонистов. Они разбегутся кто-куда при первых залпах. Но если мы объединим наши команды, то сможем дать ему отпор и, даст бог, схватить его самого!" ;
			link.l1 = "Устроим засаду? Что же, это может сработать. Собирай людей, встретимся на плантации!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Предстоит жаркое дельце. Флинт собирается освободить каторжан для своей армии. Отличная возможность прихлопнуть ублюдка. Но, всё же стоит помнить, с кем мы имеем дело. Устроим засаду на плантации".
		//Идём на плантацию. Там бродят наши в перемешку с английскими солдатами, заходим за калитку плантации. Вывести лог «Засада организована! Всем быть на готове!» Начинаем спаунить пиратов от ворот. В три-четыре волны.
		//Перебили всех, Бонс орёт : «Они с полей прут, ещё больше! Стрелки, к бою!»

		case "BS_F3_38":	//Бонс.
			dialog.text = "Они с полей прут, ещё больше! Стрелки, к бою!" ;
			link.l1 = "За мной!";
			link.l1.go = "exit";
		break;

		//Спауним пиратов прям на плантации. Перебили.


		case "BS_F3_39":	//Бонс.
			dialog.text = "Где, черт его дери Флинт?" ;
			link.l1 = "Это ещё не конец! Слышишь? Пушки стреляют! Ложись!";
			link.l1.go = "exit";
		break;

		//Нужна пара взрывов где-нибудь. От ворот ещё толпа пиратов. С ними Флинт и Вейн. Пока живы их пираты - Ф и В бессмернтые. Как только полегли все пираты Флинт начинает диалог.

		case "BS_F3_40":	//Флинт.
			dialog.text = "Вейн! Отступаем, идут подкрепления из форта!" ;
			link.l1 = "Я прикрою, уходи!"; //Вейн
			link.l1.go = "BS_F3_41";
		break;


		case "BS_F3_40":	//Флинт.
			dialog.text = "Я понимаю. "+pchar.name+" ты не на той стороне сражаешься! Но это твой выбор." ; //Убегает.
			link.l1 = "Я за Флинтом. Нельзя его упустить!"; //Бонс. Убегает.
			link.l1.go = "BS_F3_41";
		break;

		case "BS_F3_41":	//Вейн.
			dialog.text = "Ну что? Только ты и я?!" ;
			link.l1 = "Какого черта Чарьз? У нас же был уговор!";
			link.l1.go = "BS_F3_42";
		break;

		case "BS_F3_42":	//Вейн.
			dialog.text = "Ты слишком часто меняешь стороны. А твои новые друзья убили Элеонору!" ;
			link.l1 = "Как?! Когда?";
			link.l1.go = "BS_F3_43";
		break;

		case "BS_F3_43":	//Вейн.
			dialog.text = "’Скарборо’ пришёл на Бермуды, пока я искал Флинта и устроил там зачистку. Элеонору отвезли в цепях в Порт Роял и повесили в порту. Максин в тюрьме и её скоро тоже повесят. Джэк – в тюрьме Чарльзтауна, но он выкрутится. Энн помилована. Гуманный суд решил, что вешать беременную женщину, хоть и пирата – это через чур. А ты стал" + GetSexPhrase("","а") +" собачкой,  вынюхивающей испанское золото для английской разведки" ;
			link.l1 = "Тебе это Флинт рассказал? Он умеет играть с мозгами!";
			link.l1.go = "BS_F3_44";
		break;

		case "BS_F3_44":	//Вейн.
			dialog.text = "Я видел её тело. Её в клетку поместили, чтоб не развалилась при разложении. Так и висит возле пристани. Хватит болтать! Отсюда кто-то один уйдёт!" ;
			link.l1 = "В этом нет моей вины, Чарльз. Но тебя не переубедить. Начинай как будешь готов!";
			link.l1.go = "exit";
		break;

		//Рубимся с Вейном. Убиваем. Страдаем, какой автор гнида. Идём в город. Подбегает Сильвер.

		case "BS_F3_45":	//Сильвер.
			dialog.text = "Эй "+pchar.name+", на тебе лица нет! Что там было? Это Флинт?" ;
			link.l1 = "Заткнись, Джон. Как ты тут очутился?";
			link.l1.go = "BS_F3_46";
		break;

		case "BS_F3_46":	//Сильвер.
			dialog.text = "Удрал от Флинта, когда он начал хвосты подчищать. Всю старую команду вырезал!" ;
			link.l1 = "Я думаю нагнать его в море. Ты со мной?";
			link.l1.go = "BS_F3_47";
		break;

		case "BS_F3_47":	//Сильвер.
			dialog.text = "Флинта?! Нет! Да! Да, думаю, с тобой безопаснее будет. Я тут у шлюх под юбками прячусь уже неделю!" ;
			link.l1 = "Тогда в море!";
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Вейн. Черт тебя дери. Ты был мне другом! И Бонс, чертов Бонс. Пока я искал(ла) непойми что, англичане устроили зачистку. Гатри мертва. Всё катиться в бездну! Осталось поквитаться с Флинтом и плевать, что будет дальше!"
		//Выходим в море, нас атакует «Рейнджер». Топим. Выходим на глобалку. От нас по съёбам удирает квестовик-энка (типо Флинт с Бонсом). Нужно скорости им накрутить, чтоб мы только-только угнаться могли. Энка пиздует к мысу Каточе и там исчезает. Выходим на локалку. Там фрегат Бонса гасится с Моржом (Бонс зелёненький). Берём Моржа на абордаж. В каюте рубилово с Флинтом. Нулим Флинта. Диалог


		case "BS_F3_48":	//Флинт.
			dialog.text = "Вейн мёртв? Жаль, но он был слишком эмоционален. А ты принял" +GetSexPhrase("","а")+" предложение английских властей? Помилование, патент, королевские милости? Ты же понимаешь, что они легко дают обещания и так же легко забирают их обратно. Я был одним из них!" ;
			link.l1 = "…";
			link.l1.go = "BS_F3_49";
		break;

		case "BS_F3_49":	//Флинт.
			dialog.text = "Вот только не нужно жечь меня взглядом. На меня это не действует.  Есть ещё способы всё уладить. Захватим фрегат Бонса, далее под английскими флагами и с помощью его сигнальной книги, заманим в ловушку ‘Скарборо’. Таким образом, избавимся от внимания военной разведки, у них сейчас и без нас забот полон рот. Далее …" ;
			link.l1 = "Вот так у тебя голова устроена? Планы, внутри планов? Нет друзей, нет врагов. Есть только инструменты и помехи. Ты вообще человек?";
			link.l1.go = "BS_F3_50";
		break;

		case "BS_F3_50":	//Флинт.
			dialog.text = "Эмоции неуместны, мораль – признак слабости, компромиссы – путь к посредственности. Мои цели – новый мир. А что бы построить новый, нужно сломать старый. Ты мог" + GetSexPhrase("","ла") +" бы быть полезным инструментом, но я вижу иррациональные чувства, которые помешают твоей эффективности. Так и быть. Это будет чуточку труднее, но нет ничего невозможного!" ;
			link.l1 = "Просто заткнись и сдохни!";
			link.l1.go = "exit";
		break;

		//Файт. На трупе Нарвал, книга Марк Аврелий «Размышления». В сундуке 5кк денег, судовой журнал Флинта (зашифрованый).
		//Как только закрываем окно захвата корабля - СЮРПРИЗ. Спаун "Скарборо" с парой фрегатов. Бой, без диалогов в случае захвата.
		//После победы ТП на берег. Фрегат Бонса удаляем, он потонул. На берегу Бонс, Сильвер, ГГ.

		case "BS_F3_51":	//Сильвер.
			dialog.text = "Флинт мёртв?" ;
			link.l1 = "Мёртв.";
			link.l1.go = "BS_F3_52";
		break;

		case "BS_F3_52":	//Бонс.
			dialog.text = "Хех. Жаль. Живым его в Лондоне очень рады были бы видеть" ;
			link.l1 = "После всего, что было, думаю ТЕБЕ, в Лондоне будут тоже рады!";
			link.l1.go = "BS_F3_53";
		break;

		case "BS_F3_53":	//Бонс.
			dialog.text = "Думаю, да. Френсис Ньюм, эсквайр, погиб как герой, а какой-то коммандер – выжил. Мне совсем не хочется отвечать на вопросы, которые возникнут!" ;
			link.l1 = "Вы, двое! Вот бумаги Флинта, зашифрованные. Разберётесь? А я тут прилягу и отдохну. Устал" + GetSexPhrase("","а")+" убивать."; //Отдаём книгу, журнал.
			link.l1.go = "exit";
		break;

		//Запись в СЖ: "Где то на этом пути я сделал(ла) неправильный выбор. Какой момент стал поворотным? Элеонора, Джек, Чарльз. Как бы сложились их судьбы, прими я другие решения? Стал(ла) бы я бездушной машиной под руководством Флинта? Черт, как голова болит! Нужно отдохнуть".
		//Ставим табличку "Прошло десять часов", мотаем время.

		case "BS_F3_54":	//Сильвер.
			dialog.text = "Эй! Ты жив" + GetSexPhrase("","а") +"? Храпеть ты мастер!" ;
			link.l1 = "Что? Как успехи?";
			link.l1.go = "BS_F3_55";
		break;

		case "BS_F3_55":	//Бонс.
			dialog.text = "Два листа координат. Широта, долгота. Всё. Никаких “Семь шагов от засохшего дерева’, ничего!" ;
			link.l1 = "Как думал этот дьявол, как у него голова устроена – это непостижимо.";
			link.l1.go = "BS_F3_56";
		break;

		case "BS_F3_56":	//Бонс.
			dialog.text = "Возможно это маршрут? Только где начало и конец? Тут сотни точек на карте! Должна быть связь! Должна! Нужно только подумать, перечитать чертову книгу, должно что-то быть!" ;
			link.l1 = "Куда вас доставить?";
			link.l1.go = "BS_F3_57";
		break;

		case "BS_F3_57":	//Сильвер.
			dialog.text = "Что? Ты сдаёшься?" ;
			link.l1 = "Пуэрто-Принсибе? Мы недалеко от Кубы.";
			link.l1.go = "BS_F3_58";
		break;

		case "BS_F3_58":	//Бонс.
			dialog.text = "Да, Куба подойдёт. У меня есть тайничок там. На первое время хватит." ;
			link.l1 = "Тогда в путь";
			link.l1.go = "exit";
		break;

		//Везём братву на Кубу. В бухте Пуэрто Присибе подходит Сильвер.


		case "BS_F3_59":	//Сильвер.
			dialog.text = "Я присмотрю за Билли, сдаётся мне, он  не в себе. А ты куда?" ;
			link.l1 = "Попытаюсь спасти Макс. Хоть что-то сделаю правильно. Удачи, Джон!";
			link.l1.go = "exit";
		break;

		//Плывём в Порт Рояль, идём в тюрягу, комендант.

		case "BS_F3_60":	//Комендант.
			dialog.text = "Вы по какому вопросу?" ;
			link.l1 = "Я хотел" +GetSexPhrase("","а")+" поинтересоваться судьбой одной особы. Максин.";
			link.l1.go = "BS_F3_61";
		break;

		case "BS_F3_61":	//Комендант.
			dialog.text = "Ааа, мадам! Всё с ней в порядке. Подержали в клетке пару дней, потом пришёл посыльный от самого губернатора с помилованием. И отпустили с Богом!" ;
			link.l1 = "Благодарю вас.";
			link.l1.go = "exit";
		break;

		//Идём в бордель. Комната мадам.

		case "BS_F3_62":	//ГГ
			dialog.text = "Я и не надеял" +GetSexPhrase("ся","ась")+" увидеть тебя живой!" ;
			link.l1 = "Мой капитан! Пока мои девочки собирают слухи, мне ничего не грозит. Я щедро делюсь ими и с властями, и с корсарами. Каждый готов постоять за меня.";
			link.l1.go = "BS_F3_63";
		break;

		case "BS_F3_63":	//ГГ.
			dialog.text = "Что же. Тогда моя миссия завершена. Вот, твоя доля, компаньон. Здесь всё, что удалось обнаружить из золота ‘Урки’" ; //отдаём 2.5кк
			link.l1 = "Не стану отказываться. Тем более предстоят расходы. Я добилась разрешения похоронить по человечески Элеонору. И вышлю денег Энн. Ты слышал" + GetSexPhrase("","а") +" про Джека?.";
			link.l1.go = "BS_F3_64";
		break;

		case "BS_F3_64":	//ГГ.
			dialog.text = "Да. Флинт мёртв, Вейн  мёртв." ;
			link.l1 = "История подошла к концу?";
			link.l1.go = "BS_F3_65";
		break;

		case "BS_F3_65":	//ГГ.
			dialog.text = "Эта истори, да. Есть ещё много не рассказанных историй. Прощай Макс!" ;
			link.l1 = "Навещай меня, капитан, время от времени.";
			link.l1.go = "exit";
		break;

		//Уходим в закат. Макс – остаётся в роли мадам, с бесплатными потрахушками. Можно ей добавить слухов по «Лёгкой добыче».
		//На выходе из борделя – подбегает Сильвер


		case "BS_F3_66":	//Сильвер.
			dialog.text = "Бонс нашёл связь!!! Это и в правду маршрутные точки! И только у него есть карта!" ;
			link.l1 = "Карта острова сокровищ капитана Флинта?";
			link.l1.go = "BS_F3_67";
		break;


		case "BS_F3_67":	//Сильвер.
			dialog.text = "Да! Но он удрал. Растворился. Исчез вместе с картой! Нужно найти его!" ;
			link.l1 = "Это уже твоя история, Джон. Вот тебе немного. Купи себе лоханку и гонись за Билли Бонсом хоть в Англию!"; //отдаём 25к
			link.l1.go = "BS_F3_68";
		break;

		case "BS_F3_68":	//Сильвер.
			dialog.text = "Но… Ты уверен" +GetSexPhrase("","а")+"?! Вижу, что,  да. Я найду тебя, обязательно! Ох и попируем мы на денюжки Флинта!" ;
			link.l1 = "Проваливай Сильвер!";
			link.l1.go = "exit";
		break;

		//Квест уходит в архив.

}


}
