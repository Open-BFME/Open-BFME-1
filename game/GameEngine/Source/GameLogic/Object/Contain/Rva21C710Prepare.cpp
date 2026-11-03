// cl: 
// ?prepare0021C4B0@Rva21C710Owner@@QAEXPAVRva21C710Object@@@Z
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

struct Coord3D;
struct Rva21C710Vector
{
	float x;
	float y;
	float z;
	void set(const Coord3D *a);

};

class Rva21C710Object
{
public:
	const struct Rva21C710Vector *getPosition() const;
	int getMultiLogicalBonePosition(const char *, int, struct Coord3D *,
		void *, bool, int) const;
	void setPosition(const struct Coord3D *);
	void notifyModelConditionChanged();
	void setStatus(const struct Rva21C710StatusMask &, bool);

	char gap[0x90];
	unsigned char status;
};

// class-gate: allow Coord3D Retail array callbacks require the constructor and destructor omitted by the generated layout header.
struct Coord3D
{
	Coord3D();
	~Coord3D();

	float x;
	float y;
	float z;
};

// ?set@Rva21C710Vector@@QAEXPAUCoord3D@@@Z absent-from-retail
inline void Rva21C710Vector::set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }

#include "../object.h"

class Rva21C710StatusMask
{
public:
	enum _dummy_kInit { kInit };

	Rva21C710StatusMask(_dummy_kInit, int bit)
	{
		set(bit);
	}

	void set(int bit)
	{
		words.set(bit);
	}

	_STL::bitset<86> words;
};


class Rva21C710OwnerInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void prepared(Rva21C710Object *);
};

class Rva21C710Owner
{
public:
	void prepare0021C4B0(Rva21C710Object *object);

	Rva21C710Object *getObject() const
	{
		return object;
	}

	const struct Rva21C710OwnerContext *getContext() const
	{
		return context;
	}

private:
	void *vtable;
	struct Rva21C710OwnerContext *context;
	Rva21C710Object *object;
	char gap0C[0x14];
	class Rva21C710OwnerInterface interface;
};

// The matched dispatcher calls this owner through its interface at offset 0x20.

struct Rva21C710OwnerStringHolder
{
	void *data;
};

struct Rva21C710OwnerContext
{
	char gap[0x11C];
	Rva21C710OwnerStringHolder *nameHolder;
};

#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class Gen_00411DD0
{
public:
	void bfmeSet(bool value);
};

class Rva21C710PrepareObjectView
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
	virtual Gen_00411DD0 *getDrawable() = 0;

	char gap04[0x38 - 0x04];
	Rva21C710Vector position;
	char gap44[0x110 - 0x44];
	unsigned int modelConditionWord0;
	unsigned int modelConditionWord1;
	unsigned int modelConditionWord2;
	char gap11C[0x208 - 0x11C];
	class Rva21C710Physics *physics;
};

// ?getPosition@Rva21C710Object@@QBEPBURva21C710Vector@@XZ absent-from-retail
inline const Rva21C710Vector *Rva21C710Object::getPosition() const
{
	return &((const Rva21C710PrepareObjectView *)this)->position;
}

class Rva21C710Physics
{
public:
	char gap00[0x5F];
	unsigned char motiveState;
};

float g_rva00EAEB4C = 3.5f;
float g_rva00EAEB48 = 3.0f;
extern void j_00008337();
extern void j_0000d81e();
extern void j_000107ad();
extern void j_0001364c();
extern void j_00016c93();
extern void j_0002191d();
extern void j_0002a284();
extern void j_0002bd82();
extern void j_000307e7();
extern void j_0003a1a7();
extern void j_00001bae();
extern int GetGameLogicRandomValue(int, int, char *, int);

typedef int (Rva21C710Object::*Rva21C710GetBones)(const char *, int,
	Coord3D *, void *, bool, int) const;
typedef void (Rva21C710Object::*Rva21C710SetPosition)(const Coord3D *);
typedef void (Rva21C710Object::*Rva21C710NotifyConditions)();
typedef void (Rva21C710Object::*Rva21C710SetStatus)(
	const Rva21C710StatusMask &, bool);
typedef void (Rva21C710Physics::*Rva21C710ApplyForce)(
	const Rva21C710Vector *);
