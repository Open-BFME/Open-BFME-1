// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x00219800. If flags bit 0 is set, look up this+0xBC through
// TheCaveSystem's bfmeFind1101 and call the result with the two pointer args
// and (flags >> 3) & 0xFFFFFF01.

class BfmeK1101
{
public:
	void bfmeDo(void *a, void *b, int flags);
};

class BfmeJ1101
{
public:
	BfmeK1101 *bfmeFind1101(int key);
};

// The DIR32 at 0x012F086C is retail's `CaveSystem *TheCaveSystem`
// (?TheCaveSystem@@3PAVCaveSystem@@A). CaveSystem is declared by
// game/GameEngine/Source/Common/System/game_engine_subsystems.h, so it is only
// forward-declared here and this TU's own view of it, BfmeJ1101, is reached
// through a cast rather than a second CaveSystem definition in this TU.
class CaveSystem;

extern CaveSystem *TheCaveSystem;

class Gen_00219800
{
public:
	void bfmeDispatch(void *a, void *b, unsigned flags);

private:
	char m_pad[0xBC];
	int m_key;
};

// ?bfmeDispatch@Gen_00219800@@QAEXPAX0I@Z
void Gen_00219800::bfmeDispatch(void *a, void *b, unsigned flags)
{
	if (flags & 1)
	{
		BfmeK1101 *k = ((BfmeJ1101 *)TheCaveSystem)->bfmeFind1101(m_key);
		int bits = (int)(flags >> 3);
		bits &= (int)0xFFFFFF01;
		k->bfmeDo(a, b, bits);
	}
}
