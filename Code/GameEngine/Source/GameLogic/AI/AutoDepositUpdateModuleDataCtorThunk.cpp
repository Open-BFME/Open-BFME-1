// cl: /DNDEBUG /MD /EHsc

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

	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	float m_18;
	RS_Member m_1c;
};

// ??0AutoDepositUpdateModuleData@@QAE@XZ
AutoDepositUpdateModuleData::AutoDepositUpdateModuleData()
	: m_08( 0 ), m_0c( 0 ), m_10( 0 ), m_14( 0 ), m_18( 1.0f )
{
}
