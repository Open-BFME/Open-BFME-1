// ?d_00222640@@YAXXZ
// partial score=0.92 date=2026-09-24
// ?dispatch@Rva00222640Owner@@QAEXPAX@Z present-unmatched
// cl: /DNDEBUG /MD /EHs-c-
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>


typedef bool Bool;

class Object;
class DamageInfo;

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *object, const DamageInfo *damageInfo) const;
};

class BfmeXCQE
{
};

class GameLogic
{
public:
	void destroyObject(Object *object);
};

extern const float BfmeZeroRange;
extern GameLogic *TheBfmeGameLogic;
extern void j_00008337();
extern void j_0001d0de();
extern void j_000357d8();

struct Rva00222640Context
{
	unsigned char m_pad000[0x13c];
	float m_value;
	unsigned char m_pad140[0x12];
	unsigned char m_enabled;
};

class Rva00222640Probe
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
#undef S
	virtual int check();
};

class Rva00222640Activate
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
#undef S
	virtual BfmeXCQE *check(int value);
};

class Rva00222640BaseA
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29)
	S(30) S(31) S(32) S(33) S(34) S(35) S(36)
	virtual void finish(int value);
	S(38) S(39)
	S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47) S(48) S(49)
	S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59)
	S(60) S(61) S(62) S(63) S(64) S(65) S(66) S(67) S(68) S(69)
	S(70) S(71) S(72) S(73) S(74) S(75) S(76)
#undef S
	virtual void notify(void);
};

class Rva00222640BaseB
{
public:
#define S(n) virtual void slot##n();
	S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9)
	S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19)
	S(20) S(21) S(22) S(23)
#undef S
	virtual void notify(void);
};

struct Rva00222640ListNode
{
	Rva00222640ListNode *m_next;
	Rva00222640ListNode *m_prev;
	Rva00222640Probe *m_value;
};

class Rva00222640Owner
{
public:
	void dispatch(void *arg);

private:
	unsigned char m_pad00[0x10];
	_STL::list<Rva00222640Probe *> m_nodes;
	unsigned char m_pad14[0x7c];
	unsigned char m_flag;
};

void Rva00222640Owner::dispatch(void *arg)
{
	const void *key = *(const void **)((const char *)this - 0x20);
	Rva00222640Context *context = *(Rva00222640Context **)((const char *)this - 0x24);
	Rva00222640Owner *owner = this;
	m_flag = 1;
	typedef Bool (DieMuxData::*AskFunction)(const Object *, const DamageInfo *) const;
	union { void (*raw)(void); AskFunction member; } ask;
	ask.raw = j_000357d8;
	if (!(reinterpret_cast<DieMuxData *>((char *)context + 8)->*ask.member)(
		(const Object *)key, (const DamageInfo *)arg))
		return;

	context = *(Rva00222640Context **)((const char *)owner - 0x24);
	if (context->m_enabled != 0)
	{
		if (context->m_value > BfmeZeroRange)
			((Rva00222640BaseA *)((char *)owner - 8))->notify();
		Rva00222640BaseB *second = (Rva00222640BaseB *)((char *)owner - 0x28);
		second->notify();
		return ((Rva00222640BaseA *)((char *)owner - 8))->finish(0);
	}

	Rva00222640ListNode *head =
		*(Rva00222640ListNode **)&m_nodes;
	Rva00222640ListNode *node = head->m_next;
	while (node != head)
	{
		Rva00222640Probe *probe = node->m_value;
		node = node->m_next;
		if (probe != 0)
		{
			if (probe->check() != 0)
			{
				Rva00222640Activate *activate = (Rva00222640Activate *)probe;
				BfmeXCQE *result = activate->check(1);
				typedef void (BfmeXCQE::*RunFunction)(void);
				union { void (*raw)(void); RunFunction member; } run;
				run.raw = j_00008337;
				(reinterpret_cast<BfmeXCQE *>(result)->*run.member)();
			}
			typedef void (GameLogic::*DestroyFunction)(Object *);
			union { void (*raw)(void); DestroyFunction member; } destroy;
			destroy.raw = j_0001d0de;
			(TheBfmeGameLogic->*destroy.member)((Object *)probe);
		}
	}
}
