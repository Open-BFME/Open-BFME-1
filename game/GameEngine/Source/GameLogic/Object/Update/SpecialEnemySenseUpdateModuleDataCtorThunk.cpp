// cl: /DNDEBUG /MD /EHsc

// vptr, then the RS_Member at 0x08 built out of line, then two plain members.
// ModuleData's inline virtual destructor restores its vptr after member teardown.

// Four-byte indexed-handle ABI view. The destructor called on the member at
// +0x08 is retail RVA 0x0039D550, matched as AttributeHandleStandIn, so the
// member is spelled with that class's own name here.
class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();

private:
	unsigned int m_index;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
	virtual void moduleDataAnchor();
	virtual ~ModuleData() {}

	int m_moduleTagNameKey;
};

class RS_Member
{
public:
	RS_Member();

private:
	void *m_p;
};

class SpecialEnemySenseUpdateModuleData : public ModuleData
{
public:
	SpecialEnemySenseUpdateModuleData();
	virtual ~SpecialEnemySenseUpdateModuleData();

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

// Retail tears down the +0x08 handle before restoring ModuleData's vptr.
// This redeclaration suppresses only the redundant derived-vptr store in the
// destructor; the complete class above retains the constructor's real layout.
class __declspec(novtable) SpecialEnemySenseUpdateModuleData;

// ??1SpecialEnemySenseUpdateModuleData@@UAE@XZ
SpecialEnemySenseUpdateModuleData::~SpecialEnemySenseUpdateModuleData()
{
	reinterpret_cast<AttributeHandleStandIn *>(&m_08)->~AttributeHandleStandIn();
}
