// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// The matched ready() caller at 0x00203DB0 calls TheAI::compare through
// a thunk at 0x0000F4AC, which jumps to body 0x0014CE00. Mask bits link
// selected filters. The special-module check can return before the wide query.

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#include "PreRTS.h"

#pragma warning(disable:4234)

class Rva00203DB0AI
{
public:
	int compare(int left, int right, int mask);
};

extern Rva00203DB0AI *_TheAIParseDefinitionAI;

class Object;
class Player;

struct BfmeNoArgBoolCall { unsigned char call(); };
struct BfmeNoArgPlayerCall { Player *call(); };

extern void j_00001fd7(void);
extern void j_00020824(void);

static __forceinline unsigned char bfmeIsAbleToAttack(const Object *object)
{
	typedef unsigned char (BfmeNoArgBoolCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00001fd7;
	return (reinterpret_cast<BfmeNoArgBoolCall *>(const_cast<Object *>(object))->*fn.member)();
}

static __forceinline Player *bfmeControllingPlayer(const Object *object)
{
	typedef Player *(BfmeNoArgPlayerCall::*Function)();
	union { void (*raw)(void); Function member; } fn;
	fn.raw = j_00020824;
	return (reinterpret_cast<BfmeNoArgPlayerCall *>(const_cast<Object *>(object))->*fn.member)();
}

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

static __forceinline void setFilterVptr(void *filter, unsigned int value)
{
	*reinterpret_cast<unsigned int *>(filter) = value;
}

class __declspec(novtable) Rva00203DB0FilterA : public PartitionFilter
{
public:
	explicit Rva00203DB0FilterA(const Object *object) : PartitionFilter()
	{
		setFilterVptr(this, 0x01095734);
		m_object = object;
	}
	virtual ~Rva00203DB0FilterA() {}
	const Object *m_object;
};

class __declspec(novtable) Rva00203DB0FilterC : public PartitionFilter
{
public:
	explicit Rva00203DB0FilterC(const Object *object) : PartitionFilter()
	{
		setFilterVptr(this, 0x01095744);
		m_object = object;
	}
	virtual ~Rva00203DB0FilterC() {}
	const Object *m_object;
};

class __declspec(novtable) PartitionFilterRejectBuildings : public PartitionFilter
{
public:
	explicit PartitionFilterRejectBuildings(const Object *object);
	virtual ~PartitionFilterRejectBuildings() {}
	virtual unsigned char allow(Object *) { return 0; }
	const Object *m_object;
	unsigned char m_acquireEnemies;
};

class VptrZeroHead
{
public:
	VptrZeroHead() : m_unmodelled_04(0) {}
	virtual ~VptrZeroHead() {}
	unsigned int m_unmodelled_04;
};

class Rva001DCBB0Filter : public VptrZeroHead
{
public:
	Rva001DCBB0Filter(Object *object, unsigned char match);
	virtual ~Rva001DCBB0Filter() {}
	void *m_player;
	unsigned char m_match;
};

class Rva00203DB0ObjectFilter : public PartitionFilter
{
public:
	explicit Rva00203DB0ObjectFilter(void *owner) : PartitionFilter()
	{
		setFilterVptr(this, 0x010956B0);
		m_owner = owner;
	}
	virtual ~Rva00203DB0ObjectFilter() {}
	void *m_owner;
};

class __declspec(novtable) Rva00203DB0RelationFilter : public PartitionFilter
{
public:
	explicit Rva00203DB0RelationFilter(const Object *object) : PartitionFilter()
	{
		setFilterVptr(this, 0x010956C4);
		m_object = object;
		m_flags = 2;
		m_state = 0;
	}
	virtual ~Rva00203DB0RelationFilter() {}
	const Object *m_object;
	int m_flags;
	int m_state;
};

class __declspec(novtable) Rva00203DB0InsignificantFilter : public PartitionFilter
{
public:
	Rva00203DB0InsignificantFilter() : PartitionFilter()
	{
		setFilterVptr(this, 0x010956E4);
		m_allowNonBuildings = 1;
		m_allowInsignificant = 0;
	}
	virtual ~Rva00203DB0InsignificantFilter() {}
	unsigned char m_allowNonBuildings;
	unsigned char m_allowInsignificant;
};

class __declspec(novtable) Rva00203DB0FogFilter : public PartitionFilter
{
public:
	explicit Rva00203DB0FogFilter(int player) : PartitionFilter()
	{
		setFilterVptr(this, 0x010956F4);
		m_player = player;
	}
	virtual ~Rva00203DB0FogFilter() {}
	int m_player;
};

struct Rva00203DB0Entry
{
	Object *object;
	unsigned int distanceBits;
};

struct Rva00203DB0Payload
{
	_STL::vector<Rva00203DB0Entry> entries;
	Rva00203DB0Entry *current;
	int references;
};

struct BfmeWideResult
{
	Rva00203DB0Payload *value;
	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &);
	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int position, int radius, int relation,
		int filter, int flags);
};

