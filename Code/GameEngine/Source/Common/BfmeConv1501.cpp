// Open-BFME5 conversions.

float bfmeCosVNB(float a);
float bfmeSinVNB(float a);

struct BfmeVecVNB
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeXformVNB
{
public:
	void bfmeApplyVNB(BfmeVecVNB *out, float angle);
	char m_bfmePad00[0x10];
	float m_bfme10;
	float m_bfme14;
	float m_bfme18;
};

void BfmeXformVNB::bfmeApplyVNB(BfmeVecVNB *out, float angle)
{
	if (m_bfme10 == 0.0f && m_bfme14 == 0.0f)
	{
		out->m_bfme08 += m_bfme18;
		return;
	}

	float c = bfmeCosVNB(angle);
	float s = bfmeSinVNB(angle);

	out->m_bfme00 += c * m_bfme10 - s * m_bfme14;
	out->m_bfme04 += s * m_bfme10 + c * m_bfme14;
	out->m_bfme08 += m_bfme18;
}
