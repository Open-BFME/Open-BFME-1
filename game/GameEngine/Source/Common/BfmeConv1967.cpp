// Retail reaches both helpers through the five-byte ILT thunks at 0x0003472F
// and 0x0003DA46, which the ledger owns as ?j_0003472f@@YAXXZ and
// ?j_0003da46@@YAXXZ (game/gen_small/thunks_025.cpp, thunks_029.cpp).  Both
// call sites keep ECX as the receiver and push every real argument, so they are
// spelled as thiscall member pointers taken from the thunk symbols: that keeps
// the direct ILT relocation and the ECX-plus-stack-argument shape.
extern void j_0003472f();
extern void j_0003da46();

struct BfmeEntryESC
{
	unsigned char m_bfmeHeadESC[0xdc];
	int m_bfmeDCESC;
	int m_bfmeE0ESC;
	int m_bfmeE4ESC;
	int m_bfmeE8ESC;
	int m_bfmeECESC;
	int m_bfmeF0ESC;
	unsigned char m_bfmeF4ESC;
	unsigned char m_bfmeF5ESC;
};

class BfmeHostESC
{
public:
	void bfmeSendESC(void *ctx, int index);

	unsigned char m_bfmeBodyESC[4];
};

void BfmeHostESC::bfmeSendESC(void *ctx, int index)
{
	BfmeEntryESC *entry = (BfmeEntryESC *)((char *)this + index * 0x1c);

	union { void (*raw)(); void (BfmeHostESC::*member)(void *, int, unsigned char, int, int, int, int, unsigned char, int); } callRoute;
	callRoute.raw = j_0003472f;
	(this->*callRoute.member)(ctx, entry->m_bfmeDCESC, entry->m_bfmeF5ESC, entry->m_bfmeECESC,
		entry->m_bfmeE8ESC, *(int *)((char *)this + (index + 8) * 0x1c),
		entry->m_bfmeE4ESC, entry->m_bfmeF4ESC, entry->m_bfmeF0ESC);

	union { void (*raw)(); void (BfmeHostESC::*member)(int); } doneRoute;
	doneRoute.raw = j_0003da46;
	(this->*doneRoute.member)(index);
}
