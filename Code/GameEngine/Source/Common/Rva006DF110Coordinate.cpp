// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x006DF110. The Rva006DF550 vtable and constructor fields identify
// this body as the coordinate and angle calculation for that object.

#include <math.h>

#pragma intrinsic(cos, sin, tan)

typedef float Real;

extern double Gen01085F58;

struct BfmeCoord6DF110
{
	Real x;
	Real y;
	Real z;
};

class Rva006DF550
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();

	void rva006DF110(BfmeCoord6DF110 *, Real *);

	float m_04;
	float m_08;
	float m_0C;
	float m_10;
	float m_14;
	char m_18;
};

// ?rva006DF110@Rva006DF550@@QAEXPAUBfmeCoord6DF110@@PAM@Z
void Rva006DF550::rva006DF110(BfmeCoord6DF110 *out, Real *angle)
{
	if (m_18)
	{
		if (out)
		{
			Real scale = m_08 * *(const Real *)0x0111e184;
			Real radians = m_0C;
			out->x = 0.0f;
			radians *= *(const Real *)0x01087b14;
			radians *= *(const double *)0x0111e178;
			volatile Real cosine = (Real)cos(radians);
			Real sine = (Real)sin(radians);
			out->z = sine * scale;
			out->y = -cosine * scale;
		}
		if (angle)
			*angle = m_10 * *(const Real *)0x01087b14 *
				*(const double *)0x0111e178;
	}
	else
	{
		if (out)
		{
			out->z = m_08;
			out->y = -out->z / (Real)tan(m_0C * *(const double *)0x0111e168);
			out->x = -(tan(m_10 * *(const double *)0x0111e168) * out->y);
		}
		if (angle)
			*angle = 0.0f;
	}
}
