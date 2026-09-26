// Address-derived seven-byte member at 0x0069DE60.

class Rva0069DE60
{
public:
	Rva0069DE60 *clear();

private:
	char m_pad00[ 8 ];
	bool m_flag;
};

Rva0069DE60 *Rva0069DE60::clear()
{
	m_flag = false;
	return this;
}

// The sibling at 0x0069DEB0 has the same observed layout and code shape.
class Rva0069DEB0
{
public:
	Rva0069DEB0 *clear();

private:
	char m_pad00[ 8 ];
	bool m_flag;
};

Rva0069DEB0 *Rva0069DEB0::clear()
{
	m_flag = false;
	return this;
}
