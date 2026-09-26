// The carved body at 0x002E3B40 compares three dword fields.
class Rva002E3B40Array
{
public:
	bool equals(const Rva002E3B40Array &other) const;

private:
	int m_val[3];
};

bool Rva002E3B40Array::equals(const Rva002E3B40Array &other) const
{
	for (unsigned int i = 0; i < 3; ++i)
	{
		if (m_val[i] != other.m_val[i])
			return false;
	}
	return true;
}
