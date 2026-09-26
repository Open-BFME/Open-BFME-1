// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x0049D2E0 (27 bytes).

class Rva0049D2E0
{
public:
	void get(void **first, void **second);

private:
	unsigned char m_padding[0x2D8];
	void *m_first;
	void *m_second;
};

void Rva0049D2E0::get(void **first, void **second)
{
	*first = m_first;
	*second = m_second;
}
