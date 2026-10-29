// ?update@PhysicsBehavior@@UAE?AW4UpdateSleepTime@@XZ
// Retail RVA 0x0029B760, 862 bytes, __thiscall, returns UpdateSleepTime.
// Identity proven in reverse/identity_evidence/0029b760-physicsbehavior-update.md:
// constructor 0x0029A880 installs the +0x10 update-interface table 0x010C0BBC
// whose first ILT 0x00404B06 jumps here with the secondary-interface receiver
// (full object +0x10), so module data is this-0x0C and the Object is this-8.
// Members keep the landed PhysicsBehaviorRva0029B4E0 module-relative spelling
// (at20 vector, at50 index, at58 countdown, at5C/at5D/at5E flags); config view
// fields stay address-derived.
// stlport 
// cl: /DNDEBUG /MD /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWLib
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <vector>
#include <math.h>
#define _OPERATOR_NEW_DEFINED_
#include "vector3.h"
#include "matrix3d.h"

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class ModelConditionFlags
{
public:
	__forceinline bool test(int n) const { return m_bits.test(n); }
	__forceinline void reset(int n) { m_bits.reset(n); }
	__forceinline void set(int n) { m_bits.set(n); }
	_STL::bitset<320> m_bits;
};
#define BFME_HAVE_MODELCONDITIONFLAGS
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS void setPosition(const Coord3D *); void rva00132200(const Matrix3D *);
#define OBJECT_TU_MEMBERS void notifyModelConditionChanged();
#include "object.h"

class Drawable
{
	friend class PhysicsBehavior;
private:
	void applyPendingModelConditionFlags(bool);
};

// Retail 0x000D2F40 is the 37-byte word-bit test reached through ILT 0x0000666D;
// the ledger records it under the WordBitTest000D2F40 spelling.
class WordBitTest000D2F40
{
public:
	bool test(unsigned index) const;
};

class BehaviorModuleInterface { public: virtual void bslot000(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };
class Module
{
public:
	virtual void moduleSlot000();
	void *m_moduleData;				// +0x04
	Object *m_object;				// +0x08
};
class UpdateModule : public Module, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	unsigned m_nextCallFrameAndPhase;		// +0x14
	int m_indexInLogic;				// +0x18
	int m_currentUpdatePhase;			// +0x1C
};

// Module data view: this-0x0C is full-object +4. The exit sleep time is +0x20,
// the direction flags +0x40/+0x41, and the Z scale +0x4C.
struct Config0029B760
{
	char pad00[0x20];
	int at20;
	char pad24[0x1c];
	bool at40;
	bool at41;
	char pad42[10];
	float at4c;
};

class PhysicsBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva0029A6A0(bool);
	void rva0029B4E0();

	_STL::vector<Coord3D> at20;			// +0x20
	char pad2c[0x24];				// +0x2C
	int at50;					// +0x50
	int at54;					// +0x54
	int at58;					// +0x58
	bool at5c;					// +0x5C
	bool at5d;					// +0x5D
	bool at5e;					// +0x5E

	UpdateSleepTime calcSleepTime() const
	{
		if (at20.size() != 0)
			return UPDATE_SLEEP_NONE;
		if (at5c && at58 > 0)
			return UPDATE_SLEEP_NONE;
		return UPDATE_SLEEP_FOREVER;
	}
};

class Pathfinder;
class AI
{
public:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;			// +0x0C
	Pathfinder *pathfinder() const { return m_pathfinder; }
};
extern AI *TheAI;
class Pathfinder { public: void Rva003E4190(Object *); };

// Retail 0x012ED5C8 is TheWritableGlobalData (dir32); the body reads +0x1AC.
struct BfmeGlobalData { char pad00[0x1ac]; float at1ac; };
extern BfmeGlobalData *TheWritableGlobalData;
extern float g_bfmeScaleBC;

// Object+0x178/+0x186 is the next-position hint inside m_unmodelled138; the
// valid flag is stored before the position, as retail does.
inline void setHint0029B760(Object *obj, const Coord3D *pos)
{
	*(bool *)((char *)obj + 0x186) = true;
	*(Coord3D *)((char *)obj + 0x178) = *pos;
}

// ?update@PhysicsBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime PhysicsBehavior::update()
{
	Config0029B760 *data = (Config0029B760 *)m_moduleData;
	Object *obj = m_object;
	at5e = false;
	bool changed = false;

	if (at5c && at58 > 0 && !(obj->m_privateStatus & 1) && --at58 <= 0)
	{
		if (obj->m_modelConditionFlags.test(121))
		{
			obj->m_modelConditionFlags.reset(121);
			obj->notifyModelConditionChanged();
			if (!obj->m_modelConditionFlags.test(153))
			{
				obj->m_modelConditionFlags.set(153);
				obj->notifyModelConditionChanged();
			}
			at58 = data->at20;
			changed = true;
		}
		else
		{
			// The call is written in both arms: VC7.1 tail-merges the two
			// copies, which is what puts the receiver lea before push 0.
			if (((WordBitTest000D2F40 *)((char *)obj + 0x110))->test(153))
			{
				if (obj->m_modelConditionFlags.test(153))
				{
					obj->m_modelConditionFlags.reset(153);
					obj->notifyModelConditionChanged();
				}
				rva0029A6A0(false);
			}
			else
				rva0029A6A0(false);
		}
	}

	if ((unsigned)at50 >= at20.size())
	{
		PhysicsBehavior *self = (PhysicsBehavior *)((char *)this);
		self->rva0029B4E0();
		return self->calcSleepTime();
	}

	if (changed && obj->getDrawable())
		obj->getDrawable()->applyPendingModelConditionFlags(false);

	Coord3D &pos = at20[at50];

	if (data->at41 && !data->at40 && at50 > 0)
	{
		Vector3 direction(pos.x - at20[at50 - 1].x, pos.y - at20[at50 - 1].y,
				pos.z - at20[at50 - 1].z);
		if (at54 > 0)
			direction.Z = TheWritableGlobalData->at1ac * data->at4c * g_bfmeScaleBC;
		direction.Normalize();
		Vector3 position(pos.x, pos.y, pos.z);
		Matrix3D transform;
		transform.buildTransformMatrix(position, direction);
		m_object->rva00132200(&transform);
	}
	else
	{
		m_object->setPosition(&pos);
	}

	if ((unsigned)at50 < at20.size() - 1)
	{
		setHint0029B760(obj, &at20[at50 + 1]);
	}
	else
	{
		// Extrapolate one step past the last waypoint. Built in place with
		// *= and -=, the product shares next's slot (retail frame 0x4C).
		Vector3 previous(obj->m_cachedPos.x, obj->m_cachedPos.y, obj->m_cachedPos.z);
		Vector3 next(pos.x, pos.y, pos.z);
		next *= 2.0f;
		next -= previous;
		setHint0029B760(obj, (const Coord3D *)&next);
	}

	TheAI->pathfinder()->Rva003E4190(m_object);
	++at50;

	return calcSleepTime();
}
