// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x00670C80 (25 bytes).

class Rva00670C80
{
public:
	void set(unsigned short value);

private:
	unsigned char m_padding08[8];
	unsigned *m_table;
	unsigned char m_padding0C[4];
	unsigned m_index;
	unsigned char m_padding14[0x54];
};

void Rva00670C80::set(unsigned short value)
{
	unsigned index = m_index;
	unsigned key = *reinterpret_cast<unsigned *>(
		reinterpret_cast<unsigned char *>(this) + 0x68 + index * 8);
	unsigned *table = m_table;
	unsigned char *target = reinterpret_cast<unsigned char *>(table[key]);
	*reinterpret_cast<unsigned short *>(target + 0x34) = value;
}
