// ?rva002EA5D0ParseTokenEvents@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// partial score=0.39 date=2026-09-21
// ?d_002ea5d0@@YAXXZ
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// LuaScriptEngine::rva002EA5D0ParseTokenEvents, retail RVA 0x002EA5D0.
// Reached from LuaScriptEngineParseTokenFile.cpp's sibling
// rva002EC770ParseToken (reverse/attempts/0x002ec770.cpp, stashed partial)
// through the ?j_0000668b@@YAXXZ alternate name when the outer tag reads
// "Events". Re-verifies the tail reads "Events" again, requires
// XmlNameSlotList::finish() == 1 (0x00049ae4, matched), then reads the next
// tag and dispatches: InternalEvent -> the still-carved body at 0x0003A9AE's
// target 0x002E9590 (via the thunk emitted by add_match's callee pin);
// ScriptedEvent -> 0x002E9AA0; ModelConditionEvent -> 0x002E9680;
// ObjectStatusEvent -> Rva002E2970Host::applyNameFlags (matched,
// Rva002E2970ApplyNameFlags.cpp) -- the this pointer these handlers get is
// the SAME LuaScriptEngine this unmodified, matching that file's Host view
// of LuaScriptEngine's own event-flag fields. All four arms rejoin a shared
// finish()==1 recheck tail; the sibling attempt's own notes record that
// MSVC would not fold that tail across even two arms, so it stays
// duplicated here across all four.

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

// upstream layout: Rva002E2970ApplyNameFlags.cpp -- the event-flag view of
// this same LuaScriptEngine object, cast without offset.
class Rva002E2970Host
{
public:
	void applyNameFlags(XmlNameSlotList *xml);
};

class __declspec(novtable) LuaScriptEngine
{
public:
	void rva002EA5D0ParseTokenEvents(BfmeLexEAN *parser);
	void rva002EA5D0ParseInternalEvent(BfmeLexEAN *parser);
	void rva002EA5D0ParseScriptedEvent(BfmeLexEAN *parser);
	void rva002EA5D0ParseModelConditionEvent(BfmeLexEAN *parser);

private:
	char m_pad00B4[0xB4];
	unsigned char m_keepOpen;
};

#pragma comment(linker, "/alternatename:?getTailEAN@BfmeLexEAN@@QAEPADXZ=?j_000262ba@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish@XmlNameSlotList@@QAEHXZ=?j_00049ae4@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002EA5D0ParseInternalEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z=?j_0003a9ae@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002EA5D0ParseScriptedEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z=?j_00038c85@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva002EA5D0ParseModelConditionEvent@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z=?j_00047451@@YAXXZ")
#pragma comment(linker, "/alternatename:?applyNameFlags@Rva002E2970Host@@QAEXPAVXmlNameSlotList@@@Z=?j_00041678@@YAXXZ")

// ?d_002ea5d0@@YAXXZ
void LuaScriptEngine::rva002EA5D0ParseTokenEvents(BfmeLexEAN *parser)
{
	char *tail = parser->getTailEAN();
	int cmpEvents = strcmp(tail, "Events");
	if (cmpEvents != 0)
		return;

	Int status = ((XmlNameSlotList *)parser)->finish();
	if (status == 0)
		return;
	if (--status != 0)
		return;

	const char *tag = parser->getTailEAN();
	int cmp;

	cmp = strcmp(tag, "InternalEvent");
	if (cmp == 0)
	{
		rva002EA5D0ParseInternalEvent(parser);
		goto checkFinish;
	}

	cmp = strcmp(tag, "ScriptedEvent");
	if (cmp == 0)
	{
		rva002EA5D0ParseScriptedEvent(parser);
		goto checkFinish;
	}

	cmp = strcmp(tag, "ModelConditionEvent");
	if (cmp == 0)
	{
		rva002EA5D0ParseModelConditionEvent(parser);
		goto checkFinish;
	}

	cmp = strcmp(tag, "ObjectStatusEvent");
	if (cmp != 0)
		return;

	((Rva002E2970Host *)this)->applyNameFlags((XmlNameSlotList *)parser);

checkFinish:
	Int status2 = ((XmlNameSlotList *)parser)->finish();
	if (status2 == 0)
		return;
	if (--status2 != 0)
		return;
}
