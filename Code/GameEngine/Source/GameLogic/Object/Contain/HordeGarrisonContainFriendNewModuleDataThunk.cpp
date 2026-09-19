// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeGarrisonContain::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
class HordeGarrisonContainModuleData {
public:
	HordeGarrisonContainModuleData();
	virtual ~HordeGarrisonContainModuleData();
private:
	unsigned char m_pad[0x220];
};
class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
class INI { public: void initFromINIMultiProc(void *what,
	void (__cdecl *buildFieldParse)(MultiIniFieldParse &)); };
extern "C" void __cdecl HordeGarrisonContainFieldParse(MultiIniFieldParse &parse);
class HordeGarrisonContain { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *HordeGarrisonContain::friend_newModuleData(INI *ini) {
	HordeGarrisonContainModuleData *data = new HordeGarrisonContainModuleData;
	if (ini) ini->initFromINIMultiProc(data, &HordeGarrisonContainFieldParse);
	return (ModuleData *)data;
}
