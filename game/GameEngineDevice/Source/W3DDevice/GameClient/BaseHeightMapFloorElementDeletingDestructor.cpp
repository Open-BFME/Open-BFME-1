// cl: /DNDEBUG /MD /EHsc
// Emits the MSVC scalar deleting destructor used by the BaseHeightMap floor
// buffer element vtable.  The ordinary destructor is defined in the sibling
// reconstruction at retail 0x006F8290.

class BaseHeightMapFloorElement
{
public:
	virtual ~BaseHeightMapFloorElement();
};

void forceBaseHeightMapFloorElementDeletingDestructor()
{
	BaseHeightMapFloorElement value;
}
