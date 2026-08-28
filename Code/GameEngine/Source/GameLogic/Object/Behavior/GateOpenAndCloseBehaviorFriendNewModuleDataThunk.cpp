// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: GateOpenAndCloseBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class GateOpenAndCloseBehaviorModuleData
{
public:
	GateOpenAndCloseBehaviorModuleData();
	virtual ~GateOpenAndCloseBehaviorModuleData();

private:
	unsigned char m_pad[0x44];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char GateOpenAndCloseBehaviorFieldParse;

class GateOpenAndCloseBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@GateOpenAndCloseBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *GateOpenAndCloseBehavior::friend_newModuleData(INI *ini)
{
	GateOpenAndCloseBehaviorModuleData *data = new GateOpenAndCloseBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &GateOpenAndCloseBehaviorFieldParse);
	return (ModuleData *)data;
}
