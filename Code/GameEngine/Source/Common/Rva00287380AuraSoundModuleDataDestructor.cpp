// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: BaseUpgradeModuleData-shaped destructor sibling at retail
// 0x00287380, 96 bytes. Same EH-unwind shape (3 tracked members) and same
// installed vtable slot as BaseUpgradeModuleDataDestructorThunk.cpp's
// ~BaseUpgradeModuleData, but the trailing members are two AudioEventRTS
// (ILT 0x00026F35, see Audio/AudioEventRTSDtor.cpp) plus a small non-trivial
// member whose destructor is pinned as
// ??1AttributeModifierAuraUpdateModuleDataMemberC@@QAE@XZ.

class BaseUpgradeModuleDataPrimaryBase
{
public:
	virtual ~BaseUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_04;
};

class AttributeModifierAuraUpdateModuleDataMemberC
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberC();

private:
	unsigned int m_data[2];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS // non-virtual local view: matches ledger name QAE for the pinned callee
{
public:
	~AudioEventRTS();

private:
	char m_pad[0x70];
};

class __declspec(novtable) Rva00287380AuraSoundModuleData
	: public BaseUpgradeModuleDataPrimaryBase
{
public:
	virtual ~Rva00287380AuraSoundModuleData();

private:
	AttributeModifierAuraUpdateModuleDataMemberC m_08;
	AudioEventRTS m_10;
	AudioEventRTS m_80;
};

// ??1Rva00287380AuraSoundModuleData@@UAE@XZ
Rva00287380AuraSoundModuleData::~Rva00287380AuraSoundModuleData()
{
}
