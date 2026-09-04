// cl: /O2 /Ob0
// Converted from Code/gen_asm/d_005e97b0.asm (?d_00609fa0@@YAXXZ).
// Empty STLport __copy of m_24 onto m_20, then two sets on the +0x18 member.

namespace _STL
{
struct random_access_iterator_tag
{
};

char *__cdecl __copy(char *first, char *last, char *result,
	const random_access_iterator_tag &, int *);
}

class Rva0006AB10Curve
{
public:
	void set(float a, float b, int c, int d);
};

class Rva00609FA0Host
{
public:
	void reset();

	char m_pad[0x20];
	char *m_20;
	char *m_24;
};

void Rva00609FA0Host::reset()
{
	int *none = 0;
	Rva00609FA0Host *self = this;
	char *dst = self->m_20;
	char *src = self->m_24;
	_STL::random_access_iterator_tag tag;
	self->m_24 = _STL::__copy(src, src, dst, tag, none);
	Rva0006AB10Curve *curve = (Rva0006AB10Curve *)((char *)self + 0x18);
	curve->set(0.0f, 0.0f, 0, 0);
	curve->set(1.0f, 1.0f, 0, 0);
}
