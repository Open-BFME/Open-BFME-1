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
// Retail pushes the ILT thunk in front of this class's buildFieldParse body,
// 0x00405245 = `jmp 0x0064B6E0`, which the ledger owns as the ILT thunk row
// ?j_00005245@@YAXXZ, so the reference names that row. The real
// buildFieldParse body behind that second thunk is still unclaimed.
void __cdecl j_00005245(); // ?j_00005245@@YAXXZ, ILT 0x00405245
class HordeGarrisonContain { public: static ModuleData *friend_newModuleData(INI *ini); };
ModuleData *HordeGarrisonContain::friend_newModuleData(INI *ini) {
	HordeGarrisonContainModuleData *data = new HordeGarrisonContainModuleData;
	if (ini) ini->initFromINIMultiProc(data, reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_00005245));
	return (ModuleData *)data;
}
