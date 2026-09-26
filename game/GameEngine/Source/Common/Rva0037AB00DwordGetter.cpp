// cl: /DNDEBUG /MD

class Rva0037AB00Object
{
public:
	int getValue() const;

private:
	char m_padding[4];
	int m_value;
};

int Rva0037AB00Object::getValue() const
{
	return m_value;
}
