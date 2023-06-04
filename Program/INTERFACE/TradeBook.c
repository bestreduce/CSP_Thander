/// BOAL меню торговли
string CurTable, CurRow, sLastTABLE_GOODS;

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchTradeBook"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleTradeBook";
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("TableSelectChange", "TableSelectChange", 0);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
    SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);

    XI_RegistryExitKey("IExit_F2");
    // шапка -->
    GameInterface.TABLE_CITY.hr.td1.str = "Нация";
    GameInterface.TABLE_CITY.hr.td1.scale = 0.8
	GameInterface.TABLE_CITY.hr.td2.str = "Город";
	GameInterface.TABLE_CITY.hr.td2.scale = 0.8;
	GameInterface.TABLE_CITY.hr.td3.str = "Локация";
	GameInterface.TABLE_CITY.hr.td3.scale = 0.8;
	GameInterface.TABLE_CITY.hr.td4.str = "Актуальность";
	GameInterface.TABLE_CITY.hr.td4.scale = 0.8;
    // <--
//--> mod tablesort
	GameInterface.TABLE_CITY.hr.td1.sorttype = "";
	GameInterface.TABLE_CITY.hr.td2.sorttype = "string";
	GameInterface.TABLE_CITY.hr.td3.sorttype = "string";
	GameInterface.TABLE_CITY.hr.td4.sorttype = "string";
	GameInterface.TABLE_CITY.hr.td4.sortdir = "dec";//по уменьшению
//<-- mod tablesort

    // шапка -->
    GameInterface.TABLE_GOODS.hr.td1.str = XI_ConvertString("Good name");
    GameInterface.TABLE_GOODS.hr.td1.scale = 0.8;
    GameInterface.TABLE_GOODS.hr.td2.str = "Тип";
    GameInterface.TABLE_GOODS.hr.td2.scale = 0.8;
	GameInterface.TABLE_GOODS.hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.TABLE_GOODS.hr.td3.scale = 0.8;
	GameInterface.TABLE_GOODS.hr.td4.str = XI_ConvertString("Price buy");
	GameInterface.TABLE_GOODS.hr.td4.scale = 0.8;
	GameInterface.TABLE_GOODS.hr.td5.str = XI_ConvertString("In the store");
	GameInterface.TABLE_GOODS.hr.td5.scale = 0.8;
	GameInterface.TABLE_GOODS.hr.td6.str = "Пачка";
	GameInterface.TABLE_GOODS.hr.td6.scale = 0.8;
	GameInterface.TABLE_GOODS.hr.td7.str = "Вес пачки";
	GameInterface.TABLE_GOODS.hr.td7.scale = 0.8;
	GameInterface.TABLE_GOODS.hr.td8.str = "Общий вес";
	GameInterface.TABLE_GOODS.hr.td8.scale = 0.8;
//--> mod tablesort
	GameInterface.TABLE_GOODS.hr.td1.sorttype = "string";
	GameInterface.TABLE_GOODS.hr.td2.sorttype = "";
	GameInterface.TABLE_GOODS.hr.td3.sorttype = "";
	GameInterface.TABLE_GOODS.hr.td4.sorttype = "";
	GameInterface.TABLE_GOODS.hr.td5.sorttype = "";
	GameInterface.TABLE_GOODS.hr.td6.sorttype = "";
	GameInterface.TABLE_GOODS.hr.td7.sorttype = "";
	GameInterface.TABLE_GOODS.hr.td8.sorttype = "";
	GameInterface.TABLE_GOODS.hr.td8.sortdir = "dec";
//<-- mod tablesort

    FillPriceListTown("TABLE_CITY");
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("TableSelectChange", "TableSelectChange");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
    DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("OnTableClick", "OnTableClick");

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_TRADEBOOK";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_TRADEBOOK" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}
//  таблица: город, местоположение, актуальность
void FillPriceListTown(string _tabName)
{
	string  cityId, attr2, firstId;
    int     i, cn, n;
    ref     nulChr;
    string  row;
    aref    rootItems;
    aref    curItem;
    ref     rCity;

    nulChr = &NullCharacter;
    makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
    n = 1;
    firstId = "";
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
        row = "tr" + n;
		curItem = GetAttributeN(rootItems, i);
		cityId = GetAttributeName(curItem);
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).index = i;//<-- mod tablesort
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width  = 40;
		    GameInterface.(_tabName).(row).td1.icon.height = 40;
		    GameInterface.(_tabName).(row).td1.icon.offset = "-5, 0";
			GameInterface.(_tabName).(row).td1.str = rCity.nation;//<-- mod tablesort
			GameInterface.(_tabName).(row).td1.scale = 0.0;//невидимая цифра для сортировки
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td2.scale = 0.8;
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
			GameInterface.(_tabName).(row).td3.scale = 0.8;
			GameInterface.(_tabName).(row).td4.scale = 0.8;
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
		    {
		        GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
		    }
		    else
		    {
		        GameInterface.(_tabName).(row).td4.str = "??.??.????";
		    }
			n++;
		}
	}
	GameInterface.(_tabName).select = 0;
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}

