// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001B3EF0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched GhostObject destructor at 0x001B3E60.

class GhostObject
{
public:
	virtual ~GhostObject();
};

__declspec(noinline) GhostObject::~GhostObject() {}

void Force_GhostObject_Deleting_Destructor(GhostObject *p)
{
	delete p;
}
