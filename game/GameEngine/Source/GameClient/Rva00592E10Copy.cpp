// cl: /O2 /Ob0

// Retail 0x00592E10 copies four 8-byte records into this+0x4DC.
// The caller at 0x006C0FA0 passes the source buffer through ILT 0x00001244.

struct Rva00592E10Pair
{
	unsigned int m_first;
	unsigned int m_second;
};

class Rva00592E10Owner
{
public:
	void copy(const Rva00592E10Pair *source);

private:
	char m_padding[0x4dc];
	Rva00592E10Pair m_pairs[4];
};

void Rva00592E10Owner::copy(const Rva00592E10Pair *source)
{
	volatile Rva00592E10Pair *destination = m_pairs;
	const Rva00592E10Pair *adjusted = (const Rva00592E10Pair *)
		((const char *)source + ((const char *)destination - (const char *)this) - 0x4dc);

	for (int index = 0; index < 4; ++index)
	{
		destination->m_first = adjusted->m_first;
		destination->m_second = adjusted->m_second;
		++destination;
		++adjusted;
	}
}
