// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x0014F350: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched AIInternalMoveToState destructor at 0x00172430.

class AIInternalMoveToState
{
public:
	virtual ~AIInternalMoveToState();
};

__declspec(noinline) AIInternalMoveToState::~AIInternalMoveToState() {}

void Force_AIInternalMoveToState_Deleting_Destructor(AIInternalMoveToState *p)
{
	delete p;
}
