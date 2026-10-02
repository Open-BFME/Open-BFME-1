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
// The global at VA 0x012F1464 is EA's `GameClient *TheGameClient`
// (?TheGameClient@@3PAVGameClient@@A, defined in
// game/GameEngine/Source/GameClient/GameClient.cpp), so it is declared with that
// canonical spelling here and this TU's ClientRoot4120 view is reached through a
// cast.  Slot 12 of that view is the proven ?firstDrawable@GameClient@@ at
// 0x004318B0 (targets/game/reverse/functions.csv, GameClient vtable 0x01120468).
//
// Shape note: the pick-type mask must be computed into its own local before
// the pickDrawable call.  Spelled inline as an argument, MSVC 7.1 hoists the
// vtable load above the Rva00459060 call into EBX, which adds a call-crossing
// candidate and permutes ESI/EDI for `this` and screenRegion across 53 bytes.

typedef int Int;
typedef float Real;
typedef bool Bool;

#include "../../../../Libraries/Source/WWVegas/WWMath/region.h"

#define NULL 0
#define TRUE true
#define FALSE false

struct ICoord2D
{
	Int x;
	Int y;
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

class GameClient;
extern GameClient *TheGameClient;
static inline ClientRoot4120 *theGameClientView() { return (ClientRoot4120 *)TheGameClient; }
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
	Vector3 screen, world, pos;
	Real normalizedRegion[4];

	Bool regionIsPoint = FALSE;

	if (screenRegion)
	{
		if (screenRegion->y_max - screenRegion->y_min == 0 &&
			screenRegion->x_max - screenRegion->x_min == 0)
		{
			regionIsPoint = TRUE;
		}

		normalizedRegion[0] = ((Real)(screenRegion->x_min - view->m_originX) / (Real)view->getWidth()) * 2.0f - 1.0f;
		normalizedRegion[1] = -(((Real)(screenRegion->y_max - view->m_originY) / (Real)view->getHeight()) * 2.0f - 1.0f);
		normalizedRegion[2] = ((Real)(screenRegion->x_max - view->m_originX) / (Real)view->getWidth()) * 2.0f - 1.0f;
		normalizedRegion[3] = -(((Real)(screenRegion->y_min - view->m_originY) / (Real)view->getHeight()) * 2.0f - 1.0f);
	}

	Drawable *onlyDrawableToTest = NULL;
	if (regionIsPoint)
	{
		PickType pickType = (PickType)(Rva00459060(TheInGameUI->isInForceAttackMode()) | 0x100);
		onlyDrawableToTest = view->pickDrawable((ICoord2D *)&screenRegion->x_min, TRUE, pickType);
		if (onlyDrawableToTest == NULL)
		{
			return 0;
		}
	}

	for (draw = theGameClientView()->firstDrawable();
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
				pos = *(Vector3 *)draw->getPosition();
				world.X = pos.X;
				world.Y = pos.Y;
				world.Z = pos.Z;

				if (view->m_3DCamera->Project(screen, world) == CameraClass::INSIDE_FRUSTUM &&
					screen.X >= normalizedRegion[0] &&
					screen.X <= normalizedRegion[2] &&
					screen.Y >= normalizedRegion[1] &&
					screen.Y <= normalizedRegion[3])
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
