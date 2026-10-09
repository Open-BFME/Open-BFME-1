// ?stackNumber008C9650@@YAXPAUStack008C9650@@PAX@Z
// partial score=0.536 date=2026-10-09
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
struct BfmeStringData3AF0 {
    unsigned short m_refCount, m_length, m_capacity, m_flags;
};
struct BfmeStringPool3AF0 {
    void *m_unused;
    void (__cdecl *free)(void *);
};
class EAStringC { public: class StringDataC; };
extern EAStringC::StringDataC g_rva012D5298Empty;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

class Rva8CD130String {
public:
    Rva8CD130String() : m_data((BfmeStringData3AF0 *)&g_rva012D5298Empty) { ++m_data->m_refCount; }
    __forceinline ~Rva8CD130String() { BfmeStringData3AF0 *old=m_data; if (--old->m_refCount==0) g_bfmeStringPool1284->free(old); }
    int find0089FF80(const char *, int);
    int length() const { return m_data->m_length; }
    const char *text() const { return (const char *)m_data+8; }
    BfmeStringData3AF0 *m_data;
};
class Rva8CD130Value { public: void getName(Rva8CD130String *); };
class AptValue {
public:
    virtual void retain();
    virtual void release();
    unsigned m_flags;
    float toNumber();
    int toInteger() const;
    bool undefined() const { return ((unsigned char)~(m_flags>>15)&1)!=0; }
    unsigned type() const { return m_flags&63; }
    bool isFloat() const { return type()==6 && !undefined(); }
    bool isInteger() const { return type()==7 && !undefined(); }
    bool isString() const { return (type()==1 || type()==42) && !undefined(); }
    bool pooled() const { return ((m_flags>>30)&1)!=0; }
};
extern AptValue *g_bfmeFallbackDB;
extern unsigned int AptGetSwfVersion();
extern "C" long __cdecl strtol(const char *, char **, int);
extern "C" int __cdecl isdigit(int);
class Rva00899560Value;
struct Rva00899560Pool {
    int m_capacity, m_count;
    Rva00899560Value **m_items;
    template<class V> __forceinline void addPooled(V *v) {
        int &count=m_count;
        if(count>=m_capacity) {v->m_flags &= 0xBFFFFFFF;return;}
        m_items[count]=v;
        ++count;
    }
};
extern Rva00899560Pool *g_rva01337810GcRoots;
class Rva00899560Value {
public:
    virtual void retain();
    virtual void release();
    unsigned int m_flags;
    __forceinline Rva00899560Value(int type) {
        unsigned int flags = (((m_flags & ~0x3f) | type) & 0xF000803F) | 0x8000;
        m_flags = flags;
        if (type != 0x1c && type != 0xa) {
            m_flags = flags | 0x40000000;
            g_rva01337810GcRoots->addPooled(this);
        } else {
            m_flags = flags & 0xBFFFFFFF;
        }
    }
};
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

class Rva008A4C00Value : public Rva00899560Value {
public:
    static void *operator new(unsigned int bytes) { return Rva008C5D70Alloc(bytes); }
    __forceinline Rva008A4C00Value(float value) : Rva00899560Value(6), m_value(value) {}
    union { Rva008A4C00Value *m_next; float m_value; };
};

class Rva008D29A0;
extern Rva008D29A0 *g_rva008D29A0;

struct Rva008A1110Value : Rva00899560Value {
    union { int m_value; Rva008A1110Value *m_next; };
    static void *operator new(unsigned bytes) { return Rva008C5D70Alloc(bytes); }
    __forceinline Rva008A1110Value(int value) : Rva00899560Value(7), m_value(value) {}
};
class Rva008D2A10;
extern Rva008D2A10 *g_rva008D2A10;
static __forceinline AptValue *makeInteger(int value) {
    Rva008A1110Value *obj=(Rva008A1110Value *)g_rva008D2A10;
    if(obj) { g_rva008D2A10=(Rva008D2A10 *)obj->m_next; g_rva01337810GcRoots->addPooled(obj); obj->m_value=value; return (AptValue *)obj; }
    return (AptValue *)new Rva008A1110Value(value);
}
static __forceinline AptValue *makeFloat(float value) {
    Rva008A4C00Value *obj=(Rva008A4C00Value *)g_rva008D29A0;
    if(obj) { g_rva008D29A0=(Rva008D29A0 *)obj->m_next; g_rva01337810GcRoots->addPooled(obj); obj->m_value=value; return (AptValue *)obj; }
    return (AptValue *)new Rva008A4C00Value(value);
}
struct Stack008C9650 {
    int m_count, m_capacity;
    AptValue **m_values;
    __forceinline void pop(int n) { for(int i=1;i<=n;++i) { AptValue *v=m_values[m_count-i]; if(!v->pooled()) v->release(); } m_count-=n; }
    __forceinline void push(AptValue *v) { m_values[m_count++]=v; if(!v->pooled()) v->retain(); }
};
static __forceinline bool numeric008C9650(AptValue *value, AptValue *volatile &preserved) {
    if(value->isInteger() || value->isFloat()) return true;
    if(value->isString()) {
        Rva8CD130String text;
        ((Rva8CD130Value *)preserved)->getName(&text);
        if(!text.length()) return false;
        if(text.text()[0]=='0' && text.length()>2 && text.text()[1]=='x') {
            char *end;
            strtol(text.text(),&end,16);
            if(!*end) return true;
        }
        char c=text.text()[text.length()-1];
        bool dot=false;
        if(c!='-' && c!='+' && c!='e' && c!='.' && !isdigit(c)) return false;
        c=text.text()[0];
        if(c!='.' && c!='-' && c!='+' && !isdigit(c)) return false;
        for(int i=1;i<text.length();++i) {
            c=text.text()[i];
            if(c=='.' && !dot) dot=true;
            else if(c=='e' && i!=1) {
                if(i==2 && (text.text()[0]=='+' || text.text()[0]=='-')) return false;
                if(i+1<text.length()) {
                    c=text.text()[i+1];
                    if(c!='-' && c!='+' && !isdigit(c)) return false;
                    ++i;
                }
            } else if(!isdigit(c)) return false;
        }
        return true;
    }
    if(value->undefined() || value->type()==3) { if(AptGetSwfVersion()==7) return false; return true; }
    return false;
}
void stackNumber008C9650(Stack008C9650 *state, void *context) {
    AptValue *value=state->m_values[state->m_count-1];
    AptValue *volatile preserved=value;
    if(value->isFloat() || value->isInteger()) return;
    AptValue *volatile result=g_bfmeFallbackDB;
    if(numeric008C9650(value,preserved)) {
        int mode=AptGetSwfVersion();
        value=preserved;
        if(mode==7 && value->undefined()) {
            state->pop(1); state->push(result); return;
        }
        Rva8CD130String text;
        ((Rva8CD130Value *)value)->getName(&text);
        if(text.find0089FF80(".",0)!=-1) result=makeFloat(value->toNumber());
        else result=makeInteger(preserved->toInteger());
    }
    state->pop(1); state->push(result);
}
