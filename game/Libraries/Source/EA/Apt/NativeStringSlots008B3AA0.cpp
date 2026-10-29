// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Two independent 206-byte bodies: 008B3AA0 and 008B3B70, each followed by 2 INT3 bytes.
struct StringBlock008B3AA0 { unsigned short field00; };
// Retail 0x012D5298 is ?g_rva012D5298Empty@@3VStringDataC@EAStringC@@A
// (data_rows.csv, Common/Data/Rva012D5298.cpp); g_default012D5298 was only a pin.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;
#define g_default012D5298 ( *(StringBlock008B3AA0 *)&g_rva012D5298Empty )
struct StringPool008B3AA0 { void *field00; void (__cdecl *free)(void *); };
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class Rva8CD130String {
public:
    StringBlock008B3AA0 *field00;
    Rva8CD130String() { field00 = &g_default012D5298; ++g_default012D5298.field00; }
    ~Rva8CD130String() { StringBlock008B3AA0 *p = field00; if (--p->field00 == 0) (*(StringPool008B3AA0 **)&g_rva01337A30AllocPair)->free(p); }
};
struct NativeSlots008B3AA0 {
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80(const char *);
    virtual void slot84();
    virtual void slot88(const char *);
    void call80(const Rva8CD130String &s) { if (this) slot80((char *)s.field00 + 8); }
    void call88(const Rva8CD130String &s) { if (this) slot88((char *)s.field00 + 8); }
};
class Rva8CD130Value {
public:
    void getName(Rva8CD130String *);
    void *field00;
    unsigned field04;
    char field08[0x18];
    NativeSlots008B3AA0 *field20;
    unsigned getKind() const { return field04 & 0x3f; }
    bool stringKind() const { unsigned f = field04; unsigned t = f & 0x3f; return (t == 1 || t == 42) && !((unsigned char)(~(f >> 15)) & 1); }
};
struct Rva008AE770Stack { int m_count; };
extern Rva008AE770Stack Rva008AE770TheStack;
class AptValue;
extern AptValue *g_bfmeFallbackDB;
void *nativeStringSlot80At008B3AA0(Rva8CD130Value *owner, int count) {
    if (count >= 1 && owner->getKind() == 0x21) {
        Rva8CD130Value *arg = (*(Rva8CD130Value ***)((char *)&Rva008AE770TheStack + 8))[Rva008AE770TheStack.m_count - 1];
        if (arg->stringKind()) {
            Rva8CD130String text;
            arg->getName(&text);
            owner->field20->call80(text);
        }
    }
    return (*(void **)&g_bfmeFallbackDB);
}
void *nativeStringSlot88At008B3B70(Rva8CD130Value *owner, int count) {
    if (count >= 1 && owner->getKind() == 0x21) {
        Rva8CD130Value *arg = (*(Rva8CD130Value ***)((char *)&Rva008AE770TheStack + 8))[Rva008AE770TheStack.m_count - 1];
        if (arg->stringKind()) {
            Rva8CD130String text;
            arg->getName(&text);
            owner->field20->call88(text);
        }
    }
    return (*(void **)&g_bfmeFallbackDB);
}
