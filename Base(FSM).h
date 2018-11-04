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
enum CAMP {Allies, Enemy ,MAX_CAMP_NUM, Empty,};//�ѷ���Ӫ���ǵз���Ӫ
class Hero;
class GPHero;
class AIHero;

//�������״̬��
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

//AI����״̬��
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
	bool JustAttacked;//�Ƿ�ձ�����
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
//********************************������Ѱ·���ݽṹ*******************************************
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

//�ýṹ��¼������Ϣ
struct BRICK_INFO
{
	bool Occupied;//�Ƿ񱻵�λռ��
	CAMP UnitCamp;//ռ�ݵ�λ����Ӫ
	Hero* OccupyingUnit;//ռ�ݵĵ�λ
};

//������Ч���ṹ
struct Attribute
{
	CAMP Camp;//��Ӫ  ����Ч����������Ӫ
	int Number;//�Լ�����Ӫ�ڵı��
	int Md;//ħ��
	int Pd;//����
	int MaxBlood;//��ǰ���Ѫ��
	int MaxEnergy;//��ǰ�������
	int Blood;//��ǰѪ��
	int Energy;//����
	int Speed;//�ٶ�
	int Pa;//�������
	int Ma;//ħ�����
	int CrRate;//������
	double Frequence;//�������� 
	

	int RewardM;//ɱ�����ͽ�
	int  RewardE;//ɱ���ľ���

	int LastTime;//����ʱ�� Ϊ0˵����һ����Ч��
	int AttackRange;//������Χ 
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
	int TimeLeft;//ʣ�����ʱ��
	Attribute Effection;
	Special special;
	Buff* Prev;
	Buff* Next;
};

//��������Ʒ��
class Skill
{
	Attribute BaseValue;//����ֵ
	Attribute IncValue;//����ֵ
	Buff BaseBValue;//����ֵ
	Buff IncBValue;//����ֵ
	int level;
public:
	Hero * Owner;//ӵ����
	string name;
	Attribute * Effection;
	Buff* buff;//�������buff����Ϊnull
	int StockNumber;
	int index;//��Ӣ�ۼ������е�λ��
	bool JustFlushed;//�պñ�ˢ��
	int CD;//����CD
	int LastCD;//ʣ��CD
	int EnergyConsume;//��������
	double ADR;//����AD�ӳ�
	double APR;//����AP�ӳ�
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
	Buff* ConsumableEffetion;//����ƷЧ��
public:
	bool Range;
	int StockNumber;
	string name;
	Buff* Effect() { return ConsumableEffetion; }
	CAMP EffectionCamp() { return ConsumableEffetion->Effection.Camp; }
	void PrintName(int index);
	void PrintName(int index,int);//���Ǹ�ǿ����İ汾
	void SetConsumable(bool range, Buff* effectionC, string Name) { ConsumableEffetion = effectionC; Range = range; name = Name; }
};

//������Ӣ����
class Hero 
{
protected:
	int CurExperical;//��ǰ�ľ���ֵ
	int ExpercialNeeded;//�������辭��ֵ
	Attribute BaseAttribute;//0��������
	Attribute IncAttribute;//ÿ���������ӵ�����
	Special BaseSpecial;
	Special IncSpecial;
public:
	//�ò��ֳ�Ա��Ҫ��ÿ������ʱ��ʼ��
	int number;//Ӣ���ڱ���Ӫ�ı��
	bool dead;//�Ƿ��Ѿ�����
	COORD KerLoc;//������ں�λ��
	COORD Destination;//�����Ŀ�ĵ�
	Skill* Skills[MAX_THING_NUM_H];//Ӣ�۵ļ���
	Equipment* Equipments[MAX_THING_NUM_H];//Ӣ�۵�װ��
	Attribute uAttribute;//Ӣ�۵Ļ�������
	Special special;//Ӣ�۵�����Ч�� Ҫ�����ֶ���ʼ��
	int level;//Ӣ�۵ȼ�
	int LeftSkillPoint;//ʣ��ļ��ܵ�
	Buff* Head;
	Buff* Rear;
	Hero* HeroToChase;//Ҫ׷��Ķ���

	//�ò��ֳ�Աֻ������Ϸ��ʼʱ��ʼ��
	int StockNumber;//Ӣ���ڿ��еı��
	DWORD Apperance;//Ӣ�۵���� Ҫ�����ֶ���ʼ��
	string name;//Ӣ������
	string SelectedSound;//��ѡ����Ч
	string DieSound;//������Ч
	CAMP camp;//Ӣ����Ӫ

