class Rva000B8050DwordField30Getter
{
public:
	unsigned int get() const;

private:
	unsigned char m_padding[0x30];
	unsigned int m_value;
};

unsigned int Rva000B8050DwordField30Getter::get() const
{
	return m_value;
}
