// ?d_004341a0@@YAXXZ
// partial score=0.9843 date=2026-10-09
// SubtitleEntry virtual slot 1 uses the matched constructor field layout.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct Rva004340C0SubtitleOwner
{
	unsigned char m_pad00[0x24];
	Real m_lineCoordinates[15];
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

class Rva004341A0SubtitleBaseView
{
public:
	virtual ~Rva004341A0SubtitleBaseView();

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
};

// ?rva004341A0@Rva004341A0SubtitleEntryView@@UAEXHPAURva004340C0SubtitleOwner@@MMMM@Z present-unmatched
void Rva004341A0SubtitleEntryView::rva004341A0(Int frame,
    Rva004340C0SubtitleOwner *owner, Real alignmentLow,
    Real coordinateLow, Real alignmentHigh, Real coordinateHigh)
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
            display->slotB0();
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
