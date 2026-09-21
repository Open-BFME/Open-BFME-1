// ?rva001A3BD0Update@Rva001A3BD0Owner@@QAEXPAXMMM@Z
// partial score=0.44 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: retail 0x001A3BD0 (247 B). Bails when the capped record
// array (capacity 64, this+0x54c) is full or the identity pointer is
// null; otherwise removes every existing record whose id matches the
// argument (swap with the then-current last record, shrinking the
// count), then always appends a fresh record built from a virtual
// float query on the identity pointer plus the three passed floats.
// The virtual call lands on vtable slot 0x6c (index 27); dummy members
// up to that slot make the compiler emit retail's call [eax+0x6c].

class Rva001A3BD0Base
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0C() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1C() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2C() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void unused38() = 0;
	virtual void unused3C() = 0;
	virtual void unused40() = 0;
	virtual void unused44() = 0;
	virtual void unused48() = 0;
	virtual void unused4C() = 0;
	virtual void unused50() = 0;
	virtual void unused54() = 0;
	virtual void unused58() = 0;
	virtual void unused5C() = 0;
	virtual void unused60() = 0;
	virtual void unused64() = 0;
	virtual void unused68() = 0;
	virtual float rva001A3BD0Query(void *id) = 0;
};

struct Rva001A3BD0Record
{
	void *id;
	float field04;
	float field08;
	float field0C;
	float field10;
};

extern const float g_bfmeK1266C;

class Rva001A3BD0Owner : public Rva001A3BD0Base
{
public:
	void rva001A3BD0Update(void *id, float floatA, float floatB, float floatC);

private:
	unsigned char m_pad[0x4c - 4];
	Rva001A3BD0Record m_records[64];
	int m_count;
};

void Rva001A3BD0Owner::rva001A3BD0Update(void *id, float floatA, float floatB, float floatC)
{
	int count = m_count;
	if (count >= 64)
		return;
	if (id == 0)
		return;

	int i = 0;
	if (count > 0)
	{
		Rva001A3BD0Record *slot = m_records;
		do
		{
			if (slot->id == id)
			{
				int lastIndex = m_count - 1;
				*slot = m_records[lastIndex];
				m_count = lastIndex;
			}
			else
			{
				++slot;
			}
			++i;
			count = m_count;
		} while (i < count);
	}

	float queryResult = rva001A3BD0Query(id);
	int newIndex = m_count;
	Rva001A3BD0Record &rec = m_records[newIndex];
	rec.id = id;
	rec.field04 = floatA / (floatC * g_bfmeK1266C);
	rec.field08 = floatA;
	rec.field0C = floatC;
	rec.field10 = queryResult - floatA;
	m_count = newIndex + 1;
}

// @?rva001A3BD0Update@Rva001A3BD0Owner@@QAEXPAXMMM@Z 0x001A3BD0
