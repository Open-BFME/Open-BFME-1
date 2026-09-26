// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived indexed flag setter at 0x000C8930.

struct Rva000C8930Object
{
	unsigned char m_prefix[0x2a0];
	unsigned int m_flags;

	void setFlag(unsigned int index);
};

void Rva000C8930Object::setFlag(unsigned int index)
{
	m_flags |= 1U << index;
}
