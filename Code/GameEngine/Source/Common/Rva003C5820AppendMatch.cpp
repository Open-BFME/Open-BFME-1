// Address-derived reconstruction of the STLport vector append at 0x003C5820.
// The owning vector is at this+0 and the destination vector is at output+4.
// stlport

#define _M_insert_overflow j_000100d7
#include <vector>
#undef _M_insert_overflow

class Rva003C5890Item
{
};

typedef Rva003C5890Item Rva003C5820Item;

class Rva003C5820Key
{
};

class Rva003C5820Output
{
private:
    char m_pad00[ 4 ];

public:
    _STL::vector<Rva003C5820Item *> m_items;
    void append( Rva003C5820Item *item );
};

class Rva003C5820Owner
{
public:
    void appendMatch( Rva003C5820Output *output, Rva003C5820Key *key );

private:
    _STL::vector<Rva003C5820Item *> m_items;
};

extern void d_003c5270();

void Rva003C5820Owner::appendMatch( Rva003C5820Output *output,
                                    Rva003C5820Key *key )
{
    typedef int (__stdcall *FindFunction)( Rva003C5820Owner *,
                                           Rva003C5820Key * );
    int index = reinterpret_cast<FindFunction>( d_003c5270 )( this, key );
    if( index != -1 )
    {
        Rva003C5820Item *item = m_items[ index ];
        output->m_items.push_back( item );
    }
}
