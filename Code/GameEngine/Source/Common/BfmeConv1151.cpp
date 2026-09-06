// cl: /Od
// Open-BFME5 conversions.

extern "C" void __cdecl bfmeSwapC1151(int *a, int *b);

class BfmeA1151
{
public:
	void bfmeSwap1151(BfmeA1151 *o);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
};

void BfmeA1151::bfmeSwap1151(BfmeA1151 *o)
{
	// /Od picks frame slots by a name-derived order, so every local name below
	// is load bearing: change one and the ebp offsets permute. Re-verify with
	// ./build.sh after any rename here.
	int first;
	int second;
	int *theirs;
	int *self;

	first = m_bfme00;
	m_bfme00 = o->m_bfme00;
	o->m_bfme00 = first;

	// The second field is swapped through addresses taken up front, unlike the
	// first: retail keeps both `lea`s live across the exchange, and rewriting
	// this as a direct three-line swap folds them away.
	theirs = &o->m_bfme04;
	self = &m_bfme04;
	second = *self;
	*self = *theirs;
	*theirs = second;

	bfmeSwapC1151(&m_bfme08, &o->m_bfme08);
}
