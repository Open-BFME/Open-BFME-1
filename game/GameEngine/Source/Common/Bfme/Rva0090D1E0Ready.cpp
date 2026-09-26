// cl: /DNDEBUG /MD /EHsc

class Rva0090D1E0Node
{
public:
	unsigned char m_pad[8];
	int m_inner;
};

class Rva009EB940Receiver
{
public:
	void bump();
	bool ready();

private:
	unsigned char m_pad0[4];
	int m_flags;
	unsigned char m_pad8[0xC];
	Rva0090D1E0Node *m_node;
};

bool Rva009EB940Receiver::ready()
{
	if (m_node && m_node->m_inner)
		return true;
	bump();
	return (m_flags & 0x00FF0000) == 0x00030000;
}
