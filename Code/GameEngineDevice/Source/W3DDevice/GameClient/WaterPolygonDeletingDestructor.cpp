// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for the water polygon owner.
// The exact constructor at 0x007A4FD0 and matching 113-byte destructor at
// 0x007A1230 install/use the one-slot vtable 0x01127EB4; slot zero routes
// through ILT 0x000099B2 to this 30-byte wrapper.

class Rva007A1230ArrayOwner
{
public:
	virtual ~Rva007A1230ArrayOwner();

private:
	friend void forceRva007A1230ArrayOwnerDeletingDestructor();
};

void forceRva007A1230ArrayOwnerDeletingDestructor()
{
	Rva007A1230ArrayOwner value;
}
