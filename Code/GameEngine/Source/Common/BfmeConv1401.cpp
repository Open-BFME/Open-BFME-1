// Open-BFME5 conversions.

struct BfmeMat4VKH
{
	int m_bfmeArr[16];
};

class BfmeThingVKH;

void __stdcall bfmeCalcVKH(BfmeMat4VKH *out, BfmeThingVKH *self, int a);

class BfmeThingVKH
{
public:
	BfmeMat4VKH bfmeGoVKH(int a);
};

BfmeMat4VKH BfmeThingVKH::bfmeGoVKH(int a)
{
	BfmeMat4VKH t;
	bfmeCalcVKH(&t, this, a);
	return t;
}
