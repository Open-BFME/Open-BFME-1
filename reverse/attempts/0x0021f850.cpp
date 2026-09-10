// ?step@Rva0021F850Owner@@QAEXXZ
// partial score=0.94 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: address-derived. Retail 0x0021F850, 159B, HordeGarrisonContain's
// primary vtable slot 17 (+0x44) -- the same slot the +0x20 interface's owner
// cleanup call (0x00248C60, 0x0024ECA0) invokes unconditionally at the end of
// its body. No header source or matched caller names this BFME-only virtual.
//
// Counts the circular list at +0x38; past one live entry it sets model-
// condition bit 0x400 on the owning Object at +0x8 through the already-landed
// BfmeOwnerVNI::bfmeApply1VNI helper (same shape as Rva001B7CD0ConditionMove).
// Then snapshots the 40-entry, 0x14-byte array at +0xd8 to a stack local,
// calls the pinned GarrisonContain::removeInvalidObjectsFromGarrisonPoints and
// ::addValidObjectsToGarrisonPoints, and re-scatters the snapshot back
// through the own vtable's slot-26 index mapper.

class Rva0021F850Link
{
public:
	Rva0021F850Link *m_next;
};

class BfmeOwnerVNI
{
public:
	void bfmeApply1VNI();
};

struct Rva0021F850OwnerObject
{
	unsigned char m_head[0x110];
	int m_conditionFlags;   // +0x110
};

struct Rva0021F850Entry
{
	void *m_key;   // +0x00
	int m_04;      // +0x04
	int m_08;      // +0x08
	int m_0c;      // +0x0c
	int m_10;      // +0x10
};

class GarrisonContain
{
	friend class Rva0021F850Owner;
protected:
	void removeInvalidObjectsFromGarrisonPoints();
	void addValidObjectsToGarrisonPoints();
};

class Rva0021F850Owner
{
public:
	virtual void bfmeVt00(); virtual void bfmeVt01(); virtual void bfmeVt02(); virtual void bfmeVt03();
	virtual void bfmeVt04(); virtual void bfmeVt05(); virtual void bfmeVt06(); virtual void bfmeVt07();
	virtual void bfmeVt08(); virtual void bfmeVt09(); virtual void bfmeVt10(); virtual void bfmeVt11();
	virtual void bfmeVt12(); virtual void bfmeVt13(); virtual void bfmeVt14(); virtual void bfmeVt15();
	virtual void bfmeVt16(); virtual void bfmeVt17(); virtual void bfmeVt18(); virtual void bfmeVt19();
	virtual void bfmeVt20(); virtual void bfmeVt21(); virtual void bfmeVt22(); virtual void bfmeVt23();
	virtual void bfmeVt24(); virtual void bfmeVt25();
	virtual int bfmeMapEntry( void *key );   // slot 26, +0x68

	void step();

private:
	unsigned char m_head[4];
	Rva0021F850OwnerObject *m_owner;   // +0x8
	unsigned char m_gap1[0x2c];
	Rva0021F850Link *m_listHead;       // +0x38
	unsigned char m_gap2[0x9c];
	Rva0021F850Entry m_entries[40];    // +0xd8
};

// ?d_0021f850@@YAXXZ -- address-derived; the real virtual name is not
// recovered.
void Rva0021F850Owner::step()
{
	Rva0021F850Link *head = m_listHead;
	Rva0021F850Link *p = head->m_next;
	unsigned int n = 0;

	if ( p != head )
	{
		do
		{
			p = p->m_next;
			++n;
		}
		while ( p != head );

		if ( n > 0 )
		{
			Rva0021F850OwnerObject *owner = m_owner;
			int mask = 0x400;
			int flags = owner->m_conditionFlags;

			if ( ( flags & mask ) == 0 )
			{
				flags |= mask;
				owner->m_conditionFlags = flags;
				reinterpret_cast<BfmeOwnerVNI *>( owner )->bfmeApply1VNI();
			}
		}
	}

	Rva0021F850Entry tmp[40];

	for ( int i = 0; i < 40; i++ )
		tmp[i] = m_entries[i];

	reinterpret_cast<GarrisonContain *>( this )->removeInvalidObjectsFromGarrisonPoints();
	reinterpret_cast<GarrisonContain *>( this )->addValidObjectsToGarrisonPoints();

	for ( int j = 0; j < 40; j++ )
	{
		if ( tmp[j].m_key != 0 )
		{
			int k = bfmeMapEntry( tmp[j].m_key );

			if ( k != -1 )
				m_entries[k].m_08 = tmp[j].m_08;
		}
	}
}
