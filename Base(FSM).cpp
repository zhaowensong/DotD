#include"Base(FSM).h"
#include<iostream>


//*********************************************************************************************
//********************************以下是常量***************************************************
//*********************************************************************************************
const short SCREEN_WIDTH=213;//屏幕横向字符宽度
const short SCREEN_HEIGHT=60;//屏幕纵向字符宽度
const short BATTLE_WIDTH = 213;//战场横向字符宽度
const short BATTLE_HEIGHT = 48;//战场纵向字符宽度
const int MAX_INPUT_RECORD = 10;//单次同时接受的输入数量上限
const short BATTLE_AREA = 48;//操作区与显示栏的分界线
const short IMAGE_INFO = 55;//头像区与信息区的分界线
const short INFO_FUNCTION = 113; //信息区与功能区的分界线
const int MAX_MONSTER_NUM = 3;//最大辅导员数量
const int MAX_HERO_NUM=5;//最大英雄数量
const int PIX_PER_WIDTH = 9;//一个字符宽占的像素
const int PIX_PER_HEIGHT = 18;//一个字符高占的像素
const short IMAGE_WIDTH_CHAR=30;//头像区宽度(字符计)
const short IMAGE_HEIGHT_CHAR=11;//头像区高度(字符计)
const int IMAGE_LEFT = 0;//头像区左边缘的像素X坐标
const int IMAGE_TOP = PIX_PER_HEIGHT * IMAGE_WIDTH_CHAR;//头像区右边缘的像素X坐标
const int IMAGE_WIDTH_PIX = PIX_PER_WIDTH * IMAGE_WIDTH_CHAR;//头像区宽度(像素计)
const int IMAGE_HEIGHT_PIX = PIX_PER_HEIGHT * IMAGE_HEIGHT_CHAR;//头像区高度(像素计)
const int THING_WIDTH_CHAR = 10;//功能区宽度(字符计)
const short THING_HEIGHT_CHAR = 5;//功能区高度(字符计)
const int THING_WIDTH_PIX = PIX_PER_WIDTH * THING_WIDTH_CHAR;//功能区宽度(像素计)
const int THING_HEIGHT_PIX = PIX_PER_HEIGHT * THING_HEIGHT_CHAR;//功能区高度(像素计)
const int MAX_THING_NUM = 6;//最多持有的(强化书/消耗品/装备/我方英雄技能)数量
const int MAX_MONSTER_SKILL_NUM = 3;//辅导员最多持有的技能数量
const DWORD DIVIDER_COLOR = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;//分割线颜色
const char SKILL_CHAR = '#';//技能填充字符
const char ATTACK_CHAR = '#';//攻击填充字符
const int EQUIPMENT_STOCK = 6;//装备种类数
const int CONSUMABLE_STOCK = 6;//消耗品种类数
const int ENHANCEBOOK_STOCK = 6;//强化书种类书
const int SKILL_STOCK = 60;//技能
const int GP_STOCK = 5;//英雄种类数
const int AI_STOCK = 3;//辅导员种类数
const int SELL_RATE = 6;//折价率
const int INTERVAL = 10;//相邻两轮的游戏时间间隔
const int INC_HERO_EXPERICAL=500;//升级经验增长值
const int INC_HERO_PRICE=1000;//英雄价格增长值
const int SecondMonsterTurnUp=10;//第二个辅导员出现的轮数
const int ThirdMonsterTurnUp=30;//第三个辅导员出现的轮数
const int RoundsToGetMoreOneEqipment=8;//隔几轮辅导员拿到一件新的装备
const int TestTime=1000;//检测攻击的时间长度/毫秒计
const int AI_STATE_NUM = 4;
const Attribute EMPTY_ATTRIBUTE = {Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const Special EMPTY_SPECIAL = {0,0,0,0};
const Buff EMPTY_BUFF = { 1,EMPTY_ATTRIBUTE ,EMPTY_SPECIAL ,NULL,NULL };
const short ImageMidium = 27;//头像的中分线
const short EyeHeight = BATTLE_AREA + 4;//眼睛的y坐标
const short EyeDistance = 5;//单眼和中分线的间距
const short MouthHeight = SCREEN_HEIGHT-2;//嘴巴y坐标
const short NoseHeight = (EyeHeight + MouthHeight) / 2 - 1;//鼻子y坐标
const short MouthWidth = 5;//嘴巴半宽度
const short EyebrowHeight = EyeHeight - 2;//眉毛y坐标
const COORD HERO_INITIAL_LOC = { 100,20 };//英雄初始降生位置
const COORD CITADEL = { 100,20 };//寝室位置
const DWORD TearColor = BACKGROUND_BLUE | BACKGROUND_INTENSITY;//眼泪的颜色
const DWORD MoneyColor = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;//钱的颜色
const DWORD DefaultColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;//默认颜色
const DWORD BloodColor = FOREGROUND_RED | FOREGROUND_INTENSITY;//血量 生命偷取颜色
const DWORD EnergyColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;//法力 法力汲取颜色
const DWORD PaColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;//攻击力颜色
const DWORD MaColor = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;//法强颜色
const DWORD PdColor = MoneyColor;//护甲颜色
const DWORD MdColor = FOREGROUND_BLUE | FOREGROUND_RED;//魔抗颜色
const DWORD SpeedColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;//速度颜色
const DWORD CrColor = FOREGROUND_RED;//暴击率颜色
const DWORD CitadelColor = BACKGROUND_RED | BACKGROUND_INTENSITY;//主城颜色
const DWORD Illidan_Stormrage = BACKGROUND_BLUE;//伊利丹·怒风
const DWORD Cairne_Bloodhoof = BACKGROUND_RED|BACKGROUND_GREEN;
const DWORD Tyrande_Whisperwind = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
const DWORD Grom_Hellscream = BACKGROUND_BLUE | BACKGROUND_RED;
const DWORD Uther = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED| BACKGROUND_INTENSITY;
const DWORD SKILL_COLOR = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;//技能文字颜色
const DWORD EQUIPMENT_COLOR = FOREGROUND_GREEN | FOREGROUND_INTENSITY;//装备文字颜色
const DWORD CONSUMABLE_COLOR= FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;//消耗品颜色
const DWORD GAME_INFO = SKILL_COLOR;//游戏信息颜色
#define AIStill 0
#define AIPosChase 1
#define AINegChase 2
#define AI_STATE_NUM 3






//*********************************************************************************************
//******************************以下是API变量**************************************************
//*********************************************************************************************
CONSOLE_SCREEN_BUFFER_INFO csbi;//控制台缓冲区信息
HWND hwnd;//窗口句柄
HDC hdc;//设备环境句柄
HDC hmendc;//兼容的设备环境句柄
HBRUSH hBlackBrush;//黑色的画刷
HANDLE hOut, hIn;//标准输入输出句柄
CONSOLE_CURSOR_INFO cursorInfo;//光标信息
BRICK_INFO Active[BATTLE_WIDTH][BATTLE_HEIGHT];//记录各个格子的活动信息，取横向为x 纵向为y
INPUT_RECORD Inputs[MAX_INPUT_RECORD];//输入事件数组
bool LeftButtonPressed;//标记左键是否按下
int CurScreen;//当前活动的屏幕号
DWORD InputOneTime;//单次读取的输入事件数
DWORD OldConsoleInputMode, NewConsoleInputMode;//输入模式
COORD LastMousePos;//记录上次鼠标位置
DWORD num;//作为一个保留变量 不真正使用 只是为了填充实参



//*********************************************************************************************
//*******************************以下是游戏内部变量********************************************
//*********************************************************************************************
MouseOperateState* CurMOPState;
MouseOperateState* TmpMOPState;
FormalState* FMState;
SkillingState* SMState;
TransportingState* TMState;
ShoppingState* PMState;
atomic_bool isShowingDetail;//是否在显示物品详细信息
atomic_bool isShowingHero;//是否在显示英雄信息
TYPE TransportedType;//正在转移的物品的类型
COORD RelativeLoc;//鼠标移动时的相对坐标
Skill* CurTriggeredSkill;//当前正在释放的技能
short TmpSkillRange;//释放技能的范围
int money;//当前的金钱
int CurHeroPrice;//当前购买英雄所需的钱
GPHero* Heros[MAX_HERO_NUM+1];//英雄数组
AIHero* Monsters[MAX_MONSTER_NUM + 1];//辅导员数组
GPHero* Shop;//特别指向商店
GPHero* Gotta;//受益者
atomic_int CurNum[MAX_CAMP_NUM];//英雄与怪物数量数组
HANDLE AttackMsg[MAX_MONSTER_NUM + 1];//英雄与怪物的可攻击信号
HANDLE BuffMsg[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//有buff的信号
HANDLE SkillCDMsg[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//英雄技能CD信号
HANDLE MoveMsg[MAX_MONSTER_NUM + 1];//英雄移动的信号
HANDLE ChaseMsg[MAX_MONSTER_NUM + 1];//英雄追踪的信号
HANDLE hmutex[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//英雄锁
AIState* AIStates[AI_STOCK + 1][AI_STATE_NUM];//
HANDLE EndFighting;//一次进攻结束的信号
HANDLE Fighting;//下一次进攻开始的信号
HANDLE PRINTF_MUTEX;//输出锁 保证同时只有一个文本在输出
Hero* CurSelectedHero;//当前选定的英雄
MinHeap* Open[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//开启列表
Aector* Close[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//关闭列表
Astar* PathBegin[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//路径起点
Astar* NextLoc[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//下一个位置
atomic_int CurTransportedEquipIndex;//当前正在转移的装备的索引
atomic_int CurTransportedThingIndex;//当前正在转移的消耗品的索引
int LastShownType = -1;
int LastShownIndex = -1;
int Round=0;//游戏轮数
int IntervalLastTime = 0;//间隔剩余时间
int CurMonsterNum;//当前辅导员数量 为0时结束这一轮

							 

//********************************************************************************************************
//**************************************以下是游戏内英雄 技能 装备 消耗品的数据声明***********************
//********************************************************************************************************
GPHero HeroStock[GP_STOCK + 1];//GP英雄
AIHero MonsterStock[AI_STOCK + 1];//AI英雄
DWORD GPApperanceStock[GP_STOCK + 1];//GP英雄颜色
string GPNameStock[GP_STOCK + 1];//GP英雄名字
string AINameStock[AI_STOCK + 1];//AI英雄名字
Attribute GPBAttributeStock[GP_STOCK+1];//GP英雄基础属性
Attribute GPIAtrributeStock[GP_STOCK+1];//GP英雄增长属性
Attribute AIBAttributeStock[AI_STOCK+1];//AI英雄基础属性
Attribute AIIAttributeStock[AI_STOCK+1];//AI英雄基础属性
Special GPBSpecialStock[GP_STOCK + 1];//GP英雄基础special
Special GPISpecialStock[GP_STOCK + 1];//GP英雄增长special
Special AIBSpecialStock[AI_STOCK + 1];//AI英雄基础special
Special AIISpecialStock[AI_STOCK + 1];//AI英雄基础special

Skill GPSkillStock[GP_STOCK*MAX_HERO_SKILL_NUM+1];//GP英雄技能
Skill AISkillStock[AI_STOCK*MAX_MONSTER_SKILL_NUM+1];//AI英雄技能
Attribute GPSkillAttributeBStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP英雄技能基础属性
Attribute GPSkillAttributeIStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP英雄技能增长属性
Attribute AISkillAttributeBStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI英雄技能基础属性
Attribute AISkillAttributeIStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI英雄技能增长属性
Buff GPSkillBuffBStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP技能Buff基础属性
Buff GPSkillBuffIStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP技能Buff增长属性
Buff AISkillBuffBStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI技能Buff基础属性
Buff AISkillBuffIStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI技能Buff增长属性

Equipment EquipmentStock[EQUIPMENT_STOCK];
Consumable ConsumableStock[CONSUMABLE_STOCK];
Consumable EnhanceBookStock[ENHANCEBOOK_STOCK];





//*********************************************************************************************
//***************************************以下是一些全局函数的定义******************************
//*********************************************************************************************
bool MouseOperateState::LeftButtonPressed = false;
Attribute& operator+=(Attribute& Body, const Attribute& Effection)
{
	Body.MaxBlood += Effection.MaxBlood;
	Body.MaxEnergy += Effection.MaxEnergy;
	Body.Ma += Effection.Ma;
	Body.Md += Effection.Md;
	Body.Pa += Effection.Pa;
	Body.Pd += Effection.Pd;
	Body.Speed += Effection.Speed;
	Body.Blood = ((Body.Blood + Effection.Blood) > Body.MaxBlood) ? Body.MaxBlood : Body.Blood + Effection.Blood;
	Body.Energy = ((Body.Energy + Effection.Energy) > Body.MaxEnergy) ? Body.MaxEnergy : Body.Energy + Effection.Energy;
	Body.Frequence += Effection.Frequence;
	Body.CrRate += Effection.CrRate;
	return Body;
}
Attribute& operator-=(Attribute& Body, const Attribute& Effection)
{
	Body.MaxBlood -= Effection.MaxBlood;
	Body.MaxEnergy -= Effection.MaxEnergy;
	Body.Ma = ((Body.Ma - Effection.Ma) >= 0) ? Body.Ma - Effection.Ma : 0;
	Body.Md = ((Body.Md - Effection.Md) >= 0) ? Body.Md - Effection.Md : 0;
	Body.Pa = ((Body.Pa - Effection.Pa) >= 0) ? Body.Pa - Effection.Pa : 0;
	Body.Pd = ((Body.Pd - Effection.Pd) >= 0) ? Body.Pd - Effection.Pd : 0;
	Body.Speed = ((Body.Speed - Effection.Speed) >= 0) ? Body.Speed - Effection.Speed : 0;
	Body.Frequence = ((Body.Frequence - Effection.Frequence) >= 0) ? Body.Frequence - Effection.Frequence : 0.01;//攻速最低不能为零 否则会除法溢出
	Body.CrRate = ((Body.CrRate - Effection.CrRate) >= 0) ? Body.CrRate - Effection.CrRate : 0;
	return Body;
}
Attribute operator+(const Attribute& Effection1, const Attribute& Effection2)
{
	//似乎一般+号只会用于效果叠加 那么就没有最大生命值这么一说了  所以这一项也就不用管了
	Attribute Tmp;
	//Tmp.MaxBlood=Effection1.MaxBlood + Effection2.MaxBlood;
	//Effection1.MaxEnergy + Effection2.MaxEnergy;
	Tmp.Ma = Effection1.Ma + Effection2.Ma;
	Tmp.Md = Effection1.Md + Effection2.Md;
	Tmp.Pa = Effection1.Pa + Effection2.Pa;
	Tmp.Pd = Effection1.Pd + Effection2.Pd;
	Tmp.Speed = Effection1.Speed + Effection2.Speed;
	Tmp.Blood = Effection1.Blood + Effection2.Blood;
	Tmp.Energy = Effection1.Energy + Effection2.Energy;
	Tmp.Frequence = Effection1.Frequence + Effection2.Frequence;
	Tmp.CrRate = Effection1.CrRate + Effection2.CrRate;

	return Tmp;
}
Special& operator-=(Special& Body, const Special& Effection)
{
	Body.PhysicalPercent = ((Body.PhysicalPercent - Effection.PhysicalPercent) > 0) ? Body.PhysicalPercent - Effection.PhysicalPercent : 0;
	Body.MagicPercent = ((Body.MagicPercent - Effection.MagicPercent) > 0) ? Body.MagicPercent - Effection.MagicPercent : 0;
	Body.SuckBlood = ((Body.SuckBlood - Effection.SuckBlood) > 0) ? Body.SuckBlood - Effection.SuckBlood : 0;
	Body.SuckMagic = ((Body.SuckMagic - Effection.SuckMagic) > 0) ? Body.SuckMagic - Effection.SuckMagic : 0;
	return Body;
}
Special& operator+=(Special& Body, const Special& Effection)
{
	Body.PhysicalPercent += Effection.PhysicalPercent;
	Body.MagicPercent += Effection.MagicPercent;
	Body.SuckBlood += Effection.SuckBlood;
	Body.SuckMagic += Effection.SuckMagic;
	return Body;
}
Buff& operator+=(Buff& Body, const Buff& Adder)
{
	Body.TimeLeft += Adder.TimeLeft;
	Body.Effection += Adder.Effection;
	Body.special += Adder.special;
	return Body;
}
bool operator!=(const COORD& cd1, const COORD& cd2)
{
	return (cd1.X != cd2.X) || (cd1.Y != cd2.Y);
}
bool operator==(const COORD& cd1, const COORD& cd2)
{
	return (cd1.X == cd2.X) && (cd1.Y == cd2.Y);
}

void ShowGameProgress()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	SetConsoleCursorPosition(hOut, { 0,0 });
	SetConsoleTextAttribute(hOut, GAME_INFO);
	printf("寝室完好：%d轮\n距离辅导员（们）下次来查寝：%2ds", Round, IntervalLastTime);
	ReleaseMutex(PRINTF_MUTEX);
}
void EraseGameProgress()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	SetConsoleCursorPosition(hOut, { 0,0 });
	printf("               \n                               ");
	ReleaseMutex(PRINTF_MUTEX);
}
void ShowFuDaoYuanLaiLe()
{
	//  ……   TM机智
}

unsigned WINAPI LoadHero(LPVOID lpParameter)//加载一个新英雄的例程
{
	Hero* Object = (Hero*)lpParameter;
	Object->Operating();
	return 0;
}
unsigned WINAPI LoadMonster(LPVOID lpParameter)//加载一个新怪物的例程
{
	Monsters[*((int*)lpParameter)]->Operating();
	return 0;
}
unsigned WINAPI UpdateBuff(LPVOID lpParameter)
{
	Hero* Object = (Hero*)lpParameter;
	int curbuff = 0;//记录本次更新的buff数 以便发现没有buff时及时阻塞该线程
	while (!Object->dead)
	{
		WaitForSingleObject(BuffMsg[Object->camp][Object->number], INFINITE);//等待有buff
		WaitForSingleObject(hmutex[Object->camp][Object->number], INFINITE);//加锁
		curbuff = 0;
		for (auto tmp = Object->Head->Next; tmp != Object->Rear; tmp = tmp->Next)
		{
			curbuff++;
			if (tmp->TimeLeft <= 0)
			{
				Object->special -= tmp->special;//减去它提供的那部分特殊效果
				Object->uAttribute -= tmp->Effection;//减去暂时的护甲 等等加成
				tmp->Prev->Next = tmp->Next;//更新节点
				tmp->Next->Prev = tmp->Prev;//以删去当前节点
				delete tmp;
			}
			else 
			{
				tmp->TimeLeft--;//剩余时间-1
				Object->GetSlowRecovery(tmp->Effection);//更新缓慢的回血回蓝
			}
		}
		if (!curbuff)//如果遍历完这次发现没有buff了  那么设置事件阻塞函数
			ResetEvent(BuffMsg[Object->camp][Object->number]);
		ReleaseMutex(hmutex[Object->camp][Object->number]);//解锁
		Sleep(1000);
	}
	return 0;
}
unsigned WINAPI FlushGPSkill(LPVOID lpParameter)
{
	GPHero* Object = (GPHero*)lpParameter;
	Skill* SkillRecords[MAX_HERO_SKILL_NUM];
	for (int i = 0; i < MAX_HERO_SKILL_NUM; i++)
	{
		SkillRecords[i] = Object->Skills[i];//保留技能的副本
		SkillRecords[i]->JustFlushed = false;
	}
	int curskill = 0;//记录本次更新的技能数 以便发现没有技能需要刷新时及时阻塞该线程
	while (1)
	{
		if (Object->dead)
			return 0;
		WaitForSingleObject(SkillCDMsg[Allies][Object->number],INFINITE);
		WaitForSingleObject(hmutex[Allies][Object->number], INFINITE);
		curskill = 0;
		for (int i = 0; i < MAX_HERO_SKILL_NUM; i++)
		{
			if (SkillRecords[i]->LastCD > 0)
			{
				curskill++;
				if(--SkillRecords[i]->LastCD==0)
					SkillRecords[i]->JustFlushed = true;
			}
			if(SkillRecords[i]->JustFlushed)
			{
				Object->Skills[i] = SkillRecords[i];
				if (Object==CurSelectedHero)
				{
					SkillRecords[i]->JustFlushed = false;
					WaitForSingleObject(PRINTF_MUTEX, INFINITE);
					SetConsoleTextAttribute(hOut, SKILL_COLOR);
					SkillRecords[i]->PrintName();
					ReleaseMutex(PRINTF_MUTEX);
				}
			}
		}
		if (!curskill)
			ResetEvent(SkillCDMsg[Object->camp][Object->number]);
		ReleaseMutex(hmutex[Object->camp][Object->number]);
		Sleep(1000);
	}
}
unsigned WINAPI FlushAISkill(LPVOID lpParameter)
{
	AIHero* Object = (AIHero*)lpParameter;
	Skill* SkillRecords[MAX_MONSTER_SKILL_NUM];
	for (int i = 0; i < MAX_MONSTER_SKILL_NUM; i++)
	{
		SkillRecords[i] = Object->Skills[i];//保留技能的副本
		SkillRecords[i]->JustFlushed = false;
	}
	int curskill = 0;//记录本次更新的技能数 以便发现没有技能需要刷新时及时阻塞该线程
	while (!Object->dead)
	{
		WaitForSingleObject(SkillCDMsg[Enemy][Object->number], INFINITE);
		WaitForSingleObject(hmutex[Enemy][Object->number], INFINITE);
		curskill = 0;
		for (int i = 0; i < MAX_MONSTER_SKILL_NUM; i++)
		{
			if (SkillRecords[i]->LastCD > 0)
			{
				curskill++;
				if (--SkillRecords[i]->LastCD == 0)
					SkillRecords[i]->JustFlushed = true;
			}
			if (SkillRecords[i]->JustFlushed)
			{
				Object->Skills[i] = SkillRecords[i];
				if (Object == CurSelectedHero)
				{
					SkillRecords[i]->JustFlushed = false;
					WaitForSingleObject(PRINTF_MUTEX, INFINITE);
					SetConsoleTextAttribute(hOut, SKILL_COLOR);
					SkillRecords[i]->PrintName();
					ReleaseMutex(PRINTF_MUTEX);
				}
			}
		}
		if (!curskill)
			ResetEvent(SkillCDMsg[Object->camp][Object->number]);
		ReleaseMutex(hmutex[Object->camp][Object->number]);
		Sleep(1000);
	}
	return 0;
}
unsigned WINAPI SolveMove(LPVOID lpParameter)
{
	GPHero* Object = (GPHero*)lpParameter;
	COORD LastDestination;//记录上一次移动的目的地
	while (1) 
	{
		if (Object->dead)
			return 0;
		WaitForSingleObject(MoveMsg[Object->number], INFINITE);//等待移动指令
		if (!Object->FindPath())
		{
			ResetEvent(MoveMsg[Object->number]);
			continue;
		}
		LastDestination = Object->Destination;
		while (1)
		{
			if (Object->isChasing)
			{
				int dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;
				int dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;
				
				if (Object->HeroToChase->camp == Object->camp)
				{
					if (dx <= 1 && dy <= 1)//两者位于相邻位置时即可停止
						break;
				}
				else
				{
					if (dx <= Object->uAttribute.AttackRange&&dy <= Object->uAttribute.AttackRange)
						break;
				}
			}
			else
			{
				if (Object->KerLoc == Object->Destination)
					break;
			}
			for (int i = 0; i < Object->uAttribute.Speed; i++)
				NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;//找到下一步的位置
			if (Active[NextLoc[Object->camp][Object->number]->Loc.X][NextLoc[Object->camp][Object->number]->Loc.Y].Occupied || LastDestination != Object->Destination)//若果这个位置被占据了或者目的地变更了
			{
				if (Object->FindPath())//开始找新路径  如果找到了
				{
					for (int i = 0; i < Object->uAttribute.Speed; i++)//找下一步的位置
						NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;
					if (LastDestination != Object->Destination)//如果是因为目的地变更 那么更新上一次的目的地为新的这个目的地
						LastDestination = Object->Destination;
				}
				else
					break;//找不到路径就停止
			}
			Object->Jmp(NextLoc[Object->camp][Object->number]->Loc);//移动到那个位置
			Sleep(100);
		}
		ResetEvent(MoveMsg[Object->number]);
		SetEvent(AttackMsg[Object->number]);
	}
}
unsigned WINAPI ToChase(LPVOID lpParameter)
{
	GPHero* Object = (GPHero*)lpParameter;
	while (1) 
	{
		if (Object->dead)
			return 0;
		Object->isChasing = true;
		WaitForSingleObject(ChaseMsg[Object->number], INFINITE);
		Object->Destination = Object->HeroToChase->KerLoc;//设置追踪目标
		SetEvent(MoveMsg[Object->number]);//设置移动信号
		ResetEvent(AttackMsg[Object->number]);//取消攻击信号
		Sleep(100);//每过一段时间更新一次跟随目的地
	}
}
unsigned WINAPI Timer(LPVOID lpParameter)
{
	SYSTEMTIME LastSecond;
	SYSTEMTIME CurSecond;
	while (1)
	{
		WaitForSingleObject(EndFighting, INFINITE);
		IntervalLastTime = INTERVAL;//重置间隔时间
		GetLocalTime(&LastSecond);
		for (; IntervalLastTime;)
		{
			ShowGameProgress();
			GetLocalTime(&CurSecond);
			while (CurSecond.wSecond == LastSecond.wSecond)
			{
				Sleep(200);
				GetLocalTime(&CurSecond);
			}
			LastSecond = CurSecond;
			IntervalLastTime--;
		}
		Round++;
		EraseGameProgress();
		ShowFuDaoYuanLaiLe();
		ResetEvent(EndFighting);
		SetEvent(Fighting);
	}
}
unsigned WINAPI PlayMoveSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	srand(time(NULL));
	if(Tmp->number==1)
		PlaySound(Tmp->MoveSounds[rand() % Tmp->MoveSoundNum].c_str(), NULL, SND_FILENAME | SND_ASYNC);
	return 0;
}
unsigned WINAPI PlayAttackSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	srand(time(NULL));
	PlaySound(Tmp->AttackSounds[rand() % Tmp->AttackSoundNum].c_str(), NULL, SND_FILENAME | SND_ASYNC);
	return 0;
}
unsigned WINAPI PlayAttackedSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	//srand(time(NULL));
	PlaySound(Tmp->AttackedSound.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	return 0;
}
unsigned WINAPI PlayBoughtSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	//srand(time(NULL));
	PlaySound(Tmp->BoughtSound.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	return 0;
}
unsigned WINAPI PlaySelectedSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	//srand(time(NULL));
	PlaySound(Tmp->SelectedSound.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	return 0;
}
unsigned WINAPI PlayDieSound(LPVOID lpParameter)
{
	GPHero* Tmp = (GPHero*)lpParameter;
	//srand(time(NULL));
	PlaySound(Tmp->DieSound.c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
	return 0;
}
unsigned WINAPI PlayBackgroundSound(LPVOID lpParameter)
{
		/*mciSendString("open myfolder\\B1.mp3 alias aa", NULL, 0, NULL);
		mciSendString("play aa wait", NULL, 0, NULL);
		mciSendString("close aa", NULL, 0, NULL);*/
		return 0;
}
unsigned WINAPI UpdateFighting(LPVOID lpParameter)
{
	int MonsterNum;//一轮中辅导员出现的个数
	int EquipmentNum;//辅导员的装备数
	while (1)
	{
		WaitForSingleObject(Fighting, INFINITE);
		//设置出现的辅导员个数
		if (Round >= ThirdMonsterTurnUp)
			MonsterNum = 3;
		else if (Round >= SecondMonsterTurnUp)
			MonsterNum = 2;
		else
			MonsterNum = 1;

		//对各个辅导员进行初始化
		for (int i = 1; i <= MonsterNum; i++)
		{
			//初始化辅导员数组
			Monsters[i] = &MonsterStock[i];
			CloseHandle((HANDLE)_beginthreadex(NULL, 0, LoadHero, (void*)Monsters[i], 0, NULL));//开启辅导员线程
		}
		ResetEvent(EndFighting);
		WaitForSingleObject(EndFighting,INFINITE);
	}
}

void BuyHero(int HeroNumber)
{
	if (money >=CurHeroPrice)//如果有足够的钱
	{
		for (int i = 1; i <= CurNum[Allies]; i++)
			if (Heros[i]->StockNumber == HeroNumber)
				return;//已经有这个英雄了 就不能再买了
		money -= CurHeroPrice;//花钱
		CurHeroPrice += INC_HERO_PRICE;//更新价格
		//新英雄加入
		Heros[CurNum[Allies]+1] = &HeroStock[HeroNumber];
		//投入使用
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, LoadHero, (void*)Heros[CurNum[Allies] + 1], 0, NULL));//为英雄创建线程 投入使用
	}
}
void EraseThing(TYPE T, int index)//T可以是SKILL CONSUMBALE EQUIPMENT index范围0-5
{
	int left = (SCREEN_WIDTH - (3 * (3 - T) - index % 3)*(1 + THING_WIDTH_CHAR))*PIX_PER_WIDTH;//算出左边起点
	int top = (SCREEN_HEIGHT - (2 - index / 3)*(1 + THING_HEIGHT_CHAR) + 1)*PIX_PER_HEIGHT;//算出上边起点
	SelectObject(hdc, hBlackBrush);
	Rectangle(hdc, left, top, left + THING_WIDTH_PIX, top + THING_HEIGHT_PIX);//抹黑
}
void BeginTransportOrUpSkill(COORD Destination)
{
	GPHero* Tmp;
	if (Tmp=dynamic_cast<GPHero*>(CurSelectedHero))
	{
		if ((Destination.X % (THING_WIDTH_CHAR + 1) == 0) || (Destination.Y % (THING_HEIGHT_CHAR + 1) == 0))//点在分界线上无效
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//范围是0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
		int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
		int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
		switch (Ftype)
		{
		case 0://技能栏则升级技能
		{
			if (Tmp->LeftSkillPoint > 0)//如果有技能点
			{
				Tmp->LeftSkillPoint--;//技能点-1
				Tmp->Skills[RealIndex]->LevelUp();//技能升级
			}
		}
			return;
		break;
		case 1://消耗品栏
		{
			TransportedType = CONSUMABLE;
			CurTransportedThingIndex = RealIndex;
			TmpMOPState = TMState;
		}
			break;
		case 2://装备栏
		{
			TransportedType = EQUIPMENT;
			CurTransportedThingIndex = RealIndex;
			TmpMOPState = TMState;
		}
			break;
		default:
			break;
		}

	}
}
void GameOver()
{

}

//*********************************************************************************************
//**************************************以下是类函数定义***************************************
//*********************************************************************************************
void MouseOperateState::ShowDetail(int FTYPE, int REALINDEX)
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
	{
		FillConsoleOutputCharacterA(hOut, ' ', IMAGE_INFO, { 0,y }, &num);
		FillConsoleOutputAttribute(hOut, 0, IMAGE_INFO, { 0,y }, &num);
		FillConsoleOutputAttribute(hOut, 0, INFO_FUNCTION - IMAGE_INFO - 1, { IMAGE_INFO + 1,y }, &num);
	}
	SetConsoleCursorPosition(hOut, { 0,BATTLE_AREA + 1 });//定位光标
	SetConsoleTextAttribute(hOut, DefaultColor);
	switch (FTYPE)
	{
	case 0://技能
	{
		if (CurSelectedHero->Skills[REALINDEX])
		{
			switch (CurSelectedHero->Skills[REALINDEX]->StockNumber)
			{
			case 0://
			{
				/*对凯恩血蹄的六个技能的描述
				0、血蹄践踏
				凯恩血蹄开始跑步，不小心跑到别人，直接造成物理伤害 （初始伤害100  后续每升一级增加50伤害）
				1、精气光环
				凯恩血蹄想到今晚没课，突然上头，并带带动了大家，增加攻击速度  （所有友军增加攻击速度0.5 初始持续3s  每升一级增加1s ）
				2、自然秩序
				凯恩血蹄突然觉得很饿，点了一块鸡排，马上回了很多血  （初始恢复自身75点血量 每升一级增加25 不耗蓝）
				3、先祖之魂
				凯恩血蹄怕变成肥宅，于是开始锻炼身体，杀伤力增加了很多 （初始增加自身50点攻击力 后续每升一级增加30点）
				4、怒意狂击
				凯恩血蹄发现今天漫画加更，很高兴，攻速立马变快了 （增加自身攻击速度 0.5  持续7s 每升一级啊增加2s）
				5、极度饥渴
				凯恩血蹄开始帮同学找Bug，这不但对他人造成了伤害，还使他很快乐，越来越精神（攻击造成吸血效果 恢复自身攻击造成伤害的50%  持续5s 每升一级增加2s）
				*/

			}
			break;
			case 1://
			{

			}
			break;
			case 2://
			{

			}
			break;
			default:
				break;
			}
		}
	}
	break;
	case 1://消耗品
	{
		GPHero* Tmp;
		if ((Tmp = dynamic_cast<GPHero*>(CurSelectedHero)) && Tmp->Consumables[REALINDEX])//如果这个位置有消耗品
		{
			switch (Tmp->Consumables[REALINDEX]->StockNumber)
			{
			case 0://烤奶
			{
				printf("它常时沉默寡言，不愿意展示自己，“销量？我奶君是需要销\n量来证明的吗？”。然而坊间却一直流传着它军训时的光伟，\n有人说只是传说……“我高贵的奶红怎么会和原谅绿为伍！”\n的确，人们都若有所思地点点头，仿佛确信一般。");
			}
			break;
			case 1://肾宝
			{
				printf("不知名的橙色饮料");
			}
			break;
			case 2://好吃的奇异果
			{

			}
			break;
			case 3://维C柠檬茶
			{

			}
			break;
			case 4://咖啡
			{

			}
			break;
			case 5://电脑配件
			{

			}
			break;
			default:
				break;
			}
		}
	}
	break;
	case 2://装备
	{
		if (CurSelectedHero->Equipments[REALINDEX])//如果这个位置有装备
		{
			Rectangle(hdc, 0, (BATTLE_AREA + 1)*PIX_PER_HEIGHT, IMAGE_INFO*PIX_PER_WIDTH, SCREEN_HEIGHT*PIX_PER_HEIGHT);
			switch (CurSelectedHero->Equipments[REALINDEX]->StockNumber)
			{
			case 0://锋哥的指甲刀
			{
				printf("“直到那一天，人们终于想起被锋哥的指甲刀支配的恐惧，以\n及无论如何锋哥都不借给你的耻辱”\n                                             -----阿门\n");
			}
			break;
			case 1://锋哥的订书机
			{
				printf("自从用了锋哥的订书机，大家就可以在每订一次就得打开一次\n订书机摆正钉子的间隔中思考人生，思考克制自己的欲望，\n绝对不能诉诸武力，学会心平气和。看到大家都学会了控制情\n绪，锋哥高兴得想从轮椅上站起来");
			}
			break;
			case 2://拖鞋
			{
				printf("“如果非要有什么推荐给大家的话，那就一定是拖鞋了”");
			}
			break;
			case 3://加厚的班服
			{
				printf("当大家都在纠结加厚的班服是否真的适合广州的天气时，锋哥\n已经默默地把它穿上了。“明明就不热！”大家向他望去，随\n即一哄而散了。锋哥从不理会关于“虚”的一些流言，仍然在\n四十度时紧裹班服。只是据他的舍友追忆，他生前喜欢喝一罐\n不知名的橙色饮料，然后躺下睡觉。");
			}
			break;
			case 4://吹风机
			{
				printf("关于到底吹风机能不能加快攻击速度的问题，Emphasizer已经\n显得不厌其烦了，“够了！”，他大声呵斥道。人们都吓了一\n跳，“起码”，咽了咽口水，他继续说道，“我的头发是干得\n比以前快了。”");
			}
			break;
			case 5://锋哥的杠铃
			{
				printf("实际上，据Emphasizer说，在刚买来时，它还只是一个小哑铃\n。“你们看，它长得多快！”，锋哥像摸着自己的孩子一样抚\n摸着他的杠铃。“嗯……哥，你说的对……”，大家都为他鼓\n掌。可当人们问起来的时候，Emphasizer也只是模糊的回答：\n“没错，我是锋哥的舍友……但我们也不清楚他到底是怎么把\n那玩意搞得越来越大的。”");
			}
			break;
			default:
				break;
			}
		}
	}
	break;
	default:
		break;
	}
	ReleaseMutex(PRINTF_MUTEX);
}
void MouseOperateState::SolveMouseMoved(COORD MovedLoc)
{
	RelativeLoc.X = MovedLoc.X - INFO_FUNCTION;
	RelativeLoc.Y = MovedLoc.Y - BATTLE_AREA;

	if ((RelativeLoc.Y == (THING_HEIGHT_CHAR + 1)) || (RelativeLoc.X % (THING_WIDTH_CHAR + 1) == 0))//点在分界线上无效
		return;
	int xIndex = RelativeLoc.X / (THING_WIDTH_CHAR + 1);//范围是0-8
	int yIndex = RelativeLoc.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
	int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
	int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
	if (LastShownIndex != RealIndex || LastShownType != Ftype)
	{
		isShowingHero = false;//设置没在显示英雄
		ShowDetail(Ftype, RealIndex);//展示其信息
		LastShownIndex = RealIndex;
		LastShownType = Ftype;
	}
}
void FormalState::TriggerFunction(COORD Destination)
{
	GPHero* Tmp;
	if (Tmp = dynamic_cast<GPHero*>(CurSelectedHero))
	{
		if ((Destination.Y == (THING_HEIGHT_CHAR + 1)) || (Destination.X % (THING_WIDTH_CHAR + 1) == 0))//点在分界线上无效
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//范围是0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
		int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
		int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
		switch (Ftype)
		{
		case 0://技能栏
		{
			if (Tmp->Skills[RealIndex]&& Tmp->uAttribute.Energy > CurTriggeredSkill->EnergyConsume)//如果有技能且蓝量足够
			{
				TmpMOPState = SMState;
				CurTriggeredSkill = Tmp->Skills[RealIndex];//设置该技能为当前触发技能
			}
		}
		break;
		case 1://消耗品栏 
			Tmp->UseConsumable(RealIndex);
			break;
		case 2://装备栏无法主动触发
			break;
		default:
			break;
		}
	}
}
void FormalState::SolveMouseReleased(COORD Destination)
{
	if (LeftButtonPressed)//若是按下左键
	{
		if (Destination.Y < BATTLE_AREA&&Active[Destination.X][Destination.Y].Occupied)//如果位于战场区域且选中的位置有单位
		{
			Gotta = dynamic_cast<GPHero*>(CurSelectedHero);
			(CurSelectedHero = Active[Destination.X][Destination.Y].OccupyingUnit)->GetSelected();//那就选中他
		}
		else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//如果不在战场区且位于功能区
			TriggerFunction({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//触发对应区域的功能
	}
	else//若是按下右键
	{
		GPHero* Tmp;
		if (Tmp = dynamic_cast<GPHero*>(CurSelectedHero))
		{
			if (Destination.Y < BATTLE_AREA)//如果位于战场区
				Tmp->MoveTo(Destination);//英雄行动
			else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//如果位于功能区
				BeginTransportOrUpSkill({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//那么开始转移或者升级技能
		}
	}
	LeftButtonPressed = false;//重置
}
void FormalState::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X > INFO_FUNCTION&&MovedLoc.Y > BATTLE_AREA)//如果鼠标位于功能区
		MouseOperateState::SolveMouseMoved(MovedLoc);
	else if (MovedLoc.X <= INFO_FUNCTION || MovedLoc.Y <= BATTLE_AREA)//鼠标不位于功能区
	{
		if (!isShowingHero)
		{
			isShowingHero = true;//设置在显示英雄
			CurSelectedHero->PrintImage();//显示当前选定的英雄的头像
		}
		CurSelectedHero->PrintInformation();//显示当前选定的英雄的信息
											//Sleep(500);
	}
}
void FormalState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键按下
			LeftButtonPressed = true;
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右键按下
			;
		else//按键释放
			SolveMouseReleased(NewEvent.dwMousePosition);//对其进行处理
	}
	break;
	case MOUSE_MOVED://鼠标移动
		SolveMouseMoved(NewEvent.dwMousePosition);//对其处理
		break;
	default:
		break;
	}
}
void SkillingState::SolveMouseReleased(COORD Destination)
{
	for (short y = LastMousePos.Y-TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)//清除技能指示
		FillConsoleOutputCharacter(hOut, ' ', TmpSkillRange*2+1, { LastMousePos.X - TmpSkillRange,y }, &num);
	if (LeftButtonPressed) //如果左键按下
	{
		if (Destination.Y < BATTLE_AREA)//如果点在战场区 说明是在施放技能
		{
			for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
				for (short x = LastMousePos.X - TmpSkillRange; x <= LastMousePos.X + TmpSkillRange; x++)
					if (Active[x][y].Occupied)
						Active[x][y].OccupyingUnit->GetSkillEffection(CurTriggeredSkill);
			CurSelectedHero->uAttribute.Energy -= CurTriggeredSkill->EnergyConsume;//耗蓝
			CurTriggeredSkill->LastCD = CurTriggeredSkill->CD;//设置CD
			EraseThing(SKILL, CurTriggeredSkill->index);
			CurSelectedHero->Skills[CurTriggeredSkill->index] = NULL;
			SetEvent(SkillCDMsg[CurSelectedHero->camp][CurSelectedHero->number]);//发送刷新技能的信号
		}
	}
	//非左键点在战场区则不进行响应
	TmpMOPState = FMState;//状态转移
	LeftButtonPressed = false;//重置
}
void SkillingState::SolveMouseMoved(COORD MovedLoc)
{
	if ((MovedLoc.Y<BATTLE_AREA))//这里说明一下 一旦鼠标进入功能区 就不应该再判断是否在放技能了  因为这时不应该显示放技能信息
	{
		for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
			FillConsoleOutputCharacter(hOut, ' ', TmpSkillRange * 2 + 1, { LastMousePos.X - TmpSkillRange,y }, &num);
		TmpSkillRange = CurTriggeredSkill->Range();//暂存技能范围
		LastMousePos.X = MovedLoc.X > TmpSkillRange ? ((MovedLoc.X+ TmpSkillRange<BATTLE_WIDTH? MovedLoc.X : BATTLE_WIDTH -1- TmpSkillRange)): TmpSkillRange;
		LastMousePos.Y = MovedLoc.Y > TmpSkillRange ? ((MovedLoc.Y + TmpSkillRange<BATTLE_HEIGHT ? MovedLoc.Y : BATTLE_HEIGHT - 1 - TmpSkillRange)) : TmpSkillRange;
		for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
			FillConsoleOutputCharacter(hOut, SKILL_CHAR, TmpSkillRange * 2 + 1, { LastMousePos.X - TmpSkillRange,y }, &num);
	}
	else if (MovedLoc.X > INFO_FUNCTION)//如果鼠标位于功能区
		MouseOperateState::SolveMouseMoved(MovedLoc);

	if (!isShowingHero)
	{
		isShowingHero = true;//设置在显示英雄
		CurSelectedHero->PrintImage();//显示当前选定的英雄的头像
	}
}
void SkillingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键按下
			LeftButtonPressed = true;
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右键按下
			;
		else//按键释放
			SolveMouseReleased(NewEvent.dwMousePosition);//对其进行处理
	}
	break;
	case MOUSE_MOVED://鼠标移动
		SolveMouseMoved(NewEvent.dwMousePosition);//对其处理
		break;
	default:
		break;
	}
}
void TransportingState::SolveMouseReleased(COORD Destination)
{
	GPHero* Tmp;
	if (!(Tmp = dynamic_cast<GPHero*>(CurSelectedHero)))
		system("pause");
	if (LeftButtonPressed) //如果左键按下 进行转移
	{
		if (Active[Destination.X][Destination.Y].Occupied&&(Gotta=dynamic_cast<GPHero*>(Active[Destination.X][Destination.Y].OccupyingUnit)))
		{
			if (Active[Destination.X][Destination.Y].OccupyingUnit->number)//不是0说明要转移
			{
				if (TransportedType == CONSUMABLE && Gotta->GetConsumable(Tmp->Consumables[CurTransportedThingIndex]))//如果是传输的消耗品 而且有空位
				{
					Tmp->LoseConsumable(CurTransportedThingIndex);//失去装备
					EraseThing(CONSUMABLE, CurTransportedThingIndex);//抹去图片
				}
				else if (TransportedType == EQUIPMENT && Active[Destination.X][Destination.Y].OccupyingUnit->GetEquipment(Tmp->Equipments[CurTransportedThingIndex]))//如果是传输的装备 而且有空位
				{
					Tmp->LoseEquipment(CurTransportedThingIndex);//失去装备
					EraseThing(EQUIPMENT, CurTransportedThingIndex);//抹去图片
				}
			}
			else//是0说明要卖
			{
				EraseThing(TransportedType, CurTransportedThingIndex);//擦去物品图片
				money += ((TransportedType == EQUIPMENT) ? Tmp->Equipments[CurTransportedThingIndex]->GetEffection().BaseAttack->RewardM : Tmp->Consumables[CurTransportedThingIndex]->Effect()->Effection.RewardM)*SELL_RATE / 10;//拿钱
				if (TransportedType == EQUIPMENT)
					Tmp->Equipments[CurTransportedThingIndex] = NULL;//卖掉物品
				else
					Tmp->Consumables[CurTransportedThingIndex] = NULL;
			}
		}
		TmpMOPState = FMState;//转换为普通状态
	}
	else//如果按下右键
	{
		if (Destination.Y < BATTLE_AREA)//如果位于战场区
		{
			Tmp->MoveTo(Destination);//英雄行动
			TmpMOPState = FMState;//转换为普通状态
		}
	}
	LeftButtonPressed = false;//重置
	
}
void TransportingState::SolveMouseMoved(COORD MovedLoc)
{
	COORD RelativeLoc;//相对坐标
	if (MovedLoc.X > INFO_FUNCTION&&MovedLoc.Y > BATTLE_AREA)//如果鼠标位于功能区
		MouseOperateState::SolveMouseMoved(MovedLoc);
	else if (MovedLoc.X <= INFO_FUNCTION || MovedLoc.Y <= BATTLE_AREA)//鼠标不位于功能区
	{
		if (!isShowingHero)
		{
			isShowingHero = true;//设置在显示英雄
			CurSelectedHero->PrintImage();//显示当前选定的英雄的头像
		}
		CurSelectedHero->PrintInformation();//显示当前选定的英雄的信息
											//Sleep(500);
	}
}
void TransportingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键按下
			LeftButtonPressed = true;
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右键按下
			;
		else//按键释放
			SolveMouseReleased(NewEvent.dwMousePosition);//对其进行处理
	}
	break;
	case MOUSE_MOVED://鼠标移动
		SolveMouseMoved(NewEvent.dwMousePosition);//对其处理
		break;
	default:
		break;
	}
}
void ShoppingState::ShowDetail(int FTYPE, int REALINDEX)
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
	{
		FillConsoleOutputCharacterA(hOut, ' ', IMAGE_INFO, { 0,y }, &num);
		FillConsoleOutputAttribute(hOut, 0, IMAGE_INFO, { 0,y }, &num);
		FillConsoleOutputAttribute(hOut, 0, INFO_FUNCTION - IMAGE_INFO - 1, { IMAGE_INFO + 1,y }, &num);
	}
	SetConsoleCursorPosition(hOut, { 0,BATTLE_AREA + 1 });//定位光标
	SetConsoleTextAttribute(hOut, DefaultColor);
	switch (FTYPE)
	{
	case 0://强化书
	{
		switch (Shop->EnhanceBooks[REALINDEX]->StockNumber)
		{
		case 0:
		{

		}
		break;
		default:
			break;
		}
	}
	break;
	case 1://消耗品
	{
		switch (Shop->Consumables[REALINDEX]->StockNumber)
		{
		case 0://烤奶
		{
			printf("它常时沉默寡言，不愿意展示自己，“销量？我奶君是需要销\n量来证明的吗？”。然而坊间却一直流传着它军训时的光伟，\n有人说只是传说……“我高贵的奶红怎么会和原谅绿为伍！”\n的确，人们都若有所思地点点头，仿佛确信一般。");
		}
		break;
		case 1://肾宝
		{
			printf("不知名的橙色饮料");
		}
		break;
		case 2://好吃的奇异果
		{

		}
		break;
		case 3://维C柠檬茶
		{

		}
		break;
		case 4://咖啡
		{

		}
		break;
		case 5://电脑配件
		{

		}
		break;
		default:
			break;
		}
	}
	break;
	case 2://装备
	{
		Rectangle(hdc, 0, (BATTLE_AREA + 1)*PIX_PER_HEIGHT, IMAGE_INFO*PIX_PER_WIDTH, SCREEN_HEIGHT*PIX_PER_HEIGHT);
		switch (Shop->Equipments[REALINDEX]->StockNumber)
		{
		case 0://锋哥的指甲刀
		{
			printf("“直到那一天，人们终于想起被锋哥的指甲刀支配的恐惧，以\n及无论如何锋哥都不借给你的耻辱”\n                                             -----阿门\n");
		}
		break;
		case 1://锋哥的订书机
		{
			printf("自从用了锋哥的订书机，大家就可以在每订一次就得打开一次\n订书机摆正钉子的间隔中思考人生，思考克制自己的欲望，\n绝对不能诉诸武力，学会心平气和。看到大家都学会了控制情\n绪，锋哥高兴得想从轮椅上站起来");
		}
		break;
		case 2://拖鞋
		{
			printf("“如果非要有什么推荐给大家的话，那就一定是拖鞋了”");
		}
		break;
		case 3://加厚的班服
		{
			printf("当大家都在纠结加厚的班服是否真的适合广州的天气时，锋哥\n已经默默地把它穿上了。“明明就不热！”大家向他望去，随\n即一哄而散了。锋哥从不理会关于“虚”的一些流言，仍然在\n四十度时紧裹班服。只是据他的舍友追忆，他生前喜欢喝一罐\n不知名的橙色饮料，然后躺下睡觉。");
		}
		break;
		case 4://吹风机
		{
			printf("关于到底吹风机能不能加快攻击速度的问题，Emphasizer已经\n显得不厌其烦了，“够了！”，他大声呵斥道。人们都吓了一\n跳，“起码”，咽了咽口水，他继续说道，“我的头发是干得\n比以前快了。”");
		}
		break;
		case 5://锋哥的杠铃
		{
			printf("实际上，据Emphasizer说，在刚买来时，它还只是一个小哑铃\n。“你们看，它长得多快！”，锋哥像摸着自己的孩子一样抚\n摸着他的杠铃。“嗯……哥，你说的对……”，大家都为他鼓\n掌。可当人们问起来的时候，Emphasizer也只是模糊的回答：\n“没错，我是锋哥的舍友……但我们也不清楚他到底是怎么把\n那玩意搞得越来越大的。”");
		}
		break;
		default:
			break;
		}
	}
	break;
	default:
		break;
	}
	ReleaseMutex(PRINTF_MUTEX);
}
void ShoppingState::TriggerFunction(COORD Destination)
{
	if (Gotta)//如果购买者是己方
	{
		if ((Destination.Y == (THING_HEIGHT_CHAR + 1)) || (Destination.X % (THING_WIDTH_CHAR + 1) == 0))//点在分界线上无效
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//范围是0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
		int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
		int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
		switch (Ftype)
		{
		case 0://买强化书
		{
			if (money >= Shop->EnhanceBooks[RealIndex]->Effect()->Effection.RewardM&&Gotta)
			{
				Gotta->GetEffectedByBuff(Shop->EnhanceBooks[RealIndex]->Effect());//获得强化效果
				money -= Shop->EnhanceBooks[RealIndex]->Effect()->Effection.RewardM;//付钱
			}
		}
		break;
		case 1://买消耗品
		{
			if ((money >= Shop->Consumables[RealIndex]->Effect()->Effection.RewardM) && Gotta&&Gotta->GetConsumable(Shop->Consumables[RealIndex]))//钱够而且有空位
				money -= Shop->Consumables[RealIndex]->Effect()->Effection.RewardM;//付钱
		}
		break;
		case 2://买装备
		{
			if ((money >= (Shop->Equipments[RealIndex]->GetEffection()).BaseAttack->RewardM) && Gotta&& Gotta->GetEquipment(Shop->Equipments[RealIndex]))//钱够而且有空位
				money -= (Shop->Equipments[RealIndex]->GetEffection().BaseAttack->RewardM);//付钱
		}
		break;
		default:
			break;
		}
	}
}
void ShoppingState::SolveMouseReleased(COORD Destination)
{
	if (LeftButtonPressed)//若是按下左键
	{
		if (Destination.Y < BATTLE_AREA&&Active[Destination.X][Destination.Y].Occupied)//如果位于战场区域且选中的位置有单位
			(CurSelectedHero = Active[Destination.X][Destination.Y].OccupyingUnit)->GetSelected();//那就选中他
		else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//如果不在战场区且位于功能区
			TriggerFunction({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//触发对应区域的功能
	}
}
void ShoppingState::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X > INFO_FUNCTION&&MovedLoc.Y > BATTLE_AREA)//如果鼠标位于功能区
	{
		RelativeLoc.X = MovedLoc.X - INFO_FUNCTION;
		RelativeLoc.Y = MovedLoc.Y - BATTLE_AREA;

		if ((RelativeLoc.Y == (THING_HEIGHT_CHAR + 1)) || (RelativeLoc.X % (THING_WIDTH_CHAR + 1) == 0))//点在分界线上无效
			return;
		int xIndex = RelativeLoc.X / (THING_WIDTH_CHAR + 1);//范围是0-8
		int yIndex = RelativeLoc.Y / (THING_HEIGHT_CHAR + 1);//范围是0-1
		int Ftype = xIndex / 3;//范围是0-2 分别指技能 消耗品 和装备 //对商店来说分别指强化书 消耗品 和装备
		int RealIndex = yIndex * 3 + xIndex % 3;//索引范围是0-5
		if (LastShownIndex != RealIndex || LastShownType != Ftype)
		{
			isShowingHero = false;//设置没在显示英雄
			ShowDetail(Ftype, RealIndex);//展示其信息
			LastShownIndex = RealIndex;
			LastShownType = Ftype;
		}
	}
	else if (MovedLoc.X <= INFO_FUNCTION || MovedLoc.Y <= BATTLE_AREA)//鼠标不位于功能区
	{
		if (!isShowingHero)
		{
			isShowingHero = true;//设置在显示英雄
			CurSelectedHero->PrintImage();//显示当前选定的英雄的头像
		}
		CurSelectedHero->PrintInformation();//显示当前选定的英雄的信息
											//Sleep(500);
	}
}
void ShoppingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//左键按下
			LeftButtonPressed = true;
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//右键按下
			;
		else//按键释放
			SolveMouseReleased(NewEvent.dwMousePosition);//对其进行处理
	}
	break;
	case MOUSE_MOVED://鼠标移动
		SolveMouseMoved(NewEvent.dwMousePosition);//对其处理
		break;
	default:
		break;
	}
}


