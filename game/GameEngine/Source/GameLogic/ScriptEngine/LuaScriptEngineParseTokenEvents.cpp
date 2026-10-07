// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 0x002EA5D0: Events dispatch reached from matched LuaScriptEngineParseToken.cpp.
// The retail backedge at +0xE9 repeats the status==1 check at +0x40.
// Retail string/call pairs establish InternalEvent -> 002E2970, ScriptedEvent
// -> 002E9590, ModelConditionEvent -> 002E9680, ObjectStatusEvent -> 002E9AA0.
// All receive the unchanged engine ECX and parser stack argument; each returns ret 4.
typedef int Int;

extern "C" int strcmp(const char *, const char *);

class XmlNameSlotList
{
public:
	Int finish();
};

class BfmeLexEAN
{
public:
	char *getTailEAN();
};

// InternalEvent dispatch uses the established event-flag host ABI at the same this.
class Rva002E2970Host
{
public:
	void applyNameFlags(XmlNameSlotList *xml);
};

class __declspec(novtable) LuaScriptEngine
{
public:
	void ProcessEventsElement(BfmeLexEAN *parser);
	void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);
	void rva002E9590ParseScriptedEvent(BfmeLexEAN *parser);
	void rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser);

};


void LuaScriptEngine::ProcessEventsElement(BfmeLexEAN *parser)
{
	char *tail = parser->getTailEAN();
	int cmpEvents = strcmp(tail, "Events");
	if (cmpEvents != 0)
		return;

	Int status = ((XmlNameSlotList *)parser)->finish();
	while (status != 0)
	{
		if (--status != 0)
			return;

		const char *tag = parser->getTailEAN();
		int cmp;

		cmp = strcmp(tag, "InternalEvent");
		if (cmp == 0)
		{
			((Rva002E2970Host *)this)->applyNameFlags((XmlNameSlotList *)parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ScriptedEvent");
		if (cmp == 0)
		{
			rva002E9590ParseScriptedEvent(parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ModelConditionEvent");
		if (cmp == 0)
		{
			rva002E9680ParseModelConditionEvent(parser);
			goto checkFinish;
		}

		cmp = strcmp(tag, "ObjectStatusEvent");
		if (cmp != 0)
			return;

		rva002E9AA0ParseObjectStatusEvent(parser);

	checkFinish:
		status = ((XmlNameSlotList *)parser)->finish();
	}
}
