// ?rva002EC770ParseToken@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// partial score=0.73 date=2026-09-21
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// LuaScriptEngine::rva002EC770ParseToken, retail RVA 0x002EC770.
// Sibling of LuaScriptEngineParseTokenFile.cpp's rva002EC840ParseTokenFile,
// which calls this body once per XML tag through the
// ?j_0000ed95@@YAXXZ alternate name. `parser` is the same BfmeLexEAN the
// caller constructs; m_bfmeTailEAN (+0x1C) holds the tag name the lexer just
// consumed. The root element must read "SageLuaScriptSection" and
// XmlNameSlotList::finish() (already pinned to 0x0035EE70) must report 1;
// then the tag is re-read and dispatched to one of two sibling handlers --
// "Events" through the still-carved body at 0x002EA5D0 (thunk 0x0000668B)
// and "EventList" through the still-carved body at 0x002EC0A0 (thunk
// 0x0003ED33) -- before a final finish() == 1 check.

typedef int Int;
typedef bool Bool;

extern "C" int strcmp(const char *, const char *);

class XmlNameSlotList
{
public:
	Int finish();
};

class BfmeLexEAN
{
public:
	BfmeLexEAN(char *text, char *buffer, Int limit);
	~BfmeLexEAN();

	char *getTailEAN(void);

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

class __declspec(novtable) LuaScriptEngine
{
public:
	void rva002EC770ParseToken(BfmeLexEAN *parser);
	void rva002EC770ParseTokenEvents(BfmeLexEAN *parser);
	void rva002EC770ParseTokenEventList(BfmeLexEAN *parser);

private:
	char m_pad00B4[0xB4];
	unsigned char m_keepOpen;
};

#pragma comment(linker, "/alternatename:?getTailEAN@BfmeLexEAN@@QAEPADXZ=?j_000262ba@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish@XmlNameSlotList@@QAEHXZ=?j_00049ae4@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002EC770ParseTokenEvents@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z=?j_0000668b@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002EC770ParseTokenEventList@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z=?j_0003ed33@@YAXXZ")

// ?d_002ec770@@YAXXZ
void LuaScriptEngine::rva002EC770ParseToken(BfmeLexEAN *parser)
{
	char *tail = parser->getTailEAN();
	int cmp = strcmp(tail, "SageLuaScriptSection");
	if (cmp != 0)
		return;

	Int status = ((XmlNameSlotList *)parser)->finish();
	if (status == 0)
		return;
	if (--status != 0)
		return;

	const char *tag = parser->getTailEAN();

	int cmpEvents = strcmp(tag, "Events");
	if (cmpEvents == 0)
	{
		rva002EC770ParseTokenEvents(parser);
		goto checkFinish;
	}

	if (strcmp(tag, "EventList") != 0)
		return;

	rva002EC770ParseTokenEventList(parser);

checkFinish:
	Int status2 = ((XmlNameSlotList *)parser)->finish();
	if (status2 == 0)
		return;
	if (--status2 != 0)
		return;
}
