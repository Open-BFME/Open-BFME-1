// Open-BFME: two-field copy reconstructed from retail RVA 0x003C6F60.

class Rva003C6F60Object
{
public:
	void copyTo(int *output);

private:
	char m_pad0[0x6C];
	int m_first;
	int m_second;
};

void Rva003C6F60Object::copyTo(int *output)
{
	output[0] = m_first;
	output[1] = m_second;
}
