int FindFoodFromChr(ref chref, ref arFind, int startIdx)
{
	int i;
	aref arItm;
	for(i=startIdx; i<10; i++)
	{
		if (i!= -1)
		{
			makearef(arItm,Items[i]);
			if( CheckAttribute(arItm,"Food") && GetCharacterItem(chref,Items[i].id)>0 )
			{
				arFind = arItm;
				return i;
			}
		}
	}
	return -1;
}

int FindBetterFoodFromChr(ref chref, ref arFind)
{
	int i;
	aref arItm;
	for(i=10; i>-1; i--)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"Food") && GetCharacterItem(chref,Items[i].id)>0 )
		{
			arFind = arItm;
			return i;
		}
	}
	return -1;
}

bool EnableFoodUsing(ref mc, aref arItm)
{
	bool bEnableUse = false;
	if(CheckAttribute(arItm,"Food.energy") && !CheckAttribute(mc,"chr_ai.noeat"))
	{
		if(LAi_GetCharacterEnergy(mc) < LAi_GetCharacterMaxEnergy(mc))
		{
			return true;
		}
	}
	if(CheckAttribute(mc,"chr_ai.noeat"))
	{
		if(sti(mc.index)==GetMainCharacterIndex() && !CheckAttribute(pchar, "autofood") && !CheckAttribute(pchar, "query_delay"))
		{
			if (CheckAttribute(pchar, "pressedFoodButton"))
			{
				DeleteAttribute(pchar, "pressedFoodButton");

				if (!CheckAttribute(pchar, "foodquery"))
				{
					pchar.foodquery = 1;
					pchar.query_delay = 0.1;
					Log_SetStringToLog("Потребление еды поставлено в очередь.");
					Log_SetStringToLog("Очередь:"+pchar.foodquery);
				}
				else
				{
					pchar.foodquery = sti(pchar.foodquery)+1;
					pchar.query_delay = 0.1;
					Log_SetStringToLog("Потребление еды поставлено в очередь.");
					Log_SetStringToLog("Очередь:"+pchar.foodquery);
				}
			}

		}
	}



	return false;
}

void DoCharacterUsedFood(ref chref, string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 || CheckAttribute(chref,"chr_ai.Swift")) return;
	TakeItemFromCharacter(chref,itmID);

	if( CheckAttribute(arItm,"Food.energy") )
	{
		chref.chr_ai.noeat = 10.0;
		LAi_UseEnergyBottle(chref,stf(arItm.Food.energy));
		if(sti(chref.index)==GetMainCharacterIndex())
		{
			Log_SetStringToLog(XI_ConvertString("Energy Up"));
			PlaySound("interface\_Hrust_"+rand(3)+".wav");
			pchar.questTemp.foodcount = sti(pchar.questTemp.foodcount) + 1;
			// Открываем достижения
			if(sti(pchar.questTemp.foodcount) >= 50) UnlockAchievement("AchFood", 1);
			if(sti(pchar.questTemp.foodcount) >= 150) UnlockAchievement("AchFood", 2);
			if(sti(pchar.questTemp.foodcount) >= 300) UnlockAchievement("AchFood", 3);
		}
	}
}
bool IsQuestUsedItem(string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 ) return false;
	if( CheckAttribute(arItm,"price") && sti(arItm.price)>0 ) return false;
	return true;
}

void DoCharacterUsedItem(ref chref, string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 ) return;
	TakeItemFromCharacter(chref,itmID);

	 // Warship 13.06.09 fix - если только отравлен, а жизни полные (а такое бывает), то нечего и строку в лог выводить об прибавлении жизней
	if(CheckAttribute(arItm,"potion.health") && LAi_GetCharacterHP(chref) < LAi_GetCharacterMaxHP(chref))
	{
		LAi_UseHealthBottle(chref,stf(arItm.potion.health));
		if(sti(chref.index)==GetMainCharacterIndex()) {
			Log_SetStringToLog( XI_ConvertString("Health Up")+" ("+GetConvertStr(arItm.name, "ItemsDescribe.txt")+")");
			PlaySound("interface\_Glotok_"+rand(3)+".wav");
		}
		// boal
		if( CheckAttribute(arItm,"potion.health.speed") )
		{
			LAi_UseHealthBottleSpeed(chref, stf(arItm.potion.health.speed));
		}
		if(sti(chref.index)==GetMainCharacterIndex())
		{
			pchar.questTemp.healcount = sti(pchar.questTemp.healcount) + 1;

			// Открываем достижения
			if(sti(pchar.questTemp.healcount) >= 50) UnlockAchievement("heal_bottles", 1);
			if(sti(pchar.questTemp.healcount) >= 100) UnlockAchievement("heal_bottles", 2);
			if(sti(pchar.questTemp.healcount) >= 200) UnlockAchievement("heal_bottles", 3);
		}
	}

	// Warship 13.06.09 fix - если не отравлен, то нечего и строку в лог выводить
	if(CheckAttribute(arItm,"potion.antidote") && LAi_IsPoison(chref))
	{
		LAi_UseAtidoteBottle(chref);
		if(sti(chref.index)==GetMainCharacterIndex()) {
			Log_SetStringToLog( XI_ConvertString("You are cured from poison") );
		}
		else{
			Log_SetStringToLog(GetFullName(chref) + XI_ConvertString("are cured from poison") );
		}
	}

	//navy --> алкоголь
	if (CheckAttribute(arItm, "potion.drunk"))
	{
		LAi_AlcoholSetDrunk(chref, stf(arItm.potion.drunk), stf(arItm.potion.drunk.time));
		if(sti(chref.index)==GetMainCharacterIndex())
		{
			Log_SetStringToLog( XI_ConvertString("You're get drunk") );
		}
	}
	//<--
	if( CheckAttribute(arItm,"potion.sound") )
	{
		PlaySound(arItm.potion.sound);
	}
}

