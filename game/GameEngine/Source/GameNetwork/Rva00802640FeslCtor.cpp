// cl: /GX-
// Rva00802680Owner ctor: vtable, V2ZeroInt field8, zero-pair block at +0x20,
// two Gen_dtor_007f6d20 members at +0x28/+0x30, then field4/C/8 in body.
// Sibling of matched ??1Rva00802680Owner@@UAE@XZ at 0x00802680.

struct V2ZeroInt
{
	__forceinline V2ZeroInt() : m_value(0) {}
	int m_value;
};

struct V2ZeroPair
{
	__forceinline V2ZeroPair() : m_a(0), m_b(0) {}
	int m_a;
	int m_b;
};

class Gen_dtor_007f6d20
{
public:
	Gen_dtor_007f6d20();

	void *m_ptr;
	int m_size;
};

class Rva00802680Owner
{
public:
	__declspec(noinline) Rva00802680Owner();
	virtual ~Rva00802680Owner();

	int m_field4;
	V2ZeroInt m_field8;
	int m_fieldC;
	char m_pad010[0x10];
	V2ZeroPair m_block;
	Gen_dtor_007f6d20 m_b;
	Gen_dtor_007f6d20 m_c;
};

Rva00802680Owner::Rva00802680Owner()
{
	m_field4 = 0;
	m_fieldC = 0;
	m_field8.m_value = 0;
}
