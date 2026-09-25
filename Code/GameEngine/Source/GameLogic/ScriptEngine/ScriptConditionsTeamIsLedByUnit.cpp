// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/objectdlink
//
// Retail 0x003261D0 (189 bytes, ret 8): ScriptConditions::evaluateTeamIsLedByUnit.
//
// Identity: ScriptEngine's condition-template table (script_conditions.cpp,
// retail 0x003307E0) names template 123 "TEAM_IS_LED_BY_UNIT" with a TEAM and a
// UNIT parameter; the condition dispatcher at 0x0032D720 routes case 123 with
// getParameter(0), getParameter(1) through ILT 0x0004A660 straight to this body.
//
// The walk is the Zero Hour team-member DLINK_ITERATOR. The `if (!obj)
// continue;` guard is the upstream idiom and folds away against the loop test,
// but it is what keeps MSVC 7.1 from padding the loop head: without it the
// compiler emits `lea ecx,[ecx]` at +0x5D and the body grows to 192 bytes.
//
// HordeContainInterface slot 53 (+0xD4) is abstract in HordeContain's vtable
// 0x010AE8E0 and Object+0x360 is not witnessed, so both keep offset names.

typedef bool Bool;
typedef int ObjectID;

#include "ascii_string.h"
#include "ObjectDlinkPmf.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

#define BFME_SLOT(N) virtual void slot##N() = 0

// The second interface on the contain module; see ObjectTeamAndPlayer.cpp.
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
	BFME_SLOT(50); BFME_SLOT(51); BFME_SLOT(52);
	// slot 53, +0xD4 -- takes the unit's ObjectID, answers a Bool
	virtual Bool slot53Query(ObjectID id) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
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

// The Object fields this body reads, reached by casting the Object pointer.
class BfmeObjectFields
{
public:
	unsigned char m_beforeID[0x74];
	ObjectID m_id;						// this+0x74
	unsigned char m_beforeContain[0x1FC - 0x78];
	ContainModuleInterface *m_contain;			// this+0x1FC
	unsigned char m_before360[0x360 - 0x200];
	ObjectID m_unmodelled360;				// this+0x360

	ObjectID getID() const { return m_id; }
	ObjectID getUnmodelled360() const { return m_unmodelled360; }
};

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameMemory.h
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
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
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
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;	// slot 17, vtable+0x44
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;	// slot 26, vtable+0x68
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateTeamIsLedByUnit(Parameter *pTeamParm, Parameter *pUnitParm);
};

// ?evaluateTeamIsLedByUnit@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamIsLedByUnit(Parameter *pTeamParm, Parameter *pUnitParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	// Retail passes the Parameter pointer itself, as ScriptConditionsPathfinding.cpp does.
	Object *theUnit = TheScriptEngine->getUnitNamed(*(const AsciiString *)pUnitParm);
	if (!theTeam || !theUnit)
		return false;
	const BfmeObjectFields *unit = (const BfmeObjectFields *)theUnit;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *pObj = iter.cur();
		if (!pObj)
			continue;

		const BfmeObjectFields *obj = (const BfmeObjectFields *)pObj;
		ContainModuleInterface *contain = obj->m_contain;
		if (contain)
		{
			HordeContainInterface *horde = contain->getHordeContainInterface();
			if (horde && horde->slot53Query(unit->getID()))
				return true;
		}
		if (obj->getUnmodelled360() == unit->getID())
			return true;
	}
	return false;
}
