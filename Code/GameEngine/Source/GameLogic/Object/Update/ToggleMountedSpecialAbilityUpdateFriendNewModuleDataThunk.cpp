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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ToggleMountedSpecialAbilityUpdateFieldParse;

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
		ini->initFromINI(data, &ToggleMountedSpecialAbilityUpdateFieldParse);
	return (ModuleData *)data;
}
