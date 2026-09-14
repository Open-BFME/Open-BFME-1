// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5 scalar-deleting destructors for the matched BuffManager family.
// The complete destructors restore class-specific vtables, and the matched
// manager constructor plus embedded BuffEntry layout establish both owners.

class BuffEntry
{
public:
	virtual ~BuffEntry();
};

class BuffManager
{
public:
	virtual ~BuffManager();
};

void forceBuffDeletingDestructors()
{
	BuffEntry entry;
	BuffManager manager;
}
