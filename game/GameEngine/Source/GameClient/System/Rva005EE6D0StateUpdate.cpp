// The object's class and the meanings of its fields are not established by
// the available identity evidence. Keep its owner and helper names tied to
// their retail addresses.

struct Rva005EE6D0TableEntry
{
	float m_value;
	unsigned int m_duration;
};

class ParticleSystemZA
{
public:
	unsigned char m_pad00[ 8 ];
	unsigned int m_word08;
};

class Gen_005EE410
{
public:
	void bfmeUpdate(void);
};

class Rva005EE6D0Owner
{
public:
	void update();

	unsigned char m_pad00[ 0x04 ];
	unsigned char *m_data;
	unsigned char m_pad08[ 0x48 ];
	float m_value;
	float m_delta;
	int m_index;
	unsigned char m_pad5c[ 0x08 ];
};

ParticleSystemZA *bfmeNullSystemZA(void);

void Rva005EE6D0Owner::update()
{
	volatile unsigned int *lazySlot =
		reinterpret_cast<volatile unsigned int *>( m_data );
	lazySlot += 0x4C / sizeof( unsigned int );
	void *lazyObject = (void *)*lazySlot;
	if ( lazyObject == 0 )
	{
		lazyObject = bfmeNullSystemZA();
	}
	if ( static_cast<ParticleSystemZA *>( lazyObject )->m_word08 == 1 )
	{
		return;
	}

	// Retail reloads the member before making the second fallback call. Keep
	// that load independent from the first one.
	lazySlot = reinterpret_cast<volatile unsigned int *>( m_data );
	lazySlot += 0x4C / sizeof( unsigned int );
	lazyObject = (void *)*lazySlot;
	if ( lazyObject == 0 )
	{
		lazyObject = bfmeNullSystemZA();
	}
	if ( static_cast<ParticleSystemZA *>( lazyObject )->m_word08 == 2 )
	{
		return;
	}

	// Preserve retail's x87 operand order: load the current value before delta.
	m_value = *reinterpret_cast<volatile float *>(&m_value) + m_delta;
	if ( m_index >= 8 )
	{
		m_delta = 0.0f;
	}
	else
	{
		Rva005EE6D0TableEntry *entry =
			reinterpret_cast<Rva005EE6D0TableEntry *>(
				reinterpret_cast<unsigned char *>( this ) + 0x10 ) + m_index;
		if ( entry->m_duration != 0 )
		{
			const unsigned int elapsed =
				*reinterpret_cast<unsigned int *>( m_data + 0x34 ) -
				*reinterpret_cast<unsigned int *>( m_data + 0x68 );
			if ( elapsed >= entry->m_duration )
			{
				m_value = entry->m_value;
				++m_index;
				reinterpret_cast<Gen_005EE410 *>( this )->bfmeUpdate();
			}
		}
		else
		{
			m_delta = 0.0f;
		}
	}

	if ( m_value < 0.0f )
	{
		m_value = 0.0f;
	}
	else if ( m_value > 1.0f )
	{
		m_value = 1.0f;
	}
}
