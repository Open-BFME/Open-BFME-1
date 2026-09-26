// ?setBit8@Rva008993E0Owner@@QAEXH@Z
struct Rva008993E0Owner {
	char m_pad[0x1c];
	union { unsigned int m_flags; struct { unsigned int m_low : 8; unsigned int m_bit8 : 1; }; };
	void setBit8(int value);
	int getBit8();
};
void Rva008993E0Owner::setBit8(int value)
{
	m_bit8 = value != 0;
}
// ?getBit8@Rva008993E0Owner@@QAEHXZ
int Rva008993E0Owner::getBit8()
{
	return m_bit8;
}
