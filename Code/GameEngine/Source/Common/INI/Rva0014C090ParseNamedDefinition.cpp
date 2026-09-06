// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Open-BFME7: INI block parser at 0x0014C090 (174 B): reads the block name
// into an AsciiString then allocates the 16-byte Gen0014AE40 definition (its
// constructor takes the name by value: the copy is built straight into the
// argument slot) fills it through INI::initFromINI with the field table at
// VA 0x0109596C and hands it to the owning store (the instance argument)
// through the add routine at 0x0014BE10.  Names are address-derived.

#include "PreRTS.h"
#include "Common/INI.h"

class Gen0014AE40
{
public:
	Gen0014AE40( AsciiString name );
	virtual ~Gen0014AE40();

private:
	char m_unreconstructed[ 12 ];
};

extern const FieldParse Rva0014C090FieldParseTable[];

class Rva0014C090Store
{
public:
	void add( Gen0014AE40 *definition );
};

class Rva0014C090
{
public:
	static void parseDefinition( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseDefinition@Rva0014C090@@SAXPAVINI@@PAX1PBX@Z
void Rva0014C090::parseDefinition( INI *ini, void *instance, void *, const void * )
{
	AsciiString name = ini->getNextToken();
	Gen0014AE40 *definition = new Gen0014AE40( name );
	ini->initFromINI( definition, Rva0014C090FieldParseTable );
	((Rva0014C090Store *)instance)->add( definition );
}
