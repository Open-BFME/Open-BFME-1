// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x00207200: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched SiegeDockingBehavior destructor at 0x002067C0.

class SiegeDockingBehavior
{
public:
	virtual ~SiegeDockingBehavior();
};

__declspec(noinline) SiegeDockingBehavior::~SiegeDockingBehavior() {}

void Force_SiegeDockingBehavior_Deleting_Destructor(SiegeDockingBehavior *p)
{
	delete p;
}
