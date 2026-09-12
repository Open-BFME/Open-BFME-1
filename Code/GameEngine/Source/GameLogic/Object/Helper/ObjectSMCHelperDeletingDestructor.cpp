// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001C55F0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched ObjectSMCHelper destructor at 0x002570C0.

class ObjectSMCHelper
{
public:
	virtual ~ObjectSMCHelper();
};

__declspec(noinline) ObjectSMCHelper::~ObjectSMCHelper() {}

void Force_ObjectSMCHelper_Deleting_Destructor(ObjectSMCHelper *p)
{
	delete p;
}
