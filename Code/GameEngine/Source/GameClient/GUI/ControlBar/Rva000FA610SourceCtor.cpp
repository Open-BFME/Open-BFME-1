// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 0x000FA4A0 constructs the portrait record from a source object.
// The adjacent default constructor and getPortrait body identify the record
// layout. The source object's semantic type remains unknown.

#include <string.h>

void j_00016fae();
#pragma comment(linker, "/alternatename:?initialize@Rva00016FAE@@QAEXXZ=?j_00016fae@@YAXXZ")

template <typename T> struct StringInlineData;

template <typename T> class StringBase
{
    friend class AsciiString;
private:
    StringBase() : m_data( 0 ) {}
    StringBase( const T *text );
    StringBase( const StringBase<T> &other );
    ~StringBase();
    StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
    ~AsciiString() {}
};

class Rva00016FAE
{
public:
    __declspec(noinline) void initialize();
};

__declspec(noinline) void Rva00016FAE::initialize()
{
    j_00016fae();
}

class ZeroPrefix
{
public:
    ZeroPrefix() : image( 0 ), value08( 0 ) {}
    void *image;
    int value08;
};

class OneBlock
{
public:
    OneBlock() : value0c( 1 ), value10( 1 ) {}
    int value0c;
    int value10;
};

class ZeroBlock
{
public:
    int values[6];
};

class Rva000FA610
{
public:
    Rva000FA610( const unsigned char *source, int unused );

private:
    AsciiString m_name;
    ZeroPrefix m_prefix;
    OneBlock m_one;
    ZeroBlock m_zero;
    int m_value2c;
    int m_value30;
    int m_value34;
    unsigned char m_flag;
    int m_value3c;
    int m_value40;
    Rva00016FAE m_value44;
};

Rva000FA610::Rva000FA610( const unsigned char *source, int unused )
    : m_name( *(const AsciiString *)(source + 0x20) ), m_prefix(), m_one()
{
    memset( &m_zero, 0, sizeof( m_zero ) );
    m_value2c = *(const unsigned short *)(source + 0x47a);
    m_value30 = -1;
    m_value34 = (int)*(const float *)(source + 0x3bc);
    m_flag = 0;
    m_value3c = 0;
    m_value40 = -1;
    m_value44.initialize();
}
