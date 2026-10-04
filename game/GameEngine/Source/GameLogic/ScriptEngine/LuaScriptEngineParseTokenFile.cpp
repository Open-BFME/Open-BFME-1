// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// LuaScriptEngine::rva002EC840ParseTokenFile, retail RVA 0x002EC840.
// RegisterScriptFunctions calls this body with Data\\Scripts\\ScriptEvents.xml.
// The parser constructor, parser cleanup, and parser loop all use the existing
// retail ILT identities from BfmeConv2008.cpp and the XML parser table.

typedef int Int;
typedef bool Bool;

extern void *operator new[](unsigned int size);
extern void operator delete[](void *memory);

class File
{
public:
	virtual void fileVirtual00() = 0;
	virtual void fileVirtual01() = 0;
	virtual void close() = 0;
	virtual Int read(void *buffer, Int bytes) = 0;
	virtual void fileVirtual03() = 0;
	virtual void fileVirtual04() = 0;
	virtual void fileVirtual05() = 0;
	virtual void fileVirtual06() = 0;
	virtual void fileVirtual07() = 0;
	virtual void fileVirtual08() = 0;
	virtual void fileVirtual09() = 0;
	virtual Int size() = 0;
	virtual void fileVirtual12() = 0;
};

class FileSystem
{
public:
	File *openFile(const char *filename, Int access);
};

extern FileSystem *TheFileSystem;

extern void j_0000e7a0();      // retail ILT thunk for the BfmeLexEAN cleanup
extern void j_00049ae4();      // retail ILT thunk for the XmlNameSlotList slot
extern void j_0000ed95();      // retail ILT thunk for LuaScriptEngine::ParseToken

class BfmeLexEAN
{
public:
	BfmeLexEAN(char *text, char *buffer, Int limit);

	// Retail cleans the lexer up through its ILT thunk at 0x0000e7a0, so the
	// cleanup body is written here and inlined at every scope exit: the
	// generated call carries the thunk's own name.
	__forceinline ~BfmeLexEAN()
	{
		typedef void (BfmeLexEAN::*Cleanup)(void);
		union { void (*fn)(); Cleanup call; } cleanup = { j_0000e7a0 };
		(this->*cleanup.call)();
	}

	char *m_bfmePosEAN;
	char *m_bfmeLineEAN;
	char *m_bfmeSourceEAN;
	Int m_bfmeLineNumberEAN;
	Int m_bfmeTagEAN;
	char *m_bfmeBufEAN;
	Int m_bfmeLimitEAN;
	char *m_bfmeTailEAN;
	Int m_bfmeDepthEAN;
	unsigned char m_bfmeSeenEAN;
	Int m_bfmeMarkEAN;
	Int m_bfmeStackEAN[0x61];
};

class XmlNameSlotList
{
public:
};

class __declspec(novtable) LuaScriptEngine
{
public:
	void rva002EC840ParseTokenFile(const char *filename, Bool keepOpen);

private:
	char m_pad00B4[0xB4];
	unsigned char m_keepOpen;
};

void LuaScriptEngine::rva002EC840ParseTokenFile(const char *filename, Bool keepOpen)
{
	File *file = TheFileSystem->openFile(filename, 0x41);
	if (file != 0)
	{
		Int size = file->size();
		char *source = (char *)operator new[](size + 10);
		file->read(source, size);
		source[size] = 0;
		file->close();

		char buffer[0x1000];
		m_keepOpen = keepOpen;
		BfmeLexEAN parser(source, buffer, 0xFFF);
		typedef Int (XmlNameSlotList::*Slot)(void);
		typedef void (LuaScriptEngine::*ParseToken)(BfmeLexEAN *);
		for (;;)
		{
			union { void (*fn)(); Slot call; } slot = { j_00049ae4 };
			Int status = (((XmlNameSlotList *)&parser)->*slot.call)();
			if (status == 0)
				break;
			if (--status != 0)
				return;
			union { void (*fn)(); ParseToken call; } parse = { j_0000ed95 };
			(this->*parse.call)(&parser);
		}

		m_keepOpen = 0;
		operator delete[](source);
	}
}
