// ?d_000f5e40@@YAXXZ
// partial score=0.2119 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x000F5E40, 1293 bytes, ret 0xC.
// The matched ScriptActions::doTeamRecruitUnitsFromTeam (0x00303AC0) calls it
// through ILT 0x0000B866 on the destination team with (ObjectTypes*, count,
// source Team*) and reads an Int back. For each named type whose template
// carries KindOf bit 109, the first behavior module whose slot 13 answers a
// data block names two templates at +0x23C; the body then finds one member of
// each among the source prototype's team instances, moves both to the
// controlling player's default team, has the KindOf-108 one's contain slot 28
// combine them, gives the result to this team, and repeats until the count is
// reached or nothing more pairs. The method's name is not proven, so it keeps
// its address.

#define _STLP_NO_EXCEPTIONS 1

#include "ascii_string.h"
#include <vector>

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

#include <math.h>

class Object;
class Team;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

// Slot 13 of the behavior module data; the data block it answers carries the
// two template names at +0x23C. Neither is named by evidence yet.
class Rva000F5E40PairData
{
public:
	unsigned char m_unmodelled_000[0x23c];
	std::vector<AsciiString *> m_templateNames;			// +0x23C
};

class ModuleData
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12();
	virtual const Rva000F5E40PairData *slot13_000F5E40() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ModuleInfo
{
private:
	struct Nugget
	{
		AsciiString first;
		AsciiString m_moduleTag;
		const ModuleData *second;
		Int interfaceMask;
		Bool copiedFromDefault;
		Bool inheritable;
		Bool overrideableByLikeKind;
	};
	std::vector<Nugget> m_info;

public:
	Int getCount() const
	{
		return m_info.size();
	}

	const ModuleData *getNthData(Int i) const
	{
		if (i >= 0 && i < m_info.size())
		{
			return m_info[i].second;
		}
		return 0;
	}
};

class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const
	{
		return m_name;
	}

	const std::vector<AsciiString> &getBuildVariations() const
	{
		return m_buildVariations;
	}

	// KindOf mask at +0xC8: bit 108 is +0xD4 bit 12, bit 109 is +0xD4 bit 13.
	UnsignedInt getKindOfWord3() const { return m_kindOf[3]; }

	const ModuleInfo &getBehaviorModuleInfo() const { return m_behaviorModuleInfo; }

	Bool isEquivalentTo(const ThingTemplate *) const;

private:
	unsigned char m_unmodelled_00c[0x20 - 0x0c];
	AsciiString m_name;						// +0x20
	unsigned char m_unmodelled_024[0xc8 - 0x24];
	UnsignedInt m_kindOf[6];					// +0xC8
	unsigned char m_unmodelled_0e0[0x294 - 0xe0];
	ModuleInfo m_behaviorModuleInfo;				// +0x294
	unsigned char m_unmodelled_2a0[0x2d0 - 0x2a0];
	std::vector<AsciiString> m_buildVariations;			// +0x2D0
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}

private:
	const T *m_overridable;
};

static Bool isInBuildVariations(const ThingTemplate *ttWithVariations,
	const ThingTemplate *b)
{
	const std::vector<AsciiString> &bv = ttWithVariations->getBuildVariations();
	if (bv.empty())
		return false;

	for (std::vector<AsciiString>::const_iterator it = bv.begin();
		it != bv.end(); ++it)
	{
		if (b->getName().compare(*it) == 0)
			return true;
	}
	return false;
}

class BfmeObjectDlinkObject;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void setTeam(Team *team);				// slot 20, +0x50
};

class BfmeObjectDlinkBase
{
public:
	BfmeObjectDlinkObject *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	OVERRIDE<ThingTemplate> m_template;				// Object+0x04
	unsigned char m_beforePosition[0x34 - 4];
	Coord3D m_position;						// Object+0x38
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

// What Object::unidentified_001BFE20 (contain slot 26) answers: slot 27 asks
// whether the object can be taken, slot 28 combines the two into a third.
class Rva000F5E40Combiner
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual Bool slot27_000F5E40(Object *other);
	virtual Object *slot28_000F5E40(Object *other, Object *self, Int flag);
};

class BfmeHostTP;
class BfmePosTP;

class Object : public BfmeObjectDlinkObject
{
public:
	const ThingTemplate *getTemplate() const
	{
		return m_template.operator->();
	}

	const Coord3D *getPosition() const { return &m_position; }

	Real getBoundingCircleRadius() const
	{
		return *(const Real *)((const char *)this + 0xbc);
	}

	void *unidentified_001BFE20() const;
};

// The matched 190-byte position setter at 0x001D0520 (BfmeConv2025.cpp).
class BfmeHostTP
{
public:
	void bfmeSetPositionTP(const BfmePosTP *pos, Bool flag);
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern BfmeThingFactory *TheThingFactory;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectTypes.h
class ObjectTypes
{
public:
	virtual void crc(void *xfer);

	UnsignedInt getListSize(void) const { return m_objectTypes.size(); }
	AsciiString getNthInList(Int index) const;

private:
	AsciiString m_listName;
	std::vector<AsciiString> m_objectTypes;
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }

	unsigned char m_unmodelled_000[0x230];
	Team *m_defaultTeam;						// +0x230
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

class TeamPrototype
{
public:
	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const;
	Player *getControllingPlayer() const { return m_owningPlayer; }

