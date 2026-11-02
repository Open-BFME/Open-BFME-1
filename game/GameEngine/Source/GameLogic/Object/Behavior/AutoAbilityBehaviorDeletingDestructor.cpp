// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001ED970: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched AutoAbilityBehavior destructor at 0x001ED6E0.

class AutoAbilityBehavior
{
	friend void forceAutoAbilityBehaviorDeletingDestructorCopy(const AutoAbilityBehavior &that);
public:
	virtual ~AutoAbilityBehavior();
};


void Force_AutoAbilityBehavior_Deleting_Destructor(AutoAbilityBehavior *p)
{
	delete p;
}

// ~AutoAbilityBehavior is matched out of line (AutoAbilityBehaviorDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceAutoAbilityBehaviorDeletingDestructorCopy(const AutoAbilityBehavior &that)
{
	AutoAbilityBehavior value(that);
}
