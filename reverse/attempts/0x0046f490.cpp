// ?Rva0046F490DrawBoundsOverlay@@YAXPBUCoord2D@@0PAX@Z
// partial score=0.55 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Bounds-high floating-point overlay draw routine, retail 0x0046F490,
// size 480. Identity: no named caller or source owner (per brief); the
// first callee (0x0002E249) itself resolves to another unresolved dump, so
// nothing here is independently proven and it stays address-keyed.

typedef float Real;
typedef bool Bool;
typedef int Int;

#define BfmeZeroRange (*(const float *)0x01075350)
#define g_bfmeDefaultBU (*(const float *)0x01075334)
#define g_bfmeScaleBC (*(const float *)0x0107fac4)

class Rva00579160Manager
{
public:
	void computeThreshold(float *out, void *obj);		// address-derived, retail 0x0002E249
};
extern Rva00579160Manager *g_rva00579160TheManager;		// VA 0x012F19E8

class BfmeRetString
{
public:
	BfmeRetString(const char *text);			// retail 0x00888BC0
	~BfmeRetString() { releaseBuffer(); }

private:
	void releaseBuffer();					// retail 0x00887940
	void *m_data;
};

class ImageCollection
{
public:
	void *findImageByName(const BfmeRetString &name, Bool *exists);	// pinned retail 0x0001D606
};
extern ImageCollection *g_bfmeTheMappedImageCollection;	// VA 0x012F6924

extern unsigned char g_bfmeOverlayFlags;			// VA 0x012F1B2C
extern void *g_bfmeOverlayImageA;				// VA 0x012F1B28
extern void *g_bfmeOverlayImageB;				// VA 0x012F1B24

class Display
{
public:
	void __cdecl bfmeRunD(int, int, int, int, int, int, int);	// pinned retail 0x0046EC50
};
extern Display *TheDisplay;					// VA 0x012F1270

struct Coord2D
{
	Real x, y;
};

void Rva0046F490DrawBoundsOverlay(const Coord2D *posA, const Coord2D *posB, void *self)
{
	Real threshold;
	g_rva00579160TheManager->computeThreshold(&threshold, self);

	if (!(threshold > BfmeZeroRange))
		return;
	if (!(threshold > g_bfmeDefaultBU))
		return;

	if (!(g_bfmeOverlayFlags & 1))
	{
		g_bfmeOverlayFlags |= 1;
		Bool exists = false;
		g_bfmeOverlayImageA = g_bfmeTheMappedImageCollection->findImageByName(
			BfmeRetString("BoundsHighA"), &exists);
	}

	if (!(g_bfmeOverlayFlags & 2))
	{
		g_bfmeOverlayFlags |= 2;
		Bool exists = false;
		g_bfmeOverlayImageB = g_bfmeTheMappedImageCollection->findImageByName(
			BfmeRetString("BoundsHighB"), &exists);
	}

	if (g_bfmeOverlayImageA)
	{
		int y = (int)(posB->y + posA->y);
		int x = (int)(posB->x + posA->x);
		int h = (int)threshold;
		int w = (int)(posA->y * g_bfmeScaleBC);
		TheDisplay->bfmeRunD(x, y, w, h, 0, 0, (int)g_bfmeOverlayImageA);
	}

	if (g_bfmeOverlayImageB)
	{
		int y = (int)(posB->y + posA->y);
		int x = (int)(posB->x + posA->x);
		int h = (int)threshold;
		int w = (int)(posA->y * g_bfmeScaleBC);
		TheDisplay->bfmeRunD(x, y, w, h, 0, 0, (int)g_bfmeOverlayImageB);
	}
}
