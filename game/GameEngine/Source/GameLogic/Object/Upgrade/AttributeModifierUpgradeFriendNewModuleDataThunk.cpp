// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: AttributeModifierUpgrade::friend_newModuleData
// Retail: new(0x74); sub-ctor at +8; outer vtbl; dword +0x70 = 0.

class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char opaque[0x68];
};

// The outer vftable store and +0x70 clear retail inlines here; the real
// ??0AttributeModifierUpgradeModuleData@@QAE@XZ lives in
// AttributeModifierUpgradeModuleDataCtorThunk.cpp, so this TU writes the
// fields through a plain view instead of emitting a second constructor.
extern "C" const char __identifier("??_7AttributeModifierUpgradeModuleData@@6B@")[];
struct AttributeModifierUpgradeModuleDataView
{
	const void *m_vtbl;
	int m_pad;
	char m_sub_space[0x68];
	unsigned int m_extra;
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

extern "C" void __cdecl AttributeModifierUpgradeFieldParse(MultiIniFieldParse &parse);

class AttributeModifierUpgrade
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

// ?friend_newModuleData@AttributeModifierUpgrade@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *AttributeModifierUpgrade::friend_newModuleData(INI *ini)
{
	AttributeModifierUpgradeModuleDataView *data =
		(AttributeModifierUpgradeModuleDataView *)operator new(0x74);
	if (data)
	{
		UpgradeModuleDataSub *sub =
			(UpgradeModuleDataSub *)((char *)data + 8);
		sub->UpgradeModuleDataSub::UpgradeModuleDataSub();
		data->m_vtbl = __identifier("??_7AttributeModifierUpgradeModuleData@@6B@");
		data->m_extra = 0;
	}
	else
		data = 0;
	if (ini)
		ini->initFromINIMultiProc(data, &AttributeModifierUpgradeFieldParse);
	return (ModuleData *)data;
}
