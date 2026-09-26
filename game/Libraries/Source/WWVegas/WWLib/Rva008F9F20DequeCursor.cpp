// cl: /O2 /Ob0

class Rva008F9F20DequeCursor
{
	unsigned char *m_current;
	unsigned char *m_first;
	unsigned char *m_last;
	unsigned char **m_map;
public:
	Rva008F9F20DequeCursor &advance();
};
Rva008F9F20DequeCursor &Rva008F9F20DequeCursor::advance()
{
	m_current += 8;
	if (m_current == m_last) {
		m_first = *++m_map;
		m_last = m_first + 0x80;
		m_current = m_first;
	}
	return *this;
}
