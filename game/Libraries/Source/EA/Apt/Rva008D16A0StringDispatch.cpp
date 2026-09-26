// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008D16A0, opaque Apt dispatch-table body. No proprietary identity claim.
// Hub analysis proves the getName receivers and one-pointer mutable handles.
extern "C" unsigned __cdecl strlen(const char *);
extern "C" int __cdecl strncmp(const char *, const char *, unsigned);
#pragma intrinsic(strlen)
static __forceinline bool startsWith(const char *text, const char *prefix) {
    return strncmp(text,prefix,strlen(prefix))==0;
}
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unknown00; void (__cdecl *free)(void *); };
extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
class Rva8CD130String {
public:
    __forceinline Rva8CD130String() { m_data = &g_bfmeDefaultString1284; ++m_data->m_refCount; }
    __forceinline Rva8CD130String(const Rva8CD130String &s) { m_data=s.m_data; ++s.m_data->m_refCount; }
    __forceinline ~Rva8CD130String() {
        BfmeStringData3AF0 *old=m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
    }
    __forceinline Rva8CD130String &operator=(const Rva8CD130String &s) {
        ++s.m_data->m_refCount;
        BfmeStringData3AF0 *old=m_data;
        if (--old->m_refCount == 0) g_bfmeStringPool1284->free(old);
        m_data=s.m_data;
        return *this;
    }
    __forceinline const char *text() const { return reinterpret_cast<const char *>(m_data)+8; }
    void rva0089EEF0(unsigned, unsigned);
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value {
public:
    virtual void rva008D16A0Slot00();
    virtual void rva008D16A0Slot04();
    unsigned m_flags;
    Rva8CD130String m_string;
    unsigned char m_unknown0C[0x14];
    Rva8CD130Value *m_indirect;
    void getName(Rva8CD130String *);
    __forceinline bool undefined() const { return (~(unsigned(m_flags)>>15)&1)!=0; }
    __forceinline bool retained() const { return ((unsigned(m_flags)>>30)&1)!=0; }
};
class Rva00899770;
class BfmeStrVKI;
class Rva008AE770Stack {
public:
    Rva00899770 *createString(void *, int, BfmeStrVKI *, int, int, int);
    int m_count;
    int m_unknown04;
    Rva8CD130Value **m_entries;
};
class Rva008CF3C0String;
class Rva008CF3C0State { public: void parseAndAppend(void *, void *, Rva008CF3C0String *); };
class Rva00896AF0Tracker { public: void rva00896AF0(Rva8CD130String *, Rva8CD130String); };
extern void bfmeResetEVF(void *, BfmeStrVKI *);
struct Rva008D16A0Context { int m_unknown00; void *m_unknown04; int m_unknown08; };
extern const char *rva012D5A08Prefix;
extern void (__cdecl *rva01337858Callback)(const char *, const char *);
extern Rva00896AF0Tracker *g_bfmeTracker4310;
static __forceinline void dispatchCommand(const Rva8CD130String &name, const char *value) {
    const char *command=name.text()+strlen(rva012D5A08Prefix);
    rva01337858Callback(command,value);
}

void rva008D16A0Dispatch(Rva008AE770Stack *state, Rva008D16A0Context *context) {
    Rva8CD130Value *top=state->m_entries[state->m_count-1];
    Rva8CD130Value *under=state->m_entries[state->m_count-2];
    Rva8CD130String value;
    Rva8CD130String name;
    under->getName(&name);
    if (startsWith(name.text(),rva012D5A08Prefix)) {
        top->getName(&value);
        dispatchCommand(name,value.text());
    } else {
        int length=name.m_data->m_length;
        Rva8CD130String shortened;
        const unsigned block=(unsigned)name.m_data;
        // Retail +100/+10C reuse the LAST character for uppercase W/S.
        // Preserve that observed check, including its reads before the text
        // for nonempty strings shorter than four characters.
        if (!length || ((*(const char *)(length+block+7)=='f' || *(const char *)(length+block+7)=='F') &&
            (*(const char *)(length+block+6)=='w' || *(const char *)(length+block+7)=='W') &&
            (*(const char *)(length+block+5)=='s' || *(const char *)(length+block+7)=='S') && *(const char *)(length+block+4)=='.')) {
            top->getName(&value);
            shortened=name;
            if (shortened.m_data->m_length>=4) shortened.rva0089EEF0(shortened.m_data->m_length-4,4);
            Rva8CD130Value *resolved=reinterpret_cast<Rva8CD130Value *>(state->createString(
                context->m_unknown04,context->m_unknown08,reinterpret_cast<BfmeStrVKI *>(&value),1,1,0));
            int type=resolved->m_flags&0x3f;
            if (type>=12 && type<=19 && !resolved->undefined()) bfmeResetEVF(resolved,reinterpret_cast<BfmeStrVKI *>(&value));
            for (int index=1;index<=2;++index) {
                Rva8CD130Value *old=state->m_entries[state->m_count-index];
                if (!old->retained()) old->rva008D16A0Slot04();
            }
            state->m_count-=2;
            g_bfmeTracker4310->rva00896AF0(&shortened,value);
            return;
        } else {
            Rva8CD130Value *resolved;
            int type=top->m_flags&0x3f;
            if ((type==1 || type==42) && !top->undefined()) {
                Rva8CD130Value *source=top;
                if (type!=1) source=source->m_indirect;
                resolved=reinterpret_cast<Rva8CD130Value *>(state->createString(context->m_unknown04,
                    context->m_unknown08,reinterpret_cast<BfmeStrVKI *>(&source->m_string),1,1,0));
            } else resolved=top;
            reinterpret_cast<Rva008CF3C0State *>(state)->parseAndAppend(resolved,
                reinterpret_cast<void *>(context->m_unknown08),reinterpret_cast<Rva008CF3C0String *>(&name));
        }
    }
    for (int index=1;index<=2;++index) {
        Rva8CD130Value *old=state->m_entries[state->m_count-index];
        if (!old->retained()) old->rva008D16A0Slot04();
    }
    state->m_count-=2;
}
