class BfmeVec3FC
{
public:
	float x;
	float y;
	float z;
};

class BfmeObjFC
{
public:
	unsigned char m_bfmeHeadFC[8];
	BfmeObjFC *m_bfmeInnerFC;
	BfmeVec3FC m_bfmePosFC;
};

class BfmeHostFC
{
public:
	void bfmeGetPosFC(BfmeVec3FC *out);

	void *m_bfmeVfFC;
	BfmeObjFC *m_bfmeAFC;
	unsigned char m_bfmeGapFC[8];
	BfmeObjFC *m_bfmeBFC;
};

void BfmeHostFC::bfmeGetPosFC(BfmeVec3FC *out)
{
	BfmeObjFC *p = 0;

	if (m_bfmeAFC != 0)
		p = m_bfmeAFC->m_bfmeInnerFC;

	BfmeObjFC *b = m_bfmeBFC;

	if (b != 0)
	{
		p = b->m_bfmeInnerFC;

		if (p == 0)
			p = b;
	}

	if (p != 0)
	{
		*out = p->m_bfmePosFC;
	}
	else
	{
		out->x = 0.0f;
		out->y = 0.0f;
		out->z = 0.0f;
	}
}
