// cl: /DNDEBUG /MD /EHsc

// The six small Object queries about damage taken and weapons carried:
//
//   bfmeGetLastDamagePlayerIndex     0x001BF060  who hit us last
//   bfmeGetRecentDamageSource        0x001BFF70  and was it recent
//   bfmeDamageSourceCanCauseCower    0x001C5D00  is that attacker frightening
//   bfmeGetCurrentVictimIfAttacking  0x001BE070  who are we hitting
//   bfmeHasActiveOrRecentlyActiveWeapon 0x001BFE80  are we still shooting
//   bfmeGetLastShotPosition          0x001BF970  and from where
//
// Six files, six private Objects. Put together they name five consecutive module
// pointers that no single file could see:
//
//   +0x1EC  m_firingTracker   the two weapon bodies
//   +0x1FC  m_contain         bfmeGetRecentDamageSource
//   +0x200  m_body            two of the damage bodies, agreeing
//   +0x204  m_ai              two more, agreeing
//   +0x26C  m_weapons[4], +0x27C m_currentWeaponSlot, +0x284 the template set
//
// +0x27C is the same m_curWeaponSlot ObjectModelConditions.cpp reads, and +0x204
// the same m_ai it calls the state-machine notify on, so those two cross-check.
//
// The interfaces had been declared to whatever depth each file needed, and are
// now declared once to the deepest:
//
//   BodyModuleInterface     slot 15 getLastDamageInfo and slot 16
//                           getLastDamageTimestamp, one file each
//   AIUpdateInterface       slot 97 isAttacking and slot 131 bfmeCanCauseCower,
//                           one file each
//   DamageInfo              m_sourceID at +0x08 named by one and padded over by
//                           the other, which named m_sourcePlayerMask at +0x0C
//
// And ContainModuleInterface's slot 26 turns up for the fifth time in this tree.
// bfmeGetRecentDamageSource called it getDamageRedirect and used the result at
// slot 35; ObjectContainQueries.cpp has three bodies using it at slots 42, 84 and
// 108, and ObjectTeamAndPlayer.cpp has a fourth returning it outright. One
// virtual has one return type, so those are five views of ONE interface, and slot
// 35 joins the list on the HordeContainInterface named here.
//
// Which interface that is has since been settled from the image; the chain is in
// ObjectTeamAndPlayer.cpp. Slot 26 is a self-cast to a second interface on the
// same contain module (HordeContain+0xE4, vtable 0x010AE8E0, at least 129
// entries), so it is neither a Player nor an Object -- Object's own vtable has 28
// slots. The name below stays a reconstruction and stays out of the rows.
//
// Two spellings below are frozen by names that have to resolve, not chosen:
//
//   BfmeFiringTracker  ?bfmeGetLastShotPosition@BfmeFiringTracker@@... is the pin
//                      for the +0x48 getter; the member itself stays
//                      FiringTracker, which is what names +0x44, and the one call
//                      site casts. Same object at Object+0x1EC either way.
//   ObjectID           ?bfmeGetRecentDamageSource@Object@@QBE_NPAII@Z says
//                      unsigned, ?bfmeDamageSourceCanCauseCower@Object@@QBE_NH@Z
//                      says signed, and so does the findObjectByID pin that body
//                      calls. Both rows are matched, so the two spellings both
//                      stay and the disagreement is theirs, not this file's.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;
typedef unsigned short PlayerMaskType;

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfoInput
{
	void *m_snapshotVtable;
	ObjectID m_sourceID;				// DamageInfo +0x08
	PlayerMaskType m_sourcePlayerMask;		// DamageInfo +0x0C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	void *m_snapshotVtable;
	DamageInfoInput in;
};

#define BFME_SLOT(n) virtual Int bfmeSlot##n() = 0

// The one interface ContainModuleInterface's slot 26 hands back; see the note
// above and ObjectContainQueries.cpp, which names the same class.
class HordeContainInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25); BFME_SLOT(26); BFME_SLOT(27); BFME_SLOT(28); BFME_SLOT(29);
	BFME_SLOT(30); BFME_SLOT(31); BFME_SLOT(32); BFME_SLOT(33); BFME_SLOT(34);
	// slot 35, +0x8C
	virtual Bool getRecentDamageSource(ObjectID *sourceID, UnsignedInt frames) const = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ContainModule.h
class ContainModuleInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	BFME_SLOT(15); BFME_SLOT(16); BFME_SLOT(17); BFME_SLOT(18); BFME_SLOT(19);
	BFME_SLOT(20); BFME_SLOT(21); BFME_SLOT(22); BFME_SLOT(23); BFME_SLOT(24);
	BFME_SLOT(25);
	// slot 26, +0x68
	virtual HordeContainInterface *getHordeContainInterface() const = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	BFME_SLOT(00); BFME_SLOT(01); BFME_SLOT(02); BFME_SLOT(03); BFME_SLOT(04);
	BFME_SLOT(05); BFME_SLOT(06); BFME_SLOT(07); BFME_SLOT(08); BFME_SLOT(09);
	BFME_SLOT(10); BFME_SLOT(11); BFME_SLOT(12); BFME_SLOT(13); BFME_SLOT(14);
	// slot 15, +0x3C
	virtual const DamageInfo *getLastDamageInfo() const = 0;
	// slot 16, +0x40
	virtual UnsignedInt getLastDamageTimestamp() const = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	BFME_SLOT(000); BFME_SLOT(001); BFME_SLOT(002); BFME_SLOT(003); BFME_SLOT(004);
	BFME_SLOT(005); BFME_SLOT(006); BFME_SLOT(007); BFME_SLOT(008); BFME_SLOT(009);
	BFME_SLOT(010); BFME_SLOT(011); BFME_SLOT(012); BFME_SLOT(013); BFME_SLOT(014);
	BFME_SLOT(015); BFME_SLOT(016); BFME_SLOT(017); BFME_SLOT(018); BFME_SLOT(019);
	BFME_SLOT(020); BFME_SLOT(021); BFME_SLOT(022); BFME_SLOT(023); BFME_SLOT(024);
	BFME_SLOT(025); BFME_SLOT(026); BFME_SLOT(027); BFME_SLOT(028); BFME_SLOT(029);
	BFME_SLOT(030); BFME_SLOT(031); BFME_SLOT(032); BFME_SLOT(033); BFME_SLOT(034);
	BFME_SLOT(035); BFME_SLOT(036); BFME_SLOT(037); BFME_SLOT(038); BFME_SLOT(039);
	BFME_SLOT(040); BFME_SLOT(041); BFME_SLOT(042); BFME_SLOT(043); BFME_SLOT(044);
	BFME_SLOT(045); BFME_SLOT(046); BFME_SLOT(047); BFME_SLOT(048); BFME_SLOT(049);
	BFME_SLOT(050); BFME_SLOT(051); BFME_SLOT(052); BFME_SLOT(053); BFME_SLOT(054);
	BFME_SLOT(055); BFME_SLOT(056); BFME_SLOT(057); BFME_SLOT(058); BFME_SLOT(059);
	BFME_SLOT(060); BFME_SLOT(061); BFME_SLOT(062); BFME_SLOT(063); BFME_SLOT(064);
	BFME_SLOT(065); BFME_SLOT(066); BFME_SLOT(067); BFME_SLOT(068); BFME_SLOT(069);
	BFME_SLOT(070); BFME_SLOT(071); BFME_SLOT(072); BFME_SLOT(073); BFME_SLOT(074);
	BFME_SLOT(075); BFME_SLOT(076); BFME_SLOT(077); BFME_SLOT(078); BFME_SLOT(079);
	BFME_SLOT(080); BFME_SLOT(081); BFME_SLOT(082); BFME_SLOT(083); BFME_SLOT(084);
	BFME_SLOT(085); BFME_SLOT(086); BFME_SLOT(087); BFME_SLOT(088); BFME_SLOT(089);
	BFME_SLOT(090); BFME_SLOT(091); BFME_SLOT(092); BFME_SLOT(093); BFME_SLOT(094);
	BFME_SLOT(095);
	// slot 96, +0x180, is isIdle; isAttacking is declared right after it upstream.
	BFME_SLOT(096);
	// slot 97, +0x184
	virtual Bool isAttacking() const = 0;
	BFME_SLOT(098); BFME_SLOT(099);
	BFME_SLOT(100); BFME_SLOT(101); BFME_SLOT(102); BFME_SLOT(103); BFME_SLOT(104);
	BFME_SLOT(105); BFME_SLOT(106); BFME_SLOT(107); BFME_SLOT(108); BFME_SLOT(109);
	BFME_SLOT(110); BFME_SLOT(111); BFME_SLOT(112); BFME_SLOT(113); BFME_SLOT(114);
	BFME_SLOT(115); BFME_SLOT(116); BFME_SLOT(117); BFME_SLOT(118); BFME_SLOT(119);
	BFME_SLOT(120); BFME_SLOT(121); BFME_SLOT(122); BFME_SLOT(123); BFME_SLOT(124);
	BFME_SLOT(125); BFME_SLOT(126); BFME_SLOT(127); BFME_SLOT(128); BFME_SLOT(129);
	BFME_SLOT(130);
	// slot 131, +0x20C.  It defaults true; GiantBirdAI overrides it false, which
	// is what identifies it as the can-cause-cower test.
	virtual Bool bfmeCanCauseCower() const = 0;

	Object *getCurrentVictim() const;
};

