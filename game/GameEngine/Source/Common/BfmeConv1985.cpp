class ClientRoot4120
{
public:
	unsigned char m_bfmeHeadETH[0xbc];
	char m_bfmeFlagAETH;
	char m_bfmeFlagBETH;
};

extern ClientRoot4120 *TheGameClient;

class BfmeSubETH
{
public:
	int m_bfmeValETH;
};

void __fastcall bfmeNormAngleETH(float &angle);

class BfmeViewETH
{
public:
	void bfmeSetAngleETH(float angle);
	void bfmeStoreAngleETH(float angle);
	void bfmeSetCamETH();
	void bfmeApplyETH(BfmeSubETH *sub);

	unsigned char m_bfmeHeadETH[0x0c];
	BfmeSubETH m_bfmeSubETH;
	unsigned char m_bfmePadAETH[0x34];
	char m_bfmeGateETH;
	unsigned char m_bfmePadBETH[0x197];
	char m_bfmeAETH;
	unsigned char m_bfmePadCETH[0x27];
	char m_bfmeBETH;
	unsigned char m_bfmePadDETH[0x23];
	char m_bfmeCETH;
	unsigned char m_bfmePadEETH[0x53];
	char m_bfmeDETH;
	char m_bfmeEETH;
};

void BfmeViewETH::bfmeSetAngleETH(float angle)
{
	if (TheGameClient->m_bfmeFlagAETH && m_bfmeGateETH)
		return;

	if (TheGameClient->m_bfmeFlagBETH && m_bfmeGateETH)
		return;

	bfmeNormAngleETH(angle);
	bfmeStoreAngleETH(angle);

	m_bfmeAETH = 0;
	m_bfmeBETH = 0;
	m_bfmeDETH = 0;
	m_bfmeCETH = 0;
	m_bfmeEETH = 0;

	bfmeSetCamETH();
	bfmeApplyETH(&m_bfmeSubETH);
}
