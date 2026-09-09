// ?sumField440@Rva0015A5B0List@@QBEHXZ
// Open-BFME: clean reconstruction of retail 0x0015A5B0.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef int Int;

class Rva0015A5B0Thing;

class Rva0015A5B0Inner
{
public:
	Rva0015A5B0Thing *bfmeResolveKZ();
};

class Rva0015A5B0Thing
{
public:
	Int m_spare;
	Rva0015A5B0Inner *m_inner;
	unsigned char m_pad08[0x438];
	Int m_value440;
};

class Rva0015A5B0List
{
public:
	Int sumField440() const;

	Int m_count;
	void **m_items[1];
};

Int Rva0015A5B0List::sumField440() const
{
	Int total = 0;
	if (m_count > 0)
	{
		void **const *it = m_items;
		Int remaining = m_count;
		do
		{
			unsigned int *objectData = (unsigned int *)*it;
			++objectData;
			_ReadWriteBarrier();
			Rva0015A5B0Thing *thing = *(Rva0015A5B0Thing **)objectData;
			if (thing && thing->m_inner)
				thing = thing->m_inner->bfmeResolveKZ();
			total += thing->m_value440;
			++it;
			--remaining;
		}
		while (remaining);
	}
	return total;
}
