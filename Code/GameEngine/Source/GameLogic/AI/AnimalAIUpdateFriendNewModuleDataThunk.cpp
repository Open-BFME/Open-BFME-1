// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AnimalAIUpdate::friend_newModuleData factory.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AnimalAIUpdateModuleDataBaseShim
{
public:
	void construct();
};

class AnimalAIUpdateModuleDataVtbl
{
public:
	AnimalAIUpdateModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x7c];
};

class __declspec(novtable) AnimalAIUpdateModuleData
{
public:
	AnimalAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x7c];
};

AnimalAIUpdateModuleData::AnimalAIUpdateModuleData()
{
	((AnimalAIUpdateModuleDataBaseShim *)this)->construct();
	((AnimalAIUpdateModuleDataVtbl *)this)
		->AnimalAIUpdateModuleDataVtbl::AnimalAIUpdateModuleDataVtbl();
	unsigned int ten = 10;
	*(unsigned int *)((char *)this + 0x64) = 0x14;
	*(unsigned int *)((char *)this + 0x68) = 0x64;
	*(unsigned int *)((char *)this + 0x6c) = 0x32;
	*(unsigned int *)((char *)this + 0x70) = ten;
	*(unsigned int *)((char *)this + 0x74) = ten;
	*(unsigned int *)((char *)this + 0x78) = ten;
	*((unsigned char *)this + 0x7c) = 1;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AnimalAIUpdateFieldParse;

class AnimalAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AnimalAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AnimalAIUpdate::friend_newModuleData(INI *ini)
{
	AnimalAIUpdateModuleData *data = new AnimalAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &AnimalAIUpdateFieldParse);
	return (ModuleData *)data;
}
