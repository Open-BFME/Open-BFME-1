// AIStateMachine constructor at RVA 0x00185A20 (4930 bytes).
// Native factory callers and the installed table's name slot prove identity.
// Each registration preserves its decoded BFME ID and success/failure IDs.
// State names come from constructor literals plus their own virtual-name slots;
// inherited name slots are checked against the original class hierarchy.
// The local classes are constructor/layout views, not replacement vtable definitions.
// Proof: targets/game/reverse/identity_evidence/00185A20-ai-state-machine-constructor.md
// stlport
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "ascii_string.h"
#include "basetype.h"
class Object;
class Waypoint;
class Squad;
class StateMachine;
struct StateConditionInfo;
class State
{
  public:
    State(StateMachine *, AsciiString);
    virtual ~State();
    unsigned int m_id, m_successStateID, m_failureStateID;
    void *m_transitionStart, *m_transitionFinish, *m_transitionEnd;
    StateMachine *m_machine;
    bool m_sleepTransitionPending;
};
class AIInternalMoveToState : public State
{
  public:
    AIInternalMoveToState(StateMachine *, AsciiString);
    char m_24[0x2c];
};
#include <vector>
typedef std::vector<Coord3D> GoalPath;
class StateMachine
{
  public:
    StateMachine(Object *, AsciiString, bool = false);

  protected:
    // retail's StateMachine destructor is protected: ??1StateMachine@@MAE@XZ
    virtual ~StateMachine();

    void defineState(unsigned int, State *, unsigned int, unsigned int,
                     const StateConditionInfo * = 0);
    char m_04[0x40];
};
class AIStateMachine : public StateMachine
{
  public:
    AIStateMachine(Object *, AsciiString);
  protected:
    virtual ~AIStateMachine();

