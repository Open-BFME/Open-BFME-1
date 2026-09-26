// Native 55-byte setter at RVA 0x0015FCB0..0x0015FCE7 (RET4).
// ObjectModelConditions.cpp independently witnesses the field at +0x110
// and its 40-byte width (ten-word copies, returned masks and table stride).
// The notify call resolves through ILT 0x0002191D to Object's 0x001BE1C0.
// The original method name is not independently established.
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/bfmekindof /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE

#include <vector>
#include "PreRTS.h"
#include "Common/BitFlags.h"

// BFME-specific inline behavior.  The shipped ZH BitFlags inline methods call
// checked std::bitset methods; retail has no range-check branch in these
// setters.  This TU-local specialization retains the native BitFlags storage
// and API while selecting the underlying unchecked STLport operations proven
// by retail's branch-free index calculation. No shared header is changed.
template<>
inline Bool BitFlags<320>::test( Int i ) const
{
	return m_bits._Unchecked_test( i );
}

template<>
inline void BitFlags<320>::set( Int i, Int val )
{
	m_bits._Unchecked_set( i, val );
}

typedef char Rva0015FCB0MaskSizeCheck[(sizeof(BitFlags<320>) == 40) ? 1 : -1];

class Object
{
public:
	void notifyModelConditionChanged();

protected:
	unsigned char m_beforeConditionFlags[ 0x110 ];
	BitFlags<320> m_modelConditionFlags;
};

class Rva0015FCB0Owner : public Object
{
public:
	void setCondition( UnsignedInt bit );
};

void Rva0015FCB0Owner::setCondition( UnsignedInt bit )
{
	if( !m_modelConditionFlags.test( bit ) )
	{
		m_modelConditionFlags.set( bit );
		notifyModelConditionChanged();
	}
}
