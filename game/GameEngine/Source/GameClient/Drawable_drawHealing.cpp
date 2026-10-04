// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned char Bool;

extern void j_000022bb();
extern void j_0003251f();
extern void j_000102a8();
extern void j_00015b09();
extern void j_0003b0b1();
extern void j_000369a8();
extern void j_00011df1();
extern void j_00019c63();

#define g_iconTemplates (Drawable::s_animationTemplates)
#define g_animCollection (TheAnim2DCollection)
#define g_iconWidthScale 0.75f
#define g_iconHalfScale 0.5f

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
class GameLogic;

extern GameLogic *TheGameLogic;
static inline BfmeGameLogic *TheBfmeGameLogicView() { return (BfmeGameLogic *)TheGameLogic; }
extern Anim2DCollection *TheAnim2DCollection;

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
	static Anim2DTemplate **s_animationTemplates;
	char pad00[0xf8];
	BfmeObject *object;
	char pad100[0x2c4];
	int regionLeft;
	int regionRight;
	int regionBottom;
};

// Retail builds the healing icon with a new-expression, so the constructor call
// must remain inside one for MSVC 7.1 to emit the cleanup funclets retail has.
// A thunk call through a member pointer inside a new-expression either loses the
// funclets (inlined ctor) or leaves a locally-defined ctor symbol unresolved;
// neither reproduces retail, so this one pragma stays.
#pragma comment(linker, "/alternatename:??0Anim2D@@QAE@PAVAnim2DTemplate@@PAVAnim2DCollection@@@Z=?j_00015b09@@YAXXZ")

static __forceinline int askThunk002434D0(BfmeSubBIA *self)
{
	typedef int (BfmeSubBIA::*Ask)();
	union { void (*fn)(); Ask call; } route = { j_000022bb };
	return (self->*route.call)();
}

static __forceinline bool askAiaThunk002434D0(BfmeThingAIA *self, int kind)
{
	typedef bool (BfmeThingAIA::*Ask)(int);
	union { void (*fn)(); Ask call; } route = { j_0003251f };
	return (self->*route.call)(kind);
}

static __forceinline void dropEsThunk002434D0(BfmeThingES *self, int which)
{
	typedef void (BfmeThingES::*Drop)(int);
	union { void (*fn)(); Drop call; } route = { j_00019c63 };
	(self->*route.call)(which);
}

static __forceinline DrawableIconInfo *iconInfoThunk002434D0(Drawable *self)
{
	typedef DrawableIconInfo *(Drawable::*GetIconInfo)();
	union { void (*fn)(); GetIconInfo call; } route = { j_000102a8 };
	return (self->*route.call)();
}

void Drawable::drawHealing()
{
	BfmeObject *obj = *(BfmeObject **)((char *)this + 0xfc);

	BfmeThingAIA *thing = obj->templateObject;
	BfmeResolved *resolved = (BfmeResolved *)thing;
	if (thing != 0 && thing->sub != 0)
		resolved = (BfmeResolved *)askThunk002434D0(thing->sub);
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
		frame = TheBfmeGameLogicView()->getFrame();
		if (frame > 0xf)
		{
			if (frame - body->getLastHealingTimestamp() <= 0xf)
				showHealing = 1;
		}
	}
	if (askAiaThunk002434D0((BfmeThingAIA *)this, 7))
		typeIndex = 1;
	else if (askAiaThunk002434D0((BfmeThingAIA *)this, 9))
		typeIndex = 2;
	else
		typeIndex = 0;

	if (showHealing)
	{
		if (iconInfoThunk002434D0(this)->icons[typeIndex] == 0)
		{
			iconInfoThunk002434D0(this)->icons[typeIndex] = new Anim2D(
				(Anim2DTemplate *)g_iconTemplates[typeIndex],
				(Anim2DCollection *)g_animCollection);
		}

		Anim2D *icon = (Anim2D *)iconInfoThunk002434D0(this)->icons[typeIndex];
		if (icon != 0)
		{
			int barWidth = *(int *)((char *)this + 0x3cc) -
				*(int *)((char *)this + 0x3c4);
			union { void (*fn)(); unsigned int (Anim2D::*call)() const; } routeWidth =
				{ j_0003b0b1 };
			union { void (*fn)(); unsigned int (Anim2D::*call)() const; } routeHeight =
				{ j_000369a8 };
			union { void (*fn)(); void (Anim2D::*call)(int, int, int, int); } routeDraw =
				{ j_00011df1 };
			int frameWidth = (((Anim2D *)iconInfoThunk002434D0(this)->icons[typeIndex])
				->*routeWidth.call)();
			int frameHeight = (((Anim2D *)iconInfoThunk002434D0(this)->icons[typeIndex])
				->*routeHeight.call)();
			int screenX = (int)(*(int *)((char *)this + 0x3c4) + barWidth * g_iconWidthScale -
				frameWidth * g_iconHalfScale);
			int screenY = *(int *)((char *)this + 0x3c8) - frameHeight;
			(((Anim2D *)iconInfoThunk002434D0(this)->icons[typeIndex])
				->*routeDraw.call)(screenX, screenY, frameWidth, frameHeight);
		}
	}
	else
		dropEsThunk002434D0((BfmeThingES *)this, typeIndex);
}