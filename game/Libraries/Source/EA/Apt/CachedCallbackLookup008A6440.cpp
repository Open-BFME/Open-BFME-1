// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Complete 18-entry lazy callback dispatch at RVA 008A6440.
// Incoming ECX is unused; two stack arguments and RET 8.
struct R4Word { const char *name; int value; };
class AptValue;
const R4Word *Rva008A3DC0(const char *, unsigned);
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
class Rva008A4630Item {
public:
    virtual void unused0();
    virtual void release();
};
struct StringBuffer008A6440 { unsigned short refs, length; };
struct String008A6440 { StringBuffer008A6440 *data; };
extern Rva008A4630Item *g_rva008A4630_0;
AptValue *aptMathSin(void *, int);
extern Rva008A4630Item *g_rva008A4630_1;
AptValue *aptMathCos(void *, int);
extern Rva008A4630Item *g_rva008A4630_2;
AptValue *aptMathAtan2(void *, int);
extern Rva008A4630Item *g_rva008A4630_3;
AptValue *aptMathRound(void *, int);
extern Rva008A4630Item *g_rva008A4630_4;
AptValue *aptMax(void *, int);
extern Rva008A4630Item *g_rva008A4630_5;
AptValue *aptMin(void *, int);
extern Rva008A4630Item *g_rva008A4630_6;
AptValue *aptMathAbs(void *, int);
extern Rva008A4630Item *g_rva008A4630_7;
AptValue *aptMathAcos(void *, int);
extern Rva008A4630Item *g_rva008A4630_8;
AptValue *aptMathAsin(void *, int);
extern Rva008A4630Item *g_rva008A4630_9;
AptValue *aptMathAtan(void *, int);
extern Rva008A4630Item *g_rva008A4630_10;
AptValue *aptMathCeil(void *, int);
extern Rva008A4630Item *g_rva008A4630_11;
AptValue *aptMathExp(void *, int);
extern Rva008A4630Item *g_rva008A4630_12;
AptValue *aptMathFloor(void *, int);
extern Rva008A4630Item *g_rva008A4630_13;
AptValue *aptMathLog(void *, int);
extern Rva008A4630Item *g_rva008A4630_14;
AptValue *aptMathPow(void *, int);
extern Rva008A4630Item *g_rva008A4630_15;
AptValue *aptMathRandom(void *, int);
extern Rva008A4630Item *g_rva008A4630_16;
AptValue *aptMathSqrt(void *, int);
extern Rva008A4630Item *g_rva008A4630_17;
AptValue *aptMathTan(void *, int);

Rva008A4630Item *__stdcall CachedCallbackLookup008A6440(void *owner, const String008A6440 *key)
{
    if (!owner) return 0;
    const R4Word *word = Rva008A3DC0((const char *)key->data + 8, key->data->length);
    if (!word) return 0;
    switch (word->value) {
    case 1:
        if (!g_rva008A4630_0) {
            g_rva008A4630_0 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathSin);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_0;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_0->unused0();
        }
        return g_rva008A4630_0;
    case 2:
        if (!g_rva008A4630_1) {
            g_rva008A4630_1 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathCos);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_1;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_1->unused0();
        }
        return g_rva008A4630_1;
    case 3:
        if (!g_rva008A4630_2) {
            g_rva008A4630_2 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathAtan2);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_2;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_2->unused0();
        }
        return g_rva008A4630_2;
    case 4:
        if (!g_rva008A4630_3) {
            g_rva008A4630_3 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathRound);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_3;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_3->unused0();
        }
        return g_rva008A4630_3;
    case 5:
        if (!g_rva008A4630_4) {
            g_rva008A4630_4 = (Rva008A4630Item *)new Rva00899FC0((int)aptMax);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_4;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_4->unused0();
        }
        return g_rva008A4630_4;
    case 6:
        if (!g_rva008A4630_5) {
            g_rva008A4630_5 = (Rva008A4630Item *)new Rva00899FC0((int)aptMin);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_5;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_5->unused0();
        }
        return g_rva008A4630_5;
    case 7:
        if (!g_rva008A4630_6) {
            g_rva008A4630_6 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathAbs);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_6;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_6->unused0();
        }
        return g_rva008A4630_6;
    case 8:
        if (!g_rva008A4630_7) {
            g_rva008A4630_7 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathAcos);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_7;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_7->unused0();
        }
        return g_rva008A4630_7;
    case 9:
        if (!g_rva008A4630_8) {
            g_rva008A4630_8 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathAsin);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_8;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_8->unused0();
        }
        return g_rva008A4630_8;
    case 10:
        if (!g_rva008A4630_9) {
            g_rva008A4630_9 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathAtan);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_9;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_9->unused0();
        }
        return g_rva008A4630_9;
    case 11:
        if (!g_rva008A4630_10) {
            g_rva008A4630_10 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathCeil);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_10;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_10->unused0();
        }
        return g_rva008A4630_10;
    case 12:
        if (!g_rva008A4630_11) {
            g_rva008A4630_11 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathExp);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_11;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_11->unused0();
        }
        return g_rva008A4630_11;
    case 13:
        if (!g_rva008A4630_12) {
            g_rva008A4630_12 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathFloor);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_12;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_12->unused0();
        }
        return g_rva008A4630_12;
    case 14:
        if (!g_rva008A4630_13) {
            g_rva008A4630_13 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathLog);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_13;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_13->unused0();
        }
        return g_rva008A4630_13;
    case 15:
        if (!g_rva008A4630_14) {
            g_rva008A4630_14 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathPow);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_14;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_14->unused0();
        }
        return g_rva008A4630_14;
    case 16:
        if (!g_rva008A4630_15) {
            g_rva008A4630_15 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathRandom);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_15;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_15->unused0();
        }
        return g_rva008A4630_15;
    case 17:
        if (!g_rva008A4630_16) {
            g_rva008A4630_16 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathSqrt);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_16;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_16->unused0();
        }
        return g_rva008A4630_16;
    case 18:
        if (!g_rva008A4630_17) {
            g_rva008A4630_17 = (Rva008A4630Item *)new Rva00899FC0((int)aptMathTan);
            Rva00899FC0 *value = (Rva00899FC0 *)g_rva008A4630_17;
            value->flags = (value->flags & 0xffffc07f) | 0x40;
            g_rva008A4630_17->unused0();
        }
        return g_rva008A4630_17;
    default: return 0;
    }
}
