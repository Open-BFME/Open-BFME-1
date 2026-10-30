// cl: /DNDEBUG /DWIN32 /MD /O2 /Ob2 /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// RainOfFireUpdate::update, retail 0x002A0D90 (789 bytes through its ret at
// +0x314).
// BFME 1 target evidence: the matched constructor 0x002A0920 installs vtable
// VA 0x010C1844 at +0x10, whose slot 0 reaches this body, and ilt_oracle
// confirms ?update@RainOfFireUpdate@@UAE?AW4UpdateSleepTime@@XZ. `this` is
// the UpdateModuleInterface subobject (module+0x10): module data at -0xC,
// the Object at -8. The matched setter 0x002A0AD0 receives the full module
// (this-0x10); the random draws cite RainOfFireUpdate.cpp lines 125, 142 and
// 143. Module-data and member offsets are read from the retail loads; their
// names stay offset-derived.
// Donor (open-bfme-2 20a0cb6173, Code/GameEngine/Source/GameLogic/Object/
// Update/RainOfFireUpdate.cpp, retail 0x004AC2A8 there, 817 B) supplies the
// control flow: fade-in scale, ramp, accumulated shots fired from the
// tactical view's position toward an offset ground point.
#include <math.h>
#include "vector3.h"
#include "matrix3d.h"

typedef float Real;
typedef bool Bool;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// class-gate: allow Coord3D the ledgered callees take the struct-keyed (PBU) Coord3D and this body needs only its three components.
struct Coord3D
{
	Real x, y, z;
};

class Thing
{
public:
	void rva00132200(const Matrix3D *mtx);	// 0x00132200
};

class Weapon;
class WeaponSet
{
public:
	Weapon *getWeaponInWeaponSlot(WeaponSlotType slot) const;
};

class Object : public Thing
{
public:
	unsigned char m_pad000[0x264];
	WeaponSet m_weaponSet;				// +0x264
};

class Weapon
{
public:
	void loadAmmoNow(const Object *source);
	bool fireWeapon(const Object *source, const Coord3D *pos, int *projectileID);
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	unsigned int m_frame;				// +0x3C
};
extern GameLogic *TheGameLogic;

class TerrainLogic
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
	virtual void v10(); virtual void v14(); virtual void v18();
	virtual Real v1C(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal, Bool clip);
	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *point, Bool onlyHealthyBridges);
};
extern TerrainLogic *TheTerrainLogic;

template<int N> class Rva002A0D90ViewSlots : public Rva002A0D90ViewSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template<> class Rva002A0D90ViewSlots<0>
{
};
class View : public Rva002A0D90ViewSlots<69>
{
public:
	virtual void v114(Coord3D *pos);		// slot 69
};
extern View *TheTacticalView;

extern Real GetGameLogicRandomValueReal(Real lo, Real hi, char *file, int line);
extern Real Cos(Real angle);
extern Real Sin(Real angle);

// The matched setter 0x002A0AD0 (Gen002A0AD0_setScale.cpp).
class Gen002A0AD0
{
public:
	void setScale(Real value);
};

struct Rva002A0D90ModuleData
{
	unsigned char m_pad00[8];
	unsigned int m_data08;				// +0x08 frames before the rain starts
	unsigned int m_data0C;				// +0x0C fade-in frames
	Real m_data10;					// +0x10 firing height
	unsigned char m_pad14[4];
	Real m_data18;					// +0x18 jitter radius
	Real m_data1C;					// +0x1C random range low
	Real m_data20;					// +0x20 random range high
	Real m_data24;					// +0x24 ramp-up divisor
	Real m_data28;					// +0x28 target offset x
	Real m_data2C;					// +0x2C target offset y
};

class RainOfFireUpdate
{
public:
	virtual UpdateSleepTime update();
private:
	unsigned char m_pad04[0x14 - 4];
	unsigned int m_field14;				// +0x14 start frame
	Real m_field18;					// +0x18
	Real m_field1C;					// +0x1C
	Real m_field20;					// +0x20 pending shots
	Real m_field24;					// +0x24 ramp
};

#define RAIN_OF_FIRE_FILE "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\RainOfFireUpdate.cpp"

// The inlined normalize sums its squares as Z, Y, X (retail +0x224 keeps the
// just-computed z on the x87 stack); the shared vector3.h Length2() spelling
// sums Y, Z, X here, so this TU keeps a local Normalize twin.
static WWINLINE void Rva002A0D90Normalize(Vector3 &v)
{
	float len2 = v.Z * v.Z;
	len2 += v.Y * v.Y;
	len2 += v.X * v.X;
	if (len2 != 0.0f)
	{
		float oolen = WWMath::Inv_Sqrt(len2);
		v.X *= oolen;
		v.Y *= oolen;
		v.Z *= oolen;
	}
}

UpdateSleepTime RainOfFireUpdate::update()
{
	Object *obj = *(Object **)((char *)this - 8);
	const Rva002A0D90ModuleData *data = *(const Rva002A0D90ModuleData **)((char *)this - 0xc);
	if (!data)
		return UPDATE_SLEEP_FOREVER;
	unsigned int elapsed = TheGameLogic->m_frame - m_field14;
	if (elapsed <= data->m_data0C)
	{
		Real value = data->m_data0C ? (Real)elapsed / (Real)data->m_data0C : 1.0f;
		((Gen002A0AD0 *)((char *)this - 0x10))->setScale(value);
	}
	if (elapsed >= data->m_data08)
	{
		if (m_field24 < 1.0f)
		{
			m_field24 += 1.0f / data->m_data24;
			if (m_field24 > 1.0f)
				m_field24 = 1.0f;
		}
		m_field20 += GetGameLogicRandomValueReal(data->m_data1C, data->m_data20, RAIN_OF_FIRE_FILE, 125) * m_field1C * m_field24 * 0.2f;
		Weapon *weapon = obj->m_weaponSet.getWeaponInWeaponSlot(PRIMARY_WEAPON);
		if (weapon)
		{
			Coord3D center;
			TheTacticalView->v114(&center);
			center.z = data->m_data10;
			while (m_field20 >= 1.0f)
			{
				Coord3D pos = center;
				if (data->m_data18 > 0.0f)
				{
					Real angle = GetGameLogicRandomValueReal(0.0f, 6.2831855f, RAIN_OF_FIRE_FILE, 142);
					Real radius = GetGameLogicRandomValueReal(0.0f, data->m_data18, RAIN_OF_FIRE_FILE, 143);
					pos.x += Cos(angle) * radius;
					pos.y += Sin(angle) * radius;
				}
				Coord3D target;
				target.z = pos.z;
				target.x = pos.x + data->m_data28;
				target.y = pos.y + data->m_data2C;
				PathfindLayerEnum layer = TheTerrainLogic->getHighestLayerForDestination(&target, false);
				target.z = TheTerrainLogic->v1C(target.x, target.y, layer, 0, true);
				Vector3 dir(target.x - pos.x, target.y - pos.y, target.z - pos.z);
				Rva002A0D90Normalize(dir);
				Matrix3D transform;
				transform.buildTransformMatrix(Vector3(pos.x, pos.y, pos.z), dir);
				obj->rva00132200(&transform);
				weapon->loadAmmoNow(obj);
				weapon->fireWeapon(obj, &target, 0);
				m_field20 -= 1.0f;
			}
		}
		else
			m_field20 = 0.0f;
		((Gen002A0AD0 *)((char *)this - 0x10))->setScale(m_field18);
	}
	return UPDATE_SLEEP_NONE;
}
