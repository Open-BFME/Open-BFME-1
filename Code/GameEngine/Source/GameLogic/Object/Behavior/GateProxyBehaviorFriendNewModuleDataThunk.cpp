// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GateProxyBehavior::friend_newModuleData factory
// Retail: new; base construct; outer vtbl; optional initFromINI.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GateProxyBehaviorModuleDataBaseShim
{
public:
	void construct();
};

class GateProxyBehaviorModuleDataVtbl
{
public:
	GateProxyBehaviorModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x44];
};

class __declspec(novtable) GateProxyBehaviorModuleData
{
public:
	GateProxyBehaviorModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x44];
};

GateProxyBehaviorModuleData::GateProxyBehaviorModuleData()
{
	((GateProxyBehaviorModuleDataBaseShim *)this)->construct();
	((GateProxyBehaviorModuleDataVtbl *)this)->GateProxyBehaviorModuleDataVtbl::GateProxyBehaviorModuleDataVtbl();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GateProxyBehaviorFieldParse;

class GateProxyBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GateProxyBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GateProxyBehavior::friend_newModuleData(INI *ini)
{
	GateProxyBehaviorModuleData *data = new GateProxyBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &GateProxyBehaviorFieldParse);
	return (ModuleData *)data;
}
