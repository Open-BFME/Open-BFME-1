// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RepairSpecialPower::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class RepairSpecialPowerModuleData {
public:
	RepairSpecialPowerModuleData();
	virtual ~RepairSpecialPowerModuleData();
private:
	unsigned char m_pad[0x20C];
};
class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
class INI { public: void initFromINIMultiProc(void *what,
	void (__cdecl *buildFieldParse)(MultiIniFieldParse &)); };
// Retail pushes the ILT stub 0x0003A1DE (?j_0003a1de@@YAXXZ), which jumps to
// the class buildFieldParse at 0x002647C0.
extern void j_0003a1de(void);
class RepairSpecialPower { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *RepairSpecialPower::friend_newModuleData(INI *ini) {
	RepairSpecialPowerModuleData *data = new RepairSpecialPowerModuleData;
	if (ini) ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))j_0003a1de);
	return (ModuleData *)data;
}
