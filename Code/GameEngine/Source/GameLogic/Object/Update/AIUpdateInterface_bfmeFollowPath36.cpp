// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

typedef bool Bool;

enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_AI = 1
};

enum StateID
{
    BFME_AI_FOLLOW_PATH_36 = 0x36
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
    virtual void setState(StateID state);
    void setGoalPosition(const Coord3D *pos);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
protected:
    virtual void bfmeFollowPath36(const _STL::vector<Coord3D> *path,
        Object *ignoreObject, int extra, int cmdSource);
    void playMoveVoiceResponse(const Coord3D *position);
public:
    void ignoreObstacle(Object *obj);

    unsigned char m_unmodelled_04[4];
    Object *m_object;
    unsigned char m_unmodelled_0C[0x30 - 0x0C];
    StateMachine *m_stateMachine;
    unsigned char m_unmodelled_34[0x48 - 0x34];
    CommandSourceType m_lastCommandSource;
    unsigned char m_unmodelled_4C[0x1A0 - 0x4C];
    int m_extra1A0;
};

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
