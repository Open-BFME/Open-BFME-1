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

ExperienceTracker::~ExperienceTracker()
{
}

void Force_ExperienceTracker_Deleting_Destructor(ExperienceTracker *value)
{
	delete value;
}
