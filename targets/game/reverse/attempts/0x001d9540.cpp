// ??0Rva001D9540@@QAE@ABV0@@Z
// partial score=1.0 date=2026-10-05
// The 67-byte body matches every instruction outside relocation operands.
// Inline size(), begin(), and end() accessors produce the retail register order.
// Retail calls pass through thunks at 0x00044166, 0x00001D949, and 0x00018179.
// The direct caller and all helper identities remain unproven, so add_match has
// not verified this source.
struct Rva001D9540Alloc
{
	char m_pad;

	Rva001D9540Alloc();
	Rva001D9540Alloc(const Rva001D9540Alloc &other);
};

class Rva001D9540
{
public:
	Rva001D9540(const Rva001D9540 &src);

	Rva001D9540Alloc allocatorValue() const;
	void initializeBase(unsigned int count, const Rva001D9540Alloc &alloc);
	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}
	void **begin() const { return m_begin; }
	void **end() const { return m_end; }

	void **m_begin;
	void **m_end;
};

extern "C" void **__cdecl copyValues(void **first, void **last, void **dst);

Rva001D9540::Rva001D9540(const Rva001D9540 &src)
{
	initializeBase(src.size(), src.allocatorValue());

	m_end = copyValues(src.begin(), src.end(), begin());
}
