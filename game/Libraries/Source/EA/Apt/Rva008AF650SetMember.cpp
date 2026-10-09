// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008AF650: cdecl member store for text fields (type 15) and display objects; returns bool.
// Keys come from the perfect hashes at 008ABF40 and 008D48F0; owner names stay address-derived.
#include <string.h>

struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);
extern void (__cdecl *TheBfmeFree)(void *, unsigned int);

class BfmeStrVKI {
public:
    __forceinline BfmeStrVKI() : m_data(&g_bfmeDefaultString1284) { ++g_bfmeDefaultString1284.m_refCount; }
    __forceinline ~BfmeStrVKI() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    }
    __forceinline BfmeStrVKI &operator=(const BfmeStrVKI &source) {
        ++source.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
        m_data = source.m_data;
        return *this;
    }
    __forceinline bool operator==(const BfmeStrVKI &other) const {
        unsigned length = m_data->m_length;
        return length == other.m_data->m_length &&
            (m_data == other.m_data || memcmp(text(), other.text(), length) == 0);
    }
    __forceinline const char *text() const { return (const char *)m_data + 8; }
    BfmeStringData3AF0 *m_data;
};
class BfmeStrVKK { public: void bfmeTruncVKK(unsigned int length); };

struct R4Word { const char *m_name; int m_value; };
const R4Word *Rva008ABF40(const char *text, unsigned int length);
const R4Word *Rva008D48F0(const char *text, unsigned int length);
extern void ji_009f6fa0();
typedef int (__cdecl *Rva008AF650Compare)(const char *, const char *);

class Rva8CD130String;
class Rva8CD130Value {
public:
    void getName(Rva8CD130String *output);
    __forceinline bool undefined() const { return (~(m_flags >> 15) & 1) != 0; }
    __forceinline bool isType(unsigned type) const { return (m_flags & 0x3f) == type && !undefined(); }
    void *m_unknown00;
    unsigned m_flags;
    char m_gap08[8];
    float m_unknown10;
    char m_gap14[8];
    float m_unknown1c;
    char m_gap20[0x2c];
    Rva8CD130Value *m_unknown4c;
};
class AptValue {
public:
    int toInteger() const;
    float toNumber();
};

class Rva008A9B00 {
public:
    Rva008A9B00();
    static void *operator new(unsigned bytes) { return Rva008C5D70Alloc(bytes); }
    __forceinline static void operator delete(void *memory, unsigned bytes) {
        TheBfmeFree(memory, bytes);
    }
    void *m_unknown00;
    unsigned m_flags;
    BfmeStrVKI m_string;
    Rva008A9B00 *m_next;
};
struct Rva008C3B60Node;
extern Rva008C3B60Node *Rva008C3B60Head;
struct Rva00899560Pool {
    int m_capacity, m_count;
    void **m_items;
    __forceinline void add(Rva008A9B00 *node) {
        int index = m_count;
        int *count = &m_count;
        if (index >= m_capacity) node->m_flags &= 0xbfffffff;
        else { m_items[index] = node; ++*count; }
    }
};
extern Rva00899560Pool *g_rva01337810GcRoots;
struct Rva008AE770Stack;
extern Rva008AE770Stack Rva008AE770TheStack;
class Rva008CF3C0State {
public:
    void append(void *owner, void *scope, BfmeStrVKI *name, Rva008A9B00 *node, int a, int b, int c);
};

struct Rva008AF650TextSource { char m_gap00[0x2c]; int m_unknown2c; int m_unknown30; };
class Rva008AD530StringBinding {
public:
    void resolve(Rva8CD130Value *scope);
    __forceinline void markDirty(unsigned bits) { m_flags6c = (m_flags6c & ~1u) | bits; }
    char m_gap00[0x0c];
    Rva008AF650TextSource *m_unknown0c;
    char m_gap10[8];
    BfmeStrVKI m_string18;
    BfmeStrVKI m_string1c;
    char m_gap20[4];
    int m_color24;
    int m_limit28;
    int m_count2c;
    int m_color30;
    int m_color34;
    int m_align38;
    char m_gap3c[0x14];
    float m_base50;
    float m_base54;
    float m_value58;
    float m_value5c;
    char m_gap60[0x0c];
    unsigned m_flags6c;
    char m_gap70[4];
    unsigned m_bit0 : 1;
    unsigned m_bit1 : 1;
    unsigned m_bit2 : 1;
    unsigned m_bit3 : 1;
};

