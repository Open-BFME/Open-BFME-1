// ?value@Rva001C9310@@QAEHXZ
// partial score=0.9 date=2026-09-04
// ?value@Rva001C9310@@QAEHXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

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

int Rva001C9310::value()
{
	Rva001C9310Thing *thing = m_template;
	if ( thing )
	{
		if ( thing->m_nextOverride )
			thing = (Rva001C9310Thing *)thing->m_nextOverride->getFinalOverride();
	}
	register int v = thing->m_value_448;

	register Rva001C9310 *owner = this;
	thing = owner->m_template;
	if ( thing )
	{
		if ( thing->m_nextOverride )
			thing = (Rva001C9310Thing *)thing->m_nextOverride->getFinalOverride();
	}
	if ( thing->m_flags_d0 & 0x2000000 )
		return owner->m_scaleSrc->m_scale * v;
	return v;
}
