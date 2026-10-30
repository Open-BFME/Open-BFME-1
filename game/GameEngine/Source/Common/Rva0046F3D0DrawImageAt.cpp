// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib

typedef int Int;
typedef float Real;

#include "../../../Libraries/Include/Lib/Coord2D.h"

class Image;

// Local Display view copied from the verified vtable-slot layout already
// proven by ControlBarArrowTransition_draw_Thunk.cpp and reused for the
// sibling body at 0x0046F060: beginImageDraw/+0xB0, drawImageCore/+0xD4,
// endImageDraw/+0xDC.
class Display
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void beginImageDraw();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void drawImageCore(const Image *image, Real x0, Real y0,
		Real x1, Real y1, Int color, Int mode);
	virtual void unused54();
	virtual void endImageDraw();
};

extern Display *TheDisplay;

inline void drawImage(Display *display, const Image *image, Real x0,
	Real y0, Real x1, Real y1, Int color, Int mode)
{
	display->beginImageDraw();
	display->drawImageCore(image, x0, y0, x1, y1, color, mode);
	display->endImageDraw();
}

// Retail 0x0046F3D0: the sibling of Rva0046F060DrawImageAt.cpp's body --
// same manager-hash image lookup (the 0x012F19E8 global, reached through
// this TU's Rva00579160Manager view) and TheDisplay begin/drawCore/end
// sequence over the rectangle [pos, pos+size), but the draw mode is
// fetched from a caller-supplied object instead of a literal constant.
// No named caller or owning identity survived (blocked twice: this body
// and its still-unclaimed sibling 0x0046F490), so every name here is
// address-derived.

// Retail calls the image lookup through the five-byte ILT thunk at 0x00008FEE
// (?j_00008fee@@YAXXZ, game/gen_small/thunks_003.cpp, tail-jumping to the
// still-dumped body at 0x0046C7D0); the member below stays declaration-only
// and supplies the call's type.
void j_00008fee();

struct Rva00579160Manager
{
	void *bfmeLookup46C7D0(Int key);
};

class WindowManager;

// Retail's single global at 0x012F19E8 is a WindowManager*; this TU keeps a
// local view of the one method it needs.
extern WindowManager *g_rva012F19E8WindowManager;

// The direct (non-thunked) callee at 0x0046F280 (257 bytes): the draw-mode
// lookup. Retail calls it without the ILT, so it is a file-static of this TU,
// and it only compiles to retail's bytes as one (as a member or external
// function MSVC rotates one scratch register). The source object is the
// query string handed to bfmeGetParamVMZ (0x0046EFA0 via ILT 0x0003C1B4) for
// key "_mode"; the value is matched case-insensitively against the six-entry
// {mode, name} table at VA 0x010F738C; no value or no match is mode 2.
#include "string_base.h"
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }
#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

// AsciiString::isEmpty, expanded in place.  Calling the member would emit
// ?isEmpty@AsciiString@@QBE_NXZ and ?isEmpty@?$StringBase@D@@QBE_NXZ COMDATs
// that are not retail's bodies.  The buffer pointer is the string's first
// word; its length is at +4.
static __forceinline bool asciiIsEmpty( const AsciiString &string )
{
	const char *data = *reinterpret_cast<const char * const *>(&string);
	return !data || *reinterpret_cast<const unsigned short *>(data + 4) == 0;
}

class BfmeStrVMZ;
char bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out);

class Rva0046F3D0ModeSource;

struct Rva0046F280ModeName
{
	Int mode;
	const char *name;
};

extern const Rva0046F280ModeName g_Va010F738C[6] = {
	{ 0, "SOLID" },
	{ 1, "GRAYSCALE" },
	{ 2, "ALPHA" },
	{ 3, "ADDITIVE" },
	{ 4, "SOLID_GRAYSCALE" },
	{ 5, "SOLID_TEXTURE" },
};

static Int getMode0046F280( Rva0046F3D0ModeSource *source )
{
	AsciiString value;
	if (!bfmeGetParamVMZ((const char *)source, "_mode", (BfmeStrVMZ *)&value) || asciiIsEmpty(value))
		return 2;
	for (unsigned int i = 0; i < 6; ++i)
	{
		if (_strcmpi(g_Va010F738C[i].name, value.str()) == 0)
			return g_Va010F738C[i].mode;
	}
	return 2;
}

void Rva0046F3D0DrawImageAt(const Coord2D *pos, const Coord2D *size,
	Int imageKey, Rva0046F3D0ModeSource *modeSource)
{
	const Image *image;
	{
		Rva00579160Manager *manager = (Rva00579160Manager *)g_rva012F19E8WindowManager;
		union { void (*raw)(); void *(Rva00579160Manager::*m)(Int); } call;
		call.raw = j_00008fee;
		image = (const Image *)((manager->*call.m)(imageKey));
	}
	if (!image)
		return;

	Int mode = getMode0046F280( modeSource );

	drawImage(TheDisplay, image, pos->x, pos->y,
		pos->x + size->x, pos->y + size->y, -1, mode);
}
