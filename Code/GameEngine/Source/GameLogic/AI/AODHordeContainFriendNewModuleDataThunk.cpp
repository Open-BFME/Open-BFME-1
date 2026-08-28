// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AODHordeContain::friend_newModuleData factory
// Retail: new; base construct; outer vtbl; optional initFromINI.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AODHordeContainModuleDataBaseShim
{
public:
	void construct();
};

class AODHordeContainModuleDataVtbl
{
public:
	AODHordeContainModuleDataVtbl() {}
	virtual void dummy();

private:
	unsigned char m_pad[0x2F0];
};

class __declspec(novtable) AODHordeContainModuleData
{
public:
	AODHordeContainModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x2F0];
};

AODHordeContainModuleData::AODHordeContainModuleData()
{
	((AODHordeContainModuleDataBaseShim *)this)->construct();
	((AODHordeContainModuleDataVtbl *)this)->AODHordeContainModuleDataVtbl::AODHordeContainModuleDataVtbl();
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AODHordeContainFieldParse;

class AODHordeContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AODHordeContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AODHordeContain::friend_newModuleData(INI *ini)
{
	AODHordeContainModuleData *data = new AODHordeContainModuleData;
	if (ini)
		ini->initFromINI(data, &AODHordeContainFieldParse);
	return (ModuleData *)data;
}