float MinHealthPotionForCharacter(ref chref)
{
	float ftmp;
	bool isFinded = false;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"potion") )
		{
			if(CheckAttribute(&Items[n],"potion.health"))
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					if(isFinded)
					{
						if( stf(Items[n].potion.health)<ftmp )
						{
							ftmp = stf(Items[n].potion.health);
						}
					}else{
						ftmp = stf(Items[n].potion.health);
						isFinded = true;
					}
				}
			}
		}
	}
	if(!isFinded) return 0.0;
	return ftmp;
}

string FindHealthForCharacter(ref chref,float fHealth)
{
	string sret = "";
	float fdelta = fHealth + 100.0;
	float ftmp;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"potion") )
		{
			if( CheckAttribute(&Items[n],"potion.health") )
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					ftmp = stf(Items[n].potion.health);
					if( ftmp<fHealth )	{ftmp = fHealth - ftmp;}
					else	{ftmp = ftmp - fHealth;}
					if(ftmp<fdelta)
					{
						fdelta = ftmp;
						sret = Items[n].id;
					}
				}
			}
		}
	}

	return sret;
}

string FindFoodForCharacter(ref chref,float fHealth)
{
	string sret = "";
	float fdelta = fHealth + 100.0;
	float ftmp;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"Food") )
		{
			if( CheckAttribute(&Items[n],"Food.energy") )
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					ftmp = stf(Items[n].Food.energy);
					if( ftmp<fHealth )	{ftmp = fHealth - ftmp;}
					else	{ftmp = ftmp - fHealth;}
					if(ftmp<fdelta)
					{
						fdelta = ftmp;
						sret = Items[n].id;
					}
				}
			}
		}
	}
	return sret;
}
int FindPotionFromChr(ref chref, ref arFind, int startIdx)
{
	int i;
	aref arItm;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"potion") && GetCharacterItem(chref,Items[i].id)>0 )
		{
			arFind = arItm;
			return i;
		}
	}
	return -1;
}

int UseBestPotion(ref chref, bool needAntidote)
{
	int i;
	int curPotionID = -1;
	int curPotionHealAmt = 0;
	int newPotionHealAmt = 0;
	bool potionTooGood = false;
	bool bValidPot;
	int reqHealAmt = LAi_GetCharacterMaxHP(chref) - LAi_GetCharacterHP(chref);
	reqHealAmt = makeint(MakeFloat(reqHealAmt) * 1.2)
	if (reqHealAmt <=0 && !needAntidote)
	{
		return -1;
	}

	aref arItm;
	for(i=1; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		bValidPot = false;

		if (CheckAttribute(pchar,"usepotionbest"))
		{
			if (!needAntidote && CheckAttribute(arItm,"potion.health"))
			{
				bValidPot = true;
			}
			if (needAntidote && CheckAttribute(arItm,"potion.antidote"))
			{
				bValidPot = true;
			}
		}
		else
		{
			if (!needAntidote && CheckAttribute(arItm,"potion.health") && !CheckAttribute(arItm,"potion.antidote"))
			{
				bValidPot = true;
			}
			else
			{
				if (needAntidote && CheckAttribute(arItm,"potion.antidote"))
				{
					bValidPot = true;
				}
			}
		}

		if( bValidPot && (GetCharacterItem(chref,arItm.id) > 0))
		{
			if (CheckAttribute(pchar,"usepotionbest"))
			{
				if (CheckAttribute(arItm,"potion.health"))
					newPotionHealAmt = arItm.potion.health;
				else
					newPotionHealAmt = 0;

				if (newPotionHealAmt > curPotionHealAmt)
				{
					curPotionID = i;
					curPotionHealAmt = newPotionHealAmt;
				}
			}
			else
			{
				if (CheckAttribute(arItm,"potion.health"))
					newPotionHealAmt = arItm.potion.health;
				else
					newPotionHealAmt = 0;

				if (potionTooGood)
				{
					if (newPotionHealAmt < curPotionHealAmt)
					{
						curPotionID = i;
						curPotionHealAmt = newPotionHealAmt;
					}
				}
				else
				{
					if ((newPotionHealAmt + 1) > curPotionHealAmt)
					{
						if (curPotionHealAmt == 0 || newPotionHealAmt <= reqHealAmt)
						{
							curPotionID = i;
							curPotionHealAmt = newPotionHealAmt;
						}
					}
				}
				if (curPotionHealAmt > reqHealAmt)
				{
					potionTooGood = true;
				}
			}
		}
	}

	if (curPotionID > 0)
	{
		DoCharacterUsedItem(pchar, Items[curPotionID].id);
		return 1;
	}
	else return 0;
}

int FindQuestUsableItem(ref arFind, int startIdx)
{
	int i;
	aref arItm;
	bool bSeaInterface = bSeaActive && !bAbordageStarted;

	if(startIdx<0) startIdx=0;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"quest") && CheckAttribute(arItm,"quest.tex"))// boal 16.03.2004
		{
			if( bSeaInterface && arItm.quest.tex=="QuestCommands" )
			{
				arFind = arItm;
				return i;
			}
		}
	}

	return -1;
}

