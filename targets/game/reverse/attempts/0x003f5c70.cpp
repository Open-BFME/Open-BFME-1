// ?rva003f5c70@Pathfinder@@QAEEPAVObject@@PAXPAUCoord3D@@@Z
// partial score=0.95 date=2026-09-26
// cl: /O2 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath

typedef int Int;
typedef unsigned char Bool;
typedef float Real;

struct Coord3D
{
	Real x, y, z;
	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
};

struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class BfmeOverridable
{
public:
	__declspec(noinline) BfmeOverridable *friend_getFinalOverride();
	BfmeOverridable *getFinalOverride()
	{
		return m_override ? m_override->friend_getFinalOverride() : this;
	}

	Int m_unknown00;
	BfmeOverridable *m_override;
	char m_pad08[0xc8 - 8];
	Int m_flagsC8;
};

class Object
{
public:
	BfmeOverridable *getTemplate()
	{
		BfmeOverridable *result = m_template;
		if (result && result->m_override)
			result = result->getFinalOverride();
		return result;
	}

	Int m_unknown00;
	BfmeOverridable *m_template;
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip) const;

	PathfindLayerEnum getLayerForDestination(Object *obj,
		const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Rva003F55E0
{
public:
	Bool call(const ICoord2D *center, Int radius, ICoord2D *found,
		void *userData);
};

class Rva003E6200Info
{
public:
	Rva003E6200Info(class Pathfinder *pathfinder, Object *obj, void *arg3,
		const Coord3D *pos, Real arg5);

	class Pathfinder * volatile m_pathfinder;
	Object * volatile m_obj;
	void * volatile m_arg3;
	Bool m_notComputer;
	Bool m_center;
	Int m_radius;
	PathfindLayerEnum m_layer;
	Int volatile m_arg5;
	Int m_pad1c;
	Int m_pad20;
	Int volatile m_zero24;
	volatile Coord3D m_pos;
};

class Pathfinder
{
public:
	Bool rva003f5c70(Object *obj, void *arg3, Coord3D *dest);
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);

protected:
	void getRadiusAndCenter(const Object *obj, Int &radius, Bool &center);
	void adjustCoordToCell(Int x, Int y, Bool center, Coord3D &pos,
		PathfindLayerEnum layer);
};

Bool Pathfinder::rva003f5c70(Object *obj, void *arg3, Coord3D *dest)
{
	Object *object = obj;
	BfmeOverridable *objectTemplate = object->m_template;
	if (objectTemplate && objectTemplate->m_override)
		objectTemplate = objectTemplate->getFinalOverride();
	if (objectTemplate->m_flagsC8 & 0x02000000)
		return true;

	Bool center;
	ICoord2D cell;
	{
		Coord3D adjusted;
		getRadiusAndCenter(object, (Int &)adjusted.x, center);
		adjusted.set(dest);
		if (!center)
		{
			adjusted.x += 5.0f;
			adjusted.y += 5.0f;
		}
		worldToCell(&adjusted, &cell);
	}

	Rva003E6200Info info(this, object, arg3, dest,
		TheTerrainLogic->getLayerHeight(dest->x, dest->y,
			TheTerrainLogic->getLayerForDestination(object, dest), 0, true));
	{
		ICoord2D found;
		if (((Rva003F55E0 *)this)->call(&cell, 200, &found, &info))
		{
			adjustCoordToCell(found.x, found.y, center, *dest,
				(PathfindLayerEnum)info.m_layer);
			return true;
		}
	}
	if (info.m_zero24)
	{
		adjustCoordToCell(info.m_pad1c, info.m_pad20, center, *dest,
			(PathfindLayerEnum)info.m_layer);
		return true;
	}
	return false;
}

#pragma comment(linker, "/alternatename:?friend_getFinalOverride@BfmeOverridable@@QAEPAV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRadiusAndCenter@Pathfinder@@IAEXPBVObject@@AAHAA_N@Z=?j_000461ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?worldToCell@Pathfinder@@QAE_NPBVCoord3D@@PAUICoord2D@@@Z=?j_000171e8@@YAXXZ")
#pragma comment(linker, "/alternatename:?getLayerForDestination@TerrainLogic@@QAE?AW4PathfindLayerEnum@@PAVObject@@PBVCoord3D@@@Z=?j_0001c675@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva003E6200Info@@QAE@PAVPathfinder@@PAVObject@@PAXPBVCoord3D@@M@Z=?j_0003592c@@YAXXZ")
#pragma comment(linker, "/alternatename:?call@Rva003F55E0@@QAE_NPBUICoord2D@@HPAU2@PAX@Z=?j_00034e0a@@YAXXZ")
#pragma comment(linker, "/alternatename:?adjustCoordToCell@Pathfinder@@IAEXHH_NAAVCoord3D@@W4PathfindLayerEnum@@@Z=?j_000411d2@@YAXXZ")
