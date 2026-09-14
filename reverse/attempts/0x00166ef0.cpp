// ?startTraining@AIPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z
// partial score=0.96 date=2026-09-13
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// AIPlayer::startTraining, retail 0x00166EF0.
//
// The caller at AIPlayer::doTeamBuilding passes a WorkOrder and its team name.
// The three-argument findFactory body at 0x001643B0 proves the BFME build-index
// output used by this method. The debug string and the queue result identify the
// method independently of the address-derived source file.

typedef bool Bool;
typedef int Int;

template <typename T> struct StringInlineData
{
	Int m_refCount;
	Int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();
	void concat(const StringBase<T> &other);
	void concat(const T *text);

private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	__forceinline AsciiString(const char *text) : StringBase<char>(text) {}
	__forceinline AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	__forceinline ~AsciiString() {}

	__forceinline void concat(const AsciiString &other)
	{
		((StringBase<char> *)this)->concat((const StringBase<char> &)other);
	}
	__forceinline void concat(const char *text)
	{
		((StringBase<char> *)this)->concat(text);
	}
};

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

#pragma comment(linker, "/alternatename:?findFactory@AIPlayer@@IAEPAVObject@@PBVThingTemplate@@_NPAH@Z=?j_0002b62f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getProductionUpdateInterface@Object@@QAEPAVProductionUpdateInterface@@XZ=?j_00003b52@@YAXXZ")
#pragma comment(linker, "/alternatename:?AppendDebugMessage@ScriptEngine@@QAEXABVAsciiString@@_N@Z=?j_00028ce0@@YAXXZ")

// ?startTraining@AIPlayer@@MAE_NPAVWorkOrder@@_NVAsciiString@@@Z
Bool AIPlayer::startTraining(WorkOrder *order, Bool busyOK, AsciiString teamName)
{
	Int factoryID;
	Object *factory;
	ProductionUpdateInterface *pu;
	Bool busy = busyOK;
	factory = findFactory(order->m_thing, busy, &factoryID);
	if (factory != 0)
	{
		pu = factory->getProductionUpdateInterface();
		if (pu != 0 && pu->queueCreateUnit(order->m_thing,
			*(const void **)&teamName,
			pu->requestUniqueUnitID(-1, 0)))
		{
			order->m_factoryID = factory->getID();
			if (TheGlobalData->m_debugAI)
			{
				AsciiString teamStr = "Queuing ";
				teamStr.concat(order->m_thing->getName());
				teamStr.concat(" for ");
				const AsciiString *name = &teamName;
				teamStr.concat(*name);
				TheScriptEngine->AppendDebugMessage(teamStr, false);
			}
			return true;
		}
	}
	return false;
}
