// Address-derived status lookup/update reconstruction at 0x003C9530.

template <int Bits>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
    BitFlags()
    {
    }

    unsigned int m_bits[ ( Bits + 31 ) / 32 ];
};

typedef BitFlags<45> Rva003C9530Status;

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class LivingWorldRegion;

class LivingWorldRegionManager
{
public:
    LivingWorldRegion *rva003C8A50( const AsciiString &regionName );
};

extern void d_003c9470();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    char m_pad00[ 0x8C ];
    unsigned char m_flag;
};

// Retail's getStatusBits call goes through the ILT thunk at 0x00017dfa, which
// expects the hidden struct-return slot ahead of `this` and returns that slot
// in eax; the local `bits` temp supplies the slot, exactly as the sret temp the
// direct struct-returning call would have allocated.
extern void j_00017dfa();

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
    Object *object = reinterpret_cast<Object *>(
        reinterpret_cast<LivingWorldRegionManager *>( this )->rva003C8A50(
            *reinterpret_cast<const AsciiString *>( key ) ) );
    if( object == 0 )
        return false;

    if( object->m_flag )
    {
        Rva003C9530Status bits;
        typedef Rva003C9530Status * ( Object::*StatusBits )( Rva003C9530Status * ) const;
        union
        {
            void (*plain)();
            StatusBits member;
        } target;
        target.plain = j_00017dfa;
        *status = *( object->*target.member )( &bits );
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
