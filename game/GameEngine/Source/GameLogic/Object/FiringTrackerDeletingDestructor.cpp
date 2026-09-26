// cl: /DNDEBUG /MD /EHsc

// Open-BFME: FiringTracker scalar-deleting destructor at retail 0x001B31D0
// (30 bytes). The matched FiringTracker constructor at 0x001B30E0, complete
// destructor at 0x001B2C70, and named cooldown, shot-query, speed-up, transfer,
// and update methods establish the authentic class identity.

class FiringTracker
{
protected:
	__declspec(noinline) virtual ~FiringTracker();
	friend void Force_FiringTracker_Deleting_Destructor(FiringTracker *value);
};

FiringTracker::~FiringTracker()
{
}

void Force_FiringTracker_Deleting_Destructor(FiringTracker *value)
{
	delete value;
}
