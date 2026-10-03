// The two guarded dispatches at [this+0x2c] and [this+0x28] are retail's calls
// through the ILT thunk 0x000461CD, whose five bytes are `jmp 0x0048A280`. That
// body is the ledger's matched TransitionGroup::draw
// (game/GameEngine/Source/GameClient/GUI/GameWindowTransitionGroupInit.cpp,
// 43 bytes at 0x0048A280), a thiscall member with no stack arguments, which is
// exactly the shape the two call sites encode. So the guarded objects are
// TransitionGroup and the reference carries that defining name; the placeholder
// BfmeSubBPE::bfmeOneBPE nothing defined is gone.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class TransitionGroup
{
public:
	void draw(void);
};

class BfmeThingBPE
{
public:
	void bfmeGoBPE();
	unsigned char m_bfmeHead[0x28];
	TransitionGroup *m_bfmeB;
	TransitionGroup *m_bfmeA;
};

void BfmeThingBPE::bfmeGoBPE()
{
	TransitionGroup *a = m_bfmeA;
	if (a != 0)
		a->draw();
	TransitionGroup *b = m_bfmeB;
	if (b != 0)
		b->draw();
}
