// cl: /DNDEBUG /MD /EHsc

class Rva003AC410Owner
{
public:
	int GetValue() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva003AC410Owner::GetValue() const
{
	return m_value;
}
