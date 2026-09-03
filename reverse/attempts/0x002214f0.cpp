// ?bfmeSetup@Gen_002214F0@@QAEXPAVBfmeThingGJ@@H0@Z
// partial score=0.79 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x002214F0 three-field hand-off. Count floored at one via a
// max-by-reference that leaves the literal on the stack; then two +0x74
// source fields stored at this+0x9C and this+0xA0.

class BfmeThingGJ
{
public:
	char m_pad[0x74];
	int m_field74;
};

class Gen_002214F0
{
public:
	void bfmeSetup(BfmeThingGJ *a, int n, BfmeThingGJ *b);

private:
	char m_pad[0x9C];
	int m_9c;
	int m_a0;
	int m_a4;
};

// ?bfmeSetup@Gen_002214F0@@QAEXPAVBfmeThingGJ@@H0@Z
void Gen_002214F0::bfmeSetup(BfmeThingGJ *a, int n, BfmeThingGJ *b)
{
	int one = 1;
	int *pone = &one;
	m_a4 = *(n > 1 ? &n : pone);
	m_9c = a->m_field74;
	m_a0 = b->m_field74;
}
