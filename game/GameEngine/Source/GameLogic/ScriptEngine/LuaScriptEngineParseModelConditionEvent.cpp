// stlport
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// Retail 0x002E9680 (746 bytes, ret 4): the ModelConditionEvent entry of the
// Lua script engine's Events XML reader.  The matched dispatcher 0x002EA5D0
// (LuaScriptEngineParseTokenEvents.cpp) calls it for the "ModelConditionEvent"
// tag.  It reads the element's "Name" attribute, requires a "Conditions" child
// whose text is parsed twice into 304-bit condition sets (required, and an
// excluded set built as flip / parse / flip), and appends a 0x54-byte
// {name key, required, excluded} record to the vector at +0x98 unless an
// identical record is already there.  Parsing runs under
// try { } catch (INIException &) { } catch (...) { } (FuncInfo 0x0120542C:
// one try over states 1-2, handlers 0x002E996A and 0x002E99BF), and the
// INIException handler logs "Error during parsing XML data: " plus the
// exception's message.
//
// Callee names are the existing ledger identities of the bodies reached
// through the retail ILT thunks; the record and flag types keep address-derived
// names because nothing names them.

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

extern const char g_bfmeEmptyAscii[];

class LuaScriptEngine;
class Rva002E7E00Owner;

template <typename T> class StringBase;
template <> class StringBase<char>
{
public:
	void set(const char *text, int length);
	const char *str() const { return m_data != 0 ? m_data->data : g_bfmeEmptyAscii; }

private:
	friend class LuaScriptEngine;
	friend class Rva002E7E00Owner;
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

extern void *g_Rva00F36E5C; // VA 01336E5C debug manager cell (data_rows.csv owner)
#define TheBfmeAwakenDebug (static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C))
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite( Int kind );

// The XML reader the dispatcher already drives (count/finish at 0x0035EF50 /
// 0x0035EE70; attribute name/value getters 0x0035EF60 / 0x0035EF90).
class XmlNameSlotList
{
public:
	Int finish();
};

// The element count getter at 0x0035EF50, under its ledger name
// (?m@Gen_0035ef50@@QAEHXZ); same thiscall int body as the former
// XmlNameSlotList::count().
class Gen_0035ef50
{
public:
	Int m();
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

// 0x002E7E00 parses a condition string into the 40-byte set it is called on.
class Rva002E7E00Owner
{
public:
	void parse(AsciiString text);
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

// A 304-bit condition set with STLport bitset<304>'s bodies: memset reset,
// word-wise flip, then _Sanitize<16> on the top word.
class Rva002E9680Conditions
{
public:
	Rva002E9680Conditions() { memset(m_words, 0, sizeof(m_words)); }
	void doFlip()
	{
		for (unsigned int i = 0; i < 10; ++i)
			m_words[i] = ~m_words[i];
	}
	static void sanitize(unsigned long &top) { top &= ~((~0UL) << 16); }
	__forceinline void flip()
	{
		doFlip();
		sanitize(m_words[9]);
	}

	unsigned long m_words[10];
};

// The 0x54-byte model-condition event record: name key (set through
// 0x002DFA00), required and excluded condition words.  The vector's
// reallocating insert is the 84-byte instantiation at 0x002E7AA0 (reached
// through ILT 0x0001636F), whose ledger row names its element
// Rva002E9680ModelConditionEvent; this body shows what the element holds, so the record
// keeps an address-derived name of its own.
class Rva002E9680ModelConditionEvent
{
public:
	Int m_nameKey;
	unsigned int m_required[10];
	unsigned int m_excluded[10];
};

static inline Bool sameConditions006E9680(const unsigned int *left, const unsigned int *right)
{
	for (unsigned int i = 0; i < 10; ++i)
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
	void rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser);

private:
	char m_unmodelled08[0x98 - 0x08];
	_STL::vector<Rva002E9680ModelConditionEvent> m_modelConditionEvents98;
};

// ?rva002E9680ParseModelConditionEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
void LuaScriptEngine::rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser)
{

	AsciiString name;

	for (Int i = 0; i < ((Gen_0035ef50 *)parser)->m(); ++i)
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
		Rva002E9680Conditions required;
		Rva002E9680Conditions excluded;
		excluded.flip();
		((Rva002E7E00Owner *)&required)->parse(conditions);
		((Rva002E7E00Owner *)&excluded)->parse(conditions);
		excluded.flip();

		Rva002E9680ModelConditionEvent record;
		((Gen_002df780 *)&record)->m();
		memcpy(record.m_required, &required, sizeof(record.m_required));
		memcpy(record.m_excluded, &excluded, sizeof(record.m_excluded));
		((BfmeThingBLC *)&record)->bfmeGoBLC((void *)name.str());

		Bool found = false;
		for (Rva002E9680ModelConditionEvent *it = m_modelConditionEvents98.begin();
			it != m_modelConditionEvents98.end(); ++it)
		{
			if (record.m_nameKey == it->m_nameKey
				&& sameConditions006E9680(record.m_required, it->m_required)
				&& sameConditions006E9680(record.m_excluded, it->m_excluded))
			{
				found = true;
				break;
			}
		}
		if (!found)
			m_modelConditionEvents98.push_back(record);
		else
			return;
	}
	catch (INIException &e)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			TheBfmeAwakenDebug->slot6c(0, 0)
				->slot38("Error during parsing XML data: ")
				->slot38(e.mFailureMessage)
				->slot4c(2);
		}
	}
	catch (...)
	{
	}

	if (((XmlNameSlotList *)parser)->finish() == 2)
		((XmlNameSlotList *)parser)->finish();
}
