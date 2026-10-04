// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// SpecialEnemySenseUpdate::update, retail 0x002AB0F0, 549 bytes.
//
// IDENTITY. The only route to this body is ILT 0x00043CB1, which sits in slot
// zero of SpecialEnemySenseUpdate's second interface table 0x010C3880 -- the
// UpdateModuleInterface table its matched constructor (0x002AAF30) installs at
// +0x10. Slot zero of that interface is update(), and the receiver arrives as
// that interface: the module data and object are read back at -0x0C and -0x08.
// The withdrawn row called this the destructor; it returns the module data's
// scan interval and ends in a plain ret.
//
// BODY. Look for the closest enemy the module data's filter accepts within
// the module data's range; while one is in range every member of this object's
// horde (or the object itself when it leads none) carries model condition bit
// 247, and loses it otherwise. The three filters live only for the query (the
// unwind state drops to -1 right after it), and each branch copies the horde's
// member list before walking it.
#include <list>

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class Object;
class Player;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

typedef _STL::list<Object *> ObjectList;

// The filter family as AutoPickUpUpdateUpdate.cpp declares it.
class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class Rva002DC6D0Filter
{
public:
	Rva002DC6D0Filter();
	~Rva002DC6D0Filter();

private:
	unsigned int m_handle;
};

class Rva00265150RJFilter : public PartitionFilter
{
public:
	__forceinline Rva00265150RJFilter(const Rva002DC6D0Filter &filter, Player *p, Bool match)
		: m_subobject(&filter), m_player(p), m_match(match) {}
	virtual ~Rva00265150RJFilter() {}
	virtual Bool allow(Object *);
	const Rva002DC6D0Filter *m_subobject;
	Player *m_player;
	Bool m_match;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterRelationship : public PartitionFilter
{
public:
	enum { ALLOW_ENEMIES = 1 };

	PartitionFilterRelationship(Object *p, Int flags, Bool match)
		: m_object(p), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();
	Object *m_object;
	Int m_flags;
	Bool m_match;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, Real maxDist, Int distType, PartitionFilter *filters);
};

extern PartitionManager *ThePartitionManager;

#define BFME_SLOT(n) virtual void slot##n()

class HordeContainInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27); BFME_SLOT(28); BFME_SLOT(29);
	BFME_SLOT(30); BFME_SLOT(31); BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34);
	BFME_SLOT(35); BFME_SLOT(36); BFME_SLOT(37); BFME_SLOT(38); BFME_SLOT(39);
	BFME_SLOT(40); BFME_SLOT(41); BFME_SLOT(42); BFME_SLOT(43); BFME_SLOT(44);
	BFME_SLOT(45); BFME_SLOT(46); BFME_SLOT(47); BFME_SLOT(48); BFME_SLOT(49);
	BFME_SLOT(50); BFME_SLOT(51); BFME_SLOT(52); BFME_SLOT(53); BFME_SLOT(54);
	BFME_SLOT(55); BFME_SLOT(56); BFME_SLOT(57); BFME_SLOT(58);
	// slot 59, +0xEC: the member list this body copies; method name unrecovered
	virtual const ObjectList &slot59() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25);
	// slot 26, +0x68
	virtual HordeContainInterface *getHordeContainInterface() = 0;
};

#undef BFME_SLOT

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
// Offsets as ObjectModelConditions.cpp and ObjectContainQueries.cpp place them.
class Object
{
public:
	Player *getControllingPlayer() const;
	void notifyModelConditionChanged();

	ContainModuleInterface *getContain() const { return m_contain; }
	const Coord3D *getPosition() const { return &m_pos; }

	void setModelConditionState(Int bit)
	{
		UnsignedInt mask = 1u << (bit & 31);
		if ((m_modelConditionFlags[bit >> 5] & mask) == 0)
		{
			m_modelConditionFlags[bit >> 5] |= mask;
			notifyModelConditionChanged();
		}
	}

	void clearModelConditionState(Int bit)
	{
		UnsignedInt mask = 1u << (bit & 31);
		if ((m_modelConditionFlags[bit >> 5] & mask) != 0)
		{
			m_modelConditionFlags[bit >> 5] &= ~mask;
			notifyModelConditionChanged();
		}
	}

private:
	unsigned char m_pad00[0x38];
	Coord3D m_pos;										// +0x38
	unsigned char m_pad44[0x110 - 0x44];
	UnsignedInt m_modelConditionFlags[10];				// +0x110
	unsigned char m_pad138[0x1FC - 0x138];
	ContainModuleInterface *m_contain;					// +0x1FC
};

// Bit 247 is word 7, mask 0x00800000; its ModelConditionFlagType name is
// unrecovered.
enum { MODELCONDITION_BIT_247 = 247 };

class SpecialEnemySenseUpdateModuleData
{
public:
	unsigned char m_pad00[8];
	Rva002DC6D0Filter m_filter;							// +0x08
	Real m_range;										// +0x0C
	UnsignedInt m_scanInterval;							// +0x10
};

class ModuleData;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
// The base layout the matched constructor (SpecialEnemySenseUpdateCtorThunk.cpp)
// builds: module data at +0x04, object at +0x08, two interfaces at +0x0C/+0x10.
class SESU_DeepBase
{
public:
	virtual ~SESU_DeepBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class SESU_Iface1
{
public:
	virtual void slot();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public SESU_DeepBase, public SESU_Iface1, public UpdateModuleInterface
{
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *getModuleData() const { return m_moduleData; }

private:
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_updateState;
};

class SpecialEnemySenseUpdate : public UpdateModule
{
public:
	virtual ~SpecialEnemySenseUpdate();
	virtual UpdateSleepTime update();

protected:
	const SpecialEnemySenseUpdateModuleData *getSpecialEnemySenseUpdateModuleData() const
	{
		return (const SpecialEnemySenseUpdateModuleData *)getModuleData();
	}
};

// ?update@SpecialEnemySenseUpdate@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SpecialEnemySenseUpdate::update()
{
	const SpecialEnemySenseUpdateModuleData *data = getSpecialEnemySenseUpdateModuleData();
	Object *me = getObject();

	Object *enemy;
	{
		PartitionFilterRelationship enemies(me, PartitionFilterRelationship::ALLOW_ENEMIES, false);
		Rva00265150RJFilter sensed(data->m_filter, me->getControllingPlayer(), true);
		Rva0025ED50RootFilter root;
		enemy = ThePartitionManager->getClosestObject(me->getPosition(), data->m_range, 0,
			root.link(&sensed)->link(&enemies));
	}

	ContainModuleInterface *contain = me->getContain();
	if (enemy)
	{
		HordeContainInterface *horde = contain ? contain->getHordeContainInterface() : 0;
		if (horde)
		{
			ObjectList members(horde->slot59());
			for (ObjectList::iterator it = members.begin(); it != members.end(); ++it)
				(*it)->setModelConditionState(MODELCONDITION_BIT_247);
		}
		else
		{
			me->setModelConditionState(MODELCONDITION_BIT_247);
		}
	}
	else
	{
		HordeContainInterface *horde = contain ? contain->getHordeContainInterface() : 0;
		if (horde)
		{
			ObjectList members(horde->slot59());
			for (ObjectList::iterator it = members.begin(); it != members.end(); ++it)
				(*it)->clearModelConditionState(MODELCONDITION_BIT_247);
		}
		else
		{
			me->clearModelConditionState(MODELCONDITION_BIT_247);
		}
	}

	return (UpdateSleepTime)data->m_scanInterval;
}
