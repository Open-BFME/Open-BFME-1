// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ActiveBody scalar-deleting destructor at retail RVA 0x00210B70
// (30 bytes).  The primary ActiveBody vtable at 0x010A78B0 reaches this
// wrapper; its name getter, pool getter, and virtual body methods identify the
// class.  The wrapper's ILT 0x00017EEA routes to the matched complete body at
// 0x0020F8E0, while the factory-pinned ActiveBody constructor is at 0x00211A50.

// The scalar-deleting destructor (??_G, matched 30B row) must call the rowed
// complete destructor ??1Rva0020F8E0Owner (0x0020F8E0, defined in
// Rva0020F8E0Destructor.cpp) rather than an ActiveBody complete destructor
// nothing defines. An explicit empty derived destructor inlines into the
// generated ??_G wrapper, leaving the direct base call.
struct Rva0020F8E0Owner
{
	virtual ~Rva0020F8E0Owner();
};

class ActiveBody : public Rva0020F8E0Owner
{
public:
	virtual ~ActiveBody();
};

// ??1ActiveBody@@UAE@XZ present-unmatched
ActiveBody::~ActiveBody()
{
}

void forceActiveBodyDeletingDestructor()
{
	ActiveBody value;
}