  public:
    GoalPath m_goalPath;
    Waypoint *m_goalWaypoint;
    Squad *m_goalSquad;
    State *m_temporaryState;
    int m_temporaryStateFrameEnd;
    unsigned int m_objectID60;
    Coord3D m_coord64;
};
class AIIdleState : public State
{
  public:
    AIIdleState(StateMachine *m) : State(m, AsciiString("AIIdleState"))
    {
        m_shouldLookForTargets = true;
        m_inited = false;
        m_initialSleepOffset = 0xffff;
    }
    virtual ~AIIdleState();
    unsigned short m_initialSleepOffset;
    bool m_shouldLookForTargets, m_inited;
};
class AIMoveToState : public AIInternalMoveToState
{
  public:
    AIMoveToState(StateMachine *m) : AIInternalMoveToState(m, AsciiString("AIMoveToState"))
    {
        m_50 = true;
    }
    virtual ~AIMoveToState();
    bool m_50;
};
class AIMoveToStateSA : public AIInternalMoveToState
{
  public:
    AIMoveToStateSA(StateMachine *m) : AIInternalMoveToState(m, AsciiString("AIMoveToStateSA"))
    {
        m_50 = 0;
        m_54 = false;
    }
    virtual ~AIMoveToStateSA();
    int m_50;
    bool m_54;
};
class AIMoveOutOfTheWayState : public AIInternalMoveToState
{
  public:
    AIMoveOutOfTheWayState(StateMachine *m)
        : AIInternalMoveToState(m, AsciiString("AIMoveOutOfTheWayState"))
    {
    }
    virtual ~AIMoveOutOfTheWayState();
};
class AIMoveAndTightenState : public AIInternalMoveToState
{
  public:
    AIMoveAndTightenState(StateMachine *m)
        : AIInternalMoveToState(m, AsciiString("AIMoveAndTightenState"))
    {
        m_54 = false;
        m_50 = 0;
    }
    virtual ~AIMoveAndTightenState();
    int m_50;
    bool m_54;
};
// The repeated +50/+54 initialization precedes the derived vtable store:
// these BFME states share a witnessed intermediate movement-state prefix.
class Rva00185C80MovePrefix : public AIInternalMoveToState
{
  public:
    Rva00185C80MovePrefix(StateMachine *m, const char *name)
        : AIInternalMoveToState(m, AsciiString(name))
    {
        m_54 = false;
        m_50 = 0;
    }
    int m_50;
    bool m_54;
};
class AIMoveAwayFromRepulsorsState : public Rva00185C80MovePrefix
{
  public:
    AIMoveAwayFromRepulsorsState(StateMachine *m)
        : Rva00185C80MovePrefix(m, "AIMoveAwayFromRepulsors")
    {
    }
    virtual ~AIMoveAwayFromRepulsorsState();
};
class AIWanderInPlaceState : public AIInternalMoveToState
{
  public:
    AIWanderInPlaceState(StateMachine *m)
        : AIInternalMoveToState(m, AsciiString("AIWanderInPlaceState"))
    {
        m_50 = 0;
        m_54 = 0;
        m_58 = 0;
        m_5c = 0;
        m_60 = 0;
    }
    virtual ~AIWanderInPlaceState();
    int m_50, m_54, m_58, m_5c, m_60;
};
class Rva00183C10 : public State
{
  public:
    Rva00183C10(StateMachine *);
    char m_24[0x50];
};
class AIAttackFollowWaypointPathState : public State
{
  public:
    AIAttackFollowWaypointPathState(StateMachine *, bool);
    char m_24[0x4c];
};
class AIFollowWaypointPathState : public State
{
  public:
    AIFollowWaypointPathState(StateMachine *, bool);
    char m_24[0x48];
};
class AIFollowWaypointPathExactState : public AIInternalMoveToState
{
  public:
    AIFollowWaypointPathExactState(StateMachine *m, bool b)
        : AIInternalMoveToState(m, AsciiString("AIFollowWaypointPathExactState"))
    {
        m_50 = 0;
        m_54 = b;
    }
    virtual ~AIFollowWaypointPathExactState();
    int m_50;
    bool m_54;
};
class AIFollowPathState : public State
{
  public:
    AIFollowPathState(StateMachine *, AsciiString = AsciiString("AIFollowPathState"));
    char m_24[0x38];
};
class AIFollowPathAsTeamState : public State
{
  public:
    AIFollowPathAsTeamState(StateMachine *, bool,
                            AsciiString = AsciiString("AIFollowPathAsTeamState"));
    char m_24[0x48];
};
class AIMoveAndEvacuateState : public AIInternalMoveToState
{
  public:
    AIMoveAndEvacuateState(StateMachine *m)
        : AIInternalMoveToState(m, AsciiString("AIMoveAndEvacuateState"))
    {
        m_50 = 0;
        m_54 = 0;
        m_58 = 0;
    }
    virtual ~AIMoveAndEvacuateState();
    int m_50, m_54, m_58;
};
class AIMoveAndDeleteState : public AIInternalMoveToState
{
  public:
    AIMoveAndDeleteState(StateMachine *m)
        : AIInternalMoveToState(m, AsciiString("AIMoveAndDeleteState"))
    {
        m_50 = false;
    }
    virtual ~AIMoveAndDeleteState();
    bool m_50;
};
class AIWaitState : public State
{
  public:
    AIWaitState(StateMachine *m) : State(m, AsciiString("AIWaitState")) {}
    virtual ~AIWaitState();
};
class AttackExitConditionsInterface;
class AIAttackState : public State
{
  public:
    AIAttackState(StateMachine *, bool, bool, bool, AttackExitConditionsInterface *);
    char m_24[0x30];
};
class AIStartAttackObjState : public State
{
  public:
    AIStartAttackObjState(StateMachine *m) : State(m, AsciiString("AIStartAttackObjState")) {}
    virtual ~AIStartAttackObjState();
};
class AIMoveOntoWallState : public State
{
  public:
    AIMoveOntoWallState(StateMachine *m) : State(m, AsciiString("AIMoveOntoWallState"))
    {
        m_24 = 0;
    }
    virtual ~AIMoveOntoWallState();
    int m_24;
};
class AIAttackSquadState : public State
{
  public:
    AIAttackSquadState(StateMachine *m) : State(m, AsciiString("AIAttackSquadState"))
    {
        m_24 = 0;
        m_28 = false;
    }
    virtual ~AIAttackSquadState();
    int m_24;
    bool m_28;
};
class AIWanderState : public State
{
  public:
    AIWanderState(StateMachine *);
    char m_24[0x50];
};
class AIPanicState : public State
{
  public:
    AIPanicState(StateMachine *);
    char m_24[0x50];
};
class AIMoveAwayPanicState : public Rva00185C80MovePrefix
{
  public:
    AIMoveAwayPanicState(StateMachine *m) : Rva00185C80MovePrefix(m, "AIMoveAwayPanicState") {}
    virtual ~AIMoveAwayPanicState();
};
class AIFearState : public Rva00185C80MovePrefix
{
  public:
    AIFearState(StateMachine *m) : Rva00185C80MovePrefix(m, "AIFearState")
    {
        m_58 = false;
        m_5c = 0;
    }
    virtual ~AIFearState();
    bool m_58;
    int m_5c;
};
class AICowerState : public State
{
  public:
    AICowerState(StateMachine *m) : State(m, AsciiString("AICowerState")) {}
    virtual ~AICowerState();
};
class AIUncontrollableCower : public AICowerState
{
  public:
    AIUncontrollableCower(StateMachine *m) : AICowerState(m)
    {
        m_24 = true;
    }
    virtual ~AIUncontrollableCower();
    bool m_24;
};
class AIMoveAwayAndCowerState : public Rva00185C80MovePrefix
{
  public:
    AIMoveAwayAndCowerState(StateMachine *m) : Rva00185C80MovePrefix(m, "AIMoveAwayAndCowerState")
    {
    }
    virtual ~AIMoveAwayAndCowerState();
};
class AIBackAwayAndCowerState : public State
{
  public:
    AIBackAwayAndCowerState(StateMachine *m) : State(m, AsciiString("AIBackAwayAndCowerState"))
    {
        m_24 = 0;
    }
    virtual ~AIBackAwayAndCowerState();
    int m_24;
};
class AIDeadState : public State
{
  public:
    AIDeadState(StateMachine *m) : State(m, AsciiString("AIDeadState")) {}
    virtual ~AIDeadState();
};
class AIDockState : public State
{
  public:
    AIDockState(StateMachine *m) : State(m, AsciiString("AIDockState"))
    {
        m_24 = 0;
        m_28 = false;
    }
    virtual ~AIDockState();
    int m_24;
    bool m_28;
};
class AIHarvestState : public State
{
  public:
    AIHarvestState(StateMachine *m) : State(m, AsciiString("AIHarvestState"))
    {
        m_24 = 0;
        m_28 = false;
    }
    virtual ~AIHarvestState();
    int m_24;
    bool m_28;
};
class AIEnterState : public AIInternalMoveToState
{
  public:
    AIEnterState(StateMachine *m) : AIInternalMoveToState(m, AsciiString("AIEnterState"))
    {
        m_50 = 0;
    }
    virtual ~AIEnterState();
    int m_50;
};
class AICombineState : public AIInternalMoveToState
{
  public:
    AICombineState(StateMachine *m) : AIInternalMoveToState(m, AsciiString("AICombineState")) {}
    virtual ~AICombineState();
};
class AIEnterAndAttackState : public AIInternalMoveToState
{
  public:
    AIEnterAndAttackState(StateMachine *m)
        : AIInternalMoveToState(m, AsciiString("AIEnterAndAttackState"))
    {
        m_50 = 0;
        m_54 = 0;
    }
    virtual ~AIEnterAndAttackState();
    int m_50, m_54;
};
class AIExitState : public State
{
  public:
    AIExitState(StateMachine *m) : State(m, AsciiString("AIExitState"))
    {
        m_24 = 0;
    }
    virtual ~AIExitState();
    int m_24;
};
class AIHordeEnterState : public State
{
  public:
    AIHordeEnterState(StateMachine *m) : State(m, AsciiString("AIHordeEnterState")) {}
    virtual ~AIHordeEnterState();
};
class AIHordeExitState : public State
{
  public:
    AIHordeExitState(StateMachine *m) : State(m, AsciiString("AIHordeExitState")) {}
    virtual ~AIHordeExitState();
};
class AIGuardState : public State
{
  public:
    AIGuardState(StateMachine *m) : State(m, AsciiString("AIGuardState"))
    {
        m_24 = 0;
    }
    virtual ~AIGuardState();
    int m_24;
};
class AIGuardRetaliateState : public State
{
  public:
    AIGuardRetaliateState(StateMachine *m) : State(m, AsciiString("AIGuardRetaliateState"))
    {
        m_24 = 0;
    }
    virtual ~AIGuardRetaliateState();
    int m_24;
};
class AITunnelNetworkGuardState : public State
{
  public:
    AITunnelNetworkGuardState(StateMachine *m) : State(m, AsciiString("AITunnelNetworkGuardState"))
    {
        m_24 = 0;
    }
    virtual ~AITunnelNetworkGuardState();
    int m_24;
};
class AIHuntState : public State
{
  public:
    AIHuntState(StateMachine *m) : State(m, AsciiString("AIHuntState"))
    {
        m_24 = 0;
        m_28 = 0;
    }
    virtual ~AIHuntState();
    int m_24, m_28;
};
class AIAttackAreaState : public State
{
  public:
    AIAttackAreaState(StateMachine *m) : State(m, AsciiString("AIAttackAreaState"))
    {
        m_24 = 0;
        m_28 = 0;
    }
    virtual ~AIAttackAreaState();
    int m_24, m_28;
};
class AIFaceState : public AIIdleState
{
  public:
    AIFaceState(StateMachine *m, int mode) : AIIdleState(m)
    {
        m_mode = mode;
        m_canTurnInPlace = false;
    }
    virtual ~AIFaceState();
    int m_mode;
    bool m_canTurnInPlace;
};
class AIPickUpCrateState : public AIInternalMoveToState
{
  public:
    AIPickUpCrateState(StateMachine *m)
        : AIInternalMoveToState(m, AsciiString("AIAttackPickUpCrateState"))
    {
        m_50 = 0;
    }
    virtual ~AIPickUpCrateState();
    int m_50;
};
class AIBusyState : public State
{
  public:
    AIBusyState(StateMachine *m) : State(m, AsciiString("AIBusyState")) {}
    virtual ~AIBusyState();
};
class AIRampageState : public State
{
  public:
    AIRampageState(StateMachine *m) : State(m, AsciiString("AIRampageState"))
    {
        m_24 = false;
        m_28 = 0;
        m_2c = -1;
    }
    virtual ~AIRampageState();
    bool m_24;
    int m_28, m_2c;
};
class AIMoveToPositionAndDieState : public AIInternalMoveToState
{
  public:
    AIMoveToPositionAndDieState(StateMachine *m)
        : AIInternalMoveToState(m, AsciiString("AIMoveToPositionAndDieState"))
    {
        m_50 = false;
    }
    virtual ~AIMoveToPositionAndDieState();
    bool m_50;
};
class AIMoveToPositionAndEnterState : public AIMoveToState
{
  public:
    AIMoveToPositionAndEnterState(StateMachine *m) : AIMoveToState(m) {}
    virtual ~AIMoveToPositionAndEnterState();
};
class AIQuarrelState : public State
{
  public:
    AIQuarrelState(StateMachine *m) : State(m, AsciiString("AIQuarrelState")) {}
    virtual ~AIQuarrelState();
};

