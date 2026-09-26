// ?method@Rva002AA4B0Owner@@QAEXXZ
// partial score=0.46 date=2026-09-26
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

typedef bool Bool;
typedef float Real;
typedef int Int;
enum CommandSourceType { CMD_FROM_AI = 2 };

struct Coord3D
{
	Real x, y, z;
	void normalize();
	void set(const Coord3D *other) { *this = *other; }
	void zero() { x = y = z = 0.0f; }
	void scale(Real value) { x *= value; y *= value; z *= value; }
	void add(const Coord3D *other) { x += other->x; y += other->y; z += other->z; }
	void sub(const Coord3D *other) { x -= other->x; y -= other->y; z -= other->z; }
};

class Player;
class Object;
class PartitionFilter;

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *, CommandSourceType);
	void aiIdle(CommandSourceType);
};

class AIUpdateInterface
{
public:
	void ignoreObstacle(const Object *);
	AICommandInterface *getCommandInterface()
	{
		return reinterpret_cast<AICommandInterface *>(reinterpret_cast<char *>(this) + 0x20);
	}
};

class Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	const Coord3D *getPosition() const { return &m_cachedPos; }
	char m_pad_00[0x38];
	Coord3D m_cachedPos;
};

class Object : public Thing
{
public:
	Player *getControllingPlayer() const;
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	char m_pad_44[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

class GameLogic { public: Object *findObjectByID(Int); };
extern GameLogic *TheGameLogic;

template <int N> class BitFlags
{
public:
	enum BogusInitType { kInit = 0 };
	BitFlags(BogusInitType, Int);
	unsigned int bits[N / 32];
};
typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	PartitionFilter(unsigned int vptr) { m_next = 0; m_vptr = vptr; }
	PartitionFilter *link(PartitionFilter *);
	unsigned int m_vptr;
	PartitionFilter *m_next;
};

class FilterSamePlayer002AA4B0 : public PartitionFilter
{
public:
	FilterSamePlayer002AA4B0(Player *player) : PartitionFilter(0x01097144), m_player(player) {}
	~FilterSamePlayer002AA4B0() { m_vptr = 0x01083B5C; }
	Player *m_player;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	__declspec(noinline) PartitionFilterAcceptByKindOf(const KindOfMaskType &, const KindOfMaskType &);
	~PartitionFilterAcceptByKindOf() { m_vptr = 0x01083B5C; }
private:
	KindOfMaskType m_set;
	KindOfMaskType m_clear;
};

PartitionFilterAcceptByKindOf::PartitionFilterAcceptByKindOf(
	const KindOfMaskType &set, const KindOfMaskType &clear)
	: PartitionFilter(0x01083B70), m_set(set), m_clear(clear)
{
}

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *, Real, Int, PartitionFilter *);
};
extern PartitionManager *ThePartitionManager;

struct SpecialAbilityData002AA4B0
{
	char m_pad_000[0x1F8];
	Real m_fleeRangeAfterCompletion;
	char m_pad_1FC[0x244 - 0x1FC];
	Bool m_flipObjectAfterPacking;
	Bool m_flipObjectAfterUnpacking;
};

class Rva002AA4B0Owner
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
	virtual void onExit(Bool, Bool) = 0;
	void method();
private:
	SpecialAbilityData002AA4B0 *m_data;
	Object *m_object;
	char m_pad_00c[0x30 - 0x0C];
	Int m_packingState;
	char m_pad_034[0xAC - 0x34];
	Int m_targetID;
	Coord3D m_targetPos;
	char m_pad_0bc[0xE2 - 0xBC];
	Bool m_withinStartAbilityRange;
};

// ?method@Rva002AA4B0Owner@@QAEXXZ
void Rva002AA4B0Owner::method()
{
	SpecialAbilityData002AA4B0 *data = m_data;
	m_withinStartAbilityRange = false;
	m_packingState = 0;
	Bool validTarget = m_targetPos.x || m_targetPos.y || m_targetPos.z || m_targetID != 0;
	if (data->m_fleeRangeAfterCompletion && validTarget)
	{
		Coord3D pos = { m_object->m_cachedPos.x,
			m_object->m_cachedPos.y, m_object->m_cachedPos.z };
		AIUpdateInterface *ai = m_object->getAI();
		if (ai)
		{
			Coord3D dir = *m_object->getUnitDirectionVector2D();
			dir.normalize();
			dir.scale(data->m_fleeRangeAfterCompletion);
			if (data->m_flipObjectAfterUnpacking || data->m_flipObjectAfterPacking)
				pos.add(&dir);
			else
				pos.sub(&dir);
			Object *obj = m_object;
			if (obj)
			{
			Player *player = obj->getControllingPlayer();
			if (player)
			{
				Object *mine;
				{
				FilterSamePlayer002AA4B0 filterPlayer(player);
				PartitionFilterAcceptByKindOf filterKind(
					KindOfMaskType(KindOfMaskType::kInit, 54), KINDOFMASK_NONE);
				PartitionFilter *filters = filterKind.link(&filterPlayer);
				mine = ThePartitionManager->getClosestObject(
					&pos, data->m_fleeRangeAfterCompletion, 0, filters);
				}
				if (mine)
				{
					dir.x = pos.x - mine->getPosition()->x;
					dir.y = pos.y - mine->getPosition()->y;
					dir.z = 0;
					dir.normalize();
					dir.scale(data->m_fleeRangeAfterCompletion);
					pos = *mine->getPosition();
					pos.add(&dir);
				}
			}
			}
			ai->getCommandInterface()->aiMoveToPosition(&pos, CMD_FROM_AI);
			Object *target = TheGameLogic->findObjectByID(m_targetID);
			if (target) ai->ignoreObstacle(target);
		}
	}
	else
	{
		AIUpdateInterface *ai = m_object->getAI();
		if (ai) ai->getCommandInterface()->aiIdle(CMD_FROM_AI);
	}
	onExit(false, false);
}
