// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeSoundSelectorClientBehavior::friend_newModuleData factory.


class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class UpgradeSoundSelectorClientBehaviorModuleData
{
public:
	UpgradeSoundSelectorClientBehaviorModuleData();
	virtual ~UpgradeSoundSelectorClientBehaviorModuleData();

private:
	unsigned char m_pad[0x10];
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

// Retail pushes VA 0x004151A9, the five-byte ILT thunk at RVA 0x000151A9,
// which jumps to the matched address-derived 17-byte table-register
// forwarder ?Rva00609130@@YAXPAVGen00850920@@@Z (body 0x00609130 in
// Common/MidTableRegisterForwarders.cpp, registering .rdata table 0x01115A9C);
// its Gen00850920 receiver is that row's spelling, so the proc is cast to the
// initFromINIMultiProc parameter type.
// Naming that defined, matched body (instead of an undefined alias) lets the
// reference link; the pushed operand is a relocation either way.
class Gen00850920;
void Rva00609130(Gen00850920 *receiver);
typedef void (__cdecl *UpgradeSoundSelectorClientBehaviorBuildFieldParse)(MultiIniFieldParse &);

class UpgradeSoundSelectorClientBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@UpgradeSoundSelectorClientBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *UpgradeSoundSelectorClientBehavior::friend_newModuleData(INI *ini)
{
	UpgradeSoundSelectorClientBehaviorModuleData *data = new UpgradeSoundSelectorClientBehaviorModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			(UpgradeSoundSelectorClientBehaviorBuildFieldParse)Rva00609130);
	return (ModuleData *)data;
}
