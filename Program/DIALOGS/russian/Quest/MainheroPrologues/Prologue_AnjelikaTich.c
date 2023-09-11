void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	ref _location;
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
		
		case "First time":								//Авторы: Nikk и Sinistra
			dialog.text = "";
			link.l1 = "Бекки, эта комната скоро превратится в келью.";
			link.l1.go = "Rebekka_v_komnate_2";
		break;
		
		case "Rebekka_v_komnate_2":
			dialog.text = "Не начинай, я уже знаю, чем снова закончится наш разговор.";
			link.l1 = "Я была в порту, там корабль из Гаваны. Военный... Прибыл новый комендант, которого назначили на место нашего отца. Мне удалось с ним поговорить и описать со всей прямотой то непростое положение, в котором мы оказались.";
			link.l1.go = "Rebekka_v_komnate_3";
		break;
		
		case "Rebekka_v_komnate_3":
			dialog.text = "Думаю, это было не очень тактично с твоей стороны. Стоило сначала пригласить его на обед, в конце концов, этот дом совсем скоро станет его домом. Мы бы показали комнаты, решили вопрос с мебелью и некоторыми вещами.";
			link.l1 = "У нас ещё будет время! Комендант любезно дал отсрочку на целых четыре месяца. Четыре чёртовых месяца, чтоб подыскать тебе партию, и я буду спокойна за твою судьбу, сестрица.";
			link.l1.go = "Rebekka_v_komnate_4";
		break;
		
		case "Rebekka_v_komnate_4":
			dialog.text = "Вот пожалуйста, на этот раз у тебя вышло как никогда короткое предисловие, прежде чем ты перешла к сути.";
			link.l1 = "На корабле достаточно кандидатур. Знатные молодые офицеры присутствуют и при параде! Парочка из сошедших с первой шлюпки очень даже недурны собой. Пойдём, обозначим своё присутствие, пока они не попрятались в свои казарменные норы от полуденной жары.";
			link.l1.go = "Rebekka_v_komnate_5";
		break;
		
		case "Rebekka_v_komnate_5":
			dialog.text = "Присмотри кого-нибудь и ты для себя...";
			link.l1 = "";
			link.l1.go = "Rebekka_v_komnate_5_1";
		break;
		
		case "Rebekka_v_komnate_5_1":
			dialog.text = "";
			link.l1 = "Нет уж, я планирую покинуть наконец эту дыру, как только пристрою тебя в надёжные руки. Даром что ли я на протяжении последних лет осваивала искусство навигации и училась читать карты? Наймусь штурманом на корабль, отправлюсь на встречу приключениям. Ха-хах! У меня больше шансов стать штурманом, чем у этих малограмотных недорослей-аристократов, которых укачивает от одного вида палубы.";
			link.l1.go = "Rebekka_v_komnate_6";
			locCameraToPos(1.00, 4.00, 9.00, false);
		break;
		
		case "Rebekka_v_komnate_6":
			dialog.text = "Анжелика, один из этих малограмотных недорослей-аристократов, возможно, мой будущий муж, так кажется, да? А ты скорее отправишься на встречу смерти, а не приключениям. Ты женщина и...";
			link.l1 = "Э-эй! Во мне течёт кровь Тичей, не Ремедиос! Не забывай, кто мой настоящий отец.";
			link.l1.go = "Rebekka_v_komnate_7";
		break;
		
		case "Rebekka_v_komnate_7":
			dialog.text = "Конечно, я помню. Моя мачеха - русалка, променявшая ноги на голос, не раз рассказывала эту историю, как вы без малого год не ступали на твёрдую землю, носясь по всему архипелагу в поисках добычи.";
			link.l1 = "Право, как это весело. Если ты теми же словами перескажешь нашу притчу своему будущему кавалеру, он наверняка оценит, не только твою красоту, но и остроту ума.";
			link.l1.go = "Rebekka_v_komnate_8";
		break;
		
		case "Rebekka_v_komnate_8":
			dialog.text = "Ты сама начала этот разговор.";
			link.l1 = "Я его и закончу. Догоняй.";
			link.l1.go = "Rebekka_v_komnate_9";
		break;
		
		case "Rebekka_v_komnate_9":
			DialogExit();
			EndQuestMovie();
			bDisableCharacterMenu = false;
			pchar.SystemInfo.ChangePIRATES = true;
			LaunchCharacter(pchar);
			
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			
			PChar.quest.At_pr_Rebekka_gulyat.win_condition.l1 = "location";
			PChar.quest.At_pr_Rebekka_gulyat.win_condition.l1.location = "LaVega_town";
			PChar.quest.At_pr_Rebekka_gulyat.function = "At_pr_Rebekka_gulyat";
			
			sld = CharacterFromID("Edward Mansfield")
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
			
			//Испанский губернатор
			sld = GetCharacter(NPC_GenerateCharacter("AT_pr_LaVegaIspanski_Gubernator", "SpaOfficer1", "man", "man", 15, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, 100, 100, 100, "blade20", "howdah", 500);
			sld.name	= "Аурелио";
			sld.lastname	= "Серрано";
			sld.SaveItemsForDead = true;
			sld.Dialog.Filename = "Quest\MainheroPrologues\Prologue_AnjelikaTich.c";
			sld.dialog.currentnode = "LaVegaIspanski_Gubernator";
			LAi_SetHuberType(sld);
			LAi_SetImmortal(sld, true);
			DeleteAttribute(sld, "items");
			AddMoneyToCharacter(sld, 12345);
			GiveItem2Character(sld, "blade19");
			EquipCharacterByItem(sld, "blade19");
			GiveItem2Character(sld, "BackPack2");
			GiveItem2Character(sld, "talisman6");
			AddItems(sld, "jewelry4", 30);
			ChangeCharacterAddressGroup(sld,"LaVega_townhall","sit","sit1");
			
			//Торговец на улице (продолжение квеста)
			FreeSitLocator("LaVega_town", "protector2");
			sld = GetCharacter(NPC_GenerateCharacter("Gasten_Kotes", "shipowner_13", "man", "man", 1, SPAIN, -1, false));
			FantomMakeCoolFighter(sld, 1, 10, 10, "blade3", "", 10);
			sld.name	= "Гастен";
			sld.lastname	= "Котес";
			SetCharacterPerk(sld, "Trader");
			SetCharacterPerk(sld, "BasicCommerce");
			SetSPECIAL(sld, 6, 4, 8, 8, 10, 6, 7);
			SetShipSkill(sld, 27, 45, 21, 14, 18, 21, 13, 9, 28);
			TakeNItems(sld,"potion1", -10);
			TakeNItems(sld,"potion2", -10);
			sld.Dialog.Filename = "Quest\MainheroPrologues\Prologue_AnjelikaTich.c";
			sld.dialog.currentnode = "Torgovets_1";
			LAi_SetStayType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld,"LaVega_town","merchant","merchant3");
			sld.talker = 5;
			
			//Девушка на улице (продолжение квеста)
			sld = GetCharacter(NPC_GenerateCharacter("AT_pr_devushka_na_rynke", "CitizenWom_2", "woman", "woman", 10, SPAIN, -1, false));
			sld.name	= "София";
			sld.lastname	= "де ла Пьедад";
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld,"LaVega_town","merchant","mrcActive3");
			
			//Какой-то мужик со шляпой
			sld = CharacterFromID("Old Friend")
			sld.Dialog.Filename = "Quest\MainheroPrologues\Prologue_AnjelikaTich.c";
			sld.dialog.currentnode = "man_shlyapa";
			DeleteAttribute(sld, "talker");
		break;
		
		case "LaVegaIspanski_Gubernator":
			dialog.text = "Сеньорита Ремедиос? Мы с вами всё обсудили. Моё решение в силе, вам не о чем беспокоиться.";
			link.l1 = "Моя сестра настояла на том, чтобы я пригласила вас на семейный обед.";
			link.l1.go = "LaVegaIspanski_Gubernator_2";
		break;
		
		case "LaVegaIspanski_Gubernator_2":
			dialog.text = "Хм, благодарю. Думаю, буду плотно занят ближайшие несколько дней, но обязательно приму предложение.";
			link.l1 = "Чудесно. Более вас не отвлекаю.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LaVegaIspanski_Gubernator_3";
		break;
		
		case "LaVegaIspanski_Gubernator_3":
			dialog.text = "Снова вы?";
			link.l1 = "Уже ухожу.";
			link.l1.go = "exit";
			NextDiag.TempNode = "LaVegaIspanski_Gubernator_3";
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_1":
			sld = CharacterFromID(pchar.ATP_MirJitId)
			dialog.text = "(к мирному жителю) Мы вышли погулять с моей сестрой, может быть вам нужна какая-нибудь помощь?";
			link.l1 = "";
			link.l1.go = "Rebekka_s_mirnymi_jitelyami_1_1";
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(CharacterFromID("AT_pr_Rebekka"), CharacterFromID(pchar.ATP_MirJitId));
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_1_1":
			DialogExit();
			StartInstantDialog(pchar.ATP_MirJitId, "ATP_1_1", "Common_citizen.c");
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_2":
			sld = CharacterFromID(pchar.ATP_MirJitId)
			dialog.text = "(к мирному жителю) "+sld.name+", благодарю вас за комплимент.";
			link.l1 = "";
			link.l1.go = "Rebekka_s_mirnymi_jitelyami_2_1";
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(CharacterFromID("AT_pr_Rebekka"), CharacterFromID(pchar.ATP_MirJitId));
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_2_1":
			DialogExit();
			StartInstantDialog(pchar.ATP_MirJitId, "ATP_2_1", "Common_citizen.c");
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_3":
			sld = CharacterFromID(pchar.ATP_MirJitId)
			dialog.text = "(смущённо улыбается)";
			link.l1 = "";
			link.l1.go = "Rebekka_s_mirnymi_jitelyami_3_1";
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(CharacterFromID("AT_pr_Rebekka"), CharacterFromID(pchar.ATP_MirJitId));
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_3_1":
			DialogExit();
			StartInstantDialog(pchar.ATP_MirJitId, "ATP_3_1", "Common_citizen.c");
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_4":
			sld = CharacterFromID(pchar.ATP_MirJitId)
			dialog.text = "Нет, Анжелика, вчера с утра было довольно душно.";
			link.l1 = "";
			link.l1.go = "Rebekka_s_mirnymi_jitelyami_4_1";
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(CharacterFromID("AT_pr_Rebekka"), pchar);
		break;
		
		case "Rebekka_s_mirnymi_jitelyami_4_1":
			DialogExit();
			StartInstantDialog(pchar.ATP_MirJitId, "ATP_4_1", "Common_citizen.c");
		break;
		
		case "man_shlyapa":
			dialog.text = "Добрый день! Чем могу я быть вам любезен?";
			link.l1 = "Здравствуйте! У вас чудная шляпа.";
			link.l1.go = "exit";
			NextDiag.TempNode = "man_shlyapa";
		break;
		
		case "Torgovets_1":
			StartQuestMovie(true, true, true);
			dialog.text = "Сеньорита, я не могу отпускать в долг, вы не из местных, а ну как завтра сядете на проходящий корабль и только вас и видели.";
			link.l1 = "";
			link.l1.go = "Torgovets_2";
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("AT_pr_devushka_na_rynke"));
			locCameraToPos(-38.00, 7.00, 20.00, true);
		break;
		
		case "Torgovets_2":
			DialogExit();
			StartInstantDialog("AT_pr_devushka_na_rynke", "Torgovets_3", "Quest\MainheroPrologues\Prologue_AnjelikaTich.c");
		break;
		
		case "Torgovets_3":
			dialog.text = "Но я же не прошу в долг, оплачу две трети цены прямо сейчас, остальное смогу отработать - помочь вам или вашей супруге.";
			link.l1 = "";
			link.l1.go = "Torgovets_4";
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Gasten_Kotes"));
			sld = CharacterFromID("AT_pr_Rebekka")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Gasten_Kotes"));
			
			locCameraSleep(true);
		break;
		
		case "Torgovets_4":
			DialogExit();
			StartInstantDialog("Gasten_Kotes", "Torgovets_5", "Quest\MainheroPrologues\Prologue_AnjelikaTich.c");
		break;
		
		case "Torgovets_5":
			dialog.text = "У меня не то чтобы много работы, со всем прекрасно справляюсь сам, и я не женат. Могу предложить вам две трети товара...";
			link.l1 = "";
			link.l1.go = "Torgovets_6_1";
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("AT_pr_devushka_na_rynke"));
		break;
		
		case "Torgovets_6_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "merchant", "mrcActive3", "", -1);
			DoQuestFunctionDelay("AT_pr_Torgovets_6_2", 1.0);
		break;
		
		case "Torgovets_6_3":
			dialog.text = "";
			link.l1 = "Гастен-лис, разве ты не видишь, у сеньориты на лице отпечаталась нелёгкая судьба, не глядя на её молодость. Прояви же сострадание.";
			link.l1.go = "Torgovets_7";
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "Torgovets_7":
			dialog.text = "Что бы ты понимала в людях, дорогая Анжелика, если в своём отчиме, земля ему пухом, не могла разглядеть негодяя.";
			link.l1 = "Осторожнее Лис, ты же знаешь я могу вспылить из-за сущего пустяка.";
			link.l1.go = "Torgovets_8";
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "Torgovets_8":
			dialog.text = "Сначала смени юбку на брюки, прежде чем бросаться угрозами. За твоей спиной больше не стоит комендант, готовый прикрывать все твои выходки. Это добрый совет, не прими за оскорбление.";
			link.l1 = "У меня и под юбкой кое-чего имеется, это называется сарагоса, давай я тебе покажу, как могу позаботится о себе, заодно дам тебе добрый совет: защищайся!";
			link.l1.go = "Torgovets_9";
		break;
		
		case "Torgovets_9":
			dialog.text = "Не дури.";
			link.l1 = "Защищайся, или смени брюки на юбку!";
			link.l1.go = "Torgovets_10";
		break;
		
		case "Torgovets_10":
			DialogExit();
			
			LAi_SetActorType(pchar);
			
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1);
			chrDisableReloadToLocation = true;
			
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetActorType(sld);
			
			PChar.quest.AT_pr_Draka_s_Kotesom.win_condition.l1 = "location";
			PChar.quest.AT_pr_Draka_s_Kotesom.win_condition.l1.location = "LaVega_ExitTown";
			PChar.quest.AT_pr_Draka_s_Kotesom.function = "AT_pr_Draka_s_Kotesom";
			
			DoQuestFunctionDelay("AT_pr_Torgovets_10_1", 1.0);
		break;
		
		case "Rebekka_posle_draki":
			dialog.text = "Прекрати! Ты же его чуть не убила!";
			link.l1 = "Я всего лишь показала нашему другу, чего стоит язык, когда он длиннее шпаги.";
			link.l1.go = "Rebekka_posle_draki_2";
			
			sld = characterFromId("Gasten_Kotes");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			//LAi_ActorAnimation(sld, "kneeling_2", "", 2.4);
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
		break;
		
		case "Rebekka_posle_draki_2":
			dialog.text = "Молодчина, а теперь помоги его перевязать, и придумай себе оправдание, если не хочешь быть арестованной. ";
			link.l1 = "Не волнуйся, всё обойдётся. Когда этот лис сорвался в джунгли, солдаты чуть не надорвали животы, глядя на это зрелище, а царапина затянется уже через пару часов.  Меня больше волнует, кто эта девушка, откуда. Пройдусь, поищу её.";
			link.l1.go = "Rebekka_posle_draki_3";
		break;
		
		case "Rebekka_posle_draki_3":
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			pchar.questTemp.AnjelikaTichPrologue2 = "ATP2";
			
			PChar.quest.AT_pr_Oba_ischezaut.win_condition.l1 = "ExitFromLocation";
			PChar.quest.AT_pr_Oba_ischezaut.win_condition.l1.location = PChar.location;
			PChar.quest.AT_pr_Oba_ischezaut.function = "AT_pr_Oba_ischezaut";
		
			sld = characterFromId("AT_pr_Rebekka");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromId("Gasten_Kotes"), "", -1);
			
			sld = CharacterFromID("AT_pr_devushka_na_rynke")
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, "LaVega_town", "goto", "goto2");
			sld.dialog.filename = "Quest\MainheroPrologues\Prologue_AnjelikaTich.c";
			sld.dialog.currentnode = "Sofia_1";
			
			DialogExit();
		break;
		
		case "Sofia_1":
			dialog.text = "";
			link.l1 = "Извините, сеньорита, могу я составить вам компанию?";
			link.l1.go = "Sofia_2";
		break;
		
		case "Sofia_2":
			dialog.text = "Конечно... Меня зовут София, София де ла Пьедад, до недавнего времени. Правда не стоило так сурово обходиться с господином.";
			link.l1 = "Господин давно заслужил подобное обращение к себе. Но да пёс с ним. Я Анжелика Ремедиос с довольно давних времён. Приёмная дочь бывшего коменданта этой оставленной всеми христианскими святыми колонии.";
			link.l1.go = "Sofia_3";
		break;
		
		case "Sofia_3":
			dialog.text = "А сейчас? Вашего отчима переводят на другое место службы?";
			link.l1 = "Он погиб чуть больше месяца назад, довольно нелепой смертью, повздорил с одним из своих подчинённых. Других родных у нас с моей сводной сестрой тут не осталось, и мы оказались предоставлены сами себе.";
			link.l1.go = "Sofia_4";
		break;
		
		case "Sofia_4":
			dialog.text = "Сочувствую. Кажется, у нас с вами схожая беда.";
			link.l1 = "Мне сразу так показалось. Предполагаю, вы спустились с причалившего утром военного корабля, но, очевидно, без сопровождения отца или мужа.";
			link.l1.go = "Sofia_5";
		break;
		
		case "Sofia_5":
			dialog.text = "Да, совсем недавно меня выдали замуж за военного. Обвенчались мы поспешно по настоянию родителей, так как моего супруга ждала командировка сюда, в Новый свет. Он отбыл из Европы до Гаваны через Сьерра-Леоне, а меня, двумя неделями позднее, посадили на торговое судно, идущее прямиком в эти края.\n"+
							"Так я оказалась в Гаване даже раньше, а когда дождалась, узнала, что как только они отплыли от берегов Африки, корабль охватила лихорадка, и мой муж оказался среди тех, кто её не пережил.";
			link.l1 = "Вас поженили родители, то есть, это был брак по расчёту?";
			link.l1.go = "Sofia_6";
		break;
		
		case "Sofia_6":
			dialog.text = "Я даже не знала, горевать мне или радоваться, я не хотела замужества с этим человеком и едва его знала, но больше у меня никого нет, а главное не осталось средств к существованию. Капитан любезно согласился отвезти меня обратно в Европу, при условии, что по прибытию родители оплатят моё путешествие, но на что жить сейчас?\n"+
							"К тому же, перед тем как вернуться, мы ещё должны простоять пару дней тут и посетить Порто-Белло, кажется так он сказал.";
			link.l1 = "Мои детство и юность не были спокойными, я бы, наверное, отнеслась к подобным событиям как к приключению, а вам должно быть тяжело оторваться от размеренной жизни и оказаться в такой пучине из неприятностей. Но, кажется, удача всё же вам улыбнулась, мы сможем друг другу помочь.";
			link.l1.go = "Sofia_7";
		break;
		
		case "Sofia_7":
			dialog.text = "Не стоит, общение с вами уже помогло мне почувствовать себя легче...";
			link.l1 = "Никаких возражений. У меня тут неподалёку в гроте, припрятаны кое-какие вещички. Я не могу их ни продать, ни обменять, но вам они точно помогут.";
			link.l1.go = "Sofia_8";
		break;
		
		case "Sofia_8":
			dialog.text = "Что с ними, они прокляты?";
			link.l1 = "Ха-хах! Нет конечно, но готова поспорить, на их прежнего владельца не раз сыпалась изрядная доля проклятий. Ждите здесь, я скоро вернусь, только никому ни слова.";
			link.l1.go = "Sofia_9";
		break;
		
		case "Sofia_9":
			LAi_CharacterDisableDialog(npchar);
			SetQuestHeader("AT_Mechty_Sbivautsya");
			AddQuestRecord("AT_Mechty_Sbivautsya", "1");
			
			PChar.quest.AT_pr_Grot.win_condition.l1 = "location";
			PChar.quest.AT_pr_Grot.win_condition.l1.location = "Hispaniola_Grot";
			PChar.quest.AT_pr_Grot.function = "AT_pr_Grot";
			
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry6 = 10;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry17 = 5;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry12 = 15;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry3 = 10;
			pchar.GenQuestBox.Hispaniola_Grot.box1.items.potionwine = 2;
		
			DialogExit();
		break;
		
		case "Rebekka_v_grote_1":
			dialog.text = "Ой, Анжелика!";
			link.l1 = "Бекки? Ты что здесь делаешь? ";
			link.l1.go = "Rebekka_v_grote_2";
			locCameraToPos(3.80, 2.70, -4.00, true);
		break;
		
		case "Rebekka_v_grote_2":
			dialog.text = "Вынюхиваю, чем ты здесь занимаешься. Последнее время ведёшь себя странно, всех задираешь, постоянно убегаешь то в лес, то сюда на побережье.";
			link.l1 = "Значит ты время от времени за мной приглядываешь. Послушай, я не могу, следуя твоему примеру, торчать целый день взаперти, а от нашего форта меня тошнит. Я устала ловить на себе взгляды местных солдафонов, выслушивать их примитивные комплименты и шуточки.";
			link.l1.go = "Rebekka_v_grote_3";
			locCameraSleep(true);
		break;
		
		case "Rebekka_v_grote_3":
			dialog.text = "Понимаю. Но дело же не только в этом, так? Смотри\n"+
							"Похоже, это вещи Аркадио? Того солдата, который вломился к нам в дом, требуя моей руки, и кольцо - то самое, которое он пытался вручить мне, до того, как ты его вытолкала.";
			link.l1 = "Похоже. Да.";
			link.l1.go = "Rebekka_v_grote_4";
		break;
		
		case "Rebekka_v_grote_4":
			dialog.text = "Когда я узнала, что его нашли мёртвым на берегу, я вознесла молитвы матери-заступнице, что избавила нас от этого гнусного человека, а ты прятала его вещи здесь? Как они оказались у тебя? Ты его убила!";
			link.l1 = "Нет! Конечно нет... Эмм... Да, я как обычно прогуливалась за городом и наткнулась на каких-то людей. Пиратов, или контрабандистов, не знаю, они точно не местные, и с ними был Аркадио. Я конечно же убралась оттуда побыстрее, пока меня не заметили, а позже, когда вернулась, нашла его мёртвым, обыскала карманы и убежала.";
			link.l1.go = "Rebekka_v_grote_5";
		break;
		
		case "Rebekka_v_grote_5":
			dialog.text = "И спрятала здесь то, что в них нашла, чтобы никто не нашёл и не подумал, будто это ты его заколола?";
			link.l1 = "Ну конечно.";
			link.l1.go = "Rebekka_v_grote_6";
		break;
		
		case "Rebekka_v_grote_6":
			dialog.text = "Ох, хотела бы я тебе верить, но сегодня... Сеньор Котес, если бы шпага задела его чуть правее, кто знает...";
			link.l1 = "Это сарагоса, а не шпага.";
			link.l1.go = "Rebekka_v_grote_7";
		break;
		
		case "Rebekka_v_grote_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("AT_pr_Strelba_is_pushki", 1.3);
		break;
		
		case "Rebekka_v_grote_8":
			dialog.text = "Стреляют? Форт стреляет.";
			link.l1 = "Нет, орудия форта я бы узнала. Кажется, звук с моря. Пойдём быстрее!";
			link.l1.go = "Rebekka_v_grote_9";
		break;
		
		case "Rebekka_v_grote_9":
			dialog.text = "С ума сошла, а если на город напали? Давай останемся здесь, тут будет безопасно.";
			link.l1 = "";
			link.l1.go = "Rebekka_v_grote_10";
		break;
		
		case "Rebekka_v_grote_10":
			DialogExit();
			
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("AT_pr_Strelba_is_pushki_4", 1.3);
		break;
		
		case "Rebekka_v_grote_11":
			dialog.text = "";
			link.l1 = "А вот это стреляет форт. Чёрт, Ребекка, как мы вовремя тут с тобой оказались.";
			link.l1.go = "Rebekka_v_grote_12";
		break;
		
		case "Rebekka_v_grote_12":
			dialog.text = "Надеюсь, наши отобьются, кто бы их не атаковал.";
			link.l1 = "";
			link.l1.go = "Rebekka_v_grote_13";
		break;
		
		case "Rebekka_v_grote_13":
			DialogExit();
			LAi_SetActorType(pchar);
			locCameraSleep(false);
			SetLaunchFrameFormParam("Наступил вечер...", "", 0, 2.3);
			LaunchFrameForm();
			DoQuestFunctionDelay("AT_pr_Piraty_v_grote", 2.3);
		break;
		
		case "Pirate_v_grote_1":
			dialog.text = "О-о, а кто тут прячется? Вот это мы удачно отбились от своих.";
			link.l1 = "Как вы тут?.. Стой! Не подходи! Я не позволю тебе!";
			link.l1.go = "Pirate_v_grote_2";
		break;
		
		case "Pirate_v_grote_2":
			dialog.text = "Посмотрите-ка, мышку загнали в угол. Давай нападай, проверим, правду ли говорят...";
			link.l1 = "Бекки беги!";
			link.l1.go = "Pirate_v_grote_3";
		break;
		
		case "Pirate_v_grote_3":
			DialogExit();
			EndQuestMovie();
			
			sld = characterFromId("AT_pr_Rebekka");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=2; i++)
				{
				sld = CharacterFromID("AT_pr_Piraty_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);		//стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "AT_pr_Pobeda_v_grote");
		break;
		
		case "Stoim_na_pirse":
			dialog.text = "Анжелика! Не поверишь, но я чертовски рад видеть тебя живой и здоровой.";
			link.l1 = "Кто на нас напал? Мы отбились? Где выжившие?";
			link.l1.go = "Stoim_na_pirse_2";
		break;
		
		case "Stoim_na_pirse_2":
			dialog.text = "Пираты. Весь гарнизон разбит, кому-то удалось убежать в джунгли, или, как мне, отсидеться в укрытии, но здесь уже никого не осталось, последние переправились вон на тот барк.";
			link.l1 = "Зачем им наш форт, здесь же нечем поживиться?";
			link.l1.go = "Stoim_na_pirse_3";
		break;
		
		case "Stoim_na_pirse_3":
			dialog.text = "Похоже, они собираются использовать его как перевалочный пункт. Их команды высадились на берег и отправились вглубь острова. Я расслышал упоминание про Санто-Доминго, там мощная крепость, не сравнится с нашей, но если им удастся напасть на город с суши, гарнизон форта даже не успеет прийти на помощь до того, как город будет разграблен.";
			link.l1 = "Они могли высадиться в любой из бухт.";
			link.l1.go = "Stoim_na_pirse_4";
		break;
		
		case "Stoim_na_pirse_4":
			dialog.text = "Я не знаю их мотивов, но послушай, ты ведь разбираешься в морской навигации? На барке осталось несколько матросов, они конечно могут провести корабль вдоль берега, но капитан и штурман были в городе, и их не пощадили, а нам нужен оптимальный маршрут, чтоб избежать рифов, мелей. Мы должны успеть в Санто-Доминго раньше пиратов.";
			link.l1 = "Отчим нанимал мне учителей, но лично кораблём я никогда не управляла и... А где Ребекка, она тоже поднялась на барк?";
			link.l1.go = "Stoim_na_pirse_5";
		break;
		
		case "Stoim_na_pirse_5":
			dialog.text = "Я её не видел с самой осады, с того момента, когда она перевязала мне плечо.";
			link.l1 = "Она не вернулась в город? Бекки должна была прийти сюда буквально за несколько минут до меня. О нет, я не могу сейчас отплыть, мне нужно её найти.";
			link.l1.go = "Stoim_na_pirse_6";
		break;
		
		case "Stoim_na_pirse_6":
			dialog.text = "Мы тоже не можем ждать, дело даже не в том, чтобы успеть предупредить губернатора о нападении, у нас под боком стоят вражеские корабли и на них ещё остались люди, которые могут высадиться сюда в любой момент.";
			link.l1 = "Нет, я всё равно не могу.";
			link.l1.go = "Stoim_na_pirse_7";
		break;
		
		case "Stoim_na_pirse_7":
			dialog.text = "Послушай, если Ребекка столкнулась с пиратами, они скорее всего взяли её с собой как заложницу, а если ей удалось укрыться в лесу, она неизбежно вернётся сюда. Нам в любом случае нужно как можно скорее попасть в Санто-Доминго. Тогда у нас есть шанс найти твою сестру у стен города, или же местный генерал-губернатор снарядит отряд отбить наш форт, и она без опаски сможет вернуться.\n"+ 
							"Если ты останешься здесь, то точно никому не поможешь, разве что развлечёшь перед смертью эту свору убийц.";
			link.l1 = "Дьявол... Лучше бы она оставалась со мной. Но я могла и не справиться. Хорошо. Хорошо, я плыву, но дай мне минуту.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Stoim_na_pirse_8";
		break;
		
		case "Stoim_na_pirse_8":
			dialog.text = "Я больше никого здесь не вижу.";
			link.l1 = "Да, её нигде нет. Плывём.";
			link.l1.go = "Stoim_na_pirse_9";
		break;
		
		case "Stoim_na_pirse_9":
			DialogExit();
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(sld, "reload", "reload1_back", "AT_pr_Stoim_na_pirse_9", -1);
			
			sld = GetCharacter(NPC_GenerateCharacter("AT_pr_OfficerRezid", "sold_spa_7", "man", "man", 10, SPAIN, -1, true));
			ChangeCharacterAddressGroup(sld, "SantoDomingo_town", "officers", "Reload3_1");
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MainheroPrologues\Prologue_AnjelikaTich.c";
			sld.dialog.currentnode = "AT_pr_Officer_u_rezidenta";
			sld.talker = 5;
			
			sld = CharacterFromID("LaVega_tavernkeeper")	//Возвращаем тавернщику его родной диалог
			sld.Dialog.Filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First time";
		break;
		
		case "AT_pr_Officer_u_rezidenta":
			dialog.text = "Барышня, стойте! Куда?";
			link.l1 = "Я посыльный из форта Ла Вега со срочным донесением губернатору.";
			link.l1.go = "AT_pr_Officer_u_rezidenta_2";
		break;
		
		case "AT_pr_Officer_u_rezidenta_2":
			sld = CharacterFromID("SantoDomingo_Mayor")
			dialog.text = "Понятно. Я бы вас пропустил, но его светлости нет на месте. Сеньор "+GetFullName(sld)+" отбыл в адмиралтейство.";
			link.l1 = "Его нет в городе? Тогда мне нужен комендант местного гарнизона, или человек, которого господин губернатор оставил вместо себя.";
			link.l1.go = "AT_pr_Officer_u_rezidenta_3";
		break;
		
		case "AT_pr_Officer_u_rezidenta_3":
			dialog.text = "Это что, ваше первое поручение в качестве посла? Адмиралтейство - это вон то большое серое здание, на которое я обречён смотреть целыми днями. Пройдите в арку и поверните направо. Там ещё банк, прямо напротив нужной вам двери.";
			link.l1 = "Благодарю.";
			link.l1.go = "AT_pr_Officer_u_rezidenta_4";
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
		break;
		
		case "AT_pr_Officer_u_rezidenta_4":
			DialogExit();
			
			pchar.questTemp.AnjelikaTichPrologue3 = "ATP3";
		break;
		
		case "ATpr_SD_Gubernator_1":
			dialog.text = "";
			link.l1 = "Наконец-то я до вас добралась.";
			link.l1.go = "ATpr_SD_Gubernator_2";
		break;
		
		case "ATpr_SD_Gubernator_2":
			dialog.text = "Что за срочность, и кто вас сюда пустил в таком виде?";
			link.l1 = "Я одна из немногих выживших из колонии Ла Вега. Нас атаковали буканьеры, сначала обстреляли форт с моря, потом высадились на берег и устроили там резню.";
			link.l1.go = "ATpr_SD_Gubernator_3";
		break;
		
		case "ATpr_SD_Gubernator_3":
			dialog.text = "Могу ли я вам доверять?";
			link.l1 = "Со мной на корабле люди, которые расскажут то же самое, а когда я представилась секретарю на входе, он подтвердил, что знал моего отчима.";
			link.l1.go = "ATpr_SD_Gubernator_4";
		break;
		
		case "ATpr_SD_Gubernator_4":
			dialog.text = "Мне вы так и не представились, впрочем, это несущественно. Кто-нибудь из выживших общался с этими пиратами? Какие требования они выдвигают?";
			link.l1 = "Насколько мне известно, никаких. Часть команды пиратов осталась в гавани на кораблях, часть отправилась в поход через джунгли. Они идут сюда, и раз уж мы здесь разговариваем, и в городе всё спокойно, значит, мы успели обогнуть остров по воде раньше них.";
			link.l1.go = "ATpr_SD_Gubernator_5";
		break;
		
		case "ATpr_SD_Gubernator_5":
			DialogExit();
			StartInstantDialog("ATpr_SD_Off_Guber_2", "ATpr_SD_Gubernator_6", "Quest\MainheroPrologues\Prologue_AnjelikaTich.c");
		break;
		
		case "ATpr_SD_Gubernator_6":
			dialog.text = "Сколько их может быть?";
			link.l1 = "Мы видели только 2 корабля, общей вместимостью 300-400 человек. По пути сюда больше не встретили ни одного, так что в бухтах скорее всего никто не высаживался.";
			link.l1.go = "ATpr_SD_Gubernator_7";
		break;
		
		case "ATpr_SD_Gubernator_7":
			dialog.text = "Я не могу перенаправить весь гарнизон из форта для усиления города. Мы не знаем их планов, возможно, они нападут с нескольких сторон, если вообще нападут.";
			link.l1 = "";
			link.l1.go = "ATpr_SD_Gubernator_8";
			LAi_SetActorType(npchar);
		break;
		
		case "ATpr_SD_Gubernator_8":
			DialogExit();
			StartInstantDialog("SantoDomingo_Mayor", "ATpr_SD_Gubernator_9", "Quest\MainheroPrologues\Prologue_AnjelikaTich.c");
		break;
		
		case "ATpr_SD_Gubernator_9":
			dialog.text = "Думаю, пары отрядов с мушкетами будет достаточно. Если на рейде есть военные корабли, лучше отправьте их к маяку и на ближайший мыс, чтоб контролировать подступы.";
			link.l1 = "У меня есть просьба, сеньор губернатор. Я непременно должна присутствовать там, в месте ожидаемого нападения с суши. Моя сестра возможно у них.";
			link.l1.go = "ATpr_SD_Gubernator_10";
		break;
		
		case "ATpr_SD_Gubernator_10":
			dialog.text = "Вы же девушка, вам незачем там находиться. Впрочем, запретить я вам не могу, но знайте, что там будет небезопасно для вас.";
			link.l1 = "За меня можете не волноваться, я сумею о себе позаботиться.";
			link.l1.go = "ATpr_SD_Gubernator_11";
		break;
		
		case "ATpr_SD_Gubernator_11":
			DialogExit();
			StartInstantDialog("ATpr_SD_Off_Guber_1", "ATpr_SD_Gubernator_12", "Quest\MainheroPrologues\Prologue_AnjelikaTich.c");
		break;
		
		case "ATpr_SD_Gubernator_12":
			dialog.text = "Ожидайте за городскими воротами. В самое ближайшее время там будет организована оборона. Ландшафт и джунгли не позволят подойти откуда-либо ещё.";
			link.l1 = "Благодарю.";
			link.l1.go = "ATpr_SD_Gubernator_13";
			LAi_SetActorType(npchar);
		break;
		
		case "ATpr_SD_Gubernator_13":
			DialogExit();
			StartInstantDialog("SantoDomingo_Mayor", "ATpr_SD_Gubernator_14", "Quest\MainheroPrologues\Prologue_AnjelikaTich.c");
		break;
		
		case "ATpr_SD_Gubernator_14":
			dialog.text = "";
			link.l1 = "Разрешите?..";
			link.l1.go = "ATpr_SD_Gubernator_15";
		break;
		
		case "ATpr_SD_Gubernator_15":
			dialog.text = "Да, можете идти.";
			link.l1 = "";
			link.l1.go = "ATpr_SD_Gubernator_16";
			LAi_SetActorType(npchar);
		break;
		
		case "ATpr_SD_Gubernator_16":
			DialogExit();
			
			PChar.quest.ATpr_OboronaSD.win_condition.l1 = "location";
			PChar.quest.ATpr_OboronaSD.win_condition.l1.location = "SantoDomingo_ExitTown";
			PChar.quest.ATpr_OboronaSD.win_condition = "ATpr_OboronaSD";
		break;
		
		case "ATpr_SD_Koten_1":
			dialog.text = "Вот ты где! Вижу, всё позади, а я уже полгорода оббегал и, как только услышал звуки выстрелов, сразу понял, где тебя искать.";
			link.l1 = "Ребекки здесь нет...";
			link.l1.go = "ATpr_SD_Koten_2";
		break;
		
		case "ATpr_SD_Koten_2":
			dialog.text = "Мне жаль.";
			link.l1 = "Ты же это знал, да и я знала. Я просто хотела увидеть ужас и замешательство на их мордах, когда они будут дохнуть тут под стенами.";
			link.l1.go = "ATpr_SD_Koten_3";
		break;
		
		case "ATpr_SD_Koten_3":
			dialog.text = "Ещё не всё потеряно. Послушай, команда на корабле организовала совет. Решали, стоит ли нам оставаться здесь, или попытать удачу и вернуться в Ла Вегу, и заодно предложили выбрать общим голосованием себе капитана.";
			link.l1 = "Хм... И что решили?";
			link.l1.go = "ATpr_SD_Koten_4";
		break;
		
		case "ATpr_SD_Koten_4":
			dialog.text = "Решили, что последнее слово останется за капитаном. Ты с нами?";
			link.l1 = "С вами конечно. Только сначала нужно заглянуть к губернатору, в конце концов, благодаря нам нападение на город не стало неожиданностью. Я рассчитываю на вознаграждение, которое позволит нам существовать некоторое время.";
			link.l1.go = "ATpr_SD_Koten_5";
		break;
		
		case "ATpr_SD_Koten_5":
			dialog.text = "Это было бы более чем справедливо. Тогда предлагаю не медлить, а потом - добро пожаловать на борт, госпожа капитан.";
			link.l1 = "";
			link.l1.go = "ATpr_SD_Koten_6";
		break;
		
		case "ATpr_SD_Koten_6":
			dialog.text = "Также, я провёл небольшую ревизию на корабле. Нашёл для тебя подходящий наряд. Где это видано, чтоб капитан по палубе разгуливал в юбке.";
			link.l1 = "";
			link.l1.go = "ATpr_SD_Koten_6_1";
		break;
		
		case "ATpr_SD_Koten_6_1":
			dialog.text = "Вот, примерь.";
			link.l1 = "Отвернись, переоденусь...";
			link.l1.go = "ATpr_SD_Koten_6_3";
		break;
		
		/*case "ATpr_SD_Koten_6_2":
			DialogExit();
			SetLaunchFrameFormParam("Минута переодеваний...", "ATpr_Pereodevaemsya", 0, 2.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 1);
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Gasten_Kotes")
			LAi_SetActorType(sld);
		break;*/
		
		case "ATpr_SD_Koten_6_3":
			dialog.text = "";
			link.l1 = "Неплохо, неплохо. Пойдёт на первое время. Спасибо тебе, Гастен.";
			link.l1.go = "ATpr_SD_Koten_7";
			//SetLaunchFrameFormParam("Минута переодеваний", "", 0, 2.0);
			//LaunchFrameForm();
			//WaitDate("", 0, 0, 0, 0, 1);
			
			PlaySound("Interface\important_item.wav");
			Log_info("Вы получили новый костюм");
		break;
		
		case "ATpr_SD_Koten_7":
			dialog.text = "Мы теперь в одной лодке. Сколько бы не заплатил губернатор, сейчас я тоже остался без гроша в кармане, но коммерческая жилка - это тебе не лоток на площади, её из меня так просто бортовым залпом не выбить, а уж имея корабль вместе мы не пропадём.";
			link.l1 = "Да, это неплохая идея - начать с фрахта. Рыбачить в окрестных водах точно не для меня. Ладно, сеньор Котес, о наших планах на будущее - позже, сегодня ещё нужно успеть в резиденцию.";
			link.l1.go = "ATpr_SD_Koten_8";
			Log_info("Гастен стал вашим офицером");
		break;
		
		case "ATpr_SD_Koten_8":
			DialogExit();
			
			sld = CharacterFromID("Gasten_Kotes")
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			ChangeCharacterReputation(sld, 20);
			sld.loyality = MAX_LOYALITY;
			LAi_SetImmortal(sld, false);
			sld.HalfImmortal = true;
			
			AddSimpleRumour("Пираты захватили испанскую колонию Ла Вега, а заодно предприняли попытку атаковать ещё и Санто-Доминго. Правда, им это не удалось, их всех перебили у стен города.", PIRATE, 10, 1);
			AddSimpleRumour("Ужасные новости, пираты устроили резню в нашей колонии Ла Вега, говорят, не пощадили никого. Слава богу, возмездие их уже настигло, все мерзавцы полегли под стенами Санто-Доминго при неудачной попытке взять город с суши.", SPAIN, 10, 1);
			pchar.questTemp.AnjelikaTichPrologue6 = "ATP6";
			SetTimerCondition("ATpr_Jiteli_Uspokoilis", 0, 0, 1, false);
			DeleteAttribute(pchar, "questTemp.AnjelikaTichPrologue5");
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "suit_2");
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "gate_back", "");
			pchar.questTemp.AnjelikaTichPrologue4 = "ATP4";
			LocatorReloadEnterDisable("SantoDomingo_town", "Reload3_back", false);
			chrDisableReloadToLocation = false;
			
			sld = CharacterFromID("SantoDomingo_Mayor")
			sld.Dialog.Filename = "Quest\MainheroPrologues\Prologue_AnjelikaTich.c";
			sld.dialog.currentnode = "ATpr_SD_Gubernator_20";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld,"SantoDomingo_townhall","sit","sit1");
		break;
		
		case "ATpr_SD_Gubernator_20":
			dialog.text = "Вот и вы. Мне уже доложили об успешно отбитом нападении. У меня мало времени, поэтому давайте сразу к сути.";
			link.l1 = "Конечно. Смею надеяться...";
			link.l1.go = "ATpr_SD_Gubernator_21";
		break;
		
		case "ATpr_SD_Gubernator_21":
			dialog.text = "...На некоторое вознаграждение за проявленное мужество и исполнение своего долга перед короной. Итак, ваши заслуги были оценены в 15000 пиастров. Это только половина тех средств, которые вы получите на руки прямо сейчас. Мне также доложили, что судно, на котором прибыли беженцы, принадлежало некоему Хосе Карпио, а с этого дня находится под вашим командованием. Верно?";
			link.l1 = "Похоже, всё так. Я была выбрана капитаном на общем голосовании членов команды.";
			link.l1.go = "ATpr_SD_Gubernator_22";
		break;
		
		case "ATpr_SD_Gubernator_22":
			AddMoneyToCharacter(pchar, 30000);
			GiveItem2Character(PChar, "ATpr_pismo");
			dialog.text = "Поразительно. Тем не менее, именно поэтому вторая часть средств также передаётся лично вам. Воспользуйтесь ими для приведения корабля в порядок, доукомплектуйте экипаж и отправляйтесь в Гавану, доложить его Милости Франсиско Орегон-и-Гаскону – генерал-губернатору испанских колоний Карибского архипелага о случившемся. Никто не сделает это лучше непосредственных участников событий, а от моего имени передайте этот рапорт. Остаток средств будет вашим вознаграждением.";
			link.l1 = "Позвольте, перед тем как я покину резиденцию. Какая судьба ждёт Ла Вегу, планируется ли вернуть контроль над поселением?";
			link.l1.go = "ATpr_SD_Gubernator_23";
		break;
		
		case "ATpr_SD_Gubernator_23":
			dialog.text = "Этот вопрос у вас будет возможность задать лично его Превосходительству. Я не вправе принимать столь масштабные решения.";
			link.l1 = "В таком случае, у меня тоже есть личный интерес добраться до Гаваны как можно скорее.";
			link.l1.go = "ATpr_SD_Gubernator_24";
		break;
		
		case "ATpr_SD_Gubernator_24":
			dialog.text = "Приятно слышать. Больше вас не задерживаю.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("ATpr_VosstanovimGorod");
		break;
		
		case "Pirat_Guber":
			dialog.text = "Хватило же у тебя отваги, женщина, появиться здесь, или это глупость не позволила разглядеть перемены вокруг?";
			link.l1 = "Моё имя Анжелика Тич, и я здесь ровно потому, что вокруг произошли некоторые перемены.";
			link.l1.go = "Pirat_Guber_2";
		break;
		
		case "Pirat_Guber_2":
			dialog.text = "Вот как? Излагай.";
			link.l1 = "По счастью, я находилась в Санто-Доминго, когда твои люди совершили неудачную попытку штурма. По городу поползли слухи, что Испания назначила награду за двух молодых особ – дочерей коменданта этого форта, и у меня есть намерения их заполучить.";
			link.l1.go = "Pirat_Guber_3";
		break;
		
		case "Pirat_Guber_3":
			dialog.text = "Ты считаешь, будь они у меня, я бы их отдал?";
			link.l1 = "Я считаю, тебе нужен посредник в переговорах. Испанцы не подпустят тебя ни к одному из своих поселений на расстояние пушечного выстрела.";
			link.l1.go = "Pirat_Guber_4";
		break;
		
		case "Pirat_Guber_4":
			dialog.text = "У них нет на это причин. Колонию атаковали не мои люди. Я всего лишь воспользовался моментом и занял покинутое укрепление. Выгодное место, замечу, было бы глупо им пренебрегать. Тут под боком то и дело снуют английские и французские караваны, а в хорошую погоду даже просматриваются берега Тортуги.";
			link.l1 = "И всё же, что с сёстрами?";
			link.l1.go = "Pirat_Guber_5";
		break;
		
		case "Pirat_Guber_5":
			dialog.text = "Можешь взять своих ребят и прочесать остров, но я готов заключить пари, что если они живы, то придут сами. А можешь раздать лопаты и отдать приказ проверить могильник за городом. У меня ты их не найдёшь.";
			link.l1 = "Награду за мёртвых никто бы не назначил.";
			link.l1.go = "Pirat_Guber_6";
		break;
		
		case "Pirat_Guber_6":
			dialog.text = "Значит, я не смогу тебе ничем помочь.";
			link.l1 = "Я ещё наведаюсь сюда при случае.";
			link.l1.go = "Pirat_Guber_7";
		break;
		
		case "Pirat_Guber_7":
			DialogExit();
			
			AddQuestRecord("AT_Mechty_Sbivautsya", "5");
			sld = CharacterFromID("Edward Mansfield")
			sld.Dialog.Filename = "Mayor/EdwardMansfield.c";
			sld.dialog.currentnode = "First Time";
		break;
		
		case "Ispa_Guber":
			dialog.text = "";
			link.l1 = "Я прибыла по поручению сеньора губернатора Санто-Доминго с отчётом о недавних событиях на Эспаньоле.";
			link.l1.go = "Ispa_Guber_2";
			TakeItemFromCharacter(pchar, "ATpr_pismo");
		break;
		
		case "Ispa_Guber_2":
			sld = CharacterFromID("SantoDomingo_Mayor")
			dialog.text = "Я уже располагаю сведеньями о произошедшем. Слухи, знаете ли, в этих краях разлетаются быстрее ветра, но официальный отчёт, конечно же, прочту. Примите это в качестве платы за своевременную доставку.";
			link.l1 = "Сеньор "+GetFullName(sld)+" уже выдал мне вознаграждение авансом.";
			link.l1.go = "Ispa_Guber_3";
			AddMoneyToCharacter(pchar, 5000);
		break;
		
		case "Ispa_Guber_3":
			dialog.text = "Считайте это покрытием дополнительных издержек.";
			link.l1 = "Не стану возражать, я сейчас нахожусь в непростом положении. В связи с этим у меня есть вопрос, не столько государственного, сколько личного характера. Какая судьба ждёт утраченную Испанией колонию? Она долгое время была моим домом.";
			link.l1.go = "Ispa_Guber_5";
		break;
		
		case "Ispa_Guber_5":
			dialog.text = "В данном вопросе нельзя принимать поспешных решений. Но я вам могу точно сказать, что Испания просто так не оставит тот кровавый разбой, который учинили пираты. Рано или поздно в Ла Веге снова поднимут испанское знамя и справедливость восторжествует! А теперь я попрошу вас оставить меня, мне нужно работать.";
			link.l1 = "Благодарю вас, ваше Превосходительство!";
			link.l1.go = "Ispa_Guber_6";
		break;
		
		case "Ispa_Guber_6":
			DialogExit();
			
			AddQuestRecord("AT_Mechty_Sbivautsya", "6");
			CloseQuestHeader("AT_Mechty_Sbivautsya");
			sld = CharacterFromID("spa_guber")
			sld.Dialog.Filename = "Common_Governor.c";
			sld.dialog.currentnode = "First Time";
		break;
		
		//Квест продолжение сюжета: "Портниха знатной дамы"
		case "AT_PZD_Pilar_1_1":
			dialog.text = "";
			link.l1 = "Ребекка?";
			link.l1.go = "AT_PZD_Pilar_1_2";
		break;
		
		case "AT_PZD_Pilar_1_2":
			dialog.text = "Прошу прощения?";
			link.l1 = "Как... Кажется, я ошиблась. Перепутала вас с одной своей знакомой.";
			link.l1.go = "AT_PZD_Pilar_1_3";
		break;
		
		case "AT_PZD_Pilar_1_3":
			dialog.text = "И я это уже прекрасно поняла. Теперь, прошу, отойдите от меня.";
			link.l1 = "Конечно, конечно. Но мне бы только хотелось узнать, кто вам сшил платье? Из-за него мне и показалось, что вы та самая девушка.";
			link.l1.go = "AT_PZD_Pilar_1_4";
		break;
		
		case "AT_PZD_Pilar_1_4":
			dialog.text = "Чепуха.";
			link.l1 = "";
			link.l1.go = "AT_PZD_Pilar_1_5";
		break;
		
		case "AT_PZD_Pilar_1_5":
			dialog.text = "Гарберд, для чего вы здесь стоите?";
			link.l1 = "";
			link.l1.go = "AT_PZD_Pilar_1_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("AT_PZD_Herineldo"));
		break;
		
		case "AT_PZD_Pilar_1_6":
			DialogExit();
			StartInstantDialog("AT_PZD_Herineldo", "AT_PZD_Pilar_1_7", "Quest\MainheroPrologues\Prologue_AnjelikaTich.c");
			sld = CharacterFromID("AT_PZD_Pilar");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);			
		break;
		
		case "AT_PZD_Pilar_1_7":
			dialog.text = "Сеньорита, я вынужден настоять.";
			link.l1 = "Не утруждайте себя!";
			link.l1.go = "AT_PZD_Pilar_1_8";
		break;
		
		case "AT_PZD_Pilar_1_8":
			DialogExit();
		break;

	}
}
