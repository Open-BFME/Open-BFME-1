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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl SiegeAIUpdateFieldParse(MultiIniFieldParse &parse);

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
		ini->initFromINIMultiProc(data, &SiegeAIUpdateFieldParse);
	return (ModuleData *)data;
}
