// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RadiusDecalUpdateModuleData
{
public:
	RadiusDecalUpdateModuleData();
	virtual ~RadiusDecalUpdateModuleData();

private:
	int m_pad;
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char RadiusDecalUpdateFieldParse;

class RadiusDecalUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

RadiusDecalUpdateModuleData::RadiusDecalUpdateModuleData()
{
}

// ?friend_newModuleData@RadiusDecalUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *RadiusDecalUpdate::friend_newModuleData(INI *ini)
{
	RadiusDecalUpdateModuleData *data = new RadiusDecalUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &RadiusDecalUpdateFieldParse);
	return (ModuleData *)data;
}
