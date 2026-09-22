// ?rva8CDE50Continue@@YAXPAVRva8CEE00State@@PAURva8CEE00Cursor@@@Z
// partial score=0.40022050716648294 date=2026-09-22
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008CDE50, 907B. Existing opaque caller contract from 008CEE00.
// String handles and hub ABI: docs/analysis/0x008985c0.md.
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class BfmeStrVKI;
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned); };
class Rva8CD130String {
public:
    __forceinline Rva8CD130String() { m_data=&g_bfmeDefaultString1284; ++m_data->m_refCount; }
    __forceinline ~Rva8CD130String() {
        BfmeStringData3AF0 *old=m_data;
        if (--old->m_refCount==0) g_bfmeStringPool1284->free(old);
    }
    BfmeStringData3AF0 *m_data;
};
struct Rva008CDE50Link { unsigned m_unknown00, m_unknown04, m_tagged08; };
class Rva8CD130Value {
public:
    virtual void rva008CDE50Slot00();
    virtual void rva008CDE50Slot04();
    virtual void rva008CDE50Slot08();
    virtual void rva008CDE50Slot0C();
    virtual void rva008CDE50Slot10();
    virtual void rva008CDE50Slot14();
    virtual Rva008CDE50Link *rva008CDE50Slot18();
    virtual void rva008CDE50Slot1C();
    virtual void rva008CDE50Slot20();
    virtual bool rva008CDE50Slot24();
    unsigned m_flags;
    Rva8CD130String m_string;
    unsigned char m_unknown0C[0x14];
    Rva8CD130Value *m_indirect;
    void getName(Rva8CD130String *);
    __forceinline bool undefined() const { return (~(m_flags>>15)&1)!=0; }
    __forceinline bool retained() const { return ((m_flags>>30)&1)!=0; }
};
class AptValue { public: int toInteger() const; };
class Gen_008B8E50 { public: int bfmeAt(int) const; };
class Rva00899770;
class Rva008AE770Stack { public: Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int); };
class Rva8CEE00State {
public:
    int m_count;
    int m_unknown04;
    Rva8CD130Value **m_entries;
    unsigned char m_unknown0C[0x0C];
    int m_count18;
    int m_unknown1C;
    Rva8CD130Value **m_entries20;
    __forceinline void popTwo() {
        for (int i=1;i<=2;++i) {
            Rva8CD130Value *v=m_entries[m_count-i];
            if (!v->retained()) v->rva008CDE50Slot04();
        }
        m_count-=2;
    }
    __forceinline void push(Rva8CD130Value *v) {
        m_entries[m_count++]=v;
        if (!v->retained()) v->rva008CDE50Slot00();
    }
};
struct Rva8CEE00Cursor;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
extern void (__cdecl *g_bfmeFreeDWF)(void *);
extern void *(__cdecl *rva01337868Callback)(const char *);
class Rva008A9B00 {
public:
    Rva008A9B00();
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
    static void operator delete(void *p) { g_bfmeFreeDWF(p); }
    void *m_vptr;
    unsigned m_flags;
    BfmeStringData3AF0 *m_block;
    Rva008A9B00 *m_next;
};
struct BfmeRegistryKind1 {
    int m_capacity, m_count;
    void **m_entries;
    __forceinline void addOrClear(Rva008A9B00 *obj) {
        int index=m_count;
        int *pcount=&m_count;
        if (index>=m_capacity) { obj->m_flags&=~0x40000000; return; }
        m_entries[index]=obj;
        ++*pcount;
    }
};
extern "C" BfmeRegistryKind1 *g_bfmeRegistryVNF;
extern Rva008A9B00 *g_rva008C3B60Free;
extern Rva8CD130Value *g_bfmeFallbackDB;
class Rva008B2EA0Node { public: void append(void *); };

void rva8CDE50Continue(Rva8CEE00State *state, Rva8CEE00Cursor *cursor) {
    Rva8CD130Value *under=state->m_entries[state->m_count-2];
    Rva8CD130Value *top=state->m_entries[state->m_count-1];
    if (!under->undefined() && !top->undefined()) {
        int type=under->m_flags&0x3f;
        int topType=top->m_flags&0x3f;
        if (type==22 && (topType==7 || topType==6)) {
            int number=reinterpret_cast<AptValue *>(top)->toInteger();
            Rva8CD130Value *result=reinterpret_cast<Rva8CD130Value *>(reinterpret_cast<Gen_008B8E50 *>(under)->bfmeAt(number));
            state->popTwo();
            state->push(result);
            return;
        } else if (type==11) {
            Rva8CD130Value *source=top;
            if (topType!=1) source=source->m_indirect;
            void *buffer=rva01337868Callback(reinterpret_cast<const char *>(source->m_string.m_data)+8);
            Rva008A9B00 *node=g_rva008C3B60Free;
            if (node) {
                g_rva008C3B60Free=node->m_next;
                g_bfmeRegistryVNF->addOrClear(node);
                if (node->m_block!=&g_bfmeDefaultString1284) reinterpret_cast<BfmeStrVKK *>(&node->m_block)->bfmeTruncVKK(0);
            } else {
                node=new Rva008A9B00();
            }
            reinterpret_cast<Rva008B2EA0Node *>(node)->append(buffer);
            g_bfmeFreeDWF(buffer);
            state->popTwo();
            state->push(reinterpret_cast<Rva8CD130Value *>(node));
            return;
        } else {
            Rva8CD130String name;
            top->getName(&name);
            Rva8CD130Value *result=reinterpret_cast<Rva8CD130Value *>(reinterpret_cast<Rva008AE770Stack *>(state)->createString(under,0,reinterpret_cast<BfmeStrVKI *>(&name),1,0,1));
            if (result->undefined() && state->m_count18 && !state->m_entries20[state->m_count18-1]->undefined()) {
                Rva8CD130Value *scope=state->m_entries20[state->m_count18-1];
                if (scope->rva008CDE50Slot24()) {
                    Rva008CDE50Link *link=scope->rva008CDE50Slot18();
                    while (link) {
                        Rva8CD130Value *parent=reinterpret_cast<Rva8CD130Value *>(link->m_tagged08 & ~1u);
                        if (!parent) break;
                        if (parent==under) {
                            result=reinterpret_cast<Rva8CD130Value *>(reinterpret_cast<Rva008AE770Stack *>(state)->createString(under,reinterpret_cast<int>(scope),reinterpret_cast<BfmeStrVKI *>(&name),0,0,1));
                            if (!result->undefined()) break;
                        }
                        link=parent->rva008CDE50Slot18();
                    }
                }
            }
            state->popTwo();
            state->push(result);
            return;
        }
    } else {
        state->popTwo();
        state->push(g_bfmeFallbackDB);
    }
}
