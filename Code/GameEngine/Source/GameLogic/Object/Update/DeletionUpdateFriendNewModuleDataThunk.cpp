// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: DeletionUpdate::friend_newModuleData

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h
class DeletionUpdateModuleData
{
public:
	DeletionUpdateModuleData();
	virtual ~DeletionUpdateModuleData();
private:
	unsigned int m_pad;
	unsigned int m_a;
	unsigned int m_b;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DeletionUpdateFieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DeletionUpdate.h
class DeletionUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

DeletionUpdateModuleData::DeletionUpdateModuleData()
{
	m_a = 0;
	m_b = 0;
}

// ?friend_newModuleData@DeletionUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeletionUpdate::friend_newModuleData(INI *ini)
{
	DeletionUpdateModuleData *data = new DeletionUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &DeletionUpdateFieldParse);
	return (ModuleData *)data;
}
