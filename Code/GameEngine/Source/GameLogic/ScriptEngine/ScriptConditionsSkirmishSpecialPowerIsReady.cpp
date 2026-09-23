// ?evaluateSkirmishSpecialPowerIsReady@ScriptConditions@@IAE_NPAVParameter@@0@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp
//
// ScriptConditions::evaluateSkirmishSpecialPowerIsReady at retail RVA
// 0x0032B8D0 (478 bytes).  Identity: the ScriptEngine condition-template init
// stores "SKIRMISH_SPECIAL_POWER_READY" (0x010E4A98) into template +0x13054,
// nine 0x7C-byte templates after UNIT_EMPTIED (+0x12BF8, dispatcher case 76),
// i.e. condition 85; the dispatcher 0x0032D720 routes case 85 through ILT
// 0x00026265 to this body.
//
// BFME deltas: the player parameter resolves to a player MASK that is walked
// with getEachPlayerFromMask, and the special power name is passed by value.
// Team and object walks are the same three-level shape as the landed
// ScriptConditionsEvaluateUnitHasToggledWeapon.cpp.
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef UnsignedShort PlayerMaskType;

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	Int getInt() const { return m_int; }
	void friend_setInt(Int i) { m_int = i; }

private:
	UnsignedByte m_beforeString[0x10];
	AsciiString m_string;
	UnsignedByte m_beforeInt[0x0c];
	Int m_int;
};

class Player;

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	UnsignedByte m_beforeFrame[0x3c];
	UnsignedInt m_frame;
};

class SpecialPowerTemplate;
class Object;

class SpecialPowerModuleInterface
{
public:
	virtual void slot00();
	virtual Bool isReady() const = 0;
	virtual void slot08();
	virtual void slot0C();
	virtual UnsignedInt getReadyFrame() const = 0;
};

class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
	Bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *power);
};

class BfmeObjectVirtualTail
{
public:
	UnsignedByte m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	UnsignedByte m_carrier[4];
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
	UnsignedByte m_template[4];
};

class BfmeObjectDlinkPad
{
public:
	UnsignedByte m_pad[0x60];
};

class Object : public BfmeObjectVtbl,
	public BfmeObjectDlinkBase, public BfmeObjectDlinkPad,
	public BfmeObjectVbptrCarrier
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(
		const SpecialPowerTemplate *specialPowerTemplate) const;

	Bool isUnderConstruction() const { return (m_status & 4) != 0; }
	Bool isDisabled() const { return m_disabledMask != 0; }

private:
	UnsignedByte m_unmodelled_070[0x90 - 0x70];
	UnsignedByte m_status;					// +0x90
	UnsignedByte m_unmodelled_091[0x1a4 - 0x91];
	UnsignedInt m_disabledMask;				// +0x1A4
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class OBJECT>
class DLINK_ITERATOR
{
public:
	typedef OBJECT *(OBJECT::*GetNextFunc)() const;

	DLINK_ITERATOR(OBJECT *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) { }

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}
	Bool done() const { return m_cur == 0; }
	OBJECT *cur() const { return m_cur; }

private:
	OBJECT *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	Team *_bfme_nextInInstanceList();

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_teamMemberList,
			BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}

private:
	UnsignedByte m_unmodelled_000[0x0c];
	Object *m_teamMemberList;				// +0x0C
};

class TeamInstanceIterator
{
public:
	TeamInstanceIterator(Team *head) : m_cur(head) { }

	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }
	void advance()
	{
		if (m_cur)
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
	Int m_unmodelled;
};

struct TeamPrototypeInstances
{
	UnsignedByte m_unmodelled_000[0x274];
	Team *m_teamInstanceList;
};

struct PlayerTeamListNode
{
	PlayerTeamListNode *m_next;
	PlayerTeamListNode *m_prev;
	TeamPrototypeInstances *m_prototype;
};

struct PlayerTeamListField
{
	UnsignedByte m_unmodelled_000[0x288];
	PlayerTeamListNode *m_head;
};

class ScriptConditions
{
protected:
	Bool evaluateSkirmishSpecialPowerIsReady(Parameter *pSkirmishPlayerParm,
		Parameter *pPower);
};

extern GameLogic *TheGameLogic;
extern SpecialPowerStore *TheSpecialPowerStore;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

enum { LOGICFRAMES_PER_SECOND = 5 };

Bool ScriptConditions::evaluateSkirmishSpecialPowerIsReady(
	Parameter *pSkirmishPlayerParm, Parameter *pPower)
{
	if (pPower->getInt() == -1) return false;
	if (pPower->getInt() > 0 && (UnsignedInt)pPower->getInt() > TheGameLogic->getFrame()) {
		return false;
	}
	UnsignedInt nextFrame = TheGameLogic->getFrame() + 10*LOGICFRAMES_PER_SECOND;
	const SpecialPowerTemplate *power = TheSpecialPowerStore->findSpecialPowerTemplate(pPower->getString());
	if (power == 0) {
		pPower->friend_setInt(-1); // flag as never true.
		return false;
	}

	PlayerMaskType mask = TheScriptEngine->unidentified_0034DB40(pSkirmishPlayerParm);
	while (mask) {
		Player *pPlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (pPlayer == 0)
			continue;

		PlayerTeamListNode *head = ((PlayerTeamListField *)pPlayer)->m_head;
		for (PlayerTeamListNode *it = head->m_next;
			it != ((PlayerTeamListField *)pPlayer)->m_head; it = it->m_next) {
			for (TeamInstanceIterator iter(it->m_prototype->m_teamInstanceList); !iter.done(); iter.advance()) {
				Team *team = iter.cur();
				if (!team) continue;
				for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
					Object *pObj = iter.cur();
					if (!pObj) continue;
					if (pObj->isUnderConstruction() || pObj->isDisabled())
					{
						continue; // can't fire if under construction or disabled.
					}
					SpecialPowerModuleInterface *mod = pObj->getSpecialPowerModule(power);
					if (mod)
					{
						if (!TheSpecialPowerStore->canUseSpecialPower(pObj, power)) {
							continue;
						}
						if (mod->isReady()) return true;
						if (mod->getReadyFrame() < nextFrame) nextFrame = mod->getReadyFrame();
					}
				}
			}
		}
	}
	pPower->friend_setInt(nextFrame);
	return false;
}

