// ?d_002e9aa0@@YAXXZ
// partial score=0.5714 date=2026-09-28
// stlport
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Retail 0x002E9AA0 (686 bytes, ret 4): the ObjectStatusEvent entry of the
// Lua script engine's Events XML reader.  The matched dispatcher 0x002EA5D0
// (LuaScriptEngineParseTokenEvents.cpp) calls it for the "ObjectStatusEvent"
// tag.  It is the object-status twin of the ModelConditionEvent reader
// 0x002E9680 (LuaScriptEngineParseModelConditionEvent.cpp): it reads the
// element's "Name" attribute, requires a "Conditions" child whose text is
// parsed twice into 86-bit object-status sets through the matched
// DeathStatusFlags::parse (required, and an excluded set built as flip /
// parse / flip), and appends a 0x1C-byte {name key, required, excluded}
// record to the vector at +0xA4 unless an identical record is already there.
// The try / catch shape and the INIException log are the sibling's.
//
// The record is the element of the vector instantiation whose reallocating
// insert is matched at 0x002E7C50 (reached here through ILT 0x00032272), so
// it carries that body's address-derived element name.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <string.h>
#pragma intrinsic(strcmp, strlen, memcpy, memset)

typedef int Int;
typedef bool Bool;

struct StringBaseCharHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

extern const char Rva006A16B0Empty[];

class LuaScriptEngine;
class DeathStatusFlags;

template <typename T> class StringBase;
template <> class StringBase<char>
{
public:
	void set(const char *text, int length);
	const char *str() const { return m_data != 0 ? m_data->data : Rva006A16B0Empty; }

private:
	friend class LuaScriptEngine;
	friend class DeathStatusFlags;
	friend class AsciiString;
	StringBase() : m_data(0) {}
	StringBase(const char *text);
	StringBase(const StringBase &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	StringBaseCharHeader *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

// Zero Hour INI.h: the exception carries its failure message first.
class INIException
{
public:
	char *mFailureMessage;
};

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38( const char *text );
	virtual void slot3c(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual BfmeAwakenLog *slot4c( Int value );
};

class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60();
	virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6c( Int first, Int second );
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite( Int kind );

// The XML reader the dispatcher already drives (count/finish at 0x0035EF50 /
// 0x0035EE70; attribute name/value getters 0x0035EF60 / 0x0035EF90).
class XmlNameSlotList
{
public:
	Int count();
	Int finish();
};

class BfmeLexEAN
{
public:
	char *getTailEAN();
};

class Rva0035EF60
{
public:
	void *get(Int index);
};

class Rva0035EF90
{
public:
	void *get(Int index);
};


// 0x002DF780 (`m_name = 0; return this`) and 0x002DFA00
// (`m_name = TheNameKeyGenerator->nameToKey(text)`), the record's constructor
// and name setter, under their ledger names.
class Gen_002df780
{
public:
	void *m();
};

class BfmeThingBLC
{
public:
	void bfmeGoBLC(void *what);
};

// The 86-bit object-status set: DeathStatusFlags (parse at 0x00209310,
// DeathStatusFlags_parse.cpp) with STLport bitset<86>'s bodies: memset reset,
// word-wise flip, then _Sanitize<22> on the top word.
class DeathStatusFlags
{
public:
	DeathStatusFlags() { memset(m_words, 0, sizeof(m_words)); }
	void parse(AsciiString description);
	void doFlip()
	{
		for (unsigned int i = 0; i < 3; ++i)
			m_words[i] = ~m_words[i];
	}
	static void sanitize(unsigned long &top) { top &= ~((~0UL) << 22); }
	__forceinline void flip()
	{
		doFlip();
		sanitize(m_words[2]);
	}

	unsigned long m_words[3];
};

// The 0x1C-byte object-status event record.
class Rva002E7C50Element
{
public:
	Int m_nameKey;
	unsigned int m_required[3];
	unsigned int m_excluded[3];
};

static inline Bool sameStatus002E9AA0(const unsigned int *left, const unsigned int *right)
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		if (left[i] != right[i])
			return false;
	}
	return true;
}

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;
	virtual void draw();

private:
	void *m_name;
};

class __declspec(novtable) LuaScriptEngine : public SubsystemInterface
{
public:
	void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);

private:
	char m_beforeFunctionFields[0xA4 - 0x08];
	_STL::vector<Rva002E7C50Element> m_objectStatusEventsA4;
};

// ?rva002E9AA0ParseObjectStatusEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
void LuaScriptEngine::rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser)
{

	AsciiString name;

	for (Int i = 0; i < ((XmlNameSlotList *)parser)->count(); ++i)
	{
		Int nameCompare = strcmp((const char *)((Rva0035EF60 *)parser)->get(i), "Name");
		if (nameCompare == 0)
		{
			const char *value = (const char *)((Rva0035EF90 *)parser)->get(i);
			name.set(value, value != 0 ? (Int)strlen(value) : 0);
		}
	}

	if (((XmlNameSlotList *)parser)->finish() != 1)
		return;
	Int conditionsCompare = strcmp(parser->getTailEAN(), "Conditions");
	Bool isConditions = conditionsCompare == 0;
	if (!isConditions)
		return;
	if (((XmlNameSlotList *)parser)->finish() != 3)
		return;

	const char *text = parser->getTailEAN();
	try
	{
		AsciiString conditions(text);
		DeathStatusFlags required;
		DeathStatusFlags excluded;
		excluded.flip();
		required.parse(conditions);
		excluded.parse(conditions);
		excluded.flip();

		Rva002E7C50Element record;
		((Gen_002df780 *)&record)->m();
		memcpy(record.m_required, &required, sizeof(record.m_required));
		memcpy(record.m_excluded, &excluded, sizeof(record.m_excluded));
		((BfmeThingBLC *)&record)->bfmeGoBLC((void *)name.str());

		Bool found = false;
		for (Rva002E7C50Element *it = m_objectStatusEventsA4.begin();
			it != m_objectStatusEventsA4.end(); ++it)
		{
			if (record.m_nameKey == it->m_nameKey
				&& sameStatus002E9AA0(record.m_required, it->m_required)
				&& sameStatus002E9AA0(record.m_excluded, it->m_excluded))
			{
				found = true;
				break;
			}
		}
		if (!found)
			m_objectStatusEventsA4.push_back(record);
		else
			return;
	}
	catch (...)
	{
	}

	if (((XmlNameSlotList *)parser)->finish() == 2)
		((XmlNameSlotList *)parser)->finish();
}
