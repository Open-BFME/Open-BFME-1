// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// AISkirmishPlayer::startTraining (0x00168D40): slot 24 (+0x60) of
// AISkirmishPlayer's table 0x01096FB0; the same slot of AIPlayer's table
// 0x010968B0 is the matched AIPlayer::startTraining (0x00166EF0), and the two
// bodies have the same instruction sequence, as the two Zero Hour bodies are
// the same source. BFME's findFactory reports through an int out-parameter
// that queueCreateUnit then takes, with two more arguments (-1, 0).

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

enum ObjectID { INVALID_ID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_nameString; }
private:
	char m_unmodelled000[0x20];
	AsciiString m_nameString;							///< this+0x20
};

#define BFME_PRODUCTION_SLOT(n) virtual void bfmeProductionSlot##n() = 0;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ProductionUpdate.h
class ProductionUpdateInterface
{
public:
	BFME_PRODUCTION_SLOT(0) BFME_PRODUCTION_SLOT(1)
	virtual Int requestUniqueUnitID() = 0;				///< vtable +0x08
	BFME_PRODUCTION_SLOT(3) BFME_PRODUCTION_SLOT(4) BFME_PRODUCTION_SLOT(5) BFME_PRODUCTION_SLOT(6)
	virtual Bool queueCreateUnit( const ThingTemplate *unitType, Int bfmeFactoryArg, Int productionID, Int bfmeC, Int bfmeD ) = 0;	///< vtable +0x1C
};

#undef BFME_PRODUCTION_SLOT

class Object
{
public:
	ProductionUpdateInterface *getProductionUpdateInterface();
	ObjectID getID() const { return m_id; }
private:
	char m_unmodelled000[0x74];
	ObjectID m_id;										///< this+0x74
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class WorkOrder
{
public:
	char m_unmodelled000[0x4];
	const ThingTemplate *m_thing;						///< this+0x04
	ObjectID m_factoryID;								///< this+0x08
};

struct GlobalData
{
	char m_unmodelled000[0xa88];
	Int m_debugAI;										///< this+0xA88
};

extern GlobalData *TheGlobalData;

class ScriptEngine
{
public:
	void AppendDebugMessage( const AsciiString &strToAdd, Bool mustAdd );
};

extern ScriptEngine *TheScriptEngine;

class AIPlayer
{
protected:
	virtual Bool startTraining( WorkOrder *order, Bool busyOK, AsciiString teamName );
	Object *findFactory( const ThingTemplate *thing, Bool busyOK, Int *bfmeFactoryArg );
};

class AISkirmishPlayer : public AIPlayer
{
protected:
	virtual Bool startTraining( WorkOrder *order, Bool busyOK, AsciiString teamName );
};

// ?startTraining@AISkirmishPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z
Bool AISkirmishPlayer::startTraining( WorkOrder *order, Bool busyOK, AsciiString teamName)
{
	Int bfmeFactoryArg;								// written by findFactory
	Object *factory = findFactory(order->m_thing, busyOK, &bfmeFactoryArg);
	if( factory )
	{
		ProductionUpdateInterface *pu = factory->getProductionUpdateInterface();
		if (pu && pu->queueCreateUnit( order->m_thing, bfmeFactoryArg, pu->requestUniqueUnitID(), -1, 0 )) {
			order->m_factoryID = factory->getID(); 
			if (TheGlobalData->m_debugAI) {
				AsciiString teamStr = "Queuing ";
				// BFME's AsciiString methods are StringBase<char>'s; calling it directly
				// (not through ascii_string.h's forwarding inline) keeps retail's registers.
				((StringBase<char> *)&teamStr)->concat(*(const StringBase<char> *)&order->m_thing->getName());
				teamStr.concat(" for ");
				teamStr.concat(teamName);
				TheScriptEngine->AppendDebugMessage(teamStr, false);
			}
			return true;
		}
	}  // end if

	return false;

}
