// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BezierProjectileBehavior::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BezierProjectileBehaviorModuleData
{
public:
	BezierProjectileBehaviorModuleData();
	virtual ~BezierProjectileBehaviorModuleData();

private:
	unsigned char m_pad[0xa8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char BezierProjectileBehaviorFieldParse;

class BezierProjectileBehavior
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BezierProjectileBehavior@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BezierProjectileBehavior::friend_newModuleData(INI *ini)
{
	BezierProjectileBehaviorModuleData *data = new BezierProjectileBehaviorModuleData;
	if (ini)
		ini->initFromINI(data, &BezierProjectileBehaviorFieldParse);
	return (ModuleData *)data;
}
