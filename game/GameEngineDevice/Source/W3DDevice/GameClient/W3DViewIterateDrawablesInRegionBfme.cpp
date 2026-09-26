// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME W3DView::iterateDrawablesInRegion, retail 0x0073BB10 (544B).
//
// Identity: W3DView vtable 0x011217A0 slot 10 holds this address through
// the ILT thunk at VA 0x00440755 (ledger ?j_00040755), and the body follows
// the Zero Hour twin's spine and slot order (inputs/reference/
// CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/W3DDevice/
// GameClient/W3DView.cpp): normalize the screen region, pick a single
// drawable when the region is a point, then walk TheGameClient's drawable
// list projecting each centre through the camera.  tools/callers_of.py finds
// no named direct caller.
//
// BFME moved m_3DCamera to +0x104 (tools/bfme_layout.py W3DView), and the
// pick call ORs 0x100 into the pick-type mask.
//
// TheGameClient is typed ClientRoot4120 to follow targets/game/reverse/symbols.csv and the
// landed Rva006957E0ElapsedMs.cpp spelling (VA 0x012F1464); its slot 12 is the
// proven ?firstDrawable@GameClient@@ at 0x004318B0 (targets/game/reverse/functions.csv,
// GameClient vtable 0x01120468).
//
// Shape note: the pick-type mask must be computed into its own local before
// the pickDrawable call.  Spelled inline as an argument, MSVC 7.1 hoists the
// vtable load above the Rva00459060 call into EBX, which adds a call-crossing
// candidate and permutes ESI/EDI for `this` and screenRegion across 53 bytes.

typedef int Int;
typedef float Real;
typedef bool Bool;

#define NULL 0
#define TRUE true
#define FALSE false

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
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
	Drawable *getNextDrawable() const
	{
		return m_nextDrawable;
	}

private:
	unsigned char m_padding[0x104];
	Drawable *m_nextDrawable;
};

class ClientRoot4120
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

extern ClientRoot4120 *TheGameClient;
extern InGameUI *TheInGameUI;
extern int Rva00459060(bool forceAttackMode);	///< ILT 0x0000F2C2 -> 0x00459060

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

		normalizedRegion.lo.x = ((Real)(screenRegion->lo.x - view->m_originX) / (Real)view->getWidth()) * 2.0f - 1.0f;
		normalizedRegion.lo.y = -(((Real)(screenRegion->hi.y - view->m_originY) / (Real)view->getHeight()) * 2.0f - 1.0f);
		normalizedRegion.hi.x = ((Real)(screenRegion->hi.x - view->m_originX) / (Real)view->getWidth()) * 2.0f - 1.0f;
		normalizedRegion.hi.y = -(((Real)(screenRegion->lo.y - view->m_originY) / (Real)view->getHeight()) * 2.0f - 1.0f);
	}

	Drawable *onlyDrawableToTest = NULL;
	if (regionIsPoint)
	{
		PickType pickType = (PickType)(Rva00459060(TheInGameUI->isInForceAttackMode()) | 0x100);
		onlyDrawableToTest = view->pickDrawable(&screenRegion->lo, TRUE, pickType);
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
