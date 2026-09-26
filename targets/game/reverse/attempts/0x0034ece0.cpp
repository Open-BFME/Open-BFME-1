// ?bfmeAddDP@BfmeHostDP@@QAEXPAVBfmeKeyDP@@PAX@Z (identity unknown)
// partial score=0.9 date=2026-09-07
// 145/146. The shape is settled: guard, lazy `new BfmeMapDP` under the SEH
// frame the allocation needs, an optional resolve through key->m_4, then
// `*map->slot(&key) = value`.
// Key detail already applied below: assign the resolved pointer BACK TO THE
// PARAMETER (`key = key->m_bfmeAltDP->bfmeResolveDP();`) so its address is the
// parameter home slot, which is what retail uses. A separate named local costs
// an extra `push ecx` slot (149), and seeding a named local from the parameter
// costs 147.
// Residue: the SEH prologue FORM. retail is
//   mov eax,fs:[0] / push -1 / push handler / push eax / mov fs:[0],esp
// MSVC emits
//   push -1 / push handler / mov eax,fs:[0] / push eax / mov fs:[0],esp
// See [[seh-prologue-has-two-forms]] -- the landed bodies that got retail's
// form all had a named local object with a constructor in scope; this one has
// only a `new` expression, and no arrangement tried reaches the other form.
class BfmeKeyDP;

class BfmeAltDP
{
public:
	BfmeKeyDP *bfmeResolveDP();
};

class BfmeKeyDP
{
public:
	unsigned char m_bfmeHeadDP[4];
	BfmeAltDP *m_bfmeAltDP;
};

class BfmeMapDP
{
public:
	BfmeMapDP();

	void **bfmeSlotDP(BfmeKeyDP **key);

	unsigned char m_bfmePadDP[0xc];
};

class BfmeHostDP
{
public:
	void bfmeAddDP(BfmeKeyDP *key, void *value);

	unsigned char m_bfmeHeadDP[0xc];
	BfmeMapDP *m_bfmeMapDP;
};

void BfmeHostDP::bfmeAddDP(BfmeKeyDP *key, void *value)
{
	if (key == 0)
		return;

	if (m_bfmeMapDP == 0)
		m_bfmeMapDP = new BfmeMapDP;

	if (key->m_bfmeAltDP != 0)
		key = key->m_bfmeAltDP->bfmeResolveDP();

	*m_bfmeMapDP->bfmeSlotDP(&key) = value;
}
