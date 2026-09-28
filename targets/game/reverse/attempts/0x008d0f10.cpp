// ?d_008d0f10@@YAXXZ
// partial score=0.92 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008D0F10, opaque Apt action body shared by the 1212A/1214A/1216A entry
// points. It pops a member name, an object and an argument count, resolves the
// member (handling "super", Function "call"/"apply" and the "this" binding),
// invokes it through 0x008CF740 and special-cases Array "pop"/"shift". No
// proprietary identity claim; types follow Rva008D16A0StringDispatch.cpp.
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class BfmeStrVKI {
public:
    BfmeStrVKI(const char *text) { bfmeSetVKI(text); }
    void bfmeSetVKI(const char *text);
    __forceinline ~BfmeStrVKI() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130String {
public:
    __forceinline Rva8CD130String() { m_data = &g_bfmeDefaultString1284; ++m_data->m_refCount; }
    __forceinline ~Rva8CD130String() {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    __forceinline Rva8CD130String &operator=(const BfmeStrVKI &s) {
        ++s.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
        m_data = s.m_data;
        return *this;
    }
    __forceinline const char *text() const { return reinterpret_cast<const char *>(m_data) + 8; }
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value {
public:
    virtual void addRef();
    virtual void release();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual Rva8CD130Value *slot18();
    virtual int slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual int slot4c();
    unsigned m_flags;
    unsigned m_link;
    unsigned char m_unknown0C[0x0C];
    Rva8CD130Value *m_indirect;
    unsigned m_state1C;
    unsigned *m_items;
    int m_unknown24;
    int m_itemCount;
    unsigned char m_unknown2C[0x20];
    Rva8CD130Value *m_owner4C;
    void getName(Rva8CD130String *);
    int toInteger() const;
    int rva00899C20();
    __forceinline int type() const { return m_flags & 0x3f; }
    __forceinline bool undefined() const { return (~(unsigned(m_flags) >> 15) & 1) != 0; }
    __forceinline bool retained() const { return ((unsigned(m_flags) >> 30) & 1) != 0; }
    __forceinline unsigned kindBits() const { return reinterpret_cast<const unsigned short *>(this)[3] & 0xfff; }
};
class Rva00899770;
class Rva008AE770Stack {
public:
    Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int);
    void bfmePop1232(int);
    void invoke(Rva8CD130Value *, Rva8CD130Value *, int);
    int m_count;
    int m_unknown04;
    Rva8CD130Value **m_entries;
    unsigned char m_unknown0C[0x0C];
    int m_scopeCount;
    int m_unknown1C;
    Rva8CD130Value **m_scopes;
    unsigned char m_unknown24[0x0C];
    int m_frameCount;
    int m_unknown34;
    Rva8CD130Value **m_frames;
    __forceinline void pop() {
        Rva8CD130Value *old = m_entries[m_count - 1];
        if (!old->retained()) old->release();
        --m_count;
    }
};
struct Rva008D0F10Context {
    int m_unknown00;
    Rva8CD130Value *m_target;
    int m_unknown08;
    int m_unknown0C;
    Rva8CD130Value *m_global;
};
extern Rva8CD130Value *g_bfmeFallbackDB;
extern Rva8CD130Value *g_rva013379C0Value;
int bfmeCompareVSC(const char *, const char *);

void rva008D0F10InvokeNamedMember(Rva008AE770Stack *state, Rva008D0F10Context *context)
{
    Rva8CD130Value *top = state->m_entries[state->m_count - 1];
    Rva8CD130Value *countValue = state->m_entries[state->m_count - 3];
    Rva8CD130Value *object = state->m_entries[state->m_count - 2];
    Rva8CD130String name;
    bool scoped = false;
    Rva8CD130Value *result = 0;
    if (top == g_bfmeFallbackDB) {
        name = BfmeStrVKI("super");
        if (object->type() == 0x1c && !object->undefined()) result = object->m_indirect;
        else result = object;
    } else {
        top->getName(&name);
    }
    int count = countValue->toInteger();
    if (!object->undefined()) {
    Rva8CD130Value *target = context->m_target;
    state->m_frames[state->m_frameCount] = target;
    ++state->m_frameCount;
    target->addRef();
    state->pop();
    state->pop();
    state->pop();
    if (result == 0 || result == g_bfmeFallbackDB)
        result = reinterpret_cast<Rva8CD130Value *>(state->createString(object, 0,
            reinterpret_cast<BfmeStrVKI *>(&name), 1, 1, 0));
    if (result == 0 || result->undefined()) {
        if (bfmeCompareVSC(name.text(), "apply") == 0 || bfmeCompareVSC(name.text(), "call") == 0) {
            result = object;
            if ((countValue->type() == 7 && !countValue->undefined()) ||
                (countValue->type() == 6 && !countValue->undefined())) {
                if (count > 0) {
                    Rva8CD130Value *thisValue = state->m_entries[state->m_count - 1];
                    if (thisValue != 0 && !thisValue->undefined()) object = thisValue;
                    else object = g_bfmeFallbackDB;
                    state->pop();
                    --count;
                } else {
                    object = g_bfmeFallbackDB;
                }
            } else {
                object = countValue;
                count = state->m_entries[state->m_count - 1]->toInteger();
                if (count > 1) {
                    Rva8CD130Value *thisValue = state->m_entries[state->m_count - 2];
                    if (thisValue != 0 && !thisValue->undefined()) object = thisValue;
                    state->pop();
                    --count;
                }
                state->pop();
            }
            if (bfmeCompareVSC(name.text(), "apply") == 0) {
                Rva8CD130Value *array = state->m_entries[state->m_count - 1];
                if (array->type() == 0x16 && !array->undefined()) {
                    state->pop();
                    int index = array->m_itemCount - 1;
                    count += array->m_itemCount - 1;
                    for (; index >= 0; --index) {
                        Rva8CD130Value *item = reinterpret_cast<Rva8CD130Value *>(array->m_items[index] & ~1u);
                        state->m_entries[state->m_count++] = item;
                        if (!item->retained()) item->addRef();
                    }
                }
            }
        }
    }
    if (object->slot1c()) {
        Rva8CD130Value *scope = object;
        if (state->m_scopeCount == 0) {
            if (object == context->m_global) {
                BfmeStrVKI thisName("this");
                scope = reinterpret_cast<Rva8CD130Value *>(state->createString(context->m_target, 0,
                    &thisName, 1, 1, 0));
            }
        } else {
            Rva8CD130Value *current = state->m_scopes[state->m_scopeCount - 1];
            int kind = object->type();
            if (!(kind >= 0x0c && kind <= 0x13 && !object->undefined() && object->m_owner4C == current) &&
                object != current) {
                for (Rva8CD130Value *link = current->slot18(); link; link = link->slot18()) {
                    link = reinterpret_cast<Rva8CD130Value *>(link->m_link & ~1u);
                    if (!link) break;
                    if (link == object) goto bound;
                }
            }
        }
        scoped = true;
        if (scope->type() == 0x1b && !scope->undefined()) scope->m_state1C |= 0x200;
        state->m_scopes[state->m_scopeCount++] = scope;
        scope->addRef();
    }
bound:
    bool releaseObject = false;
    if (object->kindBits() == 1) {
        object->addRef();
        releaseObject = true;
    }
    if (object->rva00899C20()) {
        if (object == g_rva013379C0Value) object = state->m_frames[state->m_frameCount - 2];
        if (object == context->m_global && result->type() == 0x0a && !result->undefined()) {
            int saved = result->m_itemCount;
            if (result->slot4c() == 1) {
                result->m_itemCount = (int)context->m_target;
                state->invoke(object, result, count);
            } else {
                result->m_itemCount = (int)context->m_target;
                state->invoke(object, result, count);
            }
            result->m_itemCount = saved;
        } else {
            state->invoke(object, result, count);
        }
    } else {
        state->invoke(object, result, count);
    }
    if (scoped) {
        Rva8CD130Value *scope = state->m_scopes[state->m_scopeCount - 1];
        if (scope->type() == 0x1b && !scope->undefined()) scope->m_state1C &= ~0x200u;
        state->m_scopes[state->m_scopeCount - 1]->release();
        --state->m_scopeCount;
    }
    if (releaseObject) object->release();
    if (state->m_entries[state->m_count - 1] != g_bfmeFallbackDB && object->type() == 0x16 &&
        !object->undefined() &&
        (bfmeCompareVSC(name.text(), "pop") == 0 || bfmeCompareVSC(name.text(), "shift") == 0))
        state->m_entries[state->m_count - 1]->release();
    state->m_frames[state->m_frameCount - 1]->release();
    --state->m_frameCount;
    } else {
        state->bfmePop1232(count + 3);
        Rva8CD130Value *undefinedValue = g_bfmeFallbackDB;
        state->m_entries[state->m_count++] = undefinedValue;
        if (!undefinedValue->retained()) undefinedValue->addRef();
    }
}
