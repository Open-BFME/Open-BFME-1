// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived conditional setter at 0x000B21A0.

struct Rva000B21A0Object
{
	unsigned char m_prefix[0x28];
	unsigned int m_value;

	void setValue(unsigned int value);
};

void Rva000B21A0Object::setValue(unsigned int value)
{
	if (value != m_value) {
		m_value = value;
	}
}
