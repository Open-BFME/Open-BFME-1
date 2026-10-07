// cl: /DNDEBUG /MD /EHsc
// Emits the MSVC scalar deleting destructor used by the BaseHeightMap floor
// buffer element vtable.  The ordinary destructor is defined in the sibling
// reconstruction at retail 0x006F8290.

class BaseHeightMapFloorElement
{
public:
	BaseHeightMapFloorElement();	// not emitted here: retail's ctor lives at its own address
	virtual ~BaseHeightMapFloorElement();
};

// The implicit copy constructor (no retail twin) is what makes MSVC emit the
// vftable and with it ??_G; the default constructor stays declared so this TU
// does not emit a non-retail copy of it.
void forceBaseHeightMapFloorElementDeletingDestructor(const BaseHeightMapFloorElement &that)
{
	BaseHeightMapFloorElement value(that);
}
