// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HeroModeSpecialAbilityUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HeroModeSpecialAbilityUpdateModuleData
{
public:
	HeroModeSpecialAbilityUpdateModuleData();
	virtual ~HeroModeSpecialAbilityUpdateModuleData();

private:
	unsigned char m_pad[0x25c];
};

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl HeroModeSpecialAbilityUpdateFieldParse(MultiIniFieldParse &parse);

class HeroModeSpecialAbilityUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HeroModeSpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HeroModeSpecialAbilityUpdate::friend_newModuleData(INI *ini)
{
	HeroModeSpecialAbilityUpdateModuleData *data = new HeroModeSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &HeroModeSpecialAbilityUpdateFieldParse);
	return (ModuleData *)data;
}
