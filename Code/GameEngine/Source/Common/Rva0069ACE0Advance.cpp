// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// One ramp step on the object *pp points at, retail 0x0069ACE0.
//
// Three flags at +0x39, +0x3a and +0x3c stop the step outright.  Either of the
// two rise flags at +0x34 and +0x36 adds the owner's step at +0x44 to the
// object's level at +0x28 and clamps it at the integer ceiling the owner
// reaches through +0xc.  Either of the two fall flags at +0x35 and +0x37
// subtracts the same step and clamps at BfmeZeroRange.  Reaching the ceiling
// without the +0x34 flag raises the +0x38 flag and clears all four.
//
// No caller, vtable slot or string names the owner or the method, so both keep
// the retail address.  The field names are placeholders for the same reason.

extern const float BfmeZeroRange;

class Rva0069ACE0Obj
{
public:
	char m_pad0[0x28];
	float m_t;
	char m_pad1[0x34 - 0x2c];
	unsigned char m_f34;
	unsigned char m_f35;
	unsigned char m_f36;
	unsigned char m_f37;
	unsigned char m_f38;
	unsigned char m_f39;
	unsigned char m_f3a;
	unsigned char m_pad3b;
	unsigned char m_f3c;
};

class Rva0069ACE0Limit
{
public:
	char m_pad[0x3c];
	int m_limit;
};

class Rva0069ACE0Owner
{
public:
	unsigned char advance(Rva0069ACE0Obj **pp);

	char m_pad0[0xc];
	Rva0069ACE0Limit *m_lim;
	char m_pad1[0x44 - 0x10];
	float m_step;
};

unsigned char Rva0069ACE0Owner::advance(Rva0069ACE0Obj **pp)
{
	Rva0069ACE0Obj *o = *pp;
	if (o->m_f39)
		return 0;
	if (o->m_f3a)
		return 0;
	if (o->m_f3c)
		return 0;

	if (!o->m_f34 && !o->m_f36)
	{
		if (!o->m_f35 && !o->m_f37)
			return 0;

		o->m_t = o->m_t - m_step;
		Rva0069ACE0Obj *decayed = *pp;
		if (decayed->m_t <= BfmeZeroRange)
		{
			decayed->m_t = 0.0f;
			(*pp)->m_f35 = 0;
			(*pp)->m_f37 = 0;
		}
		return 1;
	}

	o->m_t = m_step + o->m_t;
	{
		Rva0069ACE0Obj *raised = *pp;
		float lim = (float)m_lim->m_limit;
		if (lim <= raised->m_t)
		{
			raised->m_t = lim;
			Rva0069ACE0Obj *held = *pp;
			if (!held->m_f34)
				held->m_f38 = 1;
			(*pp)->m_f34 = 0;
			(*pp)->m_f36 = 0;
			(*pp)->m_f35 = 0;
			(*pp)->m_f37 = 0;
		}
	}
	return 1;
}
