// ?advance@Rva0069ACE0Owner@@QAEEPAPAVRva0069ACE0Obj@@@Z
// partial score=0.82 date=2026-09-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Advance/decay on *pp; mid false-tail via goto to match short jcc.

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
		goto fail;
	if (o->m_f3a)
		goto fail;
	if (o->m_f3c)
		goto fail;
	if (o->m_f34)
		goto add;
	if (o->m_f36)
		goto add;
	if (o->m_f35)
		goto sub;
	if (o->m_f37)
		goto sub;
fail:
	return 0;
sub:
	o->m_t = o->m_t - m_step;
	o = *pp;
	if (o->m_t <= 0.0f)
	{
		o->m_t = 0.0f;
		(*pp)->m_f35 = 0;
		(*pp)->m_f37 = 0;
		return 1;
	}
	return 1;
add:
	o->m_t = m_step + o->m_t;
	{
		float lim = (float)m_lim->m_limit;
		Rva0069ACE0Obj *s = *pp;
		if (lim <= s->m_t)
		{
			s->m_t = lim;
			o = *pp;
			if (!o->m_f34)
				o->m_f38 = 1;
			(*pp)->m_f34 = 0;
			(*pp)->m_f36 = 0;
			(*pp)->m_f35 = 0;
			(*pp)->m_f37 = 0;
			return 1;
		}
	}
	return 1;
}
