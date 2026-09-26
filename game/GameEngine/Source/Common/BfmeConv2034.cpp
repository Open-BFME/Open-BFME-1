extern "C" double sqrt(double x);

#pragma intrinsic(sqrt)

extern const float BfmeZeroRange;

class BfmePosEJ
{
public:
	float m_bfmeXEJ;
	float m_bfmeYEJ;
};

class BfmeDataEJ
{
public:
	unsigned char m_bfmeHeadEJ[0x10];
	float m_bfmeRadiusEJ;
};

class BfmeObjEJ
{
public:
	virtual BfmeDataEJ *bfmeDataEJ();
	virtual BfmePosEJ *bfmePosEJ();
};

float bfmeSignedEJ(const BfmePosEJ *p, BfmeObjEJ *o)
{
	BfmePosEJ *a = o->bfmePosEJ();

	float dy = a->m_bfmeYEJ - p->m_bfmeYEJ;
	float dx = a->m_bfmeXEJ - p->m_bfmeXEJ;

	volatile float s = dx * dx + dy * dy;

	BfmeDataEJ *b = o->bfmeDataEJ();

	float d = (float)sqrt(s) - b->m_bfmeRadiusEJ;

	if (d < BfmeZeroRange)
		return -(d * d);

	return d * d;
}
