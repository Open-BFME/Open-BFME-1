// retail ILT 0x00013633 -> 0x00661F10 is the matched Connection::doSend row
class Connection
{
public:
	unsigned int doSend(bool flag);
};

// retail ILT 0x00015D3E -> 0x006834B0 is the matched Transport::doSend row
class Transport
{
public:
	bool doSend(void);
};

class BfmeSlotFY;
class BfmeExtraFY;

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
			((Connection *)m_bfmeSlotsFY[i])->doSend(false);
	}

	if (m_bfmeExtraFY != 0)
		((Transport *)m_bfmeExtraFY)->doSend();
}
