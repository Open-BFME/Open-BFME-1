// cl: /DNDEBUG /MD /EHsc

// Four-byte indexed-handle ABI view. The destructor called on the member at
// +0x3c is retail RVA 0x0039D550, matched as AttributeHandleStandIn, so the
// member is spelled with that class's own name here.
class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();

private:
	unsigned int m_index;
};

// Open-BFME5: RefundDieModuleData constructor lifted from retail.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Xfer;

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}
	virtual void crc(Xfer *) = 0;
	virtual void xfer(Xfer *) = 0;
	virtual void loadPostProcess() = 0;

private:
	unsigned char m_data[4];
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_data[0x2c];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public Snapshot
{
public:
	DieModuleData() {}
	virtual ~DieModuleData() {}

private:
	InstantDeathDieMuxData m_dieMuxData;
};

class RS_Member
{
public:
	RS_Member();
	~RS_Member() {}

private:
	unsigned int m_handle;
};

class RefundDieModuleData : public DieModuleData
{
public:
	RefundDieModuleData();
	virtual ~RefundDieModuleData();

private:
	unsigned int m_refundPercent;
	unsigned int m_refundMinimum;
	RS_Member m_refundData;
};

// ??0RefundDieModuleData@@QAE@XZ
RefundDieModuleData::RefundDieModuleData()
	: DieModuleData(), m_refundData()
{
	m_refundMinimum = 0;
	m_refundPercent = 0;
}

// MSVC applies novtable to this out-of-line definition while retaining the
// ordinary declaration above for constructor vtable emission.
class __declspec(novtable) RefundDieModuleData;

// ??1RefundDieModuleData@@UAE@XZ
RefundDieModuleData::~RefundDieModuleData()
{
	(reinterpret_cast<AttributeHandleStandIn *>(reinterpret_cast<unsigned char *>(this) + 0x3c))
		->~AttributeHandleStandIn();
}
