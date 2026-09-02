// Walk a pointer vector at +0x138 when either flag at +0x14D/+0x14E is set
// or the dword at +0x10 equals 0x18. Each non-null element is called.

class Rva0049B240Elem
{
public:
	void Rva0049B240Call();
};

class Rva0049B240Owner
{
public:
	void Rva0049B240();

private:
	unsigned char m_lead[ 0x10 ];
	int m_kind;
	unsigned char m_mid[ 0x138 - 0x14 ];
	Rva0049B240Elem **m_start;
	Rva0049B240Elem **m_finish;
	unsigned char m_gap[ 0x14D - 0x140 ];
	unsigned char m_flagA;
	unsigned char m_flagB;
};

void Rva0049B240Owner::Rva0049B240()
{
	Rva0049B240Owner *self = this;
	if ( !self->m_flagA && !self->m_flagB && self->m_kind != 0x18 )
		return;
	Rva0049B240Elem **end = self->m_finish;
	Rva0049B240Elem **it = self->m_start;
	while ( it != end )
	{
		Rva0049B240Elem *elem = *it;
		if ( elem )
			elem->Rva0049B240Call();
		++it;
		end = self->m_finish;
	}
}
