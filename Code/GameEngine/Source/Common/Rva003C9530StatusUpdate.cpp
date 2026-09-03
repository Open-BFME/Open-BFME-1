// Address-derived status lookup/update reconstruction at 0x003C9530.

template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
    BitFlags()
    {
    }

    unsigned int m_bits[ ( Bits + 31 ) / 32 ];
};

typedef BitFlags<45> Rva003C9530Status;

struct BfmeObj923G;

extern BfmeObj923G *__stdcall bfmeFind923G( void *owner );

extern void d_003c9470();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    Rva003C9530Status getStatusBits() const;

public:
    char m_pad00[ 0x8C ];
    unsigned char m_flag;
};

#pragma comment(linker, "/alternatename:?getStatusBits@Object@@QBE?AV?$BitFlags@$0CN@@@@XZ=?j_00017dfa@@YAXXZ")

class Rva003C9530Key
{
};

class Rva003C9530Owner
{
public:
    bool updateStatus( Rva003C9530Key *key, Rva003C9530Status *status );
};

bool Rva003C9530Owner::updateStatus( Rva003C9530Key *key,
                                     Rva003C9530Status *status )
{
    Object *object = reinterpret_cast<Object *>( bfmeFind923G( key ) );
    if( object == 0 )
        return false;

    if( object->m_flag )
    {
        *status = object->getStatusBits();
        return true;
    }

    typedef bool (Rva003C9530Owner::*Fallback)( Rva003C9530Key *,
                                                Rva003C9530Status * );
    union
    {
        void (*plain)();
        Fallback member;
    } target;
    target.plain = d_003c9470;
    return (this->*target.member)( key, status );
}
