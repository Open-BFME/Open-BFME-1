// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008A7B00 / 5603 bytes. Vtable slot +20h, two stack arguments, ret 8; incoming ECX is unused.
// Complete keyboard property dispatch: 18 pooled integer constants and eight
// cached native callbacks. The retail hash table proves the property names;
// the function and owner identities remain address-derived.
// Evidence: targets/game/reverse/identity_evidence/008a7b00-keyboard-properties.md
// Model: GPT-6.
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
};
struct Rva008A1110Value : Rva00899560Value {
    union {
        int m_value;
        Rva008A1110Value *m_next;
    };
    __forceinline Rva008A1110Value(int x) : Rva00899560Value(7), m_value(x) {}
};
// The pooled-integer free head at 0x013387D0 is the defining Rva008D2A10 list
// (see game/GameEngine/Source/Common/Rva008D2A10Link.cpp); it has no header,
// so forward-declare it and spell the reference with its defining type.
class Rva008D2A10;
extern Rva008D2A10 *g_rva008D2A10;
static __forceinline Rva008A1110Value *pooledInteger(int value) {
    Rva008A1110Value *v = (Rva008A1110Value *)g_rva008D2A10;
    if (v) {
        g_rva008D2A10 = (Rva008D2A10 *)v->m_next;
        g_rva8CD130IdleHook->addPooled(v);
        v->m_value = value;
        return v;
    }
    return new Rva008A1110Value(value);
}
struct Rva008A7B00Owner {
    void *vtable;
    unsigned flags;
};
struct Rva008A7B00Buffer {
    unsigned short refs, length;
};
struct Rva008A7B00String {
    Rva008A7B00Buffer *data;
};
struct BfmeW1229 {
    const char *name;
    int id;
};
const BfmeW1229 *bfmeFind1229(const char *, unsigned);
void *Rva00897640(unsigned);
class Rva00897670HeaderedDelete {
  public:
    static void operator delete(void *, unsigned);
};
class Rva00899FC0 : public Rva00897670HeaderedDelete {
  public:
    static void *operator new(unsigned n) { return Rva00897640(n); }
    __declspec(noinline) Rva00899FC0(int callback);
    void *vtable;
    unsigned flags;
    char gap08[0x18];
    int callback;
};
struct Rva008A7B00Slot {
    virtual void slot00();
};
extern Rva00899FC0 *Va01337A7C;
extern char Va00CA5250[];
extern Rva00899FC0 *Va01337A80;
extern char Va00CA52E0[];
extern Rva00899FC0 *Va01337A84;
extern char Va00CA52F0[];
extern Rva00899FC0 *Va01337A8C;
extern char Va00CA5360[];
extern Rva00899FC0 *Va01337A90;
extern char Va00CA5380[];
extern Rva00899FC0 *Va01337A94;
extern char Va00CA53D0[];
extern Rva00899FC0 *Va01337A98;
extern char Va00CA6CB0[];
extern Rva00899FC0 *Va01337A88;
extern char Va00CA5330[];
Rva00899560Value *__stdcall rva008A7B00(Rva008A7B00Owner *owner, const Rva008A7B00String *key) {
    if (owner) {
        unsigned flags = owner->flags;
        if ((flags & 0x3f) == 0x18 && !((unsigned char)(~(flags >> 15)) & 1)) {
            const BfmeW1229 *word = bfmeFind1229((const char *)key->data + 8, key->data->length);
            if (word) {
                switch (word->id) {
                case 1:
                    return pooledInteger(8);
                case 2:
                    return pooledInteger(20);
                case 3:
                    return pooledInteger(17);
                case 4:
                    return pooledInteger(46);
                case 5:
                    return pooledInteger(40);
                case 6:
                    return pooledInteger(35);
                case 7:
                    return pooledInteger(13);
                case 8:
                    return pooledInteger(27);
                case 9:
                    return pooledInteger(36);
                case 10:
                    return pooledInteger(45);
                case 11:
                    return pooledInteger(37);
                case 12:
                    return pooledInteger(34);
                case 13:
                    return pooledInteger(33);
                case 14:
                    return pooledInteger(39);
                case 15:
                    return pooledInteger(16);
                case 16:
                    return pooledInteger(32);
                case 17:
                    return pooledInteger(9);
                case 18:
                    return pooledInteger(38);
                case 100:
                    if (!Va01337A7C) {
                        Va01337A7C = new Rva00899FC0((int)Va00CA5250);
                        Va01337A7C->flags = (Va01337A7C->flags & 0xffffc07f) | 0x40;
                        ((Rva008A7B00Slot *)Va01337A7C)->slot00();
                    }
                    return (Rva00899560Value *)Va01337A7C;
                case 0x65:
                    if (!Va01337A80) {
                        Va01337A80 = new Rva00899FC0((int)Va00CA52E0);
                        Va01337A80->flags = (Va01337A80->flags & 0xffffc07f) | 0x40;
                        ((Rva008A7B00Slot *)Va01337A80)->slot00();
                    }
                    return (Rva00899560Value *)Va01337A80;
                case 0x66:
                    if (!Va01337A84) {
                        Va01337A84 = new Rva00899FC0((int)Va00CA52F0);
                        Va01337A84->flags = (Va01337A84->flags & 0xffffc07f) | 0x40;
                        ((Rva008A7B00Slot *)Va01337A84)->slot00();
                    }
                    return (Rva00899560Value *)Va01337A84;
                case 0x67:
                    if (!Va01337A8C) {
                        Va01337A8C = new Rva00899FC0((int)Va00CA5360);
                        Va01337A8C->flags = (Va01337A8C->flags & 0xffffc07f) | 0x40;
                        ((Rva008A7B00Slot *)Va01337A8C)->slot00();
                    }
                    return (Rva00899560Value *)Va01337A8C;
                case 0x68:
                    if (!Va01337A90) {
                        Va01337A90 = new Rva00899FC0((int)Va00CA5380);
                        Va01337A90->flags = (Va01337A90->flags & 0xffffc07f) | 0x40;
                        ((Rva008A7B00Slot *)Va01337A90)->slot00();
                    }
                    return (Rva00899560Value *)Va01337A90;
                case 0x69:
                    if (!Va01337A94) {
                        Va01337A94 = new Rva00899FC0((int)Va00CA53D0);
                        Va01337A94->flags = (Va01337A94->flags & 0xffffc07f) | 0x40;
                        ((Rva008A7B00Slot *)Va01337A94)->slot00();
                    }
                    return (Rva00899560Value *)Va01337A94;
                case 0x6a:
                    if (!Va01337A98) {
                        Va01337A98 = new Rva00899FC0((int)Va00CA6CB0);
                        Va01337A98->flags = (Va01337A98->flags & 0xffffc07f) | 0x40;
                        ((Rva008A7B00Slot *)Va01337A98)->slot00();
                    }
                    return (Rva00899560Value *)Va01337A98;
                case 0x6b:
                    if (!Va01337A88) {
                        Va01337A88 = new Rva00899FC0((int)Va00CA5330);
                        Va01337A88->flags = (Va01337A88->flags & 0xffffc07f) | 0x40;
                        ((Rva008A7B00Slot *)Va01337A88)->slot00();
                    }
                    return (Rva00899560Value *)Va01337A88;
                }
            }
        }
    }
    return 0;
}
