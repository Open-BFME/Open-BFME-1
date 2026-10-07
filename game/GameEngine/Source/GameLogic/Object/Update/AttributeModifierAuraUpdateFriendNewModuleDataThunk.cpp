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
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

// Retail pushes 0x247F8, the ILT thunk to the matched builder at 0x002800A0
// (?buildFieldParse@Rva002800A0@@SAXAAVWideMulti@@@Z).
extern void j_000247f8(void);

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
		ini->initFromINIMultiProc(data, 
			reinterpret_cast<void (__cdecl *)(MultiIniFieldParse &)>(&j_000247f8));
	return (ModuleData *)data;
}
