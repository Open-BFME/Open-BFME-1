// Pop the top entry, replace it with a factory product, and tail-release the old top.

class AptValue
{
public:
	virtual void retain(void);
	virtual void release(void);
	bool rva00898480Check(void);

	unsigned int m_bfmeFlags;				// +0x04
};

class BfmeStack7490
{
public:
	int m_bfmeCount;					// +0x00
	int m_bfmeGap04;					// +0x04
	AptValue **m_bfmeArr;					// +0x08
};

void __cdecl d_008996b0(void);			// retail 0x008996B0

// ?bfmeSwapTop@@YAXPAVBfmeStack7490@@@Z
void __cdecl bfmeSwapTop(BfmeStack7490 *stack)
{
	AptValue *top = stack->m_bfmeArr[stack->m_bfmeCount - 1];

	top->retain();

	AptValue *again = stack->m_bfmeArr[stack->m_bfmeCount - 1];
	unsigned char mark = (unsigned char)(again->m_bfmeFlags >> 30);

	if ((mark & 1) == 0)
		again->release();

	stack->m_bfmeCount = stack->m_bfmeCount - 1;

	AptValue *fresh = ((AptValue *(__cdecl *)(unsigned char))d_008996b0)(
		!top->rva00898480Check());

	stack->m_bfmeArr[stack->m_bfmeCount] = fresh;
	stack->m_bfmeCount = stack->m_bfmeCount + 1;

	unsigned char freshMark = (unsigned char)(fresh->m_bfmeFlags >> 30);

	if ((freshMark & 1) == 0)
		fresh->retain();

	top->release();
}
