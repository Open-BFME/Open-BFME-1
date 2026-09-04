// ?refreshArmor@Rva0020E9A0ArmorCache@@QAEXXZ
// partial score=0.96 date=2026-09-04
// cl: /O2

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeSubInnerEFF
{
public:
	void *bfmeGetFinalOverride();
};

struct BfmeArmorSlotE9A
{
	char m_pad00[4];
	int m_value04;
	int m_value08;
};

class BfmeArmorFinderE9A
{
public:
	BfmeArmorSlotE9A *bfmeFindArmorE9A(const void *flags) const;
	const BfmeArmorFinderE9A *bfmeGetFinalOverride() const
	{
		if (m_nextOverride)
			return (const BfmeArmorFinderE9A *)m_nextOverride->bfmeGetFinalOverride();
		return this;
	}

	char m_pad00[4];
	BfmeSubInnerEFF *m_nextOverride;
};

class Rva0020E9A0ArmorCache
{
public:
	void refreshArmor();

private:
	char m_pad00[8];
	BfmeArmorFinderE9A **m_start;
	char m_pad0C[0xD0 - 0x0C];
	int m_flags;
	BfmeArmorSlotE9A *m_cached;
	int m_valueD8;
	int m_valueDC;
};

void Rva0020E9A0ArmorCache::refreshArmor()
{
	BfmeArmorFinderE9A **s = m_start;
	++s;
	_ReadWriteBarrier();
	const BfmeArmorFinderE9A *finder = *s;
	const BfmeArmorFinderE9A *resolved = finder ? finder->bfmeGetFinalOverride() : 0;
	BfmeArmorSlotE9A *slot = resolved->bfmeFindArmorE9A(&m_flags);
	if (slot && slot != m_cached)
	{
		m_valueD8 = slot->m_value04;
		m_valueDC = slot->m_value08;
		m_cached = slot;
	}
}
