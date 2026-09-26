// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0019EC50: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched SidesList destructor at 0x0019E640.

class SidesList
{
public:
	virtual ~SidesList();
};

__declspec(noinline) SidesList::~SidesList() {}

void Force_SidesList_Deleting_Destructor(SidesList *p)
{
	delete p;
}
