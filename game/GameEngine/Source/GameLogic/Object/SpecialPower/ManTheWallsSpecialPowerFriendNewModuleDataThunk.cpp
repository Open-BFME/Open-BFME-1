// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ManTheWallsSpecialPower::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class ManTheWallsSpecialPowerModuleData {
public:
	ManTheWallsSpecialPowerModuleData();
	virtual ~ManTheWallsSpecialPowerModuleData();
private:
	unsigned char m_pad[0x20C];
};
class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
class INI { public: void initFromINIMultiProc(void *what,
	void (__cdecl *buildFieldParse)(MultiIniFieldParse &)); };
// Retail stores VA 0x0043EDEC: the matched ILT thunk ?j_0003edec, whose
// target 0x002605F0 is the matched jump stub ?j_002605f0.
void j_0003edec();
class ManTheWallsSpecialPower { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *ManTheWallsSpecialPower::friend_newModuleData(INI *ini) {
	ManTheWallsSpecialPowerModuleData *data = new ManTheWallsSpecialPowerModuleData;
	if (ini) ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))&j_0003edec);
	return (ModuleData *)data;
}
