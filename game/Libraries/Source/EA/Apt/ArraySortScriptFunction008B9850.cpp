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
// 0x01338748: the Apt stack depth global, defined in Rva00C6DCC0StaticInit.cpp.
// Its address is also what this body passes as the interpreter receiver.
struct Rva008AE770Stack
{
	int m_count;
	int m_rva0133874C;
	AptValue** m_rva01338750;
};
extern Rva008AE770Stack Rva008AE770TheStack;
extern Rva008CF740Value *Rva01338450SortFunction;
extern Rva008CF740Value *Rva01338454SortReceiver;
static void push(AptValue *v) {
    Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.m_count++] = v;
    if (!v->permanent()) v->retain();
}
int arraySortScriptFunction008B9850(unsigned *a, unsigned *b) {
    if (!Rva01338450SortFunction) return 0;
    AptValue *left = (AptValue *)(*a & ~1u);
    AptValue *right = (AptValue *)(*b & ~1u);
    push(right);
    push(left);
    ((Rva008CF740 *)&Rva008AE770TheStack)->run(Rva01338454SortReceiver, Rva01338450SortFunction, 2);
    ((BfmeR1226 *)&Rva008AE770TheStack)->bfmeLine1226("arraySortScriptFunction");
    int result = Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.m_count - 1]->toInteger();
    AptValue *top = Rva008AE770TheStack.m_rva01338750[Rva008AE770TheStack.m_count - 1];
    if (!top->permanent()) top->release();
    --Rva008AE770TheStack.m_count;
    return result;
}
