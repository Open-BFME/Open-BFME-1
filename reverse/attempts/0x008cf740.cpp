// ?d_008cf740@@YAXXZ
// partial score=0.8130046748831279 date=2026-09-22
// ?run@Rva008CF740@@QAEXPAVRva008CF740Value@@0H@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Complete address-derived reconstruction of RVA 008CF740, 2353B.
// See ANALYSIS.md for retail offsets, contracts, and EH states 0..9.
// No original hub class/member identity is claimed. No naked/inline assembly.
// Retail frame: push -1/handler/old-FS; sub esp,1c; save ebx,ebp,esi,edi;
// final ret 0c. Actual compiler frame is measured in PROGRESS.md, not asserted.
// Callee RVAs and global VAs are distinct: image base is 00400000.
// Standalone object reconstruction; opaque external declarations are NOT new pins.
// The active bank is filed under ?d_008cf740@@YAXXZ; probe the run symbol above.

struct Rva008CF740Block { unsigned short refs; };
extern Rva008CF740Block g_default012D5298;
extern void (__cdecl **Rva01337A30ReleaseTable)(void *);

class BfmeStrVKI
{
public:
    BfmeStrVKI() { m_block = &g_default012D5298; ++g_default012D5298.refs; }
    BfmeStrVKI(const char *p) { bfmeSetVKI(p); }
    void bfmeSetVKI(const char *p); // 0089E680, ret4
    __forceinline BfmeStrVKI &operator=(const BfmeStrVKI &other)
    {
        ++other.m_block->refs;
        Rva008CF740Block *old = m_block;
        if (--old->refs == 0) Rva01337A30ReleaseTable[1](old);
        m_block = other.m_block;
        return *this;
    }
    ~BfmeStrVKI()
    {
        Rva008CF740Block *p = m_block;
        --p->refs;
        if (p->refs == 0) Rva01337A30ReleaseTable[1](p);
    }
    Rva008CF740Block *m_block;
};

struct Rva008CF740StringValue { void *m_00; unsigned m_04; Rva008CF740Block *m_08; };

class Rva008CF740Value
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24();
    virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34();
    virtual void slot38(); virtual void slot3C();
    virtual void slot40(); virtual void slot44();
    virtual void slot48(); virtual int slot4C();
    Rva008CF740Value *rva0089C290(BfmeStrVKI *, Rva008CF740Value *);
    __forceinline Rva008CF740StringValue *stringView()
    {
        if ((m_04 & 0x3f) == 1) return (Rva008CF740StringValue *)this;
        return (Rva008CF740StringValue *)m_20;
    }
    unsigned m_04;
    char m_08[0x18];
    void *m_20;
    unsigned m_24;
    Rva008CF740Value *m_28;
    unsigned m_2C;
    void *m_30;
    unsigned char invalid() const { return (unsigned char)~(m_04 >> 15) & 1; }
    bool marked() const { return ((m_04 >> 30) & 1) != 0; }
};
typedef Rva008CF740Value Value;

class Rva008A0F20Header
{
public:
    int isKind13() const;
    unsigned char invalid() const { return (unsigned char)~(m_04 >> 15) & 1; }
    unsigned m_00;
    unsigned m_04;
    char m_08[0x58];
    unsigned m_60;
};

struct Rva008CF740D1
{
    unsigned m_00;
    int m_04;
    const char **m_08;
    int m_0C;
    int m_10;
    void *m_14;
    unsigned char m_18[1];
};
struct Rva008CF740Formal2 { int m_00; const char *m_04; };
struct Rva008CF740D2
{
    unsigned m_00;
    int m_04;
    unsigned short m_08;
    unsigned char m_0A;
    unsigned char m_0B;
    Rva008CF740Formal2 *m_0C;
    int m_10;
    int m_14;
    void *m_18;
    unsigned char m_1C[1];
};

extern void *Rva008C4890(unsigned bytes);
class Rva8CBC80Derived
{
public:
    Rva8CBC80Derived();
    static void *operator new(unsigned bytes) { return Rva008C4890(bytes); }
    static void operator delete(void *, unsigned); // EH only: RVA 008C48C0, cdecl
    char m_00[0x18];
};
class BfmeStackBB { public: void bfmePopN(int); };
class BfmeA1232 { public: void bfmePop1232(int); };
class BfmeItem937E;
class BfmeThing937E { public: void bfmeGo937E(BfmeItem937E *); };
class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table
{
public:
    void add(Rva8D0D80String *, Rva8D0D80Value *);
};
extern Value *g_fallback013379BC;
extern Value *g_value013387D8;
extern BfmeStrVKI g_string01338710;
extern BfmeStrVKI g_string01338700;

struct Rva008CF740Array
{
    int m_00; unsigned m_04; Value **m_08;
    __forceinline void pop()
    {
        m_08[m_00 - 1]->slot04();
        --m_00;
    }
};

