// cl: /DNDEBUG /MD /EHsc

class Rva00472B60Owner
{
public:
	int GetValue() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva00472B60Owner::GetValue() const
{
	return m_value;
}
