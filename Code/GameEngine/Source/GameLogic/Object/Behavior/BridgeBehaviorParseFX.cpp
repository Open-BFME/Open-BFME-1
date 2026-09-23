// ?parseFX@BridgeBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
// Retail 0x001F5500: BridgeDieFX FieldParse row at VA 0x010A28D0
// in table 0x010A28B0; its ILT 0x0002FE32 jumps to this body.
// Native STLport list preserves retail exception-frame restoration order.
// ?parseOCL@BridgeBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
// Retail 0x001F5620: the BridgeDieOCL row at VA 0x010A28E0 of the same table,
// ILT 0x000416B9; ZH's sibling parser, reading "OCL" and an ObjectCreationList.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/asciistring_outofline /Ireference/shims/iniexception /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad

// stlport
#include "Common/AsciiString.h"
#include "Common/INIException.h"

extern "C" __declspec( dllimport ) int __cdecl stricmp( const char *, const char * );

typedef unsigned int UnsignedInt;

class INI
{
public:
	const char *getNextToken( const char *seps );
	const char *getNextTokenOrNull( const char *seps );
	__forceinline const char *getSepsColon() const
	{
		return *(const char **)((const char *)this + 0x41C);
	}
	AsciiString getNextAsciiString();
	static void parseDurationUnsignedInt( INI *, void *, void *, const void * );
	static void parseFXList( INI *, void *, void *, const void * );
	static void parseObjectCreationList( INI *, void *, void *, const void * );
};

class FXList;
class ObjectCreationList;

struct TimeAndLocationInfo
{
	UnsignedInt delay;
	AsciiString boneName;
};

class BridgeBehaviorModuleData
{
public:
	static void parseFX( INI *, void *, void *, const void * );
	static void parseOCL( INI *, void *, void *, const void * );
};

struct BridgeFXInfo
{
    const FXList *fx;
    TimeAndLocationInfo timeAndLocationInfo;
};
struct BridgeOCLInfo
{
    const ObjectCreationList *ocl;
    TimeAndLocationInfo timeAndLocationInfo;
};

#include <list>

namespace _STL
{
// Retail calls this instantiation out of line through ILT 0x00007C84.
// Body 0x001F32A0 checks destination, copies the first eight bytes, then
// constructs the narrow string at +8 via 0x00887B60. Keep that boundary.
template <> void _Construct<BridgeFXInfo, BridgeFXInfo>(BridgeFXInfo *, const BridgeFXInfo &);
// The BridgeOCLInfo instantiation is the same out-of-line body at 0x001F3310,
// ILT 0x00028696.
template <> void _Construct<BridgeOCLInfo, BridgeOCLInfo>(BridgeOCLInfo *, const BridgeOCLInfo &);
}

struct BoneNameSlot
{
	AsciiString *destination;

	__forceinline BoneNameSlot( AsciiString *value ) : destination( value ) {}

	__forceinline void operator=( const AsciiString &value )
	{
		destination->operator=( value );
	}
};

static void parseTimeAndLocationInfo( INI *ini, void *instance, TimeAndLocationInfo *info )
{
	const char *token = ini->getNextToken( ini->getSepsColon() );
	if( stricmp( token, "Delay" ) != 0 )
		throw INIException( 3, "Expected 'Delay' token, found '%s'\n", token );
	ini->parseDurationUnsignedInt( ini, instance, &info->delay, 0 );
	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if( token != 0 )
	{
		if( stricmp( token, "Bone" ) != 0 )
			throw INIException( 3, "Expected 'Bone' token, found '%s'\n", token );
		BoneNameSlot( &info->boneName ) = ini->getNextAsciiString();
	}
}

void BridgeBehaviorModuleData::parseFX( INI *ini, void *instance, void *store, const void * )
{
	BridgeFXInfo item;
	const char *token;
	item.fx = 0;
	_STL::list<BridgeFXInfo, _STL::allocator<BridgeFXInfo> > *bridgeFXList =
		(_STL::list<BridgeFXInfo, _STL::allocator<BridgeFXInfo> > *)store;

	const char *sepsColon = *(const char **)((const char *)ini + 0x41C);
	token = ini->getNextToken( sepsColon );
	if( stricmp( token, "FX" ) != 0 )
		throw INIException( 3, "Expected 'FX' token, found '%s'\n", token );

	FXList *fx;
	INI::parseFXList( ini, instance, &fx, 0 );
	item.fx = fx;
	parseTimeAndLocationInfo( ini, instance, &item.timeAndLocationInfo );
	bridgeFXList->push_back( item );
}
void BridgeBehaviorModuleData::parseOCL( INI *ini, void *instance, void *store, const void * )
{
	BridgeOCLInfo item;
	const char *token;
	item.ocl = 0;
	_STL::list<BridgeOCLInfo, _STL::allocator<BridgeOCLInfo> > *bridgeOCLList =
		(_STL::list<BridgeOCLInfo, _STL::allocator<BridgeOCLInfo> > *)store;
	const char *sepsColon = *(const char **)((const char *)ini + 0x41C);
	token = ini->getNextToken( sepsColon );
	if( stricmp( token, "OCL" ) != 0 )
		throw INIException( 3, "Expected 'OCL' token, found '%s'\n", token );
	ObjectCreationList *ocl;
	INI::parseObjectCreationList( ini, instance, &ocl, 0 );
	item.ocl = ocl;
	parseTimeAndLocationInfo( ini, instance, &item.timeAndLocationInfo );
	bridgeOCLList->push_back( item );
}
