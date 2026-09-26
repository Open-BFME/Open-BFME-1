// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GrabPassengerSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GrabPassengerSpecialPowerModuleData
{
public:
	GrabPassengerSpecialPowerModuleData();
	virtual ~GrabPassengerSpecialPowerModuleData();

private:
	unsigned char m_pad[0x214];
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

extern "C" void __cdecl GrabPassengerSpecialPowerFieldParse(MultiIniFieldParse &parse);

class GrabPassengerSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GrabPassengerSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GrabPassengerSpecialPower::friend_newModuleData(INI *ini)
{
	GrabPassengerSpecialPowerModuleData *data = new GrabPassengerSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &GrabPassengerSpecialPowerFieldParse);
	return (ModuleData *)data;
}
