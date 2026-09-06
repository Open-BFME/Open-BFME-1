extern const float BfmeZeroRange;

class BfmeRoomZE
{
public:
	BfmeRoomZE(const BfmeRoomZE &other);
	~BfmeRoomZE();

	int m_bfmeHandleZE;
};

class BfmeAZE
{
public:
	unsigned char m_bfmeHeadZE[8];
	BfmeRoomZE m_bfmeRoomZE;
	unsigned char m_bfmeMidZE[4];
	float m_bfmeRangeZE;
};

class BfmeDZE
{
public:
	unsigned char m_bfmeHeadZE[0x344];
	unsigned char m_bfmeFlagsZE;
};

class BfmeBZE
{
public:
	unsigned char m_bfmeHeadZE[0xfc];
	BfmeDZE *m_bfmeDZE;
};

class BfmeA1087
{
public:
	void bfmeSendZE(BfmeBZE *target, BfmeRoomZE room, float range);
};

extern BfmeA1087 *g_bfmeA1087;

class BfmeOwnZE
{
public:
	void bfmeTickZE(void *unused);

	unsigned char m_bfmeHeadZE[4];
	BfmeAZE *m_bfmeAZE;
	BfmeBZE *m_bfmeBZE;
};

void BfmeOwnZE::bfmeTickZE(void *unused)
{
	BfmeAZE *source = m_bfmeAZE;
	BfmeBZE *target = m_bfmeBZE;

	if (source && target && source->m_bfmeRangeZE != BfmeZeroRange
		&& target->m_bfmeDZE && (target->m_bfmeDZE->m_bfmeFlagsZE & 1))
		g_bfmeA1087->bfmeSendZE(target, source->m_bfmeRoomZE,
			source->m_bfmeRangeZE);
}
