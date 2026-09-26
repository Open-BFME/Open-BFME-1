// cl: /DNDEBUG /MD /EHsc
// stlport
// The two AsciiString-vector field parsers, 0x002638B0 and 0x00264330.
//
// They are the same 149-byte body twice: read one token as an AsciiString and
// push it onto the vector the store argument points at. The two source files
// were byte-identical apart from the class name, which is the only thing that
// distinguishes them -- and that name is load-bearing, not decorative, because
// it is half of each pinned symbol (?parse@Rva002638B0AsciiStringVectorParse@@
// and ?parse@Rva00264330AsciiStringVectorParse@@). So both classes survive the
// merge; what does not survive is the second copy of the seventy-line string
// model they shared.
//
// Open2Elem063700 is the vector's element type rather than AsciiString itself:
// it has the same single-pointer layout and forwards to the same StringBase
// copy and release, but keeps its own name so the vector instantiation and its
// inlined copy match retail.

#include <vector>

template <typename T>
class StringBase
{
    friend class AsciiString;
    friend class Open2Elem063700;

public:
    void set(const StringBase<T> &source);

private:
    StringBase(const StringBase<T> &source);
    void releaseBuffer();
    void *m_data;
};

class AsciiString
{
public:
    AsciiString() : m_text(0) {}

    AsciiString(const AsciiString &source)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&source);
    }

    ~AsciiString()
    {
        ((StringBase<char> *)this)->releaseBuffer();
    }

    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
        return *this;
    }

private:
    void *m_text;
};

class Open2Elem063700
{
public:
    Open2Elem063700(const Open2Elem063700 &source)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&source);
    }

    ~Open2Elem063700()
    {
        ((StringBase<char> *)this)->releaseBuffer();
    }

private:
    void *m_text;
};

class INI
{
public:
    AsciiString getNextAsciiString();
};

class Rva002638B0AsciiStringVectorParse
{
public:
    static void parse(INI *ini, void *instance, void *store,
        const void *userData);
};

void Rva002638B0AsciiStringVectorParse::parse(
    INI *ini, void *, void *store, const void *)
{
    AsciiString value = ini->getNextAsciiString();
    ((std::vector<Open2Elem063700> *)store)->push_back(
        *(Open2Elem063700 *)&value);
}

class Rva00264330AsciiStringVectorParse
{
public:
    static void parse(INI *ini, void *instance, void *store,
        const void *userData);
};

void Rva00264330AsciiStringVectorParse::parse(
    INI *ini, void *, void *store, const void *)
{
    AsciiString value = ini->getNextAsciiString();
    ((std::vector<Open2Elem063700> *)store)->push_back(
        *(Open2Elem063700 *)&value);
}
