// cl: /EHs-c-
//
// 3D sibling of U4Blend006095D0::blend2 (0x006096A0, 86B).
// Retail 0x00609600 (117B): evaluate the +0x18 curve three times and write
// lo + (hi - lo) * t into a Coord3D out-parameter.

// ILT 0x00038EBF routes to the curve evaluator at 0x0006A520; retail calls through it.
extern void j_00038ebf();

class U4Curve006095D0
{
public:
	// FCurve.cpp defines the body (0x0006A520); calls bind through ILT 0x00038EBF.
	float evaluate(int t) const;
	// 0x00609710 passes the time as a real float through the same ILT.
	float evaluate(float t) const
	{
		typedef float (U4Curve006095D0::*Evaluate)(float) const;
		union { void (*fn)(); Evaluate call; } route = { j_00038ebf };
		return (this->*route.call)(t);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

struct U4Blend006095D0
{
	char m_pad[0x18];
	U4Curve006095D0 m_curve;
	void blend3(const Coord3D *lo, const Coord3D *hi, Coord3D *out, int t) const;
};

// ?blend3@U4Blend006095D0@@QBEXPBUCoord3D@@0PAU2@H@Z
void U4Blend006095D0::blend3(const Coord3D *lo, const Coord3D *hi, Coord3D *out, int t) const
{
	int tt = t;
	const U4Curve006095D0 *curve = &m_curve;
	float k = curve->evaluate(tt);
	const Coord3D *a = lo;
	const Coord3D *b = hi;
	Coord3D *o = out;
	float lx = a->x;
	float hx = b->x;
	o->x = lx + (hx - lx) * k;
	k = curve->evaluate(tt);
	float ly = a->y;
	float hy = b->y;
	o->y = ly + (hy - ly) * k;
	k = curve->evaluate(tt);
	float lz = a->z;
	float hz = b->z;
	o->z = lz + (hz - lz) * k;
}

class Keyboard
{
public:
	bool isShift();
};
extern Keyboard *TheKeyboard;

class GlobalData
{
public:
	char m_pad000[0x90];
	bool m_flag90;
};
extern GlobalData *TheWritableGlobalData;
extern float g_bfmeDefaultBU;

// Retail 0x00609710 (181B), reached only through the address-derived guard
// Rva00609850. The owner advances its blend time (ten times faster with
// shift held when the global +0x90 flag is set), clamps it at
// g_bfmeDefaultBU, blends the +0x44/+0x50 positions through blend3 above
// into virtual slot 25, then sends low + (high - low) * curve(time) to
// virtual slot 16. The owner class is unproven, so the view keeps the
// address.
class Rva00609710Owner
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(float value);
	virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24();
	virtual void slot25(const Coord3D *position);

	void rva00609710();

	char m_pad04[0x14];
	U4Curve006095D0 m_curve;
	char m_pad1c[0x44 - 0x1c];
	Coord3D m_from;
	Coord3D m_to;
	float m_time;
	bool m_active;
	float m_rate;
	float m_low;
	float m_high;
};

// ?rva00609710@Rva00609710Owner@@QAEXXZ
void Rva00609710Owner::rva00609710()
{
	if (TheKeyboard->isShift() && TheWritableGlobalData->m_flag90)
		m_time += m_rate * 10.0f;
	else
		m_time += m_rate;
	if (m_time >= g_bfmeDefaultBU)
	{
		m_time = 1.0f;
		m_active = false;
	}
	Coord3D position;
	((const U4Blend006095D0 *)this)->blend3(&m_from, &m_to, &position, *(int *)&m_time);
	slot25(&position);
	float t = m_time;
	float high = m_high;
	float low = m_low;
	float k = m_curve.evaluate(t);
	slot16(low + (high - low) * k);
}
