// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SplitHordeSpecialPower::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class SplitHordeSpecialPowerModuleData {
public:
	SplitHordeSpecialPowerModuleData();
	virtual ~SplitHordeSpecialPowerModuleData();
private:
	unsigned char m_pad[0x20C];
};
class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
class INI { public: void initFromINIMultiProc(void *what,
	void (__cdecl *buildFieldParse)(MultiIniFieldParse &)); };
extern "C" void __cdecl SplitHordeSpecialPowerFieldParse(MultiIniFieldParse &parse);
class SplitHordeSpecialPower { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *SplitHordeSpecialPower::friend_newModuleData(INI *ini) {
	SplitHordeSpecialPowerModuleData *data = new SplitHordeSpecialPowerModuleData;
	if (ini) ini->initFromINIMultiProc(data, &SplitHordeSpecialPowerFieldParse);
	return (ModuleData *)data;
}