struct Rva8BB1A0Bounds { float left, top, right, bottom; };
class BfmeB1236 { public: void bfmeApply1236(void *a); };
class BfmeN1235 { public: void bfmeInitEmpty1235(Rva8BB1A0Bounds *bounds); };
class BfmeSlotState1289 { public: void bfmeSetAxis1289(int axis, float value, int enabled); };
class BfmeRef008A4B20;
class BfmePtrTable64_008A4B20 { public: void add(BfmeRef008A4B20 *); };
class Rva008A4BD0 { public: unsigned char has(int); };
class Rva008ACFC0RegisteredObject;
class Rva008ACFC0PointerRegistry { public: void add(Rva008ACFC0RegisteredObject *); };
extern char *Rva008A5380Holder;

class Rva008AF650Object : public Rva8CD130Value {
public:
    Rva008AD530StringBinding *m_binding50;
};

bool rva008AF650Implementation(Rva008AF650Object *object, BfmeStrVKI *key, AptValue *value)
{
    if (object->isType(15)) {
        const R4Word *word = Rva008ABF40(key->text(), key->m_data->m_length);
        if (word) {
            Rva008AD530StringBinding *text = object->m_binding50;
            switch (word->m_value) {
            case 1: {
                BfmeStrVKI name;
                ((Rva8CD130Value *)value)->getName((Rva8CD130String *)&name);
                if (text->m_align38 == 3 && (strcmp(name.text(), "false") || strcmp(name.text(), "none")))
                    text->m_flags6c |= 8;
                else
                    text->m_flags6c |= 0x10;
                if (!strcmp(name.text(), "left") || !strcmp(name.text(), "true"))
                    text->m_align38 = 0;
                else if (!strcmp(name.text(), "center"))
                    text->m_align38 = 2;
                else if (!strcmp(name.text(), "right"))
                    text->m_align38 = 1;
                else if (!strcmp(name.text(), "false") || !strcmp(name.text(), "none"))
                    text->m_align38 = 3;
                text->markDirty(4);
                return true;
            }
            case 2:
                text->m_bit2 = value->toInteger();
                text->markDirty(0x20);
                return true;
            case 3:
                text->m_color30 = value->toInteger() | 0xff000000;
                text->markDirty(0x40);
                return true;
            case 4:
                text->m_bit1 = value->toInteger();
                text->markDirty(0x80);
                return true;
            case 5:
                text->m_color34 = value->toInteger() | 0xff000000;
                text->markDirty(0x100);
                return true;
            case 6:
            case 8:
            case 16:
                return true;
            case 10:
                text->m_unknown0c->m_unknown2c = value->toInteger();
                break;
            case 11: {
                int count = value->toInteger();
                int old = text->m_count2c;
                if (text->m_flags6c & 4)
                    ((BfmeB1236 *)object)->bfmeApply1236(object->m_unknown4c);
                text->m_count2c = count;
                if (count > text->m_limit28)
                    text->m_count2c = text->m_limit28;
                if (text->m_count2c < 1)
                    text->m_count2c = 1;
                if (old != text->m_count2c)
                    text->m_flags6c = 0x204;
                break;
            }
            case 12: {
                BfmeStrVKI name;
                ((Rva8CD130Value *)value)->getName((Rva8CD130String *)&name);
                if (!(text->m_string18 == name)) {
                    text->m_string18 = name;
                    if (text->m_string1c.m_data != &g_bfmeDefaultString1284) {
                        Rva8CD130Value *scope = object;
                        while (scope) {
                            if (scope->isType(13) || scope->isType(18)) break;
                            if (!scope->m_unknown4c) break;
                            scope = scope->m_unknown4c;
                        }
                        Rva008A9B00 *node = (Rva008A9B00 *)Rva008C3B60Head;
                        if (node) {
                            Rva008C3B60Head = (Rva008C3B60Node *)node->m_next;
                            g_rva01337810GcRoots->add(node);
                            if (node->m_string.m_data != &g_bfmeDefaultString1284)
                                ((BfmeStrVKK *)&node->m_string)->bfmeTruncVKK(0);
                        } else {
                            node = new Rva008A9B00();
                        }
                        node->m_string = name;
                        ((Rva008CF3C0State *)&Rva008AE770TheStack)->append(scope, 0, &text->m_string1c, node, 1, 1, 0);
                    }
                    text->m_flags6c = 0x204;
                }
                return true;
            }
            case 13:
                text->m_color24 = value->toInteger() | 0xff000000;
                text->markDirty(0x400);
                return true;
            case 17: {
                BfmeStrVKI name;
                ((Rva8CD130Value *)value)->getName((Rva8CD130String *)&name);
                if (!(text->m_string1c == name)) {
                    text->m_string1c = name;
                    text->resolve(object);
                    text->markDirty(0x204);
                }
                return true;
            }
            case 18:
                text->m_unknown0c->m_unknown30 = value->toInteger();
                text->markDirty(0x1004);
                return true;
            case 19: {
                float number = value->toNumber();
                if (number < 0.0f) return true;
                text->m_value5c = number + text->m_base54;
                text->markDirty(0x2004);
                return true;
            }
            case 20: {
                float number = value->toNumber();
                if (number < 0.0f) return true;
                text->m_value58 = number + text->m_base50;
                text->markDirty(0x4004);
                return true;
            }
            case 21: {
                int enabled = value->toInteger();
                text->m_bit3 = enabled;
                if (enabled == 1) {
                    Rva008A4BD0 *members = (Rva008A4BD0 *)(Rva008A5380Holder + 0x924);
                    if (!members->has((int)object)) {
                        ((BfmePtrTable64_008A4B20 *)members)->add((BfmeRef008A4B20 *)object);
                        ((Rva008ACFC0PointerRegistry *)(Rva008A5380Holder + 0xa28))->add((Rva008ACFC0RegisteredObject *)object);
                    }
                }
                break;
            }
            }
        }
    }

    if (!object->isType(13) && !object->isType(18) && !object->isType(14) && !object->isType(15))
        return false;
    const R4Word *word = Rva008D48F0(key->text(), key->m_data->m_length);
    if (word) {
        BfmeSlotState1289 *slots = (BfmeSlotState1289 *)object;
        switch (word->m_value) {
        case 1: {
            if (((Rva8CD130Value *)value)->undefined()) return false;
            float number = value->toNumber();
            slots->bfmeSetAxis1289(0, number, 1);
            break;
        }
        case 2: {
            if (((Rva8CD130Value *)value)->undefined()) return false;
            float number = value->toNumber();
            slots->bfmeSetAxis1289(1, number, 1);
            return true;
        }
        case 11: {
            float rotation = value->toNumber();
            if (rotation > 180.0f) rotation -= 360.0f;
            slots->bfmeSetAxis1289(6, rotation, 1);
            return true;
        }
        case 7: {
            float number = value->toNumber();
            slots->bfmeSetAxis1289(7, number, 1);
            return true;
        }
        case 3: {
            float number = value->toNumber();
            slots->bfmeSetAxis1289(2, number, 1);
            return true;
        }
        case 4: {
            float number = value->toNumber();
            slots->bfmeSetAxis1289(3, number, 1);
            return true;
        }
        case 8: {
            float number = value->toNumber();
            slots->bfmeSetAxis1289(11, number, 0);
            return true;
        }
        case 9: {
            float size = value->toNumber();
            if (size < 0.0f) return true;
            if (size == 0.0f) size = 0.0001f;
            Rva8BB1A0Bounds bounds;
            ((BfmeN1235 *)object)->bfmeInitEmpty1235(&bounds);
            float extent = bounds.right - bounds.left;
            if (extent == 0.0f) return true;
            float scale = size / extent;
            if (scale < 0.0001f) scale = 0.0001f;
            slots->bfmeSetAxis1289(2, scale * object->m_unknown10 * 100.0f, 1);
            return true;
        }
        case 10: {
            float size = value->toNumber();
            if (size < 0.0f) return true;
            if (size == 0.0f) size = 0.0001f;
            Rva8BB1A0Bounds bounds;
            ((BfmeN1235 *)object)->bfmeInitEmpty1235(&bounds);
            float extent = bounds.bottom - bounds.top;
            if (extent == 0.0f) return true;
            float scale = size / extent;
            if (scale < 0.0001f) scale = 0.0001f;
            slots->bfmeSetAxis1289(3, scale * object->m_unknown1c * 100.0f, 1);
            return true;
        }
        default:
            return false;
        }
        return true;
    } else {
        ((Rva008AF650Compare)ji_009f6fa0)(key->text(), "this"); // retail discards the result
    }
    return false;
}
