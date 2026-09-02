// ?bfmeSwapTop@@YAXPAVBfmeStack7490@@@Z
// partial score=0.99 date=2026-09-02
// Pop the top entry, replace it with a factory product, tail-release the old top.

class BfmeE1218
{
public:
	virtual void retain(void);
	virtual void release(void);
	char bfmeChk1218(void);

	unsigned int m_bfmeFlags;				// +0x04
};

class BfmeStack7490
{
public:
	int m_bfmeCount;					// +0x00
	int m_bfmeGap04;					// +0x04
	BfmeE1218 **m_bfmeArr;					// +0x08
};

BfmeE1218 *__cdecl bfmeMake7490(int flag);			// retail 0x008996B0

// ?bfmeSwapTop@@YAXPAVBfmeStack7490@@@Z
void __cdecl bfmeSwapTop(BfmeStack7490 *stack)
{
	BfmeE1218 *top = stack->m_bfmeArr[stack->m_bfmeCount - 1];

	top->retain();

	BfmeE1218 *again = stack->m_bfmeArr[stack->m_bfmeCount - 1];
	unsigned char mark = (unsigned char)(again->m_bfmeFlags >> 30);

	if ((mark & 1) == 0)
		again->release();

	stack->m_bfmeCount = stack->m_bfmeCount - 1;

	BfmeE1218 *fresh = bfmeMake7490(!top->bfmeChk1218());

	stack->m_bfmeArr[stack->m_bfmeCount] = fresh;
	stack->m_bfmeCount = stack->m_bfmeCount + 1;

	unsigned char freshMark = (unsigned char)(fresh->m_bfmeFlags >> 30);

	if ((freshMark & 1) == 0)
		fresh->retain();

	top->release();
}
