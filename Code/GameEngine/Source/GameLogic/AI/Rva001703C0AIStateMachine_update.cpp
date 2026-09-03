// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x001703C0: AIStateMachine::updateStateMachine.

typedef int ObjectID;
typedef unsigned int UnsignedInt;

enum StateReturnType
{
    STATE_CONTINUE = 0,
    STATE_SUCCESS = -1,
    STATE_FAILURE = -2
};

enum StateExitType
{
    EXIT_NORMAL = 0,
    EXIT_RESET = 1
};

struct Coord3D
{
    float x;
    float y;
    float z;
};

class Object;

class GameLogic
{
    unsigned char m_unreconstructed_000[0x3c];

public:
    UnsignedInt m_frame;
    Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class State
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void onExit(StateExitType status) = 0;
    virtual StateReturnType update() = 0;
};

class Rva00170460GoalHelper
{
public:
    void setGoalObject(const Object *object);
};

class StateMachine
{
public:
    void bfmeSetGoalPosition(const Coord3D *position);
};

class Rva001703C0AIStateMachine
{
    unsigned char m_unreconstructed_004[0x54];
    State *m_temporaryState;
    UnsignedInt m_temporaryStateFrameEnd;
    ObjectID m_goalObjectID;
    Coord3D m_goalPosition;

public:
    virtual StateReturnType updateStateMachine();
};

extern void j_0000cc84();

typedef StateReturnType (__fastcall *Rva001703C0BaseUpdate)(Rva001703C0AIStateMachine *machine);

StateReturnType Rva001703C0AIStateMachine::updateStateMachine()
{
    if (m_temporaryState)
    {
        StateReturnType status = m_temporaryState->update();
        if (m_temporaryStateFrameEnd < TheGameLogic->m_frame)
        {
            if (status == STATE_CONTINUE)
                status = STATE_SUCCESS;
        }
        if (status >= STATE_CONTINUE)
            return status;

        if (!m_temporaryState)
            return status;

        m_temporaryState->onExit(EXIT_NORMAL);
        Object *goalObject = TheGameLogic->findObjectByID(m_goalObjectID);
        ((Rva00170460GoalHelper *)this)->setGoalObject(goalObject);
        ((StateMachine *)this)->bfmeSetGoalPosition(&m_goalPosition);
        m_goalObjectID = 0;
        m_temporaryState = 0;
    }

    return ((Rva001703C0BaseUpdate)j_0000cc84)(this);
}
