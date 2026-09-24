// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Every ScriptConditions condition that looks a team up by name and then walks
// its member list, asking each object one question:
//
//   0x00324C30  evaluateTeamAttackedByPlayer        who last damaged it
//   0x00325150  evaluateSkirmishCommandButtonIsReady  a command button on it
//   0x00328470  evaluateRva00328470                 whether a player sees it
//   0x0032BB90  evaluateTeamHasObjectStatus         an object-status bit
//
// 0x00325080 evaluateTeamIsContained joins the same iterator family. Its
// upstream body is present in both pristine Zero Hour and the BFME source;
// BFME calls the StringBase<char> copy constructor at 0x00887B60, which also
// has unrelated ledger alias names.
//
// All four open with getTeamNamed at ScriptEngine's slot 17 and then run the
// same DLINK_ITERATOR over Team's member-list head, so they share every model
// here and differ only in what they ask of each member. They sat in four files
// that each carried a private copy of the iterator, of Team, of Parameter, of
// AsciiString and of the ScriptEngine vtable, and those copies had drifted.
//
// The iterator appeared twice as DLINK_ITERATOR and once as a "DlinkIterator"
// with its two members declared after the methods instead of before -- same
// layout, same inlining, a different name for one thing. The Object it walks
// is the objectdlink shim's skeleton, which two of the files included and two
// copied out by hand; copied out, nothing states that the two are the same
// class, and each hand copy carried only the member functions its own body
// happened to call.
//
// AsciiString had drifted the way it always does: two files spelled it as the
// delegating slice below, two included the stringinline shim, where it derives
// privately from StringBase<char>. Those are not two classes -- reverse pins
// ??1AsciiString@@QAE@XZ and ??1?$StringBase@D@@AAE@XZ to the same body at
// 0x00887940 -- and all four bodies byte-match against the one spelling.
//
// Parameter drifted the same way as everywhere else: three files spelled it as
// a flat 0x10-byte run up to the string, hiding the Int at +0x08 that the
// object-status body reads as the status bit to test.
//
// Finally the object itself. The three bodies that reach past the skeleton do
// it by casting the Object pointer at a private view class, and the three view
// classes were three disjoint pictures of the same object: the status bits at
// +0x90, a flag word at +0x1A4, the body module at +0x200. One layout states
// all three.
//
// The two address-derived names stay address-derived: unidentified_0034DB40
// forwards to TheScriptEngine's virtual at +0x4C, and queryRva001CAEE0 reads
// the viewer at +0x2C. Neither identity is proven.

typedef bool Bool;
typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short PlayerMaskType;

class Object;
class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }
	Int getInt(void) const { return m_int; }

private:
	unsigned char m_beforeInt[8];
	Int m_int;						// this+0x08
	Real m_real;						// this+0x0C
	AsciiString m_string;					// this+0x10
};

// The BFME Object DLINK skeleton, verbatim from reference/shims/objectdlink:
// vptr at +0, the DLINK base at +4, the vbptr-carrying base at +0x68. Copied in
// rather than included because the bodies below add member functions to Object,
// and the offsets -- not the tail sizes -- are what must hold.
class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

class AIUpdateInterface
{
public:
	Int getCurrentStateID() const;
};

// AI_EXIT is enum item 37 in the pristine Zero Hour AIStateMachine.h.
enum { BFME_AI_EXIT = 37 };

enum SpecialPowerType
{
	SPECIAL_INVALID = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID = 0,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
	Bool hasSpecialPower(SpecialPowerType type) const;
	Bool queryRva001CAEE0(const Player *viewer) const;	// address-derived: retail 0x001CAEE0
	ObjectShroudStatus getShroudedStatus(Int playerIndex) const;
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface *const *)((const char *)this + 0x204);
	}
	Object *getContainedBy() const
	{
		return *(Object *const *)((const char *)this + 0x214);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo
{
private:
	unsigned char m_beforeSourcePlayerMask[0x0c];

public:
	PlayerMaskType m_sourcePlayerMask;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
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
	virtual const DamageInfo *getLastDamageInfo() const = 0;
};

// The three fields the bodies below read off an Object without going through a
// proven accessor. Reached by casting the Object pointer, which is what retail
// does; the offsets are the claim, the class is only a place to write them.
class BfmeObjectFields
{
public:
	unsigned char m_beforeStatus[0x90];
	UnsignedInt m_status[3];				// this+0x90
	unsigned char m_beforeFlags[0x1A4 - 0x9C];
	Int m_flags;						// this+0x1A4
	unsigned char m_beforeBody[0x200 - 0x1A8];
	BodyModuleInterface *m_body;				// this+0x200
};

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_beforeIndex[0x24];
	Int m_playerIndex;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride()
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}
	const Overridable *friend_getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	void *m_vptr;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType() const { return m_type; }

private:
	unsigned char m_beforeType[0x14 - 0xC];
	SpecialPowerType m_type;
};

class UpgradeTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	Int getCommandType() const { return m_command; }
	const UpgradeTemplate *getUpgradeTemplate() const { return m_upgradeTemplate; }
	const SpecialPowerTemplate *getSpecialPowerTemplate() const { return m_specialPower; }
	Bool isReady(const Object *sourceObj) const;

