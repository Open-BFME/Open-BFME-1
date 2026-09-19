// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001F15F0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched BezierProjectileBehavior destructor at 0x001F0240.

class BezierProjectileBehavior
{
public:
	virtual ~BezierProjectileBehavior();
};

__declspec(noinline) BezierProjectileBehavior::~BezierProjectileBehavior() {}

void Force_BezierProjectileBehavior_Deleting_Destructor(BezierProjectileBehavior *p)
{
	delete p;
}
