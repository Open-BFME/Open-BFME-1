// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001ED970: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched AutoAbilityBehavior destructor at 0x001ED6E0.

class AutoAbilityBehavior
{
public:
	virtual ~AutoAbilityBehavior();
};

__declspec(noinline) AutoAbilityBehavior::~AutoAbilityBehavior() {}

void Force_AutoAbilityBehavior_Deleting_Destructor(AutoAbilityBehavior *p)
{
	delete p;
}
