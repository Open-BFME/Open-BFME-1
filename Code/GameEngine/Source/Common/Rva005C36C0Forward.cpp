// Address-derived struct-returning forwarder at retail RVA 0x005C36C0.
// The guarded pointer at +0x1C4 is independently proven to be the receiver:
// retail leaves it in ECX for the call through ILT 0x0002F4AA to the matched
// 0x005FAE40 body.  The public owner and method identity remain unknown.

typedef float Real;

extern const Real g_bfmeK1239;
extern const Real g_bfmeK1253;

struct Rva005C36C0Vec3
{
	Rva005C36C0Vec3(Real xValue, Real yValue, Real zValue)
		: x(xValue), y(yValue), z(zValue) {}

	Real x;
	Real y;
	Real z;
};

class BfmeG1269
{
public:
	unsigned char m_head[0xAB4];
	Real m_valueAB4;
};

extern BfmeG1269 *g_bfme1269;

class Rva005FAE40Receiver
{
public:
	Rva005C36C0Vec3 rva005FAE40(void *owner, Real scale, void *first, void *second);
};

class Rva005C36C0Owner
{
public:
	Rva005C36C0Vec3 rva005C36C0(void *first, void *second);

private:
	unsigned char m_head[0x180];
	void *m_value180;
	unsigned char m_mid[0x40];
	Rva005FAE40Receiver *m_receiver;
};

Rva005C36C0Vec3 Rva005C36C0Owner::rva005C36C0(void *first, void *second)
{
	if (m_receiver != 0)
		return m_receiver->rva005FAE40(m_value180,
			(*(volatile Real *)&g_bfme1269->m_valueAB4 + g_bfmeK1239) * g_bfmeK1253,
			first, second);

	return Rva005C36C0Vec3(0, 0, 0);
}
