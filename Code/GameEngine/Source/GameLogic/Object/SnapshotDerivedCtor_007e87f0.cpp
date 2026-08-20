// cl: /DNDEBUG /MD /EHsc

// Retail 0x007E87F0. Snapshot subclass constructor. Identity is not recovered
// -- the vftable at 0x011296B0 is not named in the reverse indexes -- so the
// class carries an address-derived placeholder. Byte shape is Snapshot's
// out-of-line ctor, then same-valued zeros at +8/+0xC/+4 and the derived
// vptr last.

class Snapshot
{
public:
	Snapshot();
	virtual void snapshotAnchor();
};

class Gen_007e87f0 : public Snapshot
{
public:
	Gen_007e87f0();

private:
	int m_4;
	int m_8;
	int m_c;
};

// ??0Gen_007e87f0@@QAE@XZ
Gen_007e87f0::Gen_007e87f0()
{
	m_8 = 0;
	m_c = 0;
	m_4 = 0;
}
