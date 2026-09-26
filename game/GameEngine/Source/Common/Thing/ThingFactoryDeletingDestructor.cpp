// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001384D0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched ThingFactory destructor at 0x00137C90.

class ThingFactory
{
public:
	virtual ~ThingFactory();
};

__declspec(noinline) ThingFactory::~ThingFactory() {}

void Force_ThingFactory_Deleting_Destructor(ThingFactory *p)
{
	delete p;
}
