// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// RVA 0x009CD370: public tree find wrapper around the matched 0x009C9B70
// _M_find specialization. The tree's public find call reaches that matched
// STLport helper. Several retail copies share these bytes, so the ledger
// identity keeps this address until a caller selects one copy.

#include <map>
#include "Common/AsciiString.h"

class ArchiveFile;

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

typedef _STL::_Rb_tree<AsciiString,
	_STL::pair<const AsciiString, ArchiveFile *>,
	_STL::_Select1st<_STL::pair<const AsciiString, ArchiveFile *> >,
	_STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, ArchiveFile *> > > ArchiveFileTree;

struct Rva009CD370Result
{
    void *m_node;
    explicit Rva009CD370Result(void *node) : m_node(node) {}
};

class Rva009CD370Owner
{
public:
    Rva009CD370Result find(const AsciiString &key) const;
};

Rva009CD370Result Rva009CD370Owner::find(const AsciiString &key) const
{
    return Rva009CD370Result(
        reinterpret_cast<const ArchiveFileTree *>(this)->find<AsciiString>(key)._M_node);
}
