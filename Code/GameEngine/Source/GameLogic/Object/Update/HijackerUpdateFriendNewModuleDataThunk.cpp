// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class HijackerUpdateModuleData
{
public:
	HijackerUpdateModuleData();
	virtual ~HijackerUpdateModuleData();

private:
	int m_unused;
	int m_a;
	int m_b;
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char HijackerUpdateFieldParse;

class HijackerUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

HijackerUpdateModuleData::HijackerUpdateModuleData()
	: m_a(0)
	, m_b(0)
{
}

// ?friend_newModuleData@HijackerUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *HijackerUpdate::friend_newModuleData(INI *ini)
{
	HijackerUpdateModuleData *data = new HijackerUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &HijackerUpdateFieldParse);
	return (ModuleData *)data;
}
