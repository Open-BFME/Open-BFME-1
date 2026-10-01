// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// vptr, then five init-list members, then the RS_Member at 0x1c built out of
// line. ModuleData's inline virtual destructor restores its vptr after member
// teardown.

// Four-byte indexed-handle ABI view. The destructor called on the member at
// +0x1c is retail RVA 0x0039D550, matched as AttributeHandleStandIn, so the
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AutoDepositUpdate.h
class AutoDepositUpdateModuleData : public ModuleData
{
public:
	AutoDepositUpdateModuleData();
	virtual ~AutoDepositUpdateModuleData();

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

// Retail tears down the +0x1c handle before restoring ModuleData's vptr.  The
// late redeclaration suppresses only the redundant derived-vptr store here;
// the complete class above retains the constructor's real field layout.
class __declspec(novtable) AutoDepositUpdateModuleData;

// ??1AutoDepositUpdateModuleData@@UAE@XZ
AutoDepositUpdateModuleData::~AutoDepositUpdateModuleData()
{
	reinterpret_cast<AttributeHandleStandIn *>(&m_1c)->~AttributeHandleStandIn();
}
