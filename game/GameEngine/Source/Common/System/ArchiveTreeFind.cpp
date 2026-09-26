// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

#include "PreRTS.h"
#include "Common/AsciiString.h"

class ArchivedDirectoryInfo {};
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
	_STL::pair<const AsciiString, ArchivedDirectoryInfo>,
	_STL::_Select1st<_STL::pair<const AsciiString, ArchivedDirectoryInfo> >,
	_STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, ArchivedDirectoryInfo> > > ArchivedDirectoryTree;

typedef _STL::_Rb_tree<AsciiString,
	_STL::pair<const AsciiString, ArchiveFile *>,
	_STL::_Select1st<_STL::pair<const AsciiString, ArchiveFile *> >,
	_STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, ArchiveFile *> > > ArchiveFileTree;

template _STL::_Rb_tree_node<_STL::pair<const AsciiString, ArchivedDirectoryInfo> > *
ArchivedDirectoryTree::_M_find<AsciiString>(const AsciiString &) const;

template _STL::_Rb_tree_node<_STL::pair<const AsciiString, ArchiveFile *> > *
ArchiveFileTree::_M_find<AsciiString>(const AsciiString &) const;
