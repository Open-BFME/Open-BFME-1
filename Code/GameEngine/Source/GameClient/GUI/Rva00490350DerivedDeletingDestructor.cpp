// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: scalar-deleting destructor for Rva00490350Derived.
// Its exact constructor at 0x004902C0 and matching complete destructor at
// 0x00490350 use the dedicated derived vtable 0x010F9AE4; slot zero routes
// through ILT 0x000421C7 to this 30-byte wrapper.

class Rva00490350Derived
{
public:
	virtual ~Rva00490350Derived();

private:
	friend void forceRva00490350DerivedDeletingDestructor();
};

void forceRva00490350DerivedDeletingDestructor()
{
	Rva00490350Derived value;
}
