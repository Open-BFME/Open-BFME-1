// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Retail 0x006B0850 (414 bytes): transfers an AsciiString -> float map.
// Identity: the body's only string literals are "std::map" (0x0111C360, the
// xferTypeName argument) and "Map must be empty on load" (0x0111C340); its one
// caller is Rva006ABC60::xfer (0x006B0CB0) through ILT 0x000149D4. It is one
// of a family of STL-container xfer helpers whose source name is unrecovered,
// so the name keeps the address token. The sibling set transfer at 0x006AC930
// is xferTree.cpp. The load path indexes the map through its operator[] at
// 0x006AF6D0 (ILT 0x0000D9D1), matched in RvaMapAsciiStringQuad006AF6D0.cpp,
// whose comparator stays opaque.

#include <stl/_config.h>
#undef _STLP_DEFAULT_CONSTRUCTOR_BUG
#include "Common/AsciiString.h"
#include <map>

// Retail inlines ~AsciiString: temporaries are released by a direct call to
// StringBase<char>::releaseBuffer (0x00887940), not the ??1AsciiString stub.
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

#include "../../../Include/Common/ScalarTypes.h"




namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()( const AsciiString &left, const AsciiString &right ) const
	{
		return left.compare( right ) < 0;
	}
};
}

struct Rva006AF6D0Less : _STL::less<AsciiString>
{
};

typedef _STL::map<AsciiString, Real, Rva006AF6D0Less,
	_STL::allocator<_STL::pair<const AsciiString, Real> > > Rva006AF6D0Map;

// Built by a constructor: retail frames the version record below the count,
// which VC7.1 does for a constructed record but not for a plain aggregate
// whose two bytes are assigned one by one.
struct XferVersion
{
	XferVersion(UnsignedByte current) : m_version(current), m_currentVersion(current) {}
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual Xfer &xferAsciiString(AsciiString *value);
	virtual Xfer &xferReal(Real *value);
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tag;
};

// ?Rva006B0850XferAsciiStringRealMap@@YAPAVXfer@@PAV1@PAX@Z
Xfer *Rva006B0850XferAsciiStringRealMap(Xfer *xfer, void *rawMap)
{
	Rva006AF6D0Map *map = (Rva006AF6D0Map *)rawMap;
	XferVersion version(1);
	xfer->xferVersion(&version);

	UnsignedInt count = map->size();
	xfer->xferTypeName("std::map").xferUnsignedInt(&count);

	if (xfer->isSaving())
	{
		Rva006AF6D0Map::iterator end = map->end();
		for (Rva006AF6D0Map::iterator it = map->begin(); it != end; ++it)
		{
			_STL::pair<AsciiString, Real> entry = *it;
			xfer->xferAsciiString(&entry.first).xferReal(&entry.second);
		}
	}
	else
	{
		if (!map->empty())
		{
			throw XferException(4, "Map must be empty on load");
		}

		_STL::pair<AsciiString, Real> entry;
		while (count--)
		{
			xfer->xferAsciiString(&entry.first).xferReal(&entry.second);
			(*map)[entry.first] = entry.second;
		}
	}
	return xfer;
}
