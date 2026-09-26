// cl: /DNDEBUG /MD /EHsc

#include "../../../../Include/GameLogic/Rva0039D550.h"

// Open-BFME5: RefundDieModuleData constructor lifted from retail.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
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
	(reinterpret_cast<Rva0039D550 *>(reinterpret_cast<unsigned char *>(this) + 0x3c))
		->~Rva0039D550();
}
