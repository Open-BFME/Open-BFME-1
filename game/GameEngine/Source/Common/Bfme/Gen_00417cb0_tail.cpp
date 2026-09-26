// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Gen_00417cb0::tail, retail 0x00417A70, 78 bytes. The body carried
// only a machine byte-dump row; the symbols.csv pin names it for the caller it
// was found from and does not assert an identity.
//
// Three flags at +0x140, +0x141 and +0x143 -- note the gap at +0x142 -- all
// have to be set. Then alt runs, the holder at +0xFC is asked for the current
// value of the source it keeps at +0x200, and that value plus this function's
// own argument go to the emit helper.
//
// The value defaults to zero when there is no holder, but the source pointer
// inside the holder is never tested; only the holder is.
//
// The holder goes into a local before the test. Read straight from the member
// into the test, the compiler makes a copy of it before dereferencing rather
// than reloading through the register it already tested.

class BfmeTailSource
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void *bfmeCurrent(void) = 0;			// slot 8, vtable+0x20
};

class BfmeTailHolder
{
public:
	unsigned char m_bfmeHead[0x200];
	BfmeTailSource *m_bfmeSource;				// +0x200
};

class Gen_00417cb0
{
public:
	void tail(void *param);
	void alt(void);						// retail 0x00411BE0

private:
	void bfmeEmit(void *value, void *param);		// ILT 0x0002CB79

	unsigned char m_bfmeHeadA[0xFC];
	BfmeTailHolder *m_bfmeHolder;				// +0x00FC
	unsigned char m_bfmeHeadB[0x140 - 0x100];
	bool m_bfmeFlagA;					// +0x0140
	bool m_bfmeFlagB;					// +0x0141
	unsigned char m_bfmeUnused_142;				// +0x0142
	bool m_bfmeFlagC;					// +0x0143
};

// ?tail@Gen_00417cb0@@QAEXPAX@Z
void Gen_00417cb0::tail(void *param)
{
	if (m_bfmeFlagA && m_bfmeFlagB && m_bfmeFlagC)
	{
		alt();

		BfmeTailHolder *holder = m_bfmeHolder;
		void *value = 0;

		if (holder)
			value = holder->m_bfmeSource->bfmeCurrent();

		bfmeEmit(value, param);
	}
}
