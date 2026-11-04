// cl: /Iinputs/reference/shims/asciistring_downloadmanager /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "PreRTS.h"
#include "Common/AsciiString.h"

#include <map>

inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}

// Retail AsciiString::compare shape (repe cmpsb over the shared prefix, then
// the length difference), spelled as the StringBase<char> specialization so
// this TU emits no AsciiString::compare COMDAT of its own. Same spelling as
// game/GameEngine/Source/GameNetwork/Rva00692570KeyLess.cpp.
template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

namespace _STL {
template <> struct less<AsciiString> {
    bool operator()(const AsciiString &a, const AsciiString &b) const {
        return ((const StringBase<char> &)a).compare((const StringBase<char> &)b) < 0;
    }
};
}

struct Rva00080600Value { AsciiString m_key; };
struct Rva00080600KeyOfValue {
    const AsciiString &operator()(const Rva00080600Value &v) const { return v.m_key; }
};
typedef _STL::_Rb_tree<AsciiString, Rva00080600Value,
    Rva00080600KeyOfValue, _STL::less<AsciiString>,
    _STL::allocator<Rva00080600Value> > Rva00080600Tree;
static __forceinline void *rva00080600Lookup(const Rva00080600Tree *tree,
    const AsciiString &key) throw()
{
    return tree->find<AsciiString>(key)._M_node;
}

struct CustomMapNodeShim
{
	unsigned char m_unreconstructed_00[ 0x14 ];
	AsciiString m_value;
};

struct CustomPreferenceMapShim
{
	CustomMapNodeShim *m_header;
};

class GameLODManager
{
public:
	int getStaticGameLODIndex( AsciiString name );

	unsigned char m_unreconstructed_00[ 0x16c4 ];
	int m_fixedStaticGameDetail;
};

extern GameLODManager *TheGameLODManager;

class OptionPreferences
{
public:
	int getFixedStaticGameDetail( void );
};

int OptionPreferences::getFixedStaticGameDetail( void )
{
	CustomPreferenceMapShim *map;
	CustomMapNodeShim *node;
	{
		AsciiString key( "FixedStaticGameLOD" );
		map = (CustomPreferenceMapShim *)( (unsigned char *)this + 4 );
		node = (CustomMapNodeShim *)rva00080600Lookup((const Rva00080600Tree *)map, key);
	}

	if ( node == map->m_header )
	{
		if ( TheGameLODManager )
			return TheGameLODManager->m_fixedStaticGameDetail;
		return -1;
	}

	return TheGameLODManager->getStaticGameLODIndex( node->m_value );
}
