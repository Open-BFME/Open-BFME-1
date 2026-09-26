// ?bfmeResolve1281@BfmeSlotDispatcher1281@@QAEXHHPAPAXPA_N@Z
// partial score=0.58 date=2026-09-24
// ?bfmeResolve1281@BfmeSlotDispatcher1281@@QAEXHHPAPAXPA_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 008BC3E0, matched AptInput.cpp caller fixes thiscall/four arguments/ret10.
// No semantic identity beyond that existing caller alias is claimed.
// The shared string layouts and globals are pinned by matched string helpers.
struct BfmeStringData3AF0
{
    unsigned short m_refCount,m_length,m_capacity,m_flags;
};
struct BfmeStringPool3AF0
{
    void *unused;
    void (__cdecl *free)(void *storage);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class String008BC3E0 {
public:
    String008BC3E0() { m_block=&g_bfmeDefaultString1284; ++g_bfmeDefaultString1284.m_refCount; }
    __forceinline ~String008BC3E0() { BfmeStringData3AF0 *p=m_block; if(--p->m_refCount==0) g_bfmeStringPool1284->free(p); }
    BfmeStringData3AF0 *m_block;
};
class Value008BC3E0;
class Table0089CEF0 { public: Value008BC3E0 *find(String008BC3E0 *); };
struct State008BC3E0 { char m_00[0x10]; Table0089CEF0 *m_10; };
class Value008BC3E0 {
public:
    virtual void slot00(); virtual void slot04();
    virtual void slot08(); virtual void slot0c();
    virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c();
    virtual void slot20(); virtual void slot24();
    virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34();
    virtual void slot38(); virtual void slot3c();
    virtual void slot40(); virtual void slot44();
    virtual void slot48(); virtual int slot4c();
    unsigned m_04;
    String008BC3E0 m_08;
    char m_0c[0x14]; Value008BC3E0 *m_20;
    char m_24[0x28]; Value008BC3E0 *m_4c;
    State008BC3E0 *m_50;
    int kind() const { return m_04&0x3f; }
    unsigned char invalid() const { return (unsigned char)~(m_04>>15)&1; }
    unsigned char marked() const { return (unsigned char)(m_04>>30)&1; }
    __forceinline bool accepts() const { return (kind()==14&&!invalid())||(kind()==13&&!invalid())||(kind()==18&&!invalid()); }
    __forceinline bool hasTable() const { return (kind()==13&&!invalid())||(kind()==18&&!invalid()); }
};
// The second fastcall operand supplies the vtable pointer in EDX; it is not a slot argument.
typedef void (__fastcall *Rva008BC3E0Slot00Fn)(void *, void *);
typedef void (__fastcall *Rva008BC3E0Slot04EaxFn)(void *);
typedef void (__fastcall *Rva008BC3E0Slot04EdxFn)(void *, void *);
typedef int (__fastcall *Rva008BC3E0Slot4CFn)(void *, void *);
struct Rva008BC3E0Slot00Vtable { Rva008BC3E0Slot00Fn slot00; };
struct Rva008BC3E0Slot04EaxVtable { void *slot00; Rva008BC3E0Slot04EaxFn slot04; };
struct Rva008BC3E0Slot04EdxVtable { void *slot00; Rva008BC3E0Slot04EdxFn slot04; };
struct Rva008BC3E0Slot4CVtable { void *slots[19]; Rva008BC3E0Slot4CFn slot4c; };

// 008C6320 has five cdecl pointer arguments; the caller removes 20 bytes.
// The address-derived class keeps its byte-evidenced ABI separate from its name.
class Rva008C6320 {
public:
    static unsigned char body(Value008BC3E0 *,Value008BC3E0 *,String008BC3E0 *,Value008BC3E0 **,String008BC3E0 *);
};
class Hub008CF740 { public: void run(Value008BC3E0 *,Value008BC3E0 *,int); };
class BfmeR1226 { public: void bfmeLine1226(char *); };
class BfmeNodeDX;
class Gen_008A0C30 { public: bool bfmeAllows(BfmeNodeDX *) const; };
extern char *Rva008A5380Holder;
class AptValue;
extern AptValue **g_bfmeArr1233;
struct Stack008BC3E0 {
    int m_count;
    __forceinline Value008BC3E0 *top() { return (Value008BC3E0 *)g_bfmeArr1233[m_count-1]; }
    __forceinline void pop() { Value008BC3E0 *p=top(); if(!p->marked()) p->slot04(); --m_count; }
};
extern Stack008BC3E0 stack01338748;
// Address-only anchors for the switch's static string keys.
extern String008BC3E0 key013384CC,key0133848C,key013384A8,key013384B4;
class BfmeSlotDispatcher1281 {
public:
    void bfmeResolve1281(int group,int slot,void **result,bool *handled);
    char m_00[0x126c]; Value008BC3E0 *m_126c;
};
void BfmeSlotDispatcher1281::bfmeResolve1281(int group,int slot,void **result,bool *handled)
{
    *result=0;
    *handled=false;
    if(!m_126c) return;
    if(slot!=0) return;
    String008BC3E0 *key;
    switch(group) {
    case 14:key=&key013384CC;break;
    case 15:key=&key0133848C;break;
    case 1:key=&key013384A8;break;
    case 2:key=&key013384B4;break;
    default:return;
    }
    Value008BC3E0 *scope=m_126c->m_4c;
    Value008BC3E0 *value=scope->m_50->m_10->find(key);
    if(!value) return;
    if((value->kind()==1 || value->kind()==42) && !value->invalid()) {
        String008BC3E0 name;
        Value008BC3E0 *resolved;
        Value008BC3E0 *stringValue=value;
        if(value->kind()!=1) stringValue=value->m_20;
        Rva008C6320::body(scope,0,&stringValue->m_08,&resolved,&name);
        if(resolved) {
            if(name.m_block->m_length==0 && resolved->accepts()) {
                *result=resolved;
            } else if(name.m_block->m_length>0 && resolved->hasTable()) {
                Value008BC3E0 *found=resolved->m_50->m_10->find(&name);
                if(found) value=found;
            }
        }
    }
    if((unsigned char)(value->m_04&0x3f)==10 && !value->invalid()) {
        Rva008BC3E0Slot4CVtable *vtable=*(Rva008BC3E0Slot4CVtable **)value;
        vtable->slot4c(value,vtable);
        ((Hub008CF740 *)&stack01338748)->run((Value008BC3E0 *)scope,(Value008BC3E0 *)value,0);
        ((BfmeR1226 *)&stack01338748)->bfmeLine1226("_handleFocusButton");
        value=stack01338748.top();
        if(value->kind()>=12 && value->kind()<=19 && !value->invalid()) {
            Rva008BC3E0Slot00Vtable *vtable=*(Rva008BC3E0Slot00Vtable **)value;
            vtable->slot00(value,vtable);
            stack01338748.pop();
        } else {
            stack01338748.pop();
            *handled=true;
            return;
        }
    } else {
        Rva008BC3E0Slot00Vtable *vtable=*(Rva008BC3E0Slot00Vtable **)value;
        vtable->slot00(value,vtable);
    }
    if(value->accepts() && !((Gen_008A0C30 *)Rva008A5380Holder)->bfmeAllows((BfmeNodeDX *)value)) *result=value;
    value->slot04();
}

