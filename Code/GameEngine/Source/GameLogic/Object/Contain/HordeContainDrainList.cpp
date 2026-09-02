// cl: /DNDEBUG /MD

struct Rva00249EB0Node
{
	Rva00249EB0Node *next;
	void *unused;
	void *value;
};

struct Rva00249EB0List
{
	Rva00249EB0Node *sentinel;
};

class BfmeThingAGA
{
public:
	#define RVASLOT(n) virtual void slot##n();
	RVASLOT(0) RVASLOT(1) RVASLOT(2) RVASLOT(3) RVASLOT(4) RVASLOT(5)
	RVASLOT(6) RVASLOT(7) RVASLOT(8) RVASLOT(9) RVASLOT(10) RVASLOT(11)
	RVASLOT(12) RVASLOT(13) RVASLOT(14) RVASLOT(15) RVASLOT(16) RVASLOT(17)
	RVASLOT(18) RVASLOT(19) RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23)
	RVASLOT(24) RVASLOT(25) RVASLOT(26) RVASLOT(27) RVASLOT(28) RVASLOT(29)
	RVASLOT(30) RVASLOT(31) RVASLOT(32) RVASLOT(33) RVASLOT(34) RVASLOT(35)
	#undef RVASLOT
	virtual void consumeEntry( void *entry, void *context );

	void drainEntries( void *context );
	void bfmeFinishAGA( void *context );

private:
	unsigned char unused_004[0xC8];
	Rva00249EB0List m_entries;
};

void BfmeThingAGA::drainEntries( void *context )
{
	while ( m_entries.sentinel->next != m_entries.sentinel )
	{
		void *entry = m_entries.sentinel->next->value;
		if ( entry != 0 )
			consumeEntry( entry, context );
	}

	bfmeFinishAGA( context );
}
