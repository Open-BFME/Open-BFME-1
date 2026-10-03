typedef float Real;

struct BfmeShadowPartNode;

class BfmeShadowPart
{
public:
	__declspec(noinline) void bfmeSetSize(Real width, Real height);

private:
	char m_bfmePad[0x4];
	BfmeShadowPartNode *m_bfmeClients;
};

class BfmeItemHF;

class BfmeThingHF
{
public:
	void bfmeTellHF(void *first, void *second);

private:
	BfmeItemHF **m_bfmeBegin;
	BfmeItemHF **m_bfmeEnd;
};

struct BfmeThingCRC
{
	unsigned char m_bfmeHead[0x230];
	BfmeShadowPart *m_bfmeA;
	BfmeThingHF *m_bfmeB;
};

union BfmePointerOrReal
{
	void *pointer;
	Real value;
};

void bfmeGoCRC(BfmeThingCRC *thing, void *b, void *c)
{
	BfmeShadowPart *a = thing->m_bfmeA;
	if (a != 0)
	{
		BfmePointerOrReal first = { b };
		BfmePointerOrReal second = { c };
		a->bfmeSetSize(first.value, second.value);
	}
	BfmeThingHF *bb = thing->m_bfmeB;
	if (bb != 0)
		bb->bfmeTellHF(b, c);
}
