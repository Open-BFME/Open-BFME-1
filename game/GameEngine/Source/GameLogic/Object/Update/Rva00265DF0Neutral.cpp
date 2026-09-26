// cl: /DNDEBUG /MD /EHsc
// Genuine C++ reconstruction of retail RVA 0x00265DF0 (168 bytes).
//
// The generated row has no named caller or constructor/vtable evidence.  The
// neutral owner name therefore records the proven raw ABI rather than
// inventing a gameplay class.  Retail is a no-argument __thiscall method:
// this+0x28 is an object id, this+0x2c is a Coord3D, and this+0x38 is a retry
// counter.  The containing owner object is at this-0x08.

typedef int CommandSourceType;
// Preserve the retail source value without assigning a disputed enum identity.
enum { RETAIL_COMMAND_SOURCE_2 = 2 };

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Object;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

#define TheBfmeGameLogic (*(GameLogic **)0x012F0898)

class Object
{
public:
	unsigned char m_unreconstructed_000[0x94];
	unsigned int m_unreconstructed_094;
	unsigned char m_unreconstructed_098[0x16c];
	class Rva00265DF0AI *m_ai;
	unsigned char m_unreconstructed_208[0x13c];
	unsigned char m_unreconstructed_344;
};

template <int N>
class Rva00265DF0VirtualSlots : public Rva00265DF0VirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <> class Rva00265DF0VirtualSlots<0> {};

// AIUpdateInterface's existing declaration places this query at slot 128.
// This declaration-only view emits no table; it only gives the retail virtual
// call its proven [vptr+0x200] shape.
class Rva00265DF0AI : public Rva00265DF0VirtualSlots<128>
{
public:
	virtual CommandSourceType getLastCommandSource() const;
};

class Rva00265DF0CommandInterface
{
};

class Rva00265DF0Owner
{
public:
	int run();

private:
	unsigned char m_unreconstructed_000[0x28];
	int m_targetObjectID;
	Coord3D m_targetPosition;
	int m_retryCount;
};

extern void j_0001f253();
extern void j_00024d70();
extern void j_0003436a();
extern void j_00041074();

typedef Object *(GameLogic::*FindObjectByIDCall)(int id);
typedef void (Rva00265DF0CommandInterface::*IdleCall)(CommandSourceType cmdSource);
typedef void (Rva00265DF0CommandInterface::*MoveCall)(const Coord3D *position,
	CommandSourceType cmdSource);
typedef void (Rva00265DF0CommandInterface::*TargetCall)(Object *object,
	CommandSourceType cmdSource);

int Rva00265DF0Owner::run()
{
	union
	{
		void *asVoid;
		FindObjectByIDCall asMember;
	} findObjectCast;
	findObjectCast.asVoid = (void *)j_0001f253;
	Object *target = (TheBfmeGameLogic->*findObjectCast.asMember)(m_targetObjectID);

	Object *ownerObject = *reinterpret_cast<Object **>(reinterpret_cast<unsigned char *>(this) - 8);
	Rva00265DF0AI *ai = ownerObject->m_ai;
	if (ai == 0 || ai->getLastCommandSource() == 0)
		return 0x3fffffff;

	if (target == 0 || (target->m_unreconstructed_344 & 1) != 0)
		goto idle;

	if ((target->m_unreconstructed_094 & 0x04000000) != 0)
	{
		int retryCount = ++m_retryCount;
		if (retryCount < 5)
			return 1;

		Rva00265DF0CommandInterface *commands =
			reinterpret_cast<Rva00265DF0CommandInterface *>(
				reinterpret_cast<unsigned char *>(ai) + 0x20);
		m_retryCount = 0;
		union
		{
			void *asVoid;
			IdleCall asMember;
		} idleCast;
		idleCast.asVoid = (void *)j_00024d70;
		(commands->*idleCast.asMember)(RETAIL_COMMAND_SOURCE_2);
		union
		{
			void *asVoid;
			MoveCall asMember;
		} moveCast;
		moveCast.asVoid = (void *)j_0003436a;
		(commands->*moveCast.asMember)(&m_targetPosition, RETAIL_COMMAND_SOURCE_2);
		return 0x3fffffff;
	}

	{
		Rva00265DF0CommandInterface *commands =
			reinterpret_cast<Rva00265DF0CommandInterface *>(
				reinterpret_cast<unsigned char *>(ai) + 0x20);
		union
		{
			void *asVoid;
			TargetCall asMember;
		} targetCast;
		targetCast.asVoid = (void *)j_00041074;
		(commands->*targetCast.asMember)(target, RETAIL_COMMAND_SOURCE_2);
		return 1;
	}

idle:
	{
		Rva00265DF0CommandInterface *commands =
			reinterpret_cast<Rva00265DF0CommandInterface *>(
				reinterpret_cast<unsigned char *>(ai) + 0x20);
		union
		{
			void *asVoid;
			IdleCall asMember;
		} idleCast;
		idleCast.asVoid = (void *)j_00024d70;
		(commands->*idleCast.asMember)(RETAIL_COMMAND_SOURCE_2);
		return 0x3fffffff;
	}
}
