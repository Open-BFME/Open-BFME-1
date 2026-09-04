// cl: /DNDEBUG /MD /O2

struct Rva009AAC80Context
{
	unsigned char m_pad0[0x1B8];
	int m_at1B8;
	unsigned char m_pad1[0x22C - 0x1BC];
	int m_at22C;
	int m_at230;
	unsigned char m_pad2[0x6F0 - 0x234];
	unsigned char *m_at6F0;
};

void __cdecl Rva009B4390CodecCall(
	void *, int, void *, int, int, int, int, int,
	int, int, int, int, int, int, int);

typedef void (__cdecl *Rva009B4390Four)(void *, int, void *, int);

void __cdecl Rva009AAC80CodecGrid(Rva009AAC80Context *self)
{
	unsigned int rows = self->m_at22C;
	unsigned int width = self->m_at230;
	unsigned int row = 0;

	if (rows > 0)
	{
		int rowOffset = 5;
		do
		{
			unsigned int column = 0;
			if (width > 0)
			{
				unsigned int columnOffset = 0;
				do
				{
					int value = ((const signed char *)self->m_at6F0)[self->m_at230 * row + column];
					int offset = self->m_at1B8 * rowOffset + columnOffset + 5;
					((Rva009B4390Four)Rva009B4390CodecCall)(
						self, offset, (void *)0x0107C7B4, value);
					++column;
					columnOffset += 0x10;
				} while (column < width);
			}
			++row;
			rowOffset += 0x10;
		} while (row < rows);
	}
}
