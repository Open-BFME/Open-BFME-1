struct BfmeSubBJF
{
	void bfmeDoBJF(void *one, void *two, int flag);
	unsigned char m_bfmeHead[4];
};

class BfmeThingBJF
{
public:
	void bfmeGoBJF(void *one, void *two);
	unsigned char m_bfmeHead[0x14];
	BfmeSubBJF m_bfmeSub;
};

// The forward reaches the ILT thunk at 0x00006C58
// (`?j_00006c58@@YAXXZ`, game/gen_small/thunks_002.cpp), so the callee is
// named by the thunk holding the body at that address.

extern void j_00006c58();

void BfmeThingBJF::bfmeGoBJF(void *one, void *two)
{
	typedef void (BfmeSubBJF::*Call)(void *, void *, int);
	union { void (*raw)(); Call forward; } call;

	call.raw = j_00006c58;
	(m_bfmeSub.*call.forward)(one, two, 1);
}
