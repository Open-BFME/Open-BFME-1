// ?d_008b06c0@@YAXXZ
// partial score=0.48082191780821915 date=2026-09-22
// ?run@AssociateInstance008B06C0@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008B06C0: opaque owner; retail literal associateInstToClass describes the operation.
// Layouts and hub ABI: docs/analysis/0x008cf740.md. All offsets below witnessed in this body.
struct StringBlock008B06C0 { unsigned short refs, length, capacity, flags; char text[1]; };
struct StringPool008B06C0 { void *unused; void (__cdecl *free)(void *); };
extern StringPool008B06C0 *pool01337A30;
class BfmeStrVKI {
public:
    BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
    void bfmeSetVKI(const char *);
    ~BfmeStrVKI() { StringBlock008B06C0 *p=m_block; if (--p->refs==0) pool01337A30->free(p); }
    StringBlock008B06C0 *m_block;
};
class Value008B06C0;
class Table0089CEF0 {
public:
    Value008B06C0 *find(BfmeStrVKI *); // 0089CEF0, ECX table, ret4, EAX value
    unsigned m_00, m_04, m_08, m_0c;
};
class Value008B06C0 {
public:
    virtual void slot00(); virtual void slot04();
    virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14();
    virtual Table0089CEF0 *slot18(); virtual void slot1c();
    virtual void slot20(int);
    unsigned m_04;
    unsigned m_08, m_0c;
};
class BfmeItemDX;
void bfmePush(BfmeItemDX *);
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
class BfmeHeld99CB0;
class Rva89ACB0Holder {
public:
    Rva89ACB0Holder(BfmeHeld99CB0 *);
    static void *operator new(unsigned size) {
        void *p=(char *)Rva008C5D70Alloc(size+8)+8;
        bfmePush((BfmeItemDX *)p);
        return p;
    }
    static void operator delete(void *,unsigned); // exception cleanup only
    char m_00[0x1c];
};
class BfmeTaggedItem;
class Gen_00899320 { public: void bfmeSet(BfmeTaggedItem *); };
class Gen_008992C0 { public: void bfmeSet(BfmeTaggedItem *); };
class Gen_008C41D0 { public: int bfmeValue() const; };
class BfmeNode1236 { public: void bfmeActivate1236(); };
class BfmeR1226 { public: void bfmeLine1226(char *); };
class Hub008CF740 { public: void run(Value008B06C0 *,Value008B06C0 *,int); };
struct Stack008B06C0 {
    int m_00; unsigned m_04; Value008B06C0 **m_08;
    __forceinline void pop() { Value008B06C0 *v=m_08[m_00-1]; if (!((unsigned char)(v->m_04>>30)&1)) v->slot04(); --m_00; }
};
extern Stack008B06C0 stack01338748;
extern Value008B06C0 *value013387D8;
extern BfmeStrVKI key013385F8;
extern Table0089CEF0 *table01337A28;
extern BfmeStrVKI keys01338480[];
struct KeyRecord008B06C0 { int m_00,m_04; };
extern KeyRecord008B06C0 records012D5D54[8];
struct Ring008B06C0 {
    int m_a28; Value008B06C0 *m_a2c[512];
    __forceinline void add(Value008B06C0 *v) {
        int index=++m_a28;
        while (m_a2c[index]) { if(index<511) ++index; else index=0; }
        m_a2c[index]=v; v->slot00();
    }
};
struct Registry008B06C0 { char m_00[0xa28]; Ring008B06C0 m_a28;
    __forceinline void add(Value008B06C0 *v) {
        for(int i=0;i<512;++i) if(m_a28.m_a2c[i]==v) return;
        m_a28.add(v);
    }
};
extern Registry008B06C0 *registry013377D8;
struct Entry008B06C0;
struct EntryPair008B06C0 { const char *m_00; int m_04; };
struct Entries008B06C0 {
    char m_00[0x10]; Entry008B06C0 **m_10;
    char m_14[0x14]; int m_28; EntryPair008B06C0 *m_2c;
};
struct Entry008B06C0 { unsigned m_00; Entries008B06C0 *m_04; };
struct State008B06C0 {
    char m_00[0x0c]; Entry008B06C0 *m_0c; void *m_10;
    char m_14[0x18]; unsigned m_2c;
};
class AssociateInstance008B06C0 : public Value008B06C0 {
public:
    void run();
    char m_10[0x40]; State008B06C0 *m_50;
    unsigned char invalid() const { return (unsigned char)~(m_04>>15)&1; }
};
void AssociateInstance008B06C0::run()
{
    State008B06C0 *state=m_50;
    if (!((m_04&0x3f)==13 && !invalid()) &&
        !((m_04&0x3f)==18 && !invalid())) return;
    if(state->m_2c) return;
    Entry008B06C0 *entry=state->m_0c;
    Entries008B06C0 *entries=(Entries008B06C0 *)((char *)entry->m_04+8);
    ((Gen_00899320 *)state->m_10)->bfmeSet((BfmeTaggedItem *)new Rva89ACB0Holder(0));
    Value008B06C0 *found=((Table0089CEF0 *)((char *)value013387D8+8))->find(&key013385F8);
    ((Gen_008992C0 *)state->m_10)->bfmeSet((BfmeTaggedItem *)(found->slot18()->m_0c&~1));
    if(entries->m_28>0) {
        EntryPair008B06C0 *pairs=entries->m_2c;
        Entry008B06C0 **items=entries->m_10;
        for(int i=0;i<entries->m_28;++i) {
            if(entry==items[pairs[i].m_04]) {
                if(table01337A28) {
                    Value008B06C0 *function;
                    { BfmeStrVKI name(pairs[i].m_00); function=table01337A28->find(&name); }
                    if(function && (function->m_04&0x8000)) {
                        Value008B06C0 *base=(Value008B06C0 *)(function->slot18()->m_0c&~1);
                        if(base && (base->m_04&0x8000))
                            ((Gen_008992C0 *)state->m_10)->bfmeSet((BfmeTaggedItem *)base);
                        ((BfmeNode1236 *)this)->bfmeActivate1236();
                        slot20(1);
                        ((Hub008CF740 *)&stack01338748)->run(this,function,0);
                        ((BfmeR1226 *)&stack01338748)->bfmeLine1226("associateInstToClass");
                        stack01338748.pop();
                    }
                }
                break;
            }
        }
    }
    Value008B06C0 *parent=(Value008B06C0 *)(((Value008B06C0 *)((Gen_008C41D0 *)this)->bfmeValue())->m_08&~1);
    if(!parent) return;
    Table0089CEF0 *table=parent->slot18();
    while(table) {
        for(KeyRecord008B06C0 *key=records012D5D54;(int)key<(int)(records012D5D54+8);++key) {
            if(table->find(&keys01338480[key->m_00])) { registry013377D8->add(this); return; }
        }
        parent=(Value008B06C0 *)(table->m_08&~1);
        if(!parent) return;
        table=parent->slot18();
    }
}

