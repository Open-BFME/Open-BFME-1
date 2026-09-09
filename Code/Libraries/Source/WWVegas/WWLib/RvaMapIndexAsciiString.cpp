// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: STLport map<AsciiString, V>::operator[] -- six bodies of 169
// bytes that carried only a machine byte-dump row.
//
// The shape is STLport's own: lower_bound, then a comparison against the
// candidate to decide whether the key is already there, and on a miss a
// value_type built from the key and a value-initialised mapped type, handed to
// the hinted insert.  The SEH prologue and the call to StringBase<char>'s
// destructor on the way out are that temporary's.
//
// Neither tree needs guessing.  Each body calls a _M_lower_bound and a hinted
// insert_unique that are already converted elsewhere in the repo, and the
// insert_unique names the value_type outright -- pair<const AsciiString, V>
// with a four-byte V, which agrees with the mapped reference this body returns
// at node+0x14.  The mapped types keep the names those conversions gave them.
//
// The two callees were spelled by different hands: the insert_unique rows carry
// the map spelling used here, while the _M_lower_bound rows spell the same tree
// through a key-of-value functor.  Only one spelling can be in one file, so the
// insert_unique resolves by name and each _M_lower_bound gets a pin at the ILT
// thunk this body reaches.

#include "PreRTS.h"
#include "Common/AsciiString.h"
#include <map>

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

enum Rva0033F960Mapped { Rva0033F960MappedZero = 0 };

typedef _STL::map<AsciiString, Rva0033F960Mapped, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva0033F960Mapped> > > Rva0033F960Map;

// retail 0x00347820, over the tree whose _M_lower_bound is at 0x0033F2E0
template Rva0033F960Mapped &Rva0033F960Map::operator[]( const AsciiString & );
enum Rva003B9B40Mapped { Rva003B9B40MappedZero = 0 };

typedef _STL::map<AsciiString, Rva003B9B40Mapped, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva003B9B40Mapped> > > Rva003B9B40Map;

// retail 0x003BAEF0, over the tree whose _M_lower_bound is at 0x003B9A10
template Rva003B9B40Mapped &Rva003B9B40Map::operator[]( const AsciiString & );
enum Rva00448C60Mapped { Rva00448C60MappedZero = 0 };

typedef _STL::map<AsciiString, Rva00448C60Mapped, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00448C60Mapped> > > Rva00448C60Map;

// retail 0x0044A860, over the tree whose _M_lower_bound is at 0x00448AD0
template Rva00448C60Mapped &Rva00448C60Map::operator[]( const AsciiString & );
// This one's mapped type is a single byte -- retail stores the
// default-constructed value with `mov BYTE PTR [esp+0x10], al` where its five
// siblings store a dword -- so it is one byte wide and not a four-byte
// enumeration.  Retain the existing char ABI for this byte-valued map;
// its historical char-versus-bool identity is not established here.
// The separate pointer-valued ArchiveFileMap is at retail 0x00063960.
typedef _STL::map<AsciiString, char, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, char> > > Rva0033F870Map;

// retail 0x004545A0, over the tree whose _M_lower_bound is at 0x00452E60
template char &Rva0033F870Map::operator[]( const AsciiString & );
enum Rva00461630Mapped { Rva00461630MappedZero = 0 };

typedef _STL::map<AsciiString, Rva00461630Mapped, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00461630Mapped> > > Rva00461630Map;

// retail 0x00463D50, over the tree whose _M_lower_bound is at 0x00460F80
template Rva00461630Mapped &Rva00461630Map::operator[]( const AsciiString & );
enum Rva00475300Mapped { Rva00475300MappedZero = 0 };

typedef _STL::map<AsciiString, Rva00475300Mapped, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00475300Mapped> > > Rva00475300Map;

// retail 0x00476F70, over the tree whose _M_lower_bound is at 0x00474CD0
template Rva00475300Mapped &Rva00475300Map::operator[]( const AsciiString & );
