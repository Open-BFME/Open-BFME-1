class BfmeVec3JF
{
public:
	float m_bfmeXJF;
	float m_bfmeYJF;
	float m_bfmeZJF;
};

class BfmeSetJF
{
public:
	BfmeVec3JF m_bfmeGridJF[3][3];
};

class BfmeXfJF
{
public:
	bool bfmeLoadJF(int index);

	unsigned char m_bfmeHeadJF[0x218];
	int m_bfmeIndexJF;
	unsigned char m_bfmeGap2JF[8];
	BfmeSetJF m_bfmeSetsJF[6];
	unsigned char m_bfmeGap3JF[0x510];
	BfmeVec3JF m_bfmeOutJF[3][3];
};

bool BfmeXfJF::bfmeLoadJF(int index)
{
	if (index < 6 && index >= 1)
	{
		m_bfmeIndexJF = index;

		BfmeXfJF *sp = (BfmeXfJF *)((char *)this + index * 0x6c);

		m_bfmeOutJF[0][0] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[0][0];
		m_bfmeOutJF[1][0] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[0][1];
		m_bfmeOutJF[2][0] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[0][2];
		m_bfmeOutJF[0][1] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[1][0];
		m_bfmeOutJF[1][1] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[1][1];
		m_bfmeOutJF[2][1] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[1][2];
		m_bfmeOutJF[0][2] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[2][0];
		m_bfmeOutJF[1][2] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[2][1];
		m_bfmeOutJF[2][2] = sp->m_bfmeSetsJF[0].m_bfmeGridJF[2][2];

		return true;
	}

	return false;
}
