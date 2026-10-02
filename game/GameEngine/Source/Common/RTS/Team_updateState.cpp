// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x000F4F30, Team::updateState(), 1293 bytes (ret at +0x50C).
// Identity: the matched TeamPrototype::updateState (0x000F71C0) calls it
// through ILT 0x0004383D once per team instance; Zero Hour twin
// Team::updateState in GeneralsMD Team.cpp. BFME changes over the twin:
// a proto null guard, the create block also waits for a Team+0xE7 flag and
// the Team query at 0x000F4E20, it hands a Lua handle named by the template
// string at +0x70 to every live member AI, members count through their
// contain module, runScript takes the team name first, the enemy check runs
// every eighth frame per team id through a filter chain, and all later
// checks wait for the flag the create block sets at Team+0x33.
//
// Written as plain source: every accessor is inline, and VC7.1's inline
// budget alone leaves the first Team::getName, isEmpty, isNotEmpty and the
// first two member-list iterate() calls out of line, as retail has them.

#include <bitset>

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

template <> inline bool StringBase<char>::isEmpty() const
{
	if (m_data == 0)
		return true;
	if (m_data->length == 0)
		return true;
	return false;
}

template <> inline bool StringBase<char>::isNotEmpty() const
{
	return !isEmpty();
}

class Team;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class BfmeObjectDlinkObject;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	BfmeObjectDlinkObject *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_beforePosition[0x34];
	Coord3D m_position;					// Object+0x38
	unsigned char m_afterPosition[0x64 - 0x40];
};

class BfmeObjectDlinkObject : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

typedef BfmeObjectDlinkObject *(BfmeObjectDlinkObject::*BfmeGetNextTeamMemberFunc)() const;

template <class ObjectType> class BfmeDlinkIterator
{
public:
	BfmeDlinkIterator(ObjectType *cur, BfmeGetNextTeamMemberFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	BfmeGetNextTeamMemberFunc m_getNext;
};

struct BfmeTeamMemberListView
{
	unsigned char m_unmodelled_000[0x0c];
	BfmeObjectDlinkObject *m_head;

	BfmeDlinkIterator<BfmeObjectDlinkObject> iterate() const
	{
		return BfmeDlinkIterator<BfmeObjectDlinkObject>(m_head, BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}
};

// Object+0x1FC m_contain slot 26 answers the object whose slot 84 counts
// the units it stands for; neither slot is named by evidence yet.
class Rva000F4F30ContainCount
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual Int slot84_000F4F30(Int);
};

class ContainModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25();
	virtual Rva000F4F30ContainCount *slot26_000F4F30();
};

class AIUpdateInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual void s68(); virtual void s69(); virtual void s70(); virtual void s71();
	virtual void s72(); virtual void s73(); virtual void s74(); virtual void s75();
	virtual void s76(); virtual void s77(); virtual void s78(); virtual void s79();
	virtual void s80(); virtual void s81(); virtual void s82(); virtual void s83();
	virtual void s84(); virtual void s85(); virtual void s86(); virtual void s87();
	virtual void s88(); virtual void s89(); virtual void s90(); virtual void s91();
	virtual void s92(); virtual void s93(); virtual void s94(); virtual void s95();
	virtual Bool isIdle();						// slot 96, +0x180

	// Stores the handle at +0x200; address-derived, body 0x0026ED70.
	void setRva0026ED70(Int handle);
};

class Object : public BfmeObjectDlinkObject
{
public:
	Real getVisionRange() const;
	const Coord3D *getPosition() const { return &m_position; }

	ContainModuleInterface *getContain() const
	{
		return *(ContainModuleInterface *const *)((const char *)this + 0x1fc);
	}

	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface *const *)((const char *)this + 0x204);
	}

	Bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0;
	}
};

template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;
};

// Two-index kInit construction of a 192-bit KindOf mask; ILT 0x0000198D.
class KindOfMask : public BitFlags<192>
{
public:
	KindOfMask(Int init, Int idx1, Int idx2);
};

extern const BitFlags<192> KINDOFMASK_NONE;

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

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const BitFlags<192> &mustBeSet,
		const BitFlags<192> &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *);

	BitFlags<192> m_mustBeSet;
	BitFlags<192> m_mustBeClear;
};

class Rva0025ED50ObjectFilter : public PartitionFilter
{
public:
	explicit Rva0025ED50ObjectFilter(Object *object)
		: m_object(object) {}
	virtual ~Rva0025ED50ObjectFilter() {}
	virtual Bool allow(Object *);

	Object *m_object;
};

