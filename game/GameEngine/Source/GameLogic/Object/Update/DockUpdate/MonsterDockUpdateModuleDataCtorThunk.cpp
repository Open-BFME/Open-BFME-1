// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of MonsterDockUpdateModuleData.

// Four-byte indexed-handle ABI view. The destructor called on the member at
// +0x10 is retail RVA 0x0039D550, matched as AttributeHandleStandIn, so the
// member is spelled with that class's own name here.
class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();

private:
	unsigned int m_index;
};

// The destructor's only vtable store is Snapshot's (0x01073744): the
// DockUpdateModuleData store dies against the inlined ~Snapshot.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Xfer;

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DockUpdate.h
class DockUpdateModuleData : public Snapshot
{
public:
	DockUpdateModuleData();
	virtual ~DockUpdateModuleData() {}

private:
	unsigned char m_pad[0x0c];
};

class MonsterDockDataMember
{
public:
	MonsterDockDataMember();

private:
	unsigned int m_value;
};

class MonsterDockUpdateModuleData : public DockUpdateModuleData
{
public:
	MonsterDockUpdateModuleData();
	virtual ~MonsterDockUpdateModuleData();

private:
	MonsterDockDataMember m_member;
	unsigned int m_initialDockCount;
};

// ??0MonsterDockUpdateModuleData@@QAE@XZ
MonsterDockUpdateModuleData::MonsterDockUpdateModuleData() :
	DockUpdateModuleData(),
	m_member(),
	m_initialDockCount(0)
{
}

// Retail does not rewrite the derived vtable before member teardown.
class __declspec(novtable) MonsterDockUpdateModuleData;

// ??1MonsterDockUpdateModuleData@@UAE@XZ
MonsterDockUpdateModuleData::~MonsterDockUpdateModuleData()
{
	reinterpret_cast<AttributeHandleStandIn *>(&m_member)->~AttributeHandleStandIn();
}
