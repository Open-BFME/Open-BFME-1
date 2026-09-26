// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x0014A020 (25 bytes).

class Rva0014A020
{
public:
	void set(void *value);

private:
	unsigned char m_padding[0xEC];
	void *m_value;
};

void Rva0014A020::set(void *value)
{
	void *previous = m_value;
	*reinterpret_cast<void **>(reinterpret_cast<unsigned char *>(value) + 0x1BC) = previous;
	m_value = value;
}
