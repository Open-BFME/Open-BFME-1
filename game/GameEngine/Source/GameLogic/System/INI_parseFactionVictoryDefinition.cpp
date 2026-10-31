// cl: /DNDEBUG /MD /EHsc /Ob1 /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// iniParseFactionVictoryDefinition, retail RVA 0x000C31B0, 363 bytes (plain
// ret). INI block table 0x012A88AC binds the FactionVictoryData block to its
// ILT 0x00011FAE, and the body's own assert text names it ("Could not
// find/create FactionVictoryParameters in iniParseFactionVictoryDefinition!").
// It is the sibling of iniParseVictorySystemDefinition (0x000C3060,
// INI_parseVictorySystemDefinition.cpp): the block name "neutral" maps to the
// empty name, then the named FactionVictoryParameters is found or created and
// parsed with the FactionVictoryData field table at VA 0x0109FBC8.

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *instance, const FieldParse *fieldParse);
};

class VictorySystem;
extern VictorySystem *TheVictorySystem;
struct FactionVictoryParameters;
class VictorySystem
{
public:
	FactionVictoryParameters *_bfme_findOrCreateFactionVictoryParameters(const AsciiString &name);
};
extern const FieldParse g_0109FBC8[]; // FactionVictoryData field-parse table

class Debug
{
public:
	class Format
	{
	public:
		explicit Format(const char *format, ...);
		operator const char *() const { return m_buffer; }

	private:
		char m_buffer[512];
	};
};

class BFMEIndexBufferDebugStream
{
public:
	virtual BFMEIndexBufferDebugStream *Put_Unsigned(unsigned value);
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual void Put_String(const char *text);
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual BFMEIndexBufferDebugStream *Finish(int report);
};

struct Rva00889690Obj
{
public:
	virtual void Slot00();
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual void Slot38();
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual void Slot4C();
	virtual void Slot50();
	virtual void Slot54();
	virtual void Slot58();
	virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64();
	virtual void Slot68();
	virtual BFMEIndexBufferDebugStream *Get_Stream(void *owner, void *context);
};

// Retail 0x01336E5C is ?g_Rva00F36E5C@@3PAXA (data_rows.csv,
// debug/Rva00F36E5C.cpp); g_rva00889690 was only a pin.
extern void *g_Rva00F36E5C;
#define g_rva00889690 ( *(Rva00889690Obj **)&g_Rva00F36E5C )
extern void _bfme_debugRecordCallsite(int kind);

// ?iniParseFactionVictoryDefinition@@YAXPAVINI@@@Z
void __cdecl iniParseFactionVictoryDefinition(INI *ini)
{
	AsciiString name;
	const char *token = ini->getNextToken();
	name.StringBase<char>::set(token, token ? (int)strlen(token) : 0);

	if (name.compareNoCase("neutral") == 0)
		// StringBase spelling: the AsciiString::clear forwarder would be emitted as
		// a COMDAT; the inlined StringBase<char>::clear calls releaseBuffer.
		name.StringBase<char>::clear();

	if (TheVictorySystem == 0)
	{
		_bfme_debugRecordCallsite(1);
		g_rva00889690->Begin_Report();
		const char *text = name.str();
		BFMEIndexBufferDebugStream *stream =
			g_rva00889690->Get_Stream(0, 0);
		stream->Put_String(Debug::Format("TheVictorySystem has not been initialized!.\n", text));
		stream->Finish(1);
	}
	else
	{
		FactionVictoryParameters *params = TheVictorySystem->_bfme_findOrCreateFactionVictoryParameters(name);
		if (params)
		{
			ini->initFromINI(params, g_0109FBC8);
		}
		else
		{
			_bfme_debugRecordCallsite(1);
			g_rva00889690->Begin_Report();
			const char *text = name.str();
			BFMEIndexBufferDebugStream *stream =
				g_rva00889690->Get_Stream(0, 0);
			stream->Put_String(Debug::Format("Could not find/create FactionVictoryParameters in iniParseFactionVictoryDefinition!.\n", text));
			stream->Finish(1);
		}
	}
}