#undef BFME_SLOT

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_unmodelled_000[0x24];
	Int m_playerIndex;				// +0x24
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

extern PlayerList *ThePlayerList;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	// Signed here because that is the spelling the matched findObjectByID pin
	// (?findObjectByID@GameLogic@@QAEPAVObject@@H@Z) carries.
	Object *findObjectByID(Int id);

	unsigned char m_unmodelled_000[0x3c];
	UnsignedInt m_frame;				// +0x3C
};

extern GameLogic *TheGameLogic;

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
friend class Object;

private:
	WeaponStatus bfmeComputeStatus(Bool *unknown) const;
};

// The Object+0x1EC tracker, under the spelling its last-shot getter is pinned as.
class BfmeFiringTracker;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/FiringTracker.h
class FiringTracker
{
public:
	unsigned char m_unmodelled_000[0x44];
	UnsignedInt m_recentActivityFrame;		// +0x44
};

// The last-shot position is three floats at FiringTracker+0x48. The words are
// copied as integers because retail moves them through the general registers, not
// the x87 stack.
union BfmeFiringPositionWord
{
	float f;
	volatile unsigned int u;
};

struct BfmeFiringPosition
{
	BfmeFiringPosition() {}
	BfmeFiringPosition(const BfmeFiringPosition &other)
	{
		x.u = other.x.u;
		y.u = other.y.u;
		z.u = other.z.u;
	}
	BfmeFiringPositionWord x;
	BfmeFiringPositionWord y;
	BfmeFiringPositionWord z;
};

class BfmeFiringTracker
{
public:
	BfmeFiringPosition bfmeGetLastShotPosition() const;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Int bfmeGetLastDamagePlayerIndex() const;
	Bool bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt seconds) const;
	Bool bfmeDamageSourceCanCauseCower(Int sourceID) const;
	Object *bfmeGetCurrentVictimIfAttacking() const;
	Bool bfmeHasActiveOrRecentlyActiveWeapon() const;
	BfmeFiringPosition bfmeGetLastShotPosition() const;

	AIUpdateInterface *getAIUpdateInterface() const { return m_ai; }

private:
	unsigned char m_unmodelled_000[0x1ec];
	FiringTracker *m_firingTracker;			// +0x1EC
	unsigned char m_unmodelled_1f0[0x1fc - 0x1f0];
	ContainModuleInterface *m_contain;		// +0x1FC
	BodyModuleInterface *m_body;			// +0x200
	AIUpdateInterface *m_ai;			// +0x204
	unsigned char m_unmodelled_208[0x26c - 0x208];
	Weapon *m_weapons[4];				// +0x26C
	Int m_currentWeaponSlot;			// +0x27C
	unsigned char m_unmodelled_280[4];
	void *m_currentWeaponTemplateSet;		// +0x284
};

