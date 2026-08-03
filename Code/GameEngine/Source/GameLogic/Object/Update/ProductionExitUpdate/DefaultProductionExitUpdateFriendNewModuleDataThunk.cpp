// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class DefaultProductionExitUpdateModuleData
{
public:
	DefaultProductionExitUpdateModuleData();
	virtual ~DefaultProductionExitUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DefaultProductionExitUpdateFieldParse;

class DefaultProductionExitUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

DefaultProductionExitUpdateModuleData::DefaultProductionExitUpdateModuleData()
{
	m_08 = 0;
	m_0c = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
}

// ?friend_newModuleData@DefaultProductionExitUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DefaultProductionExitUpdate::friend_newModuleData(INI *ini)
{
	DefaultProductionExitUpdateModuleData *data = new DefaultProductionExitUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &DefaultProductionExitUpdateFieldParse);
	return (ModuleData *)data;
}
