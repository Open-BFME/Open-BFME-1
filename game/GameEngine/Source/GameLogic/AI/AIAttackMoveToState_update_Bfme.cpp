// cl: /DNDEBUG /MD /EHsc
// ?update@AIAttackMoveToState@@UAE?AW4StateReturnType@@XZ

typedef bool Bool;
typedef unsigned int UnsignedInt;
enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1 };

struct Coord3D {
    float x, y, z;
    float GetLengthEstimate() const;
};

class Object;

#define SLOT(n) virtual void slot##n() = 0;
class CurrentState {
public:
    SLOT(00) SLOT(04) SLOT(08) SLOT(0c) SLOT(10) SLOT(14) SLOT(18)
    virtual Bool isIdle() const = 0;
};
class StateMachine {
public:
    SLOT(00) SLOT(04) SLOT(08) SLOT(0c)
    virtual StateReturnType updateStateMachine() = 0;
    SLOT(14) SLOT(18) SLOT(1c)
    virtual StateReturnType setState(int) = 0;
    SLOT(24) SLOT(28) SLOT(2c) SLOT(30) SLOT(34)
    virtual void setGoalObject(Object *) = 0;
    Object *getGoalObject();
    void setGoalPosition(const Coord3D *);
    Bool isInIdleState() const { return m_currentState ? m_currentState->isIdle() : true; }
    unsigned char pad04[0x0c];
    Object *m_owner;
    unsigned char pad14[0x08];
    CurrentState *m_currentState;
    int m_goalObjectId;
    Coord3D m_goalPosition;
};

class AIUpdateInterface {
public:
    Object *checkForCrateToPickup();
    Object *getNextMoodTarget(Bool, Bool);
    unsigned char pad00[0x48];
    int m_commandSrc;
    unsigned char pad4c[0x335-0x4c];
    Bool m_bfmeFlag335;
};

class Rva0026F110 { public: void set(); };

class Object {
public:
    unsigned char pad00[0x38];
    Coord3D m_position;
    unsigned char pad44[0x204-0x44];
    AIUpdateInterface *m_ai;
    AIUpdateInterface *getAI() const { return m_ai; }
};

class GameLogic {
public:
    unsigned char pad00[0x3c];
    UnsignedInt m_frame;
    Object *findObjectByID(int);
};
extern GameLogic *TheGameLogic;
extern const float g_bfmeK1266C;
extern const float g_bfmeAttackMoveThreshold001885B0;

class AIMoveToState {
public:
    virtual StateReturnType onEnter();
    SLOT(04) SLOT(08) SLOT(0c) SLOT(10) SLOT(14)
    virtual StateReturnType update();
    unsigned char pad04[0x18];
    StateMachine *m_machine;
    unsigned char pad20[0x14];
    Coord3D m_pathGoalPosition;
    unsigned char pad40[0x14];
};

class AIAttackMoveToState : public AIMoveToState {
public:
    virtual StateReturnType update();
    int m_commandSrc;
    StateMachine *m_attackMoveMachine;
    UnsignedInt m_frameToSleepUntil;
    int m_retryCount;
    Coord3D m_goalPosition;
    int m_goalObjectId;
};
#undef SLOT

StateReturnType AIAttackMoveToState::update()
{
    Object *owner = m_machine->m_owner;
    AIUpdateInterface *ai = owner->getAI();
    Bool forceRetargetThisFrame = false;
    Bool shouldRepathThisFrame = false;

    if (!m_attackMoveMachine->isInIdleState()) {
        Object *goal = m_machine->getGoalObject();
        if (goal && goal != m_attackMoveMachine->getGoalObject()) {
            m_attackMoveMachine->setGoalObject(goal);
        }
        m_attackMoveMachine->updateStateMachine();
        if (!m_attackMoveMachine || !m_attackMoveMachine->isInIdleState()) {
            return STATE_CONTINUE;
        }
        forceRetargetThisFrame = true;
        shouldRepathThisFrame = true;
        ai->m_commandSrc = m_commandSrc;
    }

    if (m_attackMoveMachine->isInIdleState()) {
        Object *crate = ai->checkForCrateToPickup();
        if (crate) {
            m_attackMoveMachine->setGoalObject(crate);
            m_attackMoveMachine->setState(0x27);
            return STATE_CONTINUE;
        }
        Object *victim = ai->getNextMoodTarget(!forceRetargetThisFrame, false);
        if (victim) {
            ((Rva0026F110 *)ai)->set();
            m_attackMoveMachine->setGoalObject(victim);
            m_attackMoveMachine->setState(0x0a);
            ai->m_commandSrc = 2;
            ai->m_bfmeFlag335 = true;
            return STATE_CONTINUE;
        }
    }

    StateMachine *machine = m_machine;
    Coord3D oldGoal;
    oldGoal.x = machine->m_goalPosition.x;
    oldGoal.y = machine->m_goalPosition.y;
    oldGoal.z = machine->m_goalPosition.z;
    Object *goal = TheGameLogic->findObjectByID(m_goalObjectId);
    Coord3D newGoal;
    if (goal) {
        __asm {
            lea edx, [ebp+0x38]
            mov eax, [edx]
            mov ecx, [edx+4]
            mov edx, [edx+8]
            mov newGoal.x, eax
            mov newGoal.y, ecx
            mov newGoal.z, edx
        }
    }
    else {
        __asm {
            lea eax, [esi+0x64]
            mov ecx, [eax]
            mov edx, [eax+4]
            mov eax, [eax+8]
            mov newGoal.x, ecx
            mov newGoal.y, edx
            mov newGoal.z, eax
        }
    }
    newGoal.x -= oldGoal.x;
    newGoal.y -= oldGoal.y;
    newGoal.z -= oldGoal.z;
    if (newGoal.GetLengthEstimate() > g_bfmeK1266C) {
        if (goal)
            machine->setGoalObject(goal);
        else
            machine->setGoalPosition(&m_goalPosition);
        shouldRepathThisFrame = true;
    }

    UnsignedInt frame = TheGameLogic->m_frame;
    if (m_frameToSleepUntil > frame)
        return STATE_CONTINUE;
    else if (m_frameToSleepUntil == frame)
        shouldRepathThisFrame = true;

    if (shouldRepathThisFrame) {
        AIMoveToState::onEnter();
        
        
        m_pathGoalPosition.x = m_pathGoalPosition.y = m_pathGoalPosition.z = -100.0f;
        *(int *)((char *)this + 0x44) = -5;
    }
    StateReturnType ret = AIMoveToState::update();
    if (ret != STATE_CONTINUE) {
        if (m_retryCount < 1) return ret;
        float dx = owner->m_position.x - m_pathGoalPosition.x;
        float dy = owner->m_position.y - m_pathGoalPosition.y;
        if (dx*dx + dy*dy < g_bfmeAttackMoveThreshold001885B0) return ret;
        ret = STATE_CONTINUE;
        --m_retryCount;
        m_frameToSleepUntil = TheGameLogic->m_frame + 15;
    }
    return ret;
}
