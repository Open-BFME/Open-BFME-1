// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2
//
// Per-frame subtitle-entry render, virtual slot 1 of the video subtitle entry.
// Identity: vtable 0x010F3920 is pinned as ??_7Rva00434810SubtitleEntry@@6B@ and
// its slot 1 (ILT 0x000460A6) jumps here; the matched constructor 0x00434810
// fixes the field layout (color +0x08, style +0x0c, alignment +0x10, line +0x14,
// frames +0x18/+0x1c, display strings +0x24, count +0x30, capacity +0x34).
// The matched broadcaster Rva0081D520Owner::broadcast calls this slot with its
// own receiver as the owner pointer, so the second argument is that owner view.
// The method name stays address-derived: no caller names this slot.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include <math.h>

// Owner view: byte +0x60 selects the alternate coordinate path and the float
// row at +0x24 is indexed by line.  Proven by the decoded helper 0x004340C0.
class Rva0081D520Owner
{
public:
	unsigned char m_unmodelled00[0x24];
	Real m_lineCoordinates[15];
	unsigned char m_alternateMode;
};

extern Int __cdecl bfmeAlignVIL(Int alignment, Int length, Int unused,
	Real low, Real high);
// Line coordinate helper 0x004340C0, defined at the end of this unit.
Int __cdecl rva004340C0SubtitleCoordinate(Int index, Rva0081D520Owner *owner,
	Real low, Real high);

class Display;
extern Display *TheDisplay;

class Rva004341A0DisplayStringView
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28(UnsignedInt color, Int mode);
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34(Int x, Int y);
	virtual void slot38();
	virtual void slot3C(Int *second, Int *first);
	virtual Int slot40(Int index);
};

class Rva004341A0DisplayView
{
public:
#define RVA004341A0_DISPLAY_SLOT(n) virtual void slot##n();
	RVA004341A0_DISPLAY_SLOT(00) RVA004341A0_DISPLAY_SLOT(04)
	RVA004341A0_DISPLAY_SLOT(08) RVA004341A0_DISPLAY_SLOT(0C)
	RVA004341A0_DISPLAY_SLOT(10) RVA004341A0_DISPLAY_SLOT(14)
	RVA004341A0_DISPLAY_SLOT(18) RVA004341A0_DISPLAY_SLOT(1C)
	RVA004341A0_DISPLAY_SLOT(20) RVA004341A0_DISPLAY_SLOT(24)
	RVA004341A0_DISPLAY_SLOT(28) RVA004341A0_DISPLAY_SLOT(2C)
	RVA004341A0_DISPLAY_SLOT(30) RVA004341A0_DISPLAY_SLOT(34)
	RVA004341A0_DISPLAY_SLOT(38) RVA004341A0_DISPLAY_SLOT(3C)
	RVA004341A0_DISPLAY_SLOT(40) RVA004341A0_DISPLAY_SLOT(44)
	RVA004341A0_DISPLAY_SLOT(48) RVA004341A0_DISPLAY_SLOT(4C)
	RVA004341A0_DISPLAY_SLOT(50) RVA004341A0_DISPLAY_SLOT(54)
	RVA004341A0_DISPLAY_SLOT(58) RVA004341A0_DISPLAY_SLOT(5C)
	RVA004341A0_DISPLAY_SLOT(60) RVA004341A0_DISPLAY_SLOT(64)
	RVA004341A0_DISPLAY_SLOT(68) RVA004341A0_DISPLAY_SLOT(6C)
	RVA004341A0_DISPLAY_SLOT(70) RVA004341A0_DISPLAY_SLOT(74)
	RVA004341A0_DISPLAY_SLOT(78) RVA004341A0_DISPLAY_SLOT(7C)
	RVA004341A0_DISPLAY_SLOT(80) RVA004341A0_DISPLAY_SLOT(84)
	RVA004341A0_DISPLAY_SLOT(88) RVA004341A0_DISPLAY_SLOT(8C)
	RVA004341A0_DISPLAY_SLOT(90) RVA004341A0_DISPLAY_SLOT(94)
	RVA004341A0_DISPLAY_SLOT(98) RVA004341A0_DISPLAY_SLOT(9C)
	RVA004341A0_DISPLAY_SLOT(A0) RVA004341A0_DISPLAY_SLOT(A4)
	RVA004341A0_DISPLAY_SLOT(A8) RVA004341A0_DISPLAY_SLOT(AC)
	virtual void slotB0();
	RVA004341A0_DISPLAY_SLOT(B4) RVA004341A0_DISPLAY_SLOT(B8)
	RVA004341A0_DISPLAY_SLOT(BC)
	virtual void slotC0(Real x, Real y, Real length, Real width,
		Int alpha);
	RVA004341A0_DISPLAY_SLOT(C4) RVA004341A0_DISPLAY_SLOT(C8)
	RVA004341A0_DISPLAY_SLOT(CC) RVA004341A0_DISPLAY_SLOT(D0)
	RVA004341A0_DISPLAY_SLOT(D4) RVA004341A0_DISPLAY_SLOT(D8)
	virtual void slotDC();
#undef RVA004341A0_DISPLAY_SLOT
};

