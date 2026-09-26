// ?d_002ff430@@YAXXZ
// partial score=0.78 date=2026-09-23
// ?doDeploySiegeNearTeam@ScriptActions@@IAEXPAVParameter@@00@Z
// Scratch-only native reconstruction for retail RVA 0x002FF430, 655 bytes.
// Identity is proven by the DEPLOY_SIEGE_NEAR_TEAM action table arm and its
// ILT caller.  This file is intentionally outside Code/ and is not a ledger
// claim.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1

#include <bitset>
#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Parameter
{
public:
	unsigned char m_beforeReal[0x0c];
	Real m_real;
	AsciiString m_string;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

enum SpecialPowerType
{
	SPECIAL_POWER_DEPLOY_SIEGE = 0x2e
};

class SpecialPowerTemplate;
class Object;

class SpecialPowerModuleInterface
{
public:
	virtual Bool isModuleForPower(const SpecialPowerTemplate *) const = 0;
	virtual Bool isReady() const = 0;
	virtual void slot02() const = 0;
	virtual void slot03() const = 0;
	virtual void slot04() const = 0;
	virtual void slot05() const = 0;
	virtual void slot06() const = 0;
	virtual void slot07() const = 0;
	virtual void slot08() const = 0;
	virtual void slot09() const = 0;
	virtual void slot10() const = 0;
	virtual void slot11() = 0;
	virtual void doSpecialPowerAtObject(Object *object,
		UnsignedInt commandOptions) = 0;
};

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0();
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class Module;

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	Module *findModule(NameKeyType key) const;
	SpecialPowerModuleInterface *findSpecialPowerModuleInterface(
		SpecialPowerType type) const;

	unsigned char m_tail[0x40];
};

typedef Object *(Object::*GetNextObjectFunc)() const;

template<class ObjectType>
class DLINK_ITERATOR
{
public:
	typedef ObjectType *(ObjectType::*GetNextFunc)() const;

	DLINK_ITERATOR(ObjectType *current, GetNextFunc getNext)
		: m_cur(current), m_getNextFunc(getNext) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	ObjectType *cur() const
	{
		return m_cur;
	}

private:
    ObjectType *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *out) const;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}

	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vptr;
	Overridable *m_nextOverride;
};

class BfmeObjectTemplateView
{
public:
	void *m_vptr;
	Overridable *m_template;
};

class BfmeThingTemplateKindView
{
public:
	unsigned char m_beforeKind[0xd0];
	UnsignedInt m_kindOfD0;
};

class SiegeDeployModuleInterface
{
public:
	virtual void slot00() {}
	virtual void slot01() {}
	virtual void slot02() {}
	virtual Bool canDeploy(Object *) { return false; }
};

class SiegeDeployModuleView
{
public:
	unsigned char m_beforeInterface[0x20];
	SiegeDeployModuleInterface m_interface;
};

class ObjectDeployFields
{
public:
	unsigned char m_before74[0x74];
	Object *m_deployReference;
	unsigned char m_before94[0x94 - 0x78];
	Int m_status94;
};

template <unsigned int NUMBITS>
class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };

	BitFlags() {}
	BitFlags(BogusInitType, Int bit)
	{
		m_bits._Unchecked_set((size_t)bit);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *) = 0;

	PartitionFilter *m_next;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *) { return false; }
	PartitionFilter *asFilter() { return this; }

	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

struct BfmeWideEntry
{
	Object *object;
	UnsignedInt word04;
};

struct BfmeWideResultData
{
	std::vector<BfmeWideEntry> entries;
	BfmeWideEntry *current;
	Int references;
};

struct BfmeWideResult
{
	BfmeWideResultData *value;

	BfmeWideResult();
	BfmeWideResult(const BfmeWideResult &other)
		: value(other.value)
	{
		++value->references;
	}

	~BfmeWideResult()
	{
		if (--value->references == 0)
			delete value;
	}

	Object *next(Object *&object)
	{
		if (value->current == value->entries.end())
			return 0;
		object = (value->current++)->object;
		return object;
	}
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(Int a, Int b, Int c, Int d, Int e);
};

class PartitionManager : public BfmeWideForwardC
{
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

class BfmeSpecialPowerModuleVtbl_30
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual UnsignedInt getReadyFrame() const = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09(UnsignedInt) = 0;
	virtual void slot10(Bool) = 0;
	virtual void slot11() = 0;
	virtual void doSpecialPowerAtObject(Object *object,
		UnsignedInt commandOptions) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;
extern PartitionManager *ThePartitionManager;

class ScriptActions
{
protected:
	void doDeploySiegeNearTeam(Parameter *sourceTeam, Parameter *targetTeam,
		Parameter *radius);
};

void ScriptActions::doDeploySiegeNearTeam(Parameter *sourceTeam,
	Parameter *targetTeam, Parameter *radius)
{
	Team *source = TheScriptEngine->getTeamNamed(sourceTeam->m_string, false);
	if (!source)
		return;

	DLINK_ITERATOR<Object> members = source->iterate_TeamMemberList();
	if (members.done())
		return;

	Team *target = TheScriptEngine->getTeamNamed(targetTeam->m_string, false);
	if (!target)
		return;

	Coord3D targetPosition;
	target->getEstimateTeamPosition(&targetPosition);
	Real searchRadius = radius->m_real;
	Int searchRadiusBits = *(const Int *)&searchRadius;

	BitFlags<192> kindMask(BitFlags<192>::kInit, 27);
	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		(Int)&targetPosition, searchRadiusBits, 0,
		(Int)PartitionFilterAcceptByKindOf(kindMask, KINDOFMASK_NONE).asFilter(),
		1);

	Object *candidate;
	while (result.next(candidate))
	{
		if (!candidate)
			continue;

		static NameKeyType siegeDeployKey =
			TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
		Module *candidateModule = candidate->findModule(siegeDeployKey);
		if (!candidateModule)
			continue;

		for (; !members.done(); )
		{
			Object *member = members.cur();

			Overridable *objectTemplate =
				((BfmeObjectTemplateView *)member)->m_template;
			if (objectTemplate && objectTemplate->m_nextOverride)
				objectTemplate = (Overridable *)objectTemplate->m_nextOverride
					->getFinalOverride();
			if ((((BfmeThingTemplateKindView *)objectTemplate)->m_kindOfD0 &
				0x10000000) == 0)
				goto advance_member;

			SpecialPowerModuleInterface *specialPower =
				member->findSpecialPowerModuleInterface(
					(SpecialPowerType)SPECIAL_POWER_DEPLOY_SIEGE);
			if (!specialPower)
				goto advance_member;
			if (!specialPower->isReady())
				goto advance_member;
			if ((((ObjectDeployFields *)member)->m_status94 &
				0x80000000u) != 0)
				goto advance_member;
			if (!((SiegeDeployModuleView *)candidateModule)->m_interface
				.canDeploy(((ObjectDeployFields *)member)->m_deployReference))
				break;

			((BfmeSpecialPowerModuleVtbl_30 *)specialPower)
				->doSpecialPowerAtObject(candidate, 2);

	advance_member:
			if (members.cur() != 0)
				members.advance();
		}
	}
}
