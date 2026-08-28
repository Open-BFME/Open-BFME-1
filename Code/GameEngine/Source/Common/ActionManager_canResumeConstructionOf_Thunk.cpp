// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?canResumeConstructionOf@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z: Code/GameEngine/Source/Common/RTS/ActionManager.cpp
// Lift ActionManager::canResumeConstructionOf to clean C++.
//
// Zero Hour's shape: reject null objects, require the actor to be the right kind,
// require an allied relationship, require the target to be under construction,
// then check the actor is the one that was building it.
//
// The bytes fix the constants Zero Hour leaves symbolic. The kind is 0x0E. The
// relationship compares against 2, so ALLIES is 2 in this enum. The
// under-construction flag is bit 2 of the byte at Object+0x90, and bit 0 of the
// byte at Object+0x344 disqualifies the actor. The builder identity read from
// the target is compared against Object+0x74 of the actor, and a zero there
// passes -- an unbuilt target is resumable by anyone.
//
// The third parameter is never read; retail still pops it, which is how the
// three-argument name and `ret 0xC` agree.

typedef bool Bool;
typedef int Int;

enum KindOfType
{
	KINDOF_UNRECONSTRUCTED_0E = 0x0E
};

enum Relationship
{
	ALLIES = 2
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;					///< ILT thunk at 0x0003251F
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Relationship getRelationship(const Object *that) const;	///< ILT thunk at 0x0004A719

	/// address-derived name -- do not treat as an identity. Returns the value
	/// compared against the actor's field at +0x74.
	Int unidentified_000029D7(void) const;					///< ILT thunk at 0x000029D7

	unsigned char m_unreconstructed_00[0x74];
	Int m_id74;												///< retail this+0x74
	unsigned char m_unreconstructed_78[0x90 - 0x78];
	unsigned char m_status90;								///< retail this+0x90
	unsigned char m_unreconstructed_91[0x344 - 0x91];
	unsigned char m_flags344;								///< retail this+0x344
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ActionManager.h
class ActionManager
{
public:
	Bool canResumeConstructionOf(const Object *, const Object *, CommandSourceType);
};

// ?canResumeConstructionOf@ActionManager@@QAE_NPBVObject@@0W4CommandSourceType@@@Z
Bool ActionManager::canResumeConstructionOf(const Object *obj, const Object *objectToResume,
	CommandSourceType commandSource)
{
	// One condition, not a ladder of early returns: retail pushes both callee-saved
	// registers in the prologue and jumps every failure to a single shared epilogue.
	// Separate `return false` statements let MSVC shrink-wrap the second push, which
	// makes the exits differ and stops it merging them.
	if (obj != 0
		&& objectToResume != 0
		&& obj->isKindOf(KINDOF_UNRECONSTRUCTED_0E)
		&& obj->getRelationship(objectToResume) == ALLIES
		&& (objectToResume->m_status90 & 4) != 0
		&& (obj->m_flags344 & 1) == 0)
	{
		Int builder = objectToResume->unidentified_000029D7();
		if (builder == 0 || builder == obj->m_id74)
			return true;
	}

	return false;
}
