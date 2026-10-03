// The store is followed by a conditional tail into the ILT thunk at 0x00012878
// (`?j_00012878@@YAXXZ`, game/gen_small/thunks_008.cpp), so the callee is
// named by the thunk that actually holds the body at that address.

extern void j_00012878();

class BfmeThingBLA
{
public:
	void bfmeGoBLA(void *what, bool flag);
	unsigned char m_bfmeHead[0x18];
	void *m_bfmeWhat;
};

void BfmeThingBLA::bfmeGoBLA(void *what, bool flag)
{
	typedef void (__stdcall *Step)(int what);
	union { void (*raw)(); Step step; } call;

	m_bfmeWhat = what;
	if (flag)
	{
		call.raw = j_00012878;
		call.step(1);
	}
}
