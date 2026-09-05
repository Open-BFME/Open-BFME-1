// cl: /DNDEBUG /MD /EHsc
// Retail 0x001901F0: constructor storing BFME water texture names.
// Image/resource names inside a ctor do not identify the owning class;
// this type is RVA-derived.

void *__cdecl operator new[](unsigned int size);

class AsciiString
{
public:
	void set(const AsciiString &other);
private:
	void *m_data;
};

class RetailLayoutString
{
public:
	void set(const char *s, int n);
private:
	void *m_data;
};

class BfmeAskResult
{
public:
	unsigned char m_pad[0x30];
	AsciiString m_str30;
	float m_riverTransparencyMultiplier;
};

class BfmeSubBIA
{
public:
	BfmeAskResult *lastNode00087A80();
};

class BfmeGlobal012F18F0
{
public:
	unsigned char m_pad00[4];
	BfmeSubBIA *m_sub;
};

extern BfmeGlobal012F18F0 *g_bfmeGlobal012F18F0;

static BfmeAskResult *bfmeAskResult()
{
	BfmeGlobal012F18F0 *g = g_bfmeGlobal012F18F0;
	if (g == 0)
		return 0;
	if (g->m_sub == 0)
		return (BfmeAskResult *)g;
	return g->m_sub->lastNode00087A80();
}

class Rva001901F0
{
public:
	void init(int count);

private:
	unsigned char m_pad00[0x10];
	void *m_array;
	void *m_array14;
	int m_count;
	unsigned char m_pad1c[0x31 - 0x1c];
	unsigned char m_flag31;
	unsigned char m_flag32;
	unsigned char m_pad33[0x38 - 0x33];
	unsigned char m_flag38;
	unsigned char m_flag39;
	unsigned char m_pad3a[0x3c - 0x3a];
	Rva001901F0 *m_self;
	unsigned char m_flag40;
	unsigned char m_pad41[3];
	int m_int44;
	AsciiString m_name48;
	RetailLayoutString m_tex4c;
	RetailLayoutString m_tex50;
	RetailLayoutString m_tex54;
	RetailLayoutString m_tex58;
	RetailLayoutString m_tex5c;
	unsigned char m_flag60;
	unsigned char m_pad61[3];
	float m_f64;
	float m_f68;
	float m_f6c;
	float m_f70;
	float m_f74;
	unsigned char m_pad78[0x7c - 0x78];
	float m_riverTransparencyMultiplier;
	void *m_ptr80;
	void *m_ptr84;
};

// ?init@Rva001901F0@@QAEXH@Z
void Rva001901F0::init(int count)
{
	m_array = 0;
	m_array14 = 0;
	m_count = 0;
	m_flag31 = 0;
	m_flag32 = 0;
	m_flag38 = 1;
	m_flag39 = 0;
	m_flag40 = 0;
	m_int44 = 0;
	m_flag60 = 0;

	m_riverTransparencyMultiplier = bfmeAskResult()->m_riverTransparencyMultiplier;

	*(unsigned int *)&m_f70 = 0x3d75c290u;
	*(unsigned int *)&m_f74 = 0x3d75c290u;

	if (count < 2)
		count = 2;

	float *ones = &m_f64;
	m_array = operator new[]((unsigned int)(count * 12));
	m_count = count;
	float one = 1.0f;
	ones[0] = one;
	ones[1] = one;
	ones[2] = one;
	m_self = this;

	m_name48.set(bfmeAskResult()->m_str30);
	m_tex4c.set("Noise0000.tga", 13);
	m_tex50.set("TWAlphaEdge.tga", 15);
	m_tex54.set("WaterSurfaceBubbles.tga", 23);
	m_tex58.set("WaterRippleBump.tga", 19);
	m_tex5c.set("SkyEnv.tga", 10);

	m_ptr80 = 0;
	m_ptr84 = 0;
}
