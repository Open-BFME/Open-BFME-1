// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// vptr, then five init-list members, then the RS_Member at 0x1c built out of
// line. ModuleData carries a declared destructor so the EH frame appears.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();
	~ModuleData();

	int m_04;
};

class RS_Member
{
public:
	RS_Member();
	~RS_Member();

private:
	void *m_p;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoDepositUpdate.h
class AutoDepositUpdateModuleData : public ModuleData
{
public:
	AutoDepositUpdateModuleData();

	virtual void moduleDataAnchor();

	int m_depositFrame;
	int m_depositAmount;
	int m_initialCaptureBonus;
	int m_14;
	float m_18;
	RS_Member m_1c;
};

// ??0AutoDepositUpdateModuleData@@QAE@XZ
AutoDepositUpdateModuleData::AutoDepositUpdateModuleData()
	: m_depositFrame( 0 ), m_depositAmount( 0 ), m_initialCaptureBonus( 0 ), m_14( 0 ), m_18( 1.0f )
{
}
