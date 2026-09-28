// ?d_0094be70@@YAXXZ
// partial score=0.71 date=2026-09-28
// cl: /DNDEBUG /MD
class Rva0094BE70Box
{
public:
	unsigned int m_key;
	unsigned int isLess(const Rva0094BE70Box *other) const;
	unsigned int getKey() const;
};
unsigned int Rva0094BE70Box::isLess(const Rva0094BE70Box *other) const
{
	return m_key < other->m_key;
}
unsigned int Rva0094BE70Box::getKey() const
{
	return m_key;
}
