// ?bfmeTintCA@BfmeHostCA@@QAEXXZ (identity unknown)
// partial score=0.96 date=2026-09-07
// 132/132 at exact size. The whole selection tree matches -- the mode test
// hoisted above the colour load, both duplicated arms, and MSVC merging the two
// `colour = m_colour` and two `colour = 0xff000000` assignments into ONE tail
// call block.
// Getting to exact SIZE needed the shared-variable form: retail's
//   mov eax,0xff000000 / push eax
// (rather than the 5-byte `push 0xff000000`) is the tell from
// [[register-pushed-constant-is-a-variable]] -- the constant and m_colour feed
// the SAME local, so write `colour = ...` in both arms and make ONE call after
// the tree, with the two info arms taking an early return.
// Residue: in those two early-return arms retail emits
//   mov eax,[eax+0x1c8] / mov ecx,edi / push eax
// and MSVC emits
//   mov edx,[eax+0x1c8] / push edx / mov ecx,edi
// -- the receiver is set before the push in retail, after it in MSVC, and the
// scratch register follows. Hoisting the argument into a local first (tried in
// both structures) does not move it.
class BfmeInfoCA
{
public:
	unsigned char m_bfmeHeadCA[0x1c4];
	unsigned int m_bfmePlainCA;
	unsigned int m_bfmeAltCA;
};

class BfmeOwnerCA
{
public:
	BfmeInfoCA *bfmeInfoCA();
};

class BfmeResCA
{
public:
	void bfmeApplyCA(unsigned int colour);
};

struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadCA[0x218];
	int m_bfmeModeCA;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class BfmeHostCA
{
public:
	virtual void bfmeSlot00CA();
	virtual void bfmeSlot01CA();
	virtual void bfmeSlot02CA();
	virtual void bfmeSlot03CA();
	virtual void bfmeSlot04CA();
	virtual void bfmeSlot05CA();
	virtual void bfmeSlot06CA();
	virtual void bfmeSlot07CA();
	virtual void bfmeSlot08CA();
	virtual void bfmeSlot09CA();
	virtual BfmeResCA *bfmeGetCA();

	void bfmeTintCA();

	unsigned char m_bfmeHeadCA[0x238];
	BfmeOwnerCA *m_bfmeOwnerCA;
	unsigned char m_bfmePadCA[4];
	unsigned int m_bfmeColourCA;
};

void BfmeHostCA::bfmeTintCA()
{
	BfmeResCA *r = bfmeGetCA();

	if (r == 0)
		return;

	unsigned int colour;
	BfmeInfoCA *info;

	if (TheWritableGlobalData->m_bfmeModeCA == 4)
	{
		if (m_bfmeColourCA != 0)
			colour = m_bfmeColourCA;
		else if (m_bfmeOwnerCA != 0 && (info = m_bfmeOwnerCA->bfmeInfoCA()) != 0)
		{
			r->bfmeApplyCA(info->m_bfmeAltCA);
			return;
		}
		else
			colour = 0xff000000;
	}
	else
	{
		if (m_bfmeColourCA != 0)
			colour = m_bfmeColourCA;
		else if (m_bfmeOwnerCA != 0 && (info = m_bfmeOwnerCA->bfmeInfoCA()) != 0)
		{
			r->bfmeApplyCA(info->m_bfmePlainCA);
			return;
		}
		else
			colour = 0xff000000;
	}

	r->bfmeApplyCA(colour);
}
