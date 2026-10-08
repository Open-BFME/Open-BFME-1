// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HordeContainModuleData
{
public:
	HordeContainModuleData();
	virtual ~HordeContainModuleData();

private:
	unsigned char m_pad[0x168];
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

// Retail pushes the ILT thunk in front of this class's buildFieldParse body,
// 0x0043DE29 = `jmp 0x00620160`, which the ledger owns as
// ?j_0003de29@@YAXXZ (game/gen_small/gthunks_069.cpp). The body it jumps to
// (RVA 0x00220160) is still unclaimed, so name the thunk: nothing defines a
// HordeContainFieldParse symbol at link time.
extern "C" void __cdecl __identifier("HordeContainFieldParse")(MultiIniFieldParse &parse);

class HordeContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HordeContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HordeContain::friend_newModuleData(INI *ini)
{
	HordeContainModuleData *data = new HordeContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &__identifier("HordeContainFieldParse"));
	return (ModuleData *)data;
}
