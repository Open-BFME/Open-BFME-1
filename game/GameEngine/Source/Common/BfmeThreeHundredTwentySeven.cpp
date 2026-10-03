class BfmeItemRY
{
};

// The retail loop at 0x00150E50 calls the five-byte ILT thunk at 0x0002852E,
// whose address-derived identity is ?j_0002852e@@YAXXZ (functions.csv,
// game/gen_small/thunks_019.cpp).  Naming it as itself is what lets this
// object link; the thiscall shape and the walk are unchanged.
extern void j_0002852e();

typedef void (BfmeItemRY::*BfmeDoRY_t)(void *, void *);

struct BfmeNodeRY
{
	BfmeNodeRY *m_bfmeNext;
	void *m_bfmeGap;
	BfmeItemRY *m_bfmeItem;
};

class BfmeListRY
{
public:
	void bfmeAllRY(void *one, void *two);
	unsigned char m_bfmeHead[4];
	BfmeNodeRY *m_bfmeEnd;
};

void BfmeListRY::bfmeAllRY(void *one, void *two)
{
	union { void (__cdecl *raw)(); BfmeDoRY_t member; } call;
	call.raw = j_0002852e;
	for (BfmeNodeRY *at = m_bfmeEnd->m_bfmeNext; at != m_bfmeEnd; at = at->m_bfmeNext)
		(at->m_bfmeItem->*call.member)(one, two);
}
