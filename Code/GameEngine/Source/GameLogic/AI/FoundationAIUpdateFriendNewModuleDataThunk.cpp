// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: FoundationAIUpdate::friend_newModuleData

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FoundationAIUpdateModuleData
{
public:
	FoundationAIUpdateModuleData();
	virtual ~FoundationAIUpdateModuleData();
private:
	unsigned int m_pad;
	unsigned int m_field;
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char FoundationAIUpdateFieldParse;

class FoundationAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

FoundationAIUpdateModuleData::FoundationAIUpdateModuleData()
{
	m_field = 0;
}

// ?friend_newModuleData@FoundationAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FoundationAIUpdate::friend_newModuleData(INI *ini)
{
	FoundationAIUpdateModuleData *data = new FoundationAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &FoundationAIUpdateFieldParse);
	return (ModuleData *)data;
}
