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

// The implicit copy constructors (no retail twins) emit the vftables and with
// them ??_G without second, non-retail copies of the default constructors.
void forceUserPreferencesDeletingDestructors(const GameSpyMiscPreferences &miscThat,
	const IgnorePreferences &ignoreThat)
{
	GameSpyMiscPreferences misc(miscThat);
	IgnorePreferences ignore(ignoreThat);
}
