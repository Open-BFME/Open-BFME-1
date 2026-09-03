// cl: /DNDEBUG /MD /EHsc
// BFME layout reconstruction of AITNGuardOuterState::update at 0x0018A7E0.

class Object;
class Team;
class TeamPrototype;

typedef int ObjectID;

enum StateReturnType
{
    STATE_CONTINUE = 0,
    STATE_SUCCESS = -1
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
    Object *findObjectByID( ObjectID id );
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
    unsigned char m_fields[0x1c2];
    unsigned char m_attackCommonTarget;

    const TeamPrototype *getTemplateInfo() const
    {
        return (TeamPrototype *)this;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
    unsigned char m_fields[4];
    TeamPrototype *m_prototype;

    const TeamPrototype *getPrototype() const
    {
        return m_prototype;
    }

    Object *getTeamTargetObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    Team *getTeam() const
    {
        return *(Team **)((const unsigned char *)this + 0x23c);
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void setGoalObject( const Object *object );

    Object *getGoalObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIAttackState
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual StateReturnType onEnter();
    virtual void slot04();
    virtual StateReturnType update();

    unsigned char m_fields[0x18];
    StateMachine *m_machine;

    Object *getMachineGoalObject()
    {
        return m_machine->getGoalObject();
    }

    StateMachine *getMachine()
    {
        return m_machine;
    }

};

class BfmeGuardMachine
{
public:
    unsigned char m_fields[0x10];
    Object *m_owner;
    unsigned char m_machineFields[0x3c];
    ObjectID m_nemesisID;

    Object *getOwner() const
    {
        return m_owner;
    }

    ObjectID getNemesisID() const
    {
        return m_nemesisID;
    }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AITNGuard.h
class AITNGuardOuterState
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual StateReturnType update();

    unsigned char m_stateFields[0x18];
    BfmeGuardMachine *m_machine;
    unsigned char m_unused[8];
    unsigned int m_attackGiveUpFrame;
    AIAttackState *m_attackState;
};

// ?update@AITNGuardOuterState@@UAE?AW4StateReturnType@@XZ
StateReturnType AITNGuardOuterState::update()
{
    Object *owner = m_machine->getOwner();
    Object *goalObj = m_attackState->getMachineGoalObject();
    if (goalObj)
    {
    }
    else
    {
        Object *teamVictim = 0;
        Object *nemesis =
            (*TheGameLogic).findObjectByID(m_machine->m_nemesisID);
        if (nemesis)
        {
            goalObj = nemesis;
        }

        if (goalObj == 0 &&
            owner->getTeam()->getPrototype()->getTemplateInfo()->m_attackCommonTarget)
        {
            teamVictim = owner->getTeam()->getTeamTargetObject();
            if (teamVictim)
                goalObj = teamVictim;

            m_attackState->getMachine()->setGoalObject(goalObj);
            return m_attackState->onEnter();
        }
    }

    return m_attackState->update();
}
