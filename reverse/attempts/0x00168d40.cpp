// ?rva00168D40@AIPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00168D40: AIPlayer::startTraining, identified by the matching
// production call sequence and the WorkOrder field accesses.

class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString(void);
	void appendString(const AsciiString &other);
	void appendText(const char *text);

private:
	void *m_data;
};

class ThingTemplate;

class Object
{
public:
	int getID(void) const
	{
		return *(const int *)((const char *)this + 0x74);
	}
	class ProductionUpdateInterface *callGetProductionUpdateInterface(void) const;
};

class ProductionUpdateInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual int requestUniqueUnitID(void) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual bool queueCreateUnit(const ThingTemplate *thing, int id) = 0;
};

class WorkOrder
{
public:
	char m_unknown_000[4];
	const ThingTemplate *m_thing;
	int m_factoryID;
};

class ScriptEngine
{
public:
	void callAppendDebugMessage(const AsciiString &msg, bool);
};

#define TheScriptEngine (*(ScriptEngine **)0x012f076c)

struct GlobalData
{
	char m_unknown_000[0xa88];
	int m_debugAI;
};

#define TheGlobalData (*(GlobalData **)0x012ed5c8)

class AIPlayer
{
	public:
	Object *callFindFactory(const ThingTemplate *thing, bool busyOK, int *factoryID);

protected:
	virtual bool rva00168D40(WorkOrder *order, bool busyOK, AsciiString teamName);
};

bool AIPlayer::rva00168D40(WorkOrder *order, bool busyOK, AsciiString teamName)
{
	Object *factory;
	int factoryID;
	ProductionUpdateInterface *pu;
	factory = callFindFactory(order->m_thing, busyOK, &factoryID);
	if (factory)
	{
		pu = factory->callGetProductionUpdateInterface();
		if (pu && pu->queueCreateUnit(order->m_thing, pu->requestUniqueUnitID()))
		{
			order->m_factoryID = factory->getID();
			GlobalData *globalData = *(GlobalData **)0x012ed5c8;
			if (globalData->m_debugAI)
			{
				AsciiString teamStr = "Queuing ";
				teamStr.appendString(*(const AsciiString *)
					((const char *)order->m_thing + 0x20));
				teamStr.appendText(" for ");
				teamStr.appendString(teamName);
				TheScriptEngine->callAppendDebugMessage(teamStr, false);
			}
			return true;
		}
	}

	return false;
}
