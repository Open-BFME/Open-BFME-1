class Rva00569330Object
{
public:
	void setFlag(unsigned int unused);

private:
	unsigned char m_prefix[0x25a];
	unsigned char m_flag;
};

void Rva00569330Object::setFlag(unsigned int)
{
	m_flag = 1;
}
