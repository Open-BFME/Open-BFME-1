// cl: /O2 /EHsc
//
// Rva00808CB0LanGameEntry scalar-deleting destructor, retail 0x007E8E70.
// The matched Rva00809050 factory constructs this 0x20-byte LAN entry and
// installs its dedicated vtable 0x011296B0.  That table's slot zero is this
// wrapper.  The empty derived destructor is folded with the base cleanup at
// 0x007E86C0, so the wrapper's only destructor call reaches that exact body.

class Rva007E86B0Base
{
public:
	virtual ~Rva007E86B0Base();
};

Rva007E86B0Base::~Rva007E86B0Base()
{
}

class Rva00808CB0LanGameEntry : public Rva007E86B0Base
{
public:
	virtual ~Rva00808CB0LanGameEntry();
};

Rva00808CB0LanGameEntry::~Rva00808CB0LanGameEntry()
{
}

void forceRva00808CB0LanGameEntryDeletingDestructor()
{
	Rva00808CB0LanGameEntry value;
}
