// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LifetimeUpdate::friend_newModuleData factory

class INI;
class ModuleData;
void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/LifetimeUpdate.h
class LifetimeUpdateModuleData {
public:
	LifetimeUpdateModuleData();
	virtual ~LifetimeUpdateModuleData();
private:
	unsigned char m_pad[0x14];
};
class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
class INI { public: void initFromINIMultiProc(void *what,
	void (__cdecl *buildFieldParse)(MultiIniFieldParse &)); };
extern "C" void __cdecl LifetimeUpdateFieldParse(MultiIniFieldParse &parse);
class LifetimeUpdate { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *LifetimeUpdate::friend_newModuleData(INI *ini) {
	LifetimeUpdateModuleData *data = new LifetimeUpdateModuleData;
	if (ini) ini->initFromINIMultiProc(data, &LifetimeUpdateFieldParse);
	return (ModuleData *)data;
}
