int iTime = 0;
int iTimeM = 0;
string sDate;
bool days = false;

void InitInterface_GM(string iniName)
{
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

    BLI_DisableShow();

    /* SetTimeScale(0.0); */
	locCameraSleep(true);

	EngineLayersOffOn(true);

    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("InterfaceBreak","ProcessCancelExit",0);
    SetEventHandler("exitCancel","ProcessCancelExit",0);
    SetEventHandler("eSlideChange","ChangeTimeProgress",0);
	SetEventHandler("RefreshVariables","RefreshVariables",0);
    SetEventHandler("exitOk","Sleep",0);

    SetWariable();

    SetTimeSlider();

    ProcessFrame();
	
	SetFormatedText("TIME_TEXT", (iTime+1)+FindHourString(iTime+1) + " и " + (iTimeM+1) + FindMinuteString(iTimeM+1));
	SetFormatedText("HOURS", "Часы");
	SetFormatedText("MINUTES", "Минуты");

    SetFormatedText("CAPTION", "Отдых");
}

void ProcessFrame()
{
	SetSelectable("TIME_CHECK2", false);
	
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 1))
	{
		days = false;
		SetSelectable("SLIDE", false);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 0,0);
		SetSelectable("SLIDE2", false);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE2", 0,0);
		SetFormatedText("TIME_TEXT", "");
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 2))
	{
		days = false;
		SetSelectable("SLIDE", false);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 0,0);
		SetSelectable("SLIDE2", false);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE2", 0,0);
		SetFormatedText("TIME_TEXT", "");
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3))
	{
		days = false;
		SetSelectable("SLIDE", true);
		SetSelectable("TIME_CHECK2", true);
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK2", 3, 1) == 1) SetSelectable("SLIDE2", true);
		else SetSelectable("SLIDE2", false);
		SetFormatedText("HOURS", "Часы");
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 4))
	{
		days = true;
		SetSelectable("SLIDE", true);
		SetSelectable("SLIDE2", false);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE2", 0,0);
		SetFormatedText("HOURS", "Дни");
	}
	SetWariable();
}

void RefreshVariables()
{
	SetTimeSlider();
	ChangeTimeProgress();
	if(days == false) SetFormatedText("TIME_TEXT", (iTime+1) + FindHourString(iTime+1) + " и " + (iTimeM+1) + FindMinuteString(iTimeM+1));
	else SetFormatedText("TIME_TEXT", "Дней: "+(iTime+1));
}

void ChangeTimeProgress()
{
	string sNode = GetEventData();

	if(sNode == "SLIDE")
	{
		iTime = GetEventData();
		if(days == false) SetFormatedText("TIME_TEXT", (iTime+1) + FindHourString(iTime+1) + " и " + (iTimeM+1) + FindMinuteString(iTimeM+1));
		else SetFormatedText("TIME_TEXT", "Дней: "+(iTime+1));
	}
	if(sNode == "SLIDE2")
	{
		iTimeM = GetEventData();
		if(days == false) SetFormatedText("TIME_TEXT", (iTime+1) + FindHourString(iTime+1) + " и " + (iTimeM+1) + FindMinuteString(iTimeM+1));
		else SetFormatedText("TIME_TEXT", "Дней: "+(iTime+1));
	}
}

void SetTimeSlider()
{
	if (days == false)
	{
		GameInterface.nodes.SLIDE.value = iTime;
		GameInterface.nodes.SLIDE.maxlimit = 23;

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 1,23);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 0,iTime);
		
		GameInterface.nodes.SLIDE2.value = iTimeM;
		GameInterface.nodes.SLIDE2.maxlimit = 59;

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"SLIDE2", 1,59);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE2", 0,iTimeM);
	}
	else
	{
		GameInterface.nodes.SLIDE.value = iTime;
		GameInterface.nodes.SLIDE.maxlimit = 6;

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 1,6);
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"SLIDE", 0,iTime);
	}
}

