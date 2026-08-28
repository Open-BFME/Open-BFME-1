// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PartitionFilterPossibleToAttack@@QAE@W4AbleToAttackType@@PBVObject@@W4CommandSourceType@@@Z: Code/GameEngine/Source/GameLogic/Object/PartitionManager.cpp
// Open-BFME5: partition filter bodies whose member offsets PartitionManager.cpp
// cannot reproduce -- PartitionFilterIrregularArea::allow,
// PartitionFilterPlayer::allow, and PartitionFilterPossibleToAttack's
// constructor.
//
// All three are the Zero Hour source unchanged; only the layout differs, and
// the three of them together say the layout differs PER FILTER, not once in the
// shared base:
//
//   PartitionFilterPossibleToAttack  ctor writes +0x04, +0x08, +0x0c
//   PartitionFilterPlayer            allow reads  +0x08, +0x0c
//   PartitionFilterPlayerAffiliation allow reads  +0x08, +0x0c, +0x10
//
// ZH's PartitionFilter contributes only a vtable pointer, so the first member
// should land at +0x04 -- which is exactly what PossibleToAttack does. So the
// base is NOT four bytes wider in BFME; the two that start at +0x08 each carry
// something of their own ahead of the members ZH declares. Widening
// PartitionFilter to explain them would break this constructor.
//
// Spelled locally rather than fixed in PartitionManager.cpp, which would move
// every one of its 74 matched rows, the same way
// PartitionFilterPlayerAffiliation_allow_Thunk.cpp already does.

struct Coord3D;
class Player;

// Only needed so the constructor below mangles as retail does; no value in
// either is read by any body here.
enum AbleToAttackType { ATTACK_TYPE_UNRECONSTRUCTED };
enum CommandSourceType { COMMAND_SOURCE_UNRECONSTRUCTED };

bool PointInsideArea2D(const Coord3D *pt, const Coord3D *area, int numPoints);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	// Thing::getPosition() is inlined at both call sites as &m_cachedPos;
	// retail reaches it with `add edx,0x38`.
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)(m_unreconstructed_00 + 0x38);
	}

	Player *getControllingPlayer(void) const;			///< pinned at 0x00020824

private:
	unsigned char m_unreconstructed_00[0x38];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterIrregularArea
{
protected:
	virtual bool allow(Object *);

private:
	unsigned char m_unreconstructed_04[0x08 - 4];		///< vtable slot then unpinned base bytes
	const Coord3D *m_area;								///< retail this+0x08
	int m_numPointsInArea;								///< retail this+0x0C
};

// Members land at +0x04 with nothing between them and the vtable pointer --
// this is the filter that shows the shared base is a bare vptr.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterPossibleToAttack
{
public:
	PartitionFilterPossibleToAttack(AbleToAttackType attackType, const Object *source,
		CommandSourceType commandSource);

protected:
	virtual bool allow(Object *);

private:
	AbleToAttackType m_attackType;						///< retail this+0x04
	const Object *m_source;								///< retail this+0x08
	CommandSourceType m_commandSource;					///< retail this+0x0c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionFilterPlayer
{
protected:
	virtual bool allow(Object *);

private:
	unsigned char m_unreconstructed_04[0x08 - 4];		///< vtable slot then unpinned base bytes
	const Player *m_player;								///< retail this+0x08
	bool m_match;										///< retail this+0x0C
};

// ?allow@PartitionFilterIrregularArea@@MAE_NPAVObject@@@Z
bool PartitionFilterIrregularArea::allow(Object *other)
{

	return PointInsideArea2D(other->getPosition(), m_area, m_numPointsInArea);
}

// ?allow@PartitionFilterPlayer@@MAE_NPAVObject@@@Z
bool PartitionFilterPlayer::allow(Object *other)
{
	return ((m_player == other->getControllingPlayer()) == m_match);
}

// ??0PartitionFilterPossibleToAttack@@QAE@W4AbleToAttackType@@PBVObject@@W4CommandSourceType@@@Z
PartitionFilterPossibleToAttack::PartitionFilterPossibleToAttack(
	AbleToAttackType attackType, const Object *source, CommandSourceType commandSource) :
	m_attackType(attackType),
	m_source(source),
	m_commandSource(commandSource)
{
}
