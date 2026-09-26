// cl: /O2 /Ob0

// This address-derived predicate compares the first pointer in another object
// with this object, then checks the two pointer fields at offsets +4 and +8.
// The body has no proven class or method identity.

class Rva00160500
{
	void *m_00;
	void *m_04;
	void *m_08;

public:
	int test(Rva00160500 *other);
};

int Rva00160500::test(Rva00160500 *other)
{
	if (other->m_00 == this || m_04 || m_08)
		return 1;
	return 0;
}
