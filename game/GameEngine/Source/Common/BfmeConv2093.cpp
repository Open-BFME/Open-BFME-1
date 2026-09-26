class Object
{
public:
	unsigned char m_bfmeHeadXW[0x90];
	unsigned char m_bfme90XW;
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadXW[0x3c];
	int m_bfme3CXW;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeHostXW
{
public:
	void bfmeSetXW(int when);
	void bfmeApplyXW(Object *obj, int value);

	unsigned char m_bfmeHeadXW[8];
	Object *m_bfme08XW;
};

void BfmeHostXW::bfmeSetXW(int when)
{
	Object *obj = m_bfme08XW;

	if (obj->m_bfme90XW & 1)
		return;

	int v;

	if (when != 0 && when != 0x3fffffff)
		v = when - TheBfmeGameLogic->m_bfme3CXW;
	else
		v = 0x3fffffff;

	bfmeApplyXW(obj, v);
}
