extern const float BfmeZeroRange;
extern const float g_bfmeLimitEK;

class BfmePairEK
{
public:
	float m_bfmeXEK;
	float m_bfmeYEK;
};

class BfmeHostEK
{
public:
	char bfmeNormEK(const BfmePairEK *in, BfmePairEK *out) const;

	unsigned char m_bfmeHeadEK[0x20];
	float m_bfmeSxEK;
	float m_bfmeSyEK;
};

char BfmeHostEK::bfmeNormEK(const BfmePairEK *in, BfmePairEK *out) const
{
	if (in != 0 && out != 0)
	{
		out->m_bfmeXEK = in->m_bfmeXEK / m_bfmeSxEK;
		out->m_bfmeYEK = in->m_bfmeYEK / m_bfmeSyEK;

		if (out->m_bfmeXEK < BfmeZeroRange)
			out->m_bfmeXEK = 0.0f;
		else if (out->m_bfmeXEK >= g_bfmeLimitEK)
			out->m_bfmeXEK = 127.0f;

		if (out->m_bfmeYEK < BfmeZeroRange)
			out->m_bfmeYEK = 0.0f;

		if (out->m_bfmeYEK >= g_bfmeLimitEK)
			out->m_bfmeYEK = 127.0f;

		return 1;
	}

	return 0;
}