class PartitionManager;
extern PartitionManager *ThePartitionManager;

class BfmeThingEQ
{
public:
	unsigned char bfmeAskEQ(void *object);
};

class Rva00203DB0Module
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0;
	virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0;
	virtual unsigned char allow(Object *source, Object **result) = 0;
};

struct Rva00203DB0Record
{
	char m_pad[0x24];
	int m_right;
	int m_limit;
};

class Rva00203DB0Owner
{
public:
	unsigned char ready() const;

private:
	char m_pad[4];
	Rva00203DB0Record *m_record;
	int m_left;
};

unsigned char Rva00203DB0Owner::ready() const
{
	Rva00203DB0Record *record = m_record;
	if (record->m_limit == 0)
		return 1;
	int left = m_left;
	int right = record->m_right;
	return _TheAIParseDefinitionAI->compare(left, right, 0x20) >= record->m_limit;
}

int Rva00203DB0AI::compare(int left, int right, int mask)
{
	Object *object = reinterpret_cast<Object *>(left);
	if ((mask & 2) && !bfmeIsAbleToAttack(object))
		return 0;

	Rva00203DB0FilterA obvious(object);
	Rva00203DB0FilterC withinRange(object);
	PartitionFilterRejectBuildings buildings(object);
	Rva001DCBB0Filter stealth(object, 0);
	Rva00203DB0ObjectFilter objectFilter(object);
	Rva00203DB0RelationFilter relation(object);
	Rva00203DB0InsignificantFilter insignificant;
	Rva00203DB0FogFilter fog(*(int *)((char *)bfmeControllingPlayer(object) + 0x24));

	if (!(mask & 8))
		obvious.link(reinterpret_cast<PartitionFilter *>(&buildings));
	if (mask & 16)
		obvious.link(reinterpret_cast<PartitionFilter *>(&withinRange));
	if (mask & 1)
		obvious.link(reinterpret_cast<PartitionFilter *>(&objectFilter));
	if (mask & 2)
		obvious.link(reinterpret_cast<PartitionFilter *>(&relation));
	if (mask & 32)
		obvious.link(reinterpret_cast<PartitionFilter *>(&fog));
	if (mask & 4)
		obvious.link(reinterpret_cast<PartitionFilter *>(&insignificant));
	obvious.link(reinterpret_cast<PartitionFilter *>(&stealth));

	if ((mask & 2) &&
		(*(unsigned char *)((char *)object + 0x94) & 0x10) != 0)
	{
		void *specialOwner = *(void **)((char *)object + 0x214);
		if (specialOwner != 0)
		{
			void *module = *(void **)((char *)specialOwner + 0x1fc);
			if (module != 0)
			{
				Object *special;
				if (((Rva00203DB0Module *)module)->allow(object, &special))
				{
					if (special == 0)
						return 0;
					if (!reinterpret_cast<BfmeThingEQ *>(&obvious)->bfmeAskEQ(special))
						return 0;
					return 1;
				}
			}
		}
	}

	return ((BfmeWideForwardC *)ThePartitionManager)->bfmeForwardWideC(
		(int)((char *)object + 0x38), right, 1,
		(int)reinterpret_cast<PartitionFilter *>(&obvious), 0).value->entries.size();
}
