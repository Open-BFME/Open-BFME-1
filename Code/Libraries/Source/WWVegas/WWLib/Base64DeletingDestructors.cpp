// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Base64Pipe/Base64Straw scalar-deleting destructors at retail
// 0x009E2500/0x009E2520.  Their adjacent matched constructors install the
// contiguous vtables at 0x011453E4/0x011453F8, whose named virtual slots make
// the class identities unambiguous.

class Base64Pipe
{
public:
	virtual ~Base64Pipe();
};

class Base64Straw
{
public:
	virtual ~Base64Straw();
};

void forceBase64DeletingDestructors()
{
	Base64Pipe pipe;
	Base64Straw straw;
}
