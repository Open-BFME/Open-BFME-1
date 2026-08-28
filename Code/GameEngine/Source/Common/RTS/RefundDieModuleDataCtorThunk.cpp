// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: RefundDieModuleData constructor lifted from retail.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public Snapshot
{
public:
	DieModuleData() {}
	virtual ~DieModuleData();

private:
	InstantDeathDieMuxData m_dieMuxData;
};

class RS_Member
{
public:
	RS_Member();
	~RS_Member();
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
