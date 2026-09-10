// ?prepare@Rva21C710Owner@@QAEXPAVRva21C710Object@@@Z
// partial score=0.88 date=2026-09-10
struct Rva21C710Vector
{
	float x;
	float y;
	float z;
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

struct Coord3D
{
	Coord3D();
	~Coord3D();

	float x;
	float y;
	float z;
};

class Rva21C710StatusMask
{
public:
	unsigned int words[3];

	void set(int bit)
	{
		words[bit >> 5] |= 1U << (bit & 31);
	}
};

const Rva21C710Vector *Rva21C710Object::getPosition() const
{
	return (const Rva21C710Vector *)((const unsigned char *)this + 0x38);
}

struct Rva21C710Node
{
	Rva21C710Node *next;
	Rva21C710Node *previous;
	Rva21C710Object *object;
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
	void prepare(Rva21C710Object *object);

private:
	void *vtable;
	struct Rva21C710OwnerContext *context;
	char gap08[0x18];
	class Rva21C710OwnerInterface interface;
};

class Rva21C710MemberDispatch
{
public:
	void dispatch(Rva21C710Object *object, void *action);
	void dispatchNew(Rva21C710Object *object, void *action);
	void dispatchMember(Rva21C710Object *object, void *action);

private:
	char gap[0x99C];
	Rva21C710Node *members;
};

void Rva21C710MemberDispatch::dispatch(Rva21C710Object *object, void *action)
{
	if ((object->status & 0x40) != 0)
		((Rva21C710Owner *)((char *)this - 0x20))->prepare(object);

	Rva21C710Node *end = members;
	Rva21C710Node *node = end->next;

	while (node != end) {
		if (node->object == object) {
			dispatchMember(object, 0);
			return;
		}
		node = node->next;
	}

	dispatchNew(object, action);
}

// The caller above reaches this body through ILT 0x0000D468.  Its adjacent
// 0x001F9180 sibling establishes the same BFME helper idiom: a 32-element
// Coord3D EH array, an AsciiString copied from a nested owner field, and the
// six-argument Object bone query.  The remaining calls below are kept bound to
// their observed retail ILTs rather than relying on a same-named ZH overload.

struct Rva21C710OwnerStringHolder
{
	void *data;
};

struct Rva21C710OwnerContext
{
	char gap[0x11C];
	Rva21C710OwnerStringHolder *nameHolder;
};

template <class CharType>
class StringBase
{
	friend class AsciiString;

private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		CharType data[1];
	};

	StringBase(const StringBase &other);
	void releaseBuffer();

protected:
	Header *data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString(const AsciiString &other)
		: StringBase<char>(*(const StringBase<char> *)&other)
	{
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	const char *str() const
	{
		return data != 0 ? &data->data[0] : (const char *)0x0107388B;
	}
};

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

	char gap2C[0x38 - 0x2C];
	Rva21C710Vector position;
	char gap44[0x110 - 0x44];
	unsigned int modelConditionWord0;
	unsigned int modelConditionWord1;
	unsigned int modelConditionWord2;
	char gap11C[0x208 - 0x11C];
	class Rva21C710Physics *physics;
};

class Rva21C710Physics
{
public:
	char gap00[0x5F];
	unsigned char motiveState;
};

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

// ?prepare@Rva21C710Owner@@QAEXPAVRva21C710Object@@@Z
void Rva21C710Owner::prepare(Rva21C710Object *object)
{
	Coord3D positions[32];
	AsciiString prefix(*(const AsciiString *)
		((const unsigned char *)context->nameHolder->data + 0x20));

	Rva21C710GetBones getBones;
	union
	{
		void (*raw)();
		Rva21C710GetBones member;
	} getBonesCall;
	getBonesCall.raw = j_000107ad;
	getBones = getBonesCall.member;
	int count = (object->*getBones)(prefix.str(), 32, positions, 0, true, 0);

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
			(char *)0x010AB460, 0x24C);
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

		Rva21C710Vector direction;
		direction.x = object->getPosition()->x - point->x;
		direction.y = object->getPosition()->y - point->y;
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

		Rva21C710Vector force;
		force.x = direction.x * *(volatile float *)0x012AEB4C;
		force.y = direction.y * *(volatile float *)0x012AEB4C;
		*(unsigned int *)&force.z =
			*(volatile unsigned int *)0x012AEB48;

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

		Gen_00411DD0 *drawable = view->getDrawable();
		Rva21C710BfmeSet bfmeSet;
		union
		{
			void (*raw)();
			Rva21C710BfmeSet member;
		} bfmeSetCall;
		bfmeSetCall.raw = j_00008337;
		bfmeSet = bfmeSetCall.member;
		(drawable->*bfmeSet)(false);
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

	Rva21C710StatusMask status;
	status.words[0] = 0;
	status.words[1] = 0;
	status.words[2] = 0;
	status.set(6);

	Rva21C710SetStatus setStatus;
	union
	{
		void (*raw)();
		Rva21C710SetStatus member;
	} setStatusCall;
	setStatusCall.raw = j_000307e7;
	setStatus = setStatusCall.member;
	(object->*setStatus)(status, false);

	interface.prepared(object);
}