bool EnablePotionUsing(ref mc, aref arItm)
{
	if( CheckAttribute(arItm,"potion.health") ) {
		if( LAi_GetCharacterHP(mc)<LAi_GetCharacterMaxHP(mc) ) {
			return true;
		}
	}

	return false;
}

// Warship 13.06.09 Для противоядий
bool EnableAntidoteUsing(ref _char, aref _item)
{
	if(CheckAttribute(_item, "potion.antidote") && LAi_IsPoison(_char) && CheckCharacterItem(_char, _item.Id))
	{
		return true;
	}

	return false;
}

bool FindCharacterAntidote(ref _char, ref _itemId)
{
	int itemIndex;
	ref item;

	for(itemIndex = 0; itemIndex < ITEMS_QUANTITY; itemIndex++)
	{
		item = &Items[itemIndex];

		if(EnableAntidoteUsing(_char, item))
		{
			_itemID = item.ID;
			return true;
		}
	}

	return false;
}

int FindItem(string sItemID)
{
	// Warship 07.07.09 Перевел на движковую функцию - по-идее, так должно работать быстрее
	return NativeFindCharacter(&Items, GetOriginalItem(sItemID));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Warship 08.05.09 НОВАЯ СИСТЕМА ПРЕДМЕТОВ -->
//      Ugeen --> 10.02.10 добавлена первичная генерация предметов и выбор из массива сгенерированных предметов
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Проверка, уникален ли каждый предмет "серии", или же идентичен
#define GEN_ITEM_DISCRET 100
#define GEN_ITEM_SEPARATOR "|"

bool IsGenerableItemIndex(int idx)
{
	ref itemRef = &Items[idx];
	return CheckAttribute(itemRef, "Generation");
}

bool IsGenerableItem(String _itemID)
{
	int itemIndex = GetItemIndex(_itemID);
	if (itemIndex == -1)
	{
		return false;
	}

	return IsGenerableItemIndex(itemIndex);
}

bool IsGeneratedItem(String _itemID)
{
	return findSubStr(_itemID, GEN_ITEM_SEPARATOR, 0) >= 0;
}

string GenerateBladeByParams(string sItemID, float dmg_min, float dmg_max, float weight)
{
	string sOriginalItemID = GetOriginalItem(sItemID);

	string dmg_min_scaled = sti(dmg_min * GEN_ITEM_DISCRET);
	string dmg_max_scaled = sti(dmg_max * GEN_ITEM_DISCRET);
	string weight_scaled = sti(weight * GEN_ITEM_DISCRET);

	return sOriginalItemID + GEN_ITEM_SEPARATOR +
		dmg_min_scaled + GEN_ITEM_SEPARATOR +
		dmg_max_scaled + GEN_ITEM_SEPARATOR +
		weight_scaled;
}

string GetOriginalItem(string sItemID)
{
	if (sItemID == "") return "";
	int sub = findSubStr(sItemID, GEN_ITEM_SEPARATOR, 0);
	if (sub > 0)
	{
		string result = strcut(sItemID, 0, sub - 1);
		return result;
	}
	return sItemID;
}

string GetBladeParams(string sItemID, ref dmg_min, ref dmg_max, ref weight)
{
	int sub0 = findSubStr(sItemID, GEN_ITEM_SEPARATOR, 0);
	if (sub0 < 0)
	{
		ref item = ItemsFromID(sItemID);
		dmg_min = item.dmg_min;
		dmg_max = item.dmg_max;
		weight = item.weight;
		return sItemID;
	}

	string origItemID = strcut(sItemID, 0, sub0 - 1);

	int sub1 = findSubStr(sItemID, GEN_ITEM_SEPARATOR, sub0 + 1);
	if (sub1 < 0) { return "ERROR"; }
	dmg_min = stf(strcut(sItemID, sub0 + 1, sub1 - 1)) / GEN_ITEM_DISCRET;

	int sub2 = findSubStr(sItemID, GEN_ITEM_SEPARATOR, sub1 + 1);
	if (sub2 < 0) { return "ERROR"; }
	dmg_max = stf(strcut(sItemID, sub1 + 1, sub2 - 1)) / GEN_ITEM_DISCRET;

	weight = stf(strcut(sItemID, sub2 + 1, strlen(sItemID) - 1)) / GEN_ITEM_DISCRET;

	return origItemID;
}

float GetItemWeight(string sItemID)
{
	if (!IsGeneratedItem(sItemID))
	{
		ref item = ItemsFromID(sItemID);
		if (!CheckAttribute(item, "weight"))
		{
			return 0;
		}
		return stf(item.weight);
	}

	float dmg_min, dmg_max, weight;
	GetBladeParams(sItemID, &dmg_min, &dmg_max, &weight);

	return weight;
}

int CalculateBladePrice(string fencingType, float dmg_min, float dmg_max, float weight)
{
	int priceMod = 1;
	switch(fencingType)
	{
		case "FencingLight": // Легкое оружие
			priceMod = 4;
		break;

		case "Fencing": // Среднее оружие
			priceMod = 5;
		break;

		case "FencingHeavy": // Тяжелое оружие
			priceMod = 7;
		break;
	}

	return sti(priceMod * dmg_min * dmg_max / weight);
}

int GetItemPrice(String _itemId)
{
	ref item = ItemsFromID(_itemId);

	if (!IsGeneratedItem(_itemId))
	{
		if (!CheckAttribute(item, "price"))
		{
			return -1;
		}
		return sti(item.price);
	}

	float dmg_min, dmg_max, weight;
	GetBladeParams(_itemId, &dmg_min, &dmg_max, &weight);

	return CalculateBladePrice(item.FencingType, dmg_min, dmg_max, weight);
}

// Создадим предмет, вернет АйДи нового предмета
string GenerateItem(String _itemId)
{
	_itemId = GetOriginalItem(_itemId);

	int itemIndex = GetItemIndex(_itemID);
	if (itemIndex == -1)
	{
		return _itemID;
	}

	ref item = &Items[itemIndex];
	if (!CheckAttribute(item, "Generation")) // Генерящийся ли предмет
	{
		return _itemID;
	}

	int minValue, maxValue;

	// Минимальный урон
	minValue = stf(item.Generation.dmg_min.min) * GEN_ITEM_DISCRET; // Нижняя граница атрибута
	maxValue = stf(item.Generation.dmg_min.max) * GEN_ITEM_DISCRET; // Верхняя граница атрибута
	float minDmg = stf(minValue + rand(maxValue - minValue)) / GEN_ITEM_DISCRET;

	// Максимальный урон
	minValue = stf(item.Generation.dmg_max.min) * GEN_ITEM_DISCRET; // Нижняя граница атрибута
	maxValue = stf(item.Generation.dmg_max.max) * GEN_ITEM_DISCRET; // Верхняя граница атрибута
	float maxDmg = stf(minValue + rand(maxValue - minValue)) / GEN_ITEM_DISCRET;

	// Вес
	minValue = stf(item.Generation.Weight.min) * GEN_ITEM_DISCRET; // Нижняя граница атрибута
	maxValue = stf(item.Generation.Weight.max) * GEN_ITEM_DISCRET; // Верхняя граница атрибута
	float weight = stf(minValue + rand(maxValue - minValue)) / GEN_ITEM_DISCRET;

	return GenerateBladeByParams(_itemId, minDmg, maxDmg, weight);
}

string ModifyGeneratedBlade(string sItemID, float delta_dmg_min, float delta_dmg_max, float delta_weight)
{
	if (!IsGenerableItem(sItemID))
	{
		return sItemID;
	}

	ref item = ItemsFromID(sItemID);

	float dmg_min, dmg_max, weight;
	string origItem = GetBladeParams(sItemID, &dmg_min, &dmg_max, &weight);

	dmg_min += delta_dmg_min;
	if (dmg_min < stf(item.Generation.dmg_min.min)) dmg_min = stf(item.Generation.dmg_min.min);
	if (dmg_min > stf(item.Generation.dmg_min.max)) dmg_min = stf(item.Generation.dmg_min.max);

	dmg_max += delta_dmg_max;
	if (dmg_max < stf(item.Generation.dmg_max.min)) dmg_max = stf(item.Generation.dmg_max.min);
	if (dmg_max > stf(item.Generation.dmg_max.max)) dmg_max = stf(item.Generation.dmg_max.max);

	weight += delta_weight;
	if (weight < stf(item.Generation.weight.min)) weight = stf(item.Generation.weight.min);
	if (weight > stf(item.Generation.weight.max)) weight = stf(item.Generation.weight.max);

	return GenerateBladeByParams(origItem, dmg_min, dmg_max, weight);
}

bool BladeIsPerfect(string sItemID)
{
	if (!IsGenerableItem(sItemID))
	{
		return true;
	}

	ref item = ItemsFromID(sItemID);

	float dmg_min, dmg_max, weight;
	string origItem = GetBladeParams(sItemID, &dmg_min, &dmg_max, &weight);

	return (dmg_min == stf(item.Generation.dmg_min.max)) &&
		(dmg_max == stf(item.Generation.dmg_max.max)) &&
		(weight == stf(item.Generation.weight.min));
}

string ImproveGeneratedBlade(string sItemID, float improveAmount)
{
	if (!IsGenerableItem(sItemID))
	{
		return sItemID;
	}

	ref item = ItemsFromID(sItemID);

	float dmg_min, dmg_max, weight, statNew;
	string origItem = GetBladeParams(sItemID, &dmg_min, &dmg_max, &weight);

	bool dmg_min_perfect = dmg_min == stf(item.Generation.dmg_min.max);
	bool dmg_max_perfect = dmg_max == stf(item.Generation.dmg_max.max);
	bool weight_perfect = weight == stf(item.Generation.weight.min);
	int statsToChoose = !dmg_min_perfect + !dmg_max_perfect + !weight_perfect;
	if (statsToChoose == 0)
	{
		return sItemID;
	}

	int seed = sti((dmg_min + dmg_max + weight) * GEN_ITEM_DISCRET);
	int statInd = seed % statsToChoose;

	if (!dmg_min_perfect)
	{
		if (statInd == 0)
		{
			statNew = (stf(item.Generation.dmg_min.max) - stf(item.Generation.dmg_min.min)) * improveAmount;
			statNew = retMin(dmg_min + statNew, stf(item.Generation.dmg_min.max));
			Log_Info("Минимальный урон клинка повышен с " + dmg_min + " до " + statNew);
			dmg_min = statNew;
		}
		statInd = statInd - 1;
	}

	if (!dmg_max_perfect)
	{
		if (statInd == 0)
		{
			statNew = (stf(item.Generation.dmg_max.max) - stf(item.Generation.dmg_max.min)) * improveAmount;
			statNew = retMin(dmg_max + statNew, stf(item.Generation.dmg_max.max));
			Log_Info("Максимальный урон клинка повышен с " + dmg_max + " до " + statNew);
			dmg_max = statNew;
		}
		statInd = statInd - 1;
	}

	if (!weight_perfect)
	{
		if (statInd == 0)
		{
			statNew = (stf(item.Generation.weight.max) - stf(item.Generation.weight.min)) * improveAmount;
			statNew = retMax(weight - statNew, stf(item.Generation.weight.min));
			Log_Info("Вес клинка снижен с " + weight + " до " + statNew);
			weight = statNew;
		}
	}

	return GenerateBladeByParams(origItem, dmg_min, dmg_max, weight);
}

//ugeen --> вернем случайный ID сгенерированного зараннее предмета
string GetGeneratedItem(string _itemId)
{
	return GenerateItem(_itemID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										<-- Warship НОВАЯ СИСТЕМА ПРЕДМЕТОВ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Warship Проверка на оружие
bool IsBlade(String _itemID)
{
	int itemIndex = GetItemIndex(_itemID);
	ref item;

	if (itemIndex == -1)
	{
		return false;
	}

	item = &Items[itemIndex];

	if (CheckAttribute(&item, "groupID"))
	{
		if (item.groupID == BLADE_ITEM_TYPE)
		{
			return true;
		}
	}

	return false;
}

// eddy -->
/////////////////////// ==> Items-методы
int GetItemIndex(string _ItemID)
{
	return FindItem(_ItemID);
}

ref ItemsFromID(string _Items)
{
	return &items[GetItemIndex(_Items)];
}

void ChangeItemDescribe(string _Items, string _Describe)
{
    Items[GetItemIndex(_Items)].describe = _Describe;
}

void BackItemDescribe(string _Items)
{
    ref ItemAR = ItemsFromID(_Items);
    ItemAR.describe = "itmdescr_" + ItemAR.id;
}

void ChangeItemName(string _Items, string _Name)
{
    Items[GetItemIndex(_Items)].name = _Name;
}

void BackItemName(string _Items)
{
    ref ItemAR = ItemsFromID(_Items);
    ItemAR.name = "itmname_" + ItemAR.id;
}
///////////////////////  Items-методы <--


void QuestCheckEnterLocItem(aref _location, string _locator) /// <<<проверка вхождения ГГ в локаторы группы Item.<<<
{
	ref sld;
	int i;
	//======> Генератор инквизиции.
	if (_location.id == "Santiago_Incquisitio" && CheckNPCQuestDate(_location, "AttackGuard_date") && sti(Colonies[FindColony(_location.fastreload)].nation) == SPAIN && findsubstr(_locator, "detector" , 0) != -1)
	{
		SetNPCQuestDate(_location, "AttackGuard_date"); //одна засада в день.

		if (CheckAttribute(pchar, "questTemp.WhisperTutorial"))
		{
			//Стража только вернулась после обеда и немного не в форме
			DoQuestFunctionDelay("WhisperIncqAlarm", 2.5);
		}
		else
		{
			StartIncquisitioAttack();
			LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
		}

		//==>фр.линейка, квест №7. Рок Бразилец, даем диалог.
		if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace") LAi_ActorWaitDialog(characterFromId("RockBrasilian"), pchar);
	}
	//=======> Квест Изабеллы, детектор на скрипт базара Сальватора с братом
	if (_location.id == "SanJuan_town" && pchar.RomanticQuest == "SeeTalkNearHouse")
	{
        pchar.quest.Romantic_DeadBrother_Cancel.over = "yes"; //убираем таймер на вовремя не явлился
		StartQuestMovie(true, true, true);
		pchar.RomanticQuest = "BrotherIsDead";
		LAi_SetActorType(pchar);
		SetMainCharacterIndex(GetCharacterIndex("Husband"));
        locCameraToPos(40.585, 6.0, -47.549, false);
		LAi_SetActorType(PChar);
		PChar.BaseNation = SPAIN; //скрипт в городе, иначе глючит опрос патрулями
		PChar.RomanticQuest = "";
		LAi_SetActorType(CharacterFromID("MigelDeValdes"));
		SetActorDialogAny2Pchar("MigelDeValdes", "", 1.0, 0.0);
		LAi_ActorFollow(pchar, CharacterFromID("MigelDeValdes"), "ActorDialog_Any2Pchar", 0.0);
	}
	//=======> Квест Изабеллы, закрываем дверь дома, если прошлялся не заходя домой более 3 месяцев
	if (_location.id == "SanJuan_town" && pchar.RomanticQuest == "NewLifeForHero")
	{
		if (GetQuestPastMonthParam("RomanticQuest") > 3)
		{
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true);
			pchar.RomanticQuest = "TheDoosIsClosed";
			AddQuestRecord("Romantic_Line", "29");
		}
	}
	//=======> Квест Изабеллы, закрываем дверь дома, если был у шлюх
	if (_location.id == "SanJuan_town" && CheckAttribute(pchar, "RomanticQuest.HorseCheck") && pchar.RomanticQuest.HorseCheck != "-1" && sti(pchar.questTemp.HorseQty) > sti(pchar.RomanticQuest.HorseCheck))
	{
		LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true);
		pchar.RomanticQuest = "over";
		pchar.RomanticQuest.HorseCheck = -1;
		AddQuestRecord("Romantic_Line", "29");
	}
	//======> Генератор маяка Порт Рояля.
	if (_location.id == "Mayak3")
	{
		int iNation = GetCityNation(GetCityNameByIsland(GiveArealByLocation(_location)));
		if(iNation == -1) return;
		string sGroup = GetNationNameByType(iNation)  + "_mayak";
		LAi_group_AttackGroup(sGroup, LAI_GROUP_PLAYER);
	}
	//======> Генератор монстров при входе в локатор духов
	if (_locator == "duhi1" && CheckAttribute(_location, "locators.monsters") && !bMonstersGen)
	{
		//проверяем флаг запрещения генерации
		if(LAi_LocationIsMonstersGen(_location) && LAi_grp_playeralarm == 0 && GenQuest_CheckMonstersGen() && _location.id != "Treasure_alcove")
		{
			if (pchar.sex == "Skeleton" && GetCharacterEquipSuitID(pchar)!= "suit_1")
			{
				sTemp = "skel_"+(rand(3)+1);
				sld = GetCharacter(NPC_GenerateCharacter("Skelet_Drug", sTemp, "skeleton", "skeleton", 3, PIRATE, -1, true));
				LAi_SetActorType(sld);
				PlaceCharacter(sld, "monsters", PChar.location);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
				sld.lifeday = 0;
				sld.dialog.filename = "Sailor.c";
				sld.dialog.currentnode = "First time";
				LAi_SetImmortal(sld, true);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				if (rand(20) <= 10+GetSummonSkillFromNameToOld(GetMainCharacter(),SKILL_LEADERSHIP)) // WW нанимаются в команду в % от авторитета (У нежити выше шанс)
				{
					sld.quest.crew = "true";
					sld.quest.crew.qty = 10+rand(14)+(GetSummonSkillFromNameToOld(GetMainCharacter(),SKILL_LEADERSHIP) * 8); // WW 10-24 + 6-60 = 16-84 от авторитета
					sld.quest.crew.type = rand(2);
					sld.quest.crew.money = (30+rand(2)*10+rand(50))*(1+(sti(Pchar.rank)/4))+rand(100);	//Для нежити дешевле
				}
				bMonstersGen = true; //флаг генерации скелетов
				for (i=1; i<=15; i++)
				{
				sTemp = "skel_"+(rand(3)+1);
				sld = GetCharacter(NPC_GenerateCharacter("Skelet_Drug_"+i, sTemp, "skeleton", "skeleton", 3, PIRATE, -1, true));
				PlaceCharacter(sld, "monsters", "random_free");
				LAi_SetWarriorType(sld);
				sld.lifeday = 0;
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
				}
			}
			else
			{
				SetSkeletonsToLocation(_location);
			}
		}
	}
	if (_locator == "spawndeadsmangod")
	{
		if (!CheckAttribute(pchar,"UmSamil") && CheckAttribute(pchar,"UmSamilGuardsDefeated"))
		{
			LoginDeadmansGod2();
			pchar.UmSamil = true;
		}
	}
	if (_locator == "fire3" && _location.id == "MountainPath")
	{
		//проверяем флаг запрещения генерации
		if(LAi_LocationIsMonstersGen(_location) && LAi_grp_playeralarm == 0 && GenQuest_CheckMonstersGen())
		{
			if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 6.0) SetReefSkeletonsToLocation(_location, "MountainPath");
		}
	}
	if (_location.id == "DeckWithReefs")
	{
		if (_locator == "fire56")
		{
			//проверяем флаг запрещения генерации
			if(LAi_LocationIsMonstersGen(_location) && LAi_grp_playeralarm == 0 && GenQuest_CheckMonstersGen())
			{
				if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 6.0) SetReefSkeletonsToLocation(_location, "DeckWithReefs");
			}
		}
		if (_locator == "item1" && !CheckAttribute(pchar,"talismangot") && CheckAttribute(pchar,"talismanpreget"))
		{
			PlayStereoSound("notebook");
			log_info("Вы получили оберег ''Святая Чаша''.");
			TakeNItems(pchar,"talisman9",1);
			pchar.talismangot = true;
		}
	}
	//======> детектор в тюрьме, вторжение без разрешения
	if (_location.type == "jail" && !sti(pchar.questTemp.jailCanMove) && _locator == "detector1")
	{
		pchar.questTemp.jailCanMove = true; //чтобы не срабатывало 2 раза
		if (!LAi_grp_alarmactive && !IsLocationCaptured(_location.id))
		{
			string slai_group = GetNationNameByType(GetCityNation(_location.parent_colony)) + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_SetFightMode(pchar, true);
		}
	}
	//======> установка метки нахождения в локаторе item1 в погребке
	if (pchar.questTemp.LSC == "toInterception" && _location.id == "FleuronTavern" && _locator == "detector1")
	{
        pchar.questTemp.LSC.itemState = true;
	}
	//======> скафандр
	if (pchar.questTemp.LSC == "toUnderwater" && _location.id == "FenixPlatform")
	{
		if (pchar.model == "protocusto")
		{	//смена со скафандра на норму
			bDisableFastReload = false;
			i = FindLocation("FenixPlatform");
			Locations[i].models.always.inside = "FenixPlatform";
			pchar.model = pchar.questTemp.LSC.immersions.model;
			pchar.model.animation = pchar.questTemp.LSC.immersions.animation;
			LocatorReloadEnterDisable("LostShipsCity_town", "reload58", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload73", true);
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload72", "");
		}
		else
		{	//смена с нормы на скафандр
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				bDisableFastReload = true;
				i = FindLocation("FenixPlatform");
				Locations[i].models.always.inside = "FenixPlatform_wout";
				if (findsubstr(pchar.model.animation, "mushketer" , 0) != -1) SetMainCharacterToMushketer("", false);
				pchar.questTemp.LSC.immersions.model = pchar.model;
				pchar.questTemp.LSC.immersions.animation = pchar.model.animation;
				pchar.model = "protocusto";
				pchar.model.animation = "armor";
				LocatorReloadEnterDisable("LostShipsCity_town", "reload58", true);
				LocatorReloadEnterDisable("LostShipsCity_town", "reload73", false);
				DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload72", "");
			}
		}
	}
}

