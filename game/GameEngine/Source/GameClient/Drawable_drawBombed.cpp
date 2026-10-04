// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Full 0x00418490..0x004185AC body reconstruction.  The Ghidra boundary is
// 284 bytes.  Identity is caller-derived: the matched Drawable::drawIconUI
// body at 0x00420AC0 reaches the named ILT ?drawBombed@Drawable@@AAEXXZ at
// 0x0002F6E9, whose target is this body.  No stronger standalone direct
// caller name was found.  The retail branch tests object status bits 4 and
// 0x40; the true path creates/draws icon slot 6 and the false path destroys
// and clears it.  The icon is placed from the health-bar region at +0x3C4
// (lo.x, hi.y less the frame and bar heights) through an ICoord2D screen
// position, which gives retail's hi.y-before-lo.y load order.  The barrier
// keeps the two status tests separate, as retail tests them.

typedef unsigned int UnsignedInt;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Anim2DTemplate;
class Anim2DCollection;

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *iconTemplate, Anim2DCollection *collection);
	virtual ~Anim2D();
	UnsignedInt getCurrentFrameWidth() const;
	UnsignedInt getCurrentFrameHeight() const;
	void draw(int x, int y, int width, int height);

	void deleteInstance() { delete this; }

private:
	unsigned char m_unmodelled[0x30];
};

class DrawableIconInfo
{
public:
	virtual ~DrawableIconInfo();
	Anim2D *m_icon[14];
	UnsignedInt m_keepTillFrame[14];
};

// The Anim2D collection (VA 0x012F4CA8) and the icon-template table
// (VA 0x012F12EC) are recorded globals in
// targets/game/reverse/dir32_addresses.csv, so both are bound to the recorded
// decorated symbols: a literal address here reads the wrong memory the moment
// the data moves in a linked build.  The template table is retail's private
// static Drawable::s_animationTemplates
// (?s_animationTemplates@Drawable@@0PAPAVAnim2DTemplate@@A), defined by
// Drawable::initStaticImages in DrawableInitStaticImages.cpp; this body only
// reads it.
extern Anim2DCollection *TheAnim2DCollection;

class Drawable
{
public:
	DrawableIconInfo *getIconInfo();

private:
	static Anim2DTemplate **s_animationTemplates;
	void drawBombed();
};

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct BfmeDrawableDrawBombedFields
{
	unsigned char m_unmodelled_000[0xFC];
	void *m_object;
	unsigned char m_unmodelled_100[0x1E0];
	DrawableIconInfo *m_iconInfo;
	unsigned char m_unmodelled_2E4[0xE0];
	int m_regionLeft;
	int m_regionTop;
	unsigned char m_unmodelled_3CC[4];
	int m_regionBottom;
};

struct BfmeDrawableDrawBombedObjectFields
{
	unsigned char m_unmodelled_000[0x1A4];
	UnsignedInt m_status;
};

void Drawable::drawBombed()
{
	BfmeDrawableDrawBombedFields *self = (BfmeDrawableDrawBombedFields *)this;
	BfmeDrawableDrawBombedObjectFields *object =
		(BfmeDrawableDrawBombedObjectFields *)self->m_object;

	const UnsignedInt status = object->m_status;
	if ((status & 4) != 0 || (_ReadWriteBarrier(), (status & 0x40) != 0))
	{
		if (getIconInfo()->m_icon[6] == 0)
		{
			getIconInfo()->m_icon[6] = new Anim2D(
				Drawable::s_animationTemplates[6],
				TheAnim2DCollection);
		}

		const IRegion2D *region = (const IRegion2D *)((unsigned char *)self + 0x3C4);
		int barHeight = region->hi.y - region->lo.y;
		int frameWidth = getIconInfo()->m_icon[6]->getCurrentFrameWidth();
		int frameHeight = getIconInfo()->m_icon[6]->getCurrentFrameHeight();
		ICoord2D screen;
		screen.x = region->lo.x;
		screen.y = region->hi.y - frameHeight - barHeight;
		getIconInfo()->m_icon[6]->draw(screen.x, screen.y, frameWidth, frameHeight);
	}
	else
	{
		DrawableIconInfo *icons = self->m_iconInfo;
		if (icons != 0 && icons->m_icon[6] != 0)
		{
			icons->m_icon[6]->deleteInstance();
			icons->m_icon[6] = 0;
			icons->m_keepTillFrame[6] = 0;
		}
	}
}