void AIStillState::Act()
{
	if (JustAttacked)//如果刚被攻击 则转移到消极追逐状态 此外 这个状态是由外界设置的 同时 攻击者应该设置Object的HeroToChase项
	{
		Object->TmpAIState = AIStates[Object->number][AINegChase];//切换到消极追逐状态
		JustAttacked = false;
	}
	else//否则继续走向寝室 并检测范围内是否有敌人
	{
		Object->Destination = CITADEL;//设置寝室为其目标位置
		for (int i = 0; i < Object->uAttribute.Speed; i++)
			NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;//找到下一步的位置
		if (Active[NextLoc[Object->camp][Object->number]->Loc.X][NextLoc[Object->camp][Object->number]->Loc.Y].Occupied || LastDestination != CITADEL)//若果这个位置被占据了或者目的地不是寝室
		{
			if (Object->FindPath())//开始找新路径  如果找到了
			{
				for (int i = 0; i < Object->uAttribute.Speed; i++)//找下一步的位置
					NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;
				if (LastDestination != CITADEL)//如果是因为目的地变更 那么更新上一次的目的地为新的这个目的地
					LastDestination = CITADEL;
			}
			else
				NextLoc[Object->camp][Object->number]->Loc=Object->KerLoc;//找不到路径就停止
		}
		Object->Jmp(NextLoc[Object->camp][Object->number]->Loc);//移动到那个位置
		GetLocalTime(&BeginTest);//取得开始检测的时间
		Sleep(1000 / Object->uAttribute.Frequence);//等待攻击间隔
		GetLocalTime(&EndTest);//取得结束检测时间
		for (; EndTest.wMilliseconds - BeginTest.wMilliseconds <= TestTime;)//也就是说 对于攻速小到一定程度的敌人，追逐状态中无法攻击 即可起到风筝的作用
		{
			int y1 = ((Object->KerLoc.Y - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.Y - Object->uAttribute.AttackRange : 0;
			int y2 = ((Object->KerLoc.Y + Object->uAttribute.AttackRange)<BATTLE_HEIGHT) ? Object->KerLoc.Y + Object->uAttribute.AttackRange : BATTLE_HEIGHT - 1;
			short x1 = ((Object->KerLoc.X - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.X - Object->uAttribute.AttackRange : 0;
			int x2 = ((Object->KerLoc.X + Object->uAttribute.AttackRange)<BATTLE_WIDTH) ? Object->KerLoc.X + Object->uAttribute.AttackRange : BATTLE_WIDTH - 1;
			int length = x2 - x1 + 1;
			for (short y = y1; y <= y2; y++)
				for (short x = x1; x <= x2; x++)
					if (Active[x][y].Occupied&&Object->KerLoc != COORD({ x, y }) && Active[x][y].UnitCamp != Object->camp)//如果有人而且不是自己而且那人是对立阵营的
					{
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
						Sleep(300);
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
						CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));//播放攻击音效
						Active[x][y].OccupyingUnit->GetInjuried(Object);//进行一次伤害
						Object->HeroToChase = Active[x][y].OccupyingUnit;//设置为追踪目标	
						Object->TmpAIState=AIStates[Object->number][AIPosChase];//转换到积极追逐状态
						goto BREAK;
					}
			GetLocalTime(&EndTest);//取得当前时间
		}
		BREAK:{}
	}
}
void AIPChaseState::Act()
{
	Object->Destination = Object->HeroToChase->KerLoc;
	int dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;
	int dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;
	while((dx<=Object->uAttribute.AttackRange+2)&&(dy <= Object->uAttribute.AttackRange + 2))//当没有超出攻击范围2的时候
	{
		if (!Object->FindPath())//不知道怎么追就不追了
			break;
		for (int i = 0; i < Object->uAttribute.Speed; i++)//找下一步的位置
			NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;
		Object->Jmp(NextLoc[Object->camp][Object->number]->Loc);
		GetLocalTime(&BeginTest);//取得开始检测的时间
		Sleep(1000 / Object->uAttribute.Frequence);//等待攻击间隔
		GetLocalTime(&EndTest);//取得结束检测时间
		for (; EndTest.wMilliseconds - BeginTest.wMilliseconds <= TestTime;)
		{
			int y1 = ((Object->KerLoc.Y - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.Y - Object->uAttribute.AttackRange : 0;
			int y2 = ((Object->KerLoc.Y + Object->uAttribute.AttackRange)<BATTLE_HEIGHT) ? Object->KerLoc.Y + Object->uAttribute.AttackRange : BATTLE_HEIGHT - 1;
			short x1 = ((Object->KerLoc.X - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.X - Object->uAttribute.AttackRange : 0;
			int x2 = ((Object->KerLoc.X + Object->uAttribute.AttackRange)<BATTLE_WIDTH) ? Object->KerLoc.X + Object->uAttribute.AttackRange : BATTLE_WIDTH - 1;
			int length = x2 - x1 + 1;
			for (short y = y1; y <= y2; y++)
				for (short x = x1; x <= x2; x++)
					if (Active[x][y].Occupied&&Object->KerLoc != COORD({ x, y }) && Active[x][y].UnitCamp != Object->camp)//如果有人而且不是自己而且那人是对立阵营的
					{
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
						Sleep(300);
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
						CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));//播放攻击音效
						Active[x][y].OccupyingUnit->GetInjuried(Object);//进行一次伤害
					}
			Sleep(1000 / Object->uAttribute.Frequence);//等待攻击间隔
			GetLocalTime(&EndTest);//取得当前时间
		}
		Object->Destination = Object->HeroToChase->KerLoc;//更新目标位置
		dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;//计算X距离
		dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;//计算Y距离
	}
	Object->TmpAIState = AIStates[Object->number][AIStill];//追逐完毕后进入静止状态
}
void AINChaseState::Act()
{
	int dx, dy;
	for(;;)
	{
		GetLocalTime(&BeginTest);//获取开始检测时间
		Object->Destination = Object->HeroToChase->KerLoc;
		if (!Object->FindPath())//不知道怎么追就不追了
			break;
		for (int i = 0; i < Object->uAttribute.Speed; i++)//找下一步的位置
			NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;
		Object->Jmp(NextLoc[Object->camp][Object->number]->Loc);
		Sleep(1000 / Object->uAttribute.Frequence);//等待攻击间隔
		GetLocalTime(&EndTest);//获取停止检测时间
		dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;//计算X相对距离
		dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;//计算Y相对距离
		if (dx > Object->uAttribute.AttackRange || dy > Object->uAttribute.AttackRange)//没到攻击范围 继续追
		{
			while (EndTest.wMilliseconds - BeginTest.wMilliseconds < TestTime)//等待足够的时间
				GetLocalTime(&EndTest);
			continue;
		}
		else
		{
			int y1 = ((Object->KerLoc.Y - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.Y - Object->uAttribute.AttackRange : 0;
			int y2 = ((Object->KerLoc.Y + Object->uAttribute.AttackRange)<BATTLE_HEIGHT) ? Object->KerLoc.Y + Object->uAttribute.AttackRange : BATTLE_HEIGHT - 1;
			short x1 = ((Object->KerLoc.X - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.X - Object->uAttribute.AttackRange : 0;
			int x2 = ((Object->KerLoc.X + Object->uAttribute.AttackRange)<BATTLE_WIDTH) ? Object->KerLoc.X + Object->uAttribute.AttackRange : BATTLE_WIDTH - 1;
			int length = x2 - x1 + 1;
			for (short y = y1; y <= y2; y++)
				FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
			Sleep(300);
			for (short y = y1; y <= y2; y++)
				FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
			CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));//播放攻击音效
			Object->HeroToChase->GetInjuried(Object);//受到伤害
			Object->TmpAIState = AIStates[Object->number][AIPosChase];//切换到积极追逐状态
			break;
		}
	}
}


Aector::Aector():CurMaxSize(AECTOR_DEFAULT_SIZE),CurSize(0)
{
	Content = new Astar*[CurMaxSize] {};
}
Aector::~Aector()
{
	Clean();
	delete[] Content;
}
void Aector::ReAector()
{
	Astar** Bigger = new Astar*[2 * CurMaxSize];
	for (int i = 0; i < CurMaxSize; i++)
		Bigger[i] = Content[i];
	delete[] Content;
	Content = Bigger;
	CurMaxSize *= 2;
}
void Aector::Add(Astar* Newstar)
{
	if (CurSize == CurMaxSize)
		ReAector();
	Content[CurSize++] = Newstar;
}
bool Aector::find(COORD Loc)
{
	for (int i = 0; i < CurSize; i++)
		if (Content[i]->Loc == Loc)
			return true;
	return false;
}
void Aector::Clean()
{
	for (int i = 0; i < CurSize; i++)
		if(!(Content[i]->IsPath))
			delete Content[i];
	CurSize = 0;
}

MinHeap::MinHeap():CurMaxSize(MINHEAP_DEFAULT_SIZE),CurSize(0),FoundIndex(0)
{
	Content = new Astar*[CurMaxSize+1] {};
}
MinHeap::~MinHeap()
{
	Clean();
	delete[] Content;
}
void MinHeap::ReHeap() 
{
	Astar** Bigger = new Astar*[CurMaxSize * 2+1];
	for (int i = 1; i <= CurMaxSize; i++)
		Bigger[i] = Content[i];
	delete[] Content;
	Content = Bigger;
	CurMaxSize *= 2;
}
void MinHeap::Swap(int i, int j)
{
	auto tmp = Content[i];
	Content[i] = Content[j];
	Content[j] = tmp;
}
Astar* MinHeap::find(COORD Loc)
{
	for (int i = 1; i < CurSize; i++)
		if (Content[i]->Loc == Loc)
		{
			FoundIndex = i;
			return Content[i];
		}
	return false;
}
Astar* MinHeap::remove()
{
	if (!CurSize)
		return 0;
	auto tmp = Content[1];
	Content[1] = Content[CurSize--];
	if (CurSize)
		HeapifyDown(1);
	return tmp;
}
void MinHeap::insert(Astar* Newstar)
{
	Content[++CurSize] = Newstar;
	HeapifyUp(CurSize);
}
void MinHeap::Heapify()
{
	if (FoundIndex == 1)
		HeapifyDown(1);
	else
	{
		if (Content[FoundIndex]->F < Content[FoundIndex / 2]->F)
			HeapifyUp(FoundIndex);
		else
			HeapifyDown(FoundIndex);
	}
}
void MinHeap::HeapifyDown(int index)
{
	for (;index*2+1<=CurSize;)
	{
		if ((Content[index]->F <= Content[index * 2]->F) && (Content[index]->F <= Content[index * 2 + 1]->F))//如果两个子节点均不小于该节点 则无需维护
			break;
		else//那么该节点至少大于两个子节点中的一个
		{
			if (Content[index * 2]->F <= Content[index * 2 + 1]->F)//当左节点较小时
			{
				Swap(index, index * 2);//那么当前节点的位子应该让给最小的左节点
				index = index * 2;
			}
			else//当右节点较小时
			{
				Swap(index, index * 2 + 1);//那么当前节点的位子应该让给最小的右节点
				index = index * 2 + 1;
			}
		}
	}
	if (index * 2 > CurSize)
		return;
	else
		if (Content[index]->F > Content[index * 2]->F)
			Swap(index, index * 2);
}
void MinHeap::HeapifyUp(int index)
{
	for (;index/2;)
	{
		if (Content[index]->F < Content[index / 2]->F)
		{
			Swap(index, index / 2);
			index /= 2;
		}
		else
			return;
	}
}
void MinHeap::Clean()
{
	for (int i = 1; i <= CurSize; i++)
		if(!(Content[i]->IsPath))
			delete Content[i];
	CurSize = 0;
}

Astar::Astar(Astar* father, COORD loc, COORD des)
{
	Father = father;
	Loc = loc;
	if (Father)
		G = Father->G + ((Father->Loc.X == Loc.X || Father->Loc.Y == Loc.Y) ? 10 : 14);
	else
		G = 0;
	des.X = (des.X >= Loc.X) ? des.X - Loc.X : Loc.X - des.X;
	des.Y = (des.Y >= Loc.Y) ? des.Y - Loc.Y : Loc.Y - des.Y;
	H = 10 * (des.X + des.Y);
	F = G + H;
	IsPath = false;
}
void Skill::LevelUp()
{
	*Effection += IncValue;
	*buff += IncBValue;
	level++;
}
void Skill::SetLevel(int DirectLevel)
{
	*Effection = BaseValue;
	for (int i = 1; i <= DirectLevel; i++)
		*Effection += IncValue;
	if (buff)
	{
		*buff = BaseBValue;
		for (int i = 1; i <= DirectLevel; i++)
			*buff += IncBValue;
	}
	level = DirectLevel;
}
void Skill::PrintName()
{
	short xStart = SCREEN_WIDTH - (9 - index % 3)*(THING_WIDTH_CHAR + 1);
	short yStart = SCREEN_HEIGHT + (index / 3-2)*(THING_HEIGHT_CHAR+1)+1;
	
	SetConsoleCursorPosition(hOut, {xStart , yStart});
	printf("等级%d", level);
	SetConsoleCursorPosition(hOut, { xStart , yStart+1 });
	printf("%s", name.c_str());
	SetConsoleCursorPosition(hOut, { xStart , yStart+2 });
	printf("消耗：%d", EnergyConsume);
	SetConsoleCursorPosition(hOut, { xStart , yStart+3 });
	printf("CD:%d", CD);
}
void Skill::SetSkill(Attribute basevalue, Attribute incvalue, Buff baseBvalue, Buff incBvalue)
{
	BaseValue = basevalue;
	IncValue = incvalue;
	if (baseBvalue.TimeLeft&&incBvalue.TimeLeft)
		buff = NULL;
	else
	{
		BaseBValue = baseBvalue;
		IncBValue = incBvalue;
	}
	SetLevel(0);
}
void Equipment::PrintName(int index)
{
	short xStart = SCREEN_WIDTH - (3 - index % 3)*(THING_WIDTH_CHAR + 1);
	short yStart = SCREEN_HEIGHT + (index / 3 - 2)*(THING_HEIGHT_CHAR + 1) + 1;
	SelectObject(hdc, hBlackBrush);
	Rectangle(hdc, xStart*PIX_PER_WIDTH, yStart*PIX_PER_HEIGHT, (xStart + THING_WIDTH_CHAR )*PIX_PER_WIDTH, (yStart + THING_HEIGHT_CHAR )*PIX_PER_HEIGHT);
	SetConsoleCursorPosition(hOut, { xStart , yStart });
	printf("￥：%d", EquipEffection.BaseAttack->RewardM);
	SetConsoleCursorPosition(hOut, { xStart , yStart +1});
	switch (StockNumber)
	{
	case 0://锋哥的指甲刀
	{
		printf("锋哥的");
		SetConsoleCursorPosition(hOut, { xStart , yStart+2 });
		printf("指甲刀");
	}
	break;
	case 1://锋哥的订书机
	{
		printf("锋哥的");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("订书机");
	}
	break;
	case 2://拖鞋
	{
		printf("拖鞋");
	}
	break;
	case 3://加厚的班服
	{
		printf("加厚的");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("班服");
	}
	break;
	case 4://吹风机
	{
		printf("吹风机");
	}
	break;
	case 5://锋哥的杠铃
	{
		printf("锋哥的");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("杠铃");
	}
	break;
	default:
		break;
	}
}
void Equipment::Set(Injury injury, string EquipName)
{
	EquipEffection = injury;
	name = EquipName;
}
void Consumable::PrintName(int index)
{
	short xStart = SCREEN_WIDTH - (6 - index % 3)*(THING_WIDTH_CHAR + 1);
	short yStart = SCREEN_HEIGHT + (index / 3 - 2)*(THING_HEIGHT_CHAR + 1) + 1;
	SetConsoleCursorPosition(hOut, { xStart , yStart });
	printf("￥：%d", ConsumableEffetion->Effection.RewardM);
	SetConsoleCursorPosition(hOut, { xStart , yStart +1});
	switch (StockNumber)
	{
	case 0://烤奶
	{
		printf("烤奶");
	}
	break;
	case 1://肾宝
	{
		printf("肾宝");
	}
	break;
	case 2://好吃的奇异果
	{
		printf("好吃的");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("奇异果");
	}
	break;
	case 3://维C柠檬茶
	{
		printf("维C柠檬茶");
	}
	break;
	case 4://咖啡
	{
		printf("咖啡");
	}
	break;
	case 5://电脑配件
	{
		printf("电脑配件");
	}
	break;
	default:
		break;
	}
}
void Consumable::PrintName(int index, int)
{

}

void Hero::GetInjuried(Hero* Attacker)
{
	if (Attacker)
	{
		HeroToChase = Attacker;
		SetEvent(ChaseMsg[number]);
		int Blood = (Attacker->uAttribute.Pa + uAttribute.Blood*Attacker->special.PhysicalPercent / 100) * 100 / (100 + uAttribute.Pd) + (Attacker->uAttribute.Ma + uAttribute.Blood*Attacker->special.MagicPercent / 100) * 100 / (100 + uAttribute.Md);
		srand(rand());
		int Rand = rand() % 100 + 1;
		if (Rand <= Attacker->uAttribute.CrRate)//暴击
			Blood *= 2;
		int BloodSucked = Blood * Attacker->special.SuckBlood / 100;
		int EnergySucked = Blood * Attacker->special.SuckMagic / 100;
		Attacker->SuckBlood(BloodSucked);
		Attacker->SuckEnergy(EnergySucked);
		uAttribute.Blood -= Blood;
	}
}
void Hero::SuckBlood(int blood)
{
	uAttribute.Blood = (uAttribute.Blood + blood) > uAttribute.MaxBlood ? uAttribute.MaxBlood : uAttribute.Blood + blood;
}
void Hero::SuckEnergy(int energy)
{
	uAttribute.Energy = (uAttribute.Energy + energy) > uAttribute.MaxEnergy ? uAttribute.MaxEnergy : uAttribute.Energy + energy;
}
void Hero::EraseSelf()
{
	FillConsoleOutputAttribute(hOut, 0, 1, KerLoc, &num);
	Active[KerLoc.X][KerLoc.Y].Occupied = false;
}
void Hero::ShowSelf()
{
	PrintSelf();//打印自己
	Active[KerLoc.X][KerLoc.Y].Occupied = true;
	Active[KerLoc.X][KerLoc.Y].OccupyingUnit = this;
	Active[KerLoc.X][KerLoc.Y].UnitCamp = camp;
}
void Hero::PrintSelf()
{
	FillConsoleOutputAttribute(hOut, Apperance, 1, KerLoc, &num);
}
void Hero::PrintImage()
{
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
		FillConsoleOutputCharacter(hOut, ' ', IMAGE_INFO, { 0,y }, &num);
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
		FillConsoleOutputAttribute(hOut, Apperance, IMAGE_INFO, { 0,y }, &num);//打印头像背景
	//下面这部分是共有的
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance,EyeHeight }, &num);//画左眼
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance,EyeHeight }, &num);//画右眼
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium,NoseHeight }, &num);//画鼻子
	FillConsoleOutputAttribute(hOut, 0, 2 * MouthWidth + 1, { ImageMidium - MouthWidth,MouthHeight }, &num);//画平嘴
	//下面这些是独特的
	if (uAttribute.Blood >= (uAttribute.MaxBlood / 2))
		PrintHappy();
	else if (uAttribute.Blood <= (uAttribute.MaxBlood / 4))
		PrintSad();
	else
		PrintGeneral();
}
void Hero::PrintHappy()
{
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance ,EyebrowHeight-1 }, &num);//画左边翘起的眉毛
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance ,EyebrowHeight - 1 }, &num);//画右边翘起的眉毛
	
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - MouthWidth,MouthHeight - 1 }, &num);//画左上扬嘴角
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + MouthWidth,MouthHeight - 1 }, &num);//画右上扬嘴角

}
void Hero::PrintSad()
{
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance ,EyebrowHeight - 1 }, &num);//画左边翘起的眉毛
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance ,EyebrowHeight - 1 }, &num);//画右边翘起的眉毛

	for (short i = 2; i <= 4; i++)//左右各画三滴眼泪
	{
		FillConsoleOutputAttribute(hOut, TearColor, 1, { ImageMidium - EyeDistance,EyeHeight + i }, &num);
		FillConsoleOutputAttribute(hOut, TearColor, 1, { ImageMidium + EyeDistance,EyeHeight + i }, &num);
	}
}
void Hero::PrintGeneral()
{
	FillConsoleOutputAttribute(hOut, 0, 3, { ImageMidium - EyeDistance - 1,EyebrowHeight }, &num);//画左边的平眉毛
	FillConsoleOutputAttribute(hOut, 0, 3, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);//画右边的平眉毛
}
void Hero::PrintInformation()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	if (this==Shop)//区分商店和英雄
	{
		SetConsoleTextAttribute(hOut, DefaultColor);
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 1 });
		printf("英雄%d:%14s               Lv.%d", number, name.c_str(),level);
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 2 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("生命值:%7d/%5d               ", uAttribute.Blood, uAttribute.MaxBlood);
		for (short y = 3; y <= 9; y++)
		{
			SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + y });
			printf("                                                       ");
		}
	}
	else
	{
		SetConsoleTextAttribute(hOut, DefaultColor);
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 1 });
		printf("英雄%d:%14s               Lv.%d", number, name.c_str(),level);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 3 });
		printf("技能点:%13d               经验:%9d/%5d",LeftSkillPoint,CurExperical,ExpercialNeeded);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 9 });
		printf("物理百分比:%8d%%               魔法百分比:%8d%%",special.PhysicalPercent,special.MagicPercent);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 4 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("生命值:%7d/%5d               ",uAttribute.Blood,uAttribute.MaxBlood);
		SetConsoleTextAttribute(hOut, EnergyColor);
		printf("法力值:%7d/%5d", uAttribute.Energy, uAttribute.MaxEnergy);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 2 });
		SetConsoleTextAttribute(hOut, MoneyColor);
		printf("金钱:%15d", money);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 5 });
		SetConsoleTextAttribute(hOut, PaColor);
		printf("攻击力:%13d               ",uAttribute.Pa);
		SetConsoleTextAttribute(hOut, MaColor);
		printf("法强:%15d",uAttribute.Ma);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 6 });
		SetConsoleTextAttribute(hOut, PdColor);
		printf("护甲:%15d               ",uAttribute.Pd);
		SetConsoleTextAttribute(hOut, MdColor);
		printf("魔抗:%15d",uAttribute.Md);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 7 });
		SetConsoleTextAttribute(hOut, SpeedColor);
		printf("攻速:%15f               移速:%15d",uAttribute.Frequence,uAttribute.Speed);
		
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 8 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("生命偷取:%10d%%               ",special.SuckBlood);
		SetConsoleTextAttribute(hOut, EnergyColor);
		printf("法力汲取:%10d%%",special.SuckMagic);
		
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 10 });
		SetConsoleTextAttribute(hOut, CrColor);
		printf("暴击率:%12d%%",uAttribute.CrRate);
	}
	ReleaseMutex(PRINTF_MUTEX);
}
bool Hero::GetEquipment(Equipment* NewEquipment)
{
	for(int i=0;i<MAX_THING_NUM;i++)
		if (!Equipments[i])
		{
			WaitForSingleObject(hmutex[camp][number], INFINITE);
			Equipments[i] = NewEquipment;//增加信息
			GetEquipmentEffection(NewEquipment->GetEffection());//获得装备效果
			ReleaseMutex(hmutex[camp][number]);
			return true;
		}
	return false;
}
void Hero::GetEquipmentEffection(Injury EquipEffection)
{
	uAttribute += *(EquipEffection.BaseAttack);
	special += *(EquipEffection.special);
}
void Hero::GetSlowRecovery(Attribute& ThingEff)
{
	uAttribute.Blood = ((uAttribute.Blood + ThingEff.Blood) > uAttribute.MaxBlood) ? uAttribute.MaxBlood : uAttribute.Blood + ThingEff.Blood;
	uAttribute.Energy = ((uAttribute.Energy + ThingEff.Energy) > uAttribute.MaxEnergy) ? uAttribute.MaxEnergy : uAttribute.Energy + ThingEff.Energy;
}
void Hero::Jmp(COORD NextKerLoc)
{
	//这一部分是抹除之前的
	EraseSelf();
	//更新内核位置
	KerLoc = NextKerLoc;
	//这一部分是更新的
	ShowSelf();

}
bool Hero::FindPath()
{
	if (KerLoc == Destination)
		return false;
	Astar* Start = new Astar(NULL, KerLoc, Destination);
	Open[camp][number]->insert(Start);//将起始点假如开启列表中
	Astar* Curstar = Open[camp][number]->remove();//获得这个位置
	Close[camp][number]->Add(Curstar);//关闭列表中增加
	for (; Curstar->Loc != Destination;)
	{
		Close[camp][number]->Add(Curstar);//关闭列表中添加当前方格
		int y1 = Curstar->Loc.Y ? Curstar->Loc.Y - 1 : 0;
		int y2 = (BATTLE_HEIGHT - Curstar->Loc.Y - 1) ? Curstar->Loc.Y + 1: BATTLE_HEIGHT-1;
		int x1 = Curstar->Loc.X ? Curstar->Loc.X - 1 : 0;
		int x2= (BATTLE_WIDTH - Curstar->Loc.X - 1) ? Curstar->Loc.X + 1 : BATTLE_WIDTH - 1;
		for (short y = y1; y <= y2; y++)
			for (short x = x1; x <= x2; x++)
			{
					if (Active[x][y].Occupied &&Destination != COORD({ x,y }))//有人而且那还不是目的地的话 就设置Flase
						Close[camp][number]->Add(new Astar(NULL, { x,y }, { x,y }));
					if (!Close[camp][number]->find({ x,y }))
					{
						Astar* Son;
						if (Son = Open[camp][number]->find({ x,y }))//如果这块砖在开启列表中
						{
							int NewG = Curstar->G + ((Curstar->Loc.X == x || Curstar->Loc.Y == y) ? 10 : 14);//计算新的G值
							if (NewG < Son->G)//如果新路径更短 那么就更新这块砖的信息
							{
								Son->Father = Curstar;
								Son->G = NewG;
								Son->F = Son->G + Son->H;
								Open[camp][number]->Heapify();//重新维护堆的性质
							}
						}
						else
							Open[camp][number]->insert(new Astar(Curstar, { x,y }, Destination));//如果不在开启列表中 开启列表中增加这一项
					}
			}
		if (!(Curstar = Open[camp][number]->remove()))//开启列表中移除最小优先方格
			return false;//如果此时列表已经空 说明没有路径 失败
	}
	Curstar->Next = Curstar;//设置最后一个的结尾
	Curstar->IsPath = true;
	auto son = Curstar;//设置Next的性质
	for (auto tmp = Curstar->Father; tmp; )
	{
		tmp->IsPath = true;
		tmp->Next = son;
		son = son->Father;
		tmp = tmp->Father;
	}
	for (; PathBegin[camp][number];)//删除旧的路径
	{
		auto tmp = PathBegin[camp][number];//暂存这个节点
		PathBegin[camp][number] = PathBegin[camp][number]->Next;//向后推一个节点
		if (tmp == PathBegin[camp][number])//如果这个节点和它的后续节点相同 说明到了结尾 那么就可以退出了
			break;
		delete tmp;//删除这个节点
	}
	NextLoc[camp][number] =PathBegin[camp][number] = Start;//设置起点
	Open[camp][number]->Clean();//将除路径外的其他
	Close[camp][number]->Clean();//节点全部删除
	return true;//寻路成功
}
void Hero::LoseEquipment(int index)
{
	EraseThing(EQUIPMENT, index);//擦去图片
	uAttribute -= *(Equipments[index]->GetEffection().BaseAttack);//删除基础效果
	special -= *(Equipments[index]->GetEffection().special);//删除特殊效果
	Equipments[index] = NULL;//清除记录
}
void Hero::GetEffectedByBuff(Buff* BuffEffection)
{
	if (camp==BuffEffection->Effection.Camp)
	{
		if (BuffEffection->Effection.LastTime)//如果是持续性效果
		{//以下是准备工作 创建一个buff的副本
			Buff* Tmp = new Buff(*BuffEffection);
			Tmp->Next = Head->Next;
			Tmp->Prev = Head;
			Head->Next = Head->Next->Prev = Tmp;//更新节点信息
			uAttribute += Tmp->Effection;//进行状态加成
			//通知线程 有Buff产生
			SetEvent(BuffMsg[camp][number]);
		}
		else
		{
			uAttribute += BuffEffection->Effection;
			special += BuffEffection->special;
		}
	}
}
void Hero::GetSkillEffection(Skill* skill)
{
	if (skill->buff)
		GetEffectedByBuff(skill->buff);
	uAttribute.Blood = (uAttribute.Blood + skill->Effection->Blood) <= uAttribute.MaxBlood ? uAttribute.Blood + skill->Effection->Blood : uAttribute.MaxBlood;
	uAttribute.Energy = (uAttribute.Energy + skill->Effection->Energy) <= uAttribute.MaxEnergy ? uAttribute.Energy + skill->Effection->Energy : uAttribute.MaxEnergy;
	int FinalInjury = (skill->Effection->Pa + skill->ADR*skill->Owner->uAttribute.Pa)*uAttribute.Pd / (100 + uAttribute.Pd) + (skill->Effection->Ma + skill->APR*skill->Owner->uAttribute.Ma)*uAttribute.Md / (100 + uAttribute.Md);
	uAttribute.Blood -= FinalInjury;
}
void Hero::LoadBIAttribute(Attribute Base, Attribute Inc)
{
	BaseAttribute = Base;
	IncAttribute = Inc;
}
void Hero::LoadBISpecial(Special Base, Special Inc)
{
	BaseSpecial = Base;
	IncSpecial = Inc;
}
void Hero::GetSelected()
{
	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
		FillConsoleOutputCharacterA(hOut, ' ', SCREEN_WIDTH - INFO_FUNCTION - 2, { INFO_FUNCTION + 1,y }, &num);
	PrintImage();//显示头像区
	PrintInformation();//显示信息区
	PrintFunction();//设置功能区
}
void Hero::LoadReuseAttribute()
{
	CurExperical = 0;
	//number=??? number只有在购买时才确定
	dead = false;
	KerLoc = HERO_INITIAL_LOC;
	Destination = HERO_INITIAL_LOC;
	uAttribute = BaseAttribute;
	special = BaseSpecial;
	level = 0;
	LeftSkillPoint = 0;
	Head = new Buff({ 0,EMPTY_ATTRIBUTE,EMPTY_SPECIAL,NULL,Rear });
	Rear = new Buff({ 0,EMPTY_ATTRIBUTE,EMPTY_SPECIAL,Head,NULL });
	HeroToChase = NULL;
	for (int i = 0; i < MAX_THING_NUM; i++)
		Equipments[i] = NULL;
}

