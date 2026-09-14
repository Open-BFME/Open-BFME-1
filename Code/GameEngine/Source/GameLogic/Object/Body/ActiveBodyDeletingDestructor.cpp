// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ActiveBody scalar-deleting destructor at retail RVA 0x00210B70
// (30 bytes).  The primary ActiveBody vtable at 0x010A78B0 reaches this
// wrapper; its name getter, pool getter, and virtual body methods identify the
// class.  The wrapper's ILT 0x00017EEA routes to the matched complete body at
// 0x0020F8E0, while the factory-pinned ActiveBody constructor is at 0x00211A50.

class ActiveBody
{
public:
	virtual ~ActiveBody();
};

void forceActiveBodyDeletingDestructor()
{
	ActiveBody value;
}
