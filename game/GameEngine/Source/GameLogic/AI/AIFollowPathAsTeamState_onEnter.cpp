// cl: /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// stlport
//
// AIFollowPathAsTeamState::onEnter, retail 0x00179740 (670 B, ret at +0x29D), and the
// out-of-line copy of AIUpdateInterface::friend_getGoalPathPosition at 0x0016FFD0 (62 B).
// BFME 1 evidence: vtable 0x01099C08 slot 4 names onEnter (attempt log); ilt_oracle
// CONFIRMS both decorations below (onEnter's ILT, and slot 7875 for 0x0016FFD0 with the
// class-keyed Coord3D). Retail inlines friend_getGoalPathPosition at the first two
// sites and calls it through ILT 0x0000A9D4 at the third: MSVC 7.1 makes the same
// choice here, and the out-of-line copy it emits is byte-identical to 0x0016FFD0.
// BFME 2 donor: open-bfme-2 45afcff3a6 Code/GameEngine/Source/GameLogic/AI/
// AIAttackApproachTargetStateOnEnter.cpp (AIFollowPathAsTeamState::onEnter, BFME 2
// 0x0034E3A5) supplies the statement order and the CritterDesync log calls; BFME 1
// offsets come from the retail listing and the matched computePath sibling
// (AIFollowPathAsTeamState_computePath_Bfme.cpp). Zero Hour: AIStates.cpp
// AIStateMachine::getGoalPathPosition and AIFollowPathState::onEnter.
#include <vector>
#include <math.h>
typedef bool Bool;
typedef float Real;
typedef int Int;
enum StateReturnType { STATE_CONTINUE = 0, STATE_FAILURE = -2 };

// class-gate: allow Coord3D BFME's class-keyed Coord3D (ilt_oracle confirms PBVCoord3D for 0x0016FFD0) with the canonical x/y/z layout
class Coord3D
{
public:
	Real x;
	Real y;
	Real z;
};

#include "Lib/Coord2D.h"

// Zero Hour's inline Coord2D::length (BaseType.h), absent from the canonical header.
static inline Real coord2DLength(const Coord2D &c) { return (Real)sqrt(c.x * c.x + c.y * c.y); }

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIStateMachine
{
public:
	const Coord3D *getGoalPathPosition(Int i) const
	{
		if (i < 0 || i >= m_goalPath.size())
			return 0;
		return &m_goalPath[i];
	}
private:
	unsigned char m_pad00[0x44];
	_STL::vector<Coord3D> m_goalPath;
};

class AIUpdateInterface
{
public:
	virtual void slot000();
	void setPathExtraDistance(Real dist);
	Int vslot200()
	{
		typedef Int (AIUpdateInterface::*Slot)();
		return (this->*(*(Slot *)&((*(void ***)this)[128])))();
	}
	const Coord3D *friend_getGoalPathPosition(Int index) const { return m_stateMachine->getGoalPathPosition(index); }
	unsigned char m_pad04[0x30 - 0x04];
	AIStateMachine *m_stateMachine;
	unsigned char m_pad34[0x194 - 0x34];
	Int m_currentGoalPathIndex;
	unsigned char m_pad198[0x1a0 - 0x198];
	Int m_rva1A0;
};

struct Object
{
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	unsigned char m_pad44[0x204 - 0x44];
	AIUpdateInterface *m_ai;
	const Coord3D *getPosition() const { return &m_position; }
	AIUpdateInterface *getAI() const { return m_ai; }
};

struct StateMachine
{
	unsigned char m_pad00[0x10];
	Object *m_owner;
	Object *getOwner() const { return m_owner; }
};

class AttackMoveMachine
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8(Int);
};

extern bool Glo012F0239;
class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern void j_0003a17a(void);
typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *, ...);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	void setAdjustsDestination(Bool b) { m_adjustDestinations = b; }
	unsigned char m_pad04[0x1c - 0x04];
	StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x4c - 0x30];
	Bool m_adjustDestinations;
};

class AIFollowPathAsTeamState : public AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
private:
	Int m_index;
	Int m_retryCount;
	Bool m_adjustFinal;
	Bool m_rva59;
	Bool m_rva5A;
	Bool m_rva5B;
	Int m_rva5C;
	AttackMoveMachine *m_rva60;
	Int m_64;
	Bool m_rva68;
};

// ?friend_getGoalPathPosition@AIUpdateInterface@@QBEPBVCoord3D@@H@Z (0x0016FFD0, emitted out of line by the third call)

// ?onEnter@AIFollowPathAsTeamState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIFollowPathAsTeamState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	m_index = 0;
	if (m_rva60)
	{
		m_rva60->slot5();
		m_rva60->slot8(0);
	}
	m_rva5C = ai->vslot200();
	m_rva68 = false;
	m_rva5B = false;
	const Coord3D *pos = ai->friend_getGoalPathPosition(m_index);
	if (pos == 0)
		return STATE_FAILURE;
	m_64 = ai->m_rva1A0;
	m_goalPosition = *pos;
	const Coord3D *nextPos = ai->friend_getGoalPathPosition(m_index + 1);
	m_adjustFinal = true;
	while (nextPos)
	{
		const Coord3D *goal = &m_goalPosition;
		Coord3D fromOwner;
		fromOwner.x = goal->x;
		fromOwner.y = goal->y;
		fromOwner.x -= obj->getPosition()->x;
		fromOwner.y -= obj->getPosition()->y;
		Coord3D toNext;
		toNext.x = nextPos->x;
		toNext.y = nextPos->y;
		toNext.x -= goal->x;
		toNext.y -= goal->y;
		if (!(toNext.x * fromOwner.x + toNext.y * fromOwner.y < 0.0f))
			break;
		m_index++;
		m_goalPosition = *nextPos;
		nextPos = ai->friend_getGoalPathPosition(m_index + 1);
	}
	ai->m_currentGoalPathIndex = m_index;

	if (Glo012F0239 && TheCRCParameterCheck)
		((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
			"CritterDesync: setAdjustDestination(nextPos=%s) 44", nextPos ? "VALID" : "NULL");
	setAdjustsDestination(nextPos != 0);
	m_adjustFinal = true;
	StateReturnType ret = AIInternalMoveToState::onEnter();
	if (nextPos)
	{
		Int followingIndex = m_index + 2;
		Coord2D delta;
		delta.x = nextPos->x - pos->x;
		delta.y = nextPos->y - pos->y;
		Real offset = coord2DLength(delta);
		if (ai->friend_getGoalPathPosition(followingIndex))
			offset += 40.0f;
		ai->setPathExtraDistance(offset);
		if (Glo012F0239 && TheCRCParameterCheck)
			((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
				"CritterDesync: setAdjustDestination(FALSE) 45");
		setAdjustsDestination(false);
	}
	else
	{
		if (Glo012F0239 && TheCRCParameterCheck)
			((BfmeCritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
				"CritterDesync: setAdjustDestination(m_adjustFinal=%s) 46", m_adjustFinal ? "TRUE" : "FALSE");
		setAdjustsDestination(m_adjustFinal);
		ai->setPathExtraDistance(0.0f);
	}
	return ret;
}