	///�ò�����AI��GP���еķ���
	bool FindPath();
	void Jmp(COORD NextKerLoc);
	bool GetEquipment(Equipment* NewEquipment);
	void PrintSelf();//��KerLoc����ӡ�Լ�
	void PrintInformation();//��ʾӢ����Ϣ
	void PrintImage();//��ʾͷ��
	void PrintHappy();
	void PrintGeneral();
	void PrintSad();
	void EraseSelf();//��KerLoc��Ĩȥ�Լ�
	void ShowSelf();//��KerLoc����ʾ�Լ�
	void SuckBlood(int blood);//��Ҫ��������Ѫ
	void SuckEnergy(int magic);//��Ҫ����������
	void GetEquipmentEffection(Injury EquipmentEffection);//���װ��Ч��
	void GetEffectedByBuff(Buff*);//��ü��� ����Ʒ��Ч��Ӱ��
	void GetSkillEffection(Skill* skill);//�ܵ�����Ч��
	void LoseEquipment(int index);//ʧȥװ��
	void GetInjuried(Hero* Attacker);//�ܵ��˺�
	void GetSlowRecovery(Attribute& ThingEff);//��Ϊ�ظ�Ч����������Ʒ ���� ��˴��פ�����ڴ��� ���Դ�����
	void LoadBIAttribute(Attribute Base, Attribute Inc);//���ػ������������� ������Ϸ��ʼʱ����
	void LoadBISpecial(Special Base, Special Inc);

	///�ò������鷽��
	virtual void GetSelected();
	virtual void LoadReuseAttribute();//�������������� ������Ϸ��ʼʱ����
	virtual void Operating() = 0;//���к��� Ӣ������Ϊ����
	virtual void PrintFunction() = 0;//
	virtual void Rebrith()=0;//����
	virtual void Die() = 0;//����
	virtual void GenerateReward() = 0;//��ý���

	Hero() {};
	virtual~Hero() {};
};
class GPHero:virtual public Hero
{
	virtual void Rebrith();//Ӣ������
	virtual void Die();//Ӣ������
public:
	///������GP���еĳ�Ա
	//�ò���ÿ������ʱ��Ҫ��ʼ��
	Consumable * Consumables[MAX_THING_NUM_H];//Ӣ�۵�����Ʒ
	Consumable* EnhanceBooks[MAX_THING_NUM_H];//�̵�����ǿ����
	bool isChasing;//�Ƿ����ڸ���

	//�ò��ֽ�����Ϸ��ʼ��ʼ��
	int MoveSoundNum;//�ƶ���Ч����
	int AttackSoundNum;//������Ч����
	string MoveSounds[MAX_MOVE_SOUND_NUM];//�ƶ���Ч
	string AttackSounds[MAX_ATTACK_SOUND_NUM];//������Ч
	string AttackedSound;//�ܵ�������Ч
	string BoughtSound;//������Ч
	
	///������GP���еķ���
	void LevelUp();
	void MoveTo(COORD destination);
	void TransportEquipTo(int HeroIndex);
	void TransportConsumableTo(int HeroIndex);
	void LoseConsumable(int index);//ʧȥ����Ʒ
	bool GetConsumable(Consumable* NewConsumable);//�õ�����Ʒ
	void UseConsumable(int index);
	void GetExperical(int experical);//��þ���
	
	///�������鷽��
	virtual void GetSelected();
	virtual void LoadReuseAttribute();//��ʼ��ʱ�������������� ������Ϸ��ʼʱ����
	virtual void Operating();//���Ǹ��Ѿ��õ�
	virtual void PrintFunction();//
	virtual void GenerateReward();
	

	GPHero() {};
	virtual~GPHero() {};
};
class AIHero :virtual public Hero
{
	virtual void Rebrith();//����Ա����
	virtual void Die();//����Ա����
public:
	///������AI���еĳ�Ա
	//�ò���ÿ������ʱ��Ҫ��ʼ��
	AIState* CurAIState;
	AIState* TmpAIState;
	
	//�ò��ֽ�����Ϸ��ʼ��ʼ��

	///������GP���еķ���
	void SetRebrithLevel(int NewLevel);

	///�������鷽��
	virtual void GetSelected();
	virtual void LoadReuseAttribute();//��ʼ��ʱ�������������� ������Ϸ��ʼʱ����
	virtual void Operating();
	virtual void PrintFunction();//
	virtual void GenerateReward();
	
	
	AIHero() {};
	virtual~AIHero() {};
};
#endif // !BASE_H