// cl: /Oy-
// Open-BFME5 conversions.

class BfmeStreamSZA
{
public:
	virtual void bfmeV0SZA() = 0;
	virtual void bfmeV1SZA() = 0;
	virtual void bfmeV2SZA() = 0;
	virtual void bfmeV3SZA() = 0;
	virtual void bfmeV4SZA() = 0;
	virtual void bfmeV5SZA() = 0;
	virtual void bfmeV6SZA() = 0;
	virtual void bfmeV7SZA() = 0;
	virtual void bfmeV8SZA() = 0;
	virtual void bfmeV9SZA() = 0;
	virtual void bfmeV10SZA() = 0;
	virtual void bfmeV11SZA() = 0;
	virtual void bfmeV12SZA() = 0;
	virtual void bfmeV13SZA() = 0;
	virtual BfmeStreamSZA *bfmeAddSZA(const char *s) = 0;
};

struct BfmeRecSZA
{
	char m_bfmePad[0xb8];
	unsigned m_bfmeAddr;
};

struct BfmeCtxSZA
{
	char m_bfmePad[4];
	BfmeRecSZA *m_bfmeRec;
};

void bfmeSymbolSZA(unsigned a, char *buf, unsigned n);

void bfmeGoSZA(BfmeStreamSZA *out, BfmeCtxSZA *ctx)
{
	char m_bfmeBuf[0x200];
	bfmeSymbolSZA(ctx->m_bfmeRec->m_bfmeAddr, m_bfmeBuf, 0x200);
	out->bfmeAddSZA("Exception occured at\n")->bfmeAddSZA(m_bfmeBuf)->bfmeAddSZA(".");
}
