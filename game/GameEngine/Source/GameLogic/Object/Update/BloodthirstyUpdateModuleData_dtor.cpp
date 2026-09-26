// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: BloodthirstyUpdateModuleData destructor at retail 0x00287380,
// 96 bytes. The exact constructor at 0x00286EC0 establishes the same
// three-member layout and dedicated vtable 0x010BC6B8. Its EH-unwind shape has
// 3 tracked members and the same
// installed vtable slot as BaseUpgradeModuleDataDestructorThunk.cpp's
// ~BaseUpgradeModuleData, but the trailing members are two AudioEventRTS
// (ILT 0x00026F35, see Audio/AudioEventRTSCopyAndLifetime.cpp) plus a small non-trivial
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS // non-virtual local view: matches ledger name QAE for the pinned callee
{
public:
	~AudioEventRTS();

private:
	char m_pad[0x70];
};

class __declspec(novtable) BloodthirstyUpdateModuleData
	: public BaseUpgradeModuleDataPrimaryBase
{
public:
	virtual ~BloodthirstyUpdateModuleData();

private:
	AttributeModifierAuraUpdateModuleDataMemberC m_08;
	AudioEventRTS m_10;
	AudioEventRTS m_80;
};

// ??1BloodthirstyUpdateModuleData@@UAE@XZ
BloodthirstyUpdateModuleData::~BloodthirstyUpdateModuleData()
{
}
