// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeSiegeEngineContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeSiegeEngineContainModuleData
{
public:
	HordeSiegeEngineContainModuleData();
	virtual ~HordeSiegeEngineContainModuleData();

private:
	unsigned char m_pad[0x248];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HordeSiegeEngineContainFieldParse;

class HordeSiegeEngineContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HordeSiegeEngineContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeSiegeEngineContain::friend_newModuleData(INI *ini)
{
	HordeSiegeEngineContainModuleData *data = new HordeSiegeEngineContainModuleData;
	if (ini)
		ini->initFromINI(data, &HordeSiegeEngineContainFieldParse);
	return (ModuleData *)data;
}
