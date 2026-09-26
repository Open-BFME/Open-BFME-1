// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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
