extern "C" char *g_bfmeGameCW;

class BfmeOwnCZ
{
public:
	void bfmeSetCZ(int enable);
	void bfmeApplyCZ(void *target, int first, int second);

	unsigned char m_bfmeHeadCZ[0x38];
	char m_bfmeStateCZ;
};

void BfmeOwnCZ::bfmeSetCZ(int enable)
{
	if ((char)enable)
	{
		if (m_bfmeStateCZ == 0)
			bfmeApplyCZ(g_bfmeGameCW + 0x16c, enable, 1);
	}
	else
	{
		if (m_bfmeStateCZ != 0)
			bfmeApplyCZ(g_bfmeGameCW + 0x16c, 1, 2);
	}

	m_bfmeStateCZ = (char)enable;
}
