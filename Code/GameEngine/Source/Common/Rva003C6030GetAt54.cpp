class Rva003C6030
{
public:
	void *getAt54();

private:
	char m_padding[ 0x54 ];
	char m_value;
};

void *Rva003C6030::getAt54()
{
	return &m_value;
}