private:
	unsigned char m_beforeCommand[0x10];
	Int m_command;
	unsigned char m_beforeUpgrade[0x20 - 0x14];
	const UpgradeTemplate *m_upgradeTemplate;
	unsigned char m_beforeSpecialPower[0x34 - 0x24];
	const SpecialPowerTemplate *m_specialPower;
};

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &);
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

	/// address-derived name -- forwards to TheScriptEngine's virtual at +0x4C
	UnsignedShort unidentified_0034DB40(Parameter *parameter);
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern ControlBar *TheControlBar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptConditions.h
class ScriptConditions
{
protected:
	Bool evaluateTeamAttackedByPlayer(Parameter *, Parameter *);
	virtual Bool evaluateSkirmishCommandButtonIsReady(Parameter *, Parameter *, Parameter *, Bool);
	Bool evaluateRva00328470(Parameter *, Parameter *);
	Bool evaluateTeamHasObjectStatus(Parameter *pTeamParm, Parameter *pObjectStatus, Bool entireTeam);
	virtual Bool evaluateTeamIsContained(Parameter *pTeamParm, Bool allContained);
};

// The upstream condition and this BFME body both look up the team, walk its
// members, and compare each member's contained-by link to the all/any flag.
Bool ScriptConditions::evaluateTeamIsContained(Parameter *pTeamParm, Bool allContained)
{
	Team *pTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!pTeam)
		return false;

	Bool anyConsidered = false;
	for (DLINK_ITERATOR<Object> iter = pTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance()) {
		Object *obj = iter.cur();
		if (!obj)
			continue;

		Bool isContained = obj->getContainedBy() != 0;
		if (!isContained) {
			AIUpdateInterface *ai = obj->getAIUpdateInterface();
			// Preserve the upstream expression. MSVC retains this pointer
			// load but folds away the state query because isContained is false.
			if (ai)
				isContained = isContained && ai->getCurrentStateID() == BFME_AI_EXIT;
		}

		if (isContained) {
			if (!allContained)
				return true;
		} else {
			if (allContained)
				return false;
		}
		anyConsidered = true;
	}
	if (anyConsidered)
		return allContained;
	return false;
}

// ?evaluateTeamAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamAttackedByPlayer(
	Parameter *pTeamParm, Parameter *pPlayerParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *pCur = iter.cur();
		if (!pCur)
			continue;

		BodyModuleInterface *body =
			((const BfmeObjectFields *)pCur)->m_body;
		if (!body)
			continue;

		const DamageInfo *lastDamageInfo = body->getLastDamageInfo();
		if (!lastDamageInfo)
			continue;

		if (lastDamageInfo->m_sourcePlayerMask == mask)
			return true;
	}

	return false;
}

// ?evaluateSkirmishCommandButtonIsReady@ScriptConditions@@MAE_NPAVParameter@@00_N@Z
Bool ScriptConditions::evaluateSkirmishCommandButtonIsReady(
	Parameter *, Parameter *pTeamParm, Parameter *pCommandButtonParm, Bool allReady)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	const CommandButton *commandButton =
		TheControlBar->findCommandButton(pCommandButtonParm->getString());
	if (!commandButton)
		return false;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance()) {
		Object *pObj = iter.cur();
		if (commandButton->getSpecialPowerTemplate()) {
			const SpecialPowerTemplate *sp = commandButton->getSpecialPowerTemplate();
			const Overridable *finalOverride = sp->friend_getFinalOverride();
			if (!pObj->hasSpecialPower(
				((const SpecialPowerTemplate *)finalOverride)->getSpecialPowerType()))
				continue;
		} else if (!commandButton->getUpgradeTemplate()) {
			if (commandButton->getCommandType() != 0x16)
				continue;
		}

		if (commandButton->isReady(pObj)) {
			if (!allReady)
				return true;
		} else {
			if (allReady)
				return false;
		}
	}

	return allReady;
}

// ?evaluateRva00328470@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateRva00328470(
	Parameter *pTeamParm, Parameter *pPlayerParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	DLINK_ITERATOR<Object> it = theTeam->iterate_TeamMemberList();
	for (; !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (((BfmeObjectFields *)obj)->m_flags & 8)
			continue;
		UnsignedShort working = mask;
		while (working) {
			Player *player = ThePlayerList->getEachPlayerFromMask(working);
			if (!obj->queryRva001CAEE0(player)) {
				Int idx = player->m_playerIndex;
				ObjectShroudStatus k = obj->getShroudedStatus(idx);
				if (k == OBJECTSHROUD_CLEAR || k == OBJECTSHROUD_FOGGED)
					return true;
			}
		}
	}

	return false;
}

// ?evaluateTeamHasObjectStatus@ScriptConditions@@IAE_NPAVParameter@@0_N@Z
Bool ScriptConditions::evaluateTeamHasObjectStatus(Parameter *pTeamParm,
	Parameter *pObjectStatus, Bool entireTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *pObj = iter.cur();
		if (!pObj)
			return false;

		UnsignedInt status = pObjectStatus->getInt();
		BfmeObjectFields *obj = (BfmeObjectFields *)pObj;
		Bool currObjHasStatus =
			(obj->m_status[status >> 5] & (1u << (status & 31))) != 0;

		if (entireTeam && !currObjHasStatus)
			return false;
		else if (!entireTeam && currObjHasStatus)
			return true;
	}

	if (entireTeam)
		return true;
	return false;
}
