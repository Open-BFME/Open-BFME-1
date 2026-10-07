// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: StopSpecialPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class StopSpecialPowerModuleData
{
public:
	StopSpecialPowerModuleData();
	virtual ~StopSpecialPowerModuleData();

private:
	unsigned char m_pad[0x210];
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

// The proc operand is ILT 0x0001F67C -> 0x0026B310, the matched
// ?buildFieldParse@Rva0026B310@@SAXAAVWideMulti@@@Z.
void j_0001f67c();

class StopSpecialPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@StopSpecialPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *StopSpecialPower::friend_newModuleData(INI *ini)
{
	StopSpecialPowerModuleData *data = new StopSpecialPowerModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))j_0001f67c);
	return (ModuleData *)data;
}
