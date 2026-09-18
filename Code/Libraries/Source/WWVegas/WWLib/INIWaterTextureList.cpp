// cl: /DNDEBUG /MD /EHsc /Ob1
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

typedef int Int;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
	};

	Header *m_data;

public:
	void set(const T *text, int length);

private:
	void releaseBuffer();
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set(const char *text, int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}

	const char *str() const
	{
		return m_data ? (const char *)((const char *)m_data + 8) : (const char *)0x0107388B;
	}
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *instance, const void *fieldParse);

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

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);

void INI::parseWaterTextureListDefinition(INI *ini)
{
	AsciiString name;
	const char *token = ini->getNextToken();
	name.set(token, token ? (int)strlen(token) : 0);

	// retail [0x012ED648]
	Rva000C2A30Owner *list = (*(Rva000AF530Table **)0x012ED648)->find(name);

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
		ini->initFromINI(list, (const void *)0x0108132C);
		list->dump();
	}
}
