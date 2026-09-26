// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?rva00893410InvokeStrings@@YAXPBDPAD0HZZ
// 00893410, 601B. cdecl varargs: name, output, scope, count, trailing strings.
// Physical contracts: docs/analysis/0x008cf740.md and retail entry through ret+258.
// The fixed nine-argument bfmeAssembleAN pin is a caller's incomplete prototype;
// this body walks trailing arguments from the fourth parameter and is variadic.
// Reused 16-byte string values: vptr+00 flags+04 holder+08 free-next+0C.
// Rva008A9B00RegistryCtor.cpp witnesses the same 16-byte constructor layout.
// Registry VA01337810: capacity+00 count+04 array+08. Free list VA01338478.
// Interpreter VA01338748: count+00 array+08. Allocation callback VA01337828.
// Calls in retail order: 89E680/8930C0/8CC940; alternative 8930C0;
// 89EC50/8A9B00/8927C0; 89E680/8CC940/8CF740/899770.
// EH states 0 and 2 destroy four-byte holders at EBP-98 and EBP-9C.
// EH state 1 (VA01056DAB) calls sized delete 00891A80 with pointer and 16;
// all three unwind predecessors are -1. No semantic class identity inferred.
#include <stdarg.h>


struct Rva00893410Block { unsigned short refs, length, capacity, flags; };
struct Rva00893410Pool { void *unused; void (__cdecl *free)(void *); };
extern Rva00893410Pool *g_bfmeStringPool1284;
extern Rva00893410Block Rva012D5298Empty;
class BfmeStrVKI {
public:
    BfmeStrVKI(const char *p) { bfmeSetVKI(p); }
    void __declspec(nothrow) bfmeSetVKI(const char *p);
    ~BfmeStrVKI() { Rva00893410Block *p = block; if (--p->refs == 0) g_bfmeStringPool1284->free(p); }
    Rva00893410Block *block;
};
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned n); };
extern void * (__cdecl *Rva01337828Allocate)(unsigned);
class Rva008B2EA0Node { public: void append(void *); };
class Rva00899770 { public: void exportString(char *); };
class Rva008CF740Value;
class Rva008CF740 { public: void run(Rva008CF740Value *, Rva008CF740Value *, int); };

class Rva008A9B00 {
public:
    virtual void retain();
    virtual void release();
    bool permanent() const { return ((flags >> 30) & 1) != 0; }
    unsigned flags;
    Rva00893410Block *block;
    Rva008A9B00 *next;
    Rva008A9B00();
    static void *operator new(unsigned n) { return Rva01337828Allocate(n); }
    static void operator delete(void *p, unsigned size);
};
struct Rva00893410Registry {
    int capacity, count;
    Rva008A9B00 **values;
    void addOrClear(Rva008A9B00 *v) {
        if (count >= capacity) v->flags &= 0xbfffffff;
        else values[count++] = v;
    }
};
extern Rva00893410Registry *g_rva8CD130IdleHook;
extern Rva008A9B00 *Rva01338478FreeHead;
class BfmeNestedBE;
extern BfmeNestedBE *Rva008930C0AptLookup(int);
class Rva008AE770Stack {
public:
    int count, unused;
    Rva008A9B00 **values;
    Rva008A9B00 *top() { return values[count - 1]; }
    Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int);
    void push(Rva008A9B00 *v) {
        values[count++] = v;
        if (!v->permanent()) v->retain();
    }
};
extern Rva008AE770Stack Rva01338748Stack;

static __forceinline Rva008A9B00 *createValue() {
    Rva008A9B00 *value = Rva01338478FreeHead;
    if (value) {
        Rva01338478FreeHead = value->next;
        g_rva8CD130IdleHook->addOrClear(value);
        if (value->block != &Rva012D5298Empty)
            ((BfmeStrVKK *)&value->block)->bfmeTruncVKK(0);
        return value;
    }
    return new Rva008A9B00;
}

void rva00893410InvokeStrings(const char *name, char *output, const char *scope, int count, ...)
{
    Rva008A9B00 *arguments[32];
    void *receiver;
    int i = 0;
    if (scope) {
        BfmeStrVKI value(scope);
        receiver = Rva01338748Stack.createString(Rva008930C0AptLookup(0), 0, &value, 1, 1, 0);
    } else receiver = Rva008930C0AptLookup(0);
    int total = count;
    va_list args;
    va_start(args, count);
    for (; i < total; ++i) {
        Rva008A9B00 *value = createValue();
        arguments[i] = value;
        ((Rva008B2EA0Node *)value)->append(va_arg(args, void *));
    }
    va_end(args);
    for (; i < 32; ++i) arguments[i] = 0;
    for (int j = total - 1; j >= 0; --j) Rva01338748Stack.push(arguments[j]);
    BfmeStrVKI functionName(name);
    Rva00899770 *function = Rva01338748Stack.createString(receiver, 0, &functionName, 1, 1, 0);
    ((Rva008CF740 *)&Rva01338748Stack)->run((Rva008CF740Value *)receiver, (Rva008CF740Value *)function, total);
    if (output) ((Rva00899770 *)Rva01338748Stack.top())->exportString(output);
    Rva008A9B00 *top = Rva01338748Stack.top();
    if (!top->permanent()) top->release();
    --Rva01338748Stack.count;
}
