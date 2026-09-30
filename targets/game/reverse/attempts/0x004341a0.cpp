// ?d_004341a0@@YAXXZ
// partial score=0.1004 date=2026-09-30
// 0x00434810 SubtitleEntry constructor. This is a reconstruction trial.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Rva004340C0SubtitleOwner
{
	unsigned char m_pad00[0x60];
	unsigned char m_alternateMode;
};

extern Int __cdecl bfmeAlignVIL(Int alignment, Int length, Int unused,
	Real low, Real high);
extern Int __cdecl rva004340C0SubtitleCoordinate(Int index,
	Rva004340C0SubtitleOwner *owner, Real low, Real high);

#pragma comment(linker, "/alternatename:?bfmeAlignVIL@@YAHHHHMM@Z=?j_00029780@@YAXXZ")
#pragma comment(linker, "/alternatename:?rva004340C0SubtitleCoordinate@@YAHHPAURva004340C0SubtitleOwner@@MM@Z=?j_0002f040@@YAXXZ")

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
	virtual void slot28(Int mode, UnsignedInt color);
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
	virtual Int slotB0();
	RVA004341A0_DISPLAY_SLOT(B4) RVA004341A0_DISPLAY_SLOT(B8)
	RVA004341A0_DISPLAY_SLOT(BC)
	virtual void slotC0(Real x, Real y, Real length, Int width,
		Int alpha);
	RVA004341A0_DISPLAY_SLOT(C4) RVA004341A0_DISPLAY_SLOT(C8)
	RVA004341A0_DISPLAY_SLOT(CC) RVA004341A0_DISPLAY_SLOT(D0)
	RVA004341A0_DISPLAY_SLOT(D4) RVA004341A0_DISPLAY_SLOT(D8)
	virtual void slotDC();
#undef RVA004341A0_DISPLAY_SLOT
};

class Rva004341A0SubtitleBaseView
{
public:
	virtual ~Rva004341A0SubtitleBaseView() {}

protected:
	void *m_text;
	UnsignedInt m_color;
	Int m_style;
	Int m_alignment;
	Int m_line;
	Int m_startFrame;
	Int m_endFrame;
	unsigned char m_displayed;
	unsigned char m_pad21[3];
};

typedef char Rva004341A0BaseSizeCheck[
	(sizeof(Rva004341A0SubtitleBaseView) == 0x24) ? 1 : -1];

class Rva004341A0SubtitleEntryView : public Rva004341A0SubtitleBaseView
{
public:
	virtual void rva004341A0(Int frame, Rva004340C0SubtitleOwner *owner,
		Real alignmentLow, Real coordinateLow, Real alignmentHigh,
		Real coordinateHigh);

private:
	Rva004341A0DisplayStringView *m_displayStrings[3];
	Int m_displayStringCount;
	Int m_displayStringCapacity;
	unsigned char m_pad38[0x10];
	Real m_lineCoordinates[15];
	unsigned char m_alternateMode;
	unsigned char m_pad85[3];
};

void Rva004341A0SubtitleEntryView::rva004341A0(Int frame,
	Rva004340C0SubtitleOwner *owner, Real alignmentLow,
	Real coordinateLow, Real alignmentHigh, Real coordinateHigh)
{
	Int currentFrame = frame;
	Rva004341A0SubtitleEntryView *self = this;
	UnsignedInt alpha = 0xFF;
	if (currentFrame >= self->m_startFrame)
	{
		if (currentFrame > self->m_endFrame)
		{
			if ((self->m_style & 1) == 0)
				return;
			if (currentFrame > self->m_endFrame + 0x0F)
				return;
			Int fade = (currentFrame - self->m_endFrame) * 18;
			if (fade >= 0xFF)
				fade = 0xFF;
			alpha -= fade;
		}
	}
	else
	{
		if ((self->m_style & 1) == 0)
			return;
		if (currentFrame < self->m_startFrame - 0x0F)
			return;
		alpha -= (self->m_startFrame - currentFrame) * 9;
	}

	alpha <<= 24;
	Int first = 0;
	Int second;
	self->m_displayStrings[0]->slot3C(&second, &first);

	if ((self->m_style & 4) != 0)
	{
		Int count = self->m_displayStringCount;
		if (count <= 0)
			return;

		Int index = 0;
		Rva004341A0DisplayStringView **current = self->m_displayStrings;
		while (index < count)
		{
			Rva004341A0DisplayStringView *text = *current;
			Int length = text->slot40(-1);
			Int x = bfmeAlignVIL(self->m_alignment, length,
				reinterpret_cast<Int>(self->m_displayStrings), alignmentLow,
				alignmentHigh);
			Int y = rva004340C0SubtitleCoordinate(self->m_line + frame,
				reinterpret_cast<Rva004340C0SubtitleOwner *>(
					self->m_displayStrings), coordinateLow, coordinateHigh);

			Rva004341A0DisplayView *display =
				reinterpret_cast<Rva004341A0DisplayView *>(TheDisplay);
			display->slotB0();
			display->slotC0((Real)x, (Real)y, (Real)length, first,
				(Int)alpha);
			display->slotDC();
			text->slot28(0, self->m_color | alpha);
			text->slot34(x, y);
			++index;
			++current;
		}
	}
	else
	{
		Int count = self->m_displayStringCount;
		Int index = 0;
		Rva004341A0DisplayStringView **current = self->m_displayStrings;
		while (index < count)
		{
			Rva004341A0DisplayStringView *text = *current;
			Int length = text->slot40(-1);
			Int x = bfmeAlignVIL(self->m_alignment, length,
				reinterpret_cast<Int>(owner), alignmentLow, alignmentHigh);
			Int y = rva004340C0SubtitleCoordinate(self->m_line + index,
				owner, coordinateLow, coordinateHigh);
			text->slot28(0, self->m_color | alpha);
			text->slot34(x, y);
			++index;
			++current;
		}
	}
}
