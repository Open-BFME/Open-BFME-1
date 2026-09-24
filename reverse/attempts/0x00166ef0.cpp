// ?startTraining@AIPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z
// partial score=0.978 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// AIPlayer::startTraining, retail 0x00166EF0.
//
// The caller at AIPlayer::doTeamBuilding passes a WorkOrder and its team name.
// The three-argument findFactory body at 0x001643B0 proves the BFME build-index
// output used by this method. The debug string and the queue result identify the
// method independently of the address-derived source file.

typedef bool Bool;
typedef int Int;

#include "ascii_string.h"

class ThingTemplate
{
public:
	const AsciiString &getName() const
	{
		return *(const AsciiString *)((const char *)this + 0x20);
	}
};

class WorkOrder
{
public:
	virtual ~WorkOrder();
	const ThingTemplate *m_thing;
	Int m_factoryID;
};

class Object;
class ProductionUpdateInterface;

class AIPlayer
{
protected:
	virtual Bool startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName);

public:
	Object *findFactory(const ThingTemplate *thing, Bool busyOK,
		Int *buildIndex);
};

class Object
{
public:
	ProductionUpdateInterface *getProductionUpdateInterface();
	Int getID() const
	{
		return *(const Int *)((const char *)this + 0x74);
	}
};

class ProductionUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual Int requestUniqueUnitID(Int first, Int second);
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual Bool queueCreateUnit(const ThingTemplate *thing, const void *order,
		Int productionID);
};

class GlobalData
{
public:
	unsigned char m_padding[0xa88];
	Int m_debugAI;
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};

#define TheGlobalData (*(GlobalData **)0x012ED5C8)
#define TheScriptEngine (*(ScriptEngine **)0x012F076C)


// ?startTraining@AIPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z
Bool AIPlayer::startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName)
{
	Object *factory;
	{
		Int factoryID;
		factory = findFactory(order->m_thing, busyOK, &factoryID);
	}
	if (factory)
	{
		ProductionUpdateInterface *pu = factory->getProductionUpdateInterface();
		if (pu && pu->queueCreateUnit(order->m_thing,
			*(const void **)&teamName,
			pu->requestUniqueUnitID(-1, 0)))
		{
			order->m_factoryID = factory->getID();
			if (TheGlobalData->m_debugAI)
			{
				AsciiString teamStr = "Queuing ";
				teamStr.concat(order->m_thing->getName());
				teamStr.concat(" for ");
				teamStr.concat(teamName);
				TheScriptEngine->AppendDebugMessage(teamStr, false);
			}
			return true;
		}
	}
	return false;
}
