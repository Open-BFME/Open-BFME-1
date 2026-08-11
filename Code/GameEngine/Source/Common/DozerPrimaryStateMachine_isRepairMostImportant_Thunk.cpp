// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: native Dozer repair-priority predicate.

class AIUpdateInterface;
class DozerAIInterface;

class Object
{
public:
    unsigned char m_pad[0x204];
    AIUpdateInterface *m_ai;
};

class StateMachine
{
public:
    unsigned char m_pad[0x10];
    Object *m_owner;
};

class State
{
public:
    unsigned char m_pad[0x1c];
    StateMachine *m_machine;
};

typedef DozerAIInterface *(__fastcall *GetDozerAIInterfaceProc)(AIUpdateInterface *);
typedef bool (__fastcall *IsIdleProc)(AIUpdateInterface *);
typedef int (__fastcall *GetMostRecentCommandProc)(DozerAIInterface *);

class DozerPrimaryStateMachine
{
public:
    static bool __cdecl isRepairMostImportant(State *state, void *);
};

// ?isRepairMostImportant@DozerPrimaryStateMachine@@SA_NPAVState@@PAX@Z
bool __cdecl DozerPrimaryStateMachine::isRepairMostImportant(State *state, void *)
{
    AIUpdateInterface *ai = state->m_machine->m_owner->m_ai;
    if (!ai)
        return false;

    DozerAIInterface *dozerAI =
        ((GetDozerAIInterfaceProc)(*(void ***)ai)[0x13c / sizeof(void *)])(ai);
    if (!dozerAI)
        return false;
    if (!((IsIdleProc)(*(void ***)ai)[0x180 / sizeof(void *)])(ai))
        return false;

    void **dozerVtable = *(void ***)dozerAI;
    return ((GetMostRecentCommandProc)dozerVtable[0x14 / sizeof(void *)])(dozerAI) == 1;
}
