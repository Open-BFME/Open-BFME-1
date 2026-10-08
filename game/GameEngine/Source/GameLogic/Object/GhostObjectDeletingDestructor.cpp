// cl: /O2 /DNDEBUG /MD /EHsc
// Retail RVA 0x001B3EF0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched GhostObject destructor at 0x001B3E60.

class GhostObject
{
public:
	virtual ~GhostObject();

private:
	// Forcer-only constructor: the default constructor is retail's strong
	// body in GhostObjectCtorDtor.cpp, so this TU must not emit its own.
	explicit GhostObject(int) {}
	friend void Force_GhostObject_Deleting_Destructor();
};

// The destructor itself is matched in GhostObjectCtorDtor.cpp.
void Force_GhostObject_Deleting_Destructor()
{
	GhostObject value(0);
}
