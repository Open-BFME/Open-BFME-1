// cl: /DNDEBUG /MD /GX- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Iinputs/vendor/stlport /Iinputs/reference/shims/sweep
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct Gen_t_00069cc0_p16cd
{
	int value[4];
};

typedef _STL::vector<Gen_t_00069cc0_p16cd> Rva0006A9D0Vector;

// Retail reaches the vector copy constructor through the incremental-link
// thunk at 0x0003EE4B, so call that thunk directly instead of aliasing the
// copy constructor's own name to it.  The copy is therefore built in place:
// a real constructor would also emit STLport's default constructor, which
// retail's inlined copy never does.
extern void j_0003ee4b();

class BfmeStateGQ
{
public:
	void bfmeSwapGQ(BfmeStateGQ *other);
};

class Rva0006A9D0State
{
public:
	Rva0006A9D0State &operator=(const Rva0006A9D0State &other);

	int m_value00;
	int m_value04;
	Rva0006A9D0Vector m_values;
	int m_value14;
	int m_value18;
	float m_value1C;
	float m_value20;
	float m_value24;
	float m_value28;
};

Rva0006A9D0State &Rva0006A9D0State::operator=(const Rva0006A9D0State &other)
{
	char storage[sizeof(Rva0006A9D0State)];
	Rva0006A9D0State *copy = reinterpret_cast<Rva0006A9D0State *>(storage);
	copy->m_value00 = other.m_value00;
	copy->m_value04 = other.m_value04;
	typedef void (Rva0006A9D0Vector::*CopyFn)(const Rva0006A9D0Vector &);
	union { void (*fn)(); CopyFn call; } u = { j_0003ee4b };
	(copy->m_values.*u.call)(other.m_values);
	copy->m_value18 = (int)copy->m_values.end();
	copy->m_value28 = 0.0f;
	copy->m_value24 = 0.0f;
	copy->m_value20 = 0.0f;
	copy->m_value1C = 0.0f;
	reinterpret_cast<BfmeStateGQ *>(this)->bfmeSwapGQ(
		reinterpret_cast<BfmeStateGQ *>(copy));
	copy->m_values.~Rva0006A9D0Vector();
	return *this;
}