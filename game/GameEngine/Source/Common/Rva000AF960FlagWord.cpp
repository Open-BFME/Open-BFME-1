// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived flag-word operations at 0x000AF960/0x000AF980.

struct Rva000AF960Object
{
	unsigned char m_prefix[0x3c];
	unsigned int m_flags;

	void addFlags(unsigned int flags);
	void removeFlags(unsigned int flags);
};

void Rva000AF960Object::addFlags(unsigned int flags)
{
	m_flags |= flags;
}

void Rva000AF960Object::removeFlags(unsigned int flags)
{
	m_flags &= ~flags;
}
