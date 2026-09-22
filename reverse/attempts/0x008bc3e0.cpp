// ?bfmeResolve1281@BfmeSlotDispatcher1281@@QAEXHHPAPAXPA_N@Z
// partial score=0.3950456323337679 date=2026-09-22
// ?bfmeResolve1281@BfmeSlotDispatcher1281@@QAEXHHPAPAXPA_N@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 008BC3E0, matched AptInput.cpp caller fixes thiscall/four arguments/ret10.
// No semantic identity beyond that existing caller alias is claimed.
// The constant VA012D5298 is a shared string block, not a vtable.
struct StringBlock008BC3E0 { unsigned short refs,length,capacity,flags; char text[1]; };
struct StringPool008BC3E0 { void *unused; void (__cdecl *free)(void *); };
extern StringBlock008BC3E0 empty012D5298;
extern StringPool008BC3E0 *pool01337A30;
class String008BC3E0 {
public:
    String008BC3E0() { m_block=&empty012D5298; ++empty012D5298.refs; }
    __forceinline ~String008BC3E0() { StringBlock008BC3E0 *p=m_block; if(--p->refs==0) pool01337A30->free(p); }
    StringBlock008BC3E0 *m_block;
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
// 008C6320 has five cdecl stack arguments: scope, alternate, holder,
// output scope pointer, output holder; caller adds 20. AL result is unused here.
unsigned char __cdecl parse008C6320(Value008BC3E0 *,Value008BC3E0 *,String008BC3E0 *,Value008BC3E0 **,String008BC3E0 *);
class Hub008CF740 { public: void run(Value008BC3E0 *,Value008BC3E0 *,int); };
class BfmeR1226 { public: void bfmeLine1226(char *); };
class BfmeNodeDX;
class Gen_008A0C30 { public: bool bfmeAllows(BfmeNodeDX *) const; };
extern Gen_008A0C30 *registry013377D8;
struct Stack008BC3E0 {
    int m_00; unsigned m_04; Value008BC3E0 **m_08;
    __forceinline Value008BC3E0 *top() { return m_08[m_00-1]; }
    __forceinline void pop() { Value008BC3E0 *p=top(); if(!p->marked()) p->slot04(); --m_00; }
};
extern Stack008BC3E0 stack01338748;
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
        parse008C6320(scope,0,&stringValue->m_08,&resolved,&name);
        if(resolved) {
            if(name.m_block->length==0 && resolved->accepts()) {
                *result=resolved;
            } else if(name.m_block->length>0 && resolved->hasTable()) {
                Value008BC3E0 *found=resolved->m_50->m_10->find(&name);
                if(found) value=found;
            }
        }
    }
    if((unsigned char)(value->m_04&0x3f)==10 && !value->invalid()) {
        value->slot4c();
        ((Hub008CF740 *)&stack01338748)->run(scope,value,0);
        ((BfmeR1226 *)&stack01338748)->bfmeLine1226("_handleFocusButton");
        value=stack01338748.top();
        if(value->kind()>=12 && value->kind()<=19 && !value->invalid()) {
            value->slot00();
            stack01338748.pop();
        } else {
            stack01338748.pop();
            *handled=true;
            return;
        }
    } else value->slot00();
    if(value->accepts() && !registry013377D8->bfmeAllows((BfmeNodeDX *)value)) *result=value;
    value->slot04();
}

