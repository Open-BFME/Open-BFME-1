// Pop the top stack entry, keep a copy, and release it unless marked.

class BfmeItemB4
{
public:
	virtual void retain(void);
	virtual void release(void);

	unsigned int m_bfmeFlags;				// +0x04
};

class BfmeStackB4
{
public:
	int m_bfmeCount;					// +0x00
	int m_bfmeGap04;					// +0x04
	BfmeItemB4 **m_bfmeArr;					// +0x08
	int m_bfmeGap0C[28];					// +0x0C
	BfmeItemB4 *m_bfmeKept;					// +0x7C
};

// ?bfmePopKeep@@YAXPAVBfmeStackB4@@@Z
void __cdecl bfmePopKeep(BfmeStackB4 *stack)
{
	BfmeItemB4 *top = stack->m_bfmeArr[stack->m_bfmeCount - 1];

	top->retain();
	stack->m_bfmeKept = top;

	BfmeItemB4 *again = stack->m_bfmeArr[stack->m_bfmeCount - 1];
	unsigned char mark = (unsigned char)(again->m_bfmeFlags >> 30);

	if ((mark & 1) == 0)
		again->release();

	stack->m_bfmeCount = stack->m_bfmeCount - 1;
}
