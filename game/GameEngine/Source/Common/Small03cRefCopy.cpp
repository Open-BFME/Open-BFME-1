struct Rva0094C260Src
{
	int m_a;
	void *m_handle;
};
class Rva0094C260Box
{
public:
	Rva0094C260Box *copyFrom(const Rva0094C260Src *src);
	int m_a;
	void *m_handle;
};
// mov eax,ecx / two word copies / null-guarded halfword inc at handle+4.
Rva0094C260Box *Rva0094C260Box::copyFrom(const Rva0094C260Src *src)
{
	m_a = src->m_a;
	m_handle = src->m_handle;
	if (m_handle)
		++*(unsigned short *)((char *)m_handle + 4);
	return this;
}
struct Rva0094C410Src
{
	int m_a;
	void *m_handle;
};
class Rva0094C410Box
{
public:
	Rva0094C410Box *copyFrom(const Rva0094C410Src *src);
	int m_a;
	void *m_handle;
};
Rva0094C410Box *Rva0094C410Box::copyFrom(const Rva0094C410Src *src)
{
	m_a = src->m_a;
	m_handle = src->m_handle;
	if (m_handle)
		++*(unsigned short *)((char *)m_handle + 4);
	return this;
}
