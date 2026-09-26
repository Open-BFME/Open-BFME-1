class BfmeProbeXM;

struct BfmeStateXM
{
	unsigned char m_bfmeHeadXM[0x18];
	unsigned char m_bfmeTagXM[0x18];
	float m_bfmeXXM;
	float m_bfmeYXM;
	unsigned char m_bfmePadXM[4];
	BfmeProbeXM *m_bfmeBestXM;
	float m_bfmeBestDistXM;
};

class BfmeProbeXM
{
public:
	bool bfmeTestXM(BfmeStateXM *state, void *tag);

	unsigned char m_bfmeHeadXM[0x38];
	float m_bfmeXXM;
	float m_bfmeYXM;
};

int bfmeVisitXM(BfmeProbeXM *probe, BfmeStateXM *state)
{
	if (probe->bfmeTestXM(state, state->m_bfmeTagXM))
	{
		float dx = probe->m_bfmeXXM - state->m_bfmeXXM;
		float dy = probe->m_bfmeYXM - state->m_bfmeYXM;
		float d = dy * dy + dx * dx;

		if (d < state->m_bfmeBestDistXM)
		{
			state->m_bfmeBestXM = probe;
			state->m_bfmeBestDistXM = d;
			return 1;
		}
	}

	return 1;
}
