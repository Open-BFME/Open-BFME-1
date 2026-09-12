// cl: /DNDEBUG /MD /EHsc
// Retail RVA 0x001DADE0: scalar-deleting destructor. The wrapper calls the class
// destructor via ILT, routing to the matched ObjectCreationListStore destructor at 0x001DA720.

class ObjectCreationListStore
{
public:
	virtual ~ObjectCreationListStore();
};

__declspec(noinline) ObjectCreationListStore::~ObjectCreationListStore() {}

void Force_ObjectCreationListStore_Deleting_Destructor(ObjectCreationListStore *p)
{
	delete p;
}
