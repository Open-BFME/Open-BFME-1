// ?bfmeAskBI@BfmeThingBI@@QAEEXZ
// partial score=0.91 date=2026-09-08
// The 0x004791F0 and 0x00479210 bodies share the same +0x1dc forwarding
// field and conditional virtual dispatch shape. The existing BFME identity
// evidence names this return-byte method BfmeThingBI.

class BfmeThingBI
{
public:
	virtual unsigned char slot0(void) = 0;
	virtual unsigned char dispatch(void) = 0;

	unsigned char bfmeAskBI(void);

private:
	unsigned char m_pad4[0x1D8];
	BfmeThingBI *m_forwardTarget;
};

unsigned char BfmeThingBI::bfmeAskBI(void)
{
	if (m_forwardTarget)
		return m_forwardTarget->dispatch();
	return dispatch();
}
