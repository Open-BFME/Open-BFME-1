// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AttributeModifierAuraUpdate::friend_newModuleData factory.

class INI;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AttributeModifierAuraUpdateModuleData
{
public:
	AttributeModifierAuraUpdateModuleData();
	virtual ~AttributeModifierAuraUpdateModuleData();

private:
	unsigned char m_pad[0xa4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINI(void *what, const void *parseTable);
};

extern "C" char AttributeModifierAuraUpdateFieldParse;

class AttributeModifierAuraUpdate
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AttributeModifierAuraUpdate@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AttributeModifierAuraUpdate::friend_newModuleData(INI *ini)
{
	AttributeModifierAuraUpdateModuleData *data = new AttributeModifierAuraUpdateModuleData;
	if (ini)
		ini->initFromINI(data, &AttributeModifierAuraUpdateFieldParse);
	return (ModuleData *)data;
}
