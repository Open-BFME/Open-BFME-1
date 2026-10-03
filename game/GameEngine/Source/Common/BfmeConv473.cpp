struct BfmeSubBIF
{
	unsigned char m_bfmeHead[4];
};

// Retail's call enters the 5-byte ILT at 0x000100A0
// (game/gen_small/thunks_007.cpp, ?j_000100a0@@YAXXZ), which tail-jumps to
// 0x0046B750. That ILT is the only definition of the address, so call it under
// its defined name with the callee's thiscall shape. VC7.1 reserves
// __thiscall in a free-function-pointer typedef, so use the established
// pointer-to-member cast idiom.
extern void j_000100a0();
struct BfmeSubBIFCallView { void **call(void *what); };
typedef void **(BfmeSubBIFCallView::*BfmeSubBIFCall)(void *what);

class BfmeThingBIF
{
public:
	void bfmeGoBIF(void *what, void *out);
	unsigned char m_bfmeHead[0x6c];
	BfmeSubBIF m_bfmeSub;
};

void BfmeThingBIF::bfmeGoBIF(void *what, void *out)
{
	union { void (*asFunction)(); BfmeSubBIFCall asMember; } makeBifCast;
	makeBifCast.asFunction = j_000100a0;
	void **got = (reinterpret_cast<BfmeSubBIFCallView *>(&m_bfmeSub)->*makeBifCast.asMember)(what);
	*got = out;
}