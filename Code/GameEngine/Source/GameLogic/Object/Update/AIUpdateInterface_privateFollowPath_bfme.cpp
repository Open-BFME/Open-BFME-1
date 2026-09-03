// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

typedef bool Bool;

enum CommandSourceType
{
    CMD_FROM_PLAYER = 0,
    CMD_FROM_AI = 1
};

struct Coord3D
{
    float x, y, z;
};

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

class AIUpdateInterface
{
protected:
    virtual void privateFollowPath(const _STL::vector<Coord3D> *path,
        Object *ignoreObject, CommandSourceType cmdSource, Bool exitProduction);
    void playMoveVoiceResponse(const Coord3D *position);

public:
    void ignoreObstacle(Object *obj);

    unsigned char m_unmodelled_04[4];
    Object *m_object;
    unsigned char m_unmodelled_0C[0x30 - 0x0C];
    StateMachine *m_stateMachine;
    unsigned char m_unmodelled_34[0x48 - 0x34];
    CommandSourceType m_lastCommandSource;
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
    m_stateMachine->setState(6 + (exitProduction ? 1 : 0));
}
