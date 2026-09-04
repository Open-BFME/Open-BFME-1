// ?value@Rva001C9310@@QAEHXZ
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Two handwritten OVERRIDE walks of m_template at +4: load dword +0x448,
// then if dword +0xD0 has bit 0x2000000 multiply by [this+0x210]+0x28.

class Overridable
{
public:
	const Overridable *getFinalOverride( void ) const;
	void *m_head;
	Overridable *m_nextOverride;
};

class Rva001C9310Thing : public Overridable
{
public:
	char m_gap_d0[ 0xD0 - 8 ];
	unsigned m_flags_d0;
	char m_gap_448[ 0x448 - 0xD4 ];
	int m_value_448;
};

class Rva001C9310Scale
{
public:
	char m_gap[ 0x28 ];
	int m_scale;
};

class Rva001C9310
{
public:
	int value();



	void *m_vptr;
	Rva001C9310Thing *m_template;
	char m_gap[ 0x210 - 8 ];
	Rva001C9310Scale *m_scaleSrc;
};

static int rva001C9310Value(Rva001C9310 *self)
{
	Rva001C9310Thing *thing = self->m_template;
	if ( thing )
	{
		if ( thing->m_nextOverride )
			thing = (Rva001C9310Thing *)thing->m_nextOverride->getFinalOverride();
	}
	int v = thing->m_value_448;

	thing = self->m_template;
	if ( thing )
	{
		if ( thing->m_nextOverride )
			thing = (Rva001C9310Thing *)thing->m_nextOverride->getFinalOverride();
	}
	if ( thing->m_flags_d0 & 0x2000000 )
		return self->m_scaleSrc->m_scale * v;
	return v;
}

int Rva001C9310::value()
{
	return rva001C9310Value(this);
}
