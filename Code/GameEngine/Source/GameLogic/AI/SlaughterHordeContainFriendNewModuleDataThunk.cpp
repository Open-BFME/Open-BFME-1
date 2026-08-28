// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SlaughterHordeContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SlaughterHordeContainModuleData
{
public:
	SlaughterHordeContainModuleData();
	virtual ~SlaughterHordeContainModuleData();

private:
	unsigned char m_pad[0x314];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SlaughterHordeContainFieldParse;

class SlaughterHordeContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SlaughterHordeContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SlaughterHordeContain::friend_newModuleData(INI *ini)
{
	SlaughterHordeContainModuleData *data = new SlaughterHordeContainModuleData;
	if (ini)
		ini->initFromINI(data, &SlaughterHordeContainFieldParse);
	return (ModuleData *)data;
}
