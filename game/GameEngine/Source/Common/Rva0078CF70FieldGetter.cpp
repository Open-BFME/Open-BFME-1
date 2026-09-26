// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
// Retail 0x0078CF70.  No named caller survives, so the owner is address-scoped;
// the complete body returns its pointer-sized field at offset 0x2C.

class Rva0078CF70Owner
{
public:
	void *getField(void) const;

private:
	char m_head[0x2c];
	void *m_field;
};

void *Rva0078CF70Owner::getField(void) const
{
	return m_field;
}
