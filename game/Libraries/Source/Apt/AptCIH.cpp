// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008C3F10, 701B: thiscall; one byte-tested stack argument; ret4.
// Layout/ABI: docs/analysis/0x008cf740.md plus full retail instruction stream.
class Rva008A0E00Owner { public: int remove(void *); };
class BfmeRef008A4B20;
class BfmePtrTable64_008A4B20 { public: int remove(BfmeRef008A4B20 *); };
class BfmeItemHH;
class BfmeThingHH { public: void bfmeRemoveHH(BfmeItemHH *); };
class BfmeNode1220 { public: int bfmeTest1220(int *,int); };
class BfmeNodeDX { public: void bfmeEmit1281(int,void *,int); };
class BfmeD1046 { public: void bfmeReset1046(int); };
class BfmeNestedBE;
BfmeNestedBE *Rva008930C0AptLookup(int);
class Rva008C3F10Value;
struct State008C3F10 {
    virtual void slot00(); virtual void slot04(int); virtual void slot08();
};
class Rva008CF740Value;
class Rva008CF740 {
public:
    void run(Rva008CF740Value *,Rva008CF740Value *,int);
    int field00; int field04; Rva008C3F10Value **field08;
};
struct Registry008C3F10 {
    int field00,field04; Rva008C3F10Value **field08;
template<class V> __forceinline void append(V *value) {
    int capacity=field00;
    int count=field04;
    int *pcount=&field04;
    if (count>=capacity) value->field04 &= ~0x40000000u;
    else { field08[count]=value; ++*pcount; }
}
};
struct Manager008C3F10 {
    char gap00[0xc]; Rva008C3F10Value **field0C; int field10;
    char gap14[0x125c-0x14]; Rva008C3F10Value *field125C,*field1260;
    void remove008A1C20(Rva008C3F10Value *);
};
extern Manager008C3F10 *g_manager013377D8;
extern Rva008C3F10Value *g_value013379BC;
extern unsigned char g_byte0133781C;
extern Registry008C3F10 *g_registry01337814;
extern Rva008CF740 g_hub01338748;
extern int g_string01338654;
class Rva008C3F10Value {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20(int);
    unsigned field04; char gap08[0x48]; State008C3F10 *field50;
    char gap54[0xc]; unsigned field60;
    __forceinline unsigned char invalid() const { return (unsigned char)~(field04>>15)&1; }
    __forceinline bool isKind(unsigned k) const {
        unsigned f=field04; return (f&0x3f)==k && !((unsigned char)~(f>>15)&1);
    }
    __forceinline unsigned char marked() const { return (field04>>30)&1; }
    void cleanup(char mode);
};
void Rva008C3F10Value::cleanup(char mode) {
    if ((field60&0xc0000)==0x40000 || invalid()) return;
    ((Rva008A0E00Owner *)((char *)g_manager013377D8+0x14))->remove(this);
    ((Rva008A0E00Owner *)((char *)g_manager013377D8+0xa28))->remove(this);
    if (g_manager013377D8->field125C==this) g_manager013377D8->field125C=g_value013379BC;
    if (g_manager013377D8->field1260==this) g_manager013377D8->field1260=g_value013379BC;
    ((BfmePtrTable64_008A4B20 *)((char *)g_manager013377D8+0x820))->remove((BfmeRef008A4B20 *)this);
    if (g_byte0133781C)
        ((BfmePtrTable64_008A4B20 *)((char *)g_manager013377D8+0x924))->remove((BfmeRef008A4B20 *)this);
    ((BfmeThingHH *)g_manager013377D8)->bfmeRemoveHH((BfmeItemHH *)this);
    for (int i=0;i<g_manager013377D8->field10;++i) {
        if (g_manager013377D8->field0C[i]==this) {
            g_manager013377D8->field0C[i]->slot04();
            g_manager013377D8->field0C[i]=g_manager013377D8->field0C[g_manager013377D8->field10-1];
            --g_manager013377D8->field10;
        }
    }
    if (isKind(18)) g_manager013377D8->remove008A1C20(this);
    if (field50) {
        if (mode==1) {
            if (isKind(13)) {
                ((BfmeNodeDX *)this)->bfmeEmit1281(4,0,0);
                Rva008C3F10Value *value=(Rva008C3F10Value *)((BfmeNode1220 *)this)->bfmeTest1220(&g_string01338654,0);
                if (value && (value->field04&0x8000) && value->isKind(10)) {
                    g_hub01338748.run((Rva008CF740Value *)this,(Rva008CF740Value *)value,0);
                    Rva008C3F10Value *top=g_hub01338748.field08[g_hub01338748.field00-1];
                    if (!top->marked()) top->slot04();
                    --g_hub01338748.field00;
                }
            }
            field50->slot00();
            field50->slot08();
        }
        if ((int)(field60&0xffff)>0 && isKind(18) && this!=(Rva008C3F10Value *)Rva008930C0AptLookup(0)) {
            if (g_registry01337814->field04<g_registry01337814->field00) {
                ((BfmeD1046 *)((char *)field50+0x24))->bfmeReset1046(1);
                field60 &= ~0x10000u;
                slot20(0);
                field04 |= 0x40000000;
                g_registry01337814->append(this);
                field60=(field60&~0x80000u)|0x40000;
                return;
            }
            field60=(field60&~0x40000u)|0x80000;
        }
        field04 &= 0xffffc03f;
        if (field50) field50->slot04(1);
        field50=0;
    }
    field60 &= ~0x10000u;
    slot20(0);
}
