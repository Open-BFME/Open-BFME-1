extern "C" double sqrt(double x);

#pragma intrinsic(sqrt)

extern "C" float g_bfmeOffsetDF;
extern const float BfmeZeroRange;

class BfmePosDF
{
public:
	float m_bfmeXDF;
	float m_bfmeYDF;
};

class BfmeThingDF
{
public:
	unsigned char m_bfmeHeadDF[0x38];
	float m_bfmeXDF;
	float m_bfmeYDF;
	unsigned char m_bfmePadDF[0x7c];
	float m_bfmeSlopDF;
};

class BfmeInfoDF
{
public:
	unsigned char m_bfmeHeadDF[0x18];
	float m_bfmeReachDF;
};

class BfmeHostDF
{
public:
	char bfmeInReachDF(const BfmeThingDF *thing, const BfmePosDF *pos) const;

	void *m_bfmeVfDF;
	BfmeInfoDF *m_bfmeInfoDF;
};

char BfmeHostDF::bfmeInReachDF(const BfmeThingDF *thing, const BfmePosDF *pos) const
{
	float reach = m_bfmeInfoDF->m_bfmeReachDF - g_bfmeOffsetDF;

	if (!(reach < BfmeZeroRange) && !(reach == BfmeZeroRange))
	{
		float dx = thing->m_bfmeXDF - pos->m_bfmeXDF;
		float dy = thing->m_bfmeYDF - pos->m_bfmeYDF;
		float d = (float)sqrt(dx * dx + dy * dy) - thing->m_bfmeSlopDF;
		float n;

		if (d < BfmeZeroRange)
			n = BfmeZeroRange;
		else
			n = d * d;

		return n < reach * reach;
	}

	return false;
}
