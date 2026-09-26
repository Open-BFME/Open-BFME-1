class Rva0014EEF0Object
{
public:
	void clearChildFlag(unsigned int unused);

private:
	unsigned char m_prefix[0x1c];
	unsigned char *m_child;
};

void Rva0014EEF0Object::clearChildFlag(unsigned int)
{
	m_child[0x40] = 0;
}
