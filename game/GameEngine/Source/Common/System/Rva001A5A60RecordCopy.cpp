// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <memory>

// The original record spelling is unknown. Raw storage and offset names retain
// the copy widths at 0x001A5A60 without claiming unrecovered field types.
class Rva001A5A60Record
{
public:
    __declspec(noinline) Rva001A5A60Record(const Rva001A5A60Record &source);

private:
    int m_field00;
    int m_field04;
    int m_field08;
    int m_field0c;
    int m_field10;
    int m_field14;
    unsigned char m_field18;
    unsigned char m_uncopied19[3];
    int m_field1c;
    int m_field20;
    int m_field24;
    int m_field28;
    unsigned char m_field2c;
    unsigned char m_field2d;
    unsigned short m_field2e;
};

// The placement helper calls this body separately; preserve that call boundary.
Rva001A5A60Record::Rva001A5A60Record(const Rva001A5A60Record &source)
{
    m_field00 = source.m_field00;
    m_field04 = source.m_field04;
    m_field08 = source.m_field08;
    m_field0c = source.m_field0c;
    m_field10 = source.m_field10;
    m_field14 = source.m_field14;
    m_field18 = source.m_field18;
    m_field1c = source.m_field1c;
    m_field20 = source.m_field20;
    m_field24 = source.m_field24;
    m_field28 = source.m_field28;
    m_field2c = source.m_field2c;
    m_field2d = source.m_field2d;
    m_field2e = source.m_field2e;
}

// Caller 0x001A6E50 allocates count*48 fresh bytes before calling this helper
// through 0x0001BBAD, proving construction into uninitialized storage.
template void _STL::_Construct(Rva001A5A60Record *, const Rva001A5A60Record &);
