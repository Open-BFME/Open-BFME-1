extern "C" void __cdecl peerStopGame(void *peer);

class BfmeSubFP
{
public:
	void bfmeSetFP(const char *name, const char *extra);

	unsigned char m_bfmeSubDataFP[4];
};

class BfmeOwnerFP
{
public:
	void bfmeStopFP(void *peer);

	unsigned char m_bfmeHeadFP[0xc0];
	BfmeSubFP m_bfmeSubFP;
	unsigned char m_bfmeMidFP[0x314];
	char m_bfmeFlagFP;
};

void BfmeOwnerFP::bfmeStopFP(void *peer)
{
	peerStopGame(peer);
	m_bfmeSubFP.bfmeSetFP("openstaging", "");
	m_bfmeFlagFP = 0;
}
