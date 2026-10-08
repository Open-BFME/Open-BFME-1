// cl: /O2 /Ob1

#include <new.h>

// The vptr installed below is Rva00605710Root's own vtable, which retail holds
// at 0x0108971C (targets/game/reverse/dir32_addresses.csv). C++ has no portable
// spelling for a vtable's address and MSVC 7.1 refuses the address of a virtual
// member function, so the class is constructed instead: the constructor names
// the vtable, and the load folds away, leaving the relocation in `set` alone.
// Placement new keeps the destructor -- which an automatic object would call --
// out of the body. The declaration matches the one in
// AnimationSoundClientBehaviorRva00605710Constructor.cpp, so the vtable this TU
// emits is the same COMDAT that file emits.
class Rva00605710Root
{
public:
	Rva00605710Root() {}
	virtual ~Rva00605710Root() {}
	int field4;
};

class Rva00113B20
{
	void *m_vptr;
	int m_04;

public:
	Rva00113B20 &set(int a);
};

Rva00113B20 &Rva00113B20::set(int a)
{
	char buf[sizeof(Rva00605710Root)];
	Rva00605710Root *base = new (buf) Rva00605710Root;
	m_vptr = *(void **)base;
	m_04 = a;
	return *this;
}