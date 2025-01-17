float fNewPos;
#define MAX_LINE         123

string STR_TEXT[MAX_LINE] = {
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"Разработчики проекта",
"",
"LEOPARD's team",
"Corsairs Ship Pack: OpenSource Edition",
"",
"",
"",
"",
"",
"Основатель аддона",
"LEOPARD",
"",
"Кодеры",
"LEOPARD",
"Gregg",
"Sinistra",
"BlackThorn",
"Qwerry, St.",
"Lipsar",
"Arty",
"Bestreducer",
"annoyer",
"Terra",
"",
"",
"",
"Правка и доработка интерфейсов",
"LEOPARD",
"Gregg",
"Qwerry, St.",
"BlackThorn",
"Lipsar",
"annoyer",
"",
"",
"",
"Моделирование кораблей и локаций",
"Noctus",
"Nikk",
"",
"",
"",
"Тестирование",
"LEOPARD",
"Gregg",
"Googman",
"Qwerry, St.",
"BlackThorn",
"Lipsar",
"Sinistra",
"Arty",
"Bestreducer",
"annoyer",
"Terra",
"Noctus",
"Nikk",
"",
"",
"Переиздание старых плагинов для моддинга и их усовершенствование",
"под современные программы для Blender'а, а также многих мелких программ",
"Arty aka Artes999",
"",
"",
"При создании модификации были",
"использованы следующие ресурсы",
"",
"Код и ресурсы из Корсары: Проклятые Судьбой",
"",
"Код и ресурсы из Корсары: Каждому Свое",
"",
"Код и ресурсы из Корсары: История Пирата",
"",
"Ресурсы из Корсары 2: Пираты Карибского Моря",
"",
"Код и ресурсы из Корсары: New abilities 0.4.0",
"",
"Код и ресурсы из Gentlemen of Fortune: Eras II",
"",
"Ресурсы с сайта 'Гавань Корсаров'",
"",
"Огромное спасибо следующим людям",
"чьи моды, предложения и прочие новинки",
"официально вошли в проект CSP",
"",
"",
"Ерилейн за его уникального героя 'Темный Странник' и за помощь по мелочам",
"Konstrush за его описание для героев и за сочный, крутой HUD",
"Etienne и Narve за шикарных персонажей из Чёрныйх парусов и не только",
"johnny88 за классный худ и переделку всех портретов",
"johnny88 а также за кучу переделок по графике",
"Kormach за переделку множества персонажей",
"EvgAnat за шикарную озвучку боссов-нежить и за уникальные механики",
"Shanks за предоставление качественных кораблей",
"",
"",
"Ребята, ранее помогавшие по проекту",
"Korsar Maxim",
"Zik",
"crem_soda",
"Krah_an_Krait",
"Shaharan",
"",
"",
"Особая благодарность всем разработчикам движка",
"OpenSource, а также нашему главному штурману",
"kb31",
"Без него мы вряд ли бы увидели развитие проекта!",
};

string STR_COLOR[MAX_LINE] = {
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"blue",
"",
"yellow",
"yellow",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"yellow",
"yellow",
"violet",
"",
"",
"blue",
"blue",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"yellow",
"",
"blue",
"blue",
"blue",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"",
"yellow",
"",
"",
"",
"",
"",
"",
"",
"yellow",
"yellow",
"violet",
"blue",
};


void InitInterface(string iniName)
{
	GameInterface.title = "";

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak", "ProcessCancelExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("My_MoveText", "MoveText", 0);

	SetFormatedText("INFO_TEXT", "");
	int i, k;

	for(i = 0; i < MAX_LINE; i++)
	{
		SendMessage(&GameInterface, "lsle", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 0, STR_TEXT[i] + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

		if(STR_COLOR[i] != "")
		{
			switch (STR_COLOR[i])
			{
				case "yellow":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,251,237,68));
				break;
				case "red":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,255,162,162));
				break;
				case "blue":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,0,255,255));
				break;
				case "violet":
					SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 8, i, argb(255,255, 20, 147));
				break;
			}
		}
	}

	PostEvent("My_MoveText", 370);
	fNewPos = 0;
	SetMusic("music_Credits"); // LEO: Об авторах - другой музон
}

void ProcessCancelExit()
{
	if(CheckAttribute(&InterfaceStates, "showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if(!CheckAttribute(&InterfaceStates, "InstantExit") || sti(InterfaceStates.InstantExit) == false) ReturnToMainMenu();
}

void IDoExit(int exitCode)
{
 	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("My_MoveText","MoveText");

	interfaceResultCommand = exitCode;
	if(CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit) == true)
		EndCancelInterface(true);
	else
		EndCancelInterface(false);
}

void MoveText()
{
	if(fNewPos >= 1)
	{
		ProcessCancelExit();
	}
	else
	{
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",2, fNewPos);
		PostEvent("My_MoveText", 30);
		fNewPos = fNewPos + 0.0003;
	}
}
