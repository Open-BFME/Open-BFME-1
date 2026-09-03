// Open-BFME5 conversion.

struct BfmeQ1206
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

extern "C" BfmeQ1206 g_bfmeD1206;

struct BfmeM1208
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
	float m_bfme0c;
	float m_bfme10;
	float m_bfme14;
};

void bfmeMul1208(const BfmeM1208 *a, const BfmeM1208 *b, BfmeM1208 *out);

struct BfmeNode008AE2E0
{
	char m_padding00[0x10];
	char m_transform[0x18];
	char m_padding28[0x24];
	BfmeNode008AE2E0 *m_next;
};

class BfmeA1236
{
public:
	void bfmeMark1236(void);
	void bfmeSet1236(void *value);
	void bfmePop1236(void);
};

class BfmeN1235
{
public:
	void bfmeDo1235(void *a, void *b);
};

struct Rva8BB1A0Bounds
{
	float left;
	float top;
	float right;
	float bottom;
};

class Rva8BB1A0BoundsSource
{
public:
	void getBounds(Rva8BB1A0Bounds *bounds);

private:
	char m_padding00[0x4C];
	BfmeNode008AE2E0 *m_node;
};

extern BfmeA1236 *g_bfmeStack008AE2E0;
extern int g_bfmeB1038;

void Rva8BB1A0BoundsSource::getBounds(Rva8BB1A0Bounds *bounds)
{
	int v00 = g_bfmeD1206.m_bfme00;
	int v08 = g_bfmeD1206.m_bfme08;
	int v04 = g_bfmeD1206.m_bfme04;
	BfmeQ1206 local;
	int v0c = g_bfmeD1206.m_bfme0c;
	int v10 = g_bfmeD1206.m_bfme10;
	int v14 = g_bfmeD1206.m_bfme14;
	local.m_bfme00 = v00;
	local.m_bfme04 = v04;
	local.m_bfme08 = v08;
	local.m_bfme0c = v0c;
	local.m_bfme10 = v10;
	local.m_bfme14 = v14;

	for (BfmeNode008AE2E0 *node = m_node; node; node = node->m_next)
		bfmeMul1208((BfmeM1208 *)&local, (BfmeM1208 *)&node->m_transform, (BfmeM1208 *)&local);

	g_bfmeStack008AE2E0->bfmeMark1236();
	g_bfmeStack008AE2E0->bfmeSet1236(&local);

	unsigned *u = (unsigned *)bounds;
	u[2] = 0xCE6E6B28;
	u[3] = 0xCE6E6B28;
	u[0] = 0x4E6E6B28;
	u[1] = 0x4E6E6B28;

	((BfmeN1235 *)this)->bfmeDo1235((void *)g_bfmeB1038, bounds);
	g_bfmeStack008AE2E0->bfmePop1236();
}
