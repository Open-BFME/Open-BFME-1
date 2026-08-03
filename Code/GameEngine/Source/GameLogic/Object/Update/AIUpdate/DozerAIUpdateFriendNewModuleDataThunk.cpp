// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DozerAIUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class JetAIUpdateModuleData
{
public:
	JetAIUpdateModuleData();
	virtual ~JetAIUpdateModuleData();

private:
	unsigned char m_pad[0x6c];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DozerAIUpdateFieldParse;

class DozerAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DozerAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DozerAIUpdate::friend_newModuleData(INI *ini)
{
	JetAIUpdateModuleData *data = new JetAIUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &DozerAIUpdateFieldParse);
	return (ModuleData *)data;
}
