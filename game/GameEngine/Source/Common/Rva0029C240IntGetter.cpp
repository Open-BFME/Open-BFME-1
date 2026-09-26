// cl: /DNDEBUG /MD /EHsc

class Rva0029C240IntField
{
public:
	int get() const;

	char m_beforeValue[4];
	int m_value;
};

int Rva0029C240IntField::get() const
{
	return m_value;
}
