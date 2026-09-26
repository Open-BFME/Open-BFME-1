// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// FontLibrary's name table is the map at this+0x10.  Its key is the retail
// four-byte AsciiString view and its value is the one-dword reference slot
// returned by parseFontDefaultSettings.
#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include "PreRTS.h"
#include "Common/AsciiString.h"
#define _STLP_NO_EXCEPTIONS 1
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

class Rva00476440Object
{
public:
	void Release_Ref();
};

class Rva00476440Ref
{
public:
	Rva00476440Ref() : m_value(0) {}
	Rva00476440Ref(const Rva00476440Ref &other) : m_value(other.m_value) {}
	~Rva00476440Ref()
	{
		if (m_value != 0)
			m_value->Release_Ref();
	}
	Rva00476440Object *m_value;
};

typedef _STL::map<AsciiString, Rva00476440Ref,
	_STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00476440Ref> > >
	FontLibraryNameMap;

// ??A?$map@VAsciiString@@VRva00476440Ref@@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@VRva00476440Ref@@@_STL@@@4@@_STL@@QAEAAVRva00476440Ref@@ABVAsciiString@@@Z
template Rva00476440Ref &FontLibraryNameMap::operator[](
	const AsciiString &key);
