// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Retail 0x00609940 (135 bytes, thiscall, ret 0xC): the W3DMouse vtable slot
// just before the cursor world-position clamp (rdata 0x00D20820).  It clears
// the mouse tooltip (Mouse::setCursorTooltip with the empty string), lets the
// object refresh its +0x44 block (own slot 14) and cache its own slot-15
// value at +0x68, then records a new target: position at +0x50, the second
// argument at +0x6C, an active flag at +0x60 with a cleared +0x5C counter,
// and 1/duration as the +0x64 rate.  IDENTITY IS NOT RECOVERED.

typedef float Real;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

struct RGBColor;

#include "string_base.h"

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() { releaseBuffer(); }

	static UnicodeString TheEmptyString;
};

class Mouse
{
public:
	void setCursorTooltip(UnicodeString tooltip, int tooltipDelay, const RGBColor *color, Real width);
};

// Retail's singleton at 0x012F4C5C is EA's Mouse *TheMouse; (defined once in
// GameClient/Input/Mouse.cpp).  The Mouse view above is this TU's own look at
// the one global, so the reference links.
extern Mouse *TheMouse;

class Rva00609940CursorTarget
{
public:
#define TARGET_SLOT(N) virtual void slot##N() = 0
	TARGET_SLOT(00); TARGET_SLOT(01); TARGET_SLOT(02); TARGET_SLOT(03);
	TARGET_SLOT(04); TARGET_SLOT(05); TARGET_SLOT(06); TARGET_SLOT(07);
	TARGET_SLOT(08); TARGET_SLOT(09); TARGET_SLOT(10); TARGET_SLOT(11);
	TARGET_SLOT(12); TARGET_SLOT(13);
#undef TARGET_SLOT
	virtual void refresh(void *block) = 0;
	virtual Real currentValue() = 0;

	void beginTarget(const Coord3D *pos, int tag, unsigned int duration);

private:
	char m_pad04[0x40];
	char m_block44[0x0c];
	Coord3D m_targetPos;
	int m_counter5C;
	bool m_active;
	char m_pad61[3];
	Real m_rate;
	Real m_value68;
	int m_tag;
};

void Rva00609940CursorTarget::beginTarget(const Coord3D *pos, int tag, unsigned int duration)
{
	((Mouse *)TheMouse)->setCursorTooltip(UnicodeString::TheEmptyString, 0, 0, 1.0f);
	refresh(m_block44);
	m_value68 = currentValue();
	m_active = true;
	m_counter5C = 0;
	m_rate = 1.0f / (Real)duration;
	m_targetPos = *pos;
	m_tag = tag;
}
