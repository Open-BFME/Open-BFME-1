// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// The factory is registered as GateProxyBehavior by ModuleFactory::init
// (0x0012E67A), and the paired retail creator is 0x00123B40.  The original
// BFME header is not present in the vendored tree, so the complete four-table
// ABI is kept local: primary 13 slots, returned Module subobject 11 slots,
// Behavior interface 41 slots, and Update interface 2 slots.  The +4 return
// adjustment is therefore a real secondary-this conversion, not a thunk.
class Thing;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GateProxyPrimaryBase
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12();
};

// Offset +4 in the retail object is the Module-facing secondary subobject.
// Its 11 emitted slots and eight bytes of trailing state preserve the shipped
// object offsets while keeping the missing BFME header out of shared includes.
class Module
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10();

private:
	unsigned char m_pad[8];
};

class GateProxyBehaviorInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40();
};

class GateProxyUpdateInterface
{
public:
	virtual void slot00();
	virtual void slot01();
};

// GateOpenAndCloseBehavior's constructor is already identified and matched at
// 0x001FC580; it initializes this full MI base before GateProxy overwrites its
// four most-derived vtable pointers and its owned proxy field.
class __declspec(novtable) GateOpenAndCloseBehavior
	: public GateProxyPrimaryBase, public Module,
	  public GateProxyBehaviorInterface, public GateProxyUpdateInterface
{
public:
	GateOpenAndCloseBehavior(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x34];
};

class GateProxyBehavior : public GateOpenAndCloseBehavior
{
public:
	GateProxyBehavior(Thing *thing, const ModuleData *data)
		: GateOpenAndCloseBehavior(thing, data), m_gateProxy(0)
	{
	}
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	void *m_gateProxy;
};

// ?friend_newModuleInstance@GateProxyBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *GateProxyBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return new GateProxyBehavior(thing, data);
}
