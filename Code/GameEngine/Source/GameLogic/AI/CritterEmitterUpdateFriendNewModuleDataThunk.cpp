// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CritterEmitterUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CritterEmitterUpdateModuleData
{
public:
	CritterEmitterUpdateModuleData();
	virtual ~CritterEmitterUpdateModuleData();

private:
	unsigned char m_pad[0xdc];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char CritterEmitterUpdateFieldParse;

class CritterEmitterUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CritterEmitterUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CritterEmitterUpdate::friend_newModuleData(INI *ini)
{
	CritterEmitterUpdateModuleData *data = new CritterEmitterUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &CritterEmitterUpdateFieldParse);
	return (ModuleData *)data;
}
