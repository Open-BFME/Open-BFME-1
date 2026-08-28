// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ClearanceTestingSlowDeathBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class ClearanceTestingSlowDeathBehaviorModuleData
{
public:
	ClearanceTestingSlowDeathBehaviorModuleData();
	virtual ~ClearanceTestingSlowDeathBehaviorModuleData();

private:
	unsigned char m_pad[0x21c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char ClearanceTestingSlowDeathBehaviorFieldParse;

class ClearanceTestingSlowDeathBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@ClearanceTestingSlowDeathBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *ClearanceTestingSlowDeathBehavior::friend_newModuleData(INI *ini)
{
	ClearanceTestingSlowDeathBehaviorModuleData *data = new ClearanceTestingSlowDeathBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &ClearanceTestingSlowDeathBehaviorFieldParse);
	return (ModuleData *)data;
}
