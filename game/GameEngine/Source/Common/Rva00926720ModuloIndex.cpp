// cl: /O2 /Ob0

struct Rva00926720Key
{
	unsigned low;
	unsigned high;
};
class Rva00926720ModuloIndex
{
	void *m_reserved;
	unsigned *m_begin;
	unsigned *m_end;
public:
	unsigned index(const Rva00926720Key *key) const;
};
unsigned Rva00926720ModuloIndex::index(const Rva00926720Key *key) const
{
	unsigned count = m_end - m_begin;
	return ((key->high << 16) + key->low) % count;
}
