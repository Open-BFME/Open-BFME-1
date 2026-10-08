// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0019EC50: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched SidesList destructor at 0x0019E640.

class SidesList
{
public:
	virtual ~SidesList();

protected:
	// Protected stand-in constructor so the forcer can install the vftable;
	// it emits only an unreferenced ??0SidesList@@IAE@XZ COMDAT and never
	// clashes with the real public constructor (0x0019EA80). The destructor
	// is matched in SidesListDestructorThunk.cpp.
	SidesList() {}
	friend void Force_SidesList_Deleting_Destructor();
};

void Force_SidesList_Deleting_Destructor()
{
	SidesList value;
}
