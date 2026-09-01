// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

class BfmeChunkVHT
{
public:
	bool bfmeOpenVHT();
	unsigned bfmeCurIdVHT();
	void bfmeCloseVHT();
	unsigned bfmeReadVHT(void *p, unsigned n);
};

class BfmeThingVHT
{
public:
	char bfmeLoadVHT(BfmeChunkVHT *c);
	char m_bfmePad[0x18];
	char m_bfmeData[0x14c];
};

char BfmeThingVHT::bfmeLoadVHT(BfmeChunkVHT *c)
{
	char ok = 0;
	if (c->bfmeOpenVHT())
	{
		if (c->bfmeCurIdVHT() == 0x503)
		{
			memset(m_bfmeData, 0, 0x14c);
			if (c->bfmeReadVHT(m_bfmeData, 0x14c) == 0x14c)
				ok = 1;
			c->bfmeCloseVHT();
		}
	}
	return ok;
}
