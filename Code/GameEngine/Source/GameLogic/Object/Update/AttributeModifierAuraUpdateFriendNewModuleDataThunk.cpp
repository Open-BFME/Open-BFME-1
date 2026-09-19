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

class MultiIniFieldParse;

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc; the
// FieldParse-table overload this TU used to name lives at 0x008520A0.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

extern "C" void __cdecl AttributeModifierAuraUpdateFieldParse(MultiIniFieldParse &parse);

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
		ini->initFromINIMultiProc(data, &AttributeModifierAuraUpdateFieldParse);
	return (ModuleData *)data;
}
