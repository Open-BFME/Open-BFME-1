// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FlammableUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class FlammableUpdateModuleData
{
public:
	FlammableUpdateModuleData();
	virtual ~FlammableUpdateModuleData();

private:
	unsigned char m_pad[0x50];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char FlammableUpdateFieldParse;

class FlammableUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@FlammableUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *FlammableUpdate::friend_newModuleData(INI *ini)
{
	FlammableUpdateModuleData *data = new FlammableUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &FlammableUpdateFieldParse);
	return (ModuleData *)data;
}
