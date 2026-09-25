// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x00322070, 20 bytes through the int3 run at +0x14: the non-deleting
// destructor of the class whose vtable 0x010E1F3C the constructor at
// 0x00322050 installs; it deletes the polymorphic object held at +4.  Its
// last 11 bytes were claimed as Campaign::deleteInstance, which `delete this`
// cannot produce (they load +4 first); retail has no COMDAT folding, so they
// belong to this body.  No caller names the class, so it keeps the address.

class Rva00322070Item
{
public:
	virtual ~Rva00322070Item();
};

class Rva00322070Owner
{
public:
	virtual ~Rva00322070Owner();
private:
	Rva00322070Item *m_item04;
};

Rva00322070Owner::~Rva00322070Owner()
{
	delete m_item04;
}
