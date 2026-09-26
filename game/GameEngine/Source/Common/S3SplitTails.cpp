// Three seventeen-byte bodies the ledger had split after their first
// instruction, with the ten bytes that follow claimed as aliases elsewhere.
//
// 0x0059BCE0 and 0x005A03C0 are the same body twice: a byte flag at +0x08 that
// skips everything when set, and otherwise a virtual call through slot 2 with
// the word at +0x14. The flag is read as a byte and tested as one, so it is a
// bool rather than a masked int.
//
// 0x0018F2C0 sets bit 0 of a global and then stores its argument at +0x70. The
// store goes through eax rather than the x87 stack, so the argument is
// int-width, not the float the alias name suggests.

class Gen_0059bce0
{
public:
	void bfmeSkip(void);

private:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeApply(int value) = 0;				// +0x08

	char m_bfmeHead[0x08 - 0x04];
	bool m_bfmeDone;						// +0x08
	char m_bfmeMid[0x14 - 0x09];
	int m_bfme0014;							// +0x14
};

class Gen_005a03c0
{
public:
	void bfmeSkip(void);

private:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeApply(int value) = 0;				// +0x08

	char m_bfmeHead[0x08 - 0x04];
	bool m_bfmeDone;						// +0x08
	char m_bfmeMid[0x14 - 0x09];
	int m_bfme0014;							// +0x14
};

extern int TheBfmeDrawableDirtyFlags;					// 0x012EF418

class Gen_0018f2c0
{
public:
	void bfmeSetValue(int value);

private:
	char m_bfmeHead[0x70];
	int m_bfme0070;							// +0x70
};

// ?bfmeSkip@Gen_0059bce0@@QAEXXZ
void Gen_0059bce0::bfmeSkip(void)
{
	if (!m_bfmeDone)
		bfmeApply(m_bfme0014);
}

// ?bfmeSkip@Gen_005a03c0@@QAEXXZ
void Gen_005a03c0::bfmeSkip(void)
{
	if (!m_bfmeDone)
		bfmeApply(m_bfme0014);
}

// ?bfmeSetValue@Gen_0018f2c0@@QAEXH@Z
void Gen_0018f2c0::bfmeSetValue(int value)
{
	TheBfmeDrawableDirtyFlags |= 1;

	m_bfme0070 = value;
}
