// cl: /O2 /MD /EHsc

class BfmeElemCU
{
public:
    BfmeElemCU();
    ~BfmeElemCU();
    void *m_value;
};
class Rva008947A0Elem : public BfmeElemCU
{
public:
    Rva008947A0Elem();
    ~Rva008947A0Elem();
};
class Rva00893030Manager { public: void rva00892F00(BfmeElemCU *, int); };
extern Rva00893030Manager *g_rva00893030Manager;
extern int g_bfme1017I;
extern char *g_bfmeHolderBU;
extern int g_rva00891FA0Ready;
extern int g_rva00891FA0Value;
extern unsigned char g_rva0133780C;
extern int g_stack01338748;
class BfmeTracker4310;
extern BfmeTracker4310 *g_bfmeTracker4310;
struct Rva00899560Pool;
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void d_00894380();
extern void d_00891fa0();
extern void d_00896710();
extern void d_008a15f0();
extern void d_008a30c0();
extern void j_00897470();
class Gen_008C6BC0 { public: void bfmeReset(); };
class Rva008A1940Queue { public: void flush(); };
class BfmeSlotDispatcher1281 { public: void bfmeFlushSlots1289(); };
class BfmeFilterWalk1236 { public: void bfmeFilterWalk1236(); };
class Rva008A15F0Call { public: void method(int); };
class Rva00896710Call { public: void method(); };
class Rva008A30C0Call { public: void method(); };
typedef void (Rva00896710Call::*TrackerCall)();
typedef void (Rva008A15F0Call::*TimerCall)(int);
typedef void (Rva008A30C0Call::*IdleCall)();
template<class T> T memberCall(void (*p)()) { union {void (*plain)(); T member;} call; call.plain = p; return call.member; }
struct Rva00892A70Interval { char pad[0x24]; unsigned interval; };
struct Rva00892A70State { char pad[0xc]; Rva00892A70Interval *movie; char pad10[0x20]; unsigned remainder; };
struct Rva00894660Value
{
    void *vptr;
    union { unsigned flags; struct { unsigned kind:6; unsigned rest:26; }; };
    bool isUndefined() const { return ((flags >> 15) & 1) == 0; }
    char pad08[0x48];
    Rva00892A70State *state;
};
struct Rva00894660Node { char pad[0x58]; Rva00894660Value *value; };
struct Rva00894660Root { char pad[0x122c]; Rva00894660Node **nodes; char pad1230[8]; int count; };
__forceinline Rva00894660Value *currentRva00894660Value() { return (*((Rva00894660Root *)g_bfmeHolderBU)->nodes)->value; }
__forceinline bool isTickAnimation(Rva00894660Value *value) { return value->kind == 0x12 && !value->isUndefined(); }
// ?Rva00892A70@@YAHI@Z
// Open BFME 2: Code/Libraries/Source/Apt/Apt.cpp.
static int Rva00892A70(unsigned elapsed)
{
    int advanced = 0;
    if (!isTickAnimation(currentRva00894660Value())) return advanced;
    Rva00892A70State *state = currentRva00894660Value()->state;
    elapsed += state->remainder;
    unsigned interval = state->movie->interval;
    while (elapsed >= interval)
    {
        (((Rva008A15F0Call *)g_bfmeHolderBU)->*memberCall<TimerCall>(d_008a15f0))(interval);
        ((BfmeFilterWalk1236 *)&((Rva00894660Root *)g_bfmeHolderBU)->nodes)->bfmeFilterWalk1236();
        ((Rva008A1940Queue *)g_bfmeHolderBU)->flush();
        ((BfmeSlotDispatcher1281 *)g_bfmeHolderBU)->bfmeFlushSlots1289();
        (((Rva00896710Call *)g_bfmeTracker4310)->*memberCall<TrackerCall>(d_00896710))();
        elapsed -= interval;
        g_rva00891FA0Value += interval;
        advanced = 1;
        if (!isTickAnimation(currentRva00894660Value())) return advanced;
        if (g_rva00891FA0Ready) break;
    }
    if (isTickAnimation(currentRva00894660Value())) currentRva00894660Value()->state->remainder = elapsed;
    return advanced;
}

// ?bfmeRva00894660@@YAXI@Z
// Open BFME 2: Code/Libraries/Source/Apt/Apt.cpp.
void bfmeRva00894660(unsigned elapsed)
{
    Rva008947A0Elem entries[96];
    g_rva00893030Manager->rva00892F00(entries, 96);
    if (g_bfme1017I) d_00894380();
    else
    {
        Rva00894660Value *value = currentRva00894660Value();
        if (value && isTickAnimation(value))
        {
            if (Rva00892A70(elapsed)) d_00891fa0();
        }
        else
        {
            (((Rva00896710Call *)g_bfmeTracker4310)->*memberCall<TrackerCall>(d_00896710))();
            ((Rva00894660Root *)g_bfmeHolderBU)->count = 0;
        }
    }
    ((Gen_008C6BC0 *)&g_stack01338748)->bfmeReset();
    (((Rva008A30C0Call *)g_rva8CD130IdleHook)->*memberCall<IdleCall>(d_008a30c0))();
    if (g_rva0133780C)
    {
        ((void (__cdecl *)(bool))j_00897470)(false);
        g_rva0133780C = 0;
    }
}
