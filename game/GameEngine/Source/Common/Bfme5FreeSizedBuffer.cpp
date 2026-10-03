// Release the counted two-dimensional storage without clearing its owner.
// Retail 0x008C5D50 calls `call dword ptr [0x01337830]` -- the project's
// sized-free slot, not an imported operator delete: the tree's convention
// (BfmeConv1046.cpp, BfmeCopyBackVPD.cpp, BfmeHolder95670.cpp) is to reach the
// sized free through that pointer.
extern void (*TheBfmeFree)(void *storage, unsigned int bytes);

class Gen_008C5D50
{
public:
	void bfmeReleaseBuffer(void);

private:
	int m_reserved;
	unsigned m_rows;
	unsigned m_columns;
	void *m_buffer;
};

void Gen_008C5D50::bfmeReleaseBuffer(void)
{
	if (m_buffer)
		TheBfmeFree(m_buffer, (m_columns * m_rows) * sizeof(unsigned int));
}
