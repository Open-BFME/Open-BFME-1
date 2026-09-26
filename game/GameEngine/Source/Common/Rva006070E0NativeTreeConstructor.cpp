// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Native STLport tree construction for the anonymous 0x006070E0 body.

#include <map>
#include <new>
#include <string.h>

struct Rva006070E0Value
{
    char m_body[ 0x70 ];
};

typedef _STL::pair<const int, Rva006070E0Value> Rva006070E0Pair;
typedef _STL::_Rb_tree<int, Rva006070E0Pair,
    _STL::_Select1st<Rva006070E0Pair>, _STL::less<int>,
    _STL::allocator<Rva006070E0Pair> > Rva006070E0Tree;

struct Rva006070E0Item
{
    virtual void release( bool now );
};

struct Rva006070E0Prefix
{
    int m_pod[ 10 ];
    Rva006070E0Item *m_values[ 0x6d ];

    Rva006070E0Prefix()
    {
        memset( m_pod, 0, sizeof( m_pod ) );

        for ( int i = 0; i < 0x6d; ++i )
            m_values[ i ] = 0;
    }

    ~Rva006070E0Prefix()
    {
        for ( int i = 0; i < 0x6d; ++i )
        {
            Rva006070E0Item *item = m_values[ i ];
            if ( item != 0 )
            {
                item->release( true );
                m_values[ i ] = 0;
            }
        }
    }
};

struct Rva006070E0Owner
{
    Rva006070E0Prefix m_prefix;
    Rva006070E0Tree m_tree;
    int m_field1e8;
    unsigned char m_field1ec;
    char m_padding1ed[ 3 ];

    Rva006070E0Owner();
    ~Rva006070E0Owner() {}
};

Rva006070E0Owner::Rva006070E0Owner()
    : m_prefix(), m_tree()
{
    m_field1e8 = 0;
    m_field1ec = 0;
}
