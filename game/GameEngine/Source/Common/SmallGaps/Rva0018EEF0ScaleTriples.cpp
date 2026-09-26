// ?scaleTriples@Rva0018EEF0Owner@@QAEXM@Z
extern unsigned int g_bfmeDirtyBG;
struct Rva0018EEF0Triple { int x; int y; int z; };
struct Rva0018EEF0Owner {
	char m_pad[0x10];
	Rva0018EEF0Triple* m_triples;
	int m_count;
	char m_pad2[0x30 - 0x18];
	bool m_dirty;
	void scaleTriples(float scale);
};
void Rva0018EEF0Owner::scaleTriples(float scale)
{
	g_bfmeDirtyBG |= 1;
	for (int i = 0; i < m_count; ++i) {
		m_triples[i].x = (int)(m_triples[i].x * scale);
		m_triples[i].y = (int)(m_triples[i].y * scale);
		m_triples[i].z = (int)(m_triples[i].z * scale);
	}
	m_dirty = true;
}
