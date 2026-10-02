// Retail defines this singleton as `BfmeGameCW *g_bfmeGameCW`
// (?g_bfmeGameCW@@3PAVBfmeGameCW@@A); this TU only needs the pointer's
// address, so it forward-declares the class and reinterprets it. The +0x16C
// member address is taken in bytes, so it does not need sizeof(BfmeGameCW).
class BfmeGameCW;
extern BfmeGameCW *g_bfmeGameCW;

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
			bfmeApplyCZ((char *)g_bfmeGameCW + 0x16c, enable, 1);
	}
	else
	{
		if (m_bfmeStateCZ != 0)
			bfmeApplyCZ((char *)g_bfmeGameCW + 0x16c, 1, 2);
	}

	m_bfmeStateCZ = (char)enable;
}
