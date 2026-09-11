// ??0W3DTruckDrawModuleData@@QAE@XZ
// partial score=0.92 date=2026-09-11
struct BfmeAsciiString0077F830
{
	unsigned int m_data;
	BfmeAsciiString0077F830() : m_data(0) {}
};

class W3DModelDrawModuleData
{
	char m_bfmeBase[0x158];

public:
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();
};

class W3DTruckDrawModuleData : public W3DModelDrawModuleData
{
	BfmeAsciiString0077F830 m_string[21];
	float m_one0;
	float m_one1;
	float m_one2;
	float m_one3;
	float m_zero;

public:
	W3DTruckDrawModuleData();
	virtual ~W3DTruckDrawModuleData();
};

W3DTruckDrawModuleData::W3DTruckDrawModuleData()
{
	m_zero = 0.0f;
	m_one0 = 1.0f;
	m_one1 = 1.0f;
	m_one2 = 1.0f;
	m_one3 = 1.0f;
}
