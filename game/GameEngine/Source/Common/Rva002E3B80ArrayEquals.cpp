class T4Host002E3B80
{
public:
	bool equals(const T4Host002E3B80 &other) const;

private:
	int m_val[10];
};

// ?equals@T4Host002E3B80@@QBE_NABV1@@Z
bool T4Host002E3B80::equals(const T4Host002E3B80 &other) const
{
	for (unsigned int i = 0; i < 10; ++i)
	{
		if (m_val[i] != other.m_val[i])
			return false;
	}
	return true;
}
