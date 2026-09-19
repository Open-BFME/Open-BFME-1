// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: HordeContain member command walk, retail 0x00243C40.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>


class Object;

enum CommandSourceType
{
	Rva00243C40CommandSourceAI = 2
};

class AICommandInterface
{
public:
	void aiAttackObject(Object *object, Int maxShots,
		CommandSourceType source);
};

class BfmeInnerCPB
{
public:
	void bfmeOneCPB(Int one, Int two);
};

class AIUpdateInterface
{
public:
#define AI_SLOT(N) virtual Int slot##N() = 0
	AI_SLOT(00); AI_SLOT(01); AI_SLOT(02); AI_SLOT(03); AI_SLOT(04);
	AI_SLOT(05); AI_SLOT(06); AI_SLOT(07); AI_SLOT(08); AI_SLOT(09);
	AI_SLOT(10); AI_SLOT(11); AI_SLOT(12); AI_SLOT(13); AI_SLOT(14);
	AI_SLOT(15); AI_SLOT(16); AI_SLOT(17); AI_SLOT(18); AI_SLOT(19);
	AI_SLOT(20); AI_SLOT(21); AI_SLOT(22); AI_SLOT(23); AI_SLOT(24);
	AI_SLOT(25); AI_SLOT(26); AI_SLOT(27); AI_SLOT(28); AI_SLOT(29);
	AI_SLOT(30); AI_SLOT(31); AI_SLOT(32); AI_SLOT(33); AI_SLOT(34);
	AI_SLOT(35); AI_SLOT(36); AI_SLOT(37); AI_SLOT(38); AI_SLOT(39);
	AI_SLOT(40); AI_SLOT(41); AI_SLOT(42); AI_SLOT(43); AI_SLOT(44);
	AI_SLOT(45); AI_SLOT(46); AI_SLOT(47); AI_SLOT(48); AI_SLOT(49);
	AI_SLOT(50); AI_SLOT(51); AI_SLOT(52); AI_SLOT(53); AI_SLOT(54);
	AI_SLOT(55); AI_SLOT(56); AI_SLOT(57); AI_SLOT(58); AI_SLOT(59);
	AI_SLOT(60); AI_SLOT(61); AI_SLOT(62); AI_SLOT(63); AI_SLOT(64);
	AI_SLOT(65); AI_SLOT(66); AI_SLOT(67); AI_SLOT(68); AI_SLOT(69);
	AI_SLOT(70); AI_SLOT(71); AI_SLOT(72); AI_SLOT(73); AI_SLOT(74);
	AI_SLOT(75); AI_SLOT(76); AI_SLOT(77); AI_SLOT(78); AI_SLOT(79);
	AI_SLOT(80); AI_SLOT(81); AI_SLOT(82); AI_SLOT(83); AI_SLOT(84);
	AI_SLOT(85); AI_SLOT(86); AI_SLOT(87); AI_SLOT(88); AI_SLOT(89);
	AI_SLOT(90); AI_SLOT(91); AI_SLOT(92); AI_SLOT(93); AI_SLOT(94);
	AI_SLOT(95); AI_SLOT(96);
	virtual Bool isAttacking() const = 0;
	AI_SLOT(98);
	virtual Bool slot99() const = 0;
	AI_SLOT(100); AI_SLOT(101); AI_SLOT(102); AI_SLOT(103); AI_SLOT(104);
	AI_SLOT(105); AI_SLOT(106); AI_SLOT(107); AI_SLOT(108); AI_SLOT(109);
	AI_SLOT(110); AI_SLOT(111); AI_SLOT(112); AI_SLOT(113); AI_SLOT(114);
	AI_SLOT(115); AI_SLOT(116); AI_SLOT(117); AI_SLOT(118); AI_SLOT(119);
	AI_SLOT(120); AI_SLOT(121); AI_SLOT(122); AI_SLOT(123); AI_SLOT(124);
	AI_SLOT(125); AI_SLOT(126); AI_SLOT(127); AI_SLOT(128); AI_SLOT(129);
	AI_SLOT(130); AI_SLOT(131);
#undef AI_SLOT
};

class Rva00243C40Object
{
public:
	unsigned char m_head[0x74];
	Int m_id;
	unsigned char m_gap78[0x20];
	UnsignedInt m_flags98;
	unsigned char m_gap9c[0x204 - 0x9c];
	AIUpdateInterface *m_ai;
};

struct BfmeMemberIndexNode
{
	unsigned char m_head[0x14];
	Int m_index;
};

struct BfmeMemberIndexIterator
{
	BfmeMemberIndexNode *m_node;
};

class BfmeMemberIndexMap
{
public:
	BfmeMemberIndexIterator find(const Int &id);

	BfmeMemberIndexNode *m_header;
	unsigned char m_tail[8];
};

class BfmeMemberSlots
{
public:
	Int size() const
	{
		return ((Int)m_end - (Int)m_begin) >> 4;
	}
	unsigned char *begin() const { return m_begin; }

private:
	unsigned char *m_begin;
	unsigned char *m_end;
};

typedef _STL::list<Rva00243C40Object *> BfmeMemberList;

extern void j_0001336d();
extern void j_0002edcf();

typedef void (BfmeInnerCPB::*BfmeOneCall)(Int, Int);
typedef void (AICommandInterface::*BfmeAttackCall)(Rva00243C40Object *,
	Int, CommandSourceType);

class Rva00243C40HordeContainInterface
{
public:
	void rva00243c40(Rva00243C40Object *target);

private:
	unsigned char m_head[0x3c];
	BfmeMemberIndexMap m_memberIndices;
	BfmeMemberSlots m_slots;
};

void Rva00243C40HordeContainInterface::rva00243c40(
	Rva00243C40Object *target)
{
	Rva00243C40Object *victim = target;
	if (victim == 0)
		return;

	Rva00243C40Object *owner =
		*(Rva00243C40Object **)((char *)this - 0xdc);
	if ((owner->m_flags98 & 0x400) == 0)
		return;

	BfmeMemberList &members =
		*(BfmeMemberList *)((char *)this - 0xac);
	for (BfmeMemberList::iterator it = members.begin();
		it != members.end(); ++it)
	{
		Rva00243C40Object *member = *it;
		AIUpdateInterface *ai = member->m_ai;
		if (ai == 0)
			continue;
		Int memberID = member->m_id;
		BfmeMemberIndexIterator index = m_memberIndices.find(memberID);
		UnsignedInt slot = (UnsignedInt)index.m_node->m_index;
		Int slotCount = m_slots.size();

		if (slot >= slotCount)
			continue;

		if (*(Int *)(m_slots.begin() + slot * 16) < 2)
		{
			if (!ai->isAttacking())
			{
				union
				{
					void *asVoid;
					BfmeAttackCall asMember;
				} call;
				call.asVoid = (void *)j_0002edcf;
				AICommandInterface *commands =
					(AICommandInterface *)((char *)ai + 0x20);
				(commands->*call.asMember)(victim, 0x7fffffff,
					Rva00243C40CommandSourceAI);
			}
		}
		else if (!ai->slot99())
		{
			union
			{
				void *asVoid;
				BfmeOneCall asMember;
			} call;
			call.asVoid = (void *)j_0001336d;
			BfmeInnerCPB *inner =
				(BfmeInnerCPB *)((char *)ai + 0x20);
			(inner->*call.asMember)(0, 2);
		}
	}
}
