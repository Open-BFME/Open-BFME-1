// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeContainModuleData
{
public:
	HordeContainModuleData();
	virtual ~HordeContainModuleData();

private:
	unsigned char m_pad[0x168];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HordeContainFieldParse;

class HordeContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HordeContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeContain::friend_newModuleData(INI *ini)
{
	HordeContainModuleData *data = new HordeContainModuleData;
	if (ini)
		ini->initFromINI(data, &HordeContainFieldParse);
	return (ModuleData *)data;
}
