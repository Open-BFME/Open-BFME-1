// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RespawnBody::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RespawnBodyModuleData
{
public:
	RespawnBodyModuleData();
	virtual ~RespawnBodyModuleData();

private:
	unsigned char m_pad[0x60];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RespawnBodyFieldParse;

class RespawnBody
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RespawnBody@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RespawnBody::friend_newModuleData(INI *ini)
{
	RespawnBodyModuleData *data = new RespawnBodyModuleData;
	if (ini)
		ini->initFromINI(data, &RespawnBodyFieldParse);
	return (ModuleData *)data;
}
