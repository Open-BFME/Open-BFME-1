// ?bfmeClampDH@BfmeHostDH@@QBEXPAVBfmeVecDH@@PBVBfmeSrcDH@@@Z
// partial score=0.96 date=2026-09-24
extern "C" double sqrt(double x);

#pragma intrinsic(sqrt)

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern const float BfmeZeroRange;

class BfmeVecDH
{
public:
	void bfmeSetDH(float x, float y, float z) volatile
	{
		m_bfmeXDH = x;
		m_bfmeYDH = y;
		m_bfmeZDH = z;
	}

	float m_bfmeXDH;
	float m_bfmeYDH;
	float m_bfmeZDH;
};

class BfmeSrcDH;

class BfmeHostDH
{
public:
	BfmeVecDH bfmeDeltaDH(const BfmeSrcDH *src) const;
	void bfmeClampDH(BfmeVecDH *out, const BfmeSrcDH *src) const;

	unsigned char m_bfmeHeadDH[0xbc];
	float m_bfmeRangeDH;
};

void BfmeHostDH::bfmeClampDH(BfmeVecDH *out, const BfmeSrcDH *src) const
{
	BfmeVecDH v = bfmeDeltaDH(src);

	float len = (float)sqrt(v.m_bfmeXDH * v.m_bfmeXDH + v.m_bfmeYDH * v.m_bfmeYDH + v.m_bfmeZDH * v.m_bfmeZDH);

	float range = m_bfmeRangeDH;

	if (len <= range)
	{
		_ReadWriteBarrier();
		BfmeVecDH zero = {
			*(const volatile float *)&BfmeZeroRange,
			*(const volatile float *)&BfmeZeroRange,
			*(const volatile float *)&BfmeZeroRange
		};
		((volatile BfmeVecDH *)out)->bfmeSetDH(zero.m_bfmeXDH, zero.m_bfmeYDH, zero.m_bfmeZDH);
	}
	else
	{
		_ReadWriteBarrier();
		volatile float t = (len - range) / len;

		((volatile BfmeVecDH *)out)->bfmeSetDH(t * v.m_bfmeXDH, v.m_bfmeYDH * t, v.m_bfmeZDH * t);
	}
}
