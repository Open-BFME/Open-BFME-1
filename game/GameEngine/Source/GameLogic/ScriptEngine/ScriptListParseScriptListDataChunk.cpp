// ?ParseScriptListDataChunk@ScriptList@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x0035BE10 (321 B). Reached as the "ScriptList" parser callback
// registered by ScriptList::ParseScriptsDataChunk (landed,
// ScriptList_ParseScriptsDataChunk_Thunk.cpp, 0x0035BFB0), matching the ZH
// twin inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/
// GameLogic/ScriptEngine/Scripts.cpp ScriptList::ParseScriptListDataChunk:
// bounds-check the read-info slot count, allocate a ScriptList, register
// nested "ScriptGroup"/"Script" parsers, then recurse into file.parse().
// BFME wraps each nested registerParser call in an RAII scope-registration
// object (Rva00352AB0ParserRegistration = "ScriptGroup", landed
// ScriptGroupParserRegistrationConstructor.cpp; Rva00350F50ParserRegistration
// = "Script", landed Rva00350F50ParserRegistrationCtor.cpp) instead of ZH's
// bare calls, and the overflow guard reports through the shared
// TheBfmeAwakenDebug object (0x01336E5C) instead of DEBUG_ASSERTCRASH; the
// retail message string at 0x010E8CBC reads "Reading too many script
// lists.  Max is " (verified against the image), confirming identity.
// DataChunkInfo's first member is AsciiString label (matches the ZH header),
// so `info` doubles as the AsciiString* label pointer the registration
// constructors expect.

#include "AsciiString.h"

typedef int Int;
typedef bool Bool;

class DataChunkInput;

struct DataChunkInfo
{
	AsciiString label;
	AsciiString parentLabel;
	int version;
	int dataSize;
};

typedef bool (__cdecl *BfmeParserCallback)( DataChunkInput &, DataChunkInfo *, void * );

class DataChunkInput
{
public:
	bool parse( void *userData );
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual BfmeAwakenLog *slot34( int );
	virtual BfmeAwakenLog *slot38( const char * );
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C( int );
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C( int, int );
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
bool __cdecl _bfme_debugReportingEnabled();
void __cdecl _bfme_debugRecordCallsite( int );

class ScriptList
{
public:
	ScriptList() throw();

	static bool __cdecl ParseScriptListDataChunk( DataChunkInput &file, DataChunkInfo *info, void *userData );

private:
	char m_pad[0x4c];
};

class BfmeInnerCN
{
public:
	void bfmeCloseCN( void *value );
};

class BfmeParserRegistrationVE
{
public:
	~BfmeParserRegistrationVE()
	{
		m_vftable = (void *)0x0107C7D0;
		((BfmeInnerCN *)m_table)->bfmeCloseCN( m_parser );
	}
protected:
	void *m_vftable;
	DataChunkInput *m_table;
	void *m_parser;
};

class Rva00350F50ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva00350F50ParserRegistration( void *dataContext, void *localList, DataChunkInput *table, AsciiString *labelOverride );
private:
	void *m_0c;
	void *m_10;
};

class Rva00352AB0ParserRegistration : public BfmeParserRegistrationVE
{
public:
	Rva00352AB0ParserRegistration( void *dataContext, void *localList, DataChunkInput *table, AsciiString *labelOverride );
private:
	void *m_0c;
	void *m_10;
};

struct ScriptListReadInfo
{
	int numLists;
	ScriptList *readLists[32];
};

bool __cdecl ScriptList::ParseScriptListDataChunk( DataChunkInput &file, DataChunkInfo *info, void *userData )
{
	ScriptListReadInfo *pInfo = (ScriptListReadInfo *)userData;

	if( !(pInfo->numLists < 0x20) )
	{
		if( _bfme_debugReportingEnabled() )
		{
			_bfme_debugRecordCallsite( 1 );
			TheBfmeAwakenDebug->slot60();
			TheBfmeAwakenDebug->slot6C( 0, 0 )->slot38( "Reading too many script lists.  Max is " )->slot34( 0x20 )->slot4C( 2 );
		}
		return false;
	}

	ScriptList *newList = new ScriptList();
	pInfo->readLists[pInfo->numLists++] = newList;

	Rva00352AB0ParserRegistration groupReg( newList, newList ? (void *)( (char *)newList + 4 ) : 0, &file, (AsciiString *)info );
	Rva00350F50ParserRegistration scriptReg( newList, newList ? (void *)( (char *)newList + 4 ) : 0, &file, (AsciiString *)info );
	return file.parse( 0 );
}