class Rva0025ED50RootFilter : public PartitionFilter
{
public:
	Rva0025ED50RootFilter() {}
	virtual ~Rva0025ED50RootFilter() {}
	virtual Bool allow(Object *);
};

class PartitionFilterRelationship : public PartitionFilter
{
public:
	enum RelationshipAllowTypes
	{
		ALLOW_ENEMIES = 1,
		ALLOW_NEUTRAL = 2,
		ALLOW_ALLIES = 4
	};

	PartitionFilterRelationship(Object *object, Int flags, Bool match)
		: m_obj(object), m_flags(flags), m_match(match) {}
	virtual ~PartitionFilterRelationship() {}
	virtual Bool allow(Object *);
	virtual Int getPlayerMask();

	Object *m_obj;
	Int m_flags;
	Bool m_match;
};

enum DistanceCalculationType
{
	FROM_CENTER_2D = 0
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, Real maxDistance,
		DistanceCalculationType dc, PartitionFilter *filters);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

	unsigned char m_unmodelled_000[0x3c];
	UnsignedInt m_frame;						// +0x3C
};

class ScriptEngine
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	// slot 15, +0x3C; BFME passes the running team's name first
	virtual void runScript(const AsciiString &teamName, const AsciiString &scriptName, Team *pThisTeam);
};

// Resolves the named Lua entry to the handle the AI members store; body
// 0x002EBF60, address-derived.
class LuaScriptEngine
{
public:
	Int rva002EBF60(const AsciiString &name);
};

extern ScriptEngine *TheScriptEngine;
LuaScriptEngine *TheLuaScriptEngine = 0;
extern PartitionManager *ThePartitionManager;
extern GameLogic *TheGameLogic;

// The shared empty AsciiString the nullable team-name accessor falls back on.
extern const AsciiString Rva01336E50EmptyString;

// TeamTemplateInfo as it sits at TeamPrototype+0x12C. BFME inserted one
// AsciiString after m_scriptOnCreate, so the Zero Hour fields that follow
// sit four bytes later; each use below mirrors the Zero Hour updateState.
struct BfmeTeamTemplateInfoView
{
	unsigned char m_unmodelled_000[0x6c];
	AsciiString m_scriptOnCreate;					// +0x6C
	AsciiString m_luaString70;					// +0x70
	AsciiString m_scriptOnIdle;					// +0x74
	unsigned char m_unmodelled_078[4];
	AsciiString m_scriptOnEnemySighted;				// +0x7C
	AsciiString m_scriptOnAllClear;					// +0x80
	unsigned char m_unmodelled_084[4];
	AsciiString m_scriptOnDestroyed;				// +0x88
	Real m_destroyedThreshold;					// +0x8C
};

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }
	const BfmeTeamTemplateInfoView *getTemplateInfo() const
	{
		return (const BfmeTeamTemplateInfoView *)((const char *)this + 0x12c);
	}

	unsigned char m_unmodelled_000[0x10];
	AsciiString m_name;						// +0x10
};

class Team
{
public:
	void updateState();
	Bool rva000F4E20();

	const AsciiString &getName() const
	{
		if (!m_proto)
			return Rva01336E50EmptyString;
		return m_proto->getName();
	}

	void *m_vptr;
	TeamPrototype *m_proto;						// +0x04
	UnsignedInt m_id;						// +0x08
	BfmeObjectDlinkObject *m_memberList;				// +0x0C
	unsigned char m_unmodelled_010[0x30 - 0x10];
	Bool m_enteredOrExited;						// +0x30
	Bool m_active;							// +0x31
	Bool m_created;							// +0x32
	Bool m_bfme33;							// +0x33
	Bool m_checkEnemySighted;					// +0x34
	Bool m_seeEnemy;						// +0x35
	Bool m_prevSeeEnemy;						// +0x36
	Bool m_wasIdle;							// +0x37
	Int m_destroyThreshold;						// +0x38
	Int m_curUnits;							// +0x3C
	unsigned char m_unmodelled_040[0xe4 - 0x40];
	unsigned char m_flagsE4[3];					// +0xE4..+0xE6
	Bool m_bfmeE7;							// +0xE7
	unsigned char m_unmodelled_0E8[0xfc - 0xe8];
	Bool m_bfmeFC;							// +0xFC
};

