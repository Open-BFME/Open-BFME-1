struct BfmeSubBID
{
	unsigned char m_bfmeHead[4];
};

// Retail's call enters the 5-byte ILT at 0x0002F333
// (game/gen_small/thunks_022.cpp, ?j_0002f333@@YAXXZ), which tail-jumps to
// 0x0075B550. That ILT is the only definition of the address, so call it under
// its defined name with the callee's thiscall shape. VC7.1 reserves
// __thiscall in a free-function-pointer typedef, so use the established
// pointer-to-member cast idiom.
extern void j_0002f333();
struct BfmeSubBIDCallView { void call(void *what); };
typedef void (BfmeSubBIDCallView::*BfmeSubBIDCall)(void *what);

class BfmeThingBID
{
public:
	BfmeThingBID *bfmeGoBID(void *what);
	unsigned char m_bfmeHead[4];
	BfmeSubBID m_bfmeSub;
};

BfmeThingBID *BfmeThingBID::bfmeGoBID(void *what)
{
	union { void (*asFunction)(); BfmeSubBIDCall asMember; } doBidCast;
	doBidCast.asFunction = j_0002f333;
	(reinterpret_cast<BfmeSubBIDCallView *>(&m_bfmeSub)->*doBidCast.asMember)(what);
	return this;
}