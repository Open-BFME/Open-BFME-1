// Two small leaf bodies neighbouring earlier Small03b landings.
// IDENTITY IS NOT RECOVERED: every name keeps its address token.
struct Rva00933920Elem
{
	char m_data[0x2C];
};
class Rva00933920Box
{
public:
	Rva00933920Elem *at(int i);
	Rva00933920Elem *m_data;
	int m_pad4;
	unsigned int m_size;
};
// unsigned clamp: past-the-end index returns the base pointer.
Rva00933920Elem *Rva00933920Box::at(int i)
{
	if ((unsigned int)i >= m_size)
		return m_data;
	return m_data + i;
}
class MeshModelClass
{
public:
	int Compute_Ram_Size();
};
class Rva0092C4B0Box
{
public:
	int ramSize() const;
	char m_pad[0xC8];
	MeshModelClass *m_model;
};
// null-guarded: a missing model reports the bare 0x318 base.
int Rva0092C4B0Box::ramSize() const
{
	int size = 0x318;
	if (m_model)
		size += m_model->Compute_Ram_Size();
	return size;
}
