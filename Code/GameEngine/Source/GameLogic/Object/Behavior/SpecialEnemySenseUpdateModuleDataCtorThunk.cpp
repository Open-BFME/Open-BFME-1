// cl: /DNDEBUG /MD /EHsc

// vptr, then the RS_Member at 0x08 built out of line, then two plain members.
// ModuleData carries a declared destructor so the EH frame appears.

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

class SpecialEnemySenseUpdateModuleData : public ModuleData
{
public:
	SpecialEnemySenseUpdateModuleData();

	virtual void moduleDataAnchor();

	RS_Member m_08;
	int m_0c;
	int m_10;
};

// ??0SpecialEnemySenseUpdateModuleData@@QAE@XZ
SpecialEnemySenseUpdateModuleData::SpecialEnemySenseUpdateModuleData()
{
	m_0c = 0;
	m_10 = 1;
}
