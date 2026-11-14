// cl: /DNDEBUG /MD /Igame/Libraries/Include
// Retail 0x003A1080, 119 bytes, thiscall, ret 0x18. Slot 2 of vtable 0x010C7E28,
// whose slots 1 and 4-6 are the matched Rva003A3770 / Rva003A39C0 / Rva003A3A90 /
// Rva003A3B50 bodies in this directory. The identity is unproven, so the class keeps
// the address (the bank's placeholder class name BfmeThingJG already names an
// unrelated layout at 0x0015BB40).
//
// The call at +0x3F goes through ILT 0x0002A1B2 to the matched
// ?setEaseTimes@ParabolicEase@@QAEXMMM@Z (0x00094970); its receiver is the eight-byte
// sub-object at +0x10, as in the matched sibling Rva0073C700::configure.
// BFME 2 (f6c3838e) has the same body as slot 2 of its vtable 0x00BC7514
// (Code/GameEngine/Source/Common/rva00086B2CRva003114A7Farm.cpp); its source supplied the
// float types of the ease-in/ease-out parameters (a donor fact, not a BFME 1 proof).
// Writing the tail fields 0x3C..0x50 directly, rather than through the bank's inline
// reset() sub-struct, gives retail's setne dl / mov [esi+0x46],dl.
#include "Lib/Coord3D.h"

typedef float Real;

class ParabolicEase
{
public:
	void setEaseTimes(Real easeInTime, Real easeOutTime, Real duration);
private:
	Real m_in;
	Real m_out;
};

static __forceinline void zeroPoint(Coord3D &point)
{
	point.x = 0.0f;
	point.y = 0.0f;
	point.z = 0.0f;
}

class Rva003A1080Owner
{
public:
	void setup(int p1, int p2, Real p3, Real p4, int p5, bool p6);

	unsigned char m_bfmeHeadJG[4];
	int m_bfme04JG;
	int m_bfme08JG;
	int m_bfme0cJG;
	ParabolicEase m_bfmeSubJG;
	int m_bfme18JG;
	int m_bfme1cJG;
	int m_bfme20JG;
	char m_bfme24JG;
	unsigned char m_bfmePad0JG[3];
	int m_bfme28JG;
	unsigned char m_bfmeGap1JG[0xc];
	int m_bfme38JG;
	int m_bfme3cJG;
	int m_bfme40JG;
	char m_bfme44JG;
	char m_bfme45JG;
	bool m_bfme46JG;
	char m_bfmePad1JG;
	Coord3D m_bfme48JG;
};

void Rva003A1080Owner::setup(int p1, int p2, Real p3, Real p4, int p5, bool p6)
{
	int n = p2;
	if (n <= 1)
		n = 1;
	m_bfme04JG = n;
	m_bfme08JG = 0;
	m_bfme18JG = 0;
	m_bfme1cJG = 0;
	m_bfme20JG = 0;
	m_bfme28JG = 1;
	m_bfmeSubJG.setEaseTimes(p3, p4, (Real)p2);
	m_bfme0cJG = p5;
	if (p6)
		m_bfme38JG = 0;
	m_bfme3cJG = 0;
	m_bfme40JG = 0;
	m_bfme45JG = 0;
	m_bfme46JG = m_bfme0cJG != 0;
	zeroPoint(m_bfme48JG);
	m_bfme24JG = 1;
}
