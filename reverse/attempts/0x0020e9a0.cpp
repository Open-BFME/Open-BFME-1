// ?refreshArmor@Rva0020E9A0ArmorCache@@QAEXXZ
// partial score=0.93 date=2026-09-02
// cl: /O2
// Open-BFME: 83-byte armor-cache refresh at retail 0x0020E9A0. Vector start at
// +8 is incremented by one pointer then dereferenced; a null finder skips the
// override walk; otherwise next-at-+4 is getFinalOverride'd. Find-armor on
// &flags at +0xD0; on a new slot copy +4/+8 into +0xD8/+0xDC and cache it.

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
	BfmeArmorSlotE9A *bfmeFindArmorE9A(const void *flags);

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
	s = (BfmeArmorFinderE9A **)((char *)s + 4);
	BfmeArmorFinderE9A *finder = *s;
	BfmeArmorFinderE9A *resolved;
	if (!finder)
		resolved = 0;
	else
	{
		BfmeSubInnerEFF *next = finder->m_nextOverride;
		if (next)
			resolved = (BfmeArmorFinderE9A *)next->bfmeGetFinalOverride();
		else
			resolved = finder;
	}

	BfmeArmorSlotE9A *slot = resolved->bfmeFindArmorE9A(&m_flags);
	if (slot && slot != m_cached)
	{
		m_valueD8 = slot->m_value04;
		m_valueDC = slot->m_value08;
		m_cached = slot;
	}
}
