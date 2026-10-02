// Retail 008B96A0..008B9770, independent prologue after INT3 at 008B969F.
// Appends stack arguments to a type-22 array and returns the resulting length.
class Value008B96A0 {
public:
    virtual void retain();
    virtual void release();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual unsigned char slot14();
    unsigned flags;
    unsigned char isType(unsigned char t) const { unsigned f=flags; return (f & 0x3f)==t && !((unsigned char)(~(f>>15)) & 1); }
};
class AptInteger { public: static AptInteger *Create(int); };
class BfmeN1242 {
public:
    char field00[0x20];
    unsigned *field20;
    int field24,field28;
    void bfmeReserve1242(int);
    __forceinline void append(Value008B96A0 *v) {
        int index=field28;
        if (index>=0) {
            int next=index+1;
            bfmeReserve1242(next);
            Value008B96A0 *old=(Value008B96A0 *)(field20[index]&~1u);
            v->retain();
            if (old) old->release();
            unsigned tagged=(unsigned)v;
            if (v->slot14()==1) tagged|=1;
            field20[index]=tagged;
            int count=field28;
            if (next>count) count=next;
            field28=count;
        }
    }
};
class AptValue;
extern AptValue **g_bfmeArr1233;
// 0x01338748: the Apt stack depth global, defined in Rva00C6DCC0StaticInit.cpp.
struct Rva008AE770Stack { int m_count; };
extern Rva008AE770Stack Rva008AE770TheStack;
// 0x013379BC is the fallback value database pointer, defined as AptValue *
// by Bfme5AppendFallback8CAFF0.cpp (?g_bfmeFallbackDB@@3PAVAptValue@@A).
extern AptValue *g_bfmeFallbackDB;
void *appendStackArray008B96A0(BfmeN1242 *source,int count) {
    if (((Value008B96A0 *)source)->isType(0x16)) {
        for (int i=0;i<count;++i) {
            Value008B96A0 *value=(Value008B96A0 *)g_bfmeArr1233[Rva008AE770TheStack.m_count-i-1];
            source->append(value);
        }
        return AptInteger::Create(source->field28);
    }
    return g_bfmeFallbackDB;
}
