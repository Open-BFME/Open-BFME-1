class BfmeSubFW;

class BfmeXferFW
{
public:
	virtual void bfmeSlot00FW(void);
	virtual void bfmeSlot01FW(void);
	virtual void bfmeSlot02FW(void);
	virtual void bfmeSlot03FW(void);
	virtual void bfmeSlot04FW(void);
	virtual void bfmeBeginFW(const char *name);
	virtual void bfmeEndFW(void);
};

class BfmeSubFW
{
public:
	void bfmeApplyFW(void *first, void *second);

	void *m_bfmeFirstFW;
	void *m_bfmeSecondFW;
};

void __cdecl bfmeHelperFW(BfmeXferFW *xfer, BfmeSubFW *sub);

class BfmeThingFW
{
public:
	void bfmeXferFW(BfmeXferFW *xfer);

	unsigned char m_bfmeHeadFW[4];
	BfmeSubFW m_bfmeSubFW;
};

void BfmeThingFW::bfmeXferFW(BfmeXferFW *xfer)
{
	xfer->bfmeBeginFW("CRCParameterCheck");

	BfmeSubFW *sub = &m_bfmeSubFW;
	bfmeHelperFW(xfer, sub);
	xfer->bfmeEndFW();
	sub->bfmeApplyFW(sub->m_bfmeFirstFW, sub->m_bfmeSecondFW);
}
