// cl: /DNDEBUG /MD /EHsc /Ob1 /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// The INI block registry pairs the block name 'WaterTextureList' with this
// body.  BFME keeps that registry as a linked list of 12-byte rows whose head
// is the global at VA 0x0130CE50, and the row at 0x012A87A8 holds the name
// string and this parser.
//
// The body reads the table of six named texture lists through the global at
// 0x012ED648, asks it for the entry the block names, and fills that entry from
// the one-row FieldParse table at 0x0108132C, whose only field is "Texture" at
// offset 8.  The lookup and the dump call are both already converted, as
// Rva000AF530Table::find and Rva000C2A30Owner::dump.
//
// The assert arm is the same five calls INI_parseVictorySystemDefinition.cpp
// carries: record the callsite, open a report, take a stream, put the formatted
// text, finish.

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)



#include "ascii_string.h"

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *instance, const FieldParse *fieldParse);

	static void parseWaterTextureListDefinition(INI *ini);
};

class Rva000C2A30Owner
{
public:
	void dump();
};

class Rva000AF530Table
{
public:
	Rva000C2A30Owner *find(const AsciiString &name);
};

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
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
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
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern void *g_Rva00F36E5C; // VA 01336E5C debug manager cell (data_rows.csv owner)
#define TheBfmeAwakenDebug (static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C))
Rva000AF530Table *g_Va012ED648 = 0;
extern const FieldParse g_0108132C[];
extern void _bfme_debugRecordCallsite(int kind);

void INI::parseWaterTextureListDefinition(INI *ini)
{
	AsciiString name;
	const char *token = ini->getNextToken();
	name.StringBase<char>::set(token, token ? (int)strlen(token) : 0);

	// retail [0x012ED648]
	Rva000C2A30Owner *list = g_Va012ED648->find(name);

	if (list == 0)
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		const char *text = name.str();
		BfmeAwakenLog *log = TheBfmeAwakenDebug->slot6C(0, 0);
		log->slot38(Debug::Format("Unable to find water texture type '%s'\n", text));
		log->slot4C(1);
	}
	else
	{
		ini->initFromINI(list, g_0108132C);
		list->dump();
	}
}