	unsigned char m_unmodelled_000[0x08];
	Player *m_owningPlayer;						// +0x08
	unsigned char m_unmodelled_00c[0x274 - 0x0c];
	Team *m_teamInstanceList;					// +0x274
};

class Team
{
public:
	Int rva000F5E40(ObjectTypes *types, Int maxCount, Team *sourceTeam);
	Team *_bfme_nextInInstanceList() const;

	Player *getControllingPlayer() const
	{
		if (m_proto == 0)
			return 0;
		return m_proto->getControllingPlayer();
	}

	void *m_vptr;
	TeamPrototype *m_proto;						// +0x04
};

inline DLINK_ITERATOR<Team> TeamPrototype::iterate_TeamInstanceList() const
{
	return DLINK_ITERATOR<Team>(m_teamInstanceList, &Team::_bfme_nextInInstanceList);
}

// ?rva000F5E40@Team@@QAEHPAVObjectTypes@@HPAV1@@Z
Int Team::rva000F5E40(ObjectTypes *types, Int maxCount, Team *sourceTeam)
{
	Int count = 0;
	if (sourceTeam == 0 || types == 0 || types->getListSize() == 0)
		return 0;

	for (Int i = 0; i < types->getListSize(); ++i)
	{
		AsciiString typeName = types->getNthInList(i);
		const ThingTemplate *thing = TheThingFactory->findTemplate(typeName);
		if (thing == 0 || (thing->getKindOfWord3() & 0x2000) == 0)
			continue;

		const Rva000F5E40PairData *pair = 0;
		Int numModules = thing->getBehaviorModuleInfo().getCount();
		for (Int j = 0; j < numModules; ++j)
		{
			const ModuleData *md = thing->getBehaviorModuleInfo().getNthData(j);
			if (md == 0)
				continue;
			const Rva000F5E40PairData *found = md->slot13_000F5E40();
			if (found)
			{
				pair = found;
				break;
			}
		}
		if (pair == 0 || pair->m_templateNames.size() <= 1)
			continue;

		const ThingTemplate *firstTemplate = TheThingFactory->findTemplate(*pair->m_templateNames[0]);
		const ThingTemplate *secondTemplate = TheThingFactory->findTemplate(*pair->m_templateNames[1]);
		if (firstTemplate == 0 || secondTemplate == 0)
			continue;

		Bool recruited;
		do
		{
			recruited = false;
			Object *first = 0;
			Object *second = 0;
			for (DLINK_ITERATOR<Team> teamIter = sourceTeam->m_proto->iterate_TeamInstanceList();
				!teamIter.done(); teamIter.advance())
			{
				Team *team = teamIter.cur();
				if (!team)
					continue;
				for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = ((const BfmeTeamMemberListView *)team)->iterate();
					!iter.done(); iter.advance())
				{
					Object *obj = (Object *)iter.cur();
					if ((first == 0 && obj->getTemplate()->isEquivalentTo(firstTemplate)) ||
						isInBuildVariations(firstTemplate, obj->getTemplate()))
						first = obj;
					else if ((second == 0 && obj->getTemplate()->isEquivalentTo(secondTemplate)) ||
						isInBuildVariations(secondTemplate, obj->getTemplate()))
						second = obj;
					if (first && second)
						break;
				}
				if (first && second)
					break;
			}

			if (first && second)
			{
				Real dx = first->getPosition()->x - second->getPosition()->x;
				Real dy = first->getPosition()->y - second->getPosition()->y;
				Real firstRadius = first->getBoundingCircleRadius();
				Real secondRadius = second->getBoundingCircleRadius();
				Real dist = sqrt(dx * dx + dy * dy) - firstRadius - secondRadius;
				Real distSqr;
				if (dist < 0.0f)
					distSqr = 0.0f;
				else
					distSqr = dist * dist;

				Player *player = getControllingPlayer();
				if (player)
				{
					Team *defaultTeam = player->getDefaultTeam();
					first->setTeam(defaultTeam);
					second->setTeam(defaultTeam);
				}

				Object *combined = 0;
				if (first->getTemplate()->getKindOfWord3() & 0x1000)
				{
					Rva000F5E40Combiner *combiner = (Rva000F5E40Combiner *)first->unidentified_001BFE20();
					if (combiner && combiner->slot27_000F5E40(second))
					{
						combined = combiner->slot28_000F5E40(second, first, 0);
						if (combined)
							combined->setTeam(this);
					}
				}
				else if (second->getTemplate()->getKindOfWord3() & 0x1000)
				{
					Rva000F5E40Combiner *combiner = (Rva000F5E40Combiner *)second->unidentified_001BFE20();
					if (combiner && combiner->slot27_000F5E40(first))
					{
						combined = combiner->slot28_000F5E40(first, second, 0);
						if (combined)
							combined->setTeam(this);
					}
				}

				if (combined)
				{
					++count;
					recruited = true;
					if (distSqr > 22500.0f)
						((BfmeHostTP *)combined)->bfmeSetPositionTP((const BfmePosTP *)combined->getPosition(), false);
				}
			}

			if (count >= maxCount)
				return count;
		} while (recruited);
	}
	return count;
}
