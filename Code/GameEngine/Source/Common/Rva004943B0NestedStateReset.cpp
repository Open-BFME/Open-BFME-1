class Rva004943B0Nested
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
};

class Rva004943B0
{
public:
	void resetNestedState();

private:
	unsigned char m_padding[0x08];
	Rva004943B0Nested *m_nested;
	unsigned char m_gap0C[0x14];
	unsigned char m_state;
};

void Rva004943B0::resetNestedState()
{
	if (m_nested != 0)
		m_nested->v7();
	m_nested = 0;
	m_state &= 0xFC;
}

class Rva00494640
{
public:
	void resetNestedState();

private:
	unsigned char m_padding[0x08];
	Rva004943B0Nested *m_nested;
	unsigned char m_gap0C[0x14];
	unsigned char m_state;
};

void Rva00494640::resetNestedState()
{
	if (m_nested != 0)
		m_nested->v7();
	m_nested = 0;
	m_state &= 0xFC;
}
