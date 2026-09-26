// ?setBit@Rva000D0070BitArray@@QAEXIH@Z
struct Rva000D0070BitArray {
	unsigned int m_bits[1];
	void setBit(unsigned int index, int value);
};
void Rva000D0070BitArray::setBit(unsigned int index, int value)
{
	if (value)
		m_bits[index >> 5] |= 1 << (index & 31);
	else
		m_bits[index >> 5] &= ~(1 << (index & 31));
}
