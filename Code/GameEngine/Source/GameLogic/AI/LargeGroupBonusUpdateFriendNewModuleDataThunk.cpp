// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LargeGroupBonusUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class LargeGroupBonusUpdateModuleData
{
public:
	LargeGroupBonusUpdateModuleData();
	virtual ~LargeGroupBonusUpdateModuleData();

private:
	unsigned char m_pad[0x2c];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char LargeGroupBonusUpdateFieldParse;

class LargeGroupBonusUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@LargeGroupBonusUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *LargeGroupBonusUpdate::friend_newModuleData(INI *ini)
{
	LargeGroupBonusUpdateModuleData *data = new LargeGroupBonusUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &LargeGroupBonusUpdateFieldParse);
	return (ModuleData *)data;
}
