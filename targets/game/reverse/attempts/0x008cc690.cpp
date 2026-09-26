// ?d_008cc690@@YAXXZ
// partial score=0.1965065502183406 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// 008CC690: thiscall, seven stack dwords, AL result, ret 1C.
// Layout/ABI witnesses: docs/analysis/0x008cf740.md and retail body.
// 008C6460 is a private helper taking value/name/flag in ESI/EBX/EDI.
struct StringBlock008CC690 { unsigned short refs, length; };
extern StringBlock008CC690 g_default012D5298;
struct Pool008CC690 { void *unused; void (__cdecl *free)(void *); };
extern Pool008CC690 *g_pool01337A30;
class String008CC690 {
public:
    StringBlock008CC690 *block;
    String008CC690() { block = &g_default012D5298; ++block->refs; }
    ~String008CC690() { StringBlock008CC690 *p=block; if (--p->refs==0) g_pool01337A30->free(p); }
    String008CC690 &operator=(const String008CC690 &s) {
        ++s.block->refs;
        StringBlock008CC690 *p=block;
        if (--p->refs==0) g_pool01337A30->free(p);
        block=s.block;
        return *this;
    }
};
class BfmeTab1024 { public: int bfmeFind1024(int); void bfmeAdd1024(int,int); };
class Gen_008C41D0 { public: int bfmeValue() const; };
struct Table008CC690 : BfmeTab1024 { unsigned field00,field04,field08,field0C; };
class Value008CC690 {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual Table008CC690 *slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(); virtual void slot28();
    virtual bool slot2C(Value008CC690 *,String008CC690 *,Value008CC690 *);
    unsigned field04; char gap08[0x44]; Gen_008C41D0 *field4C; void *field50;
    __forceinline int kind() const { return field04 & 0x3f; }
    __forceinline unsigned char invalid() const {
        return (unsigned char)~(field04 >> 15) & 1;
    }
    __forceinline bool family() const { return kind()>=12 && kind()<=19 && !invalid(); }
};
struct BfmeString008AD350;
class BfmeObject008AD350 { public: void setMember(BfmeString008AD350 *,void *,int); };
struct Rva008D30D0String;
class Rva008D30D0Owner { public: void setEvent(Rva008D30D0String *,void *,int); };
static __declspec(noinline) void notify008C6460(Value008CC690 *value,String008CC690 *name,int flag) {
    if (value->family() && (value->kind()==13 || value->kind()==18))
        ((BfmeObject008AD350 *)value->field50)->setMember((BfmeString008AD350 *)name,value,flag);
    if (value->family() && value->kind()==14)
        ((Rva008D30D0Owner *)value->field50)->setEvent((Rva008D30D0String *)name,value,flag);
}
extern void d_008c6320();
typedef void (__cdecl *Prepare008CC690)(Value008CC690 *,void *,String008CC690 *,Value008CC690 **,String008CC690 *);
extern Value008CC690 *g_value013379F4, *g_value013379BC;
struct Frame008CC690 { unsigned field00,field04; Table008CC690 table; };
class Rva008CC690State {
public:
    char gap00[12]; int field0C; int field10; Frame008CC690 **field14;
    bool assignNamed(Value008CC690 *,void *,String008CC690 *,Value008CC690 *,int,int,int);
};
bool Rva008CC690State::assignNamed(Value008CC690 *owner,void *scope,String008CC690 *input,Value008CC690 *value,int a,int b,int c) {
    String008CC690 name;
    Value008CC690 *resolved;
    if (!c) {
        ((Prepare008CC690)d_008c6320)(owner,scope,input,&owner,&name);
        resolved=owner;
    } else {
        resolved=owner;
        name=*input;
    }
    if (!resolved) return false;
    if (resolved->family() && resolved->kind()==12) return false;
    if (!resolved->invalid() && resolved->slot2C(resolved,&name,value)) return true;
    if (a) {
        if (b && field0C>0 && field14[field0C-1]->table.bfmeFind1024((int)&name)) goto frame;
        {
            notify008C6460(resolved,&name,!value ? 1 : value->invalid());
            Table008CC690 *table=resolved->slot18();
            if (table) {
                table->bfmeAdd1024((int)&name,(int)value);
                if (resolved==g_value013379F4 && (unsigned char)value->kind()==10 && !value->invalid()) {
                    Table008CC690 *next=((Value008CC690 *)(value->slot18()->field0C&~1u))->slot18();
                    Value008CC690 *old=(Value008CC690 *)(next->field08&~1u);
                    if (old) old->slot04();
                    next->field08=0;
                }
            } else if (resolved->family() && resolved->kind()==14) {
                table=(Table008CC690 *)resolved->field4C->bfmeValue();
                if (table) table->bfmeAdd1024((int)&name,(int)value);
            }
        }
    } else if (field0C>0) {
frame:
        field14[field0C-1]->table.bfmeAdd1024((int)&name,(int)value);
    } else {
        notify008C6460(resolved,&name,value==g_value013379BC);
        Table008CC690 *table=resolved->slot18();
        if (table) table->bfmeAdd1024((int)&name,(int)value);
    }
    return true;
}
