// ?rva0089EA60Append@Rva8CD130String@@QAEAAV1@PBD@Z
// partial score=0.4461 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc
extern "C" unsigned __cdecl strlen(const char *);
extern "C" void *__cdecl memcpy(void *, const void *, unsigned);
#pragma intrinsic(strlen)
#pragma intrinsic(memcpy)
struct BfmeStringData3AF0 { unsigned short m_refCount, m_length, m_capacity, m_unknown06; };
struct BfmeStringPool3AF0 { void *m_unused; void (__cdecl *free)(void *); };
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
class BfmeStrVKI { public: void bfmeSetVKI(const char *); BfmeStringData3AF0 *m_data; };
class Rva8CD130String;
class EAStringC
{
    enum CBPushZero { CB_NO_PUSH_ZERO, CB_PUSH_ZERO };
    void ChangeBuffer(unsigned, unsigned, unsigned, CBPushZero, unsigned);
    friend class Rva8CD130String;
};
template<class T> class StringBase
{
protected:
    BfmeStringData3AF0 *m_data;
    StringBase(const char *text) { ((BfmeStrVKI *)this)->bfmeSetVKI(text); }
    ~StringBase()
    {
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
    }
};
class Rva8CD130String : private StringBase<char>
{
public:
    Rva8CD130String(const char *text) : StringBase<char>(text) {}
    ~Rva8CD130String() {}
    Rva8CD130String &operator=(const Rva8CD130String &other)
    {
        ++other.m_data->m_refCount;
        BfmeStringData3AF0 *old = m_data;
        if (--old->m_refCount == 0) g_rva01337A30AllocPair->free(old);
        m_data = other.m_data;
        return *this;
    }
    Rva8CD130String &rva0089EA60Append(const char *text);
};

// Open BFME 2: Code/Libraries/Source/EA/Apt/AptString/EAStringCRefCount.cpp.
Rva8CD130String &Rva8CD130String::rva0089EA60Append(const char *text)
{
    unsigned oldSize = m_data->m_length;
    if (oldSize == 0)
    {
        Rva8CD130String tmp(text);
        operator=(tmp);
        return *this;
    }
    unsigned len = strlen(text);
    if (len == 0) return *this;
    unsigned newSize = oldSize + len;
    ((EAStringC *)this)->ChangeBuffer(newSize, 0, oldSize, EAStringC::CB_NO_PUSH_ZERO, newSize);
    memcpy((char *)m_data + sizeof(BfmeStringData3AF0) + oldSize, text, len + 1);
    return *this;
}
