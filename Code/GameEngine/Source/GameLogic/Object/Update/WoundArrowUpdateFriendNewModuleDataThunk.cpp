// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WoundArrowUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class WoundArrowUpdateModuleData
{
public:
	WoundArrowUpdateModuleData();
	virtual ~WoundArrowUpdateModuleData();

private:
	unsigned char m_pad[0x258];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char WoundArrowUpdateFieldParse;

class WoundArrowUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@WoundArrowUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *WoundArrowUpdate::friend_newModuleData(INI *ini)
{
	WoundArrowUpdateModuleData *data = new WoundArrowUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &WoundArrowUpdateFieldParse);
	return (ModuleData *)data;
}
