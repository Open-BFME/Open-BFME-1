// cl: /O2
// 0x0090D210: allocate the same 0x48-byte BFME stats object as the matched
// constructor at 0x0090C280, then apply the owner input at +0x3c.
// The class layout and initialization sequence are identical to the matched
// BfmeConv2069.cpp sibling; its apply method lives at 0x0090C9E0.
extern char *g_bfme927Vft;

class BfmeThingGR
{
public:
	BfmeThingGR()
	{
		m_bfmeVftGR = &g_bfme927Vft;
		m_bfmeFlagGR = 0;
		m_bfmeA0GR = 0;
		m_bfmeA1GR = 0;
		m_bfmeA2GR = 0;
		m_bfmeA3GR = 0;
		m_bfmeA4GR = 0;
		m_bfmeA5GR = 0;
		m_bfmeA6GR = 0;
		m_bfmeB0GR = 1;
		m_bfmeB1GR = 1;
		m_bfmeB2GR = 1;
		m_bfmeB3GR = 1;
		m_bfmeOwnerGR = 0;
		m_bfmeC1GR = 0;
		m_bfmeC2GR = 0;
		m_bfmeD0GR = 2;
		m_bfmeD1GR = 0;
	}

	void bfmeApplyGR(int v);

	void *m_bfmeVftGR;
	char m_bfmeFlagGR;
	unsigned char m_bfmePadGR[3];
	int m_bfmeA0GR;
	int m_bfmeA1GR;
	int m_bfmeA2GR;
	int m_bfmeA3GR;
	int m_bfmeA4GR;
	int m_bfmeA5GR;
	int m_bfmeA6GR;
	int m_bfmeB0GR;
	int m_bfmeB1GR;
	int m_bfmeB2GR;
	int m_bfmeB3GR;
	int m_bfmeOwnerGR;
	int m_bfmeC1GR;
	int m_bfmeC2GR;
	int m_bfmeD0GR;
	int m_bfmeD1GR;
};


class Rva0090D210Owner
{
public:
    void createStats();
    char m_pad[0x14];
    BfmeThingGR *m_stats;
    char m_gap[0x3c - 0x18];
    void *m_target;
};

void Rva0090D210Owner::createStats()
{
    BfmeThingGR *p = new BfmeThingGR();
    m_stats = p;
    p->bfmeApplyGR((int)m_target);
}

// Separate vtable target VA 0x0113A6B4 -> 0x0090D7F0. The preceding
// function's switch tables end at this start; ret at 0x0090D854 then int3.
// Same construction sequence and callee as 0x0090D210; identity stays opaque.
class Rva0090D7F0
{
public:
    void method();
    char m_pad[0x14];
    BfmeThingGR *m_stats;
    char m_gap[0x3c - 0x18];
    void *m_target;
};
void Rva0090D7F0::method()
{
    BfmeThingGR *p = new BfmeThingGR();
    m_stats = p;
    p->bfmeApplyGR((int)m_target);
}
