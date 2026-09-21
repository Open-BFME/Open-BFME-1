// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
// Retail 0x00585CF0: preserve the banked type/member labels and keep
// address tokens on unproven method identities. The range at +24/+28
// is searched for zero by STL __find at 0x005853B0. Its empty iterator
// tag explains the two equal-address arguments; it is not an output pair.
class BfmeObjYF
{
public:
	unsigned char m_bfmeHeadYF[0x10];
	int m_bfme10YF;
	unsigned char m_bfmeMidYF[0x24 - 0x14];
	const int *m_bfme24YF;
	const int *m_bfme28YF;
	unsigned char m_bfmeMid2YF[0x30 - 0x2c];
	int m_bfme30YF;
	unsigned char m_bfmeMid3YF[0x3c - 0x34];
	int m_bfme3CYF;
};

struct BfmeHandleYF
{
	__forceinline BfmeHandleYF(const BfmeHandleYF &o) { m_bfmePtrYF = o.m_bfmePtrYF; }

	BfmeObjYF *m_bfmePtrYF;
};

void bfmeGo1064C(int a, int b);

class BfmeHostYF
{
public:
	void bfmeUpdateYF_00585CF0(BfmeHandleYF h);
	void bfmeNoteYF_00585C20(BfmeHandleYF h);
};

void BfmeHostYF::bfmeUpdateYF_00585CF0(BfmeHandleYF h)
{
	BfmeObjYF *o = h.m_bfmePtrYF;

	bfmeNoteYF_00585C20(h);

	const int *n = o->m_bfme28YF;
	int v = 0;

	if (std::find(o->m_bfme24YF, n, v) != n)
	{
		if (o->m_bfme3CYF != 2)
		{
			bfmeGo1064C(o->m_bfme10YF, 2);
			o->m_bfme3CYF = 2;
		}

		o->m_bfme30YF = 2;
	}
}