// The one-field methods of the entry class are the ones whose offset the
// matched constructor witnesses; the address token stays on the method.
class Rva00434810SubtitleEntry
{
public:
	virtual void rva004341A0(Int frame, Rva0081D520Owner *owner,
		Real alignmentLow, Real coordinateLow, Real alignmentHigh,
		Real coordinateHigh);

private:
	void *m_text;
	UnsignedInt m_color;
	Int m_style;
	Int m_alignment;
	Int m_line;
	Int m_startFrame;
	Int m_endFrame;
	unsigned char m_displayed;
	unsigned char m_pad21[3];
	Rva004341A0DisplayStringView *m_displayStrings[3];
	Int m_displayStringCount;
	Int m_displayStringCapacity;
};

typedef char Rva004341A0LayoutCheck[
	(sizeof(Rva00434810SubtitleEntry) == 0x38) ? 1 : -1];

void Rva00434810SubtitleEntry::rva004341A0(Int frame,
	Rva0081D520Owner *owner, Real alignmentLow, Real coordinateLow,
	Real alignmentHigh, Real coordinateHigh)
{
	UnsignedInt alpha = 0xFF;
	if (frame < m_startFrame || frame > m_endFrame)
	{
		if ((m_style & 1) == 0)
			return;
		Int fade;
		if (frame < m_startFrame && frame >= m_startFrame - 15)
			fade = (m_startFrame - frame) * 18;
		else if (frame > m_endFrame && frame <= m_endFrame + 15)
			fade = (frame - m_endFrame) * 18;
		else
			return;
		if (fade >= 255)
			fade = 255;
		alpha -= fade;
	}

	Int first = 0;
	Int second;
	alpha <<= 24;
	m_displayStrings[0]->slot3C(&second, &first);

	if ((m_style & 4) != 0)
	{
		for (Int index = 0; index < m_displayStringCount; ++index)
		{
			Int length = m_displayStrings[index]->slot40(-1);
			Int x = bfmeAlignVIL(m_alignment, length,
				reinterpret_cast<Int>(owner), alignmentLow, alignmentHigh);
			Int y = rva004340C0SubtitleCoordinate(m_line + index,
				owner, coordinateLow, coordinateHigh);
			Rva004341A0DisplayView *display =
				reinterpret_cast<Rva004341A0DisplayView *>(TheDisplay);
			Real width = (Real)first;
			reinterpret_cast<Rva004341A0DisplayView *>(TheDisplay)->slotB0();
			display->slotC0((Real)x, (Real)y, (Real)length, width,
				(Int)alpha);
			display->slotDC();
			m_displayStrings[index]->slot28(m_color | alpha, 0);
			m_displayStrings[index]->slot34(x, y);
		}
	}
	else
	{
		for (Int index = 0; index < m_displayStringCount; ++index)
		{
			Int length = m_displayStrings[index]->slot40(-1);
			Int x = bfmeAlignVIL(m_alignment, length,
				reinterpret_cast<Int>(owner), alignmentLow, alignmentHigh);
			Int y = rva004340C0SubtitleCoordinate(m_line + index,
				owner, coordinateLow, coordinateHigh);
			m_displayStrings[index]->slot28(m_color | alpha, 0);
			m_displayStrings[index]->slot34(x, y);
		}
	}
}

// 0x004340C0: screen coordinate of subtitle line `index` between the two
// endpoints.  The only callers are the two loops above.  The alternate mode
// scales the owner's per-line factor; the default mode steps the endpoint
// span in fifteenths, with the line clamped to [0, 15] by the nested
// min/max macro form, which is what places the upper-clamp block after the
// return as retail does.
#define RVA004340C0_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define RVA004340C0_MIN(a, b) (((a) < (b)) ? (a) : (b))

__declspec(noinline) Int __cdecl rva004340C0SubtitleCoordinate(Int index,
	Rva0081D520Owner *owner, Real low, Real high)
{
	const Real difference = (Real)fabs(high - low);
	if (owner->m_alternateMode)
	{
		const Int highCoordinate = (Int)high;
		const Int lowCoordinate = (Int)low;
		const Int *selectedCoordinate = highCoordinate < lowCoordinate ?
			&highCoordinate : &lowCoordinate;
		return (Int)(difference * owner->m_lineCoordinates[index]) +
			*selectedCoordinate;
	}

	const Int highCoordinate = (Int)high;
	const Int lowCoordinate = (Int)low;
	index = RVA004340C0_MAX(RVA004340C0_MIN(index, 15), 0);
	const Int *selectedCoordinate = highCoordinate < lowCoordinate ?
		&highCoordinate : &lowCoordinate;
	return ((Int)difference / 15) * index + *selectedCoordinate;
}
