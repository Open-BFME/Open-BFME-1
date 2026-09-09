// ?drawBombed@Drawable@@AAEXXZ
// partial score=0.9 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Full 0x00418490..0x004185AC body reconstruction.  The Ghidra boundary is
// 284 bytes.  Identity is caller-derived: the matched Drawable::drawIconUI
// body at 0x00420AC0 reaches the named ILT ?drawBombed@Drawable@@AAEXXZ at
// 0x0002F6E9, whose target is this body.  No stronger standalone direct
// caller name was found.  The retail branch tests object status bits 4 and
// 0x40; the true path creates/draws icon slot 6 and the false path destroys
// and clears it.  The remaining four non-relocation bytes are the order of
// the +0x3D0 and +0x3C8 coordinate loads.

typedef unsigned int UnsignedInt;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern void j_000102a8();
extern void j_00015b09();
extern void j_0003b0b1();
extern void j_000369a8();
extern void j_00011df1();

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

#define g_iconTemplates (*(void ***)0x012F12EC)
#define g_animCollection (*(void **)0x012F4CA8)

#pragma comment(linker, "/alternatename:?getIconInfo@Drawable@@QAEPAVDrawableIconInfo@@XZ=?j_000102a8@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Anim2D@@QAE@PAVAnim2DTemplate@@PAVAnim2DCollection@@@Z=?j_00015b09@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentFrameWidth@Anim2D@@QBEIXZ=?j_0003b0b1@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentFrameHeight@Anim2D@@QBEIXZ=?j_000369a8@@YAXXZ")
#pragma comment(linker, "/alternatename:?draw@Anim2D@@QAEXHHHH@Z=?j_00011df1@@YAXXZ")

class Drawable
{
public:
	DrawableIconInfo *getIconInfo();

private:
	void drawBombed();
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
				(Anim2DTemplate *)g_iconTemplates[6],
				(Anim2DCollection *)g_animCollection);
		}

		int frameWidth;
		int frameHeight;
		int regionBottom = self->m_regionBottom;
		int regionTop = *(volatile int *)((unsigned char *)self + 0x3C8);
		int barHeight = regionBottom - regionTop;
		frameWidth = getIconInfo()->m_icon[6]->getCurrentFrameWidth();
		frameHeight = getIconInfo()->m_icon[6]->getCurrentFrameHeight();
		int screenY = self->m_regionBottom - frameHeight - barHeight;
		getIconInfo()->m_icon[6]->draw(
			self->m_regionLeft, screenY, frameWidth, frameHeight);
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
