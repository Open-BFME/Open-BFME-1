// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: BitFlags<192>'s one-index constructor, retail 0x001C5450.
// The canonical implementation is declared in Common/BitFlags.h.  BFME's
// retail STLport emits the unchecked bit operation; the vendored header's
// current set() adds a bounds/throw path, so this faithful standalone
// instantiation uses STLport's equivalent _Unchecked_set entry point.

#include <bitset>

typedef int Int;

template <size_t NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags( BogusInitType, Int idx1 );

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
BitFlags<NUMBITS>::BitFlags( BogusInitType, Int idx1 )
{
	m_bits._Unchecked_set( static_cast<size_t>( idx1 ) );
}

// ??0?$BitFlags@$0MA@@@QAE@W4BogusInitType@0@H@Z
template BitFlags<192>::BitFlags( BitFlags<192>::BogusInitType, Int );