void SetWariable()
{
	string sCurDayTime;
	SetFormatedText("CURRENTTIME_TEXT", "");

	sDate = environment.date.day + " " + XI_ConvertString("target_month_" + environment.date.month) + " " + environment.date.year;

	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"CURRENTTIME_TEXT", 0,&sDate);

	string sTime;
	string sHour = sti(worldMap.date.hour);
	string sMinuts = sti(worldMap.date.min);

   if(sti(sHour) < 10)
	{
		sHour = "0" + sHour;
	}
	if(sti(sMinuts) < 10)
	{
		sMinuts = "0" + sMinuts;
	}
	
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3))
	{
		if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK2", 3, 1) == 0) iTimeM = -1;
		string sHours = sti(worldMap.date.hour)+(iTime+1);
		string sMinutes = sti(sMinuts) + (iTimeM+1);
		if (sti(sMinutes) > 59) 
		{
			sMinutes = sti(sMinutes)-60; 
			sHours = sti(sHours) + 1;
		}
		if (sti(sMinutes) < 10) sMinutes = "0"+(sMinutes);
		if (sti(sHours)>23)
		{
			sHours = sti(sHours)-24;
			SetFormatedText("CURRENTTIME_TEXT", "");
			sDate = environment.date.day + " " + XI_ConvertString("target_month_" + environment.date.month) + " " + environment.date.year;
			SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"CURRENTTIME_TEXT", 0,&sDate);
		}
		sTime = sHour + " : " + sMinuts + " -> " + sHours + " : " + sMinutes;
	}
	else sTime = sHour + " : " + sMinuts;

	SendMessage(&GameInterface,"lsle",MSG_INTERFACE_MSG_TO_NODE,"CURRENTTIME_TEXT", 0,&sTime);

	sCurDayTime = GetDayTime();

	if(sCurDayTime != "night")
	{
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 1,0);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 2,1);
	}
	else
	{
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 1,1);
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 2,0);
	}
}

void Sleep()
{
    int iCurrentTime = sti(environment.time);
    int iAddtime = 0;
    int iOldDay = GetDataDay();

    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 1))
    {
        if (iCurrentTime < 24) iAddtime = 24 - iCurrentTime;
    }

    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 2))
    {
        if (iCurrentTime >= 21) iAddTime = 24 - iCurrentTime + 7;
		if (iCurrentTime < 7) iAddTime = 7 - iCurrentTime;
    }

    if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3) == 1 || SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 4) == 1)
    {
        iAddtime = iTime+1;
    }
	
	pchar.quest.waithours = iAddtime;
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3))
	{
		AddTimeToCurrent(0, sti(iTimeM)+1);
	}
	
    if (days == false)
	{
		DoQuestFunctionDelay("WaitNextHours", 0.1);
	}
	else
	{
		DoQuestFunctionDelay("WaitNextDays", 0.1);
	}
	ProcessCancelExit();
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_TAVERN_WAIT, true);
}

void IDoExit(int exitCode, bool bCode)
{
	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("eSlideChange","ChangeTimeProgress");
	DelEventHandler("RefreshVariables","RefreshVariables");
	DelEventHandler("exitOk","Sleep");

	SetTimeScale(1.0);
	locCameraSleep(false);

	BLI_EnableShow();

	interfaceResultCommand = exitCode;
	EndCancelInterface(bCode);
}

string FindHourString(int iHour)
{
	string sHour = " часов";

	if(iHour == 1 || iHour == 21) sHour = " час";
	if(iHour > 1 && iHour < 5) sHour = " часа";
	if(iHour > 21 && iHour < 25) sHour = " часа";

	return sHour;
}

string FindMinuteString(int minute)
{
	string minuteR = " минут";

	if(minute == 1 || minute == 21) minuteR = " минута";
	if(minute > 1 && minute < 5) minuteR = " минуты";
	if(minute > 21 && minute < 25) minuteR = " минуты";
	if(minute > 31 && minute < 35) minuteR = " минуты";
	if(minute > 41 && minute < 45) minuteR = " минуты";
	if(minute > 51 && minute < 55) minuteR = " минуты";

	return minuteR;
}

void Restore_HP()
{
	int iOfficer;
	LAi_SetCurHPMax(pchar);
	for (int i=1; i<4; i++)
	{
		if (GetOfficersIndex(Pchar, i) != -1)
		{
			iOfficer = GetOfficersIndex(Pchar, i);
			LAi_SetCurHPMax(&characters[iOfficer]);
		}
	}
}

// 2 - вкл/выкл, 3 - проверить статус, 4 - проверить порядковый номер, 5 - актив/деактив
//SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 1,1)
