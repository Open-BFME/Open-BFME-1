// ?d_00283df0@@YAXXZ
// partial score=0.3 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Oi /Ireference/shims/iniexception /Ireference/shims/stringinline
template <typename T> class StringBase
{
public:
    StringBase() : m_data(0) {}
    ~StringBase();
    void set(const T *text, int length);
    void releaseBuffer();
protected:
    void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text);
    AsciiString(const AsciiString &other);
    ~AsciiString() {}
    AsciiString &operator=(const char *text);
    void set(const char *text, int length)
    {
        ((StringBase<char> *)this)->set(text, length);
    }
    void releaseBuffer()
    {
        ((StringBase<char> *)this)->releaseBuffer();
    }
};

class RetailLayoutString
{
public:
    void set(const char *text, int length);
};

class BFMERetailAsciiString
{
public:
    void releaseBuffer();
};

class Rva002E7E00Owner
{
public:
    Rva002E7E00Owner()
    {
        m_fields[0] = 0;
        m_fields[1] = 0;
        m_fields[2] = 0;
        m_fields[3] = 0;
        m_fields[4] = 0;
        m_fields[5] = 0;
        m_fields[6] = 0;
        m_fields[7] = 0;
        m_fields[8] = 0;
        m_fields[9] = 0;
    }
    void parse(AsciiString text);
private:
    unsigned int m_fields[10];
};

class Rva00283DF0Entry
{
public:
    Rva00283DF0Entry();
    AsciiString m_unitType;
    unsigned int m_field04;
    Rva002E7E00Owner m_modelState;
    AsciiString m_locomotor;
};

Rva00283DF0Entry::Rva00283DF0Entry()
    : m_unitType(), m_modelState(), m_locomotor()
{
    m_locomotor.set("", 0);
    m_field04 = 0;
    m_unitType.releaseBuffer();
}
