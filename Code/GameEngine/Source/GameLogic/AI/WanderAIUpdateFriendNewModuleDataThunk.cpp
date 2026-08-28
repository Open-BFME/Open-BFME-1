// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WanderAIUpdate::friend_newModuleData factory
// Retail: new; base construct; outer vtbl; trailing field inits; optional initFromINI.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WanderAIUpdateModuleDataBaseShim
{
public:
	void construct();
};

class WanderAIUpdateModuleDataVtbl
{
public:
	WanderAIUpdateModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x6C];
};

class __declspec(novtable) WanderAIUpdateModuleData
{
public:
	WanderAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x6C];
};

WanderAIUpdateModuleData::WanderAIUpdateModuleData()
{
	((WanderAIUpdateModuleDataBaseShim *)this)->construct();
	((WanderAIUpdateModuleDataVtbl *)this)->WanderAIUpdateModuleDataVtbl::WanderAIUpdateModuleDataVtbl();
	*((unsigned char *)this + 0x64) = 0;
	*(unsigned int *)((char *)this + 0x68) = 0xFFFFFFFF;
	*((unsigned char *)this + 0x6C) = 1;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char WanderAIUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WanderAIUpdate.h
class WanderAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *WanderAIUpdate::friend_newModuleData(INI *ini)
{
	WanderAIUpdateModuleData *data = new WanderAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &WanderAIUpdateFieldParse);
	return (ModuleData *)data;
}
