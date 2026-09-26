// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// The List interface inherits GenericList without adding storage. Its
// scalar-deleting destructor is the 30-byte wrapper at retail 0x009E3460.
class GenericList
{
public:
	virtual ~GenericList();
};

class List : public GenericList
{
public:
	virtual ~List();
};

void forceListDeletingDestructor()
{
	List value;
}
