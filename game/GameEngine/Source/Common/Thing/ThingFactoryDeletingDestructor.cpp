// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001384D0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched ThingFactory destructor at 0x00137C90.

class ThingFactory
{
	friend void forceThingFactoryDeletingDestructorCopy(const ThingFactory &that);
public:
	virtual ~ThingFactory();
};


void Force_ThingFactory_Deleting_Destructor(ThingFactory *p)
{
	delete p;
}

// ~ThingFactory is matched out of line (ThingFactoryDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceThingFactoryDeletingDestructorCopy(const ThingFactory &that)
{
	ThingFactory value(that);
}
