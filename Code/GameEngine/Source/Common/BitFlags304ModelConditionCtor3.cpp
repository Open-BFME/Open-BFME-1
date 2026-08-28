// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: ModelConditionFlags' three-index constructor, retail 0x001C5D40.
// ModelConditionFlags is BitFlags<304>: retail's condition-name table has 304
// entries, and W3DDisplay::gatherDebugStats terminates its condition loop at
// 0x130.  DozerActionDoActionState calls this overload for the three
// construction states at indices 0x42..0x44.

#include <bitset>

typedef int Int;

template <size_t NUMBITS>
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags( BogusInitType, Int idx1, Int idx2, Int idx3 );

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
BitFlags<NUMBITS>::BitFlags( BogusInitType, Int idx1, Int idx2, Int idx3 )
{
	m_bits._Unchecked_set( static_cast<size_t>( idx1 ) );
	m_bits._Unchecked_set( static_cast<size_t>( idx2 ) );
	m_bits._Unchecked_set( static_cast<size_t>( idx3 ) );
}

// ??0?$BitFlags@$0BDA@@@QAE@W4BogusInitType@0@HHH@Z
template BitFlags<304>::BitFlags( BitFlags<304>::BogusInitType, Int, Int, Int );
