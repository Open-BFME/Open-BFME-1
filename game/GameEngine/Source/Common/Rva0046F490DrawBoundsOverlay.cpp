// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Retail 0x0046F490: draws the RadialClockOverlay1/2 images over [pos, pos+size).
// Sibling of Rva0046F3D0DrawImageAt.cpp; no named caller, so owners stay address-derived.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef float Real;
typedef int Int;

struct Coord2D
{
	Real x;
	Real y;
};

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

// Returned through hidden storage: retail 0x0046CA40 ends `ret 8` and its
// fallback path writes {1.0f, 0} into the caller's slot.
struct Rva0046CA40Result
{
	Rva0046CA40Result(Real value, Int arg) : threshold(value), m_arg(arg) {}
	Real threshold;
	Int m_arg;
};

struct Rva00579160Manager
{
	Rva0046CA40Result computeThreshold(void *obj);	// retail ILT 0x0002E249 -> 0x0046CA40
};
extern Rva00579160Manager *Rva00579160TheManager;

// Retail 0x0046EC50 (ILT 0x00034338): thiscall, `ret 0x1c`, forwards its seven
// arguments to Display slot 0xD0 between slots 0xB0 and 0xDC.
class Display
{
public:
	void bfmeRunD(const Image *image, Real x0, Real y0, Real x1, Real y1, Real value, Int color);
};
extern Display *TheDisplay;

struct LocalPlayerTemplateView
{
	char m_pad[0x118];
	char m_flag118;
};

struct Rva002EE330Player
{
	char m_pad[0x4];
	LocalPlayerTemplateView *m_template04;
};

struct Rva002EE330PlayerList
{
	char m_pad[0xc];
	Rva002EE330Player *m_localPlayer;
};
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

struct Rva006C9270GlobalData
{
	char m_pad[0x1214];
	Int m_color1214;
	Int m_color1218;
};
extern Rva006C9270GlobalData *TheWritableGlobalData;

void Rva0046F490DrawBoundsOverlay(const Coord2D *pos, const Coord2D *size, void *self)
{
	Rva0046CA40Result result = Rva00579160TheManager->computeThreshold(self);
	if (result.threshold >= 0.0f && result.threshold < 1.0f)
	{
		static const Image *overlay1 = TheMappedImageCollection->findImageByName(AsciiString("RadialClockOverlay1"));
		static const Image *overlay2 = TheMappedImageCollection->findImageByName(AsciiString("RadialClockOverlay2"));

		Int color = 0;
		if (Rva002EE330ThePlayers && Rva002EE330ThePlayers->m_localPlayer)
		{
			LocalPlayerTemplateView *t = Rva002EE330ThePlayers->m_localPlayer->m_template04;
			if (t && t->m_flag118)
				color = TheWritableGlobalData->m_color1218;
			else
				color = TheWritableGlobalData->m_color1214;
		}

		if (overlay1 && result.m_arg)
			TheDisplay->bfmeRunD(overlay1, pos->x, pos->y, pos->x + size->x,
				pos->y + size->y, result.threshold * 100.0f, result.m_arg);
		if (overlay2)
			TheDisplay->bfmeRunD(overlay2, pos->x, pos->y, pos->x + size->x,
				pos->y + size->y, result.threshold * 100.0f, color);
	}
}
