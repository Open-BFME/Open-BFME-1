// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDockingBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class SiegeDockingBehaviorModuleData
{
public:
	SiegeDockingBehaviorModuleData();
	virtual ~SiegeDockingBehaviorModuleData();

private:
	unsigned char m_pad[0x8];
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

extern "C" void __cdecl SiegeDockingBehaviorFieldParse(MultiIniFieldParse &parse);

class SiegeDockingBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@SiegeDockingBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *SiegeDockingBehavior::friend_newModuleData(INI *ini)
{
	SiegeDockingBehaviorModuleData *data = new SiegeDockingBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, &SiegeDockingBehaviorFieldParse);
	return (ModuleData *)data;
}
