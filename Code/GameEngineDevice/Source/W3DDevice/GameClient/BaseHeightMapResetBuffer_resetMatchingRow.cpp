// cl: /DNDEBUG /MD
//
// Retail 0x0071C940. DualType stride 0xA4, count at +0x1E1CC8, dirty at
// +0x1E1CCC. Cursor parks 8 bytes into the row (+0x1550) so the first three
// dwords land at -8/-4/0.

typedef int Int;
typedef float Real;

class BaseHeightMapResetBuffer
{
public:
	void resetMatchingRow(Int key);

private:
	char m_pad[0x1E1CC8];
	Int m_count;
	unsigned char m_dirty;
};

void BaseHeightMapResetBuffer::resetMatchingRow(Int key)
{
	Int i = 0;
	if (m_count > 0)
	{
		char *row = (char *)this + 0x1550;
		do
		{
			if (*(Int *)(row + 0x54) == key)
			{
				*(Int *)(row - 8) = 0;
				*(Int *)(row - 4) = 0;
				*(Int *)row = 0;
				*(Int *)(row + 0x38) = -2;
				*(Int *)(row + 0x40) = 0;
				*(Int *)(row + 0x44) = 0;
				*(Int *)(row + 0x48) = 0;
				*(Real *)(row + 0x4C) = 1.0f;
				m_dirty = 1;
			}
			++i;
			row += 0xA4;
		} while (i < m_count);
	}
}
