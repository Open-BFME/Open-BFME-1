// cl: /DNDEBUG /MD /EHsc

// A ModuleData base supplying the vptr, then a member whose constructor is out
// of line -- the call resolves to the existing pin for ??0RS_Member@@QAE@XZ at
// 0x0003747A. That member is what gives this constructor its EH frame.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();		///< vptr at 0x00

	// Declared so the base is destructible: without it MSVC emits no EH frame,
	// because a throw from the member's constructor would have nothing to unwind.
	~ModuleData();

	int m_04;
};

class RS_Member
{
public:
	RS_Member();
	~RS_Member();

private:
	unsigned char m_body[0x18];
};

class ShareExperienceBehaviorModuleData : public ModuleData
{
public:
	ShareExperienceBehaviorModuleData();

	virtual void moduleDataAnchor();

	int m_08;								///< 0x08
	int m_0c;								///< 0x0c
	float m_10;								///< 0x10

	RS_Member m_member;						///< 0x14
};

// ??0ShareExperienceBehaviorModuleData@@QAE@XZ
ShareExperienceBehaviorModuleData::ShareExperienceBehaviorModuleData()
	: m_08( 0 ), m_0c( 0 ), m_10( 1.0f )
{
}
