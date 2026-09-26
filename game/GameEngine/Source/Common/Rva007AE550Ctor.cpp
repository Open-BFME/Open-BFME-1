// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva007AE550Base
{
public:
	Rva007AE550Base(int value);
	virtual void dummy();

	int m_value;
};

Rva007AE550Base::Rva007AE550Base(int value)
{
	m_value = value;
}
