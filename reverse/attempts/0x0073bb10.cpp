// ?iterateDrawablesInRegion@W3DView@@UAEHPAUIRegion2D@@P6A_NPAVDrawable@@PAX@Z2@Z
// partial score=0.9 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Scratch BFME-layout probe for W3DView::iterateDrawablesInRegion.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

#define NULL 0
#define TRUE true
#define FALSE false

extern Real g_bfmeDefaultBU;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;

	Int height() const { return hi.y - lo.y; }
	Int width() const { return hi.x - lo.x; }
};

struct Coord2D
{
	Real x;
	Real y;
};

struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

class CameraClass
{
public:
	enum ProjectionResType
	{
		INSIDE_FRUSTUM,
		OUTSIDE_FRUSTUM,
		OUTSIDE_NEAR_CLIP,
		OUTSIDE_FAR_CLIP
	};

	ProjectionResType Project(Vector3 &destination, const Vector3 &source) const;
};

enum PickType
{
	PICK_TYPE_NONE = 0
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
	Drawable *getNextDrawable() const
	{
		return *reinterpret_cast<Drawable *const *>(reinterpret_cast<const unsigned char *>(this) + 0x104);
	}
};

class GameClient
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual Drawable *firstDrawable() = 0;
};

class InGameUI
{
public:
	Bool isInForceAttackMode() const { return m_forceAttackMode; }

private:
	unsigned char m_padding[0x12b1];
	Bool m_forceAttackMode;
};

extern GameClient *TheGameClient;
extern InGameUI *TheInGameUI;
extern UnsignedInt getPickTypesForContext(Bool forceAttackMode);

class W3DView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual Drawable *pickDrawable(const ICoord2D *screen, Bool forceAttack, PickType pickType) = 0;
	virtual Int iterateDrawablesInRegion(IRegion2D *screenRegion,
		Bool (*callback)(Drawable *draw, void *userData), void *userData);
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void setWidth(Int width) = 0;
	virtual Int getWidth() = 0;
	virtual void setHeight(Int height) = 0;
	virtual Int getHeight() = 0;

	unsigned char m_padding04[0x14];
	Int m_width;
	Int m_height;
	Int m_originX;
	Int m_originY;
	unsigned char m_padding28[0x104 - 0x28];
	CameraClass *m_3DCamera;
};

Int W3DView::iterateDrawablesInRegion(IRegion2D *screenRegion,
	Bool (*callback)(Drawable *draw, void *userData), void *userData)
{
	register W3DView *view = this;
	Bool inside = FALSE;
	Int count = 0;
	register Drawable *draw;
	Vector3 screen, world;
	Coord3D pos;
	Region2D normalizedRegion;

	Bool regionIsPoint = FALSE;

	if (screenRegion)
	{
		if (screenRegion->height() == 0 && screenRegion->width() == 0)
		{
			regionIsPoint = TRUE;
		}

		normalizedRegion.lo.x = ((Real)(screenRegion->lo.x - view->m_originX) / (Real)view->getWidth()) * 2.0f - g_bfmeDefaultBU;
		normalizedRegion.lo.y = -(((Real)(screenRegion->hi.y - view->m_originY) / (Real)view->getHeight()) * 2.0f - g_bfmeDefaultBU);
		normalizedRegion.hi.x = ((Real)(screenRegion->hi.x - view->m_originX) / (Real)view->getWidth()) * 2.0f - g_bfmeDefaultBU;
		normalizedRegion.hi.y = -(((Real)(screenRegion->lo.y - view->m_originY) / (Real)view->getHeight()) * 2.0f - g_bfmeDefaultBU);
	}

	Drawable *onlyDrawableToTest = NULL;
	if (regionIsPoint)
	{
		onlyDrawableToTest = view->pickDrawable(&screenRegion->lo, TRUE,
			(PickType)(getPickTypesForContext(TheInGameUI->isInForceAttackMode()) | 0x100));
		if (onlyDrawableToTest == NULL)
		{
			return 0;
		}
	}

	for (draw = TheGameClient->firstDrawable();
		draw;
		draw = draw->getNextDrawable())
	{
		if (onlyDrawableToTest)
		{
			draw = onlyDrawableToTest;
			inside = TRUE;
		}
		else
		{
			inside = FALSE;
			if (screenRegion == NULL)
			{
				inside = TRUE;
			}
			else
			{
				pos = *draw->getPosition();
				world.X = pos.x;
				world.Y = pos.y;
				world.Z = pos.z;

				if (view->m_3DCamera->Project(screen, world) == CameraClass::INSIDE_FRUSTUM &&
					screen.X >= normalizedRegion.lo.x &&
					screen.X <= normalizedRegion.hi.x &&
					screen.Y >= normalizedRegion.lo.y &&
					screen.Y <= normalizedRegion.hi.y)
				{
					inside = TRUE;
				}
			}
		}

		if (inside)
		{
			if (callback(draw, userData))
			{
				++count;
			}
		}

		if (onlyDrawableToTest != NULL)
		{
			break;
		}
	}

	return count;
}
