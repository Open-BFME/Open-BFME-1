// ?rva008B9930@@YAPAVAptValue@@PAURva008B9930Value@@H@Z
// partial score=0.879 date=2026-10-03
// ?rva008B9930@@YAPAVAptValue@@PAURva008B9930Value@@H@Z
// Retail complete124B; two valid qsort comparators at8B90F0 and8B9850.
// Explicit stack count local fixes base/index allocation; array count before
// callback-global stores retains retail prefix.15 differing bytes remain in
// buffer load / callback-global stores / argument scheduling. No new pins.
// cl: /DNDEBUG /MD /EHsc
class AptValue;
class Rva008CF740Value;
struct Rva008B9930Value {
    void *vptr;
    union { unsigned flags; struct { unsigned kindBits:6; unsigned remaining:26; }; };
    char field08[0x18];
    unsigned *field20;
    unsigned field24;
    unsigned field28;
    unsigned kind() const { return kindBits; }
    unsigned char invalid() const { return (unsigned char)~(flags >> 15) & 1; }
};
struct Rva008B9930Callback { char head[0x28]; Rva008CF740Value *receiver; };
struct Rva008AE770Stack { int count; int field04; AptValue **values; };
extern Rva008AE770Stack Rva008AE770TheStack;
extern Rva008CF740Value *Rva01338450SortFunction;
extern Rva008CF740Value *Rva01338454SortReceiver;
extern AptValue *g_bfmeFallbackDB;
extern "C" int __cdecl compareValues008B90F0(unsigned *, unsigned *);
int arraySortScriptFunction008B9850(unsigned *, unsigned *);
typedef int (__cdecl *Rva008B9930Compare)(unsigned *, unsigned *);
extern "C" void __cdecl qsort(void *, unsigned, unsigned, Rva008B9930Compare);
AptValue *rva008B9930(Rva008B9930Value *value, int argc) {
    if(value->kind()==22 && !value->invalid()) {
        if(argc==0) {
            qsort(value->field20, (unsigned)value->field28, 4, compareValues008B90F0);
            return g_bfmeFallbackDB;
        }
        int count=Rva008AE770TheStack.count;
        Rva008B9930Callback *top=(Rva008B9930Callback*)Rva008AE770TheStack.values[count-1];
        unsigned n=value->field28;
        Rva01338450SortFunction=(Rva008CF740Value*)top;
        Rva01338454SortReceiver=top->receiver;
        qsort(value->field20, n, 4, arraySortScriptFunction008B9850);
    }
    return g_bfmeFallbackDB;
}
