// ?maxOverrideField43C@Rva0015A560List@@QBEHXZ
// Open-BFME: clean reconstruction of retail 0x0015A560.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef int Int;

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	unsigned char m_pad00[4];
	BfmeOverridable *m_nextOverride;
	unsigned char m_pad08[0x43C - 0x08];
	Int m_value43C;
};

class Rva0015A560List
{
public:
	Int maxOverrideField43C() const;

	Int m_count;
	BfmeOverridable **m_items[1];
};

Int Rva0015A560List::maxOverrideField43C() const
{
	Int best = 0;
	if (m_count > 0)
	{
		BfmeOverridable **const *it = m_items;
		Int remaining = m_count;
		do
		{
			unsigned int *objectData = (unsigned int *)*it;
			++objectData;
			_ReadWriteBarrier();
			BfmeOverridable *tmpl = *(BfmeOverridable **)objectData;
			if (tmpl && tmpl->m_nextOverride)
				tmpl = tmpl->m_nextOverride->friend_getFinalOverride();
			Int value = tmpl->m_value43C;
			if (value > best)
				best = value;
			++it;
			--remaining;
		}
		while (remaining);
	}
	return best;
}
