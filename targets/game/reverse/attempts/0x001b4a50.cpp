// ?bfmeSetXC@BfmeXformXC@@QAEXM@Z
// partial score=0.8 date=2026-09-08
extern const float BfmeZeroRange;

float Cos(float a);
float Sin(float a);

class BfmeXformXC
{
public:
	void bfmeSetXC(float a);

	unsigned char m_bfmeHeadXC[0x64];
	float m_bfme64XC;
	float m_bfme68XC;
	float m_bfme6CXC;
	float m_bfme70XC;
	float m_bfme74XC;
	float m_bfme78XC;
	float m_bfme7CXC;
	float m_bfme80XC;
	float m_bfme84XC;
	float m_bfme88XC;
	float m_bfme8CXC;
	float m_bfme90XC;
};

void BfmeXformXC::bfmeSetXC(float a)
{
	float tx = m_bfme70XC;
	float ty = m_bfme80XC;
	float tz = m_bfme90XC;

	float c = Cos(a);
	float s = Sin(a);
	float ns = -s;

	float t1 = *(volatile float *)&s * BfmeZeroRange - *(volatile float *)&c * BfmeZeroRange;
	float *pt1 = &t1;
	float t2 = t1 * BfmeZeroRange;

	m_bfme64XC = c - t2;
	m_bfme68XC = ns;
	m_bfme6CXC = 0.0f;
	m_bfme70XC = tx;
	m_bfme74XC = t2 - ns;
	m_bfme78XC = c;
	m_bfme7CXC = 0.0f;
	m_bfme80XC = ty;
	m_bfme84XC = ns * BfmeZeroRange - c * BfmeZeroRange;
	m_bfme88XC = *pt1;
	m_bfme8CXC = 1.0f;
	m_bfme90XC = tz;
}
