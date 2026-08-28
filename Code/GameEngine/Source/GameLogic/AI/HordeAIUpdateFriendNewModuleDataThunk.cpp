// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: HordeAIUpdate::friend_newModuleData
// Retail: new(0x64); base construct; outer vtbl; optional initFromINI.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeAIUpdateModuleDataBaseShim
{
public:
	void construct();
};

class HordeAIUpdateModuleDataVtbl
{
public:
	HordeAIUpdateModuleDataVtbl()
	{
	}
	virtual void dummy();

private:
	unsigned char m_pad[0x60];
};

class __declspec(novtable) HordeAIUpdateModuleData
{
public:
	HordeAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x60];
};

HordeAIUpdateModuleData::HordeAIUpdateModuleData()
{
	((HordeAIUpdateModuleDataBaseShim *)this)->construct();
	((HordeAIUpdateModuleDataVtbl *)this)
		->HordeAIUpdateModuleDataVtbl::HordeAIUpdateModuleDataVtbl();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HordeAIUpdateFieldParse;

class HordeAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HordeAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeAIUpdate::friend_newModuleData(INI *ini)
{
	HordeAIUpdateModuleData *data = new HordeAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &HordeAIUpdateFieldParse);
	return (ModuleData *)data;
}
