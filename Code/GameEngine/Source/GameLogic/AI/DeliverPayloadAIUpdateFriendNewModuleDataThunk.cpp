// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: DeliverPayloadAIUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class CostModifierUpgradeModuleData
{
public:
	CostModifierUpgradeModuleData();
	virtual ~CostModifierUpgradeModuleData();

private:
	unsigned char m_pad[0x70];
};

class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char DeliverPayloadAIUpdateFieldParse;

class DeliverPayloadAIUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@DeliverPayloadAIUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *DeliverPayloadAIUpdate::friend_newModuleData(INI *ini)
{
	CostModifierUpgradeModuleData *data = new CostModifierUpgradeModuleData;
	if (ini)
		ini->initFromINI(data, &DeliverPayloadAIUpdateFieldParse);
	return (ModuleData *)data;
}
