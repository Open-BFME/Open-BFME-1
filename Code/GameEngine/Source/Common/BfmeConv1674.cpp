class BfmeWindowERC;

class BfmeWindowManagerERC
{
public:
	virtual void bfmeSlot00ERC(void);
	virtual void bfmeSlot01ERC(void);
	virtual void bfmeSlot02ERC(void);
	virtual void bfmeSlot03ERC(void);
	virtual void bfmeSlot04ERC(void);
	virtual void bfmeSlot05ERC(void);
	virtual void bfmeSlot06ERC(void);
	virtual void bfmeSlot07ERC(void);
	virtual void bfmeSlot08ERC(void);
	virtual void bfmeSlot09ERC(void);
	virtual void bfmeSlot10ERC(void);
	virtual void bfmeSlot11ERC(void);
	virtual void bfmeSlot12ERC(void);
	virtual void bfmeSlot13ERC(void);
	virtual void bfmeSlot14ERC(void);
	virtual void bfmeSlot15ERC(void);
	virtual void bfmeSlot16ERC(void);
	virtual void bfmeSlot17ERC(void);
	virtual void bfmeSlot18ERC(void);
	virtual void bfmeSlot19ERC(void);
	virtual void bfmeSlot20ERC(void);
	virtual void bfmeSlot21ERC(void);
	virtual void bfmeSlot22ERC(void);
	virtual void bfmeSlot23ERC(void);
	virtual void bfmeSlot24ERC(void);
	virtual void bfmeSlot25ERC(void);
	virtual void bfmeSlot26ERC(void);
	virtual void bfmeSlot27ERC(void);
	virtual void bfmeSlot28ERC(void);
	virtual void bfmeSlot29ERC(void);
	virtual void bfmeSlot30ERC(void);
	virtual void bfmeSlot31ERC(void);
	virtual void bfmeSlot32ERC(void);
	virtual void bfmeSlot33ERC(void);
	virtual void bfmeSlot34ERC(void);
	virtual void bfmeSlot35ERC(void);
	virtual void bfmeSlot36ERC(void);
	virtual void bfmeSlot37ERC(void);
	virtual void bfmeSlot38ERC(void);
	virtual void bfmeSlot39ERC(void);
	virtual void bfmeSlot40ERC(void);
	virtual void bfmeSlot41ERC(void);
	virtual void bfmeSlot42ERC(void);
	virtual void bfmeSlot43ERC(void);
	virtual void bfmeSlot44ERC(void);
	virtual void bfmeSlot45ERC(void);
	virtual void bfmeSlot46ERC(void);
	virtual void bfmeSlot47ERC(void);
	virtual void bfmeSlot48ERC(void);
	virtual void bfmeSlot49ERC(void);
	virtual void bfmeSlot50ERC(void);
	virtual void bfmeSlot51ERC(void);
	virtual void bfmeSlot52ERC(void);
	virtual int bfmeSendSystemMsgERC(BfmeWindowERC *window, unsigned int msg,
		unsigned int data1, unsigned int data2);
};

extern BfmeWindowManagerERC *g_bfmeWindowManagerERC;

class BfmeWindowERC
{
public:
	int bfmeBringToTopERC(void);
	int bfmeActivateERC(void);

	unsigned char m_bfmeHeadERC[8];
	unsigned int m_bfmeStatusERC;
};

int BfmeWindowERC::bfmeActivateERC(void)
{
	int returnCode = bfmeBringToTopERC();
	if (returnCode != 0)
		return returnCode;
	m_bfmeStatusERC |= 1;
	unsigned int before = m_bfmeStatusERC;
	m_bfmeStatusERC &= ~0x10u;
	if (m_bfmeStatusERC != before)
		g_bfmeWindowManagerERC->bfmeSendSystemMsgERC(this, 0x1b, 1, 0);
	m_bfmeStatusERC &= ~0x10000000u;
	return 0;
}
