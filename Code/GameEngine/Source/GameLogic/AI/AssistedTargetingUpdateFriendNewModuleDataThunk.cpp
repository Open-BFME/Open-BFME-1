// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: AssistedTargetingUpdate::friend_newModuleData

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AssistedTargetingUpdateModuleData
{
public:
	AssistedTargetingUpdateModuleData();
	virtual ~AssistedTargetingUpdateModuleData();
private:
	unsigned int m_pad;
	unsigned int m_one;
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AssistedTargetingUpdateFieldParse;

class AssistedTargetingUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

AssistedTargetingUpdateModuleData::AssistedTargetingUpdateModuleData()
{
	m_one = 1;
	m_a = 0;
	m_b = 0;
	m_c = 0;
}

// ?friend_newModuleData@AssistedTargetingUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AssistedTargetingUpdate::friend_newModuleData(INI *ini)
{
	AssistedTargetingUpdateModuleData *data = new AssistedTargetingUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &AssistedTargetingUpdateFieldParse);
	return (ModuleData *)data;
}
