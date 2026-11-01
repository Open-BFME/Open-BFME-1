// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// The List interface inherits GenericList without adding storage. Its
// scalar-deleting destructor is the 30-byte wrapper at retail 0x009E3460.
// List declares no destructor, so ~List (retail 0x009E3110) is the implicit
// one: a bare jump to GenericList::~GenericList 0x009E2F30 with no vptr store.
class GenericList
{
public:
	virtual ~GenericList();
};

class List : public GenericList
{
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceListDeletingDestructor(const List &that)
{
	List value(that);
}
