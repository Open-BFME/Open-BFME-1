// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CleanupAreaPower::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CashBountyPowerModuleData
{
public:
	CashBountyPowerModuleData();
	virtual ~CashBountyPowerModuleData();

private:
	unsigned char m_pad[0x74];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char CleanupAreaPowerFieldParse;

class CleanupAreaPower
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@CleanupAreaPower@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *CleanupAreaPower::friend_newModuleData(INI *ini)
{
	CashBountyPowerModuleData *data = new CashBountyPowerModuleData;
	if (ini)
		ini->initFromINI(data, &CleanupAreaPowerFieldParse);
	return (ModuleData *)data;
}
