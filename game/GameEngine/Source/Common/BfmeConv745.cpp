// The member build (ILT 0x0003F382 -> 0x0036E170) is the matched vector copy
// constructor ??0Gen_0036e170@@QAE@ABV0@@Z (S3VectorCopyConstructors.cpp).
class Gen_0036e170
{
public:
	Gen_0036e170(const Gen_0036e170 &other);
};

class BfmeSubDOF
{
};

struct BfmeOutDOF
{
	int m_bfmeA;
	BfmeSubDOF m_bfmeSub;
};

BfmeOutDOF *bfmeGoDOF(BfmeOutDOF *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	((Gen_0036e170 *)&out->m_bfmeSub)->Gen_0036e170::Gen_0036e170(*(const Gen_0036e170 *)arg);
	return out;
}
