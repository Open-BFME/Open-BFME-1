// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0089C860State
{
public:
	Rva0089C860State *initialize(int value);

private:
	int m_value;
	int m_first;
	int m_second;
	int m_third;
};

Rva0089C860State *Rva0089C860State::initialize(int value)
{
	m_value = value;
	m_first = 0;
	m_second = 0;
	m_third = 0;
	return this;
}
