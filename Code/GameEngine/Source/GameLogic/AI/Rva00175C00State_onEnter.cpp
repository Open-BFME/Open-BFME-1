// cl: /DNDEBUG /MD
// Retail 0x00175C00: enter the state using the machine goal and current frame.

enum StateReturnType
{
    STATE_CONTINUE = 0,
    STATE_SUCCESS = -1,
    STATE_FAILURE = -2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
    char m_unknown[0x3c];

public:
    int m_frame;
};

extern GameLogic *TheBfmeGameLogic;

struct Rva00175C00AIUpdate
{
    char m_unknown[0x33a];
    unsigned char m_pathFlag;
};

struct Rva00175C00Object
{
    char m_unknown[0x98];
    unsigned char m_statusFlag;
    char m_gap99[0x204 - 0x99];
    Rva00175C00AIUpdate *m_ai;
};

struct Rva00175C00StateMachine
{
    char m_unknown[0x10];
    Rva00175C00Object *m_owner;
};

class Rva00175C00State
{
    char m_unknown[0x18];
    Rva00175C00StateMachine *m_machine;
    char m_gap20[4];
    int m_goalFrame;
    int m_unknown28;

public:
    virtual StateReturnType onEnter();
};

void j_0000432c();
void j_0000e570();

typedef unsigned char (__fastcall *Rva00175C00IsGoalDestroyed)(Rva00175C00StateMachine *);
typedef void *(__fastcall *Rva00175C00GetGoalObject)(Rva00175C00StateMachine *);

StateReturnType Rva00175C00State::onEnter()
{
    m_unknown28 = 0;

    if (((Rva00175C00IsGoalDestroyed)j_0000432c)(m_machine))
        return STATE_SUCCESS;
    if (!((Rva00175C00GetGoalObject)j_0000e570)(m_machine))
        return STATE_SUCCESS;

    m_goalFrame = TheBfmeGameLogic->m_frame;
    if ((m_machine->m_owner->m_statusFlag & 8) ||
        m_machine->m_owner->m_ai->m_pathFlag)
        m_goalFrame += 7;

    return STATE_CONTINUE;
}
