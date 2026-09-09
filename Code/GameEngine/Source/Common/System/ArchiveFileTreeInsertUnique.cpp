// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Existing 310-byte unhinted insertion at retail RVA 0x00063230.
// Corrected to the ArchiveFile pointer-map type proven by its callers.
// The retail layout macro preserves the same-node begin insertion case.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"
#include "Common/AsciiString.h"

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) < 0;
	}
};
}

class ArchiveFile;
typedef _STL::pair<const AsciiString, ArchiveFile *> Rva00063230ArchivePair;

typedef _STL::_Rb_tree<AsciiString, Rva00063230ArchivePair,
	_STL::_Select1st<Rva00063230ArchivePair>,
	_STL::less<AsciiString>, _STL::allocator<Rva00063230ArchivePair> >
	Rva00063230ArchiveTree;

// retail 0x00063230, inserting through the _M_insert at 0x00063140
template _STL::pair<Rva00063230ArchiveTree::iterator, bool>
Rva00063230ArchiveTree::insert_unique( const Rva00063230ArchivePair & );
