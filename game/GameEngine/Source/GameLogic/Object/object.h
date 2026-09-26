// object.h -- BFME's Object layout, one definition instead of a thousand.
//
// Evidence and method: docs/object_layout.md. Briefly:
//  * Shape from the retail image: Object : Thing (primary, +0x00..+0x5F); four
//    more base subobjects whose vfptrs sit at +0x60/+0x64/+0x6C/+0x70, a vbptr
//    at +0x68, and a virtual base at +0x3C0 (??0Object at 0x001D29A0).
//  * Members from tools/layout_census.py: each one below is placed by at least
//    two byte-verified TU-local copies, or by one copy plus name_oracle at
//    confidence >= 0.9. Everything else is opaque storage named by offset.
//  * Virtual slots are named only where an existing pin for that very body
//    uses Object's virtual mangling; the rest carry their slot and body address.
//
// Nothing has to be included first (see thing.h). Members typed elsewhere:
//   m_id, m_producerID, m_builderID  ObjectID when the TU defines BFME_HAVE_OBJECTID,
//                                    else Int (MSVC's representation of the enum)
//   m_name, m_originalTeamName       AsciiString when the TU defines BFME_HAVE_ASCIISTRING,
//                                    else its one pointer
//   m_modelConditionFlags            ModelConditionFlags (40 bytes, BitFlags<320>) when the
//                                    TU defines BFME_HAVE_MODELCONDITIONFLAGS, else ten words
//
// The +0x60..+0x73 words and the +0x3BC/+0x3C0 words are compiler state in
// retail (other bases, vbptr, vtordisp, virtual base). This header does not
// model those bases, so it keeps their bytes as opaque members and never
// constructs, destroys or up-casts an Object. Object.cpp still defines those.
//
// Non-virtual members belong to the TU until their signatures are settled
// (several pinned names have competing spellings): define OBJECT_TU_MEMBERS to
// the declarations a TU needs, before including. Member functions only --
// a data member there is a layout change these checks cannot see. Redeclaring
// an inherited virtual there overrides it without adding a slot.

#ifndef BFME_OBJECT_H
#define BFME_OBJECT_H

#include "../../Common/Thing/thing.h"

class Drawable;
class Team;
class FiringTracker;
class BehaviorModule;
class ContainModuleInterface;
class BodyModuleInterface;
class AIUpdateInterface;
class PhysicsBehavior;
class RadarObject;
class ExperienceTracker;
class PartitionData;

