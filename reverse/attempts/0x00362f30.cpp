// ?d_00362f30@@YAXXZ
// partial score=0.45 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc

// Retail layout: reuses the exact BfmeOwnVUM field layout established by the
// landed destructor Code/GameEngine/Source/Common/BfmeConv1645.cpp
// (??1BfmeOwnVUM@@QAE@XZ, 0x00360F90, vftable ??_7BfmeOwnVUM@@6B@,
// 0x010E8F34). This constructor zero-initializes the four AsciiString-like
// string-pointer fields (+4, +0x4c, +0xac, +0xb0), the wide-string pointer
// (+0x78), and a subset of the surrounding "pad" dwords that the destructor
// treats as opaque padding but this constructor actually initializes, then
// assigns the remaining state from the incoming parameter through the
// existing pin ?bfmeAssign@BfmeCopyElementC@@QAEXPAU1@@Z,0x000470F0 (also
// pinned elsewhere as ??4Rva00364980HeapElement@@QAEAAU0@ABU0@@Z -- same
// address, additive; kept as bfmeAssign here for the explicit one-argument
// assign-style call retail makes).

class BfmeCopyElementC
{
public:
	void bfmeAssign(BfmeCopyElementC *source);
};

class BfmeOwnVUM
{
public:
	BfmeOwnVUM(BfmeCopyElementC *source);
	~BfmeOwnVUM();
	virtual void bfmeSlot0VUM();
	virtual void bfmeSlot1VUM();
	virtual void bfmeSlot2VUM();
	virtual void bfmeSlot3VUM();
	virtual void bfmeSlot4VUM();

private:
	char *m_bfme04;
	char m_pad08[8];
	int m_10, m_14, m_18, m_1c, m_20, m_24;
	int m_28, m_2c, m_30;
	char m_pad34[0x18];
	char *m_bfme4c;
	int m_50, m_54, m_58, m_5c, m_60, m_64, m_68, m_6c, m_70;
	unsigned short *m_bfme78;
	int m_7c, m_80, m_84, m_88, m_8c, m_90;
	int m_94, m_98, m_9c, m_a0, m_a4, m_a8;
	char *m_bfmeac;
	char *m_bfmeb0;
};

// ?d_00362f30@@YAXXZ
BfmeOwnVUM::BfmeOwnVUM(BfmeCopyElementC *source)
{
	m_bfme04 = 0;

	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0;

	m_28 = 0;
	m_2c = 0;
	m_30 = 0;

	m_bfme4c = 0;

	m_50 = 0;
	m_54 = 0;
	m_58 = 0;
	m_5c = 0;
	m_60 = 0;
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_70 = 0;

	m_bfme78 = 0;

	m_7c = 0;
	m_80 = 0;
	m_84 = 0;
	m_88 = 0;
	m_8c = 0;
	m_90 = 0;

	m_94 = 0;
	m_98 = 0;
	m_9c = 0;
	m_a0 = 0;
	m_a4 = 0;
	m_a8 = 0;

	m_bfmeac = 0;
	m_bfmeb0 = 0;

	((BfmeCopyElementC *)this)->bfmeAssign(source);
}
