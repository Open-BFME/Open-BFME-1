// ?refreshArmor@Rva0020E9A0ArmorCache@@QAEXXZ
// partial score=0.9 date=2026-09-01
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
	BfmeArmorFinderE9A *getFinalOverrideE9A()
	{
		return m_nextOverride ?
			static_cast<BfmeArmorFinderE9A *>(m_nextOverride->bfmeGetFinalOverride()) : this;
	}
	char m_pad00[4];
	BfmeSubInnerEFF *m_nextOverride;
};

class BfmeFinderVectorE9A
{
public:
	BfmeArmorFinderE9A *&operator[](int index) { return *(m_start + index); }

private:
	BfmeArmorFinderE9A **m_start;
};

class Rva0020E9A0ArmorCache
{
public:
	void refreshArmor();

private:
	char m_pad00[8];
	BfmeFinderVectorE9A m_sources;
	char m_pad0C[0xD0 - 0x0C];
	int m_flags;
	BfmeArmorSlotE9A *m_cached;
	int m_valueD8;
	int m_valueDC;
};

void Rva0020E9A0ArmorCache::refreshArmor()
{
	BfmeArmorFinderE9A *finder = m_sources[1];
	if (finder)
		finder = finder->getFinalOverrideE9A();

	BfmeArmorSlotE9A *slot = finder->bfmeFindArmorE9A(&m_flags);
	if (slot && slot != m_cached)
	{
		m_valueD8 = slot->m_value04;
		m_valueDC = slot->m_value08;
		m_cached = slot;
	}
}
