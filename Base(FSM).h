#ifndef BASE_H
#define BASE_H


#include<Windows.h>
#include<string>
#include<typeinfo>
#include<atomic>
#include<time.h>
#include<process.h>
#include<stdlib.h>
#include<typeinfo>
#pragma comment(lib, "winmm.lib")
using namespace std;
const int MAX_HERO_SKILL_NUM = 6;
const int MAX_HERO_LEVEL = 10;
const int MAX_THING_NUM_H=6;
const int MAX_MOVE_SOUND_NUM=8;
const int MAX_ATTACK_SOUND_NUM=8;
enum STATE{NORMAL,SLEEP,POISON,VERTIGO,DEATH};
enum RACE{HUMAN,ORC,NIGHYELF,UNDEAD};
enum TYPE{SKILL,CONSUMABLE,EQUIPMENT};
enum CAMP {Allies, Enemy ,MAX_CAMP_NUM, Empty,};//友方阵营还是敌方阵营
class Hero;
class GPHero;
class AIHero;

//鼠标有限状态机
class MouseOperateState
{
protected:
	virtual void ShowDetail(int FTYPE, int REALINDEX);
	virtual void TriggerFunction(COORD Destination) {};
	virtual void SolveMouseReleased(COORD Destination) = 0;
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent) = 0;
	static bool LeftButtonPressed;
};
class FormalState :virtual public MouseOperateState
{
	virtual void TriggerFunction(COORD Destination);
	virtual void SolveMouseReleased(COORD Destination) ;
	virtual void SolveMouseMoved(COORD MovedLoc) ;
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
};
class SkillingState:virtual public MouseOperateState
{
	virtual void SolveMouseReleased(COORD Destination);
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
};
class TransportingState :virtual public MouseOperateState
{
	virtual void SolveMouseReleased(COORD Destination);
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
};
class ShoppingState:virtual public MouseOperateState
{
	virtual void ShowDetail(int FTYPE, int REALINDEX);
	virtual void TriggerFunction(COORD Destination);
	virtual void SolveMouseReleased(COORD Destination);
	virtual void SolveMouseMoved(COORD MovedLoc);
public:
	virtual void SolveMouseInput(MOUSE_EVENT_RECORD NewEvent);
};

//AI有限状态机
class AIState
{
protected:
	AIHero* Object;
	SYSTEMTIME BeginTest;
	SYSTEMTIME EndTest;
	COORD LastDestination;
public:
	virtual void Act()=0;
};
class AIStillState:virtual public AIState
{
public:
	bool JustAttacked;//是否刚被攻击
	virtual void Act();
};
class AIMoveState :virtual public AIState
{
public:
	virtual void Act();
};
class AIPChaseState:virtual public AIState
{
public:
	virtual void Act();
};
class AINChaseState :virtual public AIState
{
public:
	virtual void Act();
};
//*********************************************************************************************
//********************************以下是寻路数据结构*******************************************
//*********************************************************************************************
class Astar
{
public:
	Astar * Father;
	Astar* Next;
	COORD Loc;
	bool IsPath;
	int F;
	int G;
	int H;
	Astar(Astar* father, COORD loc, COORD des);
};
class Aector
{
	enum { AECTOR_DEFAULT_SIZE = 20 };
	int CurMaxSize;
	int CurSize;
	Astar** Content;
public:
	Aector();
	~Aector();
	void Add(Astar* NewSatar);
	bool find(COORD Loc);
	void ReAector();
	void Clean();
};
class MinHeap
{
	enum { MINHEAP_DEFAULT_SIZE = 50 };
	Astar** Content;
	int CurMaxSize;
	int CurSize;
	void Swap(int i, int j);
	int FoundIndex;
public:
	MinHeap();
	~MinHeap();
	void insert(Astar* NewAstar);
	void HeapifyUp(int index);
	void HeapifyDown(int index);
	void Heapify();
	Astar* remove();
	Astar* find(COORD);
	void ReHeap();
	void Clean();
};

//该结构记录方格信息
struct BRICK_INFO
{
	bool Occupied;//是否被单位占据
	CAMP UnitCamp;//占据单位的阵营
	Hero* OccupyingUnit;//占据的单位
};

