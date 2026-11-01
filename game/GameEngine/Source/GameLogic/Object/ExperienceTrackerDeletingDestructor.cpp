// cl: /DNDEBUG /MD /EHsc

// Open-BFME: ExperienceTracker scalar-deleting destructor at retail
// 0x001B2660 (30 bytes). The matched ExperienceTracker constructor at
// 0x001B2570, complete BFME destructor at 0x001B22F0, and named progression
// methods/member layout establish the authentic class identity.

class ExperienceTracker
{
public:
	__declspec(noinline) virtual ~ExperienceTracker();
};

// ~ExperienceTracker is matched out of line (ExperienceTrackerBFMEDtor.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceExperienceTrackerDeletingDestructorCopy(const ExperienceTracker &that)
{
	ExperienceTracker value(that);
}

void Force_ExperienceTracker_Deleting_Destructor(ExperienceTracker *value)
{
	delete value;
}
