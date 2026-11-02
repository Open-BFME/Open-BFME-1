// cl: /DNDEBUG /MD /EHsc

// Open-BFME: Team scalar-deleting destructor at retail 0x000F7280 (30
// bytes).  The matched Team constructor at 0x000F7790, complete destructor
// at 0x000F4250, and the BFME Team member-list/relation-map implementation
// establish the authentic class identity.

class Team
{
	friend void forceTeamDeletingDestructorCopy(const Team &that);
protected:
	__declspec(noinline) virtual ~Team();
	friend void Force_Team_Deleting_Destructor(Team *value);
};


void Force_Team_Deleting_Destructor(Team *value)
{
	delete value;
}

// ~Team is matched out of line (TeamDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceTeamDeletingDestructorCopy(const Team &that)
{
	Team value(that);
}
