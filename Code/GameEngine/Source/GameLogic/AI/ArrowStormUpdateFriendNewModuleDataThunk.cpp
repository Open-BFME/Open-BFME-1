// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ArrowStormUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ArrowStormUpdateModuleData
{
public:
	ArrowStormUpdateModuleData();
	virtual ~ArrowStormUpdateModuleData();

private:
	unsigned char m_pad[0x268];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ArrowStormUpdateFieldParse;

class ArrowStormUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ArrowStormUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ArrowStormUpdate::friend_newModuleData(INI *ini)
{
	ArrowStormUpdateModuleData *data = new ArrowStormUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &ArrowStormUpdateFieldParse);
	return (ModuleData *)data;
}
