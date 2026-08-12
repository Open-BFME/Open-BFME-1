// cl: /DNDEBUG /MD /EHsc

#define DECLARE_TEN_SLOTS(prefix) \
    virtual void slot##prefix##0(); \
    virtual void slot##prefix##1(); \
    virtual void slot##prefix##2(); \
    virtual void slot##prefix##3(); \
    virtual void slot##prefix##4(); \
    virtual void slot##prefix##5(); \
    virtual void slot##prefix##6(); \
    virtual void slot##prefix##7(); \
    virtual void slot##prefix##8(); \
    virtual void slot##prefix##9()

class DozerAIInterface
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual int getMostRecentCommand();
};

class AIUpdateInterface
{
public:
    DECLARE_TEN_SLOTS(0);
    DECLARE_TEN_SLOTS(1);
    DECLARE_TEN_SLOTS(2);
    DECLARE_TEN_SLOTS(3);
    DECLARE_TEN_SLOTS(4);
    DECLARE_TEN_SLOTS(5);
    DECLARE_TEN_SLOTS(6);
    virtual void slot70();
    virtual void slot71();
    virtual void slot72();
    virtual void slot73();
    virtual void slot74();
    virtual void slot75();
    virtual void slot76();
    virtual void slot77();
    virtual void slot78();
    virtual DozerAIInterface *getDozerAIInterface();
    DECLARE_TEN_SLOTS(8);
    virtual void slot90();
    virtual void slot91();
    virtual void slot92();
    virtual void slot93();
    virtual void slot94();
    virtual void slot95();
    virtual bool isIdle();
};

#undef DECLARE_TEN_SLOTS

class Object
{
public:
    unsigned char padding[0x204];
    AIUpdateInterface *aiUpdate;
};

class StateMachine
{
public:
    unsigned char padding[0x10];
    Object *owner;
};

class State
{
public:
    unsigned char padding[0x1c];
    StateMachine *machine;
};

class DozerPrimaryStateMachine
{
public:
    static bool __cdecl isFortifyMostImportant(State *, void *);
};

// ?isFortifyMostImportant@DozerPrimaryStateMachine@@SA_NPAVState@@PAX@Z
bool __cdecl DozerPrimaryStateMachine::isFortifyMostImportant(State *state, void *)
{
    Object *dozer = state->machine->owner;
    AIUpdateInterface *ai = dozer->aiUpdate;
    if (!ai)
        return false;

    DozerAIInterface *dozerAI = ai->getDozerAIInterface();
    if (!dozerAI)
        return false;

    if (!ai->isIdle())
        return false;

    return dozerAI->getMostRecentCommand() == 2;
}
