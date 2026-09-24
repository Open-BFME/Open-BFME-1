// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: identity established by the already-landed sibling call at
// 0x002459D0 (Rva002459D0HordeMemberAdd.cpp), whose own matched-row notes
// say "The 0x00245B20 caller supplies Object member-ID storage and index
// arguments" -- this is that caller. This object's field 0x08 (an owner
// Object*) and field 0x1BC (reused here as scratch Int storage) match the
// BfmeHordeContainOwner layout proven by
// HordeContainTryScheduleReformation.cpp (retail 0x0023F9A0), whose
// m_owner sits at +8 and m_pendingRefresh at +0x1BC in the same class
// family. TheExperienceLevelSystem (0x012F0888) and the landed
// gainExpForLevel@ExperienceTracker / gainLevels@ExperienceLevelSystem
// calls pin the veterancy-sync behaviour; ExperienceTracker::m_scalarIndex
// (+0x28, vtable-adjusted from ExperienceTrackerProgression.cpp's ctor
// layout) is the value diffed between the owner and the new member. The
// public method name is not proven, so it stays address-qualified.

typedef int Int;
typedef bool Bool;

class Object;

// still-dump helper at 0x0023CDD0, reached through retail thunk 0x0003087D
// (pinned in reverse/symbols.csv at the ILT address the call site targets)
class Rva0023CDD0Owner
{
public:
	Int rva0023cdd0( Int p2, Int *outFlag );
};

// landed: Code/GameEngine/Source/GameLogic/Object/Contain/Rva002459D0HordeMemberAdd.cpp
class Rva002459D0Owner
{
public:
	void rva002459d0( Object *member, Int *memberID, Int index );
};

struct BfmeArg1002;
struct BfmeX1002;

// pinned reverse/symbols.csv: ?bfmeFind1002@BfmeA1002@@QAEPAUBfmeX1002@@PAUBfmeArg1002@@@Z @ 0x0003F5DA
class BfmeA1002
{
public:
	BfmeX1002 *bfmeFind1002( BfmeArg1002 *arg );
};

// pinned reverse/symbols.csv: ?bfmeDo1037@BfmeG1037@@QAEXHH@Z @ 0x00013CCD
class BfmeG1037
{
public:
	void bfmeDo1037( Int, Int );
};

// landed: Code/GameEngine/Source/GameLogic/Object/ExperienceTrackerProgression.cpp
class ExperienceTracker
{
public:
	Bool gainExpForLevel( Int levelsToGain, Bool canScaleForBonus, Bool provideFeedback );

private:
	unsigned char m_pad000[ 0x28 ];

public:
	Int m_scalarIndex;
};

#include "../object.h"

// landed: Code/GameEngine/Source/Common/ExperienceLevelSystemGainLevels.cpp
class ExperienceLevelSystem
{
public:
	void gainLevels( Object *object, Int levels, Bool provideFeedback );
};
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class BfmeHordeContainOwner
{
public:
	void rva00245b20( Object *member, Int p2, Bool p3, Int p4 );

private:
	unsigned char m_pad000[ 8 ];
	Object *m_owner;
	unsigned char m_gap0[ 0x1bc - 0xc ];
	Int m_pendingSlot;
};

// ?rva00245b20@BfmeHordeContainOwner@@QAEXPAVObject@@H_NH@Z
void BfmeHordeContainOwner::rva00245b20( Object *member, Int p2, Bool p3, Int p4 )
{
	Int outFlag = 0;
	Int index = ( (Rva0023CDD0Owner *)this )->rva0023cdd0( p2, &outFlag );
	if ( index == -1 )
		return;

	( (Rva002459D0Owner *)this )->rva002459d0( member, &m_pendingSlot, index );

	BfmeX1002 *carrier = ( (BfmeA1002 *)this )->bfmeFind1002( (BfmeArg1002 *)member );
	if ( carrier )
	{
		( (BfmeG1037 *)carrier )->bfmeDo1037( outFlag, p4 );
	}

	if ( !p3 )
	{
		m_owner->m_experienceTracker->gainExpForLevel( 1, true, false );
	}

	Int diff = m_owner->m_experienceTracker->m_scalarIndex
			 - member->m_experienceTracker->m_scalarIndex;
	TheExperienceLevelSystem->gainLevels( member, diff, false );
}
