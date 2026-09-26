// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x001C0BC0 (20 bytes).

class Rva001C0BC0
{
public:
	void *select();

private:
	unsigned char m_unmodelled_000[0x08];
	unsigned char m_low[0x130];
	unsigned char m_high[0x4C];
	unsigned char m_flag;
};

void *Rva001C0BC0::select()
{
	return m_flag != 0 ? static_cast<void *>(m_high) : static_cast<void *>(m_low);
}
