// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: AptPalantir vtable 0x01127A48 slot 11 (installed by the matched
// AptPalantir constructor 0x0079D9F0 and destructor 0x0079D1D0) reaches this
// 162-byte body through ILT 0x00045F39. It runs the base
// Rva00597FC0Client::bfmeReset00592B80 (ILT 0x00004002) on the same object,
// then fills the three four-element Coord2D arrays at +0x524/+0x544/+0x564
// (the constructor TU's layout) with zero. The semantic name is unproven, so
// the method keeps an address-derived one like its sibling rva0079dc00.
//
// Each array gets its own zero temporary (retail stores the pair again before
// every fill) and STLport fill reloads the value inside its loop because it
// takes the value by reference.

#include <algorithm>

#include "Lib/Coord2D.h"

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Snapshot
{
public:
	virtual ~Snapshot();
};

class Rva00597FC0Client : public SubsystemInterface, public Snapshot
{
public:
	void bfmeReset00592B80();

private:
	char m_base[0x504];
};

class AptPalantir : public Rva00597FC0Client
{
public:
	virtual void rva0079d3a0();

private:
	char m_pad510[0x524 - 0x510];
	Coord2D m_coords524[4];
	Coord2D m_coords544[4];
	Coord2D m_coords564[4];
};

static inline Coord2D zeroCoord()
{
	Coord2D c;
	c.x = 0;
	c.y = 0;
	return c;
}

void AptPalantir::rva0079d3a0()
{
	bfmeReset00592B80();
	_STL::fill(m_coords524, m_coords524 + 4, zeroCoord());
	_STL::fill(m_coords544, m_coords544 + 4, zeroCoord());
	_STL::fill(m_coords564, m_coords564 + 4, zeroCoord());
}
