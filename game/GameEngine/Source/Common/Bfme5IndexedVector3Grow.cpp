// BFME5 indexed Vector3 storage growth at retail RVA 0x0018F320.
//
// The append and insert bodies in Bfme5IndexedVector3Setter.cpp and
// Bfme5IndexedVector3Insert.cpp call this method when the indexed storage is
// full.  The element is the upstream WWMath integer vector: its empty default
// constructor is retained so MSVC emits the same vector-construction helper
// as retail.

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block) throw();

struct ICoord3D
{
	ICoord3D(void);

	int x;
	int y;
	int z;
};

class Gen_0018F210
{
public:
	void bfmeGrowVector3(void);

private:
	char m_head[0x10];
	ICoord3D *m_values;
	int m_count;
	int m_capacity;
};

// ?bfmeGrowVector3@Gen_0018F210@@QAEXXZ
void Gen_0018F210::bfmeGrowVector3(void)
{
	if (m_count == m_capacity)
	{
		int new_capacity = m_capacity + m_capacity;
		m_capacity = new_capacity;

		ICoord3D *new_values = new ICoord3D[new_capacity];
		for (int i = 0; i < m_count; ++i)
			new_values[i] = m_values[i];

		::operator delete[](m_values);
		m_values = new_values;
	}
}