// ?bfmeGetLastDamagePlayerIndex@Object@@QBEHXZ
//
// Any missing body, damage record, mask or player answers zero.
// SlowDeathBehavior::beginSlowDeath is the only named caller, and it does not
// expose this wrapper's retail spelling; the bfme prefix is descriptive.
Int Object::bfmeGetLastDamagePlayerIndex() const
{
	BodyModuleInterface *body = m_body;
	if (body != 0)
	{
		const DamageInfo *info = body->getLastDamageInfo();
		if (info != 0 && info->in.m_sourcePlayerMask != 0)
		{
			Player *player = ThePlayerList->getPlayerFromMask(info->in.m_sourcePlayerMask);
			if (player != 0)
				return player->getPlayerIndex();
		}
	}
	return 0;
}

// ?bfmeGetRecentDamageSource@Object@@QBE_NPAII@Z
//
// A horde answers for its members; otherwise the body's own timestamp decides,
// with seconds converted at BFME's five logic frames per second.
Bool Object::bfmeGetRecentDamageSource(ObjectID *sourceID, UnsignedInt seconds) const
{
	ContainModuleInterface *contain = m_contain;
	const UnsignedInt frames = seconds * 5;
	if (contain)
	{
		HordeContainInterface *horde = contain->getHordeContainInterface();
		if (horde)
			return horde->getRecentDamageSource(sourceID, frames);
	}

	BodyModuleInterface *body = m_body;
	if (body)
	{
		const UnsignedInt lastDamageFrame = body->getLastDamageTimestamp();
		if (lastDamageFrame != static_cast<UnsignedInt>(-1) &&
			lastDamageFrame + frames >= TheGameLogic->m_frame)
		{
			const DamageInfo *info = body->getLastDamageInfo();
			if (info)
				*sourceID = info->in.m_sourceID;
			return true;
		}
	}

	return false;
}

// ?bfmeDamageSourceCanCauseCower@Object@@QBE_NH@Z
//
// AICowerState::update passes the recent damage source here.
Bool Object::bfmeDamageSourceCanCauseCower(Int sourceID) const
{
	Object *source = TheGameLogic->findObjectByID(sourceID);
	if (source == 0)
		return false;
	AIUpdateInterface *ai = source->getAIUpdateInterface();
	if (ai == 0)
		return false;
	return ai->bfmeCanCauseCower();
}

// ?bfmeGetCurrentVictimIfAttacking@Object@@QBEPAV1@XZ
//
// No named caller exposes this wrapper's retail spelling; the bfme prefix is
// descriptive, and const records observed query-only behaviour rather than symbol
// metadata.
Object *Object::bfmeGetCurrentVictimIfAttacking() const
{
	AIUpdateInterface *ai = m_ai;
	Object *victim = 0;
	if (ai != 0 && ai->isAttacking())
		victim = m_ai->getCurrentVictim();
	return victim;
}

// ?bfmeHasActiveOrRecentlyActiveWeapon@Object@@QBE_NXZ
Bool Object::bfmeHasActiveOrRecentlyActiveWeapon() const
{
	if (m_currentWeaponTemplateSet)
	{
		Weapon *weapon = m_weapons[m_currentWeaponSlot];
		if (weapon)
		{
			if (weapon->bfmeComputeStatus(0) != READY_TO_FIRE)
				return true;

			FiringTracker *tracker = m_firingTracker;
			if (tracker)
			{
				UnsignedInt recentFrame = tracker->m_recentActivityFrame;
				if (recentFrame > 2 && recentFrame + 10 > TheGameLogic->m_frame)
					return true;
			}
		}
	}
	return false;
}

// ?bfmeGetLastShotPosition@Object@@QBE?AUBfmeFiringPosition@@XZ
BfmeFiringPosition Object::bfmeGetLastShotPosition() const
{
	volatile float scratch = 0.0f;
	BfmeFiringPosition empty;
	empty.x.f = 0.0f;
	empty.y.f = 0.0f;
	empty.z.f = 0.0f;
	return m_firingTracker
		? reinterpret_cast<const BfmeFiringTracker *>(m_firingTracker)->bfmeGetLastShotPosition()
		: empty;
}
