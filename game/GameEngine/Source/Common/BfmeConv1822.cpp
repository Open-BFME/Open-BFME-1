class BfmeOwnerZY
{
public:
	void bfmeSetZY(int value);
	void bfmeNotifyZY(void);

	unsigned char m_bfmeHeadZY[0x1e8];
	int m_bfmeCurrentZY;
	int m_bfmePreviousZY;
};

void BfmeOwnerZY::bfmeSetZY(int value)
{
	int current = m_bfmeCurrentZY;

	if ((value | 0x10000) == (current | 0x10000))
		m_bfmeCurrentZY = current ^ 0x10000;
	else
	{
		m_bfmePreviousZY = current;
		m_bfmeCurrentZY = value;
	}

	bfmeNotifyZY();
}
