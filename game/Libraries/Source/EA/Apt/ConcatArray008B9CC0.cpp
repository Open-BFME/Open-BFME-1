// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 008B9CC0: concatenate a type-22 array and stack values, flattening array operands.
// Base size 20h and array fields 20h/24h/28h are witnessed by constructor and reserve.
class BfmeItemDX;
void bfmePush(BfmeItemDX *);
extern void *(*WideAllocPtr)(unsigned);
extern "C" void *bfmeVft1030C[];
class Rva00899F00Base {
public:
    Rva00899F00Base(unsigned, int);
    virtual ~Rva00899F00Base();
    unsigned flags;
    char field08[0x18];
};
class Value008B9CC0 {
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
class BfmeN1242 { public: void bfmeReserve1242(int); };
class Rva008B9C90HeaderedDeleting : public Rva00899F00Base {
public:
    unsigned *m_elements;
    int m_capacity, field28;
    virtual ~Rva008B9C90HeaderedDeleting();
    Rva008B9C90HeaderedDeleting() : Rva00899F00Base(0x16,8) {
        m_capacity=0; m_elements=0; field28=0;
    }
    static void *operator new(unsigned n) {
        void *raw=WideAllocPtr(n+8); void *p=(char *)raw+8;
        bfmePush((BfmeItemDX *)p);
        return p;
    }
    static void operator delete(void *, unsigned);
    __forceinline void put(int index, Value008B9CC0 *v) {
        Value008B9CC0 *old=(Value008B9CC0 *)(m_elements[index]&~1u);
        v->retain();
        if (old) old->release();
        unsigned tagged=(unsigned)v;
        if (v->slot14()==1) tagged|=1;
        m_elements[index]=tagged;
    }
    __forceinline void set(int index, Value008B9CC0 *v) {
        if (index>=0) {
            int next=index+1;
            ((BfmeN1242 *)this)->bfmeReserve1242(next);
            put(index,v);
            field28 = next > field28 ? next : field28;
        }
    }
};
extern Value008B9CC0 **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern void *g_bfmeResult1233;
void *aptArrayConcat(Value008B9CC0 *self,int count) {
    if (self->isType(0x16)) {
        Rva008B9C90HeaderedDeleting *source=(Rva008B9C90HeaderedDeleting *)self;
        Rva008B9C90HeaderedDeleting *out=new Rva008B9C90HeaderedDeleting;
        for (int i=0;i<source->field28;++i)
            out->set(out->field28,(Value008B9CC0 *)(source->m_elements[i]&~1u));
        for (int j=0;j<count;++j) {
            Value008B9CC0 *v=g_bfmeArr1233[g_bfmeCount1233-j-1];
            if (v->isType(0x16)) {
                Rva008B9C90HeaderedDeleting *a=(Rva008B9C90HeaderedDeleting *)v;
                for (int k=0;k<a->field28;++k)
                    out->set(out->field28,(Value008B9CC0 *)(a->m_elements[k]&~1u));
            } else out->set(out->field28,v);
        }
        return out;
    }
    return g_bfmeResult1233;
}
