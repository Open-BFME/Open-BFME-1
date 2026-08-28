// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?transferUnitsTo@Team@@QAEXPAV1@@Z: Code/GameEngine/Source/Common/RTS/Team.cpp
// Open-BFME5: Team::transferUnitsTo, retail 0x000EC9B0, zh_sweep packet 000ec9b0.
//
// The Zero Hour body unchanged in shape -- bail on self or null, then hand the
// head of the team's member list to the new team until the list empties. Two
// things the bytes settle that Team.cpp's headers get wrong, so it moves to its
// own TU rather than shifting the 32 other rows compiled against them:
//
//  - getFirstItemIn_TeamMemberList() inlines to a load from [this+0x0C], where
//    the vendored Team puts the list head at +0x10.
//  - Object::setTeam is VIRTUAL in BFME, reached through [vtbl+0x50], i.e.
//    slot 20. The reference declares it a plain member and the call compiles to
//    a direct one.
//
// The list head is re-read every iteration and the null test is inside the
// loop, which is what setTeam unlinking the object from this team looks like
// from here.

class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	// Only the one slot is named; the rest exist to place it.
	virtual void unused0( void ) = 0;
	virtual void unused1( void ) = 0;
	virtual void unused2( void ) = 0;
	virtual void unused3( void ) = 0;
	virtual void unused4( void ) = 0;
	virtual void unused5( void ) = 0;
	virtual void unused6( void ) = 0;
	virtual void unused7( void ) = 0;
	virtual void unused8( void ) = 0;
	virtual void unused9( void ) = 0;
	virtual void unused10( void ) = 0;
	virtual void unused11( void ) = 0;
	virtual void unused12( void ) = 0;
	virtual void unused13( void ) = 0;
	virtual void unused14( void ) = 0;
	virtual void unused15( void ) = 0;
	virtual void unused16( void ) = 0;
	virtual void unused17( void ) = 0;
	virtual void unused18( void ) = 0;
	virtual void unused19( void ) = 0;

	virtual void setTeam( Team *team ) = 0;					///< slot 20, [vtbl+0x50]
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void transferUnitsTo( Team *newTeam );

private:
	Object *getFirstItemIn_TeamMemberList( void ) { return m_teamMemberList; }

	unsigned char m_unreconstructed_00[0x0C];
	Object *m_teamMemberList;								///< +0x0C
};

// ?transferUnitsTo@Team@@QAEXPAV1@@Z
void Team::transferUnitsTo(Team *newTeam)
{
	if (this == newTeam) return;
	if (newTeam == 0) return;
	Object *obj;
	while ((obj = getFirstItemIn_TeamMemberList()) != 0) 
	{
		obj->setTeam(newTeam);
	} 
}
