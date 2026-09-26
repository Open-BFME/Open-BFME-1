// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

typedef int Int;
typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

class Image;

// Local Display view copied from the verified vtable-slot layout already
// proven by ControlBarArrowTransition_draw_Thunk.cpp: beginImageDraw/+0xB0,
// drawImageCore/+0xD4, endImageDraw/+0xDC.
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

// Retail 0x0046F060: looks an image up through the 0x012F19E8 manager
// hash (already shared as Rva00579160Manager/Rva00579160TheManager
// elsewhere in this tree; the specific lookup method reached here has no
// named row of its own, so it keeps the address of the still-dump body
// its ILT thunk 0x00008FEE reaches) and, when found, draws it as the
// rectangle [pos, pos+size). No named caller or owning identity survived
// two prior passes, so the function itself is an address-derived free
// function rather than a claimed member.
struct Rva00579160Manager
{
	void *bfmeLookup46C7D0(Int key);
};

extern Rva00579160Manager *Rva00579160TheManager;

void Rva0046F060DrawImageAt(const Coord2D *pos, const Coord2D *size, Int imageKey)
{
	const Image *image = (const Image *)Rva00579160TheManager->bfmeLookup46C7D0(imageKey);
	if (!image)
		return;

	drawImage(TheDisplay, image, pos->x, pos->y,
		pos->x + size->x, pos->y + size->y, -1, 1);
}
