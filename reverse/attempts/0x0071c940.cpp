// ?resetMatchingRow@BaseHeightMapResetBuffer@@QAEXH@Z
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x0071C940. Same 0xA4 DualType array as stampShroudVisible. On a key
// match zero a block of fields set a -2 sentinel and 1.0f then mark dirty.
// Near miss: MSVC 7.1 parks the cursor at the row head (+0x1548) with
// non-negative displacements; retail parks it 8 bytes in (+0x1550) and uses
// -8/-4. Prologue loop-control and dirty store already match.

typedef int Int;
typedef float Real;

struct BaseHeightMapResetRowC940
{
	Int m_0;
	Int m_4;
	Int m_8;
	char m_pad0c[0x34];
	Int m_40;
	char m_pad44[4];
	Int m_48;
	Int m_4c;
	Int m_50;
	Real m_54;
	char m_pad58[4];
	Int m_key;
	char m_pad60[0x44];
};

class BaseHeightMapResetBuffer
{
public:
	void resetMatchingRow(Int key);

private:
	char m_pad[0x1548];
	BaseHeightMapResetRowC940 m_rows[11999];
	char m_pad2[0xa4];
	Int m_count;
	unsigned char m_dirty;
};

void BaseHeightMapResetBuffer::resetMatchingRow(Int key)
{
	for (Int i = 0; i < m_count; ++i)
	{
		if (m_rows[i].m_key == key)
		{
			m_rows[i].m_0 = 0;
			m_rows[i].m_4 = 0;
			m_rows[i].m_8 = 0;
			m_rows[i].m_40 = -2;
			m_rows[i].m_48 = 0;
			m_rows[i].m_4c = 0;
			m_rows[i].m_50 = 0;
			m_rows[i].m_54 = 1.0f;
			m_dirty = 1;
		}
	}
}
