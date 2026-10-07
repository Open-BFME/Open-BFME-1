// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HitReactionBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HitReactionBehaviorModuleData
{
public:
	HitReactionBehaviorModuleData();
	virtual ~HitReactionBehaviorModuleData();

private:
	unsigned char m_pad[0x2c];
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

// Retail pushes 0x0040E926, the matched ILT thunk to 0x002919E0.
extern void j_0000e926(void);

class HitReactionBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@HitReactionBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HitReactionBehavior::friend_newModuleData(INI *ini)
{
	HitReactionBehaviorModuleData *data = new HitReactionBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, 
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_0000e926));
	return (ModuleData *)data;
}
