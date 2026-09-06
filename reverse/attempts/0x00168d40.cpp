// ?d_00168d40@@YAXXZ
// partial score=0.4 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of AIPlayer::startTraining (twin 0x00166EF0,
// AIPlayer_startTraining_Thunk.cpp / real source AIPlayer.cpp:1412). Same
// callee set (findFactory, getProductionUpdateInterface, two virtual calls,
// AsciiString ctor+concat+concat+concat, AppendDebugMessage, three
// releaseBuffer dtors) -- the only observed diff is a 4-byte local/stack
// slot shift, so this is the identical logic recompiled at a second call
// site / duplicate override.

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString(void);
	void concat(const AsciiString &other);
	void concat(const char *text);

private:
	void *m_data;
};

class ThingTemplate;

class Object
{
public:
	int getID(void) const;
	class ProductionUpdateInterface *getProductionUpdateInterface(void) const;
};

class ProductionUpdateInterface
{
public:
	virtual int requestUniqueUnitID(void) = 0;
	virtual bool queueCreateUnit(const ThingTemplate *thing, int id) = 0;
};

class WorkOrder
{
public:
	const ThingTemplate *m_thing;
	int m_factoryID;
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &msg, bool);
};

extern ScriptEngine *TheScriptEngine;

struct GlobalData
{
	bool m_debugAI;
};

extern GlobalData *TheGlobalData;

extern const AsciiString &bfmeThingTemplateName(const ThingTemplate *thing);

class AIPlayer
{
public:
	Object *findFactory(const ThingTemplate *thing, bool busyOK);
	bool startTraining(WorkOrder *order, bool busyOK, AsciiString teamName);
};

bool AIPlayer::startTraining(WorkOrder *order, bool busyOK, AsciiString teamName)
{
	Object *factory = findFactory(order->m_thing, busyOK);
	if (factory)
	{
		ProductionUpdateInterface *pu = factory->getProductionUpdateInterface();
		if (pu && pu->queueCreateUnit(order->m_thing, pu->requestUniqueUnitID()))
		{
			order->m_factoryID = factory->getID();
			if (TheGlobalData->m_debugAI)
			{
				AsciiString teamStr = "Queuing ";
				teamStr.concat(bfmeThingTemplateName(order->m_thing));
				teamStr.concat(" for ");
				teamStr.concat(teamName);
				TheScriptEngine->AppendDebugMessage(teamStr, false);
			}
			return true;
		}
	}

	return false;
}
