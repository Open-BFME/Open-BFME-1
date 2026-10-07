// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DeflectSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DeflectSpecialPowerModuleData
{
public:
	DeflectSpecialPowerModuleData();
	virtual ~DeflectSpecialPowerModuleData();

private:
	unsigned char m_pad[0x1CC];
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

// The proc retail passes is VA 0x0044765E, the ILT stub ?j_0004765e@@YAXXZ (jumps to 0x0025A180).
extern void j_0004765e();

class DeflectSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DeflectSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeflectSpecialPower::friend_newModuleData(INI *ini)
{
	DeflectSpecialPowerModuleData *data = new DeflectSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_0004765e);
	return (ModuleData *)data;
}
