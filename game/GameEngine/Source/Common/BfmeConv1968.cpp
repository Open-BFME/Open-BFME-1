class BfmeSubESD
{
public:
	void bfmeAssignESD(void *a, void *b, void **spare);

	BfmeSubESD &operator=(const BfmeSubESD &other)
	{
		if (&other != this)
		{
			void *spare;

			bfmeAssignESD(other.m_bfmeAESD, other.m_bfmeBESD, &spare);
		}

		return *this;
	}

	void *m_bfmeAESD;
	void *m_bfmeBESD;
	void *m_bfmeCESD;
};

class BfmeRecESD
{
public:
	BfmeRecESD &operator=(const BfmeRecESD &other);

	BfmeSubESD m_bfmeXESD;
	BfmeSubESD m_bfmeYESD;
	BfmeSubESD m_bfmeZESD;
	int m_bfme24ESD;
	int m_bfme28ESD;
};

BfmeRecESD &BfmeRecESD::operator=(const BfmeRecESD &other)
{
	m_bfmeXESD = other.m_bfmeXESD;
	m_bfmeYESD = other.m_bfmeYESD;
	m_bfmeZESD = other.m_bfmeZESD;

	m_bfme24ESD = other.m_bfme24ESD;
	m_bfme28ESD = other.m_bfme28ESD;

	return *this;
}
