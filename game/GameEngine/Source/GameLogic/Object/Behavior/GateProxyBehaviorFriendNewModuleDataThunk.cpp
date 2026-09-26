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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl GateProxyBehaviorFieldParse(MultiIniFieldParse &parse);

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
		ini->initFromINIMultiProc(data, &GateProxyBehaviorFieldParse);
	return (ModuleData *)data;
}
