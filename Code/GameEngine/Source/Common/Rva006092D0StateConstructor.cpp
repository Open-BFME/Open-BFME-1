// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x0060A000 (237 bytes) is Rva006092D0State::Rva006092D0State().
// It installs vtable 0x01115AD0, the table the matched destructor at
// 0x00609E30 restores, and the matched derived constructor at 0x006FC970
// calls it through ILT 0x0000B89D. Its single unwind state destroys the
// curve at +0x18 through ILT 0x000136DD (0x0006A3C0, the inlined STLport
// vector teardown), and the curve setter is the matched
// Rva0006AB10Curve::set at 0x0006AB10.
//
// The curve's record vector is a native STLport vector: its constructor zeroes
// start/finish/end-of-storage and m_current = m_points.end() reloads the
// finish pointer, and clear() is the out-of-line __copy(finish, finish, start)
// at 0x000B98F0. The 16-byte record is the curve's address-derived
// Rva0006AA90Element (Rva0006AB10CurveSet.cpp); its fields are not read here.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Rva0006AA90Element
{
	float m_key;
	float m_real;
	int m_inTangent;
	int m_outTangent;
};

class Rva0006AB10Curve
{
public:
	Rva0006AB10Curve() : m_field0(0), m_field4(0)
	{
		m_current = m_points.end();
		m_dword28 = 0;
		m_dword24 = 0;
		m_dword20 = 0;
		m_dword1c = 0;
	}
	~Rva0006AB10Curve();
	void set(float time, float value, int inTangent, int outTangent);

	int m_field0;
	int m_field4;
	_STL::vector<Rva0006AA90Element> m_points;
	int m_unmodelled14;
	_STL::vector<Rva0006AA90Element>::iterator m_current;
	int m_dword1c;
	int m_dword20;
	int m_dword24;
	int m_dword28;
};

// The unwind funclet's curve teardown (see above) resolves to that ILT.
#pragma comment(linker, "/alternatename:??1Rva0006AB10Curve@@QAE@XZ=?j_000136dd@@YAXXZ")

class BfmeLivingWorldManager
{
public:
	void rva006157c0();
};

class Rva006092D0State;

extern "C" BfmeLivingWorldManager *g_bfmeGameCW;
extern "C" Rva006092D0State *g_bfmeStateDF;

class Rva006092D0State
{
public:
	Rva006092D0State();
	virtual ~Rva006092D0State();

private:
	int m_mode;
	unsigned char m_byte08;
	unsigned char m_byte09;
	unsigned char m_byte0a;
	unsigned char m_byte0b;
	int m_dword0c;
	int m_dword10;
	unsigned char m_byte14;
	unsigned char m_byte15;
	Rva0006AB10Curve m_curve;
	int m_dword44;
	int m_dword48;
	int m_dword4c;
	int m_dword50;
	int m_dword54;
	int m_dword58;
	int m_dword5c;
	unsigned char m_byte60;
	int m_dword64;
	int m_dword68;
	int m_dword6c;
};

Rva006092D0State::Rva006092D0State() :
	m_mode(0), m_byte08(0), m_byte09(0), m_byte0a(0), m_byte0b(0),
	m_dword0c(0), m_dword10(0), m_byte14(0), m_byte15(0)
{
	m_dword44 = 0;
	m_dword48 = 0;
	m_dword4c = 0;
	m_dword50 = 0;
	m_dword54 = 0;
	m_dword58 = 0;
	m_dword5c = 0;
	m_byte60 = 0;
	m_dword64 = 0;
	m_dword68 = 0;
	m_dword6c = 0;
	g_bfmeStateDF = this;
	if (g_bfmeGameCW != 0)
		g_bfmeGameCW->rva006157c0();
	m_curve.m_points.clear();
	m_curve.set(0.0f, 0.0f, 0, 0);
	m_curve.set(1.0f, 1.0f, 0, 0);
}
