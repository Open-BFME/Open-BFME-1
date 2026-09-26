// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned char Bool;

extern void j_000022bb();
extern void j_0003251f();
extern void j_000102a8();
extern void j_00015b09();
extern void j_0003b0b1();
extern void j_000369a8();
extern void j_00011df1();

#define TheBfmeGameLogic (*(BfmeGameLogic **)0x012F0898)
#define g_iconTemplates (*(void ***)0x012F12EC)
#define g_animCollection (*(void **)0x012F4CA8)
#define g_iconWidthScale (*(const float *)0x0109F748)
#define g_iconHalfScale (*(const float *)0x0107533C)

struct BfmeGameLogic
{
	char pad00[0x3c];
	unsigned int frame;
	unsigned int getFrame() { return frame; }
};

class BfmeSubBIA
{
public:
	int ask();
};

struct BfmeThingAIA
{
	char pad00[4];
	BfmeSubBIA *sub;
	bool bfmeAskAIA(int kind);
};

struct BfmeResolved
{
	char pad00[0xcc];
	unsigned int flags;
};

struct BfmeBody
{
	virtual void f00();
	virtual void f04();
	virtual void f08();
	virtual void f0c();
	virtual float getHealth();
	virtual void f14();
	virtual float getMaxHealth();
	virtual void f1c();
	virtual void f20();
	virtual void f24();
	virtual void f28();
	virtual void f2c();
	virtual void f30();
	virtual void f34();
	virtual void f38();
	virtual void f3c();
	virtual void f40();
	virtual int getLastHealingTimestamp();
};

struct BfmeObject
{
	char pad00[4];
	BfmeThingAIA *templateObject;
	char pad08[0x88];
	unsigned int status;
	char pad94[0x16c];
	BfmeBody *body;
};

class DrawableIconInfo
{
	public:
	char pad00[4];
	void *icons[14];
};

class Anim2DTemplate;
class Anim2DCollection;

class Anim2D
{
public:
	Anim2D(Anim2DTemplate *iconTemplate, Anim2DCollection *collection);
	~Anim2D();
	unsigned int getCurrentFrameWidth() const;
	unsigned int getCurrentFrameHeight() const;
	void draw(int x, int y, int width, int height);
	char pad00[0x34];
};

class BfmeThingES
{
public:
	void bfmeDropES(int which);
};

class Drawable
{
public:
	virtual void v00();
	DrawableIconInfo *getIconInfo();

private:
	void drawHealing();
	char pad00[0xf8];
	BfmeObject *object;
	char pad100[0x2c4];
	int regionLeft;
	int regionRight;
	int regionBottom;
};

#pragma comment(linker, "/alternatename:?getIconInfo@Drawable@@QAEPAVDrawableIconInfo@@XZ=?j_000102a8@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Anim2D@@QAE@PAVAnim2DTemplate@@PAVAnim2DCollection@@@Z=?j_00015b09@@YAXXZ")
#pragma comment(linker, "/alternatename:?ask@BfmeSubBIA@@QAEHXZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeAskAIA@BfmeThingAIA@@QAE_NH@Z=?j_0003251f@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentFrameWidth@Anim2D@@QBEIXZ=?j_0003b0b1@@YAXXZ")
#pragma comment(linker, "/alternatename:?getCurrentFrameHeight@Anim2D@@QBEIXZ=?j_000369a8@@YAXXZ")
#pragma comment(linker, "/alternatename:?draw@Anim2D@@QAEXHHHH@Z=?j_00011df1@@YAXXZ")
#pragma comment(linker, "/alternatename:?bfmeDropES@BfmeThingES@@QAEXH@Z=?j_00019c63@@YAXXZ")

void Drawable::drawHealing()
{
	BfmeObject *obj = *(BfmeObject **)((char *)this + 0xfc);

	BfmeThingAIA *thing = obj->templateObject;
	BfmeResolved *resolved = (BfmeResolved *)thing;
	if (thing != 0 && thing->sub != 0)
		resolved = (BfmeResolved *)(thing->sub->ask());
	if ((resolved->flags & 0x400) != 0)
		return;
	if ((obj->status & 0x80000) != 0)
		return;

	Bool showHealing = 0;
	unsigned int frame;
	int typeIndex;
	BfmeBody *body = obj->body;
	float health = body->getHealth();
	if (health != body->getMaxHealth())
	{
		frame = TheBfmeGameLogic->getFrame();
		if (frame > 0xf)
		{
			if (frame - body->getLastHealingTimestamp() <= 0xf)
				showHealing = 1;
		}
	}
	if (((BfmeThingAIA *)this)->bfmeAskAIA(7))
		typeIndex = 1;
	else if (((BfmeThingAIA *)this)->bfmeAskAIA(9))
		typeIndex = 2;
	else
		typeIndex = 0;

	if (showHealing)
	{
		if (getIconInfo()->icons[typeIndex] == 0)
		{
			getIconInfo()->icons[typeIndex] = new Anim2D(
				(Anim2DTemplate *)g_iconTemplates[typeIndex],
				(Anim2DCollection *)g_animCollection);
		}

		Anim2D *icon = (Anim2D *)getIconInfo()->icons[typeIndex];
		if (icon != 0)
		{
			int barWidth = *(int *)((char *)this + 0x3cc) -
				*(int *)((char *)this + 0x3c4);
			int frameWidth = ((Anim2D *)getIconInfo()->icons[typeIndex])->getCurrentFrameWidth();
			int frameHeight = ((Anim2D *)getIconInfo()->icons[typeIndex])->getCurrentFrameHeight();
			int screenX = (int)(*(int *)((char *)this + 0x3c4) + barWidth * g_iconWidthScale -
				frameWidth * g_iconHalfScale);
			int screenY = *(int *)((char *)this + 0x3c8) - frameHeight;
			((Anim2D *)getIconInfo()->icons[typeIndex])->draw(screenX, screenY, frameWidth, frameHeight);
		}
	}
	else
		((BfmeThingES *)this)->bfmeDropES(typeIndex);
}
