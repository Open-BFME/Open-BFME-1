// ??0Rva0034C5E0@@QAE@XZ
// partial score=0.6 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: near-twin of ??0DelayedLuaEventList (0x000EDBB0); constructor installs
// vtable 0x010E7D00 (name getter neighbour at 0x0034C660 identifies AttackPriorityInfo),
// default-constructs a string-shaped member at +4, sets a flag at +8 to 1 and a
// count/id at +0xc to 0.

class BfmeStrCVE
{
public:
	BfmeStrCVE() { m_data = 0; }
	~BfmeStrCVE() { bfmeInitCVE(); }
	void bfmeInitCVE();
	void *m_data;
};

class Rva0034C5E0
{
public:
	virtual void bfmeSlot00();

	Rva0034C5E0();

private:
	BfmeStrCVE m_str;
	int m_flag;
	int m_zero;
};

// ?d_0034c5e0@@YAXXZ
Rva0034C5E0::Rva0034C5E0()
{
	m_flag = 1;
	m_zero = 0;
	m_str.bfmeInitCVE();
}
