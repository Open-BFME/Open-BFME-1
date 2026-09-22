// ?transformRegionToBackend@Rva007845D0@@QAEXXZ
// partial score=0.9938 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /O2 /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
#include "basetype.h"

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

static inline void Rva007845D0Apply(const Rva007845D0Transform *xf, const Coord2D &in, Coord2D *out)
{
	out->x = in.x * xf->m[0] + xf->m[2] * in.y + xf->m[4];
	out->y = in.x * xf->m[1] + xf->m[3] * in.y + xf->m[5];
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
	void transformRegionToBackend(void);

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

void Rva007845D0::transformRegionToBackend(void)
{
	const Rva007845D0Transform *xf = m_byte2c ? &g_Rva00F06914Transform : &g_Rva00F0692CTransform;
	Region2D screen;
	Rva007845D0Apply(xf, m_region.lo, &screen.lo);
	Rva007845D0Apply(xf, m_region.hi, &screen.hi);
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