class Rva008CF740
{
public:
    void run(Value *argument1, Value *argument2, int argument3);
    bool rva008CC690(Value *, void *, BfmeStrVKI *, Value *, int, int, int); // ret1C, AL
    Value *rva008CC940(Value *, void *, BfmeStrVKI *, int, int, int); // ret18, EAX
    unsigned char *rva008CCED0(unsigned char *, Value *, int); // ret0C, EAX cursor
    int m_00; unsigned m_04; Value **m_08;
    int m_0C; unsigned m_10; Value **m_14;
    char m_18[0x18];
    int m_30; unsigned m_34; Value **m_38;
    int m_3C; unsigned m_40; Value **m_44;
    int m_48; unsigned m_4C; int m_50;
    Value **m_54; Value **m_58;
    int m_5C; void *m_60;
    char m_64[0x18];
    void *m_7C;
};

struct Rva008CF740Slot
{
    Value *m_00;
    __forceinline void release() { if (m_00) m_00->slot04(); }
};

static __forceinline const char *entryText(Value *v)
{
    return (const char *)v->stringView()->m_08 + 8;
}

void Rva008CF740::run(Value *argument1, Value *argument2, int argument3)
{
    Value *function = argument2;
    struct Snapshot { int entryCount; int saved5C; void *saved60; };
    Snapshot saved;
    saved.entryCount = m_00;
    if (function != 0)
    {
        unsigned kind = function->m_04 & 0x3f;
        if (kind == 9 && !function->invalid())
        {
            typedef Value *(__cdecl *Callback)(Value *, int);
            Value *result = ((Callback)function->m_20)(argument1, argument3);
            ((BfmeStackBB *)this)->bfmePopN(argument3);
            m_08[m_00++] = result;
            if (!result->marked()) result->slot00();
            goto finished;
        }
        if (kind == 10 && !function->invalid())
        {
            saved.saved5C = m_5C;
            saved.saved60 = m_60;
            if (function->slot4C() == 1)
            {
                Rva008A0F20Header *bound = (Rva008A0F20Header *)function->m_28;
                const int saved3C = m_3C;
                Rva008CF740D1 *body = (Rva008CF740D1 *)function->m_30;
                if (bound->invalid() ||
                    ((unsigned char)bound->isKind13() &&
                     (bound->m_60 & 0xc0000) == 0) ||
                    (bound->m_60 & 0xc0000) == 0x80000)
                    goto unusable;
                m_5C = body->m_10;
                m_60 = body->m_14;
                Value *frame = (Value *)function->m_20;
                if (frame == 0) frame = (Value *)new Rva8CBC80Derived;
                ((BfmeThing937E *)&m_0C)->bfmeGo937E((BfmeItem937E *)frame);
                const int limit = body->m_04 < argument3 ? body->m_04 : argument3;
                for (int i = 0; i < body->m_04; ++i)
                {
                    Value *value = i < limit ? m_08[m_00 - i - 1] : g_fallback013379BC;
                    BfmeStrVKI name(body->m_08[i]);
                    rva008CC690(function->m_28, 0, &name, value, 0, 1, 0);
                }
                ((BfmeStackBB *)this)->bfmePopN(argument3);
                m_38[m_30++] = argument1;
                argument1->slot00();
                rva008CCED0(body->m_18, function->m_28, body->m_0C);
                ((Rva008CF740Array *)&m_30)->pop();
                if (m_3C > 0 && m_3C != saved3C)
                {
                    int count = m_3C - saved3C;
                    BfmeStrVKI name;
                    for (; count > 0; --count)
                    {
                        name = BfmeStrVKI(entryText(m_44[m_3C - 1]));
                        ((Rva8D0D80Table *)((char *)m_14[m_0C - 1] + 8))->add(
                            (Rva8D0D80String *)&name, 0);
                        m_44[m_3C - 1]->slot04();
                        --m_3C;
                    }
                }
                m_14[m_0C - 1]->slot04();
                --m_0C;
                m_5C = saved.saved5C;
                m_60 = saved.saved60;
                goto finished;
            }
            if (function->slot4C() == 2)
            {
                Rva008A0F20Header *bound = (Rva008A0F20Header *)function->m_28;
                Rva008CF740D2 *body = (Rva008CF740D2 *)function->m_30;
                const int saved3C = m_3C;
                if (bound->invalid() ||
                    ((unsigned char)bound->isKind13() &&
                     (bound->m_60 & 0xc0000) == 0) ||
                    (bound->m_60 & 0xc0000) == 0x80000)
                {
                    ((BfmeStackBB *)this)->bfmePopN(argument3);
                    Value *value = g_fallback013379BC;
                    m_08[m_00++] = value;
                    if (!value->marked()) value->slot00();
                    goto finished;
                }
                m_5C = body->m_14;
                m_60 = body->m_18;
                Value *frame = (Value *)function->m_20;
                if (frame == 0) frame = (Value *)new Rva8CBC80Derived;
                ((BfmeThing937E *)&m_0C)->bfmeGo937E((BfmeItem937E *)frame);
                m_58 = m_54 + m_50 * m_48++;
                const int width = m_50;
                for (int r = 0; r < width; ++r) m_58[r] = g_fallback013379BC;
                const int limit = body->m_04 < argument3 ? body->m_04 : argument3;
                for (int i = 0; i < body->m_04; ++i)
                {
                    Value *value = i < limit ? m_08[m_00 - i - 1] : g_fallback013379BC;
                    Rva008CF740Formal2 *formal = body->m_0C + i;
                    if (formal->m_00)
                    {
                        m_58[formal->m_00] = value;
                        value->slot00();
                    }
                    else
                    {
                        BfmeStrVKI name(formal->m_04);
                        rva008CC690(function->m_28, 0, &name, value, 0, 1, 0);
                    }
                }
                ((BfmeStackBB *)this)->bfmePopN(argument3);
                m_38[m_30++] = argument1;
                argument1->slot00();
                int next = 1;
                Value *value = 0;
                if (body->m_0A & 1)
                {
                    value = function->m_28->rva0089C290(&g_string01338710, 0);
                    m_58[next++] = value;
                    if (value) value->slot00();
                }
                if (body->m_0A & 4)
                {
                    value = g_fallback013379BC;
                    m_58[next++] = value;
                    if (value) value->slot00();
                }
                if (body->m_0A & 0x10)
                {
                    value = rva008CC940(argument1, 0, &g_string01338700, 1, 1, 0);
                    if (value == 0 || (value->m_04 & 0x8000) == 0)
                        value = function->m_28->rva0089C290(&g_string01338700, 0);
                    m_58[next++] = value;
                    if (value) value->slot00();
                }
                if (body->m_0A & 0x40)
                {
                    BfmeStrVKI name("_root");
                    value = function->m_28->rva0089C290(&name, 0);
                    m_58[next++] = value;
                    if (value) value->slot00();
                }
                if (body->m_0A & 0x80)
                {
                    BfmeStrVKI name("_parent");
                    value = function->m_28->rva0089C290(&name, 0);
                    if (value == 0) value = g_fallback013379BC;
                    m_58[next++] = value;
                    if (value) value->slot00();
                }
                if (body->m_0B & 1)
                {
                    m_58[next] = g_value013387D8;
                    // Retail +069D..06B0 retains the previous value, not the global.
                    if (value) value->slot00();
                }
                rva008CCED0(body->m_1C, function->m_28, body->m_10);
                ((Rva008CF740Array *)&m_30)->pop();
                if (m_3C > 0 && m_3C != saved3C)
                {
                    int count = m_3C - saved3C;
                    BfmeStrVKI name;
                    for (; count > 0; --count)
                    {
                        name = BfmeStrVKI(entryText(m_44[m_3C - 1]));
                        ((Rva8D0D80Table *)((char *)m_14[m_0C - 1] + 8))->add(
                            (Rva8D0D80String *)&name, 0);
                        m_44[m_3C - 1]->slot04();
                        --m_3C;
                    }
                }
                for (int i = 0; i < body->m_04; ++i)
                {
                    if (body->m_0C[i].m_00)
                    {
                        if (m_58[body->m_0C[i].m_00])
                            m_58[body->m_0C[i].m_00]->slot04();
                        m_58[body->m_0C[i].m_00] = g_fallback013379BC;
                    }
                }
                for (int r = 0; r < width; ++r)
                {
                    Value *v = m_58[r];
                    // Retail +0837 reads the flag word before checking v for null.
                    if (*(unsigned short *)((char *)v + 6) & 0xfff)
                        ((Rva008CF740Slot *)(m_58 + r))->release();
                    m_58[r] = g_fallback013379BC;
                }
                if (m_48 == 0) m_58 = m_54;
                else { --m_48; m_58 = m_54 + m_50 * (m_48 - 1); }
                m_14[m_0C - 1]->slot04();
                --m_0C;
                m_5C = saved.saved5C;
                m_60 = saved.saved60;
            }
            goto finished;
        }
    }
unusable:
    ((BfmeStackBB *)this)->bfmePopN(argument3);
    {
        Value *value = g_fallback013379BC;
        m_08[m_00++] = value;
        if (!value->marked()) value->slot00();
    }
finished:
    if (m_7C != 0 && m_00 > saved.entryCount - argument3)
        ((BfmeA1232 *)this)->bfmePop1232(m_00 - saved.entryCount + argument3);
}
