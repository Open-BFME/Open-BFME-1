// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: BroadcastStealthUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class BroadcastStealthUpdateModuleData
{
public:
	BroadcastStealthUpdateModuleData();
	virtual ~BroadcastStealthUpdateModuleData();

private:
	unsigned char m_pad[0x90]; // vptr+0x90=0x94
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char BroadcastStealthUpdateFieldParse;

class BroadcastStealthUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@BroadcastStealthUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BroadcastStealthUpdate::friend_newModuleData(INI *ini)
{
	BroadcastStealthUpdateModuleData *data = new BroadcastStealthUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &BroadcastStealthUpdateFieldParse);
	return (ModuleData *)data;
}
