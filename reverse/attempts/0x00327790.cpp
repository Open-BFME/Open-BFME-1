// ?evaluateTeamAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z
// partial score=0.55 date=2026-09-23
// Open-BFME: retail RVA 0x00327790, 344 bytes.
// ?evaluateTeamAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z
//
// Identity: landed neighbours 0x00327560 (evaluateNamedUnitRankLevel) and
// 0x00327660 (evaluateNamedAttackedByType, ScriptConditionsNamedByType.cpp)
// bracket this body. The callee chain matches ZH's ScriptConditions.cpp
// evaluateTeamAttackedByType exactly: TheScriptEngine->getTeamNamed(name)
// (vtable+0x44), an ObjectTypesTemp built once via objectTypesFromParam
// (0x0003DF4B), a DLINK_ITERATOR<Object> walk of the team's member list
// (Object::dlink_next_TeamMemberList, ILT 0x00001140, reusing the layout
// proven by TeamHealAllObjects.cpp / reference/shims/objectdlink), and per
// member the same getBodyModule/getLastDamageInfo/findObjectByID/getTemplate
// chain evaluateNamedAttackedByType uses -- except BFME's DamageInfo has no
// m_sourceTemplate fast path, so only the "old system" m_sourceID branch of
// the ZH source is present. getTemplate() is called twice (once for its own
// null check, once for getName()), matching ZH's uncached calls, so it must
// be a real inline method here (BFME's Thing::getTemplate resolves the
// override chain) rather than the sibling TU's declared-only placeholder.
// Parameter::getString() returns const AsciiString &, but BFME's matched
// callers prove that ScriptEngine slot 17 takes AsciiString by value and a
// second Bool; retail constructs that value from Parameter+0x10.

// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink /ICode/Libraries/Source/WWVegas/WWLib

#include "ObjectDlinkPmf.h"
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	unsigned char m_pad[0x10];
	AsciiString m_string;   // +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x20);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
public:
	unsigned char m_beforeSourceID[8];
	Int m_sourceID;   // this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual const DamageInfo *getLastDamageInfo() const;   // slot 15, vtable+0x3C
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

static inline BodyModuleInterface *rva327790_getBodyModule(const Object *obj)
{
	return *(BodyModuleInterface **)((const char *)obj + 0x200);
}

static inline const ThingTemplate *rva327790_getTemplate(const Object *obj)
{
	const ThingTemplate *t = *(const ThingTemplate **)((const char *)obj + 0x04);
	if (t && t->m_nextOverride)
		t = (const ThingTemplate *)t->m_nextOverride->getFinalOverride();
	return t;
}

class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;   // +0xC

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

// ObjectTypes is 20 bytes (vptr + list name + vector triple). Matched
// ObjectTypesTemp ctor at 0x002ED6C0 does push 0x14 / operator new /
// ObjectTypes ctor.
class ObjectTypes
{
public:
	ObjectTypes();
	virtual ~ObjectTypes();
	Bool isInSet(const AsciiString &objectType) const;

private:
	void *m_listName;
	void *m_objTypesBegin;
	void *m_objTypesEnd;
	void *m_objTypesCap;
};

class ObjectTypesTemp
{
public:
	ObjectTypes *m_types;
	ObjectTypesTemp();
	~ObjectTypesTemp()
	{
		if (m_types)
			delete m_types;
	}
};

class ScriptEngine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16();
	virtual Team *getTeamNamed(AsciiString name, Bool exact); // slot 17, vtable+0x44
};

extern ScriptEngine *TheScriptEngine;
extern GameLogic *TheGameLogic;

class ScriptConditions
{
protected:
	Bool evaluateTeamAttackedByType(Parameter *, Parameter *);
	static void objectTypesFromParam(Parameter *, ObjectTypes *);
};

// ?evaluateTeamAttackedByType@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamAttackedByType(
	Parameter *pTeamParm, Parameter *pTypeParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	ObjectTypesTemp types;
	objectTypesFromParam(pTypeParm, types.m_types);

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *pCur = iter.cur();
		if (!pCur)
			continue;

		BodyModuleInterface *theBodyModule = rva327790_getBodyModule(pCur);
		if (!theBodyModule)
			continue;

		const DamageInfo *lastDamageInfo = theBodyModule->getLastDamageInfo();
		if (!lastDamageInfo)
			continue;

		Int id = lastDamageInfo->m_sourceID;
		Object *pAttacker = TheGameLogic->findObjectByID(id);
		if (!pAttacker || !rva327790_getTemplate(pAttacker))
			continue;

		if (types.m_types->isInSet(rva327790_getTemplate(pAttacker)->getName()))
			return true;
	}

	return false;
}