//以下是效果结构
struct Attribute
{
	CAMP Camp;//阵营  或者效果的作用阵营
	int Number;//自己在阵营内的编号
	int Md;//魔抗
	int Pd;//护甲
	int MaxBlood;//当前最大血量
	int MaxEnergy;//当前最大能量
	int Blood;//当前血量
	int Energy;//能量
	int Speed;//速度
	int Pa;//物理输出
	int Ma;//魔法输出
	int CrRate;//暴击率
	double Frequence;//攻击速率 
	

	int RewardM;//杀死的赏金
	int  RewardE;//杀死的经验

	int LastTime;//持续时间 为0说明是一次性效果
	int AttackRange;//攻击范围 
};
struct Special
{
	int SuckBlood;
	int SuckMagic;
	int PhysicalPercent;
	int MagicPercent;
};
struct Injury
{
	Attribute* BaseAttack;
	Special* special;
};
struct Buff {
	int TimeLeft;//剩余持续时间
	Attribute Effection;
	Special special;
	Buff* Prev;
	Buff* Next;
};

//以下是物品类
class Skill
{
	Attribute BaseValue;//基础值
	Attribute IncValue;//增长值
	Buff BaseBValue;//基础值
	Buff IncBValue;//增长值
	int level;
public:
	Hero * Owner;//拥有者
	string name;
	Attribute * Effection;
	Buff* buff;//如果不是buff就设为null
	int StockNumber;
	int index;//在英雄技能栏中的位置
	bool JustFlushed;//刚好被刷新
	int CD;//技能CD
	int LastCD;//剩余CD
	int EnergyConsume;//能量消耗
	double ADR;//技能AD加成
	double APR;//技能AP加成
	int Range() { return Effection->AttackRange; }
	void LevelUp();
	void SetLevel(int DirectLevel);
	void PrintName();
	void SetSkill(Attribute basevalue, Attribute incvalue, Buff baseBvalue, Buff incBvalue);
	Skill() { Effection = new Attribute; buff = new Buff; }
};
class Equipment
{
	Injury EquipEffection;
public:
	int StockNumber;
	string name;
	Injury GetEffection() { return EquipEffection; }
	void PrintName(int index);
	Equipment() {};
	void Set(Injury, string);
};
class Consumable
{
	Buff* ConsumableEffetion;//消耗品效果
public:
	bool Range;
	int StockNumber;
	string name;
	Buff* Effect() { return ConsumableEffetion; }
	CAMP EffectionCamp() { return ConsumableEffetion->Effection.Camp; }
	void PrintName(int index);
	void PrintName(int index,int);//这是给强化书的版本
	void SetConsumable(bool range, Buff* effectionC, string Name) { ConsumableEffetion = effectionC; Range = range; name = Name; }
};

//以下是英雄类
class Hero 
{
protected:
	int CurExperical;//当前的经验值
	int ExpercialNeeded;//升级所需经验值
	Attribute BaseAttribute;//0级的属性
	Attribute IncAttribute;//每次升级增加的属性
	Special BaseSpecial;
	Special IncSpecial;
public:
	//该部分成员需要在每次重生时初始化
	int number;//英雄在本阵营的编号
	bool dead;//是否已经死亡
	COORD KerLoc;//标记其内核位置
	COORD Destination;//标记其目的地
	Skill* Skills[MAX_THING_NUM_H];//英雄的技能
	Equipment* Equipments[MAX_THING_NUM_H];//英雄的装备
	Attribute uAttribute;//英雄的基础属性
	Special special;//英雄的特殊效果 要挨个手动初始化
	int level;//英雄等级
	int LeftSkillPoint;//剩余的技能点
	Buff* Head;
	Buff* Rear;
	Hero* HeroToChase;//要追逐的对象

	//该部分成员只需在游戏开始时初始化
	int StockNumber;//英雄在库中的编号
	DWORD Apperance;//英雄的外观 要挨个手动初始化
	string name;//英雄名字
	string SelectedSound;//被选择音效
	string DieSound;//死亡音效
	CAMP camp;//英雄阵营