typedef char AIStateMachineSize[sizeof(AIStateMachine) == 0x70 ? 1 : -1];
typedef char StateSize[sizeof(State) == 0x24 ? 1 : -1];
typedef char MoveStateSize[sizeof(AIInternalMoveToState) == 0x50 ? 1 : -1];

AIStateMachine::AIStateMachine(Object *obj, AsciiString name) : StateMachine(obj, name)
{
    m_goalPath.clear();
    m_goalWaypoint = 0;
    m_goalSquad = 0;
    m_objectID60 = 0;
    m_coord64.zero();
    m_temporaryState = 0;
    m_temporaryStateFrameEnd = 0;
    defineState(0, new AIIdleState(this), 0, 0);
    defineState(1, new AIMoveToState(this), 0, 0);
    defineState(63, new AIMoveToStateSA(this), 0, 0);
    defineState(26, new AIMoveOutOfTheWayState(this), 0, 0);
    defineState(27, new AIMoveAndTightenState(this), 0, 0);
    defineState(40, new AIMoveAwayFromRepulsorsState(this), 41, 41);
    defineState(41, new AIWanderInPlaceState(this), 40, 40);
    defineState(33, new Rva00183C10(this), 0, 0);
    defineState(35, new AIAttackFollowWaypointPathState(this, true), 0, 0);
    defineState(34, new AIAttackFollowWaypointPathState(this, false), 0, 0);
    defineState(2, new AIFollowWaypointPathState(this, true), 0, 0);
    defineState(3, new AIFollowWaypointPathState(this, false), 0, 0);
    defineState(4, new AIFollowWaypointPathExactState(this, true), 0, 0);
    defineState(5, new AIFollowWaypointPathExactState(this, false), 0, 0);
    defineState(6, new AIFollowPathState(this), 0, 0);
    defineState(54, new AIFollowPathAsTeamState(this, false), 0, 0);
    defineState(61, new AIFollowPathAsTeamState(this, true), 0, 0);
    defineState(7, new AIFollowPathState(this), 0, 0);
    defineState(28, new AIMoveAndEvacuateState(this), 0, 0);
    defineState(29, new AIMoveAndEvacuateState(this), 30, 30);
    defineState(30, new AIMoveAndDeleteState(this), 0, 0);
    defineState(8, new AIWaitState(this), 0, 0);
    defineState(9, new AIAttackState(this, false, false, false, 0), 0, 0);
    defineState(10, new AIStartAttackObjState(this), 50, 50);
    defineState(50, new AIAttackState(this, false, true, false, 0), 0, 0);
    defineState(11, new AIStartAttackObjState(this), 51, 51);
    defineState(51, new AIAttackState(this, false, true, true, 0), 0, 0);
    defineState(43, new AIMoveOntoWallState(this), 0, 0);
    defineState(12, new AIAttackState(this, true, true, false, 0), 0, 0);
    defineState(23, new AIAttackSquadState(this), 0, 0);
    defineState(18, new AIWanderState(this), 0, 40);
    defineState(19, new AIPanicState(this), 0, 40);
    defineState(20, new AIMoveAwayPanicState(this), 21, 0);
    defineState(21, new AIFearState(this), 0, 0);
    defineState(48, new AICowerState(this), 0, 0);
    defineState(57, new AIUncontrollableCower(this), 0, 0);
    defineState(22, new AIMoveAwayAndCowerState(this), 48, 0);
    defineState(32, new AIBackAwayAndCowerState(this), 0, 0);
    defineState(13, new AIDeadState(this), 0, 0);
    defineState(14, new AIDockState(this), 0, 0);
    defineState(47, new AIHarvestState(this), 0, 0);
    defineState(15, new AIEnterState(this), 0, 0);
    defineState(60, new AICombineState(this), 0, 0);
    defineState(49, new AIEnterAndAttackState(this), 10, 10);
    defineState(38, new AIExitState(this), 0, 0);
    defineState(52, new AIHordeEnterState(this), 0, 0);
    defineState(53, new AIHordeExitState(this), 0, 0);
    defineState(16, new AIGuardState(this), 0, 0);
    defineState(62, new AIGuardRetaliateState(this), 0, 0);
    defineState(24, new AITunnelNetworkGuardState(this), 0, 0);
    defineState(17, new AIHuntState(this), 0, 0);
    defineState(31, new AIAttackAreaState(this), 0, 0);
    defineState(36, new AIFaceState(this, 1), 0, 0);
    defineState(37, new AIFaceState(this, 0), 0, 0);
    defineState(59, new AIFaceState(this, 2), 0, 0);
    defineState(39, new AIPickUpCrateState(this), 0, 0);
    defineState(42, new AIBusyState(this), 0, 0);
    defineState(45, new AIRampageState(this), 0, 0);
    defineState(55, new AIMoveToPositionAndDieState(this), 0, 0);
    defineState(56, new AIMoveToPositionAndEnterState(this), 0, 0);
    defineState(58, new AIQuarrelState(this), 0, 0);
}
