// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: SEH scalar dtor at retail 0x003367E0 (80B). Sets derived
// vftable 0x010E7530, optionally calls virtual slot+4 on the object held at
// +0x08 when +0x04 is non-null, then stores base vftable 0x010E7520 inline.

class BfmeReleaseTarget
{
public:
	virtual void bfmeSlot0(void) = 0;
	virtual void bfmeRelease(void) = 0;
};

class BfmeDualVtableReleaseBase
{
public:
	__forceinline ~BfmeDualVtableReleaseBase(void) {}
	virtual void bfmeKeepVtable(void) {}
};

class BfmeDualVtableReleaseDtor : public BfmeDualVtableReleaseBase
{
public:
	virtual ~BfmeDualVtableReleaseDtor(void);

private:
	void *m_guard;                 // +0x04
	BfmeReleaseTarget *m_target;   // +0x08
};

// ??1BfmeDualVtableReleaseDtor@@UAE@XZ
BfmeDualVtableReleaseDtor::~BfmeDualVtableReleaseDtor(void)
{
	if (m_guard)
		m_target->bfmeRelease();
}