typedef void (Rva21C710Physics::*Rva21C710SetMotiveState)(bool);
typedef void (Coord3D::*Rva21C710Normalize)();
typedef int (__cdecl *Rva21C710Random)(int, int, char *, int);
typedef void (Gen_00411DD0::*Rva21C710BfmeSet)(bool);

// ?prepare0021C4B0@Rva21C710Owner@@QAEXPAVRva21C710Object@@@Z
void Rva21C710Owner::prepare0021C4B0(Rva21C710Object *object)
{
	Coord3D positions[32];
	AsciiString prefix(*(const AsciiString *)
		((const unsigned char *)getContext()->nameHolder->data + 0x20));

	union { void (*raw)(); Rva21C710GetBones member; } boneCall;
	boneCall.raw = j_000107ad;
	int count = (getObject()->*boneCall.member)(prefix.str(), 32, positions, 0, true, 0);

	Rva21C710PrepareObjectView *view =
		(Rva21C710PrepareObjectView *)object;
	Rva21C710Physics *physics = view->physics;
	if (physics != 0)
	{
		union
		{
			void (*raw)();
			Rva21C710Random function;
		} randomCall;
		randomCall.raw = j_00001bae;
		int index = randomCall.function(0, count - 1,
			(char *)"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\ContestableContain.cpp", 0x24C);
		Coord3D *point = &positions[index];

		Rva21C710SetPosition setPosition;
		union
		{
			void (*raw)();
			Rva21C710SetPosition member;
		} setPositionCall;
		setPositionCall.raw = j_0003a1a7;
		setPosition = setPositionCall.member;
		(object->*setPosition)(point);

		const Rva21C710Vector *origin = getObject()->getPosition();
		Rva21C710Vector direction;
		float originX = origin->x;
		float originY = origin->y;
		// Preserve the position snapshot write before replacing its vertical component.
		*(volatile float *)&direction.z = origin->z;
		direction.set(point);
		direction.x -= originX;
		direction.y -= originY;
		direction.z = 0.0f;

		Rva21C710Normalize normalize;
		union
		{
			void (*raw)();
			Rva21C710Normalize member;
		} normalizeCall;
		normalizeCall.raw = j_0002bd82;
		normalize = normalizeCall.member;
		(((Coord3D *)&direction)->*normalize)();

		float forceX = direction.x * g_rva00EAEB4C;
		float forceY = direction.y * g_rva00EAEB4C;
		Rva21C710Vector force;
		force.x = forceX;
		force.y = forceY;
		force.z = g_rva00EAEB48;

		Rva21C710ApplyForce applyForce;
		union
		{
			void (*raw)();
			Rva21C710ApplyForce member;
		} applyForceCall;
		applyForceCall.raw = j_0002a284;
		applyForce = applyForceCall.member;
		(physics->*applyForce)(&force);

		Rva21C710SetMotiveState setMotiveState;
		union
		{
			void (*raw)();
			Rva21C710SetMotiveState member;
		} setMotiveStateCall;
		setMotiveStateCall.raw = j_0000d81e;
		setMotiveState = setMotiveStateCall.member;
		(physics->*setMotiveState)(true);
		physics->motiveState = 1;

		Rva21C710BfmeSet bfmeSet;
		union
		{
			void (*raw)();
			Rva21C710BfmeSet member;
		} bfmeSetCall;
		bfmeSetCall.raw = j_00008337;
		bfmeSet = bfmeSetCall.member;
		(view->getDrawable()->*bfmeSet)(false);
	}

	if ((view->modelConditionWord2 & 0x80) == 0)
	{
		view->modelConditionWord2 |= 0x80;

		Rva21C710NotifyConditions notifyConditions;
		union
		{
			void (*raw)();
			Rva21C710NotifyConditions member;
		} notifyConditionsCall;
		notifyConditionsCall.raw = j_0002191d;
		notifyConditions = notifyConditionsCall.member;
		(object->*notifyConditions)();
	}

	Rva21C710SetStatus setStatus;
	union
	{
		void (*raw)();
		Rva21C710SetStatus member;
	} setStatusCall;
	setStatusCall.raw = j_000307e7;
	setStatus = setStatusCall.member;
	(object->*setStatus)(
		Rva21C710StatusMask(Rva21C710StatusMask::kInit, 6), false);

	interface.prepared(object);
}
