// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: SiegeAIUpdate::friend_newModuleData
// Retail SEH factory: new(0x64); ModuleData ctor; optional initFromINI.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeAIUpdateModuleData
{
public:
	SiegeAIUpdateModuleData();
	virtual void dummy();

private:
	unsigned char m_pad[0x60];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char SiegeAIUpdateFieldParse;

class SiegeAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeAIUpdate::friend_newModuleData(INI *ini)
{
	SiegeAIUpdateModuleData *data = new SiegeAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &SiegeAIUpdateFieldParse);
	return (ModuleData *)data;
}
