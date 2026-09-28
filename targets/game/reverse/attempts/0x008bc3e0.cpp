// ?bfmeResolve1281@BfmeSlotDispatcher1281@@QAEXHHPAPAXPA_N@Z
// partial score=0.997 date=2026-09-28
// ?bfmeResolve1281@BfmeSlotDispatcher1281@@QAEXHHPAPAXPA_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 008BC3E0: the matched AptInput.cpp caller fixes thiscall, four arguments and ret 0x10.
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
struct BfmeNode1285;
// 0x0089CEF0 is still a dump; its pinned spelling takes the key object's address as an int.
class BfmeLookup1285 { public: BfmeNode1285 *bfmeFind1285(int key); };
struct State008BC3E0 { char m_00[0x10]; BfmeLookup1285 *m_10; BfmeLookup1285 *table() const { return m_10; } };
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
// 0x008C6320 is still a dump: cdecl, five pointer arguments, called like Rva8CC570Resolve.cpp does.
extern void d_008c6320();
typedef unsigned char (__cdecl *Rva008C6320Fn)(Value008BC3E0 *,Value008BC3E0 *,String008BC3E0 *,Value008BC3E0 **,String008BC3E0 *);
class Rva008CF740Value;
class Rva008CF740 { public: void run(Rva008CF740Value *,Rva008CF740Value *,int); };
class BfmeR1226 { public: void bfmeLine1226(char *); };
class BfmeNodeDX;
class Gen_008A0C30 { public: bool bfmeAllows(BfmeNodeDX *) const; };
extern char *Rva008A5380Holder;
class AptValue;
extern AptValue **g_bfmeArr1233;
struct Rva008AE770Stack {
    int m_count;
    __forceinline Value008BC3E0 *top() { return (Value008BC3E0 *)g_bfmeArr1233[m_count-1]; }
    __forceinline void pop() { Value008BC3E0 *p=top(); if(!p->marked()) p->slot04(); --m_count; }
};
extern Rva008AE770Stack Rva008AE770TheStack;
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
    State008BC3E0 *state=scope->m_50;
    Value008BC3E0 *value=(Value008BC3E0 *)state->table()->bfmeFind1285((int)key);
    if(!value) return;
    if((value->kind()==1 || value->kind()==42) && !value->invalid()) {
        String008BC3E0 name;
        Value008BC3E0 *resolved;
        int type=value->kind();
        Value008BC3E0 *stringValue=type==1?value:value->m_20;
        ((Rva008C6320Fn)d_008c6320)(scope,0,&stringValue->m_08,&resolved,&name);
        if(resolved) {
            if(name.m_block->m_length==0 && resolved->accepts()) {
                *result=resolved;
            } else if(name.m_block->m_length>0 && resolved->hasTable()) {
                Value008BC3E0 *found=(Value008BC3E0 *)resolved->m_50->table()->bfmeFind1285((int)&name);
                if(found) value=found;
            }
        }
    }
    if(value->kind()==10 && !value->invalid()) {
        value->slot4c();
        ((Rva008CF740 *)&Rva008AE770TheStack)->run((Rva008CF740Value *)scope,(Rva008CF740Value *)value,0);
        ((BfmeR1226 *)&Rva008AE770TheStack)->bfmeLine1226("_handleFocusButton");
        value=Rva008AE770TheStack.top();
        if(value->kind()>=12 && value->kind()<=19 && !value->invalid()) {
            value->slot00();
            Rva008AE770TheStack.pop();
        } else {
            Rva008AE770TheStack.pop();
            *handled=true;
            return;
        }
    } else {
        value->slot00();
    }
    if(value->accepts() && !((Gen_008A0C30 *)Rva008A5380Holder)->bfmeAllows((BfmeNodeDX *)value)) *result=value;
    value->slot04();
}
