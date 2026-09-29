// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: SpecialAbilityUpdate::finishAbility, retail 0x002AA4B0, 734 bytes.
// Identity: SpecialAbilityUpdate vtable 0x010C37B8 slot 17; update() at 0x002AA9D0 calls slot 17 at Zero Hour's finishAbility sites.
#include <bitset>
#include "basetype.h"
#include "../../command_source_type.h"

class Player;
class Object;
class PartitionFilter;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
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
private:
	_STL::bitset<N> m_bits;
};
typedef BitFlags<192> KindOfMaskType;
extern const KindOfMaskType KINDOFMASK_NONE;

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual bool allow(Object *) = 0;
	virtual Int getPlayerMask();
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterSamePlayer : public PartitionFilter
{
public:
	PartitionFilterSamePlayer(const Player *player) : m_player(player) {}
	virtual bool allow(Object *);
private:
	const Player *m_player;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &, const KindOfMaskType &);
	virtual bool allow(Object *);
private:
	KindOfMaskType m_set;
	KindOfMaskType m_clear;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *, Real, Int, PartitionFilter *);
};
extern PartitionManager *ThePartitionManager;

struct SpecialAbilityUpdateModuleData
{
	char m_pad_000[0x1F8];
	Real m_fleeRangeAfterCompletion;
	char m_pad_1FC[0x244 - 0x1FC];
	Bool m_flipObjectAfterPacking;
	Bool m_flipObjectAfterUnpacking;
};

class SpecialAbilityUpdate
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
	void finishAbility();
private:
	SpecialAbilityUpdateModuleData *m_data;
	Object *m_object;
	char m_pad_00c[0x30 - 0x0C];
	Int m_packingState;
	char m_pad_034[0xAC - 0x34];
	Int m_targetID;
	Coord3D m_targetPos;
	char m_pad_0bc[0xE2 - 0xBC];
	Bool m_withinStartAbilityRange;
};


// ?finishAbility@SpecialAbilityUpdate@@QAEXXZ
void SpecialAbilityUpdate::finishAbility()
{
	SpecialAbilityUpdateModuleData *data = m_data;
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
			{
			Coord3D dir = *m_object->getUnitDirectionVector2D();
			dir.normalize();
			dir.scale(data->m_fleeRangeAfterCompletion);
			if (data->m_flipObjectAfterUnpacking || data->m_flipObjectAfterPacking)
				pos.add(&dir);
			else
				pos.sub(&dir);
			}
			Object *obj = m_object;
			if (obj)
			{
			Player *player = obj->getControllingPlayer();
			if (player)
			{
				Object *mine = ThePartitionManager->getClosestObject(
					&pos, data->m_fleeRangeAfterCompletion, 0,
					PartitionFilterAcceptByKindOf(
						KindOfMaskType(KindOfMaskType::kInit, 54), KINDOFMASK_NONE).link(&PartitionFilterSamePlayer(player)));
				if (mine)
				{
					Coord3D dir;
					dir.set(pos.x - mine->getPosition()->x, pos.y - mine->getPosition()->y, 0);
					dir.normalize();
					dir.scale(data->m_fleeRangeAfterCompletion);
					pos = *mine->getPosition();
					pos.add(&dir);
				}
			}
			}
			Object *target = TheGameLogic->findObjectByID(m_targetID);
			if (target) ai->ignoreObstacle(target);
			ai->getCommandInterface()->aiMoveToPosition(&pos, CMD_FROM_AI);
		}
	}
	else
	{
		AIUpdateInterface *ai = m_object->getAI();
		if (ai) ai->getCommandInterface()->aiIdle(CMD_FROM_AI);
	}
	onExit(false, false);
}