void FillPriceList(string _tabName, string attr1)// картинка, название, картинка экспорта, продажа, покупка, колво, пачка, вес пачки
{
	sLastTABLE_GOODS = attr1;
    string  sGoods;
    int     i, n, iTradeType;
    ref     nulChr;
    string  row;
    nulChr = &NullCharacter;
	if (attr1 != "")
	{
	    n = 1;
	    for (i = 0; i < GOODS_QUANTITY; i++)
	    {
			if(i > 36 && i < 57) continue;
	        row = "tr" + n;
	        sGoods = "Gidx" + i;
			iTradeType = sti(nulChr.PriceList.(attr1).(sGoods).TradeType);
	        if (iTradeType == TRADE_TYPE_CANNONS && !bBettaTestMode) continue; // не пушки

			GameInterface.(_tabName).(row).index = i;//<-- mod tablesort
            GameInterface.(_tabName).(row).UserData.ID = Goods[i].name;
            GameInterface.(_tabName).(row).UserData.IDX = i;

	        GameInterface.(_tabName).(row).td1.icon.group = "GOODS";
			GameInterface.(_tabName).(row).td1.icon.image = Goods[i].name;
			GameInterface.(_tabName).(row).td1.icon.offset = "0, 0";
			GameInterface.(_tabName).(row).td1.icon.width = 20;
			GameInterface.(_tabName).(row).td1.icon.height = 20;
			GameInterface.(_tabName).(row).td1.textoffset = "20,0";
			GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);
			GameInterface.(_tabName).(row).td1.scale = 0.85;

	        GameInterface.(_tabName).(row).td2.icon.group = "TRADE_TYPE";
			GameInterface.(_tabName).(row).td2.icon.image = "ico_" + iTradeType;
			GameInterface.(_tabName).(row).td2.icon.offset = "1, 0";
			GameInterface.(_tabName).(row).td2.icon.width = 18;
			GameInterface.(_tabName).(row).td2.icon.height = 18;

			GameInterface.(_tabName).(row).td2.str = iTradeType;//<-- mod tablesort
			GameInterface.(_tabName).(row).td2.scale = 0.0;//невидимая цифра для сортировки
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Buy"))
	        {
	            GameInterface.(_tabName).(row).td3.str = nulChr.PriceList.(attr1).(sGoods).Buy;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td3.str = "???";
	        }
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Sell"))
	        {
	            GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(attr1).(sGoods).Sell;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td4.str = "???";
	        }
	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Qty"))
	        {
	            GameInterface.(_tabName).(row).td5.str = nulChr.PriceList.(attr1).(sGoods).Qty;
	        }
	        else
	        {
	            GameInterface.(_tabName).(row).td5.str = "????";
	        }
	        GameInterface.(_tabName).(row).td6.str = Goods[i].Units;
			GameInterface.(_tabName).(row).td7.str = Goods[i].Weight;
			GameInterface.(_tabName).(row).td8.str = GetGoodWeightByType(i, sti(nulChr.PriceList.(attr1).(sGoods).Qty));
	        n++;
	    }
    }
	GameInterface.(_tabName).select = 0;
	if (checkattribute(&GameInterface, _tabName + ".hr.sortedColumn"))//таблица уже сортировалось ранее
	{
		int nColumn = sti(GameInterface.(_tabName).hr.sortedColumn);
		DeleteAttribute(&GameInterface, _tabName + ".hr.sortedColumn");
		SortTable(_tabName, nColumn);//сохраняем сортировку
//Нужно сохранять последнее направление сортировки дополнительно. Может быть, перезаписывать sortdir каждый раз? Из-за этого и запоминание строки сбивалось 
	}
    Table_UpdateWindow(_tabName);
}

void TableSelectChange()
{
//не присылает номер колонки, а номер строки с единицы начинает, на заголовке не срабатывает
	string sControl = GetEventData();
	int iRow = GetEventData();
    CurTable = sControl;
    CurRow   = "tr" + (iRow);
	
    if (CurTable == "TABLE_CITY" && sLastTABLE_GOODS != GameInterface.(CurTable).(CurRow).UserData.CityID)//перерисуем прайс
    {
		Table_Clear("TABLE_GOODS", false, true, false);
		FillPriceList("TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID);
    }
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	//Boyer fix #20170401-01 Can't load texture -1.tx log errors
	//sPicture = "-1";
	sPicture = "";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "TABLE_GOODS":
		    sGroup = "GOODS";
		    sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
		    sText1  = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
			sText2 = "Цвета указателя типа товара :" + newStr() +
				 "- зелёный : колониальные товары" + newStr() +
				 "- синий : импортные товары" + newStr() +
				 "- красный : контрабандные товары" + newStr() +
				 "- коричневый : товары агрессивного спроса";
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);

}

void HideInfoWindow()
{
	CloseTooltip();
}

void OnTableClick()
{
//TableSelectChange срабатывает раньше OnTableClick
	string sControl = GetEventData();
	int iRow = GetEventData();
	//string sRow = "tr" + (iRow+1);
	int iColumn = GetEventData();

	if (!SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, sControl, 1 )) 
	{
		SortTable(sControl, iColumn);//<-- mod tablesort
		Table_UpdateWindow(sControl);
	}
}