void GPHero::Operating()
{
	Rebrith();
	while (!dead)
	{
		WaitForSingleObject(AttackMsg[number], INFINITE);//等待攻击指令
		if (dead)
		{
			CloseHandle(AttackMsg[number]);
			for (int i = number; i <= CurNum[camp] - 1; i++)
			{
				Heros[i] = Heros[i + 1];//填补这个英雄的空
				Heros[i]->number--;
			}
			CurNum[camp]--;//删除这个英雄
			for (int i = 1; i <= CurNum[camp]; i++)
				Heros[i]->GetExperical(uAttribute.RewardE);//获得经验
			money += uAttribute.RewardM;//获得金钱
			return;
		}
		int y1 = ((KerLoc.Y - uAttribute.AttackRange) >= 0) ? KerLoc.Y - uAttribute.AttackRange : 0;
		int y2 = ((KerLoc.Y + uAttribute.AttackRange)<BATTLE_HEIGHT) ? KerLoc.Y + uAttribute.AttackRange : BATTLE_HEIGHT - 1;
		short x1 = ((KerLoc.X - uAttribute.AttackRange) >= 0) ? KerLoc.X - uAttribute.AttackRange : 0;
		int x2 = ((KerLoc.X + uAttribute.AttackRange)<BATTLE_WIDTH) ? KerLoc.X + uAttribute.AttackRange : BATTLE_WIDTH - 1;
		int length = x2 - x1 + 1;
		for (short y = y1; y <= y2; y++)
			for (short x = x1; x <= x2; x++)
			{
				
				if (Active[x][y].Occupied&&KerLoc != COORD({x, y})&&Active[x][y].UnitCamp!=camp)//如果有人而且不是自己而且那人是对立阵营的
				{
					for (short y = y1; y <= y2; y++)
						FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, {x1,y},&num);
					Sleep(300);
					for (short y = y1; y <= y2; y++)
						FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
					CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));
					Active[x][y].OccupyingUnit->GetInjuried(this);//进行一次伤害后退出
					HeroToChase = Active[x][y].OccupyingUnit;//设置为追踪目标	
					SetEvent(ChaseMsg[number]);//发送追踪信号 模拟仇恨机制
					isChasing = true;
					break;
				}
			}
		if (uAttribute.Blood <= 0)
			Die();
		Sleep((double)1000/uAttribute.Frequence);
	}
	Die();
}
void GPHero::GetExperical(int experical)
{
	if (experical + CurExperical >= ExpercialNeeded)
	{
		experical = experical + CurExperical - ExpercialNeeded;
		LevelUp();
	}
	else
		CurExperical += experical;
}
void GPHero::LevelUp()
{
	level++;
	LeftSkillPoint++;
	uAttribute += IncAttribute;
	ExpercialNeeded += INC_HERO_EXPERICAL;
}
void GPHero::GetSelected()
{
	if (!number)
	{
		//商店随机生成商品
		for (int i = 0; i < MAX_THING_NUM; i++)
		{
			srand(rand() + 1);
			Consumables[i] = &ConsumableStock[rand() % CONSUMABLE_STOCK];
			srand(rand() + 1);
			Equipments[i] = &EquipmentStock[rand() % EQUIPMENT_STOCK];
			srand(rand() + 1);
			EnhanceBooks[i] = &EnhanceBookStock[rand() % ENHANCEBOOK_STOCK];
		}
		TmpMOPState = PMState;//切换到购物状态
		Gotta = dynamic_cast<GPHero*>(CurSelectedHero);//设置购买者
	}
	else
		TmpMOPState = FMState;//否则切换到普通状态
	Hero::GetSelected();
}
void GPHero::PrintFunction()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	SetConsoleTextAttribute(hOut, SKILL_COLOR);
	if (this == Shop)
	{
		for (int i = 0; i < MAX_THING_NUM; i++)
			EnhanceBooks[i]->PrintName(i, 0);
	}
	else
	{
		for (int i = 0; i < MAX_THING_NUM; i++)
			if (Skills[i])
				Skills[i]->PrintName();
	}
	SetConsoleTextAttribute(hOut, EQUIPMENT_COLOR);
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Equipments[i])
			Equipments[i]->PrintName(i);

	SetConsoleTextAttribute(hOut, CONSUMABLE_COLOR);
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Consumables[i])
			Consumables[i]->PrintName(i);
	ReleaseMutex(PRINTF_MUTEX);
}
void GPHero::UseConsumable(int index)//index范围是0-5
{
	if (Consumables[index])//如果这个格子里有消耗品
	{
		if (Consumables[index]->Range)
		{
			if (Consumables[index]->EffectionCamp() == Allies)
				for (int i = 1; i <= CurNum[Allies]; i++)
					Heros[i]->GetEffectedByBuff(Consumables[index]->Effect());//获得效果
			else
				for (int i = 1; i <= CurNum[Enemy]; i++)
					Monsters[i]->GetEffectedByBuff(Consumables[index]->Effect());//获得效果
		}
		else
			GetEffectedByBuff(Consumables[index]->Effect());//获得效果
		EraseThing(CONSUMABLE, index);//擦去图片
		LoseConsumable(index);//在成员中设置NULL
	}
}
void GPHero::MoveTo(COORD destination)
{
	if (camp == Allies && number)
	{
		WaitForSingleObject(hmutex[camp][number], INFINITE);
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMoveSound, (void*)this, 0, NULL));
		ResetEvent(AttackMsg[number]);//设置取消取消攻击
		if (Active[destination.X][destination.Y].Occupied)
		{
			HeroToChase = Active[destination.X][destination.Y].OccupyingUnit;
			SetEvent(ChaseMsg[number]);//设置追逐信号
			isChasing = true;
		}
		else
		{
			ResetEvent(ChaseMsg[number]);//设置不追逐的信号
			isChasing = false;
			Destination = destination;//设置目的地
		}
		SetEvent(MoveMsg[number]);//设置移动信号
		ReleaseMutex(hmutex[camp][number]);
	}
}
void GPHero::TransportEquipTo(int HeroIndex)
{
	if (Heros[HeroIndex]->GetEquipment(Equipments[CurTransportedEquipIndex]))
		LoseEquipment(CurTransportedEquipIndex);
}
void GPHero::TransportConsumableTo(int HeroIndex)
{
	if (Heros[HeroIndex]->GetConsumable(Consumables[CurTransportedThingIndex]))
		LoseConsumable(CurTransportedThingIndex);
}
void GPHero::LoseConsumable(int index) { Consumables[index] = NULL; }
bool GPHero::GetConsumable(Consumable* NewConsumable)
{
	for (int i = 0; i<MAX_THING_NUM; i++)
		if (!Consumables[i])
		{
			Consumables[i] = NewConsumable;
			return true;
		}
	return false;
}
void GPHero::LoadReuseAttribute()
{
	Hero::LoadReuseAttribute();
	ExpercialNeeded = INC_HERO_EXPERICAL;
	for (int i = 0; i < MAX_THING_NUM; i++)
	{
		Consumables[i] = NULL;
		EnhanceBooks[i] = NULL;
		Skills[i] = &GPSkillStock[(StockNumber-1)*MAX_HERO_SKILL_NUM+i + 1];
	}
	isChasing = false;
}
void GPHero::Rebrith()
{
	number = ++CurNum[Allies];
	dead = false;
	KerLoc = HERO_INITIAL_LOC;
	Destination = HERO_INITIAL_LOC;
	for (int i = 0; i < MAX_HERO_SKILL_NUM; i++)
		Skills[i] = &GPSkillStock[(number - 1)*MAX_HERO_SKILL_NUM + i + 1];
	uAttribute.Blood = uAttribute.MaxBlood;
	uAttribute.Energy = uAttribute.MaxEnergy;
	HeroToChase = NULL;
	isChasing = false;
	//重新创建资源量并设置状态
	Open[Allies][number] = new MinHeap;
	Close[Allies][number] = new Aector;
	hmutex[Allies][number] = CreateMutex(NULL, false, NULL);//生成锁
	AttackMsg[number] = CreateEvent(NULL, true, true, NULL);//初始即可检测攻击
	BuffMsg[Allies][number] = CreateEvent(NULL, true, false, NULL);//初始无buff
	SkillCDMsg[Allies][number] = CreateEvent(NULL, true, false, NULL);//初始无技能处于CD
	MoveMsg[number] = CreateEvent(NULL, true, false, NULL);//初始未移动
	ChaseMsg[number] = CreateEvent(NULL, true, false, NULL);//初始未追逐
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, UpdateBuff, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, FlushGPSkill, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, SolveMove, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, ToChase, (void*)this, 0, NULL));
	CurSelectedHero = this;
	ShowSelf();
	GetSelected();
}
void GPHero::Die()
{

	if (!number)
		GameOver();
	else
	{
		GenerateReward();
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayDieSound, (void*)this, 0, NULL));
		SetEvent(BuffMsg[camp][number]);//确保退出线程
		SetEvent(SkillCDMsg[camp][number]);//确保退出线程
		SetEvent(MoveMsg[number]);//确保退出线程
		SetEvent(ChaseMsg[number]);//确保退出线程
		//清除buff
		for (auto tmp = Head->Next; tmp != Rear; tmp = tmp->Next)
		{
			tmp->Prev->Next = tmp->Next;
			tmp->Next->Prev = tmp->Prev;
			delete tmp;
		}
		//删除旧的路径
		Open[Allies][number]->Clean();
		Close[Allies][number]->Clean();
		for (; PathBegin[Allies][number];)
		{
			auto tmp = PathBegin[Allies][number];//暂存这个节点
			PathBegin[Allies][number] = PathBegin[Allies][number]->Next;//向后推一个节点
			if (tmp == PathBegin[Allies][number])//如果这个节点和它的后续节点相同 说明到了结尾 那么就可以退出了
				break;
			delete tmp;//删除这个节点
		}
		//关闭句柄 删除占用的资源 
		CloseHandle(BuffMsg[Allies][number]);
		CloseHandle(SkillCDMsg[Allies][number]);
		CloseHandle(MoveMsg[number]);
		CloseHandle(ChaseMsg[number]);
		CloseHandle(AttackMsg[number]);
		delete Open[Allies][number];
		delete Close[Allies][number];
		for (int i = number; i <= CurNum[Allies] - 1; i++)
		{
			BuffMsg[Allies][i] = BuffMsg[Allies][i + 1];
			SkillCDMsg[Allies][i] = SkillCDMsg[Allies][i + 1];
			MoveMsg[i] = MoveMsg[i + 1];
			ChaseMsg[i] = ChaseMsg[i + 1];
			AttackMsg[i] = AttackMsg[i + 1];
			hmutex[Allies][i] = hmutex[Allies][i + 1];
			Open[Allies][i] = Open[Allies][i + 1];
			Close[Allies][i] = Close[Allies][i + 1];
			PathBegin[Allies][i] = PathBegin[Allies][i + 1];
			NextLoc[Allies][i] = NextLoc[Allies][i + 1];
			Heros[i + 1]->number--;
			Heros[i] = Heros[i + 1];
		}
		EraseSelf();
		CurNum[Allies]--;
	}
}
void GPHero::GenerateReward()
{
	for(int i=1;i<=number-1;i++)
		Heros[i]->GetExperical(uAttribute.RewardE);
	for (int i = number + 1; i <= CurNum[Allies]; i++)
		Heros[i]->GetExperical(uAttribute.RewardE);
	money += uAttribute.RewardM;
}

