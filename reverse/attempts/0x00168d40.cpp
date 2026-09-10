// ?rva00168D40@AIPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z
// partial score=0.85 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Retail 0x00168D40: twin of the naked-lifted AIPlayer::startTraining at
// 0x00166EF0 (both call ProductionUpdateInterface slot+8 with constants
// (-1, 0), then slot+0x1c with (thing, order, id) -- a 3-arg BFME-local
// queueCreateUnit taking the WorkOrder* itself, not ZH's 2-arg form).

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

class WorkOrder;

class ProductionUpdateInterface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual int requestUniqueUnitID(int, int) = 0;
	virtual void slot0c(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual bool queueCreateUnit(const ThingTemplate *thing, WorkOrder *order, int id) = 0;
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
		if (pu && pu->queueCreateUnit(order->m_thing, order, pu->requestUniqueUnitID(-1, 0)))
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
