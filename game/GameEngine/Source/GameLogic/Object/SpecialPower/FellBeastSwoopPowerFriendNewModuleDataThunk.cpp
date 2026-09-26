// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FellBeastSwoopPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FellBeastSwoopPowerModuleData
{
public:
	FellBeastSwoopPowerModuleData();
	virtual ~FellBeastSwoopPowerModuleData();

private:
	unsigned char m_pad[0x258];
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

extern "C" void __cdecl FellBeastSwoopPowerFieldParse(MultiIniFieldParse &parse);

class FellBeastSwoopPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FellBeastSwoopPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FellBeastSwoopPower::friend_newModuleData(INI *ini)
{
	FellBeastSwoopPowerModuleData *data = new FellBeastSwoopPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &FellBeastSwoopPowerFieldParse);
	return (ModuleData *)data;
}
