// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: scalar-deleting destructors for two UserPreferences subclasses.
// Their matched constructors install distinct vtables whose slot-zero ILTs
// route to these wrappers, and both complete destructors are already pinned.

class GameSpyMiscPreferences
{
public:
	virtual ~GameSpyMiscPreferences();
};

class IgnorePreferences
{
public:
	virtual ~IgnorePreferences();
};

void forceUserPreferencesDeletingDestructors()
{
	GameSpyMiscPreferences misc;
	IgnorePreferences ignore;
}
