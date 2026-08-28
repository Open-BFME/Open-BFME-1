// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift ModuleData dtor MASM dump to clean C++.
// Retail SEH dtor stores the derived vftable at entry, destroys two adjacent
// 4-byte string members at this+0x1C then this+0x18 (reverse declaration
// order), then stores the base vftable. Member names are inferred from the
// byte evidence (8 base bytes + four ints + two strings); the body is
// ICF-identical to the DieModuleData dtor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char *m_str;
public:
	~AsciiString();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual ~ModuleData() {}
	unsigned int m_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
class UpgradeModuleData : public ModuleData
{
public:
	virtual ~UpgradeModuleData();

private:
	int m_field08;
	int m_field0c;
	int m_field10;
	int m_field14;
	AsciiString m_upgradeName;
	AsciiString m_upgradeLabel;
};

// ??1UpgradeModuleData@@UAE@XZ
UpgradeModuleData::~UpgradeModuleData()
{
}
