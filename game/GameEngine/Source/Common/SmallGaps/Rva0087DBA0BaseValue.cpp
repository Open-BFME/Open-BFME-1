// ?getValue@Rva0087DBA0Owner@@QBEMXZ
struct Rva0087DBA0Owner { int m_mode; float m_a; float m_b; int m_pad[3]; float m_offset; float getValue() const; };
float Rva0087DBA0Owner::getValue() const
{
	float v = 0.0f;
	switch (m_mode) { case 0: v = m_b; break; case 1: case 2: v = m_a; break; }
	return v + m_offset;
}
