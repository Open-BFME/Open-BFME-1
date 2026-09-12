// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2
// BFME DozerActionState lifecycle; constructor 002B76F0 installs vtable 010C6F70.
// Slots +10/+14 route to 002B6390/002B63E0; both bodies verified byte-for-byte.
typedef bool Bool;
typedef int Int;

enum StateReturnType { STATE_CONTINUE = 0, STATE_FAILURE = -2 };
enum StateExitType { STATE_EXIT_UNKNOWN = 0 };
enum { DOZER_TASK_INVALID = -1 };

class Object;
class AIUpdateInterface;
class DozerAIInterface;

template <int N>
class DozerAIInterfaceSlots : public DozerAIInterfaceSlots<N - 1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template <> class DozerAIInterfaceSlots<0> {};

template <int N>
class AIUpdateInterfaceSlots : public AIUpdateInterfaceSlots<N - 1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template <> class AIUpdateInterfaceSlots<0> {};

class StateMachine
{
public:
    virtual void slot00() = 0;
    virtual void slot04() = 0;
    virtual void slot08() = 0;
    virtual void slot0c() = 0;
    virtual void slot10() = 0;
    virtual void slot14() = 0;
    virtual void resetToDefaultState() = 0;

    unsigned char m_beforeOwner[0x0c];
    Object *m_owner;
};

class State
{
public:
    virtual void slot00() = 0;

    Object *getMachineOwner() const
    {
        return m_machine->m_owner;
    }

protected:
    unsigned char m_beforeMachine[0x18];
    StateMachine *m_machine;
    unsigned char m_afterMachine[4];
};

class DozerAIInterface : public DozerAIInterfaceSlots<10>
{
public:
    virtual void setCurrentTask(Int task) = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void finishBuildingSound() = 0;
};

class AIUpdateInterface : public AIUpdateInterfaceSlots<79>
{
public:
    virtual DozerAIInterface *getDozerAIInterface() = 0;
};

class Object
{
public:
    virtual void slot00() = 0;

    AIUpdateInterface *getAIUpdateInterface() const
    {
        return m_ai;
    }

private:
    unsigned char m_beforeAi[0x200];
    AIUpdateInterface *m_ai;
};

class DozerActionState : public State
{
public:
    virtual StateReturnType onEnter();
    virtual void onExit(StateExitType status);

private:
    Int m_task;
    StateMachine *m_actionMachine;
};

StateReturnType DozerActionState::onEnter()
{
    Object *dozer = getMachineOwner();
    if (!dozer->getAIUpdateInterface())
        return STATE_FAILURE;

    DozerAIInterface *dozerAI = dozer->getAIUpdateInterface()->getDozerAIInterface();
    dozerAI->setCurrentTask(m_task);
    m_actionMachine->resetToDefaultState();
    return STATE_CONTINUE;
}

