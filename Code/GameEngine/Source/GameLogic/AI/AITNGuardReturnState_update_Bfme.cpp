// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction of AITNGuardReturnState::update at 0x00189C00.

typedef unsigned int ObjectID;

enum StateReturnType
{
    STATE_CONTINUE = 0,
    STATE_SUCCESS = -1,
    STATE_FAILURE = -2
};

class Object;
class Player;
class Team;

class GameLogic
{
public:
    Object *findObjectByID( ObjectID id );
};

class TunnelTracker
{
public:
    Object *getCurNemesis();
};

class Player
{
public:
    TunnelTracker *getTunnelSystem() const
    {
        return *(TunnelTracker **)((const unsigned char *)this + 0x22c);
    }
};

class Team
{
public:
    Object *getTeamTargetObject();
};

class Object
{
public:
    Player *getControllingPlayer() const;

    Team *getTeam() const
    {
        return *(Team **)((const unsigned char *)this + 0x23c);
    }

    ObjectID getID() const
    {
        return *(const ObjectID *)((const unsigned char *)this + 0x74);
    }
};

class BfmeGuardMachine
{
public:
    unsigned char m_fields[0x10];
    Object *m_owner;
    unsigned char m_machineFields[0x3c];
    ObjectID m_nemesisID;
};

class AIEnterState
{
public:
    virtual StateReturnType update();
};

class AITNGuardReturnState : public AIEnterState
{
public:
    virtual StateReturnType update();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();

    unsigned char m_stateFields[0x18];
    BfmeGuardMachine *m_machine;
};

// ?update@AITNGuardReturnState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITNGuardReturnState::update()
{
    Player *ownerPlayer = m_machine->m_owner->getControllingPlayer();
    Team *team = m_machine->m_owner->getTeam();
    Object *teamVictim = 0;
    if (team == 0 || (teamVictim = team->getTeamTargetObject()) == 0)
    {
        if (ownerPlayer != 0)
        {
            TunnelTracker *tunnels = ownerPlayer->getTunnelSystem();
            if (tunnels != 0)
            {
                Object *nemesis = tunnels->getCurNemesis();
                if (nemesis != 0)
                {
                    m_machine->m_nemesisID = nemesis->getID();
                    return STATE_FAILURE;
                }
            }
        }
    }
    else
    {
        m_machine->m_nemesisID = teamVictim->getID();
        return STATE_FAILURE;
    }

    return (StateReturnType)(AIEnterState::update() != STATE_CONTINUE ? STATE_SUCCESS : STATE_CONTINUE);
}
