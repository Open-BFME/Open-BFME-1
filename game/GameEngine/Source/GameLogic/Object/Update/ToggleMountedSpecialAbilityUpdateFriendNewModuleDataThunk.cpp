// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ToggleMountedSpecialAbilityUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ToggleMountedSpecialAbilityUpdateModuleData
{
public:
	ToggleMountedSpecialAbilityUpdateModuleData();
	virtual ~ToggleMountedSpecialAbilityUpdateModuleData();

private:
	unsigned char m_pad[0x258];
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

// Retail pushes the ILT stub 0x00046EAC (?j_00046eac@@YAXXZ).
extern void j_00046eac(void);

class ToggleMountedSpecialAbilityUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ToggleMountedSpecialAbilityUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ToggleMountedSpecialAbilityUpdate::friend_newModuleData(INI *ini)
{
	ToggleMountedSpecialAbilityUpdateModuleData *data = new ToggleMountedSpecialAbilityUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, (void (__cdecl *)(MultiIniFieldParse &))j_00046eac);
	return (ModuleData *)data;
}
