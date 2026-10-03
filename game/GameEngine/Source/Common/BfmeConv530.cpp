// 0x00045EB7 is retail's 5-byte ILT thunk (?j_00045eb7@@YAXXZ); the callee's
// own identity is not recovered, so the __thiscall is routed through the
// thunk's address.
extern void j_00045eb7();

struct BfmeSlotBTE
{
	unsigned char m_bfmeHead[12];
};

class BfmeThingBTE
{
public:
	void bfmeGoBTE(int at, void *what, void *out);
	unsigned char m_bfmeHead[0x170e0];
	BfmeSlotBTE m_bfmeSlots[1];
};

void BfmeThingBTE::bfmeGoBTE(int at, void *what, void *out)
{
	typedef void **(BfmeSlotBTE::*Make)(void *);
	union { void (*address)(); Make member; } make = { j_00045eb7 };
	void **got = (m_bfmeSlots[at].*make.member)(what);
	*got = out;
}
