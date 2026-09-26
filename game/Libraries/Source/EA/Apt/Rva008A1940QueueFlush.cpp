// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?flush@Rva008A1940Queue@@QAEXXZ
// 008A1940: no stack arguments; ECX queue owner; tail calls 008A07D0.
// 20-byte records and S+00/+08/+30/+38 witnessed by the analyst hub and this body.
// docs/analysis/0x008cf740.md proves hub ECX S plus receiver/function/count.
// Queue fields +00 storage +04 begin +08 end +12B0 capacity match the independently
// landed BfmeThingLN::bfmeClearLN, the tail target 008A07D0.
// First path calls 008CCED0 with stream/value/-1; the cursor return is unused.
// Calls 008A18C0 twice: ECX queue, zero stack args, target plain ret+7F.
// Value flags+04 and descriptor pointer+50; descriptor field+18 gates negative codes.
// Volatile accesses preserve the two independently witnessed flag/packed reloads;
// they are code-generation shaping, not a claim about the original declarations.
// Receiver retention is unconditional; primary-stack retention tests bit30.
// Signed pointer-distance adjustment and 20-byte ring wrap follow retail+0217 onward.
struct Rva008A1940Descriptor { char gap00[0x18]; int field18; };
class Rva008A1940Value {
public:
    virtual void retain();
    virtual void release();
    volatile unsigned flags;
    char gap08[0x48];
    Rva008A1940Descriptor *field50;
    bool permanent() const { return ((flags >> 30) & 1) != 0; }
    bool invalid() const { return ((~(flags >> 15)) & 1) != 0; }
    bool kind19() const {
        unsigned f = flags;
        return (f & 0x3f) == 0x13 && ((unsigned char)~(f >> 15) & 1) == 0;
    }
};
struct Rva008A1940Record {
    int type;
    volatile unsigned packed;
    union { int code; Rva008A1940Value *receiver; } field08;
    union { void **stream; Rva008A1940Value *function; } field0c;
    union { int count; Rva008A1940Value *value; } field10;
};
struct Rva008A1940Stack {
    int count, unused;
    Rva008A1940Value **values;
    __forceinline void push(Rva008A1940Value *v) {
        values[count++] = v;
        if (!v->permanent()) v->retain();
    }
    void pushAlways(Rva008A1940Value *v) { values[count++] = v; v->retain(); }
    Rva008A1940Value *top() { return values[count - 1]; }
    void pop() { Rva008A1940Value *v = top(); if (!v->permanent()) v->release(); --count; }
    void popAlways() { top()->release(); --count; }
};
struct Rva008A1940Interpreter {
    Rva008A1940Stack primary;
    char gap0c[0x24];
    Rva008A1940Stack retained;
};
extern Rva008A1940Interpreter Rva01338748State;
extern unsigned Rva008A5250LastKey;
struct Rva008A1940Holder { char gap00[0x1268]; Rva008A1940Value *field1268; Rva008A1940Value *get() { return field1268; } };
extern Rva008A1940Holder *g_bfmeHolderBU;
class AptInteger { public: static AptInteger *Create(int); };
class BfmeR1226 { public: void bfmeAdd1226(void *, void *, int); void bfmeLine1226(char *); };
class Rva008CF740Value;
class Rva008CF740 { public: void run(Rva008CF740Value *, Rva008CF740Value *, int); };
class BfmeThingLN { public: void bfmeClearLN(); };
class Rva008A1940Queue {
public:
    Rva008A1940Record *storage, *begin, *end;
    char gap0c[0x12a4];
    int capacity;
    void flush();
    void rva008A18C0();
};

void Rva008A1940Queue::flush()
{
    Rva008A1940Record *it = begin;
    while (it != end) {
        Rva008A1940Record *oldEnd = end;
        if (it->type == 0) {
            Rva008A5250LastKey = it->packed;
            Rva008A1940Value *value = it->field10.value;
            if (!value->invalid() && !value->kind19() &&
                (it->field08.code >= 0 || -it->field08.code == value->field50->field18)) {
                ((BfmeR1226 *)&Rva01338748State)->bfmeAdd1226(*it->field0c.stream, value, -1);
                ((BfmeR1226 *)&Rva01338748State)->bfmeLine1226("eActionType == AAT_ACTION");
                rva008A18C0();
            }
        } else if (it->type == 1) {
            Rva008A5250LastKey = it->packed;
            Rva01338748State.retained.pushAlways(it->field08.receiver);
            unsigned key = it->packed;
            if (key && (unsigned char)(key & 3) == 1) {
                unsigned packed = it->packed;
                unsigned selector = packed >> 10;
                int number = packed >> 17;
                selector &= 0x7f;
                if (it->field10.count > 0 && (packed & 0x3fc) == 4 && (selector & 7)) {
                    if (it->field10.count > 1) Rva01338748State.primary.push(g_bfmeHolderBU->get());
                    if (selector == 4) number = -number;
                    Rva01338748State.primary.push((Rva008A1940Value *)AptInteger::Create(number));
                }
            }
            ((Rva008CF740 *)&Rva01338748State)->run((Rva008CF740Value *)it->field08.receiver,
                (Rva008CF740Value *)it->field0c.function, it->field10.count);
            ((BfmeR1226 *)&Rva01338748State)->bfmeLine1226("eActionType == AAT_FUNCTION");
            Rva01338748State.retained.popAlways();
            Rva01338748State.primary.pop();
        }
        if (Rva01338748State.primary.count > 0) Rva01338748State.primary.pop();
        if (oldEnd > end) it -= oldEnd - end;
        ++it;
        if (it == storage + capacity) it = storage;
    }
    rva008A18C0();
    ((BfmeThingLN *)this)->bfmeClearLN();
}
