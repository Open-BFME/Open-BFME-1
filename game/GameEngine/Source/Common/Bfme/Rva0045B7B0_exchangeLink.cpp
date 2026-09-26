// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x0045B7B0 (21 bytes).
// Retail exchanges the opaque link at this+0x80 with a caller-provided slot.

class Rva0045B7B0
{
public:
	void exchangeLink(void **slot);

private:
	unsigned char m_unmodelled_000[0x80];
	void *m_link;
};

void Rva0045B7B0::exchangeLink(void **slot)
{
	*slot = m_link;
	m_link = slot;
}
