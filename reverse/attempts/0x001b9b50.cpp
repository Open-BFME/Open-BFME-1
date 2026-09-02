// ?queryClamp@BfmeSub1CC_EC3@@QAEXMPAX@Z
// partial score=0.48 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x001B9B50: clamp this+0x3C toward a float limit using queryDivMin40
// then re-query and clamp into [0, query].

class BfmeSub1CC_EC3
{
public:
	float query(void *val);
	float queryDivMin40(void *val);
	void queryClamp(float limit, void *val);

private:
	char m_pad[0x3C];
	float m_value;
};

extern float g_bfmeZeroCY;

void BfmeSub1CC_EC3::queryClamp(float limit, void *val)
{
	if (limit > m_value)
	{
		m_value = m_value + queryDivMin40(val);
		if (m_value > limit)
			m_value = limit;
	}
	else
		m_value = limit;

	float q = query(val);
	limit = m_value;
	if (limit < g_bfmeZeroCY)
		m_value = 0.0f;
	else if (limit > q)
		m_value = q;
	else
		m_value = limit;
}
