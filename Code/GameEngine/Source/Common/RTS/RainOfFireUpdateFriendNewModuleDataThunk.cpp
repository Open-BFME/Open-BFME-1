// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RainOfFireUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RainOfFireUpdateModuleData
{
public:
	RainOfFireUpdateModuleData();
	virtual ~RainOfFireUpdateModuleData();

private:
	unsigned char m_pad[0x2c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RainOfFireUpdateFieldParse;

class RainOfFireUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@RainOfFireUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RainOfFireUpdate::friend_newModuleData(INI *ini)
{
	RainOfFireUpdateModuleData *data = new RainOfFireUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &RainOfFireUpdateFieldParse);
	return (ModuleData *)data;
}
