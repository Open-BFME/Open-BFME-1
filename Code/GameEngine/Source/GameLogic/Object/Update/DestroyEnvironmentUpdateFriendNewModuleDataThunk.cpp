// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DestroyEnvironmentUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DestroyEnvironmentUpdateModuleData
{
public:
	DestroyEnvironmentUpdateModuleData();
	virtual ~DestroyEnvironmentUpdateModuleData();

private:
	unsigned char m_pad[0xc];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DestroyEnvironmentUpdateFieldParse;

class DestroyEnvironmentUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DestroyEnvironmentUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DestroyEnvironmentUpdate::friend_newModuleData(INI *ini)
{
	DestroyEnvironmentUpdateModuleData *data = new DestroyEnvironmentUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &DestroyEnvironmentUpdateFieldParse);
	return (ModuleData *)data;
}