void AIHero::SetRebrithLevel(int NewLevel)
{
	level = NewLevel;
	//以下设定技能等级
	if (level%MAX_MONSTER_SKILL_NUM == 0)
		for (int i = 0; i < MAX_MONSTER_SKILL_NUM; i++)
			Skills[i]->SetLevel(level / MAX_MONSTER_SKILL_NUM);
	else
	{
		for (int i = 0; i < MAX_MONSTER_SKILL_NUM - 1; i++)
			Skills[i]->SetLevel(level / (MAX_MONSTER_SKILL_NUM - 1));
		Skills[MAX_MONSTER_SKILL_NUM - 1]->SetLevel(level % (MAX_MONSTER_SKILL_NUM - 1));
	}
	uAttribute = BaseAttribute;
	special = BaseSpecial;
	for (int i = 1; i <= level; i++)
	{
		uAttribute += IncAttribute;
		special += IncSpecial;
	}
}
void AIHero::Rebrith()
{
	number = ++CurNum[Enemy];
	dead = false;
	srand(rand() + 1);
	//设定重生等级
	SetRebrithLevel(StockNumber == 1 ? Round : (StockNumber == 2 ? Round - SecondMonsterTurnUp : Round - ThirdMonsterTurnUp));
	//随机生成重生位置
	switch (rand() % 4)//设定初始降生位置
	{
	case 0:
	{
		srand(rand() + 1);
		KerLoc = { rand() % (BATTLE_WIDTH - 2) + 1,0 };
	}
	break;
	case 1:
	{
		srand(rand() + 1);
		KerLoc = { rand() % (BATTLE_WIDTH - 2) + 1,BATTLE_HEIGHT - 1 };
	}
	case 2:
	{
		srand(rand() + 1);
		KerLoc = { 0,rand() % (BATTLE_HEIGHT - 2) + 1 };
	}
	break;
	case 3:
	{
		srand(rand() + 1);
		KerLoc = { BATTLE_WIDTH - 1,rand() % (BATTLE_HEIGHT - 2) + 1 };
	}
	break;
	default:
		break;
	}
	Destination = CITADEL;
	//重新获得技能
	for (int i = 0; i<MAX_MONSTER_SKILL_NUM; i++)
		Skills[i] = &AISkillStock[(StockNumber - 1)*MAX_MONSTER_SKILL_NUM + i + 1];
	//失去现有装备
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Equipments[i])
			LoseEquipment(i);
	//设置辅导员的装备数
	int EquipmentNum;
	if (Round >= MAX_THING_NUM * RoundsToGetMoreOneEqipment)
		EquipmentNum = 6;
	else
		EquipmentNum = Round / RoundsToGetMoreOneEqipment;
	//重新获得装备
	for (int i = 1; i <= EquipmentNum; i++)
	{
		srand(rand() + 1);
		GetEquipment(&EquipmentStock[rand() % EQUIPMENT_STOCK]);
	}
	HeroToChase = NULL;
	//重新创建资源量并设置状态
	AIStates[number][AIStill] = new AIStillState;
	AIStates[number][AIPosChase] = new AIPChaseState;
	AIStates[number][AINegChase] = new AINChaseState;
	CurAIState = AIStates[number][AIStill];
	TmpAIState = AIStates[number][AIStill];
	Open[Enemy][number] = new MinHeap;
	Close[Enemy][number] = new Aector;
	hmutex[Enemy][number]=CreateMutex(NULL, false, NULL);//生成锁
	BuffMsg[Enemy][number] = CreateEvent(NULL, true, false, NULL);//初始无buff
	SkillCDMsg[Enemy][number] = CreateEvent(NULL, true, false, NULL);//初始无技能处于CD
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, UpdateBuff, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, FlushAISkill, (void*)this, 0, NULL));
	ShowSelf();
}
void AIHero::Die()
{
	GenerateReward();
	SetEvent(BuffMsg[Enemy][number]);//确保退出线程
	SetEvent(SkillCDMsg[Enemy][number]);//确保退出线程
	//清除buff
	for (auto tmp = Head->Next; tmp != Rear; tmp = tmp->Next)
	{
		tmp->Prev->Next = tmp->Next;
		tmp->Next->Prev = tmp->Prev;
		delete tmp;
	}
	//删除旧的路径
	Open[Enemy][number]->Clean();
	Close[Enemy][number]->Clean();
	for (; PathBegin[Enemy][number];)
	{
		auto tmp = PathBegin[Enemy][number];//暂存这个节点
		PathBegin[Enemy][number] = PathBegin[Enemy][number]->Next;//向后推一个节点
		if (tmp == PathBegin[Enemy][number])//如果这个节点和它的后续节点相同 说明到了结尾 那么就可以退出了
			break;
		delete tmp;//删除这个节点
	}
	//关闭句柄 删除占用的资源 
	CloseHandle(BuffMsg[Enemy][number]);
	CloseHandle(SkillCDMsg[Enemy][number]);
	CloseHandle(hmutex[Enemy][number]);
	delete Open[Enemy][number];
	delete Close[Enemy][number];
	for (int i = 0; i < AI_STATE_NUM; i++)
		delete AIStates[number][i];
	for (int i = number; i <= CurNum[Enemy] - 1; i++)
	{
		BuffMsg[Enemy][i] = BuffMsg[Enemy][i + 1];
		SkillCDMsg[Enemy][i] = SkillCDMsg[Enemy][i + 1];
		hmutex[Enemy][i] = hmutex[Enemy][i + 1];
		Open[Enemy][i] = Open[Enemy][i + 1];
		Close[Enemy][i] = Close[Enemy][i + 1];
		PathBegin[Enemy][i] = PathBegin[Enemy][i + 1];
		NextLoc[Enemy][i] = NextLoc[Enemy][i + 1];
		Monsters[i + 1]->number--;
	}
	EraseSelf();
	CurNum[Enemy]--;
}
void AIHero::Operating()
{
	Rebrith();
	while(!dead)
	{
		CurAIState->Act();
		CurAIState = TmpAIState;
	}
	Die();
}
void AIHero::GetSelected()
{
	TmpMOPState = FMState;
	Hero::GetSelected();
}
void AIHero::LoadReuseAttribute()
{
	Hero::LoadReuseAttribute();
	ExpercialNeeded = 0;
	for(int i=0;i<MAX_MONSTER_SKILL_NUM;i++)
		Skills[i]= &AISkillStock[(StockNumber - 1)*MAX_MONSTER_SKILL_NUM + i + 1];
}
void AIHero::GenerateReward()
{
	for (int i = 1; i <= CurNum[Allies]; i++)
		Heros[i]->GetExperical(uAttribute.RewardE);
	money += uAttribute.RewardM;
}
void AIHero::PrintFunction()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);

	SetConsoleTextAttribute(hOut, SKILL_COLOR);
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Skills[i])
			Skills[i]->PrintName();

	SetConsoleTextAttribute(hOut, EQUIPMENT_COLOR);
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Equipments[i])
			Equipments[i]->PrintName(i);

	ReleaseMutex(PRINTF_MUTEX);

}
//***********************************************************************************************
//***********************************以下是实际运营时内部的调度函数******************************
//***********************************************************************************************
void HandleKeyInput(KEY_EVENT_RECORD NewEvent) 
{
	GPHero* Tmp;
	if (NewEvent.bKeyDown)
	{
		int HeroNumber = NewEvent.wVirtualKeyCode - 48;
		if (NewEvent.dwControlKeyState&LEFT_CTRL_PRESSED&&HeroNumber > 0 && HeroNumber <= GP_STOCK)//如果控制键按下 说明是要买英雄
			BuyHero(HeroNumber);
		else if (HeroNumber >= 0 && HeroNumber <= CurNum[Allies])//如果是合法的英雄选定
		{
			if(CurMOPState==TMState)//如果在转移
			{
				if (!(Tmp = dynamic_cast<GPHero*>(CurSelectedHero)))
					system("pause");
				if (HeroNumber == 0)//选0说明要卖装备
				{
					EraseThing(TransportedType, CurTransportedThingIndex);//擦去物品图片
					money += ((TransportedType == EQUIPMENT) ? Tmp->Equipments[CurTransportedThingIndex]->GetEffection().BaseAttack->RewardM : Tmp->Consumables[CurTransportedThingIndex]->Effect()->Effection.RewardM)*SELL_RATE / 10;//拿钱
					if (TransportedType == EQUIPMENT)
						Tmp->Equipments[CurTransportedThingIndex] = NULL;//卖掉物品
					else
						Tmp->Consumables[CurTransportedThingIndex] = NULL;
				}
				else//说明要转移东西
				{
					if (TransportedType == CONSUMABLE && Heros[HeroNumber]->GetConsumable(Tmp->Consumables[CurTransportedThingIndex]))//如果是传输的消耗品 而且有空位
					{
						Tmp->LoseConsumable(CurTransportedThingIndex);//失去装备
						EraseThing(CONSUMABLE, CurTransportedThingIndex);//抹去图片
					}
					else if (TransportedType == EQUIPMENT && Heros[HeroNumber]->GetEquipment(Tmp->Equipments[CurTransportedThingIndex]))//如果是传输的装备 而且有空位
					{
						Tmp->LoseEquipment(CurTransportedThingIndex);//失去装备
						EraseThing(EQUIPMENT, CurTransportedThingIndex);//抹去图片
					}
				}
				CurMOPState = FMState;//重置状态
			}
			else//如果不是转移就切换英雄 或者购买英雄
			{
				Gotta = dynamic_cast<GPHero*>(CurSelectedHero);
				(CurSelectedHero = Heros[HeroNumber])->GetSelected();//登记信息 通知英雄他被选定了 指示他做出动作
			}
		}
		CurMOPState = FMState;//重置状态
	}
}
void HandleMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	CurMOPState->SolveMouseInput(NewEvent);
	CurMOPState = TmpMOPState;
}
void Operate()
{
	while (ReadConsoleInput(hIn, Inputs, MAX_INPUT_RECORD, &InputOneTime))
	{
		for (int i = 0; i < InputOneTime; i++)
		{
			if (Inputs[i].EventType == MOUSE_EVENT)//鼠标事件
				HandleMouseInput(Inputs[i].Event.MouseEvent);
			else if (Inputs[i].EventType == KEY_EVENT)//键盘事件
				HandleKeyInput(Inputs[i].Event.KeyEvent);
		}
	}
}

