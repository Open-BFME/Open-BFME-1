// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: OneRingPenaltyUpdateModuleData default ctor.
// Retail zeros gap@4 uninit; stores +8,+20,+10,+14,+18,+c,+1c in that order.

class OneRingPenaltyUpdateModuleData
{
public:
	OneRingPenaltyUpdateModuleData();
	virtual ~OneRingPenaltyUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
};

// ??0OneRingPenaltyUpdateModuleData@@QAE@XZ
OneRingPenaltyUpdateModuleData::OneRingPenaltyUpdateModuleData()
{
	m_08 = 0;
	m_20 = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_0c = 0;
	m_1c = 0;
}
