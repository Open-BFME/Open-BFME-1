class Rva0039D0F0
{
	int m_words[6];

public:
	bool equals(const Rva0039D0F0 *other) const;
};

// ?equals@Rva0039D0F0@@QBE_NPBV1@@Z
bool Rva0039D0F0::equals(const Rva0039D0F0 *other) const
{
	for (unsigned int i = 0; i < 6; ++i)
	{
		if (m_words[i] != other->m_words[i])
			return false;
	}
	return true;
}