//**********************************************************************************************
//*********************************以下是主函数内调用的函数*************************************
//**********************************************************************************************
void LoadHeroApperance()
{
	HeroStock[0].Apperance = CitadelColor;
	HeroStock[1].Apperance = Cairne_Bloodhoof;
	HeroStock[2].Apperance = Tyrande_Whisperwind;
	HeroStock[3].Apperance = Illidan_Stormrage;
	HeroStock[4].Apperance = Uther;
	HeroStock[5].Apperance = Grom_Hellscream;
}
void LoadHeroSound()
{
	HeroStock[1].MoveSoundNum = 8;
	HeroStock[1].MoveSounds[0] = "大一移动1.wav";
	HeroStock[1].MoveSounds[1] = "大一移动2.wav";
	HeroStock[1].MoveSounds[2] = "大一移动3.wav";
	HeroStock[1].MoveSounds[3] = "大一移动4.wav";
	HeroStock[1].MoveSounds[4] = "大一移动5.wav";
	HeroStock[1].MoveSounds[5] = "大一移动6.wav";
	HeroStock[1].MoveSounds[6] = "大一移动7.wav";
	HeroStock[1].MoveSounds[7] = "大一移动8.wav";
	HeroStock[1].AttackSoundNum = 11;
	HeroStock[1].AttackSounds[0] = "大一攻击1.wav";
	HeroStock[1].AttackSounds[1] = "大一攻击2.wav";
	HeroStock[1].AttackSounds[2] = "大一攻击3.wav";
	HeroStock[1].AttackSounds[3] = "大一攻击4.wav";
	HeroStock[1].AttackSounds[4] = "大一攻击5.wav";
	HeroStock[1].AttackSounds[5] = "大一攻击6.wav";
	HeroStock[1].AttackSounds[6] = "大一攻击7.wav";
	HeroStock[1].AttackSounds[7] = "大一攻击8.wav";
	HeroStock[1].AttackSounds[8] = "大一攻击9.wav";
	HeroStock[1].AttackSounds[9] = "大一攻击10.wav";
	HeroStock[1].AttackSounds[10] = "大一攻击11.wav";
}
void LoadHeroName()
{
	HeroStock[0].name = "寝室";
	HeroStock[1].name = "大一萌新";
	HeroStock[2].name = "大二学姐";
	HeroStock[3].name = "大三腊肉";
	HeroStock[4].name = "大四骨灰";
}
void LoadHeroBaseAtttibuteStock()
{
	
	//{阵营，魔抗，护甲，血量上限，法力上限，当前血量，当前法力，移速，物攻，魔攻，暴击，攻速，赏金，赏经验，(持续时间)，攻击范围}
	//寝室
	GPBAttributeStock[0] = {Allies,0,0,0,5000,0,5000,0,0,0,0,0,0,0,0,0,0};
	//大一萌新
	GPBAttributeStock[1] = { Allies,0,10,10,625,200,625,200,1,45,0,0,0.5,100,50,0,1};
	//大二学姐
	GPBAttributeStock[2] = { Allies,1,0,0,400,200,400,200,1,70,25,0,1,60,50,0,4 };
	//大三腊肉
	GPBAttributeStock[3] = { Allies,2,5,5,525,200,525,200,1,65,20,10,0.5,100,50,0,2 };
	//大四骨灰
	GPBAttributeStock[4] = { Allies,3,0,0,425,400,425,400,1,35,20,0,0.5,100,50,0,2 };
}
void LoadHeroIncAtttibuteStock()
{
	//{阵营，魔抗，护甲，血量上限，法力上限，当前血量，当前法力，移速，物攻，魔攻，暴击，攻速，赏金，赏经验，(持续时间)，攻击范围}
	//寝室
	GPIAtrributeStock[0] = { Allies,0,100,100,1000,0,1000,0,0,0,0,0,0,0,0,0,0 };
	//大一萌新
	GPIAtrributeStock[1] = { Allies,0,4,4,60,20,60,20,0,0,1,1,0,0,0,0,0 };
	//大二学姐
	GPIAtrributeStock[2] = { Allies,1,1,1,40,20,40,20,0,3,2,0,0.04,0,0,0,0 };
	//大三腊肉
	GPIAtrributeStock[3] = { Allies,2,3,2,50,20,50,20,0,2,2,0,0.03,0,0,0,0 };
	//大四骨灰
	GPIAtrributeStock[4] = { Allies,3,1,1,40,50,40,50,0,1,5,0,0,0,0,0,0 };
}
void LoadHeroBaseSpecialStock()
{
	//{吸血率，吸蓝率，物理百分比率，魔法百分比率}
	GPBSpecialStock[0];
}
void LoadHeroIncSpecialStock()
{
	//{吸血率，吸蓝率，物理百分比率，魔法百分比率}
	GPISpecialStock[0];

}

