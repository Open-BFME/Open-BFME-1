// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ShroudCrateCollide::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ShroudCrateCollideModuleData
{
public:
	ShroudCrateCollideModuleData();
	virtual ~ShroudCrateCollideModuleData();

private:
	unsigned char m_pad[0x50];
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

extern "C" void __cdecl ShroudCrateCollideFieldParse(MultiIniFieldParse &parse);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ShroudCrateCollide.h
class ShroudCrateCollide
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ShroudCrateCollide@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ShroudCrateCollide::friend_newModuleData(INI *ini)
{
	ShroudCrateCollideModuleData *data = new ShroudCrateCollideModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &ShroudCrateCollideFieldParse);
	return (ModuleData *)data;
}
