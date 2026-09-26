// Release the counted two-dimensional storage without clearing its owner.
__declspec(dllimport) void __cdecl operator delete(void *, unsigned int);

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
		operator delete(m_buffer, (m_columns * m_rows) * sizeof(unsigned int));
}
