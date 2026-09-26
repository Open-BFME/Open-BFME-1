// ?rva00431A60@GameClient@@UAEXPAVFrustumClass@@MP6AXPAVDrawable@@PAX@Z2@Z
// partial score=0.9607843137254902 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// GameClient virtual at retail 0x00431A60 (357B), address-derived method name.
//
// Owner: GameClient vtables 0x01120468 and 0x010F37F0 hold ILT 0x00021B07
// (jmp 0x00431A60) at slot 21 (+0x54); slot 12 of 0x01120468 is the matched
// GameClient::firstDrawable (0x004318B0) and slot 2 is
// SubsystemInterface::loadIniFilesFromLegend. m_drawableList +0x10 and the
// Drawable next link +0x104 match the landed GameClient::reset and
// GameClient::iterateDrawablesInRegion. The one caller (0x007450CF) runs
// CameraClass::Update_Frustum and passes camera+0x104 (the camera frustum), a
// sqrt-derived float, callback 0x00B3AD50 and a user pointer through
// [vtable+0x54].
//
// Body: walk the drawable list; a drawable whose object's template has bit
// 0x20 at +0xD8 bypasses culling and is always reported. Otherwise build a
// sphere from the interpolated position (0x0041D150) and the radius helper at
// 0x00416B20 plus the extra radius, test the cached plane index at +0x2E8
// first, then side planes 1..4 with the WWMath PlaneClass::In_Front(const
// SphereClass &) inline. Visible drawables go to the callback, clear the
// cached plane and get bfmeGo923B(1); culled or hidden ones get bfmeGo923B(0).

#include "sphere.h"
#include "frustum.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
private:
	void *m_vtable;
	const Overridable *m_nextOverride;

public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride != 0)
			return m_nextOverride->getFinalOverride();
		return this;
	}
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_opaque[0xD8 - sizeof(Overridable)];
	unsigned char m_byteD8;
};

template <class T> class OverridePtr
{
private:
	const T *m_overridable;

public:
	operator const T *() const
	{
		if (m_overridable == 0)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
private:
	void *m_vtable;
	OverridePtr<ThingTemplate> m_template;

public:
	const ThingTemplate *getTemplate() const { return m_template; }
};

class Object : public Thing
{
};

// Matched 0x0041D150 spelling (BFMERopeDrawableLinearInterpolatedPosition.cpp).
struct BfmeLinearCoord3D
{
	float x;
	float y;
	float z;
};

class BFMERopeDrawableGetPositionShim
{
public:
	const BfmeLinearCoord3D *getPositionLinear() const;
};

// Matched 0x00416B20 spelling (Rva00416B20GetFloat.cpp).
class Rva00416B20
{
public:
	float get();
};

// Matched 0x00410DD0 spelling (BfmeConv923.cpp).
class BfmeThing923B
{
public:
	void bfmeGo923B(char);
};

class Drawable : public Thing
{
private:
	unsigned char m_opaque[0xFC - sizeof(Thing)];
	Object *m_object;
	unsigned char m_pad100[4];
	Drawable *m_nextDrawable;
	unsigned char m_pad108[0x2E8 - 0x108];

public:
	int m_dword2E8;

	const Object *getObject() const { return m_object; }
	Drawable *getNextDrawable() const { return m_nextDrawable; }
	bool isDrawableEffectivelyHidden() const;	///< ILT 0x00012E3B -> 0x00410BA0
};

typedef void (*GameClientFuncPtr)(Drawable *draw, void *userData);

class GameClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual Drawable *firstDrawable();
	virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20();
	virtual void rva00431A60(FrustumClass *frustum, float radius, GameClientFuncPtr userFunc, void *userData);

private:
	unsigned char m_pad[0x0C];
	Drawable *m_drawableList;
};

void GameClient::rva00431A60(FrustumClass *frustum, float radius, GameClientFuncPtr userFunc, void *userData)
{
	if (radius < 0.0f)
		radius = 25.0f;

	Drawable *draw;
	Drawable *nextDrawable;
	for (draw = m_drawableList; draw; draw = nextDrawable)
	{
		nextDrawable = draw->getNextDrawable();

		bool visible = true;
		const Object *obj = draw->getObject();
		if (!obj || !(obj->getTemplate()->m_byteD8 & 0x20))
		{
			Coord3D pos = *(const Coord3D *)((const BFMERopeDrawableGetPositionShim *)draw)->getPositionLinear();
			SphereClass sphere(Vector3(&pos.x), ((Rva00416B20 *)draw)->get() + radius);

			int plane = draw->m_dword2E8;
			if (plane >= 1 && plane <= 4 && frustum->Planes[plane].In_Front(sphere))
				continue;

			visible = !draw->isDrawableEffectivelyHidden();
			for (int i = 1; i <= 4; i++)
			{
				if (plane == i)
					continue;
				if (frustum->Planes[i].In_Front(sphere))
				{
					draw->m_dword2E8 = i;
					visible = false;
					break;
				}
			}
		}
		if (visible)
		{
			userFunc(draw, userData);
			draw->m_dword2E8 = 0;
			((BfmeThing923B *)draw)->bfmeGo923B(1);
		}
		else
		{
			((BfmeThing923B *)draw)->bfmeGo923B(0);
		}
	}
}
