// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RubbleRiseUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RubbleRiseUpdateModuleData
{
public:
	RubbleRiseUpdateModuleData();
	virtual ~RubbleRiseUpdateModuleData();

private:
	unsigned char m_pad[0xd0];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RubbleRiseUpdateFieldParse;

class RubbleRiseUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RubbleRiseUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RubbleRiseUpdate::friend_newModuleData(INI *ini)
{
	RubbleRiseUpdateModuleData *data = new RubbleRiseUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &RubbleRiseUpdateFieldParse);
	return (ModuleData *)data;
}
