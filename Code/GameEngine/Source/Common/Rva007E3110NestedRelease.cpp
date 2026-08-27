class Rva007E3110Nested
{
public:
	virtual void v0(); virtual void v1(); virtual void v2();
};

class Rva007E3110
{
public:
	bool releaseNested();

private:
	unsigned char m_padding[0x04];
	Rva007E3110Nested *m_nested;
};

bool Rva007E3110::releaseNested()
{
	if (m_nested != 0)
	{
		m_nested->v2();
		m_nested = 0;
		return true;
	}
	return false;
}
