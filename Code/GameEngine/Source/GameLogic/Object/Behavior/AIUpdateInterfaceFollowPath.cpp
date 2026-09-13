// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?privateFollowPath@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
//
// Open-BFME: the three AIUpdateInterface handlers that take a whole path.
//
//   ?privateFollowPath@   0x00278950, 197 bytes, state 6 or 7
//   ?bfmeFollowPath36@    0x00278A50, 181 bytes, state 0x36
//   ?bfmeFollowPath3D@    0x00278B40, 181 bytes, state 0x3D
//
// One contiguous run and one body: refuse the order if the object cannot move,
// clear the state machine, take the LAST point of the path as the goal
// position, play the move voice for a player or AI command, hand the whole
// vector to the state machine's path step at +0x30, record the command source,
// tell the AI to ignore one obstacle object, and set the state.
//
// privateFollowPath is the named one and it carries the pair 6 and 7 -- follow
// a path, or follow it as a production exit -- chosen by its Bool argument,
// which is also what suppresses the voice response. The two BFME additions drop
// that argument, always play the voice, and take an extra integer they write
// straight to +0x1A0.
//
// That +0x1A0 store is worth stating rather than repeating. Both BFME bodies
// declared a member for it and then bypassed the member, writing through
// `*(volatile int *)((unsigned char *)this + 0x1A0)`. The member and the cast
// are both kept below because the cast is what retail's bytes require and the
// member is what says where it lands. The same shape appears one line earlier:
// the command source is read back through a `const volatile int *` alias of the
// argument rather than the argument itself, which is what keeps the reload in
// the right place.
//
// The three files disagreed only in spelling. StateMachine::setState took an
// `int` in two of them and a one-value `enum StateID` in the third, which made
// the third's state look typed and the other two's look arbitrary; they are the
// same untyped slot, and the four state numbers are named together below.

#include <vector>

typedef bool Bool;

enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_AI = 1
};

enum StateID
{
    BFME_AI_FOLLOW_PATH = 0x06,
    BFME_AI_FOLLOW_EXIT_PRODUCTION_PATH = 0x07,
    BFME_AI_FOLLOW_PATH_36 = 0x36,
    BFME_AI_FOLLOW_PATH_3D = 0x3D
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
    float x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    Bool isMobile() const;
};

class BfmeSub30_7F0
{
public:
    void step2(void *path);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void clear();
    virtual void slot18();
    virtual void slot1C();
    virtual void setState(int state);
    void setGoalPosition(const Coord3D *pos);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
    virtual void privateFollowPath(const _STL::vector<Coord3D> *path,
        Object *ignoreObject, CommandSourceType cmdSource, Bool exitProduction);
    virtual void bfmeFollowPath36(const _STL::vector<Coord3D> *path,
        Object *ignoreObject, int extra, int cmdSource);
    virtual void bfmeFollowPath3D(const _STL::vector<Coord3D> *path,
        Object *ignoreObject, int extra, int cmdSource);

    void playMoveVoiceResponse(const Coord3D *position);

public:
    void ignoreObstacle(Object *obj);

    unsigned char m_unmodelled_04[4];
    Object *m_object;                           // +0x08
    unsigned char m_unmodelled_0C[0x30 - 0x0C];
    StateMachine *m_stateMachine;               // +0x30
    unsigned char m_unmodelled_34[0x48 - 0x34];
    CommandSourceType m_lastCommandSource;      // +0x48
    unsigned char m_unmodelled_4C[0x1A0 - 0x4C];
    int m_extra1A0;                             // +0x1A0, written by raw cast
};

void AIUpdateInterface::privateFollowPath(const _STL::vector<Coord3D> *path,
    Object *ignoreObject, CommandSourceType cmdSource, Bool exitProduction)
{
    if (!m_object->isMobile())
        return;

    m_stateMachine->clear();
    if (path->size() > 0)
    {
        const Coord3D *last = &(*path)[path->size() - 1];
        const Coord3D goal = *last;
        m_stateMachine->setGoalPosition(&goal);
        if (!exitProduction &&
            (cmdSource == CMD_FROM_PLAYER || cmdSource == CMD_FROM_AI))
            playMoveVoiceResponse(&goal);
    }
    reinterpret_cast<BfmeSub30_7F0 *>(m_stateMachine)->step2(
        const_cast<_STL::vector<Coord3D> *>(path));
    m_lastCommandSource = cmdSource;
    ignoreObstacle(ignoreObject);
    m_stateMachine->setState(BFME_AI_FOLLOW_PATH + (exitProduction ? 1 : 0));
}

void AIUpdateInterface::bfmeFollowPath36(const _STL::vector<Coord3D> *path,
    Object *ignoreObject, int extra, int cmdSource)
{
    const volatile int *commandSource = &cmdSource;
    if (!m_object->isMobile())
        return;

    m_stateMachine->clear();
    if (path->size() > 0)
    {
        const Coord3D *last = &(*path)[path->size() - 1];
        const Coord3D goal = *last;
        m_stateMachine->setGoalPosition(&goal);
        const int source = *commandSource;
        if (source == CMD_FROM_PLAYER || source == CMD_FROM_AI)
            playMoveVoiceResponse(&goal);

        reinterpret_cast<BfmeSub30_7F0 *>(m_stateMachine)->step2(
            const_cast<_STL::vector<Coord3D> *>(path));
        m_lastCommandSource = (CommandSourceType)source;
        ignoreObstacle(ignoreObject);
        *reinterpret_cast<volatile int *>(reinterpret_cast<unsigned char *>(this) + 0x1A0) = extra;
        m_stateMachine->setState(BFME_AI_FOLLOW_PATH_36);
    }
}

void AIUpdateInterface::bfmeFollowPath3D(const _STL::vector<Coord3D> *path,
    Object *ignoreObject, int extra, int cmdSource)
{
    const volatile int *commandSource = &cmdSource;
    if (!m_object->isMobile())
        return;

    m_stateMachine->clear();
    if (path->size() > 0)
    {
        const Coord3D *last = &(*path)[path->size() - 1];
        const Coord3D goal = *last;
        m_stateMachine->setGoalPosition(&goal);
        const int source = *commandSource;
        if (source == CMD_FROM_PLAYER || source == CMD_FROM_AI)
            playMoveVoiceResponse(&goal);

        reinterpret_cast<BfmeSub30_7F0 *>(m_stateMachine)->step2(
            const_cast<_STL::vector<Coord3D> *>(path));
        m_lastCommandSource = (CommandSourceType)source;
        ignoreObstacle(ignoreObject);
        *reinterpret_cast<volatile int *>(reinterpret_cast<unsigned char *>(this) + 0x1A0) = extra;
        m_stateMachine->setState(BFME_AI_FOLLOW_PATH_3D);
    }
}
