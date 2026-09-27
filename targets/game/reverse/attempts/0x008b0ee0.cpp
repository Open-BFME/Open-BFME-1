// ?d_008b0ee0@@YAXXZ
// partial score=0.28399888299357723 date=2026-09-27
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008B0EE0. Address-qualified property dispatch; retail extent includes two switch tables.
struct Rva00899560Value;
struct Rva00899560Pool {
    int m_capacity, m_count;
    Rva00899560Value **m_items;
    template <class T> __forceinline void addPooled(T *v) {
        int &count = m_count;
        if (count >= m_capacity) {
            v->m_flags &= 0xBFFFFFFF;
            return;
        }
        m_items[count] = (Rva00899560Value *)v;
        ++count;
    }
};
extern Rva00899560Pool *g_rva8CD130IdleHook;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned);
struct Rva00899560Value {
    virtual ~Rva00899560Value();
    unsigned m_flags;
    __forceinline Rva00899560Value(int type) {
        unsigned flags = (((m_flags & ~0x3f) | type) & 0xF000803F) | 0x8000;
        m_flags = flags;
        if (type != 0x1c && type != 0xa) {
            m_flags = flags | 0x40000000;
            g_rva8CD130IdleHook->addPooled(this);
        } else
            m_flags = flags & 0xBFFFFFFF;
    }
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
    static void operator delete(void *) {}
};
struct Rva008995E0Value : Rva00899560Value {
    union {
        bool m_value;
        Rva008995E0Value *m_next;
    };
    __forceinline Rva008995E0Value(bool x) : Rva00899560Value(5), m_value(x) {}
};
struct Rva008A1110Value : Rva00899560Value {
    union {
        int m_value;
        Rva008A1110Value *m_next;
    };
    __forceinline Rva008A1110Value(int x) : Rva00899560Value(7), m_value(x) {}
};
struct Rva008A4C00Value : Rva00899560Value {
    union {
        float m_value;
        Rva008A4C00Value *m_next;
    };
    __forceinline Rva008A4C00Value(float x) : Rva00899560Value(6), m_value(x) {}
};
extern Rva008995E0Value *Rva013387D4;
extern Rva008A1110Value *Rva013387D0;
extern Rva008A4C00Value *Rva008AF330Head;
template <class T, class V> __forceinline T *pooled(T *&head, V value) {
    T *v = head;
    if (v) {
        head = v->m_next;
        g_rva8CD130IdleHook->addPooled(v);
        v->m_value = value;
        return v;
    }
    return new T(value);
}
struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};
struct BfmeStringPool3AF0 {
    void *m_unknown00;
    void(__cdecl *free)(void *);
};
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class BfmeStrVKI {
  public:
    BfmeStringData3AF0 *m_data;
    __forceinline BfmeStrVKI() : m_data(&g_bfmeDefaultString1284) { ++m_data->m_refCount; }
    __forceinline ~BfmeStrVKI() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
    }
    __forceinline BfmeStrVKI &operator=(const BfmeStrVKI &other) {
        ++other.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0)
            g_bfmeStringPool1284->free(old);
        m_data = other.m_data;
        return *this;
    }
};
class BfmeStrVKK {
  public:
    void bfmeTruncVKK(unsigned);
};
struct Rva008A9A70Str {
    BfmeStringData3AF0 *m_block;
};
class Rva008A9A70 {
  public:
    void set(const Rva008A9A70Str &);
};
class Rva008B2EA0Node {
  public:
    void append(void *);
};
class Rva008A9B00 {
  public:
    static void *operator new(unsigned n) { return Rva008C5D70Alloc(n); }
    static void operator delete(void *) {}
    Rva008A9B00();
    void *m_vtable;
    unsigned m_flags;
    BfmeStrVKI m_string;
    Rva008A9B00 *m_next;
};
extern Rva008A9B00 *g_aptStringFreeList;
__forceinline Rva008A9B00 *pooledString() {
    Rva008A9B00 *v = g_aptStringFreeList;
    if (v) {
        g_aptStringFreeList = v->m_next;
        g_rva8CD130IdleHook->addPooled(v);
        if (v->m_string.m_data != &g_bfmeDefaultString1284)
            ((BfmeStrVKK *)&v->m_string)->bfmeTruncVKK(0);
    } else
        v = new Rva008A9B00;
    return v;
}
struct Rva8BB1A0Bounds {
    float left, top, right, bottom;
};
class BfmeN1235 {
  public:
    void bfmeInitEmpty1235(Rva8BB1A0Bounds *);
};
class BfmeB1236 {
  public:
    void bfmeApply1236(void *);
};
class Rva008A0F20Header {
  public:
    int isKind0F() const;
};
class Rva8CD130Value;
class Rva008AD750StringBinding {
  public:
    void refresh(Rva8CD130Value *);
};
struct BfmeM1208 {
    float m[6];
};
void bfmeMul1208(const BfmeM1208 *, const BfmeM1208 *, BfmeM1208 *);
void bfmeNormalizeEVF(void *, BfmeStrVKI *);
void bfmeResetEVF(void *, BfmeStrVKI *);
class BfmeSlotState1289 {
  public:
    void rva008AC790();
};
struct R4Word {
    const char *name;
    int value;
};
const R4Word *Rva008ABF40(const char *, unsigned);
const R4Word *Rva008D48F0(const char *, unsigned);
struct Rva008B0EE0State {
    char gap00[0xc];
    char *field0c;
    char gap10[8];
    BfmeStrVKI field18, field1c;
    unsigned field20, field24, field28, field2c, field30, field34;
    int field38;
    char gap3c[8];
    float field44, field48;
    char gap4c[0x20];
    unsigned field6c, field70, field74;
};
struct Rva008B0EE0Owner {
    void *vtable;
    unsigned flags;
    unsigned field08;
    BfmeStrVKI field0c;
    BfmeM1208 field10;
    float field28;
    char gap2c[0x1c];
    float *field48;
    Rva008B0EE0Owner *field4c;
    Rva008B0EE0State *field50;
    __forceinline bool active() const { return !((unsigned char)(~(flags >> 15)) & 1); }
    __forceinline void refresh() { ((BfmeB1236 *)this)->bfmeApply1236(field4c); }
};
extern Rva008A9A70Str Rva013385D8, Rva01338678, Rva01338524, Rva01338604;
extern Rva00899560Value *Rva013379BC, *Rva013379EC, *Rva013379C4, *Rva013379C8, *Rva013379F8,
    *Rva013379B8, *Rva013379B0;
