// _bfmeReload1221
// partial score=0.8 date=2026-09-11
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The ledger size 275 is six bytes short and cuts this body inside shr eax,0x12.
// The real body runs 281 bytes. Its ret sits at +0x118, seven int3 bytes pad to
// +0x11f, and bfmeNext1221 starts at 0x008D3C00. Probe with --size 281.
//
// The first twist loop matches retail byte for byte. The second loop is a clean
// two-register swap: retail holds the lag pointer in ebx and the mixed word in
// edx, and this body holds them the other way round. Declaring lag before the
// loop, dropping the register qualifier and storing an unnamed temporary instead
// of a named local all leave the swap in place. The tail after the second loop
// also reorders: retail loads state[0] into esi, mixes into eax, stores, then
// tempers from a saved copy in edx, while MSVC hoists the lag read into ebp and
// starts tempering before the store.

extern int g_bfmeIndexFA;
extern unsigned int g_bfmeStateFA[];
extern unsigned int *g_bfmeNext1221;
extern void bfmeSeed(int seed);

extern "C" unsigned int bfmeReload1221(void)
{
	unsigned int *entry = &g_bfmeStateFA[0];
	unsigned int *next = &g_bfmeStateFA[2];

	if (g_bfmeIndexFA < -1)
		bfmeSeed(0x1105);

	int previous = g_bfmeStateFA[0];
	int value = g_bfmeStateFA[1];

	g_bfmeIndexFA = 0x26f;
	g_bfmeNext1221 = &g_bfmeStateFA[1];

	int count = 0xe3;
	do
	{
		unsigned int mixed = value ^ previous;
		mixed = (mixed & 0x7ffffffe) ^ previous;
		mixed >>= 1;
		mixed ^= ((value & 1) ? 0x9908b0df : 0);
		mixed ^= next[395];
		*entry = mixed;

		previous = value;
		value = *next;
		++entry;
		++next;
	}
	while (--count != 0);

	int *lag = (int *)&g_bfmeStateFA[0];
	count = 0x18c;
	do
	{
		unsigned int secondMixed = value ^ previous;
		secondMixed = (secondMixed & 0x7ffffffe) ^ previous;
		secondMixed >>= 1;
		secondMixed ^= ((value & 1) ? 0x9908b0df : 0);
		secondMixed ^= *lag;
		*entry = secondMixed;

		previous = value;
		value = *next;
		++entry;
		++lag;
		++next;
	}
	while (--count != 0);

	int first = g_bfmeStateFA[0];
	unsigned int mixed = first ^ previous;
	mixed = (mixed & 0x7ffffffe) ^ previous;
	mixed >>= 1;
	mixed ^= ((first & 1) ? 0x9908b0df : 0);
	mixed ^= *lag;
	*entry = mixed;

	unsigned int result = first;
	result ^= result >> 11;
	result ^= (result << 7) & 0xff3a58ad;
	result ^= (result << 15) & 0xffffdf8c;
	return result ^ (result >> 18);
}
