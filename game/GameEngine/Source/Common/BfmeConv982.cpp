// Open-BFME5 conversions.
// cl: /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

#include "../../../Libraries/Source/WWVegas/WWLib/basetype.h"

class BfmeZ982;

class BfmeY982
{
public:
	virtual void bfmeVY0982();
	virtual void bfmeVY1982();
	virtual void bfmeVY2982();
	virtual void bfmeVY3982();
	virtual void bfmeVY4982();
	virtual void bfmeVY5982();
	virtual BfmeZ982 *bfmeNext982B();

	BfmeY982 *bfmeConv982B();
};

class BfmeSrc982
{
public:
	virtual void bfmeVS0982();
	virtual void bfmeVS1982();
	virtual void bfmeVS2982();
	virtual void bfmeVS3982();
	virtual void bfmeVS4982();
	virtual void bfmeVS5982();
	virtual void bfmeVS6982();
	virtual void bfmeVS7982();
	virtual void bfmeVS8982();
	virtual void bfmeVS9982();
	virtual void bfmeVS10982();
	virtual void bfmeVS11982();
	virtual void bfmeVS12982();
	virtual void bfmeVS13982();
	virtual void bfmeVS14982();
	virtual void bfmeVS15982();
	virtual void bfmeVS16982();
	virtual void bfmeVS17982();
	virtual void bfmeVS18982();
	virtual void bfmeVS19982();
	virtual void bfmeVS20982();
	virtual void bfmeVS21982();
	virtual void bfmeVS22982();
	virtual void bfmeVS23982();
	virtual void bfmeVS24982();
	virtual void bfmeVS25982();
	virtual BfmeY982 *bfmeGet982B(int a);
};

class BfmeOut982
{
public:
	virtual void bfmeVO0982();
	virtual void bfmeVO1982();
	virtual void bfmeVO2982();
	virtual void bfmeVO3982();
	virtual void bfmeVO4982();
	virtual void bfmeVO5982();
	virtual void bfmeVO6982();
	virtual void bfmeVO7982();
	virtual void bfmeVO8982();
	virtual void bfmeVO9982();
	virtual void bfmeVO10982();
	virtual void bfmeVO11982();
	virtual void bfmeVO12982();
	virtual void bfmeVO13982();
	virtual void bfmeVO14982();
	virtual void bfmeVO15982();
	virtual void bfmeVO16982();
	virtual void bfmeVO17982();
	virtual void bfmeSend982B(BfmeZ982 *z);
};

extern BfmeSrc982 *g_bfmeSrc982;
extern BfmeOut982 *g_bfmeOut982;

void __stdcall bfmeGo982B(int a)
{
	BfmeY982 *y = g_bfmeSrc982->bfmeGet982B(a);

	if (!y)
		return;

	BfmeZ982 *z = y->bfmeConv982B()->bfmeNext982B();

	if (!z)
		return;

	g_bfmeOut982->bfmeSend982B(z);
}

class BfmeT982
{
public:
	void bfmeTouch982C();
};

class BfmeHub982
{
public:
	void bfmeBegin982C();
	void bfmeEnd982C();
};

extern BfmeHub982 *g_bfmeHub982;

void bfmeStep982C(void);

void bfmeGo982C(BfmeT982 *t)
{
	if (!t)
		return;

	bfmeStep982C();

	if (!g_bfmeHub982)
		return;

	g_bfmeHub982->bfmeBegin982C();
	t->bfmeTouch982C();
	g_bfmeHub982->bfmeEnd982C();
}

int __cdecl bfmeHelpWI(int color);

struct Rva007845D0Transform
{
	float m[6];
};

extern Rva007845D0Transform g_Rva00F06914Transform;
extern Rva007845D0Transform g_Rva00F0692CTransform;

class Rva007845D0Backend
{
public:
	virtual void slot00(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(int a, int b);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(int x, int y);
	virtual void slot38(int x, int y, int a, int b);
	virtual void slot3c(void);
	virtual void slot40(void);
	virtual void slot44(void);
	virtual void slot48(float a, float b);
};

static inline void Rva007845D0Apply(
	const Rva007845D0Transform *xf, const Coord2D &in, Coord2D *out)
{
	out->x = in.x * xf->m[0] + xf->m[2] * in.y + xf->m[4];
	out->y = in.x * xf->m[1] + xf->m[3] * in.y + xf->m[5];
}

static inline void Rva007845D0ApplyHigh(
	const Rva007845D0Transform *xf, const Coord2D &in, Coord2D *out)
{
	out->x = in.x * xf->m[0] + xf->m[2] * in.y + xf->m[4];
	float y = xf->m[3] * in.y;
	y = y + xf->m[1] * in.x;
	out->y = y + xf->m[5];
}

static inline float Rva007845D0Ratio(float b, float a)
{
	if (b < 0.0001f)
		return 1.0f;
	if (fabs(a - b) < 0.01f)
		return 1.0f;
	return a / b;
}

class Rva007845D0
{
public:
	void method(void);

	char m_pad00[8];
	Rva007845D0Backend *m_backend;
	Region2D m_region;
	float m_width;
	float m_height;
	int m_color;
	int m_align;
	bool m_byte2c;
	bool m_byte2d;
	bool m_byte2e;
};

void Rva007845D0::method(void)
{
	const Rva007845D0Transform *xf = m_byte2c
		? &g_Rva00F06914Transform : &g_Rva00F0692CTransform;
	Region2D screen;
	Rva007845D0Apply(xf, m_region.lo, &screen.lo);
	Rva007845D0ApplyHigh(xf, m_region.hi, &screen.hi);
	float ratioX = Rva007845D0Ratio(m_region.width(), screen.width());
	float ratioY = Rva007845D0Ratio(m_region.height(), screen.hi.y - screen.lo.y);
	float w = ratioX * m_width;
	float h = ratioY * m_height;
	float maxW = screen.width();
	if (w > maxW)
	{
		ratioX = Rva007845D0Ratio(w, maxW);
		w = maxW;
	}
	if (ratioX == 1.0f && ratioY == 1.0f)
		m_backend->slot48(0, 0);
	else
		m_backend->slot48(w, h);
	Rva007845D0Backend *backend = m_backend;
	backend->slot28(bfmeHelpWI(m_color), bfmeHelpWI(0xff000000));
	float x = screen.lo.x;
	switch (m_align)
	{
	case 1:
		x = screen.hi.x - w;
		break;
	case 2:
		x = (screen.width() - w) * 0.5f + screen.lo.x;
		break;
	}
	float y = screen.lo.y;
	if (m_byte2e)
		y = (m_region.height() - m_height) * 0.5f + screen.lo.y;
	if (m_byte2d)
		m_backend->slot38((int)x, (int)y, 1, 1);
	else
		m_backend->slot34((int)x, (int)y);
}
