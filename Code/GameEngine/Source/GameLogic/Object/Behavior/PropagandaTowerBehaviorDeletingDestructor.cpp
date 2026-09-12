// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x002034C0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched PropagandaTowerBehavior destructor at 0x002034F0.

class PropagandaTowerBehavior
{
public:
	virtual ~PropagandaTowerBehavior();
};

__declspec(noinline) PropagandaTowerBehavior::~PropagandaTowerBehavior() {}

void Force_PropagandaTowerBehavior_Deleting_Destructor(PropagandaTowerBehavior *p)
{
	delete p;
}