void QuestCheckExitLocItem(aref _location, string _locator) /// <<<проверка выхода ГГ из локаторов группы Item.<<<
{
	//=======> Испанская линейка, квест №4. В спальне нашёл возле комода нашёл недописанное письмо
	if (_location.id == "Havana_houseS1Bedroom" && pchar.questTemp.State == "Sp4Detection_toMirderPlace" && CheckCharacterItem(pchar, "letter_notes"))
    {
        DoQuestCheckDelay("TalkSelf_Quest", 0.1); //диалог сам-на-сам
    }
	//=======> Квест Аскольда, нашли гробницу.
    if (_location.id == "Guadeloupe_Cave" && _locator == "detector1")
    {
        if (pchar.questTemp.Ascold == "Ascold_SeekGrave" || pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
        {
            Log_QuestInfo("Прерывание на нахождение входа в пещеру сработало.");
            pchar.questTemp.Ascold = "Ascold_NotEnterFoundGrave";
    		DoQuestCheckDelay("TalkSelf_Quest", 0.1); //диалог сам-на-сам
        }
    }
	//=======> Квест Аскольда, ГГ добрался до мумии, но бутылки ещё не имеет. Вместо прерывания на локатор.
    if (_location.id == "Guadeloupe_Cave" && _locator == "button02")
    {
		if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" || pchar.questTemp.Ascold == "Ascold_EnterGrave")
		{
			pchar.questTemp.Ascold = "Ascold_FoundMummy";
			characters[GetCharacterIndex("Ascold")].dialog.currentnode = "Found_Grave";
		}
	}
	//=======> Энкаунтеры заманухи в пещеру, открываем закрытый релоад на колодце.
    if (_locator == "CheckReload1" && CheckAttribute(pchar, "GenQuest.OpenTheRopeExit") && pchar.GenQuest.OpenTheRopeExit == pchar.location)
    {
		DeleteAttribute(pchar, "GenQuest.OpenTheRopeExit");
		LocatorReloadEnterDisable(pchar.location, "reload2", false);
	}
	//=======> Изабелла, в доме начало скрипта с братом
    if (_location.id == "SanJuan_houseSp6" && pchar.RomanticQuest == "exitFromDetector")
    {
		pchar.RomanticQuest = "executeFromDetector";
		StartQuestMovie(true, true, true);
		// ГГ теперь Сальватор
		//sGlobalTemp = GetMainCharacterIndex();
		SetMainCharacterIndex(GetCharacterIndex("MigelDeValdes"));
        PChar   = GetMainCharacter();
		locCameraToPos(-2.41, 2.35, -2.41, false);
		SetActorDialogAny2Pchar("Isabella", "", 3.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Isabella"), "ActorDialog_Any2Pchar", 4.0);
	}
	//=======> Изабелла, в доме Роситы после смерти мужа
    if (_location.id == "Beliz_houseS4" && pchar.RomanticQuest == "Beliz_exitFromDetector")
    {
		pchar.RomanticQuest = "Beliz_executeFromDetector";
		StartQuestMovie(true, true, true);
        // ГГ теперь Изабелла
		ChangeCharacterAddressGroup(CharacterFromID("Isabella"), pchar.location, "goto",  "goto3");
		ChangeCharacterAddressGroup(CharacterFromID("Rosita"), pchar.location, "goto",  "goto1");
        SetMainCharacterIndex(GetCharacterIndex("Isabella"));
        PChar   = GetMainCharacter();
        locCameraToPos(-3.84, 2.35, 0.85, false);
		LAi_SetActorType(CharacterFromID("Rosita"));
		LAi_SetActorType(pchar);
		PChar.BaseNation = SPAIN; //скрипт в городе, иначе глючит опрос патрулями
		SetActorDialogAny2Pchar("Rosita", "", 1.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Rosita"), "ActorDialog_Any2Pchar", 0.0);
	}
	//=======> Пиратка, квест №5
    if (_location.id == "Pirates_houseS1" && pchar.questTemp.piratesLine == "PL5Hunter_exitReload")
    {
		pchar.questTemp.piratesLine = "PL5Hunter_executeReload";
		StartQuestMovie(true, true, true);
		SetMainCharacterIndex(GetCharacterIndex("Orry"));
        PChar   = GetMainCharacter();
		locCameraToPos(1.34, 2.1, 1.68, false);
		LAi_SetActorType(CharacterFromID("Aivory"));
		LAi_SetActorType(pchar);
		SetActorDialogAny2Pchar("Aivory", "", 3.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Aivory"), "ActorDialog_Any2Pchar", 4.0);
	}
	//======> установка метки нахождения в локаторе item1 в погребке
	if (pchar.questTemp.LSC == "toInterception" && _location.id == "FleuronTavern" && _locator == "detector1")
	{
		pchar.questTemp.LSC.itemState = false;
	}
}

void QuestCheckUseButton(aref _location, string _locator, string _itemId) /// <<< квестовые действия при установке предметов в button <<<
{
    //==> Квест Аскольда, установка скрижалей для открытия входа в пещеру к гробнице.
    if (_location.id == "Guadeloupe_Cave" && _locator == "button01")
    {
		//==> перебиваем иниты пещеры Гваделупы
		_location.reload.l1.name = "reload3_back";
		locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.emerge = "reload3";
		//==> перемещаемся на reload5
		DoQuestFunctionDelay("Ascold_OpenTheGrave", 1.5);
    }
    //==> Квест Аскольда, вскрытие гробницы кочергой.
    if (_location.id == "Guadeloupe_Cave" && _locator == "button02" && pchar.questTemp.Ascold == "Ascold_WateringMummy")
    {
        ref sld;
		for (int i=1; i<=3; i++)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Enemy_"+i, "Skel"+i, "skeleton", "skeleton", 30, PIRATE, 0, true));
			FantomMakeCoolFighter(sld, 30, 85, 85, "topor2", "pistol3", 100);
            LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
            ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
        }
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "Ascold_InGraveAfterFight");
        chrDisableReloadToLocation = true;
    }
    //==> Квест Аскольда, вскрытие лампы и появление Аззи на верфи
    if (_location.id == (pchar.questTemp.Ascold.ShipyarderColony + "_shipyard") && _locator == "button01")
    {
		LAi_SetActorType(PChar);
		DoQuestCheckDelay("TalkSelf_Quest", 0.2);
    }
	//==> Пиратка, квест №7
    if (_location.id == "PuertoPrincipe_town" && _locator == "button01")
    {
		ref loc = &locations[FindLocation("PuertoPrincipe_townhall")];
		loc.reload.l2.name = "reload2";
		loc.reload.l2.go = "PuertoPrincipe_town";
		loc.reload.l2.emerge = "reload9";
		loc.reload.l2.autoreload = "0";
		loc.reload.l2.label = "Street";
		DoQuestFunctionDelay("PQ7_loadToRecidence", 2.0);
	}
	//установки тотемов в храмах
    if (findsubstr(_itemId, "Totem_" , 0) != -1)
    {
		SetItemModelOnLocation(_location, _itemId, _locator);
		SetAztecUsedTotem(_location, _itemId, _locator);
	}
	//открываем доступ в храм к шотгану
    if (_itemId == "KnifeAztec")
    {
		SetItemModelOnLocation(_location, _itemId, _locator);
		LocatorReloadEnterDisable("Tenochtitlan", "reloadTemple31", false);
	}
}
//проверка взятия предметов из локатора item
void QuestCheckTakeItem(aref _location, string _itemId)
{
	//квест промышленного шпионажа не верфях
	if (_itemId == "ShipyardsMap")
	{
		AddQuestRecord("ShipyardsMap", "2");
		if (IsLoginTime() && !IsLocationCaptured(_location.id))
		{
			ref sld = characterFromId(_location.fastreload + "_shipyarder");
			sld.dialog.currentnode = "Allarm";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", 0, 0);
		}
	}
	//генератор - "Спихнуть судовые документы"
	if (_itemId == "CaptainBook")
	{
		ReOpenQuestHeader("GiveShipLetters");
		AddQuestRecord("GiveShipLetters", "1");
		AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("","а"));
	}
	//квест поиски кольца мэра в борделях
	if (_itemId == "MayorsRing")
	{
		AddQuestRecord("SeekMayorsRing", "6");
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
	}
	//квест поиска драгоценного камня ростовщика
	if (_itemId == "UsurersJew")
	{
		string sTitle = _location.townsack + "UsurersJewel";
		AddQuestRecordEx(sTitle, "SeekUsurersJewel", "2");
		if (drand(1)==0) SpawnGreedyBastards();
	}
	//пиратка, квест №7
	if (_itemId == "OpenBook")
	{
		AddQuestRecord("Pir_Line_7_Soukins", "9");
		SaveCurrentQuestDateParam("questTemp.piratesLine");
		pchar.questTemp.piratesLine = "Soukins_catchBattleship";
		Pchar.quest.PQ7_setBattleShip.win_condition.l1 = "MapEnter";
	    Pchar.quest.PQ7_setBattleShip.function = "PQ7_setBattleShip";
	}
	//линейка ГПК, квест со скелетом Декстера. найденный ключ адмирала
	if (_itemId == "keyPanama" && CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC.lostDecster == "admiralLostKey")
	{
		pchar.quest.LSC_admiralFoundOwnKey.over = "yes"; //снимаем таймер
		AddQuestRecord("LSC_findDekster", "12");
		CloseQuestHeader("LSC_findDekster");
		pchar.questTemp.LSC.lostDecster = "over";
	}
	//меняем сеабед у Тено, снимаем 11 тотем
	if (_itemId == "Totem_11")
	{
		_location.models.always.seabed = "TenochtitlanWout_sb";
	}
	//взятие нефритового черепа
	if (_itemId == "SkullAztec")
	{
		LoginDeadmansGod();
	}
}

void StartIncquisitioAttack()
{
	ref sld;
    for (int i=1; i<=5; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("IncqAddGuard_"+i, "sold_spa_"+(rand(7)+1), "man", "man", 35, SPAIN, 1, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8, 80, 70, BLADE_LONG, "pistol4", 50);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
        ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", LAi_FindRandomLocator("goto"));
    }
}

void SetItemModelOnLocation(ref loc, string model, string locator)
{
	loc.models.always.totem = model;
	loc.models.always.totem.locator.group = "item";
	loc.models.always.totem.locator.name = locator;
	loc.models.always.totem.tech = "DLightModel";
}
