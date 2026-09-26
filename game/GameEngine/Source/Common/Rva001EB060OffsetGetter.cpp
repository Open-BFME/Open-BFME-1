class Rva001EB060Accessor
{
	public:
	unsigned int get(unsigned int index);

	private:
	unsigned char m_prefix[0x18];
	unsigned int m_values[1];
};

unsigned int Rva001EB060Accessor::get(unsigned int index)
{
	return m_values[index];
}
