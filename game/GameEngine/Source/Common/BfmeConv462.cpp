class BfmeThingBGG
{
public:
	void bfmeGoBGG();
	unsigned char m_bfmeHead[0x38];
	void *m_bfmeWhat;
	unsigned char m_bfmeGap[7];
	bool m_bfmeFlag;
};

// Retail's call enters the 5-byte ILT at 0x00015E0B
// (game/gen_small/thunks_010.cpp, ?j_00015e0b@@YAXXZ), which tail-jumps to
// 0x002B2070. That ILT is the only definition of the address, so call it under
// its defined name with the callee's thiscall shape. VC7.1 reserves
// __thiscall in a free-function-pointer typedef, so use the established
// pointer-to-member cast idiom.
extern void j_00015e0b();
struct BfmeThingBGGCallView { void call(); };
typedef void (BfmeThingBGGCallView::*BfmeThingBGGCall)(void);

void BfmeThingBGG::bfmeGoBGG()
{
	union { void (*asFunction)(); BfmeThingBGGCall asMember; } stepCast;
	stepCast.asFunction = j_00015e0b;
	(reinterpret_cast<BfmeThingBGGCallView *>(this)->*stepCast.asMember)();
	if (m_bfmeWhat != 0)
		m_bfmeFlag = true;
}