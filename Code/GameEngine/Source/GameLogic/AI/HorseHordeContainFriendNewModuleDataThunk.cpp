// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HorseHordeContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HorseHordeContainModuleData
{
public:
	HorseHordeContainModuleData();
	virtual ~HorseHordeContainModuleData();

private:
	unsigned char m_pad[0x2f0];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HorseHordeContainFieldParse;

class HorseHordeContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HorseHordeContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HorseHordeContain::friend_newModuleData(INI *ini)
{
	HorseHordeContainModuleData *data = new HorseHordeContainModuleData;
	if (ini)
		ini->initFromINI(data, &HorseHordeContainFieldParse);
	return (ModuleData *)data;
}
