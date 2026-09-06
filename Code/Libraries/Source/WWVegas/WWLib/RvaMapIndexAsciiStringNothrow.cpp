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

// Open-BFME7: retail 0x0054FA30 (169 bytes) is one more map<AsciiString, enum>::operator[]
// as built in a TU with the array/scalar delete declared nothrow (docs/shape_levers.md):
// the model of RvaMapIndexAsciiString.cpp with that declaration and its own mapped tag.
void __cdecl operator delete[](void *) throw();
void __cdecl operator delete(void *) throw();
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

enum Rva0054FA30Mapped { Rva0054FA30MappedZero = 0 };

typedef _STL::map<AsciiString, Rva0054FA30Mapped, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva0054FA30Mapped> > > Rva0054FA30Map;

// retail 0x0054FA30
template Rva0054FA30Mapped &Rva0054FA30Map::operator[]( const AsciiString & );