void LoadSkillBaseStock()
{
	//这部分全都是永久效果 要小心
	//对敌军时
	//{Enemy，0，削减魔抗，削减护甲，(血量上限)，(法力上限)，()，()，削减移速，物理伤害，魔法伤害，削减暴击，削减攻速，(赏金)，(赏经验)，(持续时间)，削减攻击范围}
	//对友军时
	//{Allies，0，增加魔抗，增加护甲，(血量上限)，(法力上限)，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，(赏金)，(赏经验)，(持续时间)，增加攻击范围}
	GPSkillAttributeBStock[0] = { Enemy,0,0,0,0,0,0,0,0,100,0,0,0,0,0,0,2 };
	GPSkillAttributeBStock[1] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[2] = { Allies,0,0,0,0,0,75,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeBStock[3] = { Allies,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0 };
	GPSkillAttributeBStock[4] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[5] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[6] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0, 2 };
	GPSkillAttributeBStock[7] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[8] = EMPTY_ATTRIBUTE; 
	GPSkillAttributeBStock[9] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[10] = { Allies,0,0,0,0,0,85,0,0,0,0,0,0,0,0,0,0 };// 回复血量
	GPSkillAttributeBStock[11] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0, 2 }; //敌人收到致命的打击
	GPSkillAttributeBStock[12] = { Allies,0,0,0,0,0,90,0,0,0,0,0,0,0,0,0,0 };// 回复血量
	GPSkillAttributeBStock[13] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[14] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[15] = { Enemy, 0, 2, 2, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 }; // 降低魔抗护甲
	GPSkillAttributeBStock[16] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[17] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[18] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[19] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[20] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 120, 0, 0, 0, 0, 0, 0, 2 };
	GPSkillAttributeBStock[21] = { Allies,0,0,0,0,0,100,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeBStock[22] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[23] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 160, 0, 0, 0, 0, 0, 0, 2 };
}
void LoadSkillIncStock()
{
	//这部分全都是永久效果 要小心
	//对敌军时
	//{Enemy，，削减魔抗，削减护甲，(血量上限)，(法力上限)，()，()，削减移速，物理伤害，魔法伤害，削减暴击，削减攻速，(赏金)，(赏经验)，(持续时间)，削减攻击范围}
	//对友军时
	//{Allies，增加魔抗，增加护甲，(血量上限)，(法力上限)，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，(赏金)，(赏经验)，(持续时间)，增加攻击范围}
	GPSkillAttributeIStock[0] = { Enemy,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[1] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[2] = { Allies,0,0,0,0,0,25,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[3] = { Allies,0,0,0,0,0,0,0,0,30,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[4] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[5] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[6] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 55, 0, 0, 0, 0, 0, 0, 0 };
	GPSkillAttributeIStock[7] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[8] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[9] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[10] = { Allies,0,0,0,0,0,30,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[11] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 60, 0, 0, 0, 0, 0, 0, 0 };
	GPSkillAttributeIStock[12] = { Allies,0,0,0,0,0,35,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[13] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[14] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[15] = { Enemy, 0, 1, 1, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 };
	GPSkillAttributeIStock[16] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[17] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[18] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[19] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[20] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0 };
	GPSkillAttributeIStock[21] = { Allies,0,0,0,0,0,40,0,0,0,0,0,0,0,0,0,0 };
	GPSkillAttributeIStock[22] = EMPTY_ATTRIBUTE;
	GPSkillAttributeIStock[23] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 65, 0, 0, 0, 0, 0, 0, 0 };
}
void LoadSkillBuffBaseStock()
{
	//这部分全都是暂时的 但是数值也不要太高～
	
	//buff里的Attribute
	//对敌军时
	//{Enemy，（库编号），削减魔抗，削减护甲，削减血量上限，削减法力上限，削减当前血量，削减当前法力，削减移速，削减物攻，削减魔攻，削减暴击，削减攻速，(赏金)，(赏经验)，持续时间，削减攻击范围}
	//对友军时
	//{Allies，增加魔抗，增加护甲，增加血量上限，增加法力上限，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，(赏金)，(赏经验)，持续时间，增加攻击范围}
	
	//buff里的special
	//对敌军时(一般不会有这个效果)
	//{降低吸血率，降低吸蓝率，降低物理百分比率，降低魔法百分比率}
	//对友军时(这个可以有)
	//{增加吸血率，增加吸蓝率，增加物理百分比率，降低魔法百分比率}
	
	//总的来说   { (剩余持续时间),Attribute,Special,NULL,NULL}
	GPSkillBuffBStock[0] = EMPTY_BUFF;
	GPSkillBuffBStock[1] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,3,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffBStock[2] = EMPTY_BUFF;
	GPSkillBuffBStock[3] = EMPTY_BUFF;
	GPSkillBuffBStock[4] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,4,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffBStock[5] = { 0,EMPTY_ATTRIBUTE,{ 50,0,0,0 },NULL,NULL };
	GPSkillBuffBStock[6]=EMPTY_BUFF;
	GPSkillBuffBStock[7] = { 0,{ Allies,0,0,0,0,0,0,0,0,55,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; // 攻击
	GPSkillBuffBStock[8] = { 0,{ Allies,0,0,0,0,0,0,0,1,0,0,0,0,0,0,4,0 },EMPTY_SPECIAL,NULL,NULL }; //移速
	GPSkillBuffBStock[9] = { 0,{ Allies,0,1,1,0,0,0,0,0,10,5,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; //全方面
	GPSkillBuffBStock[10]= EMPTY_BUFF;
	GPSkillBuffBStock[11]= EMPTY_BUFF;
	GPSkillBuffBStock[12]= EMPTY_BUFF;
	GPSkillBuffBStock[13]={ 0,{ Allies,0,0,0,0,0,0,0,0,60,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; // 攻击力
	GPSkillBuffBStock[14]= { 0,{ Allies,0,2,2,0,0,0,0,0,15,10,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//各方面
	GPSkillBuffBStock[15]= EMPTY_BUFF;
	GPSkillBuffBStock[16]= { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,6,0 },EMPTY_SPECIAL,NULL,NULL };//攻速
	GPSkillBuffBStock[17]= { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,30,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//暴击率
	GPSkillBuffBStock[18]= { 0,{ Allies,0,3,3,0,0,0,0,0,20,15,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//各方面
	GPSkillBuffBStock[19]= { 0,{ Allies,0,0,0,0,0,0,0,0,70,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//攻击力
	GPSkillBuffBStock[20]= EMPTY_BUFF;
	GPSkillBuffBStock[21]= EMPTY_BUFF;
	GPSkillBuffBStock[22]== { 0, { Allies,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,0 }, EMPTY_SPECIAL, NULL, NULL };//移速
	GPSkillBuffBStock[23]= EMPTY_BUFF;
}
void LoadSkillBuffIncStock()
{
	//这部分全都是暂时的 但是数值也不要太高～

	//buff里的Attribute
	//对敌军时
	//{Enemy，削减魔抗，削减护甲，削减血量上限，削减法力上限，削减当前血量，削减当前法力，削减移速，削减物攻，削减魔攻，削减暴击，削减攻速，(赏金)，(赏经验)，持续时间，削减攻击范围}
	//对友军时
	//{Allies，增加魔抗，增加护甲，增加血量上限，增加法力上限，增加当前血量，增加当前法力，增加移速，增加物攻，增加魔攻，增加暴击，增加攻速，(赏金)，(赏经验)，持续时间，增加攻击范围}

	//buff里的special
	//对敌军时(一般不会有这个效果)
	//{降低吸血率，降低吸蓝率，降低物理百分比率，降低魔法百分比率}
	//对友军时(这个可以有)
	//{增加吸血率，增加吸蓝率，增加物理百分比率，降低魔法百分比率}

	//总的来说   { (剩余持续时间),Attribute,Special,NULL,NULL}	
	//非buff技能第一项是 0 是buff  1不是buff
	GPSkillBuffIStock[0] = EMPTY_BUFF;
	GPSkillBuffIStock[1] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[2] = EMPTY_BUFF;
	GPSkillBuffIStock[3] = EMPTY_BUFF;
	GPSkillBuffIStock[4] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[5] = { 0,EMPTY_ATTRIBUTE,EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[6] = EMPTY_BUFF;
	GPSkillBuffIStock[7] = { 0,{ Allies,0,0,0,0,0,0,0,0,10,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[8] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[9] = { 0,{ Allies,0,1,1,0,0,0,0,0,10,5,0,0,0,0,0,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[10] = EMPTY_BUFF;
	GPSkillBuffIStock[11] = EMPTY_BUFF;
	GPSkillBuffIStock[12] = EMPTY_BUFF;
	GPSkillBuffIStock[13] = { 0,{ Allies,0,0,0,0,0,0,0,0,15,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[14] = { 0,{ Allies,0,2,2,0,0,0,0,0,15,10,0,0,0,0,0,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[15] = EMPTY_BUFF;
	GPSkillBuffIStock[16] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[17] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,10,0,0,0,1,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[18] = { 0,{ Allies,0,3,3,0,0,0,0,0,20,15,0,0,0,0,0,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[19] = { 0,{ Allies,0,0,0,0,0,0,0,0,25,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[20] = EMPTY_BUFF;
	GPSkillBuffIStock[21] = EMPTY_BUFF;
	GPSkillBuffIStock[22] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffIStock[23] = EMPTY_BUFF;

}
void LoadSkillStock()
{
	LoadSkillBaseStock();
	LoadSkillIncStock();
	LoadSkillBuffBaseStock();
	LoadSkillBuffIncStock();
	for (int i = 1; i <= GP_STOCK * MAX_HERO_SKILL_NUM; i++)
	{
		GPSkillStock[i].StockNumber = i;
		GPSkillStock[i].index = (i - 1) % MAX_HERO_SKILL_NUM;
		GPSkillStock[i].SetSkill(GPSkillAttributeBStock[i], GPSkillAttributeIStock[i], GPSkillBuffBStock[i], GPSkillBuffIStock[i]);
		GPSkillStock[i].Owner = Heros[(i - 1) / MAX_HERO_SKILL_NUM + 1];
		GPSkillStock[i].JustFlushed = false;
		GPSkillStock[i].LastCD = 0;
	}
	for (int i = 1; i <= AI_STOCK * MAX_MONSTER_SKILL_NUM; i++)
	{
		AISkillStock[i].StockNumber = i;
		AISkillStock[i].index = (i - 1) % MAX_MONSTER_SKILL_NUM;
		AISkillStock[i].SetSkill(AISkillAttributeBStock[i], AISkillAttributeIStock[i], AISkillBuffBStock[i], AISkillBuffIStock[i]);
		AISkillStock[i].Owner = Monsters[(i - 1) / MAX_MONSTER_SKILL_NUM + 1];
		AISkillStock[i].JustFlushed = false;
		AISkillStock[i].LastCD = 0;
	}

	GPSkillStock[0].name = "跑步";
	GPSkillStock[0].CD = 10;
	GPSkillStock[0].EnergyConsume = 20;

	GPSkillStock[1].name = "突然上头";
	GPSkillStock[1].CD = 15;
	GPSkillStock[1].EnergyConsume = 20;

	GPSkillStock[2].name = "吃鸡排";
	GPSkillStock[2].CD = 20;
	GPSkillStock[2].EnergyConsume = 5;

	GPSkillStock[3].name = "锻炼身体";
	GPSkillStock[3].CD = 15;
	GPSkillStock[3].EnergyConsume = 20;

	GPSkillStock[4].name = "自嗨";
	GPSkillStock[4].CD = 25;
	GPSkillStock[4].EnergyConsume = 30;

	GPSkillStock[5].name = "帮找Bug";
	GPSkillStock[5].CD = 20;
	GPSkillStock[5].EnergyConsume = 30;

	GPSkillStock[6].name = "化妆";
	GPSkillStock[6].CD = 10;
	GPSkillStock[6].EnergyConsume = 20;

	GPSkillStock[7].name = "志我奋斗";
	GPSkillStock[7].CD = 15;
	GPSkillStock[7].EnergyConsume = 25;

	GPSkillStock[8].name = "拖鞋的加成";
	GPSkillStock[8].CD = 15;
	GPSkillStock[8].EnergyConsume = 25;

	GPSkillStock[9].name = "人生的经验";
	GPSkillStock[9].CD = 20;
	GPSkillStock[9].EnergyConsume = 25;

	GPSkillStock[10].name = "不是谦虚";
	GPSkillStock[10].CD = 20;
	GPSkillStock[10].EnergyConsume = 20;

	GPSkillStock[11].name = "无可奉告";
	GPSkillStock[11].CD = 25;
	GPSkillStock[11].EnergyConsume = 30;

	GPSkillStock[12].name = "背心的加成";
	GPSkillStock[12].CD = 20;
	GPSkillStock[12].EnergyConsume = 20;

	GPSkillStock[13].name = "长者的教诲";
	GPSkillStock[13].CD = 20;
	GPSkillStock[13].EnergyConsume = 30;

	GPSkillStock[14].name = "历史的钦定";
	GPSkillStock[14].CD = 20;
	GPSkillStock[14].EnergyConsume = 30;

	GPSkillStock[15].name = "另请高明";
	GPSkillStock[15].CD = 20;
	GPSkillStock[15].EnergyConsume = 25;

	GPSkillStock[16].name = "见的多了";
	GPSkillStock[16].CD = 20;
	GPSkillStock[16].EnergyConsume = 25;

	GPSkillStock[17].name = "一颗赛艇";
	GPSkillStock[17].CD = 20;
	GPSkillStock[17].EnergyConsume = 25;

	GPSkillStock[18].name = "实习";
	GPSkillStock[18].CD = 15;
	GPSkillStock[18].EnergyConsume = 25;

	GPSkillStock[19].name = "历史进程";
	GPSkillStock[19].CD = 20;
	GPSkillStock[19].EnergyConsume = 25;

	GPSkillStock[20].name = "谈笑风生";
	GPSkillStock[20].CD = 20;
	GPSkillStock[20].EnergyConsume = 20;

	GPSkillStock[21].name = "身经百战";
	GPSkillStock[21].CD = 20;
	GPSkillStock[21].EnergyConsume = 30;

	GPSkillStock[22].name = "图样图森破";
	GPSkillStock[22].CD = 20;
	GPSkillStock[22].EnergyConsume = 30;

	GPSkillStock[23].name = "拿衣服";
	GPSkillStock[23].CD = 30;
	GPSkillStock[23].EnergyConsume = 30;
}

void LoadHeroStock()
{
	LoadHeroApperance();//加载英雄颜色
	LoadHeroName();//加载英雄名字
	LoadHeroSound();//加载英雄音效
	LoadSkillStock();//加载英雄技能
					 //加载各个库
	LoadHeroBaseAtttibuteStock();
	LoadHeroIncAtttibuteStock();
	LoadHeroBaseSpecialStock();
	LoadHeroIncSpecialStock();

	//英雄设置
	for (int i = 1; i <= GP_STOCK; i++)//GP设置
	{
		HeroStock[i].LoadReuseAttribute();//设置通用属性
		HeroStock[i].LoadBIAttribute(GPBAttributeStock[i], GPIAtrributeStock[i]);//设置基础属性和增长值
		HeroStock[i].LoadBISpecial(GPBSpecialStock[i], GPISpecialStock[i]);//设置基础和增长special
		for (int j = 0; j < MAX_HERO_SKILL_NUM; j++)//获得技能
			HeroStock[i].Skills[j] = &GPSkillStock[(i - 1)*MAX_HERO_SKILL_NUM + j + 1];
	}
	for (int i = 1; i <= AI_STOCK; i++)//AI设置
	{
		MonsterStock[i].LoadReuseAttribute();//设置通用属性
		MonsterStock[i].LoadBIAttribute(AIBAttributeStock[i], AIIAttributeStock[i]);//设置基础属性和增长值
		MonsterStock[i].LoadBISpecial(AIBSpecialStock[i], AIISpecialStock[i]);//设置基础和增长special
		for (int j = 0; j < MAX_MONSTER_SKILL_NUM; j++)//获得技能
			MonsterStock->Skills[j] = &GPSkillStock[(i - 1)*MAX_MONSTER_SKILL_NUM + j + 1];
	}
}
void LoadBackgroundSound()
{
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayBackgroundSound, NULL, 0, NULL));
}
void LoadTimer()
{
	HANDLE TmpHandle = (HANDLE)_beginthreadex(NULL, 0, Timer, NULL, 0, NULL);
	SetThreadPriority(TmpHandle, THREAD_PRIORITY_ABOVE_NORMAL);
	CloseHandle(TmpHandle);
}
void LoadEquipmentStock()
{
	//以下为六个装备的属性
	/*
	1、峰哥的指甲刀  （增加50点攻击力  100 块）
	2、峰哥的订书机   （降低0.5攻速 不要钱）
	3、Eul的神圣法杖 （增加移动速度 1  100块）
	4、Guinsoo的邪恶镰刀 （增加自身最大血量200 最大能量100  100块 ）
	5、斯嘉蒂之眼 （增加攻击速度0.5 120块）
	6、梅塞斯密特的掠夺 （增加暴击30 60块 ）
	*/
	EquipmentStock[0].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,50,0,0,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "锋哥的指甲刀");
	EquipmentStock[0].StockNumber = 0;
	EquipmentStock[1].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,0,0,0,-0.5,0,0,0,0 }),new Special({ 0,0,0,0 }) }, "锋哥的订书机");
	EquipmentStock[1].StockNumber = 1;
	EquipmentStock[2].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,1,0,0,0,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "拖鞋");
	EquipmentStock[2].StockNumber = 2;
	EquipmentStock[3].Set({ new Attribute({ Allies,0,0,0,200,100,200,100,0,0,0,0,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "加厚的班服");
	EquipmentStock[3].StockNumber = 3;
	EquipmentStock[4].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "吹风机");
	EquipmentStock[4].StockNumber = 4;
	EquipmentStock[5].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,0,0,30,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "锋哥的杠铃");
	EquipmentStock[5].StockNumber = 5;

}
void LoadConsumableStock()
{
	// 以下为六个消耗品的属性
	/*
	1、烤奶 所有友军每秒回复血量20点 持续5s（20块）
	2、肾宝 每秒恢复能量20点 持续5s（30块）
	3、好吃的奇异果 瞬间恢复能量80点 （30块）
	4、维C柠檬茶 瞬间恢复血量80点 能量60点（40块）
	5、咖啡 增加自身攻击速度0.5 持续10s （50块）
	6、电脑配件 增加自身攻击力50点 持续10s （40块）
	*/
	ConsumableStock[0].SetConsumable(true, new Buff({ 5,{ Allies,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "烤奶");
	ConsumableStock[0].StockNumber = 0;
	ConsumableStock[1].SetConsumable(true, new Buff({ 5, { Allies,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "肾宝");
	ConsumableStock[1].StockNumber = 1;
	ConsumableStock[2].SetConsumable(false, new Buff({ 0, { Allies,0,0,0,0,0,0,80,0,0,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "好吃的奇异果");
	ConsumableStock[2].StockNumber = 2;
	ConsumableStock[3].SetConsumable(false, new Buff({ 0, { Allies,0,0,0,0,0,80,60,0,0,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "维C柠檬茶");
	ConsumableStock[3].StockNumber = 3;
	ConsumableStock[4].SetConsumable(false, new Buff({ 10, { Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "咖啡");
	ConsumableStock[4].StockNumber = 4;
	ConsumableStock[5].SetConsumable(false, new Buff({ 10, { Allies,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "电脑配件");
	ConsumableStock[5].StockNumber = 5;
}
void LoadCitadel()
{
	GPHero* Citadel = &HeroStock[0];
	Heros[0] = Citadel;//增添记录
	Citadel->number = 0;//设置编号
	Citadel->camp = Allies;//设置阵营
	for (short y = BATTLE_HEIGHT / 2 - 1; y <= BATTLE_HEIGHT / 2 + 1; y++)//设置主城处的砖块信息
	{
		FillConsoleOutputAttribute(hOut, CitadelColor, 3, { BATTLE_WIDTH / 2 - 1,y }, &num);//涂抹主城的颜色
		for (short x = BATTLE_WIDTH / 2 - 1; x <= BATTLE_WIDTH / 2 + 1; x++)//设置砖块信息
		{
			Active[x][y].Occupied = true;
			Active[x][y].UnitCamp = Empty;
			Active[x][y].OccupyingUnit = Citadel;
		}
	}
	AttackMsg[0] = CreateEvent(NULL, true, false, NULL);//初始即可检测攻击
	BuffMsg[Allies][0] = CreateEvent(NULL, true, false, NULL);//初始无buff
	SkillCDMsg[Allies][0] = CreateEvent(NULL, true, false, NULL);//初始无技能处于CD
	MoveMsg[0] = CreateEvent(NULL, true, false, NULL);//初始未移动
	ChaseMsg[0] = CreateEvent(NULL, true, false, NULL);//初始未追逐
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, LoadHero, (void*)Citadel, 0, NULL));//为英雄创建线程 投入使用
	CurSelectedHero = Citadel;
	Shop = Citadel;
	CurSelectedHero->GetSelected();
	
	
}
void LoadDivider()
{
	FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, BATTLE_WIDTH, { 0,BATTLE_AREA }, &num);//加载战场与非战场的分界线
	FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, BATTLE_WIDTH - INFO_FUNCTION, { INFO_FUNCTION,BATTLE_AREA + THING_HEIGHT_CHAR + 1 }, &num);//加载上下物品区分界线

	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
	{
		for (short x = INFO_FUNCTION; x < SCREEN_WIDTH; x += 11)
			FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, 1, { x,y }, &num);//加载功能区竖直分界线
		FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, 1, { IMAGE_INFO,y }, &num);
	}
}
void ShowMainMenu()
{

}
void InitialWindow()
{
	//获取各种句柄
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle("魔兽进化史");
	hwnd = FindWindow(NULL, "魔兽进化史");
	hdc = GetDC(hwnd);
	hmendc = CreateCompatibleDC(hdc);
	hBlackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//hmutex[camp][number] = CreateMutex(NULL, false, NULL);

	//初始化屏幕信息
	GetConsoleScreenBufferInfo(hOut, &csbi);//获得屏幕信息
	GetConsoleMode(hIn, &OldConsoleInputMode);//获取原始输入模式
	NewConsoleInputMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | OldConsoleInputMode;//在原基础上增添接受鼠标输入
	SetConsoleMode(hIn, NewConsoleInputMode);//设置新的输入模式
	


	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, NULL);//设置全屏
	GetConsoleCursorInfo(hOut, &cursorInfo);//获得原始光标信息
	cursorInfo.bVisible = false;//仅将光标
	SetConsoleCursorInfo(hOut, &cursorInfo);//设为不可见
}
void InitialGame()
{
	//初始化有限状态机
	FMState = new FormalState;
	SMState = new SkillingState;
	TMState = new TransportingState;
	PMState = new ShoppingState;
	CurMOPState = PMState;
	TmpMOPState = PMState;

	//初始化小量
	isShowingHero = true;
	CurNum[Allies] = 0;
	CurNum[Enemy] = 0;
	money = 5000;
	CurHeroPrice = 0;
	
	//初始化信号量 互斥量
	Fighting = CreateEvent(NULL, true, false, NULL);
	EndFighting = CreateEvent(NULL, true, true, NULL);
	PRINTF_MUTEX = CreateMutex(NULL, false, NULL);

	//加载背景音乐
	LoadBackgroundSound();
	//加载装备库
	LoadEquipmentStock();
	//加载消耗品库
	LoadConsumableStock();
	//加载英雄库
	LoadHeroStock();
	//加载分界条
	LoadDivider();
	//加载大本营 商店 也是0号英雄
	LoadCitadel();
	//加载游戏轮数计时器
	LoadTimer();
	
}
