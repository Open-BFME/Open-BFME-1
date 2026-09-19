// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva002A08A0Owner
{
public:
	unsigned int value() const;

private:
	void *m_first;
	unsigned int m_value;
};

unsigned int Rva002A08A0Owner::value() const
{
	return m_value;
}