class Object : public Thing
{
	// Primary vftable 0x00C9EE58: Thing's slots 0-7, then these, in order.
public:
	virtual void objectSlot08_001C6870();				// slot 8
	virtual void onDestroy();							// slot 9: ?onDestroy@Object@@UAEXXZ
	virtual Drawable *getDrawable() const;				// slot 10: ?getDrawable@Object@@UBEPAVDrawable@@XZ
	virtual void objectSlot11_001CD990();				// slot 11: pinned as a fireCurrentWeapon
	virtual void objectSlot12_001BE680();				// slot 12: reactToTurretChange(WhichTurretType, Real, Real)
	virtual void objectSlot13_001D4810();				// slot 13: an attemptDamage
	virtual void objectSlot14_001D0490();				// slot 14: an attemptDamage
	virtual void updatePendingDamage();					// slot 15: ?updatePendingDamage@Object@@UAEXXZ
	virtual void objectSlot16_001C3080();				// slot 16: pinned as attemptHealing (non-virtual spelling)
	virtual void objectSlot17_001CE240();				// slot 17
	virtual void objectSlot18_001CBC20();				// slot 18
	virtual void objectSlot19_001C4670();				// slot 19: pinned as restoreOriginalTeam (non-virtual spelling)
	virtual void setTeam(Team *team);					// slot 20: ?setTeam@Object@@UAEXPAVTeam@@@Z
	virtual void objectSlot21_001D5D90();				// slot 21: pinned as setTemporaryTeam (non-virtual spelling)
	virtual void objectSlot22_001CBD70();				// slot 22
	virtual void objectSlot23_001C6E00();				// slot 23
	virtual void objectSlot24_001BE0C0();				// slot 24
	virtual void objectSlot25_001BE070();				// slot 25
	virtual void rva001cff30(Object *other);			// slot 26: ?rva001cff30@Object@@UAEXPAV1@@Z
	virtual void objectSlot27_001C5C00();				// slot 27
protected:
	virtual ~Object();									// slot 7: ??_GObject@@MAEPAXI@Z 0x001D5CF0

public:
	void *m_secondaryVfptr060;							// +0x60 compiler: base subobject vfptr
	void *m_secondaryVfptr064;							// +0x64 compiler: base subobject vfptr
	void *m_vbptr068;									// +0x68 compiler: vbptr, vbtable 0x00C9EEE0
	void *m_secondaryVfptr06C;							// +0x6C compiler: base subobject vfptr
	void *m_secondaryVfptr070;							// +0x70 compiler: base subobject vfptr
#ifdef BFME_HAVE_OBJECTID
	ObjectID m_id;										// +0x74
	ObjectID m_producerID;								// +0x78
	ObjectID m_builderID;								// +0x7C
#else
	Int m_id;											// +0x74 define BFME_HAVE_OBJECTID for the enum
	Int m_producerID;									// +0x78
	Int m_builderID;									// +0x7C
#endif
	Drawable *m_drawable;								// +0x80
#ifdef BFME_HAVE_ASCIISTRING
	AsciiString m_name;									// +0x84
#else
	void *m_name;										// +0x84 define BFME_HAVE_ASCIISTRING for the real type
#endif
	Object *m_next;										// +0x88
	Object *m_prev;										// +0x8C
	UnsignedInt m_status[3];							// +0x90 status bit set, three words
	UnsignedByte m_unmodelled09C[0x10];					// +0x9C
	UnsignedInt m_geometryInfo[23];						// +0xAC GeometryInfo, 92 bytes; BFME's layout is not geometry.h's
	UnsignedByte m_unmodelled108[0x8];					// +0x108
#ifdef BFME_HAVE_MODELCONDITIONFLAGS
	ModelConditionFlags m_modelConditionFlags;			// +0x110
#else
	UnsignedInt m_modelConditionFlags[10];				// +0x110 model-condition bit set, BitFlags<320>
#endif
	UnsignedByte m_unmodelled138[0x6C];					// +0x138
	UnsignedInt m_disabledMask;							// +0x1A4
	UnsignedInt m_disabledTillFrame[11];				// +0x1A8 [DISABLED_COUNT]
	UnsignedByte m_unmodelled1D4[0x18];					// +0x1D4
	FiringTracker *m_firingTracker;						// +0x1EC
	BehaviorModule **m_behaviors;						// +0x1F0
	UnsignedByte m_unmodelled1F4[0x8];					// +0x1F4
	ContainModuleInterface *m_contain;					// +0x1FC
	BodyModuleInterface *m_body;						// +0x200
	AIUpdateInterface *m_ai;							// +0x204
	PhysicsBehavior *m_physics;							// +0x208
	RadarObject *m_radarData;							// +0x20C
	ExperienceTracker *m_experienceTracker;				// +0x210
	Object *m_containedBy;								// +0x214
	UnsignedByte m_unmodelled218[0x4];					// +0x218
	UnsignedInt m_containedByFrame;						// +0x21C
	Real m_constructionPercent;							// +0x220
	UnsignedInt m_objectUpgradesCompleted[6];			// +0x224 upgrade bit set, six words
	Team *m_team;										// +0x23C
#ifdef BFME_HAVE_ASCIISTRING
	AsciiString m_originalTeamName;						// +0x240
#else
	void *m_originalTeamName;							// +0x240
#endif
	Int m_indicatorColor;								// +0x244
	UnsignedByte m_unmodelled248[0x58];					// +0x248 m_weaponSet starts at +0x264; its extent is unproven
	UnsignedInt m_weaponBonusCondition;					// +0x2A0
	UnsignedByte m_unmodelled2A4[0x9F];					// +0x2A4
	UnsignedByte m_scriptStatus;						// +0x343
	UnsignedByte m_privateStatus;						// +0x344
	UnsignedByte m_unmodelled345[0x6B];					// +0x345
	PartitionData *m_partitionData;						// +0x3B0
	UnsignedByte m_unmodelled3B4[0x8];					// +0x3B4
	UnsignedInt m_vtordisp3BC;							// +0x3BC compiler: vtordisp for the virtual base
	void *m_virtualBaseVfptr3C0;						// +0x3C0 compiler: virtual base vfptr

#ifdef OBJECT_TU_MEMBERS
public:
	OBJECT_TU_MEMBERS
#endif
};

BFME_LAYOUT_CHECK(Object, m_secondaryVfptr060, 0x60);
BFME_LAYOUT_CHECK(Object, m_id, 0x74);
BFME_LAYOUT_CHECK(Object, m_drawable, 0x80);
BFME_LAYOUT_CHECK(Object, m_name, 0x84);
BFME_LAYOUT_CHECK(Object, m_next, 0x88);
BFME_LAYOUT_CHECK(Object, m_status, 0x90);
BFME_LAYOUT_CHECK(Object, m_geometryInfo, 0xAC);
BFME_LAYOUT_CHECK(Object, m_modelConditionFlags, 0x110);
BFME_LAYOUT_CHECK(Object, m_disabledMask, 0x1A4);
BFME_LAYOUT_CHECK(Object, m_firingTracker, 0x1EC);
BFME_LAYOUT_CHECK(Object, m_behaviors, 0x1F0);
BFME_LAYOUT_CHECK(Object, m_contain, 0x1FC);
BFME_LAYOUT_CHECK(Object, m_ai, 0x204);
BFME_LAYOUT_CHECK(Object, m_containedBy, 0x214);
BFME_LAYOUT_CHECK(Object, m_objectUpgradesCompleted, 0x224);
BFME_LAYOUT_CHECK(Object, m_team, 0x23C);
BFME_LAYOUT_CHECK(Object, m_originalTeamName, 0x240);
BFME_LAYOUT_CHECK(Object, m_weaponBonusCondition, 0x2A0);
BFME_LAYOUT_CHECK(Object, m_scriptStatus, 0x343);
BFME_LAYOUT_CHECK(Object, m_privateStatus, 0x344);
BFME_LAYOUT_CHECK(Object, m_partitionData, 0x3B0);
BFME_LAYOUT_CHECK(Object, m_virtualBaseVfptr3C0, 0x3C0);
typedef char Object_size_is_not_0x3C4[sizeof(Object) == 0x3C4 ? 1 : -1];

#endif // BFME_OBJECT_H
