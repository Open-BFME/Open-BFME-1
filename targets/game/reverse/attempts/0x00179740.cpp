// ?onEnter@AIFollowPathAsTeamState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9582 date=2026-11-02
// ?onEnter@AIFollowPathAsTeamState@@UAE?AW4StateReturnType@@XZ retail 0x00179740 (670 B, ret at +0x29D).
// BFME 2 donor: open-bfme-2 45afcff3a6 Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp
// (AIFollowPathAsTeamState::onEnter, BFME 2 0x0034E3A5) ported to BFME 1 offsets; ZH AIStateMachine::getGoalPathPosition
// over a real STLport vector<Coord3D> at state machine +0x44 (inlined twice, out of line via ILT 0xA9D4 the third time).
// cl: /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include <math.h>
typedef bool Bool;
typedef float Real;
typedef int Int;
enum StateReturnType { STATE_CONTINUE = 0, STATE_FAILURE = -2 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;
	Real y;
	Real length() const { return (Real)sqrt(x * x + y * y); }
};

class Path
{
public:
	const Coord3D *getPoint(Int i) const
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
	Int getCommandSource()
	{
		typedef Int (AIUpdateInterface::*Slot)();
		return (this->*(*(Slot *)&((*(void ***)this)[128])))();
	}
	unsigned char m_pad04[0x30 - 0x04];
	Path *m_goalPath;
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
extern void j_0000a9d4(void);
typedef void (__cdecl *BfmeCritterDesyncLog)(void *, const char *, ...);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
protected:
	Object *getMachineOwner() const { return m_machine->getOwner(); }
	void setAdjustsDestination(Bool b) { m_adjustDestination = b; }
	unsigned char m_pad04[0x1c - 0x04];
	StateMachine *m_machine;
	unsigned char m_pad20[4];
	Coord3D m_goalPosition;
	unsigned char m_pad30[0x4c - 0x30];
	Bool m_adjustDestination;
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
	Int m_lastCommandSource;
	AttackMoveMachine *m_attackMove;
	Int m_64;
	Bool m_rva68;
};

static __forceinline Coord3D *getPathPoint(AIUpdateInterface *ai, Int index)
{
	typedef Coord3D *(AIUpdateInterface::*GetPointCall)(Int);
	union
	{
		void (*asFunction)(void);
		GetPointCall asMember;
	} call;
	call.asFunction = j_0000a9d4;
	return (ai->*call.asMember)(index);
}

StateReturnType AIFollowPathAsTeamState::onEnter()
{
	Object *obj = getMachineOwner();
	AIUpdateInterface *ai = obj->getAI();
	m_index = 0;
	if (m_attackMove)
	{
		m_attackMove->slot5();
		m_attackMove->slot8(0);
	}
	m_lastCommandSource = ai->getCommandSource();
	m_rva68 = false;
	m_rva5B = false;
	const Coord3D *pos = ai->m_goalPath->getPoint(m_index);
	if (pos == 0)
		return STATE_FAILURE;
	m_64 = ai->m_rva1A0;
	m_goalPosition = *pos;
	const Coord3D *nextPos = ai->m_goalPath->getPoint(m_index + 1);
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
		nextPos = ai->m_goalPath->getPoint(m_index + 1);
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
		Real offset = delta.length();
		if (getPathPoint(ai, followingIndex))
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