extern BfmeM1208 Rva01337A08;
struct Rva013377D8Owner {
    char gap[0x1274];
    int field1274, field1278;
};
extern Rva013377D8Owner *Rva013377D8;
void *Rva00897640(unsigned);
class BfmeA1029 {
  public:
    static void *operator new(unsigned n) { return Rva00897640(n); }
    static void operator delete(void *) {}
    BfmeA1029 *bfmeGo1029A(int);
    __declspec(noinline) BfmeA1029(int callback);
    void bfmeBase1029(int, int);
    void *vtable;
    unsigned flags;
    char gap08[0x18];
    int callback;
};
struct Rva008B0EE0Slot {
    virtual void slot00();
};
extern BfmeA1029 *Rva01338300;
extern char Rva00cae490[];
extern BfmeA1029 *Rva0133830c;
extern char Rva00cae770[];
extern BfmeA1029 *Rva013382fc;
extern char Rva00cae470[];
extern BfmeA1029 *Rva013382f8;
extern char Rva00cae450[];
extern BfmeA1029 *Rva01338304;
extern char Rva00cae600[];
extern BfmeA1029 *Rva01338338;
extern char Rva00caf210[];
extern BfmeA1029 *Rva01338340;
extern char Rva00caf2f0[];
extern BfmeA1029 *Rva01338348;
extern char Rva00cacf90[];
extern BfmeA1029 *Rva01338310;
extern char Rva00cacea0[];
extern BfmeA1029 *Rva0133833c;
extern char Rva00caf2b0[];
extern BfmeA1029 *Rva01338350;
extern char Rva00caf4c0[];
extern BfmeA1029 *Rva0133834c;
extern char Rva00caf330[];
extern BfmeA1029 *Rva01338344;
extern char Rva00cacf60[];
extern BfmeA1029 *Rva01338318;
extern char Rva00cae7c0[];
extern BfmeA1029 *Rva0133831c;
extern char Rva00caea80[];
extern BfmeA1029 *Rva01338334;
extern char Rva00caf0b0[];
extern BfmeA1029 *Rva01338328;
extern char Rva00cb02a0[];
extern BfmeA1029 *Rva01338330;
extern char Rva00caeec0[];
extern BfmeA1029 *Rva01338314;
extern char Rva00cacf00[];
extern BfmeA1029 *Rva01338320;
extern char Rva00caeac0[];
extern BfmeA1029 *Rva01338308;
extern char Rva00cacdc0[];
extern BfmeA1029 *Rva01338324;
extern char Rva00caecc0[];
extern BfmeA1029 *Rva01338358;
extern char Rva00cb0b00[];
extern BfmeA1029 *Rva0133835c;
extern char Rva00cb0cf0[];
extern BfmeA1029 *Rva01338354;
extern char Rva00cb09a0[];
extern BfmeA1029 *Rva0133832c;
extern char Rva00caed50[];
Rva00899560Value *rva008B0EE0(Rva008B0EE0Owner *owner, const BfmeStrVKI &key) {
    unsigned flags = owner->flags;
    int kind = flags & 0x3f;
    const R4Word *word;
    union {
        BfmeM1208 matrix;
        Rva8BB1A0Bounds bounds;
    } scratch;
    BfmeM1208 &m = scratch.matrix;
    if (kind == 15 && !((unsigned char)(~(flags >> 15)) & 1) &&
        (word = Rva008ABF40((const char *)key.m_data + 8, key.m_data->m_length))) {
        Rva008B0EE0State *state = owner->field50;
        switch (word->value) {
        case 1: {
            Rva008A9B00 *v = pooledString();
            switch (state->field38) {
            case 0:
                ((Rva008A9A70 *)v)->set(Rva013385D8);
                break;
            case 1:
                ((Rva008A9A70 *)v)->set(Rva01338678);
                break;
            case 2:
                ((Rva008A9A70 *)v)->set(Rva01338524);
                break;
            case 3:
                ((Rva008A9A70 *)v)->set(Rva01338604);
                break;
            default:
                ((Rva008A9A70 *)v)->set(Rva01338604);
                break;
            }
            return (Rva00899560Value *)v;
        }
        case 2:
            return pooled(Rva013387D4, ((state->field74 >> 2) & 1) != 0);
        case 3:
            return pooled(Rva013387D0, (int)(state->field30 & 0xffffff));
        case 4:
            return pooled(Rva013387D4, ((state->field74 >> 1) & 1) != 0);
        case 5:
            return pooled(Rva013387D0, (int)(state->field34 & 0xffffff));
        case 7:
            ((Rva008AD750StringBinding *)state)->refresh((Rva8CD130Value *)owner);
            return pooled(Rva013387D0, (int)state->field18.m_data->m_length);
        case 8:
            return Rva013379BC;
        case 9:
            if (state->field6c & 4)
                owner->refresh();
            return pooled(Rva013387D0, (int)state->field28);
        case 10:
            return pooled(Rva013387D4, (*(unsigned *)(state->field0c + 0x2c) & 0xffffff) != 0);
        case 11:
            if (state->field6c & 4)
                owner->refresh();
            return pooled(Rva013387D0, (int)state->field2c);
        case 12: {
            ((Rva008AD750StringBinding *)state)->refresh((Rva8CD130Value *)owner);
            Rva008A9B00 *v = pooledString();
            v->m_string = state->field18;
            return (Rva00899560Value *)v;
        }
        case 13:
            return pooled(Rva013387D0, (int)(state->field24 & 0xffffff));
        case 14:
            if (state->field6c & 4)
                owner->refresh();
            return pooled(Rva008AF330Head, state->field48);
        case 15:
            if (state->field6c & 4)
                owner->refresh();
            return pooled(Rva008AF330Head, state->field44);
        case 16: {
            Rva008A9B00 *v = pooledString();
            ((Rva008B2EA0Node *)v)->append((void *)"dynamic");
            return (Rva00899560Value *)v;
        }
        case 17: {
            if (state->field1c.m_data == &g_bfmeDefaultString1284)
                return Rva013379BC;
            Rva008A9B00 *v = pooledString();
            v->m_string = state->field1c;
            return (Rva00899560Value *)v;
        }
        case 18:
            return pooled(Rva013387D4, (*(unsigned *)(state->field0c + 0x30) & 0xffffff) != 0);
        case 19: {
            if (state->field6c & 4)
                owner->refresh();
            Rva8BB1A0Bounds &b = scratch.bounds;
            ((BfmeN1235 *)owner)->bfmeInitEmpty1235(&b);
            float v = b.bottom - b.top;
            if (v < 0)
                v = 0;
            return pooled(Rva008AF330Head, v);
        }
        case 20: {
            if (state->field6c & 4)
                owner->refresh();
            Rva8BB1A0Bounds &b = scratch.bounds;
            ((BfmeN1235 *)owner)->bfmeInitEmpty1235(&b);
            float v = b.right - b.left;
            if (v < 0)
                v = 0;
            return pooled(Rva008AF330Head, v);
        }
        case 21:
            return pooled(Rva013387D4, ((state->field74 >> 3) & 1) != 0);
        }
    }
    if (!(kind >= 12 && kind <= 19 && !((unsigned char)(~(flags >> 15)) & 1)))
        return 0;
    word = Rva008D48F0((const char *)key.m_data + 8, key.m_data->m_length);
    if (!word)
        return 0;
    Rva008B0EE0State *state = owner->field50;
    switch (word->value) {
    case 1:
        if ((unsigned char)((Rva008A0F20Header *)owner)->isKind0F() && state->field38 != 3 &&
            state->field38 != 0 && (state->field6c & 4))
            owner->refresh();
        return pooled(Rva008AF330Head, owner->field10.m[4]);
    case 2:
        return pooled(Rva008AF330Head, owner->field10.m[5]);
    case 3:
        return pooled(Rva008AF330Head,
                      owner->field48 ? owner->field48[2] : owner->field10.m[0] * 100.0f);
    case 4:
        return pooled(Rva008AF330Head,
                      owner->field48 ? owner->field48[3] : owner->field10.m[3] * 100.0f);
    case 7:
        return pooled(Rva008AF330Head,
                      owner->field48 ? owner->field48[7] : owner->field28 * 100.0f);
    case 8:
        return pooled(Rva008AF330Head, owner->field48 ? owner->field48[11] : 1.0f);
    case 5:
        return pooled(Rva008AF330Head, (float)((int)state->field18.m_data + 1));
    case 24:
        return Rva013379EC;
    case 25:
        return Rva013379C4;
    case 26:
        return Rva013379C8;
    case 27:
        return Rva013379F8;
    case 28:
        return Rva013379B8;
    case 29:
        return Rva013379B0;
    case 12: {
        BfmeStrVKI text;
        bfmeNormalizeEVF(owner, &text);
        Rva008A9B00 *v = pooledString();
        v->m_string = text;
        return (Rva00899560Value *)v;
    }
    case 9: {
        Rva8BB1A0Bounds &b = scratch.bounds;
        ((BfmeN1235 *)owner)->bfmeInitEmpty1235(&b);
        float v = b.right - b.left;
        if (v < 0)
            v = 0;
        return pooled(Rva008AF330Head, v);
    }
    case 10: {
        Rva8BB1A0Bounds &b = scratch.bounds;
        ((BfmeN1235 *)owner)->bfmeInitEmpty1235(&b);
        float v = b.bottom - b.top;
        if (v < 0)
            v = 0;
        return pooled(Rva008AF330Head, v);
    }
    case 11:
        ((BfmeSlotState1289 *)owner)->rva008AC790();
        return pooled(Rva008AF330Head, owner->field48[6]);
    case 6:
        return pooled(Rva008AF330Head, (float)*(int *)(state->field0c + 8));
    case 13:
        return pooled(Rva008AF330Head, (float)*(int *)(state->field0c + 8));
    case 21: {
        m.m[0] = Rva01337A08.m[0];
        m.m[1] = Rva01337A08.m[1];
        m.m[2] = Rva01337A08.m[2];
        m.m[3] = Rva01337A08.m[3];
        m.m[4] = Rva01337A08.m[4];
        m.m[5] = Rva01337A08.m[5];
        do {
            bfmeMul1208(&m, &owner->field10, &m);
            owner = owner->field4c;
        } while (owner);
        float v = ((float)Rva013377D8->field1274 - m.m[4]) * m.m[0] -
                  ((float)Rva013377D8->field1278 - m.m[5]) * m.m[1];
        return pooled(Rva008AF330Head, v);
    }
    case 22: {
        m.m[0] = Rva01337A08.m[0];
        m.m[1] = Rva01337A08.m[1];
        m.m[2] = Rva01337A08.m[2];
        m.m[3] = Rva01337A08.m[3];
        m.m[4] = Rva01337A08.m[4];
        m.m[5] = Rva01337A08.m[5];
        do {
            bfmeMul1208(&m, &owner->field10, &m);
            owner = owner->field4c;
        } while (owner);
        float v = ((float)Rva013377D8->field1274 - m.m[4]) * m.m[2] +
                  ((float)Rva013377D8->field1278 - m.m[5]) * m.m[3];
        return pooled(Rva008AF330Head, v);
    }
    case 118:
        if (!Rva01338330) {
            Rva01338330 = new BfmeA1029((int)Rva00caeec0);
            Rva01338330->flags = (Rva01338330->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338330)->slot00();
        }
        return (Rva00899560Value *)Rva01338330;
    case 126:
        if (!Rva0133832c) {
            Rva0133832c = new BfmeA1029((int)Rva00caed50);
            Rva0133832c->flags = (Rva0133832c->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva0133832c)->slot00();
        }
        return (Rva00899560Value *)Rva0133832c;
    case 106:
        if (!Rva01338338) {
            Rva01338338 = new BfmeA1029((int)Rva00caf210);
            Rva01338338->flags = (Rva01338338->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338338)->slot00();
        }
        return (Rva00899560Value *)Rva01338338;
    case 103:
        if (!Rva013382fc) {
            Rva013382fc = new BfmeA1029((int)Rva00cae470);
            Rva013382fc->flags = (Rva013382fc->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva013382fc)->slot00();
        }
        return (Rva00899560Value *)Rva013382fc;
    case 104:
        if (!Rva013382f8) {
            Rva013382f8 = new BfmeA1029((int)Rva00cae450);
            Rva013382f8->flags = (Rva013382f8->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva013382f8)->slot00();
        }
        return (Rva00899560Value *)Rva013382f8;
    case 100:
        if (!Rva01338300) {
            Rva01338300 = new BfmeA1029((int)Rva00cae490);
            Rva01338300->flags = (Rva01338300->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338300)->slot00();
        }
        return (Rva00899560Value *)Rva01338300;
    case 107:
        if (!Rva01338340) {
            Rva01338340 = new BfmeA1029((int)Rva00caf2f0);
            Rva01338340->flags = (Rva01338340->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338340)->slot00();
        }
        return (Rva00899560Value *)Rva01338340;
    case 110:
        if (!Rva0133833c) {
            Rva0133833c = new BfmeA1029((int)Rva00caf2b0);
            Rva0133833c->flags = (Rva0133833c->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva0133833c)->slot00();
        }
        return (Rva00899560Value *)Rva0133833c;
    case 108:
        if (!Rva01338348) {
            Rva01338348 = new BfmeA1029((int)Rva00cacf90);
            Rva01338348->flags = (Rva01338348->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338348)->slot00();
        }
        return (Rva00899560Value *)Rva01338348;
    case 113:
        if (!Rva01338344) {
            Rva01338344 = new BfmeA1029((int)Rva00cacf60);
            Rva01338344->flags = (Rva01338344->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338344)->slot00();
        }
        return (Rva00899560Value *)Rva01338344;
    case 112:
        if (!Rva0133834c) {
            Rva0133834c = new BfmeA1029((int)Rva00caf330);
            Rva0133834c->flags = (Rva0133834c->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva0133834c)->slot00();
        }
        return (Rva00899560Value *)Rva0133834c;
    case 111:
        if (!Rva01338350) {
            Rva01338350 = new BfmeA1029((int)Rva00caf4c0);
            Rva01338350->flags = (Rva01338350->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338350)->slot00();
        }
        return (Rva00899560Value *)Rva01338350;
    case 101:
        if (!Rva0133830c) {
            Rva0133830c = new BfmeA1029((int)Rva00cae770);
            Rva0133830c->flags = (Rva0133830c->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva0133830c)->slot00();
        }
        return (Rva00899560Value *)Rva0133830c;
    case 109:
        if (!Rva01338310) {
            Rva01338310 = new BfmeA1029((int)Rva00cacea0);
            Rva01338310->flags = (Rva01338310->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338310)->slot00();
        }
        return (Rva00899560Value *)Rva01338310;
    case 105:
        if (!Rva01338304) {
            Rva01338304 = new BfmeA1029((int)Rva00cae600);
            Rva01338304->flags = (Rva01338304->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338304)->slot00();
        }
        return (Rva00899560Value *)Rva01338304;
    case 121:
        if (!Rva01338308) {
            Rva01338308 = new BfmeA1029((int)Rva00cacdc0);
            Rva01338308->flags = (Rva01338308->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338308)->slot00();
        }
        return (Rva00899560Value *)Rva01338308;
    case 114:
        if (!Rva01338318) {
            Rva01338318 = new BfmeA1029((int)Rva00cae7c0);
            Rva01338318->flags = (Rva01338318->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338318)->slot00();
        }
        return (Rva00899560Value *)Rva01338318;
    case 119:
        if (!Rva01338314) {
            Rva01338314 = new BfmeA1029((int)Rva00cacf00);
            Rva01338314->flags = (Rva01338314->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338314)->slot00();
        }
        return (Rva00899560Value *)Rva01338314;
    case 115:
        if (!Rva0133831c) {
            Rva0133831c = new BfmeA1029((int)Rva00caea80);
            Rva0133831c->flags = (Rva0133831c->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva0133831c)->slot00();
        }
        return (Rva00899560Value *)Rva0133831c;
    case 117:
        if (!Rva01338328) {
            Rva01338328 = new BfmeA1029((int)Rva00cb02a0);
            Rva01338328->flags = (Rva01338328->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338328)->slot00();
        }
        return (Rva00899560Value *)Rva01338328;
    case 116:
        if (!Rva01338334) {
            Rva01338334 = new BfmeA1029((int)Rva00caf0b0);
            Rva01338334->flags = (Rva01338334->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338334)->slot00();
        }
        return (Rva00899560Value *)Rva01338334;
    case 120:
        if (!Rva01338320) {
            Rva01338320 = new BfmeA1029((int)Rva00caeac0);
            Rva01338320->flags = (Rva01338320->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338320)->slot00();
        }
        return (Rva00899560Value *)Rva01338320;
    case 122:
        if (!Rva01338324) {
            Rva01338324 = new BfmeA1029((int)Rva00caecc0);
            Rva01338324->flags = (Rva01338324->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338324)->slot00();
        }
        return (Rva00899560Value *)Rva01338324;
    case 14: {
        Rva008A9B00 *v = pooledString();
        v->m_string = owner->field0c;
        return (Rva00899560Value *)v;
    }
    case 16: {
        Rva008A9B00 *v = pooledString();
        BfmeStrVKI text;
        bfmeResetEVF(owner, &text);
        ((Rva008B2EA0Node *)v)->append((char *)text.m_data + 8);
        return (Rva00899560Value *)v;
    }
    case 124:
        if (!Rva0133835c) {
            Rva0133835c = new BfmeA1029((int)Rva00cb0cf0);
            Rva0133835c->flags = (Rva0133835c->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva0133835c)->slot00();
        }
        return (Rva00899560Value *)Rva0133835c;
    case 123:
        if (!Rva01338358) {
            Rva01338358 = new BfmeA1029((int)Rva00cb0b00);
            Rva01338358->flags = (Rva01338358->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338358)->slot00();
        }
        return (Rva00899560Value *)Rva01338358;
    case 125:
        if (!Rva01338354) {
            Rva01338354 = new BfmeA1029((int)Rva00cb09a0);
            Rva01338354->flags = (Rva01338354->flags & 0xffffc07f) | 0x40;
            ((Rva008B0EE0Slot *)Rva01338354)->slot00();
        }
        return (Rva00899560Value *)Rva01338354;
    }
    return 0;
}

extern "C" void *bfmeVft1029A[];
BfmeA1029::BfmeA1029(int value) {
    bfmeBase1029(9, 8);
    callback = value;
    vtable = bfmeVft1029A;
}
