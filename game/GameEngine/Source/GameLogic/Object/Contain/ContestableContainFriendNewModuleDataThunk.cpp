// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ContestableContain::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ContestableContainModuleData
{
public:
	ContestableContainModuleData();
	virtual ~ContestableContainModuleData();

private:
	unsigned char m_pad[0x1a4];
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
// 0x00415654 = `jmp 0x00648F00`, which the ledger owns as
// ?j_00015654@@YAXXZ (game/gen_small/thunks_009.cpp). The body it jumps to
// (RVA 0x00248F00) is still unclaimed, so name the thunk: nothing defines a
// ContestableContainFieldParse symbol at link time.
extern "C" void __cdecl __identifier("?j_00015654@@YAXXZ")(MultiIniFieldParse &parse);

class ContestableContain
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ContestableContain@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ContestableContain::friend_newModuleData(INI *ini)
{
	ContestableContainModuleData *data = new ContestableContainModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &__identifier("?j_00015654@@YAXXZ"));
	return (ModuleData *)data;
}
