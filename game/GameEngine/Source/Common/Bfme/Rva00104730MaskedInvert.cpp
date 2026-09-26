// cl: /DNDEBUG /MD /EHsc

class Rva00104730
{
public:
	void maskInvert();

private:
	volatile unsigned m_value;
};

void Rva00104730::maskInvert()
{
	m_value = (~m_value) & 0x7FF;
}