// ?updateState@Team@@QAEXXZ
void Team::updateState(void)
{
	if (!m_proto)
		return;
	m_enteredOrExited = false;
	if (!m_active)
		return;

	const BfmeTeamTemplateInfoView *pInfo = m_proto->getTemplateInfo();
	if (m_created && !m_bfmeE7 && rva000F4E20())
	{
		m_created = false;
		m_bfme33 = true;
		if (!pInfo->m_scriptOnCreate.isEmpty())
			TheScriptEngine->runScript(getName(), pInfo->m_scriptOnCreate, this);

		if (pInfo->m_luaString70.isNotEmpty())
		{
			Int handle = TheLuaScriptEngine->rva002EBF60(pInfo->m_luaString70);
			for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = ((const BfmeTeamMemberListView *)this)->iterate();
				!iter.done(); iter.advance())
			{
				Object *obj = (Object *)iter.cur();
				AIUpdateInterface *ai = obj->getAIUpdateInterface();
				if (!obj->isEffectivelyDead() && ai)
					ai->setRva0026ED70(handle);
			}
		}

		if (!pInfo->m_scriptOnDestroyed.isEmpty())
		{
			for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = ((const BfmeTeamMemberListView *)this)->iterate();
				!iter.done(); iter.advance())
			{
				Object *obj = (Object *)iter.cur();
				ContainModuleInterface *contain = obj->getContain();
				Rva000F4F30ContainCount *count;
				if (contain && (count = contain->slot26_000F4F30()) != 0)
					m_curUnits += count->slot84_000F4F30(0);
				else
					m_curUnits++;
			}
			m_destroyThreshold = m_curUnits - (m_curUnits * pInfo->m_destroyedThreshold);
			if (m_destroyThreshold > m_curUnits - 1)
				m_destroyThreshold = m_curUnits - 1;
			if (m_destroyThreshold < 0)
				m_destroyThreshold = 0;
		}
	}

	if (!m_bfme33)
		return;

	if (!m_bfmeFC && m_memberList)
		m_bfmeFC = true;

	if (m_checkEnemySighted && ((m_id ^ TheGameLogic->getFrame()) & 7) == 0)
	{
		m_prevSeeEnemy = m_seeEnemy;
		m_seeEnemy = false;
		for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = ((const BfmeTeamMemberListView *)this)->iterate();
			!iter.done(); iter.advance())
		{
			Object *obj = (Object *)iter.cur();
			if (obj->isEffectivelyDead())
				continue;

			if (ThePartitionManager->getClosestObject(obj->getPosition(), obj->getVisionRange(), FROM_CENTER_2D,
				PartitionFilterRelationship(obj, PartitionFilterRelationship::ALLOW_ENEMIES, false).link(
				Rva0025ED50RootFilter().link(
				Rva0025ED50ObjectFilter(obj).link(
				&PartitionFilterAcceptByKindOf(KINDOFMASK_NONE, KindOfMask(0, 88, 133)))))))
			{
				m_seeEnemy = true;
				break;
			}
		}
		if (m_prevSeeEnemy != m_seeEnemy)
		{
			if (m_seeEnemy)
				TheScriptEngine->runScript(getName(), pInfo->m_scriptOnEnemySighted, this);
			else
				TheScriptEngine->runScript(getName(), pInfo->m_scriptOnAllClear, this);
		}
	}

	if (!pInfo->m_scriptOnDestroyed.isEmpty())
	{
		Int prevUnits = m_curUnits;
		m_curUnits = 0;
		for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = ((const BfmeTeamMemberListView *)this)->iterate();
			!iter.done(); iter.advance())
		{
			Object *obj = (Object *)iter.cur();
			if (obj->isEffectivelyDead())
				continue;
			ContainModuleInterface *contain = obj->getContain();
			Rva000F4F30ContainCount *count;
			if (contain && (count = contain->slot26_000F4F30()) != 0)
				m_curUnits += count->slot84_000F4F30(0);
			else
				m_curUnits++;
		}
		if (m_curUnits != prevUnits && m_curUnits <= m_destroyThreshold)
		{
			TheScriptEngine->runScript(getName(), pInfo->m_scriptOnDestroyed, this);
			m_destroyThreshold = -1;
		}
	}

	if (!pInfo->m_scriptOnIdle.isEmpty())
	{
		Bool isIdle = true;
		Bool anyAliveInTeam = false;
		for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = ((const BfmeTeamMemberListView *)this)->iterate();
			!iter.done(); iter.advance())
		{
			Object *obj = (Object *)iter.cur();
			if (obj->isEffectivelyDead())
				continue;
			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			if (!ai)
				continue;
			anyAliveInTeam = true;
			if (!ai->isIdle())
				isIdle = false;
		}
		if (anyAliveInTeam && isIdle && m_wasIdle)
			TheScriptEngine->runScript(getName(), pInfo->m_scriptOnIdle, this);
		m_wasIdle = isIdle;
	}
}
