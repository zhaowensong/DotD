#include"Base(FSM).h"
#include<iostream>


//*********************************************************************************************
//********************************�����ǳ���***************************************************
//*********************************************************************************************
const short SCREEN_WIDTH=213;//��Ļ�����ַ����
const short SCREEN_HEIGHT=60;//��Ļ�����ַ����
const short BATTLE_WIDTH = 213;//ս�������ַ����
const short BATTLE_HEIGHT = 48;//ս�������ַ����
const int MAX_INPUT_RECORD = 10;//����ͬʱ���ܵ�������������
const short BATTLE_AREA = 48;//����������ʾ���ķֽ���
const short IMAGE_INFO = 55;//ͷ��������Ϣ���ķֽ���
const short INFO_FUNCTION = 113; //��Ϣ���빦�����ķֽ���
const int MAX_MONSTER_NUM = 3;//��󸨵�Ա����
const int MAX_HERO_NUM=5;//���Ӣ������
const int PIX_PER_WIDTH = 9;//һ���ַ���ռ������
const int PIX_PER_HEIGHT = 18;//һ���ַ���ռ������
const short IMAGE_WIDTH_CHAR=30;//ͷ�������(�ַ���)
const short IMAGE_HEIGHT_CHAR=11;//ͷ�����߶�(�ַ���)
const int IMAGE_LEFT = 0;//ͷ�������Ե������X����
const int IMAGE_TOP = PIX_PER_HEIGHT * IMAGE_WIDTH_CHAR;//ͷ�����ұ�Ե������X����
const int IMAGE_WIDTH_PIX = PIX_PER_WIDTH * IMAGE_WIDTH_CHAR;//ͷ�������(���ؼ�)
const int IMAGE_HEIGHT_PIX = PIX_PER_HEIGHT * IMAGE_HEIGHT_CHAR;//ͷ�����߶�(���ؼ�)
const int THING_WIDTH_CHAR = 10;//���������(�ַ���)
const short THING_HEIGHT_CHAR = 5;//�������߶�(�ַ���)
const int THING_WIDTH_PIX = PIX_PER_WIDTH * THING_WIDTH_CHAR;//���������(���ؼ�)
const int THING_HEIGHT_PIX = PIX_PER_HEIGHT * THING_HEIGHT_CHAR;//�������߶�(���ؼ�)
const int MAX_THING_NUM = 6;//�����е�(ǿ����/����Ʒ/װ��/�ҷ�Ӣ�ۼ���)����
const int MAX_MONSTER_SKILL_NUM = 3;//����Ա�����еļ�������
const DWORD DIVIDER_COLOR = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY;//�ָ�����ɫ
const char SKILL_CHAR = '#';//��������ַ�
const char ATTACK_CHAR = '#';//��������ַ�
const int EQUIPMENT_STOCK = 6;//װ��������
const int CONSUMABLE_STOCK = 6;//����Ʒ������
const int ENHANCEBOOK_STOCK = 6;//ǿ����������
const int SKILL_STOCK = 60;//����
const int GP_STOCK = 5;//Ӣ��������
const int AI_STOCK = 3;//����Ա������
const int SELL_RATE = 6;//�ۼ���
const int INTERVAL = 10;//�������ֵ���Ϸʱ����
const int INC_HERO_EXPERICAL=500;//������������ֵ
const int INC_HERO_PRICE=1000;//Ӣ�ۼ۸�����ֵ
const int SecondMonsterTurnUp=10;//�ڶ�������Ա���ֵ�����
const int ThirdMonsterTurnUp=30;//����������Ա���ֵ�����
const int RoundsToGetMoreOneEqipment=8;//�����ָ���Ա�õ�һ���µ�װ��
const int TestTime=1000;//��⹥����ʱ�䳤��/�����
const int AI_STATE_NUM = 4;
const Attribute EMPTY_ATTRIBUTE = {Allies,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const Special EMPTY_SPECIAL = {0,0,0,0};
const Buff EMPTY_BUFF = { 1,EMPTY_ATTRIBUTE ,EMPTY_SPECIAL ,NULL,NULL };
const short ImageMidium = 27;//ͷ����з���
const short EyeHeight = BATTLE_AREA + 4;//�۾���y����
const short EyeDistance = 5;//���ۺ��з��ߵļ��
const short MouthHeight = SCREEN_HEIGHT-2;//���y����
const short NoseHeight = (EyeHeight + MouthHeight) / 2 - 1;//����y����
const short MouthWidth = 5;//��Ͱ���
const short EyebrowHeight = EyeHeight - 2;//üëy����
const COORD HERO_INITIAL_LOC = { 100,20 };//Ӣ�۳�ʼ����λ��
const COORD CITADEL = { 100,20 };//����λ��
const DWORD TearColor = BACKGROUND_BLUE | BACKGROUND_INTENSITY;//�������ɫ
const DWORD MoneyColor = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;//Ǯ����ɫ
const DWORD DefaultColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;//Ĭ����ɫ
const DWORD BloodColor = FOREGROUND_RED | FOREGROUND_INTENSITY;//Ѫ�� ����͵ȡ��ɫ
const DWORD EnergyColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;//���� ������ȡ��ɫ
const DWORD PaColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;//��������ɫ
const DWORD MaColor = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;//��ǿ��ɫ
const DWORD PdColor = MoneyColor;//������ɫ
const DWORD MdColor = FOREGROUND_BLUE | FOREGROUND_RED;//ħ����ɫ
const DWORD SpeedColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;//�ٶ���ɫ
const DWORD CrColor = FOREGROUND_RED;//��������ɫ
const DWORD CitadelColor = BACKGROUND_RED | BACKGROUND_INTENSITY;//������ɫ
const DWORD Illidan_Stormrage = BACKGROUND_BLUE;//��������ŭ��
const DWORD Cairne_Bloodhoof = BACKGROUND_RED|BACKGROUND_GREEN;
const DWORD Tyrande_Whisperwind = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
const DWORD Grom_Hellscream = BACKGROUND_BLUE | BACKGROUND_RED;
const DWORD Uther = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED| BACKGROUND_INTENSITY;
const DWORD SKILL_COLOR = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;//����������ɫ
const DWORD EQUIPMENT_COLOR = FOREGROUND_GREEN | FOREGROUND_INTENSITY;//װ��������ɫ
const DWORD CONSUMABLE_COLOR= FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY;//����Ʒ��ɫ
const DWORD GAME_INFO = SKILL_COLOR;//��Ϸ��Ϣ��ɫ
#define AIStill 0
#define AIPosChase 1
#define AINegChase 2
#define AI_STATE_NUM 3






//*********************************************************************************************
//******************************������API����**************************************************
//*********************************************************************************************
CONSOLE_SCREEN_BUFFER_INFO csbi;//����̨��������Ϣ
HWND hwnd;//���ھ��
HDC hdc;//�豸�������
HDC hmendc;//���ݵ��豸�������
HBRUSH hBlackBrush;//��ɫ�Ļ�ˢ
HANDLE hOut, hIn;//��׼����������
CONSOLE_CURSOR_INFO cursorInfo;//�����Ϣ
BRICK_INFO Active[BATTLE_WIDTH][BATTLE_HEIGHT];//��¼�������ӵĻ��Ϣ��ȡ����Ϊx ����Ϊy
INPUT_RECORD Inputs[MAX_INPUT_RECORD];//�����¼�����
bool LeftButtonPressed;//�������Ƿ���
int CurScreen;//��ǰ�����Ļ��
DWORD InputOneTime;//���ζ�ȡ�������¼���
DWORD OldConsoleInputMode, NewConsoleInputMode;//����ģʽ
COORD LastMousePos;//��¼�ϴ����λ��
DWORD num;//��Ϊһ���������� ������ʹ�� ֻ��Ϊ�����ʵ��



//*********************************************************************************************
//*******************************��������Ϸ�ڲ�����********************************************
//*********************************************************************************************
MouseOperateState* CurMOPState;
MouseOperateState* TmpMOPState;
FormalState* FMState;
SkillingState* SMState;
TransportingState* TMState;
ShoppingState* PMState;
atomic_bool isShowingDetail;//�Ƿ�����ʾ��Ʒ��ϸ��Ϣ
atomic_bool isShowingHero;//�Ƿ�����ʾӢ����Ϣ
TYPE TransportedType;//����ת�Ƶ���Ʒ������
COORD RelativeLoc;//����ƶ�ʱ���������
Skill* CurTriggeredSkill;//��ǰ�����ͷŵļ���
short TmpSkillRange;//�ͷż��ܵķ�Χ
int money;//��ǰ�Ľ�Ǯ
int CurHeroPrice;//��ǰ����Ӣ�������Ǯ
GPHero* Heros[MAX_HERO_NUM+1];//Ӣ������
AIHero* Monsters[MAX_MONSTER_NUM + 1];//����Ա����
GPHero* Shop;//�ر�ָ���̵�
GPHero* Gotta;//������
atomic_int CurNum[MAX_CAMP_NUM];//Ӣ���������������
HANDLE AttackMsg[MAX_MONSTER_NUM + 1];//Ӣ�������Ŀɹ����ź�
HANDLE BuffMsg[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//��buff���ź�
HANDLE SkillCDMsg[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//Ӣ�ۼ���CD�ź�
HANDLE MoveMsg[MAX_MONSTER_NUM + 1];//Ӣ���ƶ����ź�
HANDLE ChaseMsg[MAX_MONSTER_NUM + 1];//Ӣ��׷�ٵ��ź�
HANDLE hmutex[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//Ӣ����
AIState* AIStates[AI_STOCK + 1][AI_STATE_NUM];//
HANDLE EndFighting;//һ�ν����������ź�
HANDLE Fighting;//��һ�ν�����ʼ���ź�
HANDLE PRINTF_MUTEX;//����� ��֤ͬʱֻ��һ���ı������
Hero* CurSelectedHero;//��ǰѡ����Ӣ��
MinHeap* Open[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//�����б�
Aector* Close[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//�ر��б�
Astar* PathBegin[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//·�����
Astar* NextLoc[MAX_CAMP_NUM][MAX_MONSTER_NUM + 1];//��һ��λ��
atomic_int CurTransportedEquipIndex;//��ǰ����ת�Ƶ�װ��������
atomic_int CurTransportedThingIndex;//��ǰ����ת�Ƶ�����Ʒ������
int LastShownType = -1;
int LastShownIndex = -1;
int Round=0;//��Ϸ����
int IntervalLastTime = 0;//���ʣ��ʱ��
int CurMonsterNum;//��ǰ����Ա���� Ϊ0ʱ������һ��

							 

//********************************************************************************************************
//**************************************��������Ϸ��Ӣ�� ���� װ�� ����Ʒ����������***********************
//********************************************************************************************************
GPHero HeroStock[GP_STOCK + 1];//GPӢ��
AIHero MonsterStock[AI_STOCK + 1];//AIӢ��
DWORD GPApperanceStock[GP_STOCK + 1];//GPӢ����ɫ
string GPNameStock[GP_STOCK + 1];//GPӢ������
string AINameStock[AI_STOCK + 1];//AIӢ������
Attribute GPBAttributeStock[GP_STOCK+1];//GPӢ�ۻ�������
Attribute GPIAtrributeStock[GP_STOCK+1];//GPӢ����������
Attribute AIBAttributeStock[AI_STOCK+1];//AIӢ�ۻ�������
Attribute AIIAttributeStock[AI_STOCK+1];//AIӢ�ۻ�������
Special GPBSpecialStock[GP_STOCK + 1];//GPӢ�ۻ���special
Special GPISpecialStock[GP_STOCK + 1];//GPӢ������special
Special AIBSpecialStock[AI_STOCK + 1];//AIӢ�ۻ���special
Special AIISpecialStock[AI_STOCK + 1];//AIӢ�ۻ���special

Skill GPSkillStock[GP_STOCK*MAX_HERO_SKILL_NUM+1];//GPӢ�ۼ���
Skill AISkillStock[AI_STOCK*MAX_MONSTER_SKILL_NUM+1];//AIӢ�ۼ���
Attribute GPSkillAttributeBStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GPӢ�ۼ��ܻ�������
Attribute GPSkillAttributeIStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GPӢ�ۼ�����������
Attribute AISkillAttributeBStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AIӢ�ۼ��ܻ�������
Attribute AISkillAttributeIStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AIӢ�ۼ�����������
Buff GPSkillBuffBStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP����Buff��������
Buff GPSkillBuffIStock[GP_STOCK*MAX_HERO_SKILL_NUM + 1];//GP����Buff��������
Buff AISkillBuffBStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI����Buff��������
Buff AISkillBuffIStock[AI_STOCK*MAX_MONSTER_SKILL_NUM + 1];//AI����Buff��������

Equipment EquipmentStock[EQUIPMENT_STOCK];
Consumable ConsumableStock[CONSUMABLE_STOCK];
Consumable EnhanceBookStock[ENHANCEBOOK_STOCK];





//*********************************************************************************************
//***************************************������һЩȫ�ֺ����Ķ���******************************
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
	Body.Frequence = ((Body.Frequence - Effection.Frequence) >= 0) ? Body.Frequence - Effection.Frequence : 0.01;//������Ͳ���Ϊ�� �����������
	Body.CrRate = ((Body.CrRate - Effection.CrRate) >= 0) ? Body.CrRate - Effection.CrRate : 0;
	return Body;
}
Attribute operator+(const Attribute& Effection1, const Attribute& Effection2)
{
	//�ƺ�һ��+��ֻ������Ч������ ��ô��û���������ֵ��ôһ˵��  ������һ��Ҳ�Ͳ��ù���
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
	printf("������ã�%d��\n���븨��Ա���ǣ��´������ޣ�%2ds", Round, IntervalLastTime);
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
	//  ����   TM����
}

unsigned WINAPI LoadHero(LPVOID lpParameter)//����һ����Ӣ�۵�����
{
	Hero* Object = (Hero*)lpParameter;
	Object->Operating();
	return 0;
}
unsigned WINAPI LoadMonster(LPVOID lpParameter)//����һ���¹��������
{
	Monsters[*((int*)lpParameter)]->Operating();
	return 0;
}
unsigned WINAPI UpdateBuff(LPVOID lpParameter)
{
	Hero* Object = (Hero*)lpParameter;
	int curbuff = 0;//��¼���θ��µ�buff�� �Ա㷢��û��buffʱ��ʱ�������߳�
	while (!Object->dead)
	{
		WaitForSingleObject(BuffMsg[Object->camp][Object->number], INFINITE);//�ȴ���buff
		WaitForSingleObject(hmutex[Object->camp][Object->number], INFINITE);//����
		curbuff = 0;
		for (auto tmp = Object->Head->Next; tmp != Object->Rear; tmp = tmp->Next)
		{
			curbuff++;
			if (tmp->TimeLeft <= 0)
			{
				Object->special -= tmp->special;//��ȥ���ṩ���ǲ�������Ч��
				Object->uAttribute -= tmp->Effection;//��ȥ��ʱ�Ļ��� �ȵȼӳ�
				tmp->Prev->Next = tmp->Next;//���½ڵ�
				tmp->Next->Prev = tmp->Prev;//��ɾȥ��ǰ�ڵ�
				delete tmp;
			}
			else 
			{
				tmp->TimeLeft--;//ʣ��ʱ��-1
				Object->GetSlowRecovery(tmp->Effection);//���»����Ļ�Ѫ����
			}
		}
		if (!curbuff)//�����������η���û��buff��  ��ô�����¼���������
			ResetEvent(BuffMsg[Object->camp][Object->number]);
		ReleaseMutex(hmutex[Object->camp][Object->number]);//����
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
		SkillRecords[i] = Object->Skills[i];//�������ܵĸ���
		SkillRecords[i]->JustFlushed = false;
	}
	int curskill = 0;//��¼���θ��µļ����� �Ա㷢��û�м�����Ҫˢ��ʱ��ʱ�������߳�
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
		SkillRecords[i] = Object->Skills[i];//�������ܵĸ���
		SkillRecords[i]->JustFlushed = false;
	}
	int curskill = 0;//��¼���θ��µļ����� �Ա㷢��û�м�����Ҫˢ��ʱ��ʱ�������߳�
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
	COORD LastDestination;//��¼��һ���ƶ���Ŀ�ĵ�
	while (1) 
	{
		if (Object->dead)
			return 0;
		WaitForSingleObject(MoveMsg[Object->number], INFINITE);//�ȴ��ƶ�ָ��
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
					if (dx <= 1 && dy <= 1)//����λ������λ��ʱ����ֹͣ
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
				NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;//�ҵ���һ����λ��
			if (Active[NextLoc[Object->camp][Object->number]->Loc.X][NextLoc[Object->camp][Object->number]->Loc.Y].Occupied || LastDestination != Object->Destination)//�������λ�ñ�ռ���˻���Ŀ�ĵر����
			{
				if (Object->FindPath())//��ʼ����·��  ����ҵ���
				{
					for (int i = 0; i < Object->uAttribute.Speed; i++)//����һ����λ��
						NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;
					if (LastDestination != Object->Destination)//�������ΪĿ�ĵر�� ��ô������һ�ε�Ŀ�ĵ�Ϊ�µ����Ŀ�ĵ�
						LastDestination = Object->Destination;
				}
				else
					break;//�Ҳ���·����ֹͣ
			}
			Object->Jmp(NextLoc[Object->camp][Object->number]->Loc);//�ƶ����Ǹ�λ��
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
		Object->Destination = Object->HeroToChase->KerLoc;//����׷��Ŀ��
		SetEvent(MoveMsg[Object->number]);//�����ƶ��ź�
		ResetEvent(AttackMsg[Object->number]);//ȡ�������ź�
		Sleep(100);//ÿ��һ��ʱ�����һ�θ���Ŀ�ĵ�
	}
}
unsigned WINAPI Timer(LPVOID lpParameter)
{
	SYSTEMTIME LastSecond;
	SYSTEMTIME CurSecond;
	while (1)
	{
		WaitForSingleObject(EndFighting, INFINITE);
		IntervalLastTime = INTERVAL;//���ü��ʱ��
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
	int MonsterNum;//һ���и���Ա���ֵĸ���
	int EquipmentNum;//����Ա��װ����
	while (1)
	{
		WaitForSingleObject(Fighting, INFINITE);
		//���ó��ֵĸ���Ա����
		if (Round >= ThirdMonsterTurnUp)
			MonsterNum = 3;
		else if (Round >= SecondMonsterTurnUp)
			MonsterNum = 2;
		else
			MonsterNum = 1;

		//�Ը�������Ա���г�ʼ��
		for (int i = 1; i <= MonsterNum; i++)
		{
			//��ʼ������Ա����
			Monsters[i] = &MonsterStock[i];
			CloseHandle((HANDLE)_beginthreadex(NULL, 0, LoadHero, (void*)Monsters[i], 0, NULL));//��������Ա�߳�
		}
		ResetEvent(EndFighting);
		WaitForSingleObject(EndFighting,INFINITE);
	}
}

void BuyHero(int HeroNumber)
{
	if (money >=CurHeroPrice)//������㹻��Ǯ
	{
		for (int i = 1; i <= CurNum[Allies]; i++)
			if (Heros[i]->StockNumber == HeroNumber)
				return;//�Ѿ������Ӣ���� �Ͳ���������
		money -= CurHeroPrice;//��Ǯ
		CurHeroPrice += INC_HERO_PRICE;//���¼۸�
		//��Ӣ�ۼ���
		Heros[CurNum[Allies]+1] = &HeroStock[HeroNumber];
		//Ͷ��ʹ��
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, LoadHero, (void*)Heros[CurNum[Allies] + 1], 0, NULL));//ΪӢ�۴����߳� Ͷ��ʹ��
	}
}
void EraseThing(TYPE T, int index)//T������SKILL CONSUMBALE EQUIPMENT index��Χ0-5
{
	int left = (SCREEN_WIDTH - (3 * (3 - T) - index % 3)*(1 + THING_WIDTH_CHAR))*PIX_PER_WIDTH;//���������
	int top = (SCREEN_HEIGHT - (2 - index / 3)*(1 + THING_HEIGHT_CHAR) + 1)*PIX_PER_HEIGHT;//����ϱ����
	SelectObject(hdc, hBlackBrush);
	Rectangle(hdc, left, top, left + THING_WIDTH_PIX, top + THING_HEIGHT_PIX);//Ĩ��
}
void BeginTransportOrUpSkill(COORD Destination)
{
	GPHero* Tmp;
	if (Tmp=dynamic_cast<GPHero*>(CurSelectedHero))
	{
		if ((Destination.X % (THING_WIDTH_CHAR + 1) == 0) || (Destination.Y % (THING_HEIGHT_CHAR + 1) == 0))//���ڷֽ�������Ч
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//��Χ��0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//��Χ��0-1
		int Ftype = xIndex / 3;//��Χ��0-2 �ֱ�ָ���� ����Ʒ ��װ�� //���̵���˵�ֱ�ָǿ���� ����Ʒ ��װ��
		int RealIndex = yIndex * 3 + xIndex % 3;//������Χ��0-5
		switch (Ftype)
		{
		case 0://����������������
		{
			if (Tmp->LeftSkillPoint > 0)//����м��ܵ�
			{
				Tmp->LeftSkillPoint--;//���ܵ�-1
				Tmp->Skills[RealIndex]->LevelUp();//��������
			}
		}
			return;
		break;
		case 1://����Ʒ��
		{
			TransportedType = CONSUMABLE;
			CurTransportedThingIndex = RealIndex;
			TmpMOPState = TMState;
		}
			break;
		case 2://װ����
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
//**************************************�������ຯ������***************************************
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
	SetConsoleCursorPosition(hOut, { 0,BATTLE_AREA + 1 });//��λ���
	SetConsoleTextAttribute(hOut, DefaultColor);
	switch (FTYPE)
	{
	case 0://����
	{
		if (CurSelectedHero->Skills[REALINDEX])
		{
			switch (CurSelectedHero->Skills[REALINDEX]->StockNumber)
			{
			case 0://
			{
				/*�Կ���Ѫ����������ܵ�����
				0��Ѫ���̤
				����Ѫ�㿪ʼ�ܲ�����С���ܵ����ˣ�ֱ����������˺� ����ʼ�˺�100  ����ÿ��һ������50�˺���
				1�������⻷
				����Ѫ���뵽����û�Σ�ͻȻ��ͷ�����������˴�ң����ӹ����ٶ�  �������Ѿ����ӹ����ٶ�0.5 ��ʼ����3s  ÿ��һ������1s ��
				2����Ȼ����
				����Ѫ��ͻȻ���úܶ�������һ�鼦�ţ����ϻ��˺ܶ�Ѫ  ����ʼ�ָ�����75��Ѫ�� ÿ��һ������25 ��������
				3������֮��
				����Ѫ���±�ɷ�լ�����ǿ�ʼ�������壬ɱ���������˺ܶ� ����ʼ��������50�㹥���� ����ÿ��һ������30�㣩
				4��ŭ����
				����Ѫ�㷢�ֽ��������Ӹ����ܸ��ˣ������������� �������������ٶ� 0.5  ����7s ÿ��һ��������2s��
				5�����ȼ���
				����Ѫ�㿪ʼ��ͬѧ��Bug���ⲻ��������������˺�����ʹ���ܿ��֣�Խ��Խ���񣨹��������ѪЧ�� �ָ�����������˺���50%  ����5s ÿ��һ������2s��
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
	case 1://����Ʒ
	{
		GPHero* Tmp;
		if ((Tmp = dynamic_cast<GPHero*>(CurSelectedHero)) && Tmp->Consumables[REALINDEX])//������λ��������Ʒ
		{
			switch (Tmp->Consumables[REALINDEX]->StockNumber)
			{
			case 0://����
			{
				printf("����ʱ��Ĭ���ԣ���Ը��չʾ�Լ��������������̾�����Ҫ��\n����֤�����𣿡���Ȼ������ȴһֱ����������ѵʱ�Ĺ�ΰ��\n����˵ֻ�Ǵ�˵�������Ҹ߹���̺���ô���ԭ����Ϊ�飡��\n��ȷ�����Ƕ�������˼�ص��ͷ���·�ȷ��һ�㡣");
			}
			break;
			case 1://����
			{
				printf("��֪���ĳ�ɫ����");
			}
			break;
			case 2://�óԵ������
			{

			}
			break;
			case 3://άC���ʲ�
			{

			}
			break;
			case 4://����
			{

			}
			break;
			case 5://�������
			{

			}
			break;
			default:
				break;
			}
		}
	}
	break;
	case 2://װ��
	{
		if (CurSelectedHero->Equipments[REALINDEX])//������λ����װ��
		{
			Rectangle(hdc, 0, (BATTLE_AREA + 1)*PIX_PER_HEIGHT, IMAGE_INFO*PIX_PER_WIDTH, SCREEN_HEIGHT*PIX_PER_HEIGHT);
			switch (CurSelectedHero->Equipments[REALINDEX]->StockNumber)
			{
			case 0://����ָ�׵�
			{
				printf("��ֱ����һ�죬�����������𱻷���ָ�׵�֧��Ŀ־壬��\n��������η�綼�������ĳ��衱\n                                             -----����\n");
			}
			break;
			case 1://���Ķ����
			{
				printf("�Դ����˷��Ķ��������ҾͿ�����ÿ��һ�ξ͵ô�һ��\n������������ӵļ����˼��������˼�������Լ���������\n���Բ�������������ѧ����ƽ���͡�������Ҷ�ѧ���˿�����\n���������˵����������վ����");
			}
			break;
			case 2://��Ь
			{
				printf("�������Ҫ��ʲô�Ƽ�����ҵĻ����Ǿ�һ������Ь�ˡ�");
			}
			break;
			case 3://�Ӻ�İ��
			{
				printf("����Ҷ��ھ���Ӻ�İ���Ƿ�����ʺϹ��ݵ�����ʱ�����\n�Ѿ�ĬĬ�ذ��������ˡ��������Ͳ��ȣ������������ȥ����\n��һ���ɢ�ˡ����Ӳ������ڡ��顱��һЩ���ԣ���Ȼ��\n��ʮ��ʱ���������ֻ�Ǿ���������׷�䣬����ǰϲ����һ��\n��֪���ĳ�ɫ���ϣ�Ȼ������˯����");
			}
			break;
			case 4://�����
			{
				printf("���ڵ��״�����ܲ��ܼӿ칥���ٶȵ����⣬Emphasizer�Ѿ�\n�Եò����䷳�ˣ������ˣ������������ǳ�������Ƕ�����һ\n���������롱�������ʿ�ˮ��������˵�������ҵ�ͷ���Ǹɵ�\n����ǰ���ˡ���");
			}
			break;
			case 5://���ĸ���
			{
				printf("ʵ���ϣ���Emphasizer˵���ڸ�����ʱ������ֻ��һ��С����\n�������ǿ��������ö�죡��������������Լ��ĺ���һ����\n�������ĸ��塣���š����磬��˵�Ķԡ���������Ҷ�Ϊ����\n�ơ��ɵ�������������ʱ��EmphasizerҲֻ��ģ���Ļش�\n��û�����Ƿ������ѡ���������Ҳ���������������ô��\n��������Խ��Խ��ġ���");
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

	if ((RelativeLoc.Y == (THING_HEIGHT_CHAR + 1)) || (RelativeLoc.X % (THING_WIDTH_CHAR + 1) == 0))//���ڷֽ�������Ч
		return;
	int xIndex = RelativeLoc.X / (THING_WIDTH_CHAR + 1);//��Χ��0-8
	int yIndex = RelativeLoc.Y / (THING_HEIGHT_CHAR + 1);//��Χ��0-1
	int Ftype = xIndex / 3;//��Χ��0-2 �ֱ�ָ���� ����Ʒ ��װ�� //���̵���˵�ֱ�ָǿ���� ����Ʒ ��װ��
	int RealIndex = yIndex * 3 + xIndex % 3;//������Χ��0-5
	if (LastShownIndex != RealIndex || LastShownType != Ftype)
	{
		isShowingHero = false;//����û����ʾӢ��
		ShowDetail(Ftype, RealIndex);//չʾ����Ϣ
		LastShownIndex = RealIndex;
		LastShownType = Ftype;
	}
}
void FormalState::TriggerFunction(COORD Destination)
{
	GPHero* Tmp;
	if (Tmp = dynamic_cast<GPHero*>(CurSelectedHero))
	{
		if ((Destination.Y == (THING_HEIGHT_CHAR + 1)) || (Destination.X % (THING_WIDTH_CHAR + 1) == 0))//���ڷֽ�������Ч
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//��Χ��0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//��Χ��0-1
		int Ftype = xIndex / 3;//��Χ��0-2 �ֱ�ָ���� ����Ʒ ��װ�� //���̵���˵�ֱ�ָǿ���� ����Ʒ ��װ��
		int RealIndex = yIndex * 3 + xIndex % 3;//������Χ��0-5
		switch (Ftype)
		{
		case 0://������
		{
			if (Tmp->Skills[RealIndex]&& Tmp->uAttribute.Energy > CurTriggeredSkill->EnergyConsume)//����м����������㹻
			{
				TmpMOPState = SMState;
				CurTriggeredSkill = Tmp->Skills[RealIndex];//���øü���Ϊ��ǰ��������
			}
		}
		break;
		case 1://����Ʒ�� 
			Tmp->UseConsumable(RealIndex);
			break;
		case 2://װ�����޷���������
			break;
		default:
			break;
		}
	}
}
void FormalState::SolveMouseReleased(COORD Destination)
{
	if (LeftButtonPressed)//���ǰ������
	{
		if (Destination.Y < BATTLE_AREA&&Active[Destination.X][Destination.Y].Occupied)//���λ��ս��������ѡ�е�λ���е�λ
		{
			Gotta = dynamic_cast<GPHero*>(CurSelectedHero);
			(CurSelectedHero = Active[Destination.X][Destination.Y].OccupyingUnit)->GetSelected();//�Ǿ�ѡ����
		}
		else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//�������ս������λ�ڹ�����
			TriggerFunction({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//������Ӧ����Ĺ���
	}
	else//���ǰ����Ҽ�
	{
		GPHero* Tmp;
		if (Tmp = dynamic_cast<GPHero*>(CurSelectedHero))
		{
			if (Destination.Y < BATTLE_AREA)//���λ��ս����
				Tmp->MoveTo(Destination);//Ӣ���ж�
			else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//���λ�ڹ�����
				BeginTransportOrUpSkill({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//��ô��ʼת�ƻ�����������
		}
	}
	LeftButtonPressed = false;//����
}
void FormalState::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X > INFO_FUNCTION&&MovedLoc.Y > BATTLE_AREA)//������λ�ڹ�����
		MouseOperateState::SolveMouseMoved(MovedLoc);
	else if (MovedLoc.X <= INFO_FUNCTION || MovedLoc.Y <= BATTLE_AREA)//��겻λ�ڹ�����
	{
		if (!isShowingHero)
		{
			isShowingHero = true;//��������ʾӢ��
			CurSelectedHero->PrintImage();//��ʾ��ǰѡ����Ӣ�۵�ͷ��
		}
		CurSelectedHero->PrintInformation();//��ʾ��ǰѡ����Ӣ�۵���Ϣ
											//Sleep(500);
	}
}
void FormalState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�������
			LeftButtonPressed = true;
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�Ҽ�����
			;
		else//�����ͷ�
			SolveMouseReleased(NewEvent.dwMousePosition);//������д���
	}
	break;
	case MOUSE_MOVED://����ƶ�
		SolveMouseMoved(NewEvent.dwMousePosition);//���䴦��
		break;
	default:
		break;
	}
}
void SkillingState::SolveMouseReleased(COORD Destination)
{
	for (short y = LastMousePos.Y-TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)//�������ָʾ
		FillConsoleOutputCharacter(hOut, ' ', TmpSkillRange*2+1, { LastMousePos.X - TmpSkillRange,y }, &num);
	if (LeftButtonPressed) //����������
	{
		if (Destination.Y < BATTLE_AREA)//�������ս���� ˵������ʩ�ż���
		{
			for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
				for (short x = LastMousePos.X - TmpSkillRange; x <= LastMousePos.X + TmpSkillRange; x++)
					if (Active[x][y].Occupied)
						Active[x][y].OccupyingUnit->GetSkillEffection(CurTriggeredSkill);
			CurSelectedHero->uAttribute.Energy -= CurTriggeredSkill->EnergyConsume;//����
			CurTriggeredSkill->LastCD = CurTriggeredSkill->CD;//����CD
			EraseThing(SKILL, CurTriggeredSkill->index);
			CurSelectedHero->Skills[CurTriggeredSkill->index] = NULL;
			SetEvent(SkillCDMsg[CurSelectedHero->camp][CurSelectedHero->number]);//����ˢ�¼��ܵ��ź�
		}
	}
	//���������ս�����򲻽�����Ӧ
	TmpMOPState = FMState;//״̬ת��
	LeftButtonPressed = false;//����
}
void SkillingState::SolveMouseMoved(COORD MovedLoc)
{
	if ((MovedLoc.Y<BATTLE_AREA))//����˵��һ�� һ�������빦���� �Ͳ�Ӧ�����ж��Ƿ��ڷż�����  ��Ϊ��ʱ��Ӧ����ʾ�ż�����Ϣ
	{
		for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
			FillConsoleOutputCharacter(hOut, ' ', TmpSkillRange * 2 + 1, { LastMousePos.X - TmpSkillRange,y }, &num);
		TmpSkillRange = CurTriggeredSkill->Range();//�ݴ漼�ܷ�Χ
		LastMousePos.X = MovedLoc.X > TmpSkillRange ? ((MovedLoc.X+ TmpSkillRange<BATTLE_WIDTH? MovedLoc.X : BATTLE_WIDTH -1- TmpSkillRange)): TmpSkillRange;
		LastMousePos.Y = MovedLoc.Y > TmpSkillRange ? ((MovedLoc.Y + TmpSkillRange<BATTLE_HEIGHT ? MovedLoc.Y : BATTLE_HEIGHT - 1 - TmpSkillRange)) : TmpSkillRange;
		for (short y = LastMousePos.Y - TmpSkillRange; y <= LastMousePos.Y + TmpSkillRange; y++)
			FillConsoleOutputCharacter(hOut, SKILL_CHAR, TmpSkillRange * 2 + 1, { LastMousePos.X - TmpSkillRange,y }, &num);
	}
	else if (MovedLoc.X > INFO_FUNCTION)//������λ�ڹ�����
		MouseOperateState::SolveMouseMoved(MovedLoc);

	if (!isShowingHero)
	{
		isShowingHero = true;//��������ʾӢ��
		CurSelectedHero->PrintImage();//��ʾ��ǰѡ����Ӣ�۵�ͷ��
	}
}
void SkillingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�������
			LeftButtonPressed = true;
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�Ҽ�����
			;
		else//�����ͷ�
			SolveMouseReleased(NewEvent.dwMousePosition);//������д���
	}
	break;
	case MOUSE_MOVED://����ƶ�
		SolveMouseMoved(NewEvent.dwMousePosition);//���䴦��
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
	if (LeftButtonPressed) //���������� ����ת��
	{
		if (Active[Destination.X][Destination.Y].Occupied&&(Gotta=dynamic_cast<GPHero*>(Active[Destination.X][Destination.Y].OccupyingUnit)))
		{
			if (Active[Destination.X][Destination.Y].OccupyingUnit->number)//����0˵��Ҫת��
			{
				if (TransportedType == CONSUMABLE && Gotta->GetConsumable(Tmp->Consumables[CurTransportedThingIndex]))//����Ǵ��������Ʒ �����п�λ
				{
					Tmp->LoseConsumable(CurTransportedThingIndex);//ʧȥװ��
					EraseThing(CONSUMABLE, CurTransportedThingIndex);//ĨȥͼƬ
				}
				else if (TransportedType == EQUIPMENT && Active[Destination.X][Destination.Y].OccupyingUnit->GetEquipment(Tmp->Equipments[CurTransportedThingIndex]))//����Ǵ����װ�� �����п�λ
				{
					Tmp->LoseEquipment(CurTransportedThingIndex);//ʧȥװ��
					EraseThing(EQUIPMENT, CurTransportedThingIndex);//ĨȥͼƬ
				}
			}
			else//��0˵��Ҫ��
			{
				EraseThing(TransportedType, CurTransportedThingIndex);//��ȥ��ƷͼƬ
				money += ((TransportedType == EQUIPMENT) ? Tmp->Equipments[CurTransportedThingIndex]->GetEffection().BaseAttack->RewardM : Tmp->Consumables[CurTransportedThingIndex]->Effect()->Effection.RewardM)*SELL_RATE / 10;//��Ǯ
				if (TransportedType == EQUIPMENT)
					Tmp->Equipments[CurTransportedThingIndex] = NULL;//������Ʒ
				else
					Tmp->Consumables[CurTransportedThingIndex] = NULL;
			}
		}
		TmpMOPState = FMState;//ת��Ϊ��ͨ״̬
	}
	else//��������Ҽ�
	{
		if (Destination.Y < BATTLE_AREA)//���λ��ս����
		{
			Tmp->MoveTo(Destination);//Ӣ���ж�
			TmpMOPState = FMState;//ת��Ϊ��ͨ״̬
		}
	}
	LeftButtonPressed = false;//����
	
}
void TransportingState::SolveMouseMoved(COORD MovedLoc)
{
	COORD RelativeLoc;//�������
	if (MovedLoc.X > INFO_FUNCTION&&MovedLoc.Y > BATTLE_AREA)//������λ�ڹ�����
		MouseOperateState::SolveMouseMoved(MovedLoc);
	else if (MovedLoc.X <= INFO_FUNCTION || MovedLoc.Y <= BATTLE_AREA)//��겻λ�ڹ�����
	{
		if (!isShowingHero)
		{
			isShowingHero = true;//��������ʾӢ��
			CurSelectedHero->PrintImage();//��ʾ��ǰѡ����Ӣ�۵�ͷ��
		}
		CurSelectedHero->PrintInformation();//��ʾ��ǰѡ����Ӣ�۵���Ϣ
											//Sleep(500);
	}
}
void TransportingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�������
			LeftButtonPressed = true;
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�Ҽ�����
			;
		else//�����ͷ�
			SolveMouseReleased(NewEvent.dwMousePosition);//������д���
	}
	break;
	case MOUSE_MOVED://����ƶ�
		SolveMouseMoved(NewEvent.dwMousePosition);//���䴦��
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
	SetConsoleCursorPosition(hOut, { 0,BATTLE_AREA + 1 });//��λ���
	SetConsoleTextAttribute(hOut, DefaultColor);
	switch (FTYPE)
	{
	case 0://ǿ����
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
	case 1://����Ʒ
	{
		switch (Shop->Consumables[REALINDEX]->StockNumber)
		{
		case 0://����
		{
			printf("����ʱ��Ĭ���ԣ���Ը��չʾ�Լ��������������̾�����Ҫ��\n����֤�����𣿡���Ȼ������ȴһֱ����������ѵʱ�Ĺ�ΰ��\n����˵ֻ�Ǵ�˵�������Ҹ߹���̺���ô���ԭ����Ϊ�飡��\n��ȷ�����Ƕ�������˼�ص��ͷ���·�ȷ��һ�㡣");
		}
		break;
		case 1://����
		{
			printf("��֪���ĳ�ɫ����");
		}
		break;
		case 2://�óԵ������
		{

		}
		break;
		case 3://άC���ʲ�
		{

		}
		break;
		case 4://����
		{

		}
		break;
		case 5://�������
		{

		}
		break;
		default:
			break;
		}
	}
	break;
	case 2://װ��
	{
		Rectangle(hdc, 0, (BATTLE_AREA + 1)*PIX_PER_HEIGHT, IMAGE_INFO*PIX_PER_WIDTH, SCREEN_HEIGHT*PIX_PER_HEIGHT);
		switch (Shop->Equipments[REALINDEX]->StockNumber)
		{
		case 0://����ָ�׵�
		{
			printf("��ֱ����һ�죬�����������𱻷���ָ�׵�֧��Ŀ־壬��\n��������η�綼�������ĳ��衱\n                                             -----����\n");
		}
		break;
		case 1://���Ķ����
		{
			printf("�Դ����˷��Ķ��������ҾͿ�����ÿ��һ�ξ͵ô�һ��\n������������ӵļ����˼��������˼�������Լ���������\n���Բ�������������ѧ����ƽ���͡�������Ҷ�ѧ���˿�����\n���������˵����������վ����");
		}
		break;
		case 2://��Ь
		{
			printf("�������Ҫ��ʲô�Ƽ�����ҵĻ����Ǿ�һ������Ь�ˡ�");
		}
		break;
		case 3://�Ӻ�İ��
		{
			printf("����Ҷ��ھ���Ӻ�İ���Ƿ�����ʺϹ��ݵ�����ʱ�����\n�Ѿ�ĬĬ�ذ��������ˡ��������Ͳ��ȣ������������ȥ����\n��һ���ɢ�ˡ����Ӳ������ڡ��顱��һЩ���ԣ���Ȼ��\n��ʮ��ʱ���������ֻ�Ǿ���������׷�䣬����ǰϲ����һ��\n��֪���ĳ�ɫ���ϣ�Ȼ������˯����");
		}
		break;
		case 4://�����
		{
			printf("���ڵ��״�����ܲ��ܼӿ칥���ٶȵ����⣬Emphasizer�Ѿ�\n�Եò����䷳�ˣ������ˣ������������ǳ�������Ƕ�����һ\n���������롱�������ʿ�ˮ��������˵�������ҵ�ͷ���Ǹɵ�\n����ǰ���ˡ���");
		}
		break;
		case 5://���ĸ���
		{
			printf("ʵ���ϣ���Emphasizer˵���ڸ�����ʱ������ֻ��һ��С����\n�������ǿ��������ö�죡��������������Լ��ĺ���һ����\n�������ĸ��塣���š����磬��˵�Ķԡ���������Ҷ�Ϊ����\n�ơ��ɵ�������������ʱ��EmphasizerҲֻ��ģ���Ļش�\n��û�����Ƿ������ѡ���������Ҳ���������������ô��\n��������Խ��Խ��ġ���");
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
	if (Gotta)//����������Ǽ���
	{
		if ((Destination.Y == (THING_HEIGHT_CHAR + 1)) || (Destination.X % (THING_WIDTH_CHAR + 1) == 0))//���ڷֽ�������Ч
			return;
		int xIndex = Destination.X / (THING_WIDTH_CHAR + 1);//��Χ��0-8
		int yIndex = Destination.Y / (THING_HEIGHT_CHAR + 1);//��Χ��0-1
		int Ftype = xIndex / 3;//��Χ��0-2 �ֱ�ָ���� ����Ʒ ��װ�� //���̵���˵�ֱ�ָǿ���� ����Ʒ ��װ��
		int RealIndex = yIndex * 3 + xIndex % 3;//������Χ��0-5
		switch (Ftype)
		{
		case 0://��ǿ����
		{
			if (money >= Shop->EnhanceBooks[RealIndex]->Effect()->Effection.RewardM&&Gotta)
			{
				Gotta->GetEffectedByBuff(Shop->EnhanceBooks[RealIndex]->Effect());//���ǿ��Ч��
				money -= Shop->EnhanceBooks[RealIndex]->Effect()->Effection.RewardM;//��Ǯ
			}
		}
		break;
		case 1://������Ʒ
		{
			if ((money >= Shop->Consumables[RealIndex]->Effect()->Effection.RewardM) && Gotta&&Gotta->GetConsumable(Shop->Consumables[RealIndex]))//Ǯ�������п�λ
				money -= Shop->Consumables[RealIndex]->Effect()->Effection.RewardM;//��Ǯ
		}
		break;
		case 2://��װ��
		{
			if ((money >= (Shop->Equipments[RealIndex]->GetEffection()).BaseAttack->RewardM) && Gotta&& Gotta->GetEquipment(Shop->Equipments[RealIndex]))//Ǯ�������п�λ
				money -= (Shop->Equipments[RealIndex]->GetEffection().BaseAttack->RewardM);//��Ǯ
		}
		break;
		default:
			break;
		}
	}
}
void ShoppingState::SolveMouseReleased(COORD Destination)
{
	if (LeftButtonPressed)//���ǰ������
	{
		if (Destination.Y < BATTLE_AREA&&Active[Destination.X][Destination.Y].Occupied)//���λ��ս��������ѡ�е�λ���е�λ
			(CurSelectedHero = Active[Destination.X][Destination.Y].OccupyingUnit)->GetSelected();//�Ǿ�ѡ����
		else if (Destination.Y > BATTLE_AREA&&Destination.X > INFO_FUNCTION)//�������ս������λ�ڹ�����
			TriggerFunction({ Destination.X - INFO_FUNCTION,Destination.Y - BATTLE_AREA });//������Ӧ����Ĺ���
	}
}
void ShoppingState::SolveMouseMoved(COORD MovedLoc)
{
	if (MovedLoc.X > INFO_FUNCTION&&MovedLoc.Y > BATTLE_AREA)//������λ�ڹ�����
	{
		RelativeLoc.X = MovedLoc.X - INFO_FUNCTION;
		RelativeLoc.Y = MovedLoc.Y - BATTLE_AREA;

		if ((RelativeLoc.Y == (THING_HEIGHT_CHAR + 1)) || (RelativeLoc.X % (THING_WIDTH_CHAR + 1) == 0))//���ڷֽ�������Ч
			return;
		int xIndex = RelativeLoc.X / (THING_WIDTH_CHAR + 1);//��Χ��0-8
		int yIndex = RelativeLoc.Y / (THING_HEIGHT_CHAR + 1);//��Χ��0-1
		int Ftype = xIndex / 3;//��Χ��0-2 �ֱ�ָ���� ����Ʒ ��װ�� //���̵���˵�ֱ�ָǿ���� ����Ʒ ��װ��
		int RealIndex = yIndex * 3 + xIndex % 3;//������Χ��0-5
		if (LastShownIndex != RealIndex || LastShownType != Ftype)
		{
			isShowingHero = false;//����û����ʾӢ��
			ShowDetail(Ftype, RealIndex);//չʾ����Ϣ
			LastShownIndex = RealIndex;
			LastShownType = Ftype;
		}
	}
	else if (MovedLoc.X <= INFO_FUNCTION || MovedLoc.Y <= BATTLE_AREA)//��겻λ�ڹ�����
	{
		if (!isShowingHero)
		{
			isShowingHero = true;//��������ʾӢ��
			CurSelectedHero->PrintImage();//��ʾ��ǰѡ����Ӣ�۵�ͷ��
		}
		CurSelectedHero->PrintInformation();//��ʾ��ǰѡ����Ӣ�۵���Ϣ
											//Sleep(500);
	}
}
void ShoppingState::SolveMouseInput(MOUSE_EVENT_RECORD NewEvent)
{
	switch (NewEvent.dwEventFlags)
	{
	case 0:
	{
		if (NewEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)//�������
			LeftButtonPressed = true;
		else if (NewEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)//�Ҽ�����
			;
		else//�����ͷ�
			SolveMouseReleased(NewEvent.dwMousePosition);//������д���
	}
	break;
	case MOUSE_MOVED://����ƶ�
		SolveMouseMoved(NewEvent.dwMousePosition);//���䴦��
		break;
	default:
		break;
	}
}


void AIStillState::Act()
{
	if (JustAttacked)//����ձ����� ��ת�Ƶ�����׷��״̬ ���� ���״̬����������õ� ͬʱ ������Ӧ������Object��HeroToChase��
	{
		Object->TmpAIState = AIStates[Object->number][AINegChase];//�л�������׷��״̬
		JustAttacked = false;
	}
	else//��������������� ����ⷶΧ���Ƿ��е���
	{
		Object->Destination = CITADEL;//��������Ϊ��Ŀ��λ��
		for (int i = 0; i < Object->uAttribute.Speed; i++)
			NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;//�ҵ���һ����λ��
		if (Active[NextLoc[Object->camp][Object->number]->Loc.X][NextLoc[Object->camp][Object->number]->Loc.Y].Occupied || LastDestination != CITADEL)//�������λ�ñ�ռ���˻���Ŀ�ĵز�������
		{
			if (Object->FindPath())//��ʼ����·��  ����ҵ���
			{
				for (int i = 0; i < Object->uAttribute.Speed; i++)//����һ����λ��
					NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;
				if (LastDestination != CITADEL)//�������ΪĿ�ĵر�� ��ô������һ�ε�Ŀ�ĵ�Ϊ�µ����Ŀ�ĵ�
					LastDestination = CITADEL;
			}
			else
				NextLoc[Object->camp][Object->number]->Loc=Object->KerLoc;//�Ҳ���·����ֹͣ
		}
		Object->Jmp(NextLoc[Object->camp][Object->number]->Loc);//�ƶ����Ǹ�λ��
		GetLocalTime(&BeginTest);//ȡ�ÿ�ʼ����ʱ��
		Sleep(1000 / Object->uAttribute.Frequence);//�ȴ��������
		GetLocalTime(&EndTest);//ȡ�ý������ʱ��
		for (; EndTest.wMilliseconds - BeginTest.wMilliseconds <= TestTime;)//Ҳ����˵ ���ڹ���С��һ���̶ȵĵ��ˣ�׷��״̬���޷����� �����𵽷��ݵ�����
		{
			int y1 = ((Object->KerLoc.Y - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.Y - Object->uAttribute.AttackRange : 0;
			int y2 = ((Object->KerLoc.Y + Object->uAttribute.AttackRange)<BATTLE_HEIGHT) ? Object->KerLoc.Y + Object->uAttribute.AttackRange : BATTLE_HEIGHT - 1;
			short x1 = ((Object->KerLoc.X - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.X - Object->uAttribute.AttackRange : 0;
			int x2 = ((Object->KerLoc.X + Object->uAttribute.AttackRange)<BATTLE_WIDTH) ? Object->KerLoc.X + Object->uAttribute.AttackRange : BATTLE_WIDTH - 1;
			int length = x2 - x1 + 1;
			for (short y = y1; y <= y2; y++)
				for (short x = x1; x <= x2; x++)
					if (Active[x][y].Occupied&&Object->KerLoc != COORD({ x, y }) && Active[x][y].UnitCamp != Object->camp)//������˶��Ҳ����Լ����������Ƕ�����Ӫ��
					{
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
						Sleep(300);
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
						CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));//���Ź�����Ч
						Active[x][y].OccupyingUnit->GetInjuried(Object);//����һ���˺�
						Object->HeroToChase = Active[x][y].OccupyingUnit;//����Ϊ׷��Ŀ��	
						Object->TmpAIState=AIStates[Object->number][AIPosChase];//ת��������׷��״̬
						goto BREAK;
					}
			GetLocalTime(&EndTest);//ȡ�õ�ǰʱ��
		}
		BREAK:{}
	}
}
void AIPChaseState::Act()
{
	Object->Destination = Object->HeroToChase->KerLoc;
	int dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;
	int dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;
	while((dx<=Object->uAttribute.AttackRange+2)&&(dy <= Object->uAttribute.AttackRange + 2))//��û�г���������Χ2��ʱ��
	{
		if (!Object->FindPath())//��֪����ô׷�Ͳ�׷��
			break;
		for (int i = 0; i < Object->uAttribute.Speed; i++)//����һ����λ��
			NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;
		Object->Jmp(NextLoc[Object->camp][Object->number]->Loc);
		GetLocalTime(&BeginTest);//ȡ�ÿ�ʼ����ʱ��
		Sleep(1000 / Object->uAttribute.Frequence);//�ȴ��������
		GetLocalTime(&EndTest);//ȡ�ý������ʱ��
		for (; EndTest.wMilliseconds - BeginTest.wMilliseconds <= TestTime;)
		{
			int y1 = ((Object->KerLoc.Y - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.Y - Object->uAttribute.AttackRange : 0;
			int y2 = ((Object->KerLoc.Y + Object->uAttribute.AttackRange)<BATTLE_HEIGHT) ? Object->KerLoc.Y + Object->uAttribute.AttackRange : BATTLE_HEIGHT - 1;
			short x1 = ((Object->KerLoc.X - Object->uAttribute.AttackRange) >= 0) ? Object->KerLoc.X - Object->uAttribute.AttackRange : 0;
			int x2 = ((Object->KerLoc.X + Object->uAttribute.AttackRange)<BATTLE_WIDTH) ? Object->KerLoc.X + Object->uAttribute.AttackRange : BATTLE_WIDTH - 1;
			int length = x2 - x1 + 1;
			for (short y = y1; y <= y2; y++)
				for (short x = x1; x <= x2; x++)
					if (Active[x][y].Occupied&&Object->KerLoc != COORD({ x, y }) && Active[x][y].UnitCamp != Object->camp)//������˶��Ҳ����Լ����������Ƕ�����Ӫ��
					{
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, { x1,y }, &num);
						Sleep(300);
						for (short y = y1; y <= y2; y++)
							FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
						CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));//���Ź�����Ч
						Active[x][y].OccupyingUnit->GetInjuried(Object);//����һ���˺�
					}
			Sleep(1000 / Object->uAttribute.Frequence);//�ȴ��������
			GetLocalTime(&EndTest);//ȡ�õ�ǰʱ��
		}
		Object->Destination = Object->HeroToChase->KerLoc;//����Ŀ��λ��
		dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;//����X����
		dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;//����Y����
	}
	Object->TmpAIState = AIStates[Object->number][AIStill];//׷����Ϻ���뾲ֹ״̬
}
void AINChaseState::Act()
{
	int dx, dy;
	for(;;)
	{
		GetLocalTime(&BeginTest);//��ȡ��ʼ���ʱ��
		Object->Destination = Object->HeroToChase->KerLoc;
		if (!Object->FindPath())//��֪����ô׷�Ͳ�׷��
			break;
		for (int i = 0; i < Object->uAttribute.Speed; i++)//����һ����λ��
			NextLoc[Object->camp][Object->number] = NextLoc[Object->camp][Object->number]->Next;
		Object->Jmp(NextLoc[Object->camp][Object->number]->Loc);
		Sleep(1000 / Object->uAttribute.Frequence);//�ȴ��������
		GetLocalTime(&EndTest);//��ȡֹͣ���ʱ��
		dx = (Object->KerLoc.X - Object->Destination.X) > 0 ? Object->KerLoc.X - Object->Destination.X : Object->Destination.X - Object->KerLoc.X;//����X��Ծ���
		dy = (Object->KerLoc.Y - Object->Destination.Y) > 0 ? Object->KerLoc.Y - Object->Destination.Y : Object->Destination.Y - Object->KerLoc.Y;//����Y��Ծ���
		if (dx > Object->uAttribute.AttackRange || dy > Object->uAttribute.AttackRange)//û��������Χ ����׷
		{
			while (EndTest.wMilliseconds - BeginTest.wMilliseconds < TestTime)//�ȴ��㹻��ʱ��
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
			CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));//���Ź�����Ч
			Object->HeroToChase->GetInjuried(Object);//�ܵ��˺�
			Object->TmpAIState = AIStates[Object->number][AIPosChase];//�л�������׷��״̬
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
		if ((Content[index]->F <= Content[index * 2]->F) && (Content[index]->F <= Content[index * 2 + 1]->F))//��������ӽڵ����С�ڸýڵ� ������ά��
			break;
		else//��ô�ýڵ����ٴ��������ӽڵ��е�һ��
		{
			if (Content[index * 2]->F <= Content[index * 2 + 1]->F)//����ڵ��Сʱ
			{
				Swap(index, index * 2);//��ô��ǰ�ڵ��λ��Ӧ���ø���С����ڵ�
				index = index * 2;
			}
			else//���ҽڵ��Сʱ
			{
				Swap(index, index * 2 + 1);//��ô��ǰ�ڵ��λ��Ӧ���ø���С���ҽڵ�
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
	printf("�ȼ�%d", level);
	SetConsoleCursorPosition(hOut, { xStart , yStart+1 });
	printf("%s", name.c_str());
	SetConsoleCursorPosition(hOut, { xStart , yStart+2 });
	printf("���ģ�%d", EnergyConsume);
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
	printf("����%d", EquipEffection.BaseAttack->RewardM);
	SetConsoleCursorPosition(hOut, { xStart , yStart +1});
	switch (StockNumber)
	{
	case 0://����ָ�׵�
	{
		printf("����");
		SetConsoleCursorPosition(hOut, { xStart , yStart+2 });
		printf("ָ�׵�");
	}
	break;
	case 1://���Ķ����
	{
		printf("����");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("�����");
	}
	break;
	case 2://��Ь
	{
		printf("��Ь");
	}
	break;
	case 3://�Ӻ�İ��
	{
		printf("�Ӻ��");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("���");
	}
	break;
	case 4://�����
	{
		printf("�����");
	}
	break;
	case 5://���ĸ���
	{
		printf("����");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("����");
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
	printf("����%d", ConsumableEffetion->Effection.RewardM);
	SetConsoleCursorPosition(hOut, { xStart , yStart +1});
	switch (StockNumber)
	{
	case 0://����
	{
		printf("����");
	}
	break;
	case 1://����
	{
		printf("����");
	}
	break;
	case 2://�óԵ������
	{
		printf("�óԵ�");
		SetConsoleCursorPosition(hOut, { xStart , yStart + 2 });
		printf("�����");
	}
	break;
	case 3://άC���ʲ�
	{
		printf("άC���ʲ�");
	}
	break;
	case 4://����
	{
		printf("����");
	}
	break;
	case 5://�������
	{
		printf("�������");
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
		if (Rand <= Attacker->uAttribute.CrRate)//����
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
	PrintSelf();//��ӡ�Լ�
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
		FillConsoleOutputAttribute(hOut, Apperance, IMAGE_INFO, { 0,y }, &num);//��ӡͷ�񱳾�
	//�����ⲿ���ǹ��е�
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance,EyeHeight }, &num);//������
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance,EyeHeight }, &num);//������
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium,NoseHeight }, &num);//������
	FillConsoleOutputAttribute(hOut, 0, 2 * MouthWidth + 1, { ImageMidium - MouthWidth,MouthHeight }, &num);//��ƽ��
	//������Щ�Ƕ��ص�
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
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance ,EyebrowHeight-1 }, &num);//����������üë
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance ,EyebrowHeight - 1 }, &num);//���ұ������üë
	
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - MouthWidth,MouthHeight - 1 }, &num);//�����������
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + MouthWidth,MouthHeight - 1 }, &num);//�����������

}
void Hero::PrintSad()
{
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium - EyeDistance ,EyebrowHeight - 1 }, &num);//����������üë
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance + 1,EyebrowHeight }, &num);
	FillConsoleOutputAttribute(hOut, 0, 1, { ImageMidium + EyeDistance ,EyebrowHeight - 1 }, &num);//���ұ������üë

	for (short i = 2; i <= 4; i++)//���Ҹ�����������
	{
		FillConsoleOutputAttribute(hOut, TearColor, 1, { ImageMidium - EyeDistance,EyeHeight + i }, &num);
		FillConsoleOutputAttribute(hOut, TearColor, 1, { ImageMidium + EyeDistance,EyeHeight + i }, &num);
	}
}
void Hero::PrintGeneral()
{
	FillConsoleOutputAttribute(hOut, 0, 3, { ImageMidium - EyeDistance - 1,EyebrowHeight }, &num);//����ߵ�ƽüë
	FillConsoleOutputAttribute(hOut, 0, 3, { ImageMidium + EyeDistance - 1,EyebrowHeight }, &num);//���ұߵ�ƽüë
}
void Hero::PrintInformation()
{
	WaitForSingleObject(PRINTF_MUTEX, INFINITE);
	if (this==Shop)//�����̵��Ӣ��
	{
		SetConsoleTextAttribute(hOut, DefaultColor);
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 1 });
		printf("Ӣ��%d:%14s               Lv.%d", number, name.c_str(),level);
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 2 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("����ֵ:%7d/%5d               ", uAttribute.Blood, uAttribute.MaxBlood);
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
		printf("Ӣ��%d:%14s               Lv.%d", number, name.c_str(),level);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 3 });
		printf("���ܵ�:%13d               ����:%9d/%5d",LeftSkillPoint,CurExperical,ExpercialNeeded);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 9 });
		printf("����ٷֱ�:%8d%%               ħ���ٷֱ�:%8d%%",special.PhysicalPercent,special.MagicPercent);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 4 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("����ֵ:%7d/%5d               ",uAttribute.Blood,uAttribute.MaxBlood);
		SetConsoleTextAttribute(hOut, EnergyColor);
		printf("����ֵ:%7d/%5d", uAttribute.Energy, uAttribute.MaxEnergy);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 2 });
		SetConsoleTextAttribute(hOut, MoneyColor);
		printf("��Ǯ:%15d", money);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 5 });
		SetConsoleTextAttribute(hOut, PaColor);
		printf("������:%13d               ",uAttribute.Pa);
		SetConsoleTextAttribute(hOut, MaColor);
		printf("��ǿ:%15d",uAttribute.Ma);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 6 });
		SetConsoleTextAttribute(hOut, PdColor);
		printf("����:%15d               ",uAttribute.Pd);
		SetConsoleTextAttribute(hOut, MdColor);
		printf("ħ��:%15d",uAttribute.Md);

		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 7 });
		SetConsoleTextAttribute(hOut, SpeedColor);
		printf("����:%15f               ����:%15d",uAttribute.Frequence,uAttribute.Speed);
		
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 8 });
		SetConsoleTextAttribute(hOut, BloodColor);
		printf("����͵ȡ:%10d%%               ",special.SuckBlood);
		SetConsoleTextAttribute(hOut, EnergyColor);
		printf("������ȡ:%10d%%",special.SuckMagic);
		
		SetConsoleCursorPosition(hOut, { IMAGE_INFO + 1,BATTLE_HEIGHT + 10 });
		SetConsoleTextAttribute(hOut, CrColor);
		printf("������:%12d%%",uAttribute.CrRate);
	}
	ReleaseMutex(PRINTF_MUTEX);
}
bool Hero::GetEquipment(Equipment* NewEquipment)
{
	for(int i=0;i<MAX_THING_NUM;i++)
		if (!Equipments[i])
		{
			WaitForSingleObject(hmutex[camp][number], INFINITE);
			Equipments[i] = NewEquipment;//������Ϣ
			GetEquipmentEffection(NewEquipment->GetEffection());//���װ��Ч��
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
	//��һ������Ĩ��֮ǰ��
	EraseSelf();
	//�����ں�λ��
	KerLoc = NextKerLoc;
	//��һ�����Ǹ��µ�
	ShowSelf();

}
bool Hero::FindPath()
{
	if (KerLoc == Destination)
		return false;
	Astar* Start = new Astar(NULL, KerLoc, Destination);
	Open[camp][number]->insert(Start);//����ʼ����翪���б���
	Astar* Curstar = Open[camp][number]->remove();//������λ��
	Close[camp][number]->Add(Curstar);//�ر��б�������
	for (; Curstar->Loc != Destination;)
	{
		Close[camp][number]->Add(Curstar);//�ر��б�����ӵ�ǰ����
		int y1 = Curstar->Loc.Y ? Curstar->Loc.Y - 1 : 0;
		int y2 = (BATTLE_HEIGHT - Curstar->Loc.Y - 1) ? Curstar->Loc.Y + 1: BATTLE_HEIGHT-1;
		int x1 = Curstar->Loc.X ? Curstar->Loc.X - 1 : 0;
		int x2= (BATTLE_WIDTH - Curstar->Loc.X - 1) ? Curstar->Loc.X + 1 : BATTLE_WIDTH - 1;
		for (short y = y1; y <= y2; y++)
			for (short x = x1; x <= x2; x++)
			{
					if (Active[x][y].Occupied &&Destination != COORD({ x,y }))//���˶����ǻ�����Ŀ�ĵصĻ� ������Flase
						Close[camp][number]->Add(new Astar(NULL, { x,y }, { x,y }));
					if (!Close[camp][number]->find({ x,y }))
					{
						Astar* Son;
						if (Son = Open[camp][number]->find({ x,y }))//������ש�ڿ����б���
						{
							int NewG = Curstar->G + ((Curstar->Loc.X == x || Curstar->Loc.Y == y) ? 10 : 14);//�����µ�Gֵ
							if (NewG < Son->G)//�����·������ ��ô�͸������ש����Ϣ
							{
								Son->Father = Curstar;
								Son->G = NewG;
								Son->F = Son->G + Son->H;
								Open[camp][number]->Heapify();//����ά���ѵ�����
							}
						}
						else
							Open[camp][number]->insert(new Astar(Curstar, { x,y }, Destination));//������ڿ����б��� �����б���������һ��
					}
			}
		if (!(Curstar = Open[camp][number]->remove()))//�����б����Ƴ���С���ȷ���
			return false;//�����ʱ�б��Ѿ��� ˵��û��·�� ʧ��
	}
	Curstar->Next = Curstar;//�������һ���Ľ�β
	Curstar->IsPath = true;
	auto son = Curstar;//����Next������
	for (auto tmp = Curstar->Father; tmp; )
	{
		tmp->IsPath = true;
		tmp->Next = son;
		son = son->Father;
		tmp = tmp->Father;
	}
	for (; PathBegin[camp][number];)//ɾ���ɵ�·��
	{
		auto tmp = PathBegin[camp][number];//�ݴ�����ڵ�
		PathBegin[camp][number] = PathBegin[camp][number]->Next;//�����һ���ڵ�
		if (tmp == PathBegin[camp][number])//�������ڵ�����ĺ����ڵ���ͬ ˵�����˽�β ��ô�Ϳ����˳���
			break;
		delete tmp;//ɾ������ڵ�
	}
	NextLoc[camp][number] =PathBegin[camp][number] = Start;//�������
	Open[camp][number]->Clean();//����·���������
	Close[camp][number]->Clean();//�ڵ�ȫ��ɾ��
	return true;//Ѱ·�ɹ�
}
void Hero::LoseEquipment(int index)
{
	EraseThing(EQUIPMENT, index);//��ȥͼƬ
	uAttribute -= *(Equipments[index]->GetEffection().BaseAttack);//ɾ������Ч��
	special -= *(Equipments[index]->GetEffection().special);//ɾ������Ч��
	Equipments[index] = NULL;//�����¼
}
void Hero::GetEffectedByBuff(Buff* BuffEffection)
{
	if (camp==BuffEffection->Effection.Camp)
	{
		if (BuffEffection->Effection.LastTime)//����ǳ�����Ч��
		{//������׼������ ����һ��buff�ĸ���
			Buff* Tmp = new Buff(*BuffEffection);
			Tmp->Next = Head->Next;
			Tmp->Prev = Head;
			Head->Next = Head->Next->Prev = Tmp;//���½ڵ���Ϣ
			uAttribute += Tmp->Effection;//����״̬�ӳ�
			//֪ͨ�߳� ��Buff����
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
	PrintImage();//��ʾͷ����
	PrintInformation();//��ʾ��Ϣ��
	PrintFunction();//���ù�����
}
void Hero::LoadReuseAttribute()
{
	CurExperical = 0;
	//number=??? numberֻ���ڹ���ʱ��ȷ��
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
		WaitForSingleObject(AttackMsg[number], INFINITE);//�ȴ�����ָ��
		if (dead)
		{
			CloseHandle(AttackMsg[number]);
			for (int i = number; i <= CurNum[camp] - 1; i++)
			{
				Heros[i] = Heros[i + 1];//����Ӣ�۵Ŀ�
				Heros[i]->number--;
			}
			CurNum[camp]--;//ɾ�����Ӣ��
			for (int i = 1; i <= CurNum[camp]; i++)
				Heros[i]->GetExperical(uAttribute.RewardE);//��þ���
			money += uAttribute.RewardM;//��ý�Ǯ
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
				
				if (Active[x][y].Occupied&&KerLoc != COORD({x, y})&&Active[x][y].UnitCamp!=camp)//������˶��Ҳ����Լ����������Ƕ�����Ӫ��
				{
					for (short y = y1; y <= y2; y++)
						FillConsoleOutputCharacterA(hOut, ATTACK_CHAR, length, {x1,y},&num);
					Sleep(300);
					for (short y = y1; y <= y2; y++)
						FillConsoleOutputCharacterA(hOut, ' ', length, { x1,y }, &num);
					CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayAttackSound, (void*)this, 0, NULL));
					Active[x][y].OccupyingUnit->GetInjuried(this);//����һ���˺����˳�
					HeroToChase = Active[x][y].OccupyingUnit;//����Ϊ׷��Ŀ��	
					SetEvent(ChaseMsg[number]);//����׷���ź� ģ���޻���
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
		//�̵����������Ʒ
		for (int i = 0; i < MAX_THING_NUM; i++)
		{
			srand(rand() + 1);
			Consumables[i] = &ConsumableStock[rand() % CONSUMABLE_STOCK];
			srand(rand() + 1);
			Equipments[i] = &EquipmentStock[rand() % EQUIPMENT_STOCK];
			srand(rand() + 1);
			EnhanceBooks[i] = &EnhanceBookStock[rand() % ENHANCEBOOK_STOCK];
		}
		TmpMOPState = PMState;//�л�������״̬
		Gotta = dynamic_cast<GPHero*>(CurSelectedHero);//���ù�����
	}
	else
		TmpMOPState = FMState;//�����л�����ͨ״̬
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
void GPHero::UseConsumable(int index)//index��Χ��0-5
{
	if (Consumables[index])//������������������Ʒ
	{
		if (Consumables[index]->Range)
		{
			if (Consumables[index]->EffectionCamp() == Allies)
				for (int i = 1; i <= CurNum[Allies]; i++)
					Heros[i]->GetEffectedByBuff(Consumables[index]->Effect());//���Ч��
			else
				for (int i = 1; i <= CurNum[Enemy]; i++)
					Monsters[i]->GetEffectedByBuff(Consumables[index]->Effect());//���Ч��
		}
		else
			GetEffectedByBuff(Consumables[index]->Effect());//���Ч��
		EraseThing(CONSUMABLE, index);//��ȥͼƬ
		LoseConsumable(index);//�ڳ�Ա������NULL
	}
}
void GPHero::MoveTo(COORD destination)
{
	if (camp == Allies && number)
	{
		WaitForSingleObject(hmutex[camp][number], INFINITE);
		CloseHandle((HANDLE)_beginthreadex(NULL, 0, PlayMoveSound, (void*)this, 0, NULL));
		ResetEvent(AttackMsg[number]);//����ȡ��ȡ������
		if (Active[destination.X][destination.Y].Occupied)
		{
			HeroToChase = Active[destination.X][destination.Y].OccupyingUnit;
			SetEvent(ChaseMsg[number]);//����׷���ź�
			isChasing = true;
		}
		else
		{
			ResetEvent(ChaseMsg[number]);//���ò�׷����ź�
			isChasing = false;
			Destination = destination;//����Ŀ�ĵ�
		}
		SetEvent(MoveMsg[number]);//�����ƶ��ź�
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
	//���´�����Դ��������״̬
	Open[Allies][number] = new MinHeap;
	Close[Allies][number] = new Aector;
	hmutex[Allies][number] = CreateMutex(NULL, false, NULL);//������
	AttackMsg[number] = CreateEvent(NULL, true, true, NULL);//��ʼ���ɼ�⹥��
	BuffMsg[Allies][number] = CreateEvent(NULL, true, false, NULL);//��ʼ��buff
	SkillCDMsg[Allies][number] = CreateEvent(NULL, true, false, NULL);//��ʼ�޼��ܴ���CD
	MoveMsg[number] = CreateEvent(NULL, true, false, NULL);//��ʼδ�ƶ�
	ChaseMsg[number] = CreateEvent(NULL, true, false, NULL);//��ʼδ׷��
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
		SetEvent(BuffMsg[camp][number]);//ȷ���˳��߳�
		SetEvent(SkillCDMsg[camp][number]);//ȷ���˳��߳�
		SetEvent(MoveMsg[number]);//ȷ���˳��߳�
		SetEvent(ChaseMsg[number]);//ȷ���˳��߳�
		//���buff
		for (auto tmp = Head->Next; tmp != Rear; tmp = tmp->Next)
		{
			tmp->Prev->Next = tmp->Next;
			tmp->Next->Prev = tmp->Prev;
			delete tmp;
		}
		//ɾ���ɵ�·��
		Open[Allies][number]->Clean();
		Close[Allies][number]->Clean();
		for (; PathBegin[Allies][number];)
		{
			auto tmp = PathBegin[Allies][number];//�ݴ�����ڵ�
			PathBegin[Allies][number] = PathBegin[Allies][number]->Next;//�����һ���ڵ�
			if (tmp == PathBegin[Allies][number])//�������ڵ�����ĺ����ڵ���ͬ ˵�����˽�β ��ô�Ϳ����˳���
				break;
			delete tmp;//ɾ������ڵ�
		}
		//�رվ�� ɾ��ռ�õ���Դ 
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
	//�����趨���ܵȼ�
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
	//�趨�����ȼ�
	SetRebrithLevel(StockNumber == 1 ? Round : (StockNumber == 2 ? Round - SecondMonsterTurnUp : Round - ThirdMonsterTurnUp));
	//�����������λ��
	switch (rand() % 4)//�趨��ʼ����λ��
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
	//���»�ü���
	for (int i = 0; i<MAX_MONSTER_SKILL_NUM; i++)
		Skills[i] = &AISkillStock[(StockNumber - 1)*MAX_MONSTER_SKILL_NUM + i + 1];
	//ʧȥ����װ��
	for (int i = 0; i < MAX_THING_NUM; i++)
		if (Equipments[i])
			LoseEquipment(i);
	//���ø���Ա��װ����
	int EquipmentNum;
	if (Round >= MAX_THING_NUM * RoundsToGetMoreOneEqipment)
		EquipmentNum = 6;
	else
		EquipmentNum = Round / RoundsToGetMoreOneEqipment;
	//���»��װ��
	for (int i = 1; i <= EquipmentNum; i++)
	{
		srand(rand() + 1);
		GetEquipment(&EquipmentStock[rand() % EQUIPMENT_STOCK]);
	}
	HeroToChase = NULL;
	//���´�����Դ��������״̬
	AIStates[number][AIStill] = new AIStillState;
	AIStates[number][AIPosChase] = new AIPChaseState;
	AIStates[number][AINegChase] = new AINChaseState;
	CurAIState = AIStates[number][AIStill];
	TmpAIState = AIStates[number][AIStill];
	Open[Enemy][number] = new MinHeap;
	Close[Enemy][number] = new Aector;
	hmutex[Enemy][number]=CreateMutex(NULL, false, NULL);//������
	BuffMsg[Enemy][number] = CreateEvent(NULL, true, false, NULL);//��ʼ��buff
	SkillCDMsg[Enemy][number] = CreateEvent(NULL, true, false, NULL);//��ʼ�޼��ܴ���CD
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, UpdateBuff, (void*)this, 0, NULL));
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, FlushAISkill, (void*)this, 0, NULL));
	ShowSelf();
}
void AIHero::Die()
{
	GenerateReward();
	SetEvent(BuffMsg[Enemy][number]);//ȷ���˳��߳�
	SetEvent(SkillCDMsg[Enemy][number]);//ȷ���˳��߳�
	//���buff
	for (auto tmp = Head->Next; tmp != Rear; tmp = tmp->Next)
	{
		tmp->Prev->Next = tmp->Next;
		tmp->Next->Prev = tmp->Prev;
		delete tmp;
	}
	//ɾ���ɵ�·��
	Open[Enemy][number]->Clean();
	Close[Enemy][number]->Clean();
	for (; PathBegin[Enemy][number];)
	{
		auto tmp = PathBegin[Enemy][number];//�ݴ�����ڵ�
		PathBegin[Enemy][number] = PathBegin[Enemy][number]->Next;//�����һ���ڵ�
		if (tmp == PathBegin[Enemy][number])//�������ڵ�����ĺ����ڵ���ͬ ˵�����˽�β ��ô�Ϳ����˳���
			break;
		delete tmp;//ɾ������ڵ�
	}
	//�رվ�� ɾ��ռ�õ���Դ 
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
//***********************************������ʵ����Ӫʱ�ڲ��ĵ��Ⱥ���******************************
//***********************************************************************************************
void HandleKeyInput(KEY_EVENT_RECORD NewEvent) 
{
	GPHero* Tmp;
	if (NewEvent.bKeyDown)
	{
		int HeroNumber = NewEvent.wVirtualKeyCode - 48;
		if (NewEvent.dwControlKeyState&LEFT_CTRL_PRESSED&&HeroNumber > 0 && HeroNumber <= GP_STOCK)//������Ƽ����� ˵����Ҫ��Ӣ��
			BuyHero(HeroNumber);
		else if (HeroNumber >= 0 && HeroNumber <= CurNum[Allies])//����ǺϷ���Ӣ��ѡ��
		{
			if(CurMOPState==TMState)//�����ת��
			{
				if (!(Tmp = dynamic_cast<GPHero*>(CurSelectedHero)))
					system("pause");
				if (HeroNumber == 0)//ѡ0˵��Ҫ��װ��
				{
					EraseThing(TransportedType, CurTransportedThingIndex);//��ȥ��ƷͼƬ
					money += ((TransportedType == EQUIPMENT) ? Tmp->Equipments[CurTransportedThingIndex]->GetEffection().BaseAttack->RewardM : Tmp->Consumables[CurTransportedThingIndex]->Effect()->Effection.RewardM)*SELL_RATE / 10;//��Ǯ
					if (TransportedType == EQUIPMENT)
						Tmp->Equipments[CurTransportedThingIndex] = NULL;//������Ʒ
					else
						Tmp->Consumables[CurTransportedThingIndex] = NULL;
				}
				else//˵��Ҫת�ƶ���
				{
					if (TransportedType == CONSUMABLE && Heros[HeroNumber]->GetConsumable(Tmp->Consumables[CurTransportedThingIndex]))//����Ǵ��������Ʒ �����п�λ
					{
						Tmp->LoseConsumable(CurTransportedThingIndex);//ʧȥװ��
						EraseThing(CONSUMABLE, CurTransportedThingIndex);//ĨȥͼƬ
					}
					else if (TransportedType == EQUIPMENT && Heros[HeroNumber]->GetEquipment(Tmp->Equipments[CurTransportedThingIndex]))//����Ǵ����װ�� �����п�λ
					{
						Tmp->LoseEquipment(CurTransportedThingIndex);//ʧȥװ��
						EraseThing(EQUIPMENT, CurTransportedThingIndex);//ĨȥͼƬ
					}
				}
				CurMOPState = FMState;//����״̬
			}
			else//�������ת�ƾ��л�Ӣ�� ���߹���Ӣ��
			{
				Gotta = dynamic_cast<GPHero*>(CurSelectedHero);
				(CurSelectedHero = Heros[HeroNumber])->GetSelected();//�Ǽ���Ϣ ֪ͨӢ������ѡ���� ָʾ����������
			}
		}
		CurMOPState = FMState;//����״̬
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
			if (Inputs[i].EventType == MOUSE_EVENT)//����¼�
				HandleMouseInput(Inputs[i].Event.MouseEvent);
			else if (Inputs[i].EventType == KEY_EVENT)//�����¼�
				HandleKeyInput(Inputs[i].Event.KeyEvent);
		}
	}
}

//**********************************************************************************************
//*********************************�������������ڵ��õĺ���*************************************
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
	HeroStock[1].MoveSounds[0] = "��һ�ƶ�1.wav";
	HeroStock[1].MoveSounds[1] = "��һ�ƶ�2.wav";
	HeroStock[1].MoveSounds[2] = "��һ�ƶ�3.wav";
	HeroStock[1].MoveSounds[3] = "��һ�ƶ�4.wav";
	HeroStock[1].MoveSounds[4] = "��һ�ƶ�5.wav";
	HeroStock[1].MoveSounds[5] = "��һ�ƶ�6.wav";
	HeroStock[1].MoveSounds[6] = "��һ�ƶ�7.wav";
	HeroStock[1].MoveSounds[7] = "��һ�ƶ�8.wav";
	HeroStock[1].AttackSoundNum = 11;
	HeroStock[1].AttackSounds[0] = "��һ����1.wav";
	HeroStock[1].AttackSounds[1] = "��һ����2.wav";
	HeroStock[1].AttackSounds[2] = "��һ����3.wav";
	HeroStock[1].AttackSounds[3] = "��һ����4.wav";
	HeroStock[1].AttackSounds[4] = "��һ����5.wav";
	HeroStock[1].AttackSounds[5] = "��һ����6.wav";
	HeroStock[1].AttackSounds[6] = "��һ����7.wav";
	HeroStock[1].AttackSounds[7] = "��һ����8.wav";
	HeroStock[1].AttackSounds[8] = "��һ����9.wav";
	HeroStock[1].AttackSounds[9] = "��һ����10.wav";
	HeroStock[1].AttackSounds[10] = "��һ����11.wav";
}
void LoadHeroName()
{
	HeroStock[0].name = "����";
	HeroStock[1].name = "��һ����";
	HeroStock[2].name = "���ѧ��";
	HeroStock[3].name = "��������";
	HeroStock[4].name = "���Ĺǻ�";
}
void LoadHeroBaseAtttibuteStock()
{
	
	//{��Ӫ��ħ�������ף�Ѫ�����ޣ��������ޣ���ǰѪ������ǰ���������٣��﹥��ħ�������������٣��ͽ��;��飬(����ʱ��)��������Χ}
	//����
	GPBAttributeStock[0] = {Allies,0,0,0,5000,0,5000,0,0,0,0,0,0,0,0,0,0};
	//��һ����
	GPBAttributeStock[1] = { Allies,0,10,10,625,200,625,200,1,45,0,0,0.5,100,50,0,1};
	//���ѧ��
	GPBAttributeStock[2] = { Allies,1,0,0,400,200,400,200,1,70,25,0,1,60,50,0,4 };
	//��������
	GPBAttributeStock[3] = { Allies,2,5,5,525,200,525,200,1,65,20,10,0.5,100,50,0,2 };
	//���Ĺǻ�
	GPBAttributeStock[4] = { Allies,3,0,0,425,400,425,400,1,35,20,0,0.5,100,50,0,2 };
}
void LoadHeroIncAtttibuteStock()
{
	//{��Ӫ��ħ�������ף�Ѫ�����ޣ��������ޣ���ǰѪ������ǰ���������٣��﹥��ħ�������������٣��ͽ��;��飬(����ʱ��)��������Χ}
	//����
	GPIAtrributeStock[0] = { Allies,0,100,100,1000,0,1000,0,0,0,0,0,0,0,0,0,0 };
	//��һ����
	GPIAtrributeStock[1] = { Allies,0,4,4,60,20,60,20,0,0,1,1,0,0,0,0,0 };
	//���ѧ��
	GPIAtrributeStock[2] = { Allies,1,1,1,40,20,40,20,0,3,2,0,0.04,0,0,0,0 };
	//��������
	GPIAtrributeStock[3] = { Allies,2,3,2,50,20,50,20,0,2,2,0,0.03,0,0,0,0 };
	//���Ĺǻ�
	GPIAtrributeStock[4] = { Allies,3,1,1,40,50,40,50,0,1,5,0,0,0,0,0,0 };
}
void LoadHeroBaseSpecialStock()
{
	//{��Ѫ�ʣ������ʣ�����ٷֱ��ʣ�ħ���ٷֱ���}
	GPBSpecialStock[0];
}
void LoadHeroIncSpecialStock()
{
	//{��Ѫ�ʣ������ʣ�����ٷֱ��ʣ�ħ���ٷֱ���}
	GPISpecialStock[0];

}

void LoadSkillBaseStock()
{
	//�ⲿ��ȫ��������Ч�� ҪС��
	//�Եо�ʱ
	//{Enemy��0������ħ�����������ף�(Ѫ������)��(��������)��()��()���������٣������˺���ħ���˺��������������������٣�(�ͽ�)��(�;���)��(����ʱ��)������������Χ}
	//���Ѿ�ʱ
	//{Allies��0������ħ�������ӻ��ף�(Ѫ������)��(��������)�����ӵ�ǰѪ�������ӵ�ǰ�������������٣������﹥������ħ�������ӱ��������ӹ��٣�(�ͽ�)��(�;���)��(����ʱ��)�����ӹ�����Χ}
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
	GPSkillAttributeBStock[10] = { Allies,0,0,0,0,0,85,0,0,0,0,0,0,0,0,0,0 };// �ظ�Ѫ��
	GPSkillAttributeBStock[11] = { Enemy, 0, 0, 0, 0, 0, 0, 0, 0, 110, 0, 0, 0, 0, 0, 0, 2 }; //�����յ������Ĵ��
	GPSkillAttributeBStock[12] = { Allies,0,0,0,0,0,90,0,0,0,0,0,0,0,0,0,0 };// �ظ�Ѫ��
	GPSkillAttributeBStock[13] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[14] = EMPTY_ATTRIBUTE;
	GPSkillAttributeBStock[15] = { Enemy, 0, 2, 2, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0 }; // ����ħ������
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
	//�ⲿ��ȫ��������Ч�� ҪС��
	//�Եо�ʱ
	//{Enemy��������ħ�����������ף�(Ѫ������)��(��������)��()��()���������٣������˺���ħ���˺��������������������٣�(�ͽ�)��(�;���)��(����ʱ��)������������Χ}
	//���Ѿ�ʱ
	//{Allies������ħ�������ӻ��ף�(Ѫ������)��(��������)�����ӵ�ǰѪ�������ӵ�ǰ�������������٣������﹥������ħ�������ӱ��������ӹ��٣�(�ͽ�)��(�;���)��(����ʱ��)�����ӹ�����Χ}
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
	//�ⲿ��ȫ������ʱ�� ������ֵҲ��Ҫ̫�ߡ�
	
	//buff���Attribute
	//�Եо�ʱ
	//{Enemy�������ţ�������ħ�����������ף�����Ѫ�����ޣ������������ޣ�������ǰѪ����������ǰ�������������٣������﹥������ħ���������������������٣�(�ͽ�)��(�;���)������ʱ�䣬����������Χ}
	//���Ѿ�ʱ
	//{Allies������ħ�������ӻ��ף�����Ѫ�����ޣ����ӷ������ޣ����ӵ�ǰѪ�������ӵ�ǰ�������������٣������﹥������ħ�������ӱ��������ӹ��٣�(�ͽ�)��(�;���)������ʱ�䣬���ӹ�����Χ}
	
	//buff���special
	//�Եо�ʱ(һ�㲻�������Ч��)
	//{������Ѫ�ʣ����������ʣ���������ٷֱ��ʣ�����ħ���ٷֱ���}
	//���Ѿ�ʱ(���������)
	//{������Ѫ�ʣ����������ʣ���������ٷֱ��ʣ�����ħ���ٷֱ���}
	
	//�ܵ���˵   { (ʣ�����ʱ��),Attribute,Special,NULL,NULL}
	GPSkillBuffBStock[0] = EMPTY_BUFF;
	GPSkillBuffBStock[1] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,3,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffBStock[2] = EMPTY_BUFF;
	GPSkillBuffBStock[3] = EMPTY_BUFF;
	GPSkillBuffBStock[4] = { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,4,0 },EMPTY_SPECIAL,NULL,NULL };
	GPSkillBuffBStock[5] = { 0,EMPTY_ATTRIBUTE,{ 50,0,0,0 },NULL,NULL };
	GPSkillBuffBStock[6]=EMPTY_BUFF;
	GPSkillBuffBStock[7] = { 0,{ Allies,0,0,0,0,0,0,0,0,55,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; // ����
	GPSkillBuffBStock[8] = { 0,{ Allies,0,0,0,0,0,0,0,1,0,0,0,0,0,0,4,0 },EMPTY_SPECIAL,NULL,NULL }; //����
	GPSkillBuffBStock[9] = { 0,{ Allies,0,1,1,0,0,0,0,0,10,5,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; //ȫ����
	GPSkillBuffBStock[10]= EMPTY_BUFF;
	GPSkillBuffBStock[11]= EMPTY_BUFF;
	GPSkillBuffBStock[12]= EMPTY_BUFF;
	GPSkillBuffBStock[13]={ 0,{ Allies,0,0,0,0,0,0,0,0,60,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL }; // ������
	GPSkillBuffBStock[14]= { 0,{ Allies,0,2,2,0,0,0,0,0,15,10,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//������
	GPSkillBuffBStock[15]= EMPTY_BUFF;
	GPSkillBuffBStock[16]= { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,6,0 },EMPTY_SPECIAL,NULL,NULL };//����
	GPSkillBuffBStock[17]= { 0,{ Allies,0,0,0,0,0,0,0,0,0,0,30,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//������
	GPSkillBuffBStock[18]= { 0,{ Allies,0,3,3,0,0,0,0,0,20,15,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//������
	GPSkillBuffBStock[19]= { 0,{ Allies,0,0,0,0,0,0,0,0,70,0,0,0,0,0,5,0 },EMPTY_SPECIAL,NULL,NULL };//������
	GPSkillBuffBStock[20]= EMPTY_BUFF;
	GPSkillBuffBStock[21]= EMPTY_BUFF;
	GPSkillBuffBStock[22]== { 0, { Allies,0,0,0,0,0,0,0,1,0,0,0,0,0,0,6,0 }, EMPTY_SPECIAL, NULL, NULL };//����
	GPSkillBuffBStock[23]= EMPTY_BUFF;
}
void LoadSkillBuffIncStock()
{
	//�ⲿ��ȫ������ʱ�� ������ֵҲ��Ҫ̫�ߡ�

	//buff���Attribute
	//�Եо�ʱ
	//{Enemy������ħ�����������ף�����Ѫ�����ޣ������������ޣ�������ǰѪ����������ǰ�������������٣������﹥������ħ���������������������٣�(�ͽ�)��(�;���)������ʱ�䣬����������Χ}
	//���Ѿ�ʱ
	//{Allies������ħ�������ӻ��ף�����Ѫ�����ޣ����ӷ������ޣ����ӵ�ǰѪ�������ӵ�ǰ�������������٣������﹥������ħ�������ӱ��������ӹ��٣�(�ͽ�)��(�;���)������ʱ�䣬���ӹ�����Χ}

	//buff���special
	//�Եо�ʱ(һ�㲻�������Ч��)
	//{������Ѫ�ʣ����������ʣ���������ٷֱ��ʣ�����ħ���ٷֱ���}
	//���Ѿ�ʱ(���������)
	//{������Ѫ�ʣ����������ʣ���������ٷֱ��ʣ�����ħ���ٷֱ���}

	//�ܵ���˵   { (ʣ�����ʱ��),Attribute,Special,NULL,NULL}	
	//��buff���ܵ�һ���� 0 ��buff  1����buff
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

	GPSkillStock[0].name = "�ܲ�";
	GPSkillStock[0].CD = 10;
	GPSkillStock[0].EnergyConsume = 20;

	GPSkillStock[1].name = "ͻȻ��ͷ";
	GPSkillStock[1].CD = 15;
	GPSkillStock[1].EnergyConsume = 20;

	GPSkillStock[2].name = "�Լ���";
	GPSkillStock[2].CD = 20;
	GPSkillStock[2].EnergyConsume = 5;

	GPSkillStock[3].name = "��������";
	GPSkillStock[3].CD = 15;
	GPSkillStock[3].EnergyConsume = 20;

	GPSkillStock[4].name = "����";
	GPSkillStock[4].CD = 25;
	GPSkillStock[4].EnergyConsume = 30;

	GPSkillStock[5].name = "����Bug";
	GPSkillStock[5].CD = 20;
	GPSkillStock[5].EnergyConsume = 30;

	GPSkillStock[6].name = "��ױ";
	GPSkillStock[6].CD = 10;
	GPSkillStock[6].EnergyConsume = 20;

	GPSkillStock[7].name = "־�ҷܶ�";
	GPSkillStock[7].CD = 15;
	GPSkillStock[7].EnergyConsume = 25;

	GPSkillStock[8].name = "��Ь�ļӳ�";
	GPSkillStock[8].CD = 15;
	GPSkillStock[8].EnergyConsume = 25;

	GPSkillStock[9].name = "�����ľ���";
	GPSkillStock[9].CD = 20;
	GPSkillStock[9].EnergyConsume = 25;

	GPSkillStock[10].name = "����ǫ��";
	GPSkillStock[10].CD = 20;
	GPSkillStock[10].EnergyConsume = 20;

	GPSkillStock[11].name = "�޿ɷ��";
	GPSkillStock[11].CD = 25;
	GPSkillStock[11].EnergyConsume = 30;

	GPSkillStock[12].name = "���ĵļӳ�";
	GPSkillStock[12].CD = 20;
	GPSkillStock[12].EnergyConsume = 20;

	GPSkillStock[13].name = "���ߵĽ̻�";
	GPSkillStock[13].CD = 20;
	GPSkillStock[13].EnergyConsume = 30;

	GPSkillStock[14].name = "��ʷ���ն�";
	GPSkillStock[14].CD = 20;
	GPSkillStock[14].EnergyConsume = 30;

	GPSkillStock[15].name = "�������";
	GPSkillStock[15].CD = 20;
	GPSkillStock[15].EnergyConsume = 25;

	GPSkillStock[16].name = "���Ķ���";
	GPSkillStock[16].CD = 20;
	GPSkillStock[16].EnergyConsume = 25;

	GPSkillStock[17].name = "һ����ͧ";
	GPSkillStock[17].CD = 20;
	GPSkillStock[17].EnergyConsume = 25;

	GPSkillStock[18].name = "ʵϰ";
	GPSkillStock[18].CD = 15;
	GPSkillStock[18].EnergyConsume = 25;

	GPSkillStock[19].name = "��ʷ����";
	GPSkillStock[19].CD = 20;
	GPSkillStock[19].EnergyConsume = 25;

	GPSkillStock[20].name = "̸Ц����";
	GPSkillStock[20].CD = 20;
	GPSkillStock[20].EnergyConsume = 20;

	GPSkillStock[21].name = "����ս";
	GPSkillStock[21].CD = 20;
	GPSkillStock[21].EnergyConsume = 30;

	GPSkillStock[22].name = "ͼ��ͼɭ��";
	GPSkillStock[22].CD = 20;
	GPSkillStock[22].EnergyConsume = 30;

	GPSkillStock[23].name = "���·�";
	GPSkillStock[23].CD = 30;
	GPSkillStock[23].EnergyConsume = 30;
}

void LoadHeroStock()
{
	LoadHeroApperance();//����Ӣ����ɫ
	LoadHeroName();//����Ӣ������
	LoadHeroSound();//����Ӣ����Ч
	LoadSkillStock();//����Ӣ�ۼ���
					 //���ظ�����
	LoadHeroBaseAtttibuteStock();
	LoadHeroIncAtttibuteStock();
	LoadHeroBaseSpecialStock();
	LoadHeroIncSpecialStock();

	//Ӣ������
	for (int i = 1; i <= GP_STOCK; i++)//GP����
	{
		HeroStock[i].LoadReuseAttribute();//����ͨ������
		HeroStock[i].LoadBIAttribute(GPBAttributeStock[i], GPIAtrributeStock[i]);//���û������Ժ�����ֵ
		HeroStock[i].LoadBISpecial(GPBSpecialStock[i], GPISpecialStock[i]);//���û���������special
		for (int j = 0; j < MAX_HERO_SKILL_NUM; j++)//��ü���
			HeroStock[i].Skills[j] = &GPSkillStock[(i - 1)*MAX_HERO_SKILL_NUM + j + 1];
	}
	for (int i = 1; i <= AI_STOCK; i++)//AI����
	{
		MonsterStock[i].LoadReuseAttribute();//����ͨ������
		MonsterStock[i].LoadBIAttribute(AIBAttributeStock[i], AIIAttributeStock[i]);//���û������Ժ�����ֵ
		MonsterStock[i].LoadBISpecial(AIBSpecialStock[i], AIISpecialStock[i]);//���û���������special
		for (int j = 0; j < MAX_MONSTER_SKILL_NUM; j++)//��ü���
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
	//����Ϊ����װ��������
	/*
	1������ָ�׵�  ������50�㹥����  100 �飩
	2�����Ķ����   ������0.5���� ��ҪǮ��
	3��Eul����ʥ���� �������ƶ��ٶ� 1  100�飩
	4��Guinsoo��а������ �������������Ѫ��200 �������100  100�� ��
	5��˹�ε�֮�� �����ӹ����ٶ�0.5 120�飩
	6��÷��˹���ص��Ӷ� �����ӱ���30 60�� ��
	*/
	EquipmentStock[0].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,50,0,0,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "����ָ�׵�");
	EquipmentStock[0].StockNumber = 0;
	EquipmentStock[1].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,0,0,0,-0.5,0,0,0,0 }),new Special({ 0,0,0,0 }) }, "���Ķ����");
	EquipmentStock[1].StockNumber = 1;
	EquipmentStock[2].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,1,0,0,0,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "��Ь");
	EquipmentStock[2].StockNumber = 2;
	EquipmentStock[3].Set({ new Attribute({ Allies,0,0,0,200,100,200,100,0,0,0,0,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "�Ӻ�İ��");
	EquipmentStock[3].StockNumber = 3;
	EquipmentStock[4].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "�����");
	EquipmentStock[4].StockNumber = 4;
	EquipmentStock[5].Set({ new Attribute({ Allies,0,0,0,0,0,0,0,0,0,0,30,0,100,0,0,0 }),new Special({ 0,0,0,0 }) }, "���ĸ���");
	EquipmentStock[5].StockNumber = 5;

}
void LoadConsumableStock()
{
	// ����Ϊ��������Ʒ������
	/*
	1������ �����Ѿ�ÿ��ظ�Ѫ��20�� ����5s��20�飩
	2������ ÿ��ָ�����20�� ����5s��30�飩
	3���óԵ������ ˲��ָ�����80�� ��30�飩
	4��άC���ʲ� ˲��ָ�Ѫ��80�� ����60�㣨40�飩
	5������ �����������ٶ�0.5 ����10s ��50�飩
	6��������� ������������50�� ����10s ��40�飩
	*/
	ConsumableStock[0].SetConsumable(true, new Buff({ 5,{ Allies,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "����");
	ConsumableStock[0].StockNumber = 0;
	ConsumableStock[1].SetConsumable(true, new Buff({ 5, { Allies,0,0,0,0,0,0,20,0,0,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "����");
	ConsumableStock[1].StockNumber = 1;
	ConsumableStock[2].SetConsumable(false, new Buff({ 0, { Allies,0,0,0,0,0,0,80,0,0,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "�óԵ������");
	ConsumableStock[2].StockNumber = 2;
	ConsumableStock[3].SetConsumable(false, new Buff({ 0, { Allies,0,0,0,0,0,80,60,0,0,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "άC���ʲ�");
	ConsumableStock[3].StockNumber = 3;
	ConsumableStock[4].SetConsumable(false, new Buff({ 10, { Allies,0,0,0,0,0,0,0,0,0,0,0,0.5,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "����");
	ConsumableStock[4].StockNumber = 4;
	ConsumableStock[5].SetConsumable(false, new Buff({ 10, { Allies,0,0,0,0,0,0,0,0,50,0,0,0,0,0,0,0 }, EMPTY_SPECIAL, NULL, NULL }), "�������");
	ConsumableStock[5].StockNumber = 5;
}
void LoadCitadel()
{
	GPHero* Citadel = &HeroStock[0];
	Heros[0] = Citadel;//�����¼
	Citadel->number = 0;//���ñ��
	Citadel->camp = Allies;//������Ӫ
	for (short y = BATTLE_HEIGHT / 2 - 1; y <= BATTLE_HEIGHT / 2 + 1; y++)//�������Ǵ���ש����Ϣ
	{
		FillConsoleOutputAttribute(hOut, CitadelColor, 3, { BATTLE_WIDTH / 2 - 1,y }, &num);//ͿĨ���ǵ���ɫ
		for (short x = BATTLE_WIDTH / 2 - 1; x <= BATTLE_WIDTH / 2 + 1; x++)//����ש����Ϣ
		{
			Active[x][y].Occupied = true;
			Active[x][y].UnitCamp = Empty;
			Active[x][y].OccupyingUnit = Citadel;
		}
	}
	AttackMsg[0] = CreateEvent(NULL, true, false, NULL);//��ʼ���ɼ�⹥��
	BuffMsg[Allies][0] = CreateEvent(NULL, true, false, NULL);//��ʼ��buff
	SkillCDMsg[Allies][0] = CreateEvent(NULL, true, false, NULL);//��ʼ�޼��ܴ���CD
	MoveMsg[0] = CreateEvent(NULL, true, false, NULL);//��ʼδ�ƶ�
	ChaseMsg[0] = CreateEvent(NULL, true, false, NULL);//��ʼδ׷��
	CloseHandle((HANDLE)_beginthreadex(NULL, 0, LoadHero, (void*)Citadel, 0, NULL));//ΪӢ�۴����߳� Ͷ��ʹ��
	CurSelectedHero = Citadel;
	Shop = Citadel;
	CurSelectedHero->GetSelected();
	
	
}
void LoadDivider()
{
	FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, BATTLE_WIDTH, { 0,BATTLE_AREA }, &num);//����ս�����ս���ķֽ���
	FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, BATTLE_WIDTH - INFO_FUNCTION, { INFO_FUNCTION,BATTLE_AREA + THING_HEIGHT_CHAR + 1 }, &num);//����������Ʒ���ֽ���

	for (short y = BATTLE_AREA + 1; y < SCREEN_HEIGHT; y++)
	{
		for (short x = INFO_FUNCTION; x < SCREEN_WIDTH; x += 11)
			FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, 1, { x,y }, &num);//���ع�������ֱ�ֽ���
		FillConsoleOutputAttribute(hOut, DIVIDER_COLOR, 1, { IMAGE_INFO,y }, &num);
	}
}
void ShowMainMenu()
{

}
void InitialWindow()
{
	//��ȡ���־��
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hIn = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleTitle("ħ�޽���ʷ");
	hwnd = FindWindow(NULL, "ħ�޽���ʷ");
	hdc = GetDC(hwnd);
	hmendc = CreateCompatibleDC(hdc);
	hBlackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//hmutex[camp][number] = CreateMutex(NULL, false, NULL);

	//��ʼ����Ļ��Ϣ
	GetConsoleScreenBufferInfo(hOut, &csbi);//�����Ļ��Ϣ
	GetConsoleMode(hIn, &OldConsoleInputMode);//��ȡԭʼ����ģʽ
	NewConsoleInputMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | OldConsoleInputMode;//��ԭ��������������������
	SetConsoleMode(hIn, NewConsoleInputMode);//�����µ�����ģʽ
	


	SetConsoleDisplayMode(hOut, CONSOLE_FULLSCREEN_MODE, NULL);//����ȫ��
	GetConsoleCursorInfo(hOut, &cursorInfo);//���ԭʼ�����Ϣ
	cursorInfo.bVisible = false;//�������
	SetConsoleCursorInfo(hOut, &cursorInfo);//��Ϊ���ɼ�
}
void InitialGame()
{
	//��ʼ������״̬��
	FMState = new FormalState;
	SMState = new SkillingState;
	TMState = new TransportingState;
	PMState = new ShoppingState;
	CurMOPState = PMState;
	TmpMOPState = PMState;

	//��ʼ��С��
	isShowingHero = true;
	CurNum[Allies] = 0;
	CurNum[Enemy] = 0;
	money = 5000;
	CurHeroPrice = 0;
	
	//��ʼ���ź��� ������
	Fighting = CreateEvent(NULL, true, false, NULL);
	EndFighting = CreateEvent(NULL, true, true, NULL);
	PRINTF_MUTEX = CreateMutex(NULL, false, NULL);

	//���ر�������
	LoadBackgroundSound();
	//����װ����
	LoadEquipmentStock();
	//��������Ʒ��
	LoadConsumableStock();
	//����Ӣ�ۿ�
	LoadHeroStock();
	//���طֽ���
	LoadDivider();
	//���ش�Ӫ �̵� Ҳ��0��Ӣ��
	LoadCitadel();
	//������Ϸ������ʱ��
	LoadTimer();
	
}
