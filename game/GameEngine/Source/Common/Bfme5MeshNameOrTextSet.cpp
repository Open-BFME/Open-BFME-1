class LightEnvironmentClass
{
public:
	LightEnvironmentClass &operator=(const LightEnvironmentClass &other);
};

class Gen_0092E440
{
public:
	void bfmeSet(const char *text);

private:
	char m_bfmeHead[0xCC];					// +0x00
	const void *m_ptr;					// +0xCC
	LightEnvironmentClass m_embedded;			// +0xD0
};

// ?bfmeSet@Gen_0092E440@@QAEXPBD@Z
void Gen_0092E440::bfmeSet(const char *text)
{
	if (text)
	{
		if (text[0] != 0)
		{
			m_ptr = text;
			return;
		}

		m_embedded = *(const LightEnvironmentClass *)text;
		m_ptr = &m_embedded;
		return;
	}

	m_ptr = 0;
}
