// ?Rva000C2BC0RiverNoiseTextures@@YAXPAVINI@@@Z
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /Ob1
// stlport

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

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
};

// Address-derived: uninitialized global pointer read at VA 0x012ED648. Zeroed
// in the image (bss), populated at runtime by a subsystem this lane did not
// identify. Its one known use is this body: query(&outName) returns a nonzero
// "instance" pointer that becomes initFromINI's first argument, or 0 on
// failure (falls into the missing-water-texture error report).
class Rva012ED648Mgr
{
public:
	void *query(AsciiString *outName);
};
extern Rva012ED648Mgr *g_rva012ed648Mgr;

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

class BFMEIndexBufferDebugClass
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

extern BFMEIndexBufferDebugClass *g_BFMEIndexBufferDebug;
extern void _bfme_debugRecordCallsite(int kind);

// Address-derived name: instruction stream is a 0.911 difflib match to the
// landed ?iniParseVictorySystemDefinition@@YAXPAVINI@@@Z (Code/GameEngine/
// Source/GameLogic/INI_parseVictorySystemDefinition.cpp) but the retail data
// referenced proves a different field: the format string at VA 0x01083900 is
// "Unable to find water texture type '%s'\n" and the FieldParse table
// literal is 0x0108132C, near a "RiverNoiseTextures" label in the image. The
// twin's direct `TheVictorySystem == 0` global test is replaced here by a
// thiscall query(&name) through the unidentified singleton at 0x012ED648;
// its nonzero return becomes initFromINI's instance argument. Real class and
// field names not recovered.
// ?Rva000C2BC0RiverNoiseTextures@@YAXPAVINI@@@Z
void __cdecl Rva000C2BC0RiverNoiseTextures(INI *ini)
{
	AsciiString name;
	const char *token = ini->getNextToken();
	name.set(token, token ? (int)strlen(token) : 0);

	void *instance = g_rva012ed648Mgr->query(&name);
	if (instance == 0)
	{
		_bfme_debugRecordCallsite(1);
		g_BFMEIndexBufferDebug->Begin_Report();
		const char *text = name.str();
		BFMEIndexBufferDebugStream *stream =
			g_BFMEIndexBufferDebug->Get_Stream(0, 0);
		stream->Put_String(Debug::Format("Unable to find water texture type '%s'\n", text));
		stream->Finish(1);
	}
	else
	{
		ini->initFromINI(instance, (const void *)0x0108132C);
	}
}
