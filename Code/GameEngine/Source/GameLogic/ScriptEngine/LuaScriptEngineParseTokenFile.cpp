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

class BfmeLexEAN
{
public:
	BfmeLexEAN(char *text, char *buffer, Int limit);
	~BfmeLexEAN();

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
	Int finish();
};

class __declspec(novtable) LuaScriptEngine
{
public:
	void rva002EC840ParseTokenFile(const char *filename, Bool keepOpen);
	void rva002EC770ParseToken(BfmeLexEAN *parser);

private:
	char m_pad00B4[0xB4];
	unsigned char m_keepOpen;
};

#pragma comment(linker, "/alternatename:??1BfmeLexEAN@@QAE@XZ=?j_0000e7a0@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish@XmlNameSlotList@@QAEHXZ=?j_00049ae4@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002EC770ParseToken@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z=?j_0000ed95@@YAXXZ")

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
		for (;;)
		{
			Int status = ((XmlNameSlotList *)&parser)->finish();
			if (status == 0)
				break;
			if (--status != 0)
				return;
			rva002EC770ParseToken(&parser);
		}

		m_keepOpen = 0;
		operator delete[](source);
	}
}
