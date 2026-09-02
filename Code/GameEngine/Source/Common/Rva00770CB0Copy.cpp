// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: compiler-generated copy constructor for the 108-byte aggregate
// at retail 0x00770CB0. The two ten-dword tails are distinct subobjects.
#include <new>

class Rva00770CB0Base
{
public:
	Rva00770CB0Base(const Rva00770CB0Base &);
	~Rva00770CB0Base();
private:
	int m_value;
};

class Rva00770CB0Member12
{
public:
	Rva00770CB0Member12(const Rva00770CB0Member12 &);
private:
	int m_value[3];
};

class Rva00770CB0Payload : private Rva00770CB0Base
{
public:
	int m_at04;
	int m_at08;
	int m_at0C;
	Rva00770CB0Member12 m_at10;
	int m_at1C[10];
	int m_at44[10];
};

Rva00770CB0Payload *Rva00770CB0CopyAnchor(
	Rva00770CB0Payload *slot, const Rva00770CB0Payload &source)
{
	return new (slot) Rva00770CB0Payload(source);
}
