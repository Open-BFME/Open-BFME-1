// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME: address-derived comparison at 0x000C7E10.

struct Rva000C7E10Object
{
	unsigned int m_prefix;
	int m_limit;
	int m_count;

	bool isLimitAtLeastCount() const;
};

bool Rva000C7E10Object::isLimitAtLeastCount() const
{
	return m_limit >= m_count;
}
