void j_0001abd1();

struct BfmeSubBJC
{
	unsigned char m_bfmeHead[4];
};

class BfmeThingBJC
{
public:
	void *bfmeGoBJC(void *what);
	unsigned char m_bfmeHead[0x9c];
	BfmeSubBJC m_bfmeSub;
};

void *BfmeThingBJC::bfmeGoBJC(void *what)
{
	// Keep the pointer word on the stack while fastcall supplies the subobject in ECX.
	reinterpret_cast<void (__fastcall *)(BfmeSubBJC *, float)>(j_0001abd1)(&m_bfmeSub, *reinterpret_cast<float *>(&what));
	return what;
}
