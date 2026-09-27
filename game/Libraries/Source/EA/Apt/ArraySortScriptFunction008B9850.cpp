// Retail 008B9850: arraySortScriptFunction literal; two tagged arguments.
// AptValue +04 flags and virtual slots 00/04 witnessed by this body.
class AptValue {
public:
    virtual void retain();
    virtual void release();
    unsigned m_valueBits;
    int toInteger() const;
    bool permanent() const { return ((m_valueBits >> 30) & 1) != 0; }
};
class Rva008CF740Value;
class Rva008CF740 { public: void run(Rva008CF740Value *, Rva008CF740Value *, int); };
class BfmeR1226 { public: void bfmeLine1226(char *); };
extern BfmeR1226 g_bfmeR1226;
extern AptValue **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern Rva008CF740Value *Rva01338450SortFunction;
extern Rva008CF740Value *Rva01338454SortReceiver;
static void push(AptValue *v) {
    g_bfmeArr1233[g_bfmeCount1233++] = v;
    if (!v->permanent()) v->retain();
}
int arraySortScriptFunction008B9850(unsigned *a, unsigned *b) {
    if (!Rva01338450SortFunction) return 0;
    AptValue *left = (AptValue *)(*a & ~1u);
    AptValue *right = (AptValue *)(*b & ~1u);
    push(right);
    push(left);
    ((Rva008CF740 *)&g_bfmeR1226)->run(Rva01338454SortReceiver, Rva01338450SortFunction, 2);
    g_bfmeR1226.bfmeLine1226("arraySortScriptFunction");
    int result = g_bfmeArr1233[g_bfmeCount1233 - 1]->toInteger();
    AptValue *top = g_bfmeArr1233[g_bfmeCount1233 - 1];
    if (!top->permanent()) top->release();
    --g_bfmeCount1233;
    return result;
}
