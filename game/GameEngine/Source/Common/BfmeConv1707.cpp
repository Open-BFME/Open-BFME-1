class BfmeSlotFY
{
public:
	void bfmeCloseFY(int flag);
};

class BfmeExtraFY
{
public:
	void bfmeFinishFY(void);
};

class BfmeOwnerFY
{
public:
	void bfmeShutdownFY(void);

	unsigned char m_bfmeHeadFY[4];
	BfmeSlotFY *m_bfmeSlotsFY[8];
	unsigned char m_bfmeMidFY[0x12000];
	BfmeExtraFY *m_bfmeExtraFY;
};

void BfmeOwnerFY::bfmeShutdownFY(void)
{
	for (int i = 0; i < 8; ++i)
	{
		if (m_bfmeSlotsFY[i] != 0)
			m_bfmeSlotsFY[i]->bfmeCloseFY(0);
	}

	if (m_bfmeExtraFY != 0)
		m_bfmeExtraFY->bfmeFinishFY();
}
