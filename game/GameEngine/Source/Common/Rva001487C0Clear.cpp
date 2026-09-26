// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva001487C0Clear
{
public:
	Rva001487C0Clear *clear(int, int);

private:
	int m_value;
};

Rva001487C0Clear *Rva001487C0Clear::clear(int, int)
{
	m_value = 0;
	return this;
}
