// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: TemporarilyDefectUpdate::friend_newModuleData

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class TemporarilyDefectUpdateModuleData
{
public:
	TemporarilyDefectUpdateModuleData();
	virtual ~TemporarilyDefectUpdateModuleData();
private:
	unsigned int m_pad;
	unsigned int m_field;
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char TemporarilyDefectUpdateFieldParse;

class TemporarilyDefectUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

TemporarilyDefectUpdateModuleData::TemporarilyDefectUpdateModuleData()
{
	m_field = 0;
}

// ?friend_newModuleData@TemporarilyDefectUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *TemporarilyDefectUpdate::friend_newModuleData(INI *ini)
{
	TemporarilyDefectUpdateModuleData *data = new TemporarilyDefectUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &TemporarilyDefectUpdateFieldParse);
	return (ModuleData *)data;
}