	///该部分是AI与GP共有的方法
	bool FindPath();
	void Jmp(COORD NextKerLoc);
	bool GetEquipment(Equipment* NewEquipment);
	void PrintSelf();//在KerLoc处打印自己
	void PrintInformation();//显示英雄信息
	void PrintImage();//显示头像
	void PrintHappy();
	void PrintGeneral();
	void PrintSad();
	void EraseSelf();//在KerLoc处抹去自己
	void ShowSelf();//在KerLoc处显示自己
	void SuckBlood(int blood);//主要是用于吸血
	void SuckEnergy(int magic);//主要是用于吸蓝
	void GetEquipmentEffection(Injury EquipmentEffection);//获得装备效果
	void GetEffectedByBuff(Buff*);//获得技能 消耗品的效果影响
	void GetSkillEffection(Skill* skill);//受到技能效果
	void LoseEquipment(int index);//失去装备
	void GetInjuried(Hero* Attacker);//受到伤害
	void GetSlowRecovery(Attribute& ThingEff);//因为回复效果来自消耗品 技能 因此大多驻留在内存中 可以传引用
	void LoadBIAttribute(Attribute Base, Attribute Inc);//加载基础和增长属性 仅在游戏开始时调用
	void LoadBISpecial(Special Base, Special Inc);

	///该部分是虚方法
	virtual void GetSelected();
	virtual void LoadReuseAttribute();//加载重利用属性 仅在游戏开始时调用
	virtual void Operating() = 0;//运行函数 英雄依次为主体
	virtual void PrintFunction() = 0;//
	virtual void Rebrith()=0;//重生
	virtual void Die() = 0;//死亡
	virtual void GenerateReward() = 0;//获得奖励

	Hero() {};
	virtual~Hero() {};
};
class GPHero:virtual public Hero
{
	virtual void Rebrith();//英雄重生
	virtual void Die();//英雄死亡
public:
	///以下是GP特有的成员
	//该部分每次重生时需要初始化
	Consumable * Consumables[MAX_THING_NUM_H];//英雄的消耗品
	Consumable* EnhanceBooks[MAX_THING_NUM_H];//商店卖的强化书
	bool isChasing;//是否正在跟随

	//该部分仅在游戏开始初始化
	int MoveSoundNum;//移动音效数量
	int AttackSoundNum;//攻击音效数量
	string MoveSounds[MAX_MOVE_SOUND_NUM];//移动音效
	string AttackSounds[MAX_ATTACK_SOUND_NUM];//攻击音效
	string AttackedSound;//受到攻击音效
	string BoughtSound;//购买音效
	
	///以下是GP特有的方法
	void LevelUp();
	void MoveTo(COORD destination);
	void TransportEquipTo(int HeroIndex);
	void TransportConsumableTo(int HeroIndex);
	void LoseConsumable(int index);//失去消耗品
	bool GetConsumable(Consumable* NewConsumable);//得到消耗品
	void UseConsumable(int index);
	void GetExperical(int experical);//获得经验
	
	///以下是虚方法
	virtual void GetSelected();
	virtual void LoadReuseAttribute();//初始化时设置重利用属性 仅在游戏开始时调用
	virtual void Operating();//这是给友军用的
	virtual void PrintFunction();//
	virtual void GenerateReward();
	

	GPHero() {};
	virtual~GPHero() {};
};
class AIHero :virtual public Hero
{
	virtual void Rebrith();//辅导员重生
	virtual void Die();//辅导员死亡
public:
	///以下是AI特有的成员
	//该部分每次重生时需要初始化
	AIState* CurAIState;
	AIState* TmpAIState;
	
	//该部分仅在游戏开始初始化

	///以下是GP特有的方法
	void SetRebrithLevel(int NewLevel);

	///以下是虚方法
	virtual void GetSelected();
	virtual void LoadReuseAttribute();//初始化时设置重利用属性 仅在游戏开始时调用
	virtual void Operating();
	virtual void PrintFunction();//
	virtual void GenerateReward();
	
	
	AIHero() {};
	virtual~AIHero() {};
};
#endif // !BASE_H