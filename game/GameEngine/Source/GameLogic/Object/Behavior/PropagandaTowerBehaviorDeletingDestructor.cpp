// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x002034C0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched PropagandaTowerBehavior destructor at 0x002034F0.

class PropagandaTowerBehavior
{
	friend void forcePropagandaTowerBehaviorDeletingDestructorCopy(const PropagandaTowerBehavior &that);
public:
	virtual ~PropagandaTowerBehavior();
};


void Force_PropagandaTowerBehavior_Deleting_Destructor(PropagandaTowerBehavior *p)
{
	delete p;
}

// ~PropagandaTowerBehavior is matched out of line (PropagandaTowerBehaviorDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forcePropagandaTowerBehaviorDeletingDestructorCopy(const PropagandaTowerBehavior &that)
{
	PropagandaTowerBehavior value(that);
}
