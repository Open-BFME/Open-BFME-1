// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DefectorSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DefectorSpecialPower.h
class DefectorSpecialPowerModuleData
{
public:
	DefectorSpecialPowerModuleData();
	virtual ~DefectorSpecialPowerModuleData();

private:
	unsigned char m_pad[0x210];
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

extern "C" void __cdecl DefectorSpecialPowerFieldParse(MultiIniFieldParse &parse);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DefectorSpecialPower.h
class DefectorSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DefectorSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DefectorSpecialPower::friend_newModuleData(INI *ini)
{
	DefectorSpecialPowerModuleData *data = new DefectorSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &DefectorSpecialPowerFieldParse);
	return (ModuleData *)data;
}
