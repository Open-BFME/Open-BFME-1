// cl: /DNDEBUG /MD /EHsc
//
// WW3D AABTreeClass scalar-deleting destructor.  Three matched constructors
// install vtable 0x0113E678; after RefCountClass::Delete_This, its second slot
// is the deleting wrapper at retail RVA 0x0096ACA0.

class AABTreeClass
{
public:
	virtual ~AABTreeClass();
};

__declspec(noinline) AABTreeClass::~AABTreeClass()
{
}

void Force_AABTreeClass_Deleting_Destructor(AABTreeClass *tree)
{
	delete tree;
}
