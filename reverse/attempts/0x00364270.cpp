// ?setFields@Rva00364270Owner@@QAEXURva00364270Data@@@Z
// partial score=0.68 date=2026-09-21
// cl: /O2 /Ob2 /G6
//
// Address-derived at retail RVA 0x00364270. No caller, vtable entry, string
// or data-pointer xref names an owner (adjacent 0x00364210 is also
// anonymous), so the class/method keep the address token. The body copies a
// ten-dword-by-value argument block into this+0x50 with `rep movsd`, then
// masks each of those ten dwords in place against a lazily-initialized
// static mask table at retail 0x012F07A4..0x012F07C8 (mask[6] defaults to
// 0x20000, the rest zero); the guard byte/bit at 0x012F07D4 is MSVC's own
// local-static-object init guard for that table.

struct Rva00364270Data
{
	unsigned int w[10];
};

struct Rva00364270Masks
{
	Rva00364270Masks()
	{
		w[0] = 0;
		w[1] = 0;
		w[2] = 0;
		w[3] = 0;
		w[4] = 0;
		w[5] = 0;
		w[6] = 0x20000;
		w[7] = 0;
		w[8] = 0;
		w[9] = 0;
	}

	unsigned int w[10];
};

class Rva00364270Owner
{
public:
	void setFields(Rva00364270Data data);

private:
	unsigned char m_pad[0x50];
	Rva00364270Data m_fields;			// +0x50
};

void Rva00364270Owner::setFields(Rva00364270Data data)
{
	static Rva00364270Masks s_masks;

	m_fields = data;

	m_fields.w[0] &= s_masks.w[0];
	m_fields.w[1] &= s_masks.w[1];
	m_fields.w[2] &= s_masks.w[2];
	m_fields.w[3] &= s_masks.w[3];
	m_fields.w[4] &= s_masks.w[4];
	m_fields.w[5] &= s_masks.w[5];
	m_fields.w[6] &= s_masks.w[6];
	m_fields.w[7] &= s_masks.w[7];
	m_fields.w[8] &= s_masks.w[8];
	m_fields.w[9] &= s_masks.w[9];
}
