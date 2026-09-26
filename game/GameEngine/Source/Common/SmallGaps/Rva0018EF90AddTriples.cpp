// ?addTriples@Rva0018EF90Owner@@QAEXPBM@Z
extern "C" long __ftol2(double value);

struct Rva0018EF90Triple { int x; int y; int z; };
struct Rva0018EF90Owner {
	char m_pad[0x10];
	Rva0018EF90Triple *m_triples;
	int m_count;
	char m_pad2[0x30 - 0x18];
	bool m_dirty;
	void addTriples(const float *delta);
};

void Rva0018EF90Owner::addTriples(const float *delta)
{
	for (int i = 0; i < m_count; ++i) {
		m_triples[i].x = (int)(m_triples[i].x + delta[0]);
		m_triples[i].y = (int)(m_triples[i].y + delta[1]);
		m_triples[i].z = (int)(m_triples[i].z + delta[2]);
	}
	m_dirty = true;
}
