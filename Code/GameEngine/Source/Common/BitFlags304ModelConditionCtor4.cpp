// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: ModelConditionFlags' four-index constructor, retail 0x001C5DE0.
// ModelConditionFlags is BitFlags<304>: retail's condition-name table has 304
// entries, and W3DDisplay::gatherDebugStats terminates its condition loop at
// 0x130. StructureCollapseUpdate calls this overload for four collapse states.

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

	BitFlags( BogusInitType, Int idx1, Int idx2, Int idx3, Int idx4 );

private:
	_STL::bitset<NUMBITS> m_bits;
};

template <size_t NUMBITS>
BitFlags<NUMBITS>::BitFlags(
	BogusInitType, Int idx1, Int idx2, Int idx3, Int idx4 )
{
	m_bits._Unchecked_set( static_cast<size_t>( idx1 ) );
	m_bits._Unchecked_set( static_cast<size_t>( idx2 ) );
	m_bits._Unchecked_set( static_cast<size_t>( idx3 ) );
	m_bits._Unchecked_set( static_cast<size_t>( idx4 ) );
}

// ??0?$BitFlags@$0BDA@@@QAE@W4BogusInitType@0@HHHH@Z
template BitFlags<304>::BitFlags(
	BitFlags<304>::BogusInitType, Int, Int, Int, Int );
