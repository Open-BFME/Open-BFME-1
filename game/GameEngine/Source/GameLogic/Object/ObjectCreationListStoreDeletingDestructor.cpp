// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001DADE0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched ObjectCreationListStore destructor at 0x001DA720.

class ObjectCreationListStore
{
	friend void forceObjectCreationListStoreDeletingDestructorCopy(const ObjectCreationListStore &that);
public:
	virtual ~ObjectCreationListStore();
};


void Force_ObjectCreationListStore_Deleting_Destructor(ObjectCreationListStore *p)
{
	delete p;
}

// ~ObjectCreationListStore is matched out of line (ObjectCreationListStoreDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceObjectCreationListStoreDeletingDestructorCopy(const ObjectCreationListStore &that)
{
	ObjectCreationListStore value(that);
}